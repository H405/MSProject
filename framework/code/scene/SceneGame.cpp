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
#include "../framework/graphic/Material.h"
#include "../framework/input/VirtualController.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/light/LightDirection.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/Window.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerPoint.h"
#include "../system/ManagerFireworks.h"
#include "../system/ManagerTarget.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

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
#include "../object//ObjectScore.h"

#include "../graphic/graphic/GraphicPoint.h"
#include "../framework/polygon/PolygonPoint.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define RANDAM(value) (float)((rand() % value) - (rand() % value))

//******************************************************************************
// �ÓI�ϐ�
//******************************************************************************
//	�_�ŗp�J�E���g��
static const int flashingCountHirf = 20;
static const int flashingCountMax = 40;

//	�����@�����̃T�C�Y
static const float stringXX_NormalSizeX = 400.0f;
static const float stringXX_NormalSizeY = 120.0f;

//	�����l���Z�l
static const float addFlashingAlpha = 0.02f;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneGame::SceneGame( void ) : SceneMain()
{
	// �N���X���̏���������
	InitializeSelf();

	buffFlag = false;
}

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
	pObjectSky_ = nullptr;
	pauseFrame = nullptr;
	stringScore = nullptr;
	stringReturn = nullptr;
	stringStop = nullptr;
	stringRetry = nullptr;
	stringNext = nullptr;

	testArm = nullptr;
	testObj[0] = nullptr;
	testObj[1] = nullptr;
	testObj[2] = nullptr;
	testObj[3] = nullptr;
	managerFireworks = nullptr;
	managerTarget = nullptr;

	fpUpdate = nullptr;
	finger = nullptr;
	reConnectWiimote = nullptr;
	reConnectWiiboard = nullptr;
	chooseObject = nullptr;
	pushChooseObjectFlashingCount = 0;
	chooseFlag = false;
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneGame::~SceneGame( void )
{
	// �I������
	Finalize();
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
		1000.0f,
		D3DXVECTOR3( 0.0f, 22.0f, -10.0f ),
		D3DXVECTOR3( 0.0f, 24.0f, 0.0f ),
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


	//	�I�u�W�F�N�g�̐����J�n
	Effect*		pEffect = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;



	// �X�J�C�h�[���̐���
	Effect*	pEffectSky = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "common/sky.jpg" ) );
	pObjectSky_ = new ObjectSky();
	pObjectSky_->Initialize( 0, pArgument->pDevice_, 32, 32, 500.0f, 1.0f, 1.0f );
	pObjectSky_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSky, pTexture );



	//	���̃t�B�[���h
	pTexture = pArgument_->pTexture_->Get( _T( "common/field.jpg" ) );
	pEffect = pArgument_->pEffect_->Get( _T( "Mesh.fx" ) );
	field = new ObjectMesh();
	field->Initialize( 0, pArgument->pDevice_, 10, 20, 40.0f, 40.0f, 1.0f, 1.0f );
	field->CreateGraphic( 0, pArgument->pEffectParameter_, pEffect, pTexture );



	//	�|�C���g�X�v���C�g�Ǘ��I�u�W�F�N�g����
	Effect*		pEffectPoint = nullptr;			// �|�C���g�G�t�F�N�g
	Texture*	pTexturePoint = nullptr;		// �|�C���g�e�N�X�`��
	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pTexturePoint = pArgument->pTexture_->Get( _T( "common/effect000.jpg" ) );
	managerPoint = new ManagerPoint();
	if( managerPoint == nullptr )
	{
		return 1;
	}
	result = managerPoint->Initialize( 1000, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pTexturePoint->pTexture_ );
	if( result != 0 )
	{
		return result;
	}

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



	//	�e�X�g�p�̘r�I�u�W�F�N�g
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument_->pModel_->Get( _T( "arm_r.x" ) );
	testArm = new ObjectModelMaterial();
	testArm->Initialize(0);
	testArm->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);

	testArm->SetPositionY(20.0f);


	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument_->pModel_->Get( _T( "torii_005.x" ) );
	testObj[0] = new ObjectModelMaterial();
	testObj[0]->Initialize(0);
	testObj[0]->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	testObj[0]->SetEnableGraphic(false);

	testObj[1] = new ObjectModelMaterial();
	testObj[1]->Initialize(0);
	testObj[1]->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);

	testObj[2] = new ObjectModelMaterial();
	testObj[2]->Initialize(0);
	testObj[2]->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);

	testObj[3] = new ObjectModelMaterial();
	testObj[3]->Initialize(0);
	testObj[3]->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);

	testObj[1]->SetPositionX(-50.0f);
	testObj[2]->SetPositionX(50.0f);

	testObj[1]->SetPositionZ(200.0f);
	testObj[2]->SetPositionZ(200.0f);
	testObj[3]->SetPositionZ(200.0f);


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


	//	�f�t�H���g�̑I�������u�ĊJ�v�ɐݒ�
	chooseObject = stringReturn;

	//	wii�����R�����o�^����Ă�ꍇ�͓o�^���Ȃ�
	if(pArgument_->pWiiController_->getIsConnectWiimote() == true)
		chooseObject = nullptr;


	//	�X�V�֐��ݒ�
	fpUpdate = &SceneGame::normalUpdate;

	// �t�F�[�h�C��
	pArgument->pFade_->FadeIn( 20 );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int SceneGame::Finalize( void )
{
	// �X�J�C�h�[���̊J��
	delete pObjectSky_;
	pObjectSky_ = nullptr;

	delete testObj[0];
	delete testObj[1];
	delete testObj[2];
	delete testObj[3];

	// ���t�B�[���h�̊J��
	delete field;
	field = nullptr;

	//	�e�X�g�I�u�W�F�N�g�̉��
	delete testArm;
	testArm = nullptr;

	//	�^�[�Q�b�g�Ǘ��N���X�̉��
	delete managerTarget;
	managerTarget = nullptr;

	//	�ԉΊǗ��N���X�̉��
	delete managerFireworks;
	managerFireworks = nullptr;

	// �|�C���g�X�v���C�g�Ǘ��N���X�̊J��
	delete managerPoint;
	managerPoint = nullptr;

	// �|�[�Y�p�w�i�̊J��
	delete pauseFrame;
	pauseFrame = nullptr;

	//	�X�R�A�I�u�W�F�N�g�̉��
	delete score;
	score = nullptr;

	// �u�X�R�A�v�����I�u�W�F�N�g�̊J��
	delete stringScore;
	stringScore = nullptr;

	// �u�ĊJ�v�����I�u�W�F�N�g�̊J��
	delete stringReturn;
	stringReturn = nullptr;

	// �u���~�v�����I�u�W�F�N�g�̊J��
	delete stringStop;
	stringStop = nullptr;

	// �u���߂���v�����I�u�W�F�N�g�̊J��
	delete stringRetry;
	stringRetry = nullptr;

	// �w�I�u�W�F�N�g�̊J��
	delete finger;
	finger = nullptr;

	//	�uwii�����R���Đڑ��v���v�I�u�W�F�N�g���
	delete reConnectWiimote;
	reConnectWiimote = nullptr;

	//	�uwii�{�[�h�Đڑ��v���v�I�u�W�F�N�g�̉��
	delete reConnectWiiboard;
	reConnectWiiboard = nullptr;

	// ���C�g�̊J��
	delete pLight_;
	pLight_ = nullptr;
	pArgument_->pEffectParameter_->SetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL, nullptr );

	// �J�����̊J��
	delete pCamera_;
	pCamera_ = nullptr;
	pArgument_->pEffectParameter_->SetCamera( GraphicMain::CAMERA_GENERAL, pCamera_ );

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
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

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : SceneGame* pOut						: �R�s�[��A�h���X
//==============================================================================
int SceneGame::Copy( SceneGame* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::Update( void )
{
	// �J�����̍X�V
	pCamera_->Update();

	// �e�X�g
	PrintDebug( _T( "�Q�[���V�[��\n" ) );

	//	�ݒ肳�ꂽ�X�V�֐���
	(this->*fpUpdate)();
}
//==============================================================================
// Brief  : �ʏ�X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::normalUpdate(void)
{
	PrintDebug( _T( "normalUpdate\n" ) );

	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;

	//	�ԉΊǗ��N���X�̍X�V
	managerFireworks->Update();

	//	�^�[�Q�b�g�Ǘ��N���X�̍X�V
	managerTarget->Update();

	// �|�C���g�X�v���C�g�Ǘ��N���X�̍X�V
	managerPoint->Update();

	//	�X�R�A�N���X�̍X�V
	score->Update();



	//	�e�X�g�p��������
	//---------------------------------------------------------------------------------------------------------
	if(pArgument_->pWiiController_->getTrigger(WC_B) == true)
	{
		managerFireworks->Add(
			ManagerFireworks::STATE_NORMAL,
			managerPoint,
			D3DXVECTOR3(0.0f, 0.0f, 200.0f),
			D3DXVECTOR3(0.1f, 0.1f, 0.0f),
			DEG_TO_RAD(5.0f),
			DEG_TO_RAD(1.0f)
			);

		managerTarget->Add(
			D3DXVECTOR3(RANDAM(200), (float)(rand() % 50) + 100.0f, 200.0f)
			);
	}

	if(pArgument_->pWiiController_->getTrigger(WC_A) == true)
	{
		//	�^�[�Q�b�g�Ɖԉ΂̓����蔻��
		collision_fireworks_target();
	}

	//testObj[1]->AddRotationX(0.1f);
	//testObj[2]->AddRotationY(0.1f);
	//testObj[3]->AddRotationZ(0.1f);

	if(pArgument_->pVirtualController_->IsPress(VC_UP) && pArgument_->pKeyboard_->IsPress(DIK_Z))
	{
		testArm->AddPositionZ(1.0f);
	}
	if(pArgument_->pVirtualController_->IsPress(VC_DOWN) && pArgument_->pKeyboard_->IsPress(DIK_Z))
	{
		testArm->AddPositionZ(-1.0f);
	}

	if(pArgument_->pVirtualController_->IsPress(VC_UP) && pArgument_->pKeyboard_->IsPress(DIK_Y))
	{
		testArm->AddPositionY(1.0f);
	}
	if(pArgument_->pVirtualController_->IsPress(VC_DOWN) && pArgument_->pKeyboard_->IsPress(DIK_Y))
	{
		testArm->AddPositionY(-1.0f);
	}

	if(pArgument_->pVirtualController_->IsPress(VC_UP) && pArgument_->pKeyboard_->IsPress(DIK_X))
	{
		testArm->AddPositionX(1.0f);
	}
	if(pArgument_->pVirtualController_->IsPress(VC_DOWN) && pArgument_->pKeyboard_->IsPress(DIK_X))
	{
		testArm->AddPositionX(-1.0f);
	}

	if(pArgument_->pWiiController_->getPress(WC_A) && pArgument_->pWiiController_->getPress(WC_B))
		pArgument_->pWiiController_->rotReset();

	D3DXVECTOR3 buffRot = pArgument_->pWiiController_->getRot();
	testArm->SetRotation(DEG_TO_RAD(buffRot.x), DEG_TO_RAD(-buffRot.y), DEG_TO_RAD(buffRot.z));

	//---------------------------------------------------------------------------------------------------------
	//	�e�X�g�p�����܂�

	//	�|�[�Y�L�[�������ꂽ��
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE))
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::pauseUpdate;

		//	Object�̍X�V���~�߂�
		updateFlag = false;

		//	�`��ĊJ
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);

		if(finger != nullptr)
			finger->SetEnableGraphic(true);
	}
}
//==============================================================================
// Brief  : �|�[�Y�X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::pauseUpdate(void)
{
	PrintDebug( _T( "pauseUpdate\n" ) );

	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;

	//	wii�����R������������Ă���Ύw�̈ړ�
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();
		finger->SetPosition(IRBuff.x, IRBuff.y, 0.0f);
	}

	//	�P�t���[���O�̓o�^�I�u�W�F�N�g��ۑ�
	chooseObjectPrev = chooseObject;


	//	����L�[�����ꂽ��
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	�I������Ă���ꍇ
		if(chooseObject != nullptr)
		{
			//	�_�ŃJ�E���g������
			pushChooseObjectFlashingCount = 0;

			//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
			chooseObject->SetColorA(1.0f);

			//	�ĊJ�������ꂽ��
			if(chooseObject == stringReturn)
			{
				//	�X�V�֐��ݒ�
				fpUpdate = &SceneGame::normalUpdate;

				//	Object�̍X�V���ĊJ
				updateFlag = true;

				//	�`���~
				pauseFrame->SetEnableGraphic(false);
				stringReturn->SetEnableGraphic(false);
				stringStop->SetEnableGraphic(false);
				stringRetry->SetEnableGraphic(false);

				if(finger != nullptr)
					finger->SetEnableGraphic(false);
			}
			else
			{
				//	�X�V�֐��ݒ�
				fpUpdate = &SceneGame::pauseFadeUpdate;

				if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
				{
					pArgument_->pFade_->FadeOut( 20 );
				}
			}
		}
	}


	//	���L�[�ňړ�
	if(pArgument_->pVirtualController_->IsTrigger(VC_UP))
	{
		//	�_�ŃJ�E���g������
		pushChooseObjectFlashingCount = 0;

		//	wii�����R���ڑ����͈Ⴄ����
		if(chooseObject == nullptr)
		{
			//	�����L�[�ɕύX
			chooseFlag = false;

			//	�I�u�W�F�N�g�o�^
			chooseObject = stringReturn;
		}
		else
		{
			//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
			chooseObject->SetColorA(1.0f);

			//	�I�����ړ�
			if(chooseObject == stringReturn)
				chooseObject = stringRetry;
			else if(chooseObject == stringRetry)
				chooseObject = stringStop;
			else
				chooseObject = stringReturn;
		}
	}
	if(pArgument_->pVirtualController_->IsTrigger(VC_DOWN))
	{
		//	�_�ŃJ�E���g������
		pushChooseObjectFlashingCount = 0;

		//	wii�����R���ڑ����͈Ⴄ����
		if(chooseObject == nullptr)
		{
			//	�����L�[�ɕύX
			chooseFlag = false;

			//	�I�u�W�F�N�g�o�^
			chooseObject = stringRetry;
		}
		else
		{
			//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
			chooseObject->SetColorA(1.0f);

			//	�I�����ړ�
			if(chooseObject == stringReturn)
				chooseObject = stringStop;
			else if(chooseObject == stringStop)
				chooseObject = stringRetry;
			else
				chooseObject = stringReturn;
		}
	}


	//	wii�����R������������Ă���Ύw�̈ړ�
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();

		//	�u�ĊJ�v�ɓ������Ă��
		if((IRBuff.x <= (stringReturn->GetPositionX() + (stringReturn->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringReturn->GetPositionX() - (stringReturn->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringReturn->GetPositionY() + (stringReturn->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringReturn->GetPositionY() - (stringReturn->GetScaleY() * 0.5f))) )
		{
			//	�_�ŃI�u�W�F�N�g�Ƃ��ēo�^
			chooseObject = stringReturn;

			//	�I����@��IR�ɕύX
			chooseFlag = true;
		}
		//	�u���~�v�ɓ������Ă��
		else if((IRBuff.x <= (stringStop->GetPositionX() + (stringStop->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringStop->GetPositionX() - (stringStop->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringStop->GetPositionY() + (stringStop->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringStop->GetPositionY() - (stringStop->GetScaleY() * 0.5f))) )
		{
			//	�_�ŃI�u�W�F�N�g�Ƃ��ēo�^
			chooseObject = stringStop;

			//	�I����@��IR�ɕύX
			chooseFlag = true;
		}
		//	�u���߂���v�ɓ������Ă��
		else if((IRBuff.x <= (stringRetry->GetPositionX() + (stringRetry->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringRetry->GetPositionX() - (stringRetry->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringRetry->GetPositionY() + (stringRetry->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringRetry->GetPositionY() - (stringRetry->GetScaleY() * 0.5f))) )
		{
			//	�_�ŃI�u�W�F�N�g�Ƃ��ēo�^
			chooseObject = stringRetry;

			//	�I����@��IR�ɕύX
			chooseFlag = true;
		}
		//	���ɂ��������ĂȂ����
		else
		{
			//	�I����@��IR�̏ꍇ�̂�
			if(chooseFlag == true)
			{
				if(chooseObject != nullptr)
				{
					//	�o�^����
					chooseObject->SetColorA(1.0f);
					chooseObject = nullptr;
					pushChooseObjectFlashingCount = 0;
				}
			}
		}
	}


	//	PAUSE�L�[�������ꂽ��
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE))
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::normalUpdate;

		//	Object�̍X�V���ĊJ
		updateFlag = true;

		//	�`���~
		pauseFrame->SetEnableGraphic(false);
		stringReturn->SetEnableGraphic(false);
		stringStop->SetEnableGraphic(false);
		stringRetry->SetEnableGraphic(false);

		if(finger != nullptr)
			finger->SetEnableGraphic(false);
	}


	//	�I�����ڂ̓_�ŏ���
	if(chooseObject != nullptr)
	{
		chooseObject->SetScaleX(stringXX_NormalSizeX * 1.3f);
		chooseObject->SetScaleY(stringXX_NormalSizeY * 1.3f);

		pushChooseObjectFlashingCount++;

		if(pushChooseObjectFlashingCount <= flashingCountHirf)
			chooseObject->AddColorA(-addFlashingAlpha);
		else if(pushChooseObjectFlashingCount <= flashingCountMax)
			chooseObject->AddColorA(addFlashingAlpha);
		else
			pushChooseObjectFlashingCount = 0;

		//	�P�t���[���O�̑I���I�u�W�F�N�g�̃T�C�Y��ύX
		if((chooseObjectPrev != nullptr) &&
			(chooseObjectPrev != chooseObject))
		{
			chooseObjectPrev->SetScaleX(stringXX_NormalSizeX);
			chooseObjectPrev->SetScaleY(stringXX_NormalSizeY);
		}
	}
	else
	{
		stringReturn->SetScaleX(stringXX_NormalSizeX);
		stringReturn->SetScaleY(stringXX_NormalSizeY);

		stringStop->SetScaleX(stringXX_NormalSizeX);
		stringStop->SetScaleY(stringXX_NormalSizeY);

		stringRetry->SetScaleX(stringXX_NormalSizeX);
		stringRetry->SetScaleY(stringXX_NormalSizeY);
	}



	//	Object�N���X�̍X�V���~�܂��Ă邩��A�����ōX�V����
	if(finger != nullptr)
		finger->Update();

	stringRetry->Update();
	stringReturn->Update();
	stringStop->Update();
}
//==============================================================================
// Brief  : �|�[�Y�X�V����(�t�F�[�h�p)
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::pauseFadeUpdate(void)
{
	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;

	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		if(chooseObject == stringStop)
			SetSceneNext( ManagerSceneMain::TYPE_TITLE );
		else
			SetSceneNext( ManagerSceneMain::TYPE_GAME );

		SetIsEnd( true );
	}
}
//==============================================================================
// Brief  : �Đڑ��v�����p�̍X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::reConnectWiimoteUpdate(void)
{
	//	�Đڑ��v��
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		pArgument_->pWiiController_->reConnectWiimote();

	//	wii�����R�����Đڑ����I��������
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == false)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::pauseUpdate;

		//	Object�̍X�V���~�߂�
		updateFlag = false;

		//	�`���߂�
		reConnectWiimote->SetEnableGraphic(false);

		//	�`��ĊJ
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);
		finger->SetEnableGraphic(true);
	}

	//	Object�N���X�̍X�V���~�܂��Ă邩��A�����ōX�V����
	reConnectWiimote->Update();
}
//==============================================================================
// Brief  : �Đڑ��v�����p�̍X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::reConnectWiiboardUpdate(void)
{
	//	�Đڑ��v��
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		pArgument_->pWiiController_->reConnectWiiboard();

	//	wii�����R�����Đڑ����I��������
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == false)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::pauseUpdate;

		//	Object�̍X�V���~�߂�
		updateFlag = false;

		//	�`���߂�
		reConnectWiiboard->SetEnableGraphic(false);

		//	�`��ĊJ
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);
		finger->SetEnableGraphic(true);
	}

	//	Object�N���X�̍X�V���~�܂��Ă邩��A�����ōX�V����
	reConnectWiiboard->Update();
}
//==============================================================================
// Brief  : wii�����R���̃��X�g�`�F�b�N����
// Return : bool								: true = ��薳�� false = ���X�g
// Arg    : void								: �Ȃ�
//==============================================================================
bool SceneGame::wiiLostCheck(void)
{
	//	wii�����R�����Đڑ��v���������ꍇ
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == true)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::reConnectWiimoteUpdate;

		//	�Đڑ��v���I�u�W�F�N�g����
		reConnectWiimote->SetEnableGraphic(true);

		//	Object�̍X�V���~�߂�
		updateFlag = false;

		return false;
	}

	//	wii�{�[�h���Đڑ��v���������ꍇ
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == true)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::reConnectWiiboardUpdate;

		//	�Đڑ��v���I�u�W�F�N�g����
		reConnectWiiboard->SetEnableGraphic(true);

		//	Object�̍X�V���~�߂�
		updateFlag = false;

		return false;
	}

	return true;
}
//==============================================================================
// Brief  : �ԉ΂ƃ^�[�Q�b�g�̓����蔻�菈��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::collision_fireworks_target()
{
	Fireworks* buffF;
	Target* buffT;

	//	��������
	managerFireworks->Burn();
}
