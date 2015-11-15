//==============================================================================
//
// File   : SceneGame.cpp
// Brief  : �Q�[���V�[���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "SceneGame.h"
#include "../framework/camera/CameraObject.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/develop/DebugMeasure.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/VirtualController.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/light/LightDirection.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/ManagerMotion.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/Window.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerPoint.h"
#include "../system/ManagerFireworks.h"
#include "../system/ManagerTarget.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"
#include "../system/fire/Fire.h"

// �e�X�g
#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectModelMaterial.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectSky.h"
#include "../object/ObjectBillboard.h"
#include "../object/ObjectScore.h"
#include "../object/ObjectSkinMesh.h"
#include "../object/ObjectWaterwheel.h"

#include "../framework/system/ManagerDraw.h"
#include "../graphic/graphic/GraphicPoint.h"
#include "../framework/polygon/PolygonPoint.h"

#include "../framework/radianTable/radianTable.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define RANDOM(value) (float)((rand() % value) - (rand() % value))
#define SQUARE(_value) (_value * _value)

//******************************************************************************
// �ÓI�ϐ�
//******************************************************************************
//	�����@�����̃T�C�Y
static const float stringXX_NormalSizeX = 400.0f;
static const float stringXX_NormalSizeY = 120.0f;

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pCamera_ = nullptr;
	pLight_ = nullptr;

	//	�Q�[��UI�֌W
	//----------------------------------------------------------
	stringScore = nullptr;
	score = nullptr;
	pauseFrame = nullptr;
	stringReturn = nullptr;
	stringStop = nullptr;
	stringRetry = nullptr;
	stringNext = nullptr;
	reConnectWiimote = nullptr;
	reConnectWiiboard = nullptr;
	finger = nullptr;
	chooseObject = nullptr;
	chooseObjectPrev = nullptr;

	pushChooseObjectFlashingCount = 0;
	chooseFlag = false;
	//----------------------------------------------------------



	//	�Q�[���p�X�e�[�W�E�RD�I�u�W�F�N�g�֌W
	//----------------------------------------------------------
	pObjectSky_ = nullptr;
	waterWheel[0] = nullptr;
	waterWheel[1] = nullptr;
	waterWheel[2] = nullptr;
	house[0] = nullptr;
	house[1] = nullptr;
	house[2] = nullptr;

	bridge = nullptr;
	field = nullptr;

	player = nullptr;
	playerArm = nullptr;

	managerPoint = nullptr;
	managerFireworks = nullptr;
	managerTarget = nullptr;

	pObjectSkinMesh_[0] = nullptr;
	pObjectSkinMesh_[1] = nullptr;
	pObjectSkinMesh_[2] = nullptr;

	launchFlag = false;
	launchCount = 0;

	for(int count = 0;count < FIREWORKS_MAX;count++)
		fireworksTable[count] = -1;

	for(int count = 0;count < TARGET_MAX;count++)
		targetTable[count] = -1;

	fireworksTableIndex = 0;
	targetTableIndex = 0;
	//----------------------------------------------------------


	cameraState = CAMERA_STATE_FRONT;
	fpUpdate = nullptr;



	// SceneGame2�̃N���X��������
	InitializeSelf2();



	targetAppearCount = 0;
	buffWiiAccel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	buffWiiRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
int SceneGame::Initialize( SceneArgumentMain* pArgument )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Initialize( pArgument );
	if( result != 0 )
	{
		return result;
	}

	//	���색�W�A���e�[�u��
	CRadianTable::Init();

	// �J�����̐���
	pCamera_ = new CameraObject();
	if( pCamera_ == nullptr )
	{
		return 1;
	}
	result = pCamera_->Initialize(
		D3DX_PI / 4.0f,
		pArgument->pWindow_->GetWidth(),
		pArgument->pWindow_->GetHeight(),
		0.1f,
		10000.0f,
		D3DXVECTOR3( 0.0f, 120.0f, -2400.0f ),
		D3DXVECTOR3( 0.0f, 720.0f, 0.0f ),
		D3DXVECTOR3( 0.0f, 1.0f, 0.0f )
		);

	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetCamera( GraphicMain::CAMERA_GENERAL, pCamera_ );

	// ���C�g�̐���
	pLight_ = new LightDirection();
	if( pLight_ == nullptr )
	{
		return 1;
	}
	result = pLight_->Initialize( D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR3( 0.0f, -0.7f, 0.7f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL, pLight_ );




	//	�X�e�[�W�I�u�W�F�N�g�̐���
	InitializeStage(pArgument);

	//	�RD�I�u�W�F�N�g�̐���
	Initialize3DObject(pArgument);

	//	UI�֘A�̏�����
	InitializeUI(pArgument);



	//	�f�t�H���g�̑I�������u�ĊJ�v�ɐݒ�
	chooseObject = stringReturn;

	//	wii�����R�����o�^����Ă�ꍇ�͓o�^���Ȃ�
	if(pArgument_->pWiiController_->getIsConnectWiimote() == true)
		chooseObject = nullptr;

	// SceneGame2�̏�����
	result = Initialize2();
	if( result != 0 )
	{
		return result;
	}

	//	�X�V�֐��ݒ�
	fpUpdate = &SceneGame::normalUpdate;

	// �t�F�[�h�C��
	pArgument->pFade_->FadeIn( 20 );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�e�[�W�֘A�̓ǂݍ��ݏ���
// Return : void								: �Ȃ�
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
void SceneGame::InitializeStage(SceneArgumentMain* pArgument)
{
	//	�I�u�W�F�N�g�̐����J�n
	Effect*		pEffect = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;


	// �X�J�C�h�[���̐���
	Effect*	pEffectSky = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "common/sky.jpg" ) );
	pObjectSky_ = new ObjectSky();
	pObjectSky_->Initialize( 0, pArgument->pDevice_, 32, 32, 5000.0f, 1.0f, 1.0f );
	pObjectSky_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSky, pTexture );


	//	���̃t�B�[���h
	pModel = pArgument_->pModel_->Get( _T( "testfield_01_low.x" ) );
	pEffect = pArgument_->pEffect_->Get( _T( "Model.fx" ) );
	field = new ObjectModel();
	field->Initialize(0);
	field->CreateGraphic( 0, pModel,pArgument->pEffectParameter_, pEffect);
	field->SetScale(5.0f, 5.0f, 5.0f);
	field->AddPositionY(-300.0f);

	//	���ԃI�u�W�F�N�g�̐���
	waterWheel[0] = new ObjectWaterwheel;
	waterWheel[0]->Initialize(
		D3DXVECTOR3(-2500.0f, 200.0f, -300.0f),
		DEG_TO_RAD(90),
		0.001f,
		pArgument);

	waterWheel[1] = new ObjectWaterwheel;
	waterWheel[1]->Initialize(
		D3DXVECTOR3(-2500.0f, 200.0f, -900.0f),
		DEG_TO_RAD(90),
		0.001f,
		pArgument);

	waterWheel[2] = new ObjectWaterwheel;
	waterWheel[2]->Initialize(
		D3DXVECTOR3(-2500.0f, 200.0f, -1500.0f),
		DEG_TO_RAD(90),
		0.001f,
		pArgument);


	//	�Ɛ���
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "house_002.x" ) );
	house[0] = new ObjectModelMaterial();
	house[0]->Initialize(0);
	house[0]->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	house[0]->SetPosition(3200.0f, 100.0f, -700.0f);
	house[0]->SetScale(30.0f, 30.0f, 30.0f);
	
	house[1] = new ObjectModelMaterial();
	house[1]->Initialize(0);
	house[1]->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	house[1]->SetPosition(3200.0f, 100.0f, -1300.0f);
	house[1]->SetScale(30.0f, 30.0f, 30.0f);
	
	house[2] = new ObjectModelMaterial();
	house[2]->Initialize(0);
	house[2]->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	house[2]->SetPosition(3200.0f, 100.0f, -1900.0f);
	house[2]->SetScale(30.0f, 30.0f, 30.0f);

	//	������
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "bridge.x" ) );
	bridge = new ObjectModelMaterial();
	bridge->Initialize(0);
	bridge->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	bridge->SetPosition(0.0f, 1000.0f, 2300.0f);
	bridge->SetScale(350.0f, 350.0f, 350.0f);
	bridge->SetRotationY(DEG_TO_RAD(90));
}

//==============================================================================
// Brief  : ���̑��RD�I�u�W�F�N�g�̓ǂݍ��ݏ���
// Return : void								: �Ȃ�
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
void SceneGame::Initialize3DObject(SceneArgumentMain* pArgument)
{
	//	�I�u�W�F�N�g�̐����J�n
	Effect*		pEffect = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;
	int		result;		// ���s����


	//	�|�C���g�X�v���C�g�Ǘ��I�u�W�F�N�g����
	Effect*		pEffectPoint = nullptr;			// �|�C���g�G�t�F�N�g
	Texture*	pTexturePoint = nullptr;		// �|�C���g�e�N�X�`��
	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pTexturePoint = pArgument->pTexture_->Get( _T( "common/effect000.jpg" ) );
	managerPoint = new ManagerPoint();
	if( managerPoint == nullptr )
	{
		//return 1;
	}
	result = managerPoint->Initialize( 10000, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pTexturePoint->pTexture_ );
	if( result != 0 )
	{
		//return result;
	}

	//	�ΉԃI�u�W�F�N�g�̃X�e�[�g������
	Fire::InitializeState();

	//	�ԉΊǗ��I�u�W�F�N�g����
	managerFireworks = new ManagerFireworks;
	managerFireworks->Initialize(managerPoint);

	//	�^�[�Q�b�g�Ǘ��I�u�W�F�N�g����
	Effect*		pEffectTarget = pArgument->pEffect_->Get( _T( "Billboard.fx" ) );
	Texture*	pTextureCross = pArgument->pTexture_->Get( _T( "game/targetCross.png" ) );
	Texture*	pTextureArrow = pArgument->pTexture_->Get( _T( "game/targetArrow.png" ) );
	Texture*	pTextureCircle = pArgument->pTexture_->Get( _T( "game/targetCircle.png" ) );
	managerTarget = new ManagerTarget;
	managerTarget->Initialize(
		pArgument->pDevice_,
		pArgument->pEffectParameter_,
		pEffectTarget,
		pTextureCross,
		pTextureArrow,
		pTextureCircle
		);


	//	�v���C���[�I�u�W�F�N�g
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument_->pModel_->Get( _T( "kuma.x" ) );
	player = new ObjectModelMaterial();
	player->Initialize(0);
	player->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);

	player->SetPositionX(-30.0f);
	player->SetPositionY(100.0f);
	player->SetPositionZ(-2000.0f);
	player->SetScale(2.0f, 2.0f, 2.0f);


	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument_->pModel_->Get( _T( "arm_r.x" ) );
	playerArm = new ObjectModelMaterial();
	playerArm->Initialize(0);
	playerArm->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);

	playerArm->SetPositionY(150.0f);
	playerArm->SetPositionX(0.0f);
	playerArm->SetPositionZ(-2000.0f);
	playerArm->SetScale(3.0f, 3.0f, 3.0f);


	// �X�L�����b�V���̐���
	Effect*	pEffectSkinMesh = nullptr;		// �G�t�F�N�g
	Model*	pModelSkinMesh = nullptr;		// ���f��
	pEffectSkinMesh = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pModelSkinMesh = pArgument_->pModel_->Get( _T( "test.model" ) );
	pObjectSkinMesh_[0] = new ObjectSkinMesh();
	pObjectSkinMesh_[0]->Initialize( 0, 1 );
	pObjectSkinMesh_[0]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh );
	pObjectSkinMesh_[0]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[0]->SetPosition( 300.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[1] = new ObjectSkinMesh();
	pObjectSkinMesh_[1]->Initialize( 0, 1 );
	pObjectSkinMesh_[1]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh );
	pObjectSkinMesh_[1]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[1]->SetPosition( 0.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[2] = new ObjectSkinMesh();
	pObjectSkinMesh_[2]->Initialize( 0, 1 );
	pObjectSkinMesh_[2]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh );
	pObjectSkinMesh_[2]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[2]->SetPosition( -300.0f, 100.0f, 0.0f );
}

//==============================================================================
// Brief  : UI�֘A�̓ǂݍ��ݏ���
// Return : void								: �Ȃ�
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
void SceneGame::InitializeUI(SceneArgumentMain* pArgument)
{
	//	�I�u�W�F�N�g�̐����J�n
	Effect*		pEffect = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;


	//	�u�X�R�A�v�����I�u�W�F�N�g����
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "game/stringScore.png" ) );

	stringScore = new Object2D;
	stringScore->Initialize(0);

	stringScore->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringScore->SetScale(150.0f, 80.0f, 0.0f);
	stringScore->SetPosition(-550.0f, 300.0f, 0.0f);



	//	�X�R�A�I�u�W�F�N�g����
	pTexture = pArgument_->pTexture_->Get( _T( "common/number.png" ) );

	score = new ObjectScore;
	score->Initialize(0, 10);

	score->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	score->SetSizeX(32.0f);
	score->SetSizeY(32.0f);
	score->SetPosX(-470.0f);
	score->SetPosY(300.0f);

	score->SetScoreFuture(123456789);


	//	�|�[�Y���p�w�i�I�u�W�F�N�g����
	pTexture = pArgument_->pTexture_->Get( _T( "common/fade.jpg" ) );

	pauseFrame = new Object2D;
	pauseFrame->Initialize(0);

	pauseFrame->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	pauseFrame->SetColor(1.0f, 1.0f, 1.0f,0.5f);
	pauseFrame->SetScale(1280.0f * 0.7f, 720.0f * 0.7f, 0.0f);
	pauseFrame->SetEnableGraphic(false);



	//	�u�ĊJ�v�����I�u�W�F�N�g�̐���
	pTexture = pArgument_->pTexture_->Get( _T( "game/pause/stringReturn.png" ) );

	stringReturn = new Object2D;
	stringReturn->Initialize(0);

	stringReturn->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringReturn->SetPosition(0.0f, 200.0f, 0.0f);
	stringReturn->SetScale(stringXX_NormalSizeX, stringXX_NormalSizeY, 0.0f);
	stringReturn->SetEnableGraphic(false);



	//	�u���~�v�����I�u�W�F�N�g�̐���
	pTexture = pArgument_->pTexture_->Get( _T( "game/pause/stringStop.png" ) );

	stringStop = new Object2D;
	stringStop->Initialize(0);

	stringStop->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringStop->SetPosition(0.0f, 0.0f, 0.0f);
	stringStop->SetScale(stringXX_NormalSizeX, stringXX_NormalSizeY, 0.0f);
	stringStop->SetEnableGraphic(false);



	//	�u���߂���v�����I�u�W�F�N�g�̐���
	pTexture = pArgument_->pTexture_->Get( _T( "game/pause/stringRetry.png" ) );

	stringRetry = new Object2D;
	stringRetry->Initialize(0);

	stringRetry->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringRetry->SetPosition(0.0f, -200.0f, 0.0f);
	stringRetry->SetScale(stringXX_NormalSizeX, stringXX_NormalSizeY, 0.0f);
	stringRetry->SetEnableGraphic(false);



	//	wii�����R�����ڑ�����Ă����
	//	�w�̏�����
	if(pArgument_->pWiiController_->getIsConnectWiimote() == true)
	{
		pTexture = pArgument_->pTexture_->Get( _T( "common/finger.png" ) );
		finger = new Object2D;
		finger->Initialize(0);

		finger->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		finger->SetScale(50.0f, 50.0f, 0.1f);
		finger->SetEnableGraphic(false);

		//	IR�őI���ɕύX
		chooseFlag = true;


		//	�uwii�����R���Đڑ��v���v�I�u�W�F�N�g����
		pTexture = pArgument_->pTexture_->Get( _T( "common/reConnectWiimote.png" ) );
		reConnectWiimote = new Object2D;
		reConnectWiimote->Initialize(1);

		reConnectWiimote->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		reConnectWiimote->SetEnableGraphic(false);


		//	�uwii�{�[�h�Đڑ��v���v�I�u�W�F�N�g����
		pTexture = pArgument_->pTexture_->Get( _T( "common/reConnectWiiboard.png" ) );
		reConnectWiiboard = new Object2D;
		reConnectWiiboard->Initialize(1);

		reConnectWiiboard->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		reConnectWiiboard->SetEnableGraphic(false);
	}
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
int SceneGame::Reinitialize( SceneArgumentMain* pArgument )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pArgument );
}