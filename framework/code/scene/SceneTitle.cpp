//==============================================================================
//
// File   : SceneTitle.cpp
// Brief  : �^�C�g���V�[���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "SceneTitle.h"
#include "../framework/camera/CameraObject.h"
#include "../framework/camera/ManagerCamera.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/VirtualController.h"
#include "../framework/light/LightDirection.h"
#include "../framework/light/ManagerLight.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/ManagerMotion.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/ManagerUpdate.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectModelMaterial.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectSky.h"
#include "../object/ObjectSkinMesh.h"
#include "../framework/polygon/PolygonMesh.h"
#include "../system/point/ManagerPoint.h"
#include "../system/ManagerFireworks.h"
#include "../system/fire/Fire.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//******************************************************************************
// �ÓI�ϐ�
//******************************************************************************
//	�_�ŗp�J�E���g��
static const int flashingCountHirf = 20;
static const int flashingCountMax = 40;

//	�����J�n�@�����̃T�C�Y
static const float startXX_NormalSizeX = 400.0f;
static const float startXX_NormalSizeY = 120.0f;

//	�����l���Z�l
static const float addFlashingAlpha = 0.02f;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneTitle::SceneTitle( void ) : SceneMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pCamera_ = nullptr;
	pLight_ = nullptr;

	//	�^�C�g��UI�֌W
	//----------------------------------------------------------
	titleLogo = nullptr;
	pushAKey = nullptr;
	startGame = nullptr;
	startTutorial = nullptr;
	finger = nullptr;
	reConnectWiimote = nullptr;
	reConnectWiiboard = nullptr;

	chooseObject = nullptr;
	chooseObjectPrev = nullptr;

	pushAKeyFlashingCount = 0;
	pushChooseObjectFlashingCount = 0;

	chooseFlag = false;
	//----------------------------------------------------------



	//	�^�C�g���p�X�e�[�W�E�RD�I�u�W�F�N�g�֌W
	//----------------------------------------------------------
	pObjectSky_ = nullptr;
	field = nullptr;
	bridge = nullptr;
	managerPoint = nullptr;
	managerFireworks = nullptr;
	pObjectSkinMesh_[0] = nullptr;
	pObjectSkinMesh_[1] = nullptr;
	pObjectSkinMesh_[2] = nullptr;

	launchFlag = false;
	launchCount = 0;

	for(int count = 0;count < FIREWORKS_MAX;count++)
		fireworksTable[count] = -1;

	fireworksTableIndex = 0;
	//----------------------------------------------------------




	fpUpdate = nullptr;
	fpUpdatePrev = nullptr;
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneTitle::~SceneTitle( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
int SceneTitle::Initialize( SceneArgumentMain* pArgument )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Initialize( pArgument );
	if( result != 0 )
	{
		return result;
	}

	// �J�����̐���
	pCamera_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pCamera_->Set(
		D3DX_PI / 4.0f,
		1280,
		720,
		0.1f,
		10000.0f,
		D3DXVECTOR3( 0.0f, 120.0f, -2400.0f ),
		D3DXVECTOR3( 0.0f, 720.0f, 0.0f ),
		D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );

	// ���C�g�̐���
	pLight_ = pArgument->pLight_->GetLightDirection();
	if( pLight_ == nullptr )
	{
		return 1;
	}
	pLight_->Set( D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR3( 0.0f, -0.7f, 0.7f ) );

	//	�I�u�W�F�N�g�̐����J�n
	Effect*		pEffect = nullptr;
	Effect*		pEffectReflect = nullptr;
	Effect*		pEffectShadow = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;


	// �X�J�C�h�[���̐���
	Effect*	pEffectSky = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	Effect*	pEffectSkyReflect = pArgument->pEffect_->Get( _T( "SkyReflect.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "common/sky.jpg" ) );
	pObjectSky_ = new ObjectSky();
	pObjectSky_->Initialize( 0, pArgument->pDevice_, 32, 32, 5000.0f, 1.0f, 1.0f );
	pObjectSky_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSky, pEffectSkyReflect, pTexture );



	//	���̃t�B�[���h
	pModel = pArgument_->pModel_->Get( _T( "testfield_01_low.x" ) );
	pEffect = pArgument_->pEffect_->Get( _T( "Model.fx" ) );
	pEffectReflect = pArgument_->pEffect_->Get( _T( "ModelReflect.fx" ) );
	pEffectShadow = pArgument_->pEffect_->Get( _T( "ModelShadow.fx" ) );
	field = new ObjectModel();
	field->Initialize(0);
	field->CreateGraphic( 0, pModel,pArgument->pEffectParameter_, pEffect, pEffectReflect, pEffectShadow );
	field->SetScale(5.0f, 5.0f, 5.0f);
	field->AddPositionY(-300.0f);



	//	������
	pEffect = pArgument->pEffect_->Get( _T( "ModelMaterial.fx" ) );
	pEffectReflect = pArgument->pEffect_->Get( _T( "ModelMaterialReflect.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "bridge.x" ) );
	bridge = new ObjectModelMaterial();
	bridge->Initialize(0);
	bridge->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect);
	bridge->SetPosition(0.0f, 1000.0f, 2300.0f);
	bridge->SetScale(350.0f, 350.0f, 350.0f);
	bridge->SetRotationY(DEG_TO_RAD(90));








	//	�|�C���g�X�v���C�g�Ǘ��I�u�W�F�N�g����
	Effect*		pEffectPoint = nullptr;				// �|�C���g�G�t�F�N�g
	Effect*		pEffectPointReflect = nullptr;		// �|�C���g�G�t�F�N�g
	Texture*	pTexturePoint = nullptr;			// �|�C���g�e�N�X�`��
	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pEffectPointReflect = pArgument->pEffect_->Get( _T( "PointReflect.fx" ) );
	pTexturePoint = pArgument->pTexture_->Get( _T( "common/effect000.jpg" ) );
	managerPoint = new ManagerPoint();
	if( managerPoint == nullptr )
	{
		//return 1;
	}
	result = managerPoint->Initialize( 10000, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pEffectPointReflect, pTexturePoint->pTexture_ );
	if( result != 0 )
	{
		//return result;
	}

	//	�ΉԃI�u�W�F�N�g�̃X�e�[�g������
	Fire::InitializeState();

	//	�ԉΊǗ��I�u�W�F�N�g����
	managerFireworks = new ManagerFireworks;
	managerFireworks->Initialize(managerPoint);




	// �X�L�����b�V���̐���
	Effect*	pEffectSkinMesh = nullptr;				// �G�t�F�N�g
	Effect*	pEffectSkinMeshReflect = nullptr;		// �G�t�F�N�g
	Model*	pModelSkinMesh = nullptr;				// ���f��
	pEffectSkinMesh = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pEffectSkinMeshReflect = pArgument->pEffect_->Get( _T( "SkinMeshReflect.fx" ) );
	pModelSkinMesh = pArgument_->pModel_->Get( _T( "test.model" ) );
	pObjectSkinMesh_[0] = new ObjectSkinMesh();
	pObjectSkinMesh_[0]->Initialize( 0, 1 );
	pObjectSkinMesh_[0]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh, pEffectSkinMeshReflect );
	pObjectSkinMesh_[0]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[0]->SetPosition( 300.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[1] = new ObjectSkinMesh();
	pObjectSkinMesh_[1]->Initialize( 0, 1 );
	pObjectSkinMesh_[1]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh, pEffectSkinMeshReflect );
	pObjectSkinMesh_[1]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[1]->SetPosition( 0.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[2] = new ObjectSkinMesh();
	pObjectSkinMesh_[2]->Initialize( 0, 1 );
	pObjectSkinMesh_[2]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh, pEffectSkinMeshReflect );
	pObjectSkinMesh_[2]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[2]->SetPosition( -300.0f, 100.0f, 0.0f );




	//	�^�C�g�����S
	titleLogo = new Object2D;
	titleLogo->Initialize(0);
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "title/titlelogo.png" ) );

	titleLogo->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	titleLogo->SetPosition(350.0f, 100.0f, 0.0f);


	//	A�{�^���������Ă�
	pTexture = pArgument_->pTexture_->Get( _T( "title/pressAKey.png" ) );
	pushAKey = new Object2D;
	pushAKey->Initialize(0);

	pushAKey->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	pushAKey->SetPosition(0.0f, -200.0f, 0.0f);


	//	�u�����J�n�v�����I�u�W�F�N�g�̐���
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "title/startGame.png" ) );

	startGame = new Object2D;
	startGame->Initialize(0);

	startGame->CreateGraphic(
	0,
	pArgument_->pEffectParameter_,
	pEffect,
	pTexture);

	startGame->SetPosition(-300.0f, -100.0f, 0.0f);
	startGame->SetScaleX(startXX_NormalSizeX);
	startGame->SetScaleY(startXX_NormalSizeY);
	startGame->SetEnableGraphic(false);


	//	�u���K�J�n�v�����I�u�W�F�N�g�̐���
	pTexture = pArgument_->pTexture_->Get( _T( "title/startTutorial.png" ) );

	startTutorial = new Object2D;
	startTutorial->Initialize(0);

	startTutorial->CreateGraphic(
	0,
	pArgument_->pEffectParameter_,
	pEffect,
	pTexture);

	startTutorial->SetPosition(300.0f, -100.0f, 0.0f);
	startTutorial->SetScaleX(startXX_NormalSizeX);
	startTutorial->SetScaleY(startXX_NormalSizeY);
	startTutorial->SetEnableGraphic(false);



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




	//	�X�V�֐��Z�b�g
	fpUpdate = &SceneTitle::firstUpdate;

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
int SceneTitle::Finalize( void )
{
	delete reConnectWiiboard;
	reConnectWiiboard = nullptr;

	delete reConnectWiimote;
	reConnectWiimote = nullptr;

	delete finger;
	finger = nullptr;

	delete startTutorial;
	startTutorial = nullptr;

	delete startGame;
	startGame = nullptr;

	delete pushAKey;
	pushAKey = nullptr;

	delete titleLogo;
	titleLogo = nullptr;

	delete pObjectSkinMesh_[2];
	pObjectSkinMesh_[2] = nullptr;

	delete pObjectSkinMesh_[1];
	pObjectSkinMesh_[1] = nullptr;

	delete pObjectSkinMesh_[0];
	pObjectSkinMesh_[0] = nullptr;

	delete managerFireworks;
	managerFireworks = nullptr;

	Fire::FinalizeState();

	delete managerPoint;
	managerPoint = nullptr;

	delete bridge;
	bridge = nullptr;

	delete field;
	field = nullptr;

	delete pObjectSky_;
	pObjectSky_ = nullptr;

	// ���C�g�̊J��
	if( pLight_ != nullptr )
	{
		pLight_->Release();
		pLight_ = nullptr;
	}

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
int SceneTitle::Reinitialize( SceneArgumentMain* pArgument )
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
// Arg    : SceneTitle* pOut					: �R�s�[��A�h���X
//==============================================================================
int SceneTitle::Copy( SceneTitle* pOut ) const
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
void SceneTitle::Update( void )
{
	// �e�X�g
	PrintDebug( _T( "kawashima\n" ) );

	//	�ݒ肳�ꂽ�X�V�N���X��
	(this->*fpUpdate)();
}

//==============================================================================
// Brief  : �X�V����1(�uA�{�^���������Ăˁv�̓_��)
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::firstUpdate( void )
{
	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;



	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}


	//	�uA�{�^���������Ăˁv�̓_�ŏ���
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount <= flashingCountHirf)
			pushAKey->AddColorA(-addFlashingAlpha);
		else if(pushAKeyFlashingCount <= flashingCountMax)
			pushAKey->AddColorA(addFlashingAlpha);
		else
			pushAKeyFlashingCount = 0;
	}


	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	�uA�{�^���������Ăˁv�������āA�u�����J�n�v�Ɓu���K�J�n�v�Ǝw�I�u�W�F�N�g������
		pushAKey->SetEnableGraphic(false);
		startTutorial->SetEnableGraphic(true);
		startGame->SetEnableGraphic(true);

		//	wii�����R�����o�^����Ă�ꍇ�͓o�^���Ȃ�
		if(pArgument_->pWiiController_->getIsConnectWiimote() == true)
		{
			chooseObject = nullptr;
			finger->SetEnableGraphic(true);
		}

		//	�f�t�H���g�̑I�������u�����J�n�v�ɐݒ�
		chooseObject = startGame;

		//	�_�ŃJ�E���g������
		pushAKeyFlashingCount = 0;

		//	���̍X�V�֐���
		fpUpdate = &SceneTitle::secondUpdate;
	}
}
//==============================================================================
// Brief  : �X�V����2(�Q�[���J�n�E�`���[�g���A���J�n�̑I������)
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::secondUpdate( void )
{
	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;

	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}

	//	�P�t���[���O�̓o�^�I�u�W�F�N�g��ۑ�
	chooseObjectPrev = chooseObject;


	//	wii�����R������������Ă���Ύw�̈ړ�
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();

		finger->SetPosition(IRBuff.x, IRBuff.y, 0.0f);
	}


	//	����L�[�����ꂽ��
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	�I������Ă���ꍇ
		if(chooseObject != nullptr)
		{
			//	�_�ŃJ�E���g������
			pushAKeyFlashingCount = 0;

			//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
			chooseObject->SetColorA(1.0f);

			//	���̍X�V�֐���
			fpUpdate = &SceneTitle::fadeUpdate;

			if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
			{
				pArgument_->pFade_->FadeOut( 20 );
			}
		}
	}

	//	���L�[�ňړ�
	if(pArgument_->pVirtualController_->IsTrigger(VC_LEFT))
	{
		//	�_�ŃJ�E���g������
		pushAKeyFlashingCount = 0;

		//	wii�����R���ڑ����͈Ⴄ����
		if(chooseObject == nullptr)
		{
			//	�����L�[�ɕύX
			chooseFlag = false;

			//	�I�u�W�F�N�g�o�^
			chooseObject = startGame;
		}
		else
		{
			//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
			chooseObject->SetColorA(1.0f);

			//	�I�����ړ�
			(chooseObject == startGame) ? chooseObject = startTutorial : chooseObject = startGame;
		}
	}
	if(pArgument_->pVirtualController_->IsTrigger(VC_RIGHT))
	{
		//	�_�ŃJ�E���g������
		pushAKeyFlashingCount = 0;

		//	wii�����R���ڑ����͈Ⴄ����
		if(chooseObject == nullptr)
		{
			//	�����L�[�ɕύX
			chooseFlag = false;

			//	�I�u�W�F�N�g�o�^
			chooseObject = startTutorial;
		}
		else
		{
			//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
			chooseObject->SetColorA(1.0f);

			//	�I�����ړ�
			(chooseObject == startGame) ? chooseObject = startTutorial : chooseObject = startGame;
		}
	}


	//	wii�����R������������Ă���Ύw�̈ړ�
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();

		//	�u�����J�n�v�ɓ������Ă��
		if((IRBuff.x <= (startGame->GetPositionX() + (startGame->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (startGame->GetPositionX() - (startGame->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (startGame->GetPositionY() + (startGame->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (startGame->GetPositionY() - (startGame->GetScaleY() * 0.5f))) )
		{
			//	�_�ŃI�u�W�F�N�g�Ƃ��ēo�^
			chooseObject = startGame;

			//	�I����@��IR�ɕύX
			chooseFlag = true;
		}
		//	�u���K�J�n�v�ɓ������Ă��
		else if((IRBuff.x <= (startTutorial->GetPositionX() + (startTutorial->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (startTutorial->GetPositionX() - (startTutorial->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (startTutorial->GetPositionY() + (startTutorial->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (startTutorial->GetPositionY() - (startTutorial->GetScaleY() * 0.5f))) )
		{
			//	�_�ŃI�u�W�F�N�g�Ƃ��ēo�^
			chooseObject = startTutorial;

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
					pushAKeyFlashingCount = 0;
				}
			}
		}
	}


	//	�I�����ڂ̓_�ŏ���
	if(chooseObject != nullptr)
	{
		chooseObject->SetScaleX(startXX_NormalSizeX * 1.3f);
		chooseObject->SetScaleY(startXX_NormalSizeY * 1.3f);

		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount <= flashingCountHirf)
			chooseObject->AddColorA(-addFlashingAlpha);
		else if(pushAKeyFlashingCount <= flashingCountMax)
			chooseObject->AddColorA(addFlashingAlpha);
		else
			pushAKeyFlashingCount = 0;


		//	�P�t���[���O�̑I���I�u�W�F�N�g�̃T�C�Y��ύX
		if((chooseObjectPrev != nullptr) &&
			(chooseObjectPrev != chooseObject))
		{
			chooseObjectPrev->SetScaleX(startXX_NormalSizeX);
			chooseObjectPrev->SetScaleY(startXX_NormalSizeY);
		}
	}
	else
	{
		startGame->SetScaleX(startXX_NormalSizeX);
		startGame->SetScaleY(startXX_NormalSizeY);

		startTutorial->SetScaleX(startXX_NormalSizeX);
		startTutorial->SetScaleY(startXX_NormalSizeY);
	}
}
//==============================================================================
// Brief  : �X�V����(����L�[�����ꂽ��̑J�ڏ���)
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::fadeUpdate( void )
{
	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;

	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		if(chooseObject == startGame)
			SetSceneNext( ManagerSceneMain::TYPE_GAME );
		else
			SetSceneNext( ManagerSceneMain::TYPE_GAME );//�ق�Ƃ̓`���[�g���A��

		SetIsEnd( true );
	}
}
//==============================================================================
// Brief  : �Đڑ��v�����p�̍X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::reConnectWiimoteUpdate(void)
{
	//	�Đڑ��v��
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		pArgument_->pWiiController_->reConnectWiimote();

	//	wii�����R�����Đڑ����I��������
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == false)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = fpUpdatePrev;
		fpUpdatePrev = nullptr;

		//	Object�̍X�V���~�߂�
		pArgument_->pUpdate_->SetIsEnable( true );

		//	�`���߂�
		reConnectWiimote->SetEnableGraphic(false);

		//	�`��ĊJ
		if(fpUpdate == &SceneTitle::secondUpdate)
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
void SceneTitle::reConnectWiiboardUpdate(void)
{
	//	�Đڑ��v��
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		pArgument_->pWiiController_->reConnectWiiboard();

	//	wii�����R�����Đڑ����I��������
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == false)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = fpUpdatePrev;
		fpUpdatePrev = nullptr;

		//	Object�̍X�V���~�߂�
		pArgument_->pUpdate_->SetIsEnable( true );

		//	�`���߂�
		reConnectWiiboard->SetEnableGraphic(false);

		//	�`��ĊJ
		if(fpUpdate == &SceneTitle::secondUpdate)
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
bool SceneTitle::wiiLostCheck(void)
{
	//	wii�����R�����Đڑ��v���������ꍇ
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == true)
	{
		//	�X�V�֐��ݒ�
		fpUpdatePrev = fpUpdate;
		fpUpdate = &SceneTitle::reConnectWiimoteUpdate;

		//	�Đڑ��v���I�u�W�F�N�g����
		reConnectWiimote->SetEnableGraphic(true);

		//	Object�̍X�V���~�߂�
		pArgument_->pUpdate_->SetIsEnable( false );

		return false;
	}

	//	wii�{�[�h���Đڑ��v���������ꍇ
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == true)
	{
		//	�X�V�֐��ݒ�
		fpUpdatePrev = fpUpdate;
		fpUpdate = &SceneTitle::reConnectWiiboardUpdate;

		//	�Đڑ��v���I�u�W�F�N�g����
		reConnectWiiboard->SetEnableGraphic(true);

		//	Object�̍X�V���~�߂�
		pArgument_->pUpdate_->SetIsEnable( false );

		return false;
	}

	return true;
}
