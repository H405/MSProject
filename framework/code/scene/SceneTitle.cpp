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
#include "../framework/light/LightPoint.h"
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
#include "../framework/system/Window.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"
#include "../object/ObjectRiver.h"

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
#include "../system/ManagerTarget.h"
#include "../system/fire/Fire.h"
#include "../object/ObjectWaterwheel.h"
#include "../system/player/Player.h"
#include "../framework/resource/ManagerSound.h"
#include "../framework/resource/Sound.h"

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
	pCameraShadowNear_ = nullptr;
	pCameraShadowFar_ = nullptr;
	ppCameraShadowPoint_ = nullptr;
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



	//	�Q�[���p�X�e�[�W�E�RD�I�u�W�F�N�g�֌W
	//----------------------------------------------------------
	sky = nullptr;
	river = nullptr;
	field = nullptr;

	bridge = nullptr;
	waterwheel = nullptr;
	houses = nullptr;
	gate = nullptr;

//	markers = nullptr;

	player = nullptr;

	managerPoint = nullptr;
	managerFireworks = nullptr;

//	pObjectSkinMesh_[0] = nullptr;
//	pObjectSkinMesh_[1] = nullptr;
//	pObjectSkinMesh_[2] = nullptr;

	launchFlag = false;
	launchCount = 0;

	for(int count = 0;count < FIREWORKS_MAX;count++)
		fireworksTable[count] = -1;

	fireworksTableIndex = 0;
	//----------------------------------------------------------

	//	���֘A
	//----------------------------------------------------------
	bgmSound = nullptr;
	desideSound = nullptr;
	selectSound = nullptr;
	cancelSound = nullptr;
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
		pArgument->pWindow_->GetWidth(),
		pArgument->pWindow_->GetHeight(),
		0.1f,
		20000.0f,
		D3DXVECTOR3( 0.0f, 120.0f, -2400.0f ),
		D3DXVECTOR3( 0.0f, 720.0f, 0.0f ),
		D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	
	// ���C�g�̐���
	pLight_ = pArgument->pLight_->GetLightDirection();
	if( pLight_ == nullptr )
	{
		return 1;
	}
	pLight_->Set( D3DXCOLOR( 0.25f, 0.3f, 0.4f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ), D3DXVECTOR3( -1.0f, -1.0f, -1.0f ) );

	// �e�p�J�����߂̐ݒ�
	D3DXVECTOR3	vectorLight;		// ���C�g�x�N�g��
	pLight_->GetVector( &vectorLight );
	vectorLight *= -3500.0f;
	pCameraShadowNear_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_SHADOW_NEAR );
	pCameraShadowNear_->Set( D3DX_PI / 4.0f, 8 * pArgument->pWindow_->GetWidth(), 8 * pArgument->pWindow_->GetHeight(), 0.1f, 7000.0f,
		vectorLight, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), false );

	// �e�p�J�������̐ݒ�
	pLight_->GetVector( &vectorLight );
	vectorLight *= -10000.0f;
	pCameraShadowFar_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_SHADOW_FAR );
	pCameraShadowFar_->Set( D3DX_PI / 4.0f, 24 * pArgument->pWindow_->GetWidth(), 24 * pArgument->pWindow_->GetHeight(), 0.1f, 20000.0f,
		vectorLight, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), false );

	// �e�p�J�����_�̐ݒ�
	ppCameraShadowPoint_ = new CameraObject*[ GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW ];
	if( ppCameraShadowPoint_ == nullptr )
	{
		return 1;
	}
	for( int counterLightPoint = 0; counterLightPoint < GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW; ++ counterLightPoint )
	{
		ppCameraShadowPoint_[ counterLightPoint ] = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_SHADOW_POINT_0 + counterLightPoint );
		ppCameraShadowPoint_[ counterLightPoint ]->Set( D3DX_PI / 4.0f, pArgument->pWindow_->GetWidth(), pArgument->pWindow_->GetHeight(), 0.1f, 10000.0f,
			D3DXVECTOR3( 0.0f, 1000.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, 1.0f ), false );
	}

	// �����̐ݒ�
	pArgument->pEffectParameter_->SetColorAmbient( 0.1f, 0.15f, 0.2f );

	//	�I�u�W�F�N�g�̐����J�n
	Effect*		pEffect = nullptr;
	Effect*		pEffectReflect = nullptr;
	Effect*		pEffectShadow = nullptr;
	Effect*		pEffectParaboloid = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;

	// �X�J�C�h�[���̐���
	Texture*	pTextureSky = nullptr;				// �e�N�X�`��
	Effect*		pEffectSkyGeneral = nullptr;		// �ʏ�`��G�t�F�N�g
	Effect*		pEffectSkyReflect = nullptr;		// ���˕`��G�t�F�N�g
	pTextureSky = pArgument_->pTexture_->Get( _T( "test/night.png" ) );
	pEffectSkyGeneral = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	pEffectSkyReflect = pArgument->pEffect_->Get( _T( "SkyReflect.fx" ) );
	sky = new ObjectSky();
	sky->Initialize( 0, pArgument->pDevice_, 32, 32, 11500.0f, 1.0f, 1.0f );
	sky->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSkyGeneral, pEffectSkyReflect, pTextureSky );

	// ��̐���
	Model*	pModelRiver = nullptr;		// ���f��
	Effect*	pEffectRiver = nullptr;		// �G�t�F�N�g
	pModelRiver = pArgument->pModel_->Get( _T( "river_ver103_04.x" ), Vertex::ELEMENT_SET_NORMAL_MAP );
	pEffectRiver = pArgument->pEffect_->Get( "Water.fx" );
	river = new ObjectRiver();
	river->Initialize( 0 );
	river->CreateGraphic( 0, pModelRiver, pArgument->pEffectParameter_, pEffectRiver, pArgument->pTextureNormalWave_,
		pArgument->pTextureReflect_, pArgument->pTextureReflectNotLight_, pArgument->pTextureReflectAdd_, pArgument->pTexture3D_, pArgument->pTextureDepth_ );
	river->SetPositionY( -100.0f );
	pArgument->pEffectParameter_->SetHeightReflect( -100.0f );
	//pRiver_->SetIsEnable(false);

	// �n�`�̐���
	Model*	pModelField = nullptr;					// ���f��
	Effect*	pEffectFieldGeneral = nullptr;			// �ʏ�`��G�t�F�N�g
	Effect*	pEffectFieldReflect = nullptr;			// ���˃G�t�F�N�g
	Effect*	pEffectFieldShadow = nullptr;			// �e�G�t�F�N�g
	Effect*	pEffectFieldParaboloid = nullptr;		// �����ϊ��G�t�F�N�g
	pModelField = pArgument->pModel_->Get( _T( "Stagever.1.03.x" ) );
	pEffectFieldGeneral = pArgument->pEffect_->Get( "Model.fx" );
	pEffectFieldReflect = pArgument->pEffect_->Get( "ModelReflect.fx" );
	pEffectFieldShadow = pArgument->pEffect_->Get( "ModelShadow.fx" );
	pEffectFieldParaboloid = pArgument->pEffect_->Get( "ModelParaboloid.fx" );
	field = new ObjectModel();
	field->Initialize( 0 );
	field->CreateGraphic( 0, pModelField, pArgument->pEffectParameter_, pEffectFieldGeneral, pEffectFieldReflect, pEffectFieldShadow, pEffectFieldParaboloid );
	field->SetPositionY( -400.0f );
	field->SetScale( 2.0f, 2.0f, 2.0f );

	// ���̐���
	Model*	pModelBridge = nullptr;					// ���f��
	Effect*	pEffectBridgeGeneral = nullptr;			// �ʏ�`��G�t�F�N�g
	Effect*	pEffectBridgeReflect = nullptr;			// ���˃G�t�F�N�g
	Effect*	pEffectBridgeShadow = nullptr;			// �e�G�t�F�N�g
	Effect*	pEffectBridgeParaboloid = nullptr;		// �����ϊ��G�t�F�N�g
	pModelBridge = pArgument->pModel_->Get( _T( "bridge_002.x" ) );
	pEffectBridgeGeneral = pArgument->pEffect_->Get( "ModelMaterial.fx" );
	pEffectBridgeReflect = pArgument->pEffect_->Get( "ModelMaterialReflect.fx" );
	pEffectBridgeShadow = pArgument->pEffect_->Get( "ModelShadow.fx" );
	pEffectBridgeParaboloid = pArgument->pEffect_->Get( "ModelParaboloid.fx" );
	bridge = new ObjectModelMaterial();
	bridge->Initialize( 0 );
	bridge->CreateGraphic( 0, pModelBridge, pArgument->pEffectParameter_, pEffectBridgeGeneral, pEffectBridgeReflect, pEffectBridgeShadow, pEffectBridgeParaboloid );
	bridge->SetPosition( 1558.0f, 460.0f, -2240.0f );
	bridge->SetRotationY( DEG_TO_RAD( 101.0f ) );
	bridge->SetScale( 285.0f, 285.0f, 285.0f );

	// ���Ԃ̐���
	waterwheel = new ObjectWaterwheel();
	waterwheel->Initialize( D3DXVECTOR3( 110.0f, 230.0f, 3780.0f ), DEG_TO_RAD( 74 ), -0.001f, pArgument );

	// �Ƃ̐���
	Model*	pModelHouse = nullptr;					// ���f��
	Effect*	pEffectHouseGeneral = nullptr;			// �ʏ�`��G�t�F�N�g
	Effect*	pEffectHouseReflect = nullptr;			// ���˃G�t�F�N�g
	Effect*	pEffectHouseShadow = nullptr;			// �e�G�t�F�N�g
	Effect*	pEffectHouseParaboloid = nullptr;		// �����ϊ��G�t�F�N�g
	pModelHouse = pArgument->pModel_->Get( _T( "house_002.x" ) );
	pEffectHouseGeneral = pArgument->pEffect_->Get( "ModelMaterial.fx" );
	pEffectHouseReflect = pArgument->pEffect_->Get( "ModelMaterialReflect.fx" );
	pEffectHouseShadow = pArgument->pEffect_->Get( "ModelShadow.fx" );
	pEffectHouseParaboloid = pArgument->pEffect_->Get( "ModelParaboloid.fx" );
	houses = new ObjectModelMaterial[ COUNT_HOUSE ];
	for( int counterHouse = 0; counterHouse < COUNT_HOUSE; ++counterHouse )
	{
		houses[ counterHouse ].Initialize( 0 );
		houses[ counterHouse ].CreateGraphic( 0, pModelHouse, pArgument->pEffectParameter_, pEffectHouseGeneral, pEffectHouseReflect, pEffectHouseShadow, pEffectHouseParaboloid );
		houses[ counterHouse ].SetScale( 300.0f, 300.0f, 300.0f );
	}
	houses[ 0 ].SetPosition( 640.0f, 0.0f, 3690.0f );
	houses[ 0 ].SetRotationY( DEG_TO_RAD( 254.0f ) );
	houses[ 0 ].SetScale( 150.0f, 150.0f, 150.0f );
	houses[ 1 ].SetPosition( -3700.0f, 0.0f, 2480.0f );
	houses[ 1 ].SetRotationY( DEG_TO_RAD( 252.0f ) );
	houses[ 2 ].SetPosition( -3120.0f, 0.0f, 1010.0f );
	houses[ 2 ].SetRotationY( DEG_TO_RAD( 243.0f ) );
	houses[ 3 ].SetPosition( -2030.0f, 0.0f, -750.0f );
	houses[ 3 ].SetRotationY( DEG_TO_RAD( 222.0f ) );
	houses[ 4 ].SetPosition( -1880.0f, 0.0f, 3160.0f );
	houses[ 4 ].SetRotationY( DEG_TO_RAD( 51.0f ) );
	houses[ 5 ].SetPosition( 3500.0f, 0.0f, 5500.0f );
	houses[ 5 ].SetRotationY( DEG_TO_RAD( 58.0f ) );
	houses[ 6 ].SetPosition( 4260.0f, 0.0f, 3650.0f );
	houses[ 6 ].SetRotationY( DEG_TO_RAD( 76.0f ) );
	houses[ 7 ].SetPosition( 4460.0f, 0.0f, 1610.0f );
	houses[ 7 ].SetRotationY( DEG_TO_RAD( 92.0f ) );
	houses[ 8 ].SetPosition( 1200.0f, 0.0f, 6400.0f );
	houses[ 8 ].SetRotationY( DEG_TO_RAD( 353.0f ) );
	houses[ 9 ].SetPosition( 4500.0f, 0.0f, -4500.0f );
	houses[ 9 ].SetRotationY( DEG_TO_RAD( 125.0f ) );
	houses[ 10 ].SetPosition( 2660.0f, 0.0f, -5720.0f );
	houses[ 10 ].SetRotationY( DEG_TO_RAD( 169.0f ) );

	// �����̐���
	Model*	pModelGate = nullptr;					// ���f��
	Effect*	pEffectGateGeneral = nullptr;			// �ʏ�`��G�t�F�N�g
	Effect*	pEffectGateReflect = nullptr;			// ���˃G�t�F�N�g
	Effect*	pEffectGateShadow = nullptr;			// �e�G�t�F�N�g
	Effect*	pEffectGateParaboloid = nullptr;		// �����ϊ��G�t�F�N�g
	pModelGate = pArgument->pModel_->Get( _T( "torii.x" ) );
	pEffectGateGeneral = pArgument->pEffect_->Get( "ModelMaterial.fx" );
	pEffectGateReflect = pArgument->pEffect_->Get( "ModelMaterialReflect.fx" );
	pEffectGateShadow = pArgument->pEffect_->Get( "ModelShadow.fx" );
	pEffectGateParaboloid = pArgument->pEffect_->Get( "ModelParaboloid.fx" );
	gate = new ObjectModelMaterial();
	gate->Initialize( 0 );
	gate->CreateGraphic( 0, pModelGate, pArgument->pEffectParameter_, pEffectGateGeneral, pEffectGateReflect, pEffectGateShadow, pEffectGateParaboloid );
	gate->SetPosition( 5870.0f, 0.0f, -400.0f );
	gate->SetRotationY( DEG_TO_RAD( 90 ) );
	gate->SetScale( 1.0f, 1.0f, 1.0f );
/*
	// �ꏊ�̖ڈ�I�u�W�F�N�g�̐���
	Model*	pModelMarker = nullptr;					// ���f��
	Effect*	pEffectMarkerGeneral = nullptr;			// �ʏ�`��G�t�F�N�g
	Effect*	pEffectMarkerReflect = nullptr;			// ���˃G�t�F�N�g
	Effect*	pEffectMarkerShadow = nullptr;			// �e�G�t�F�N�g
	Effect*	pEffectMarkerParaboloid = nullptr;		// �����ϊ��G�t�F�N�g
	pModelMarker = pArgument->pModel_->Get( _T( "sizeTest.model" ) );
	pEffectMarkerGeneral = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pEffectMarkerReflect = pArgument->pEffect_->Get( _T( "SkinMeshReflect.fx" ) );
	pEffectMarkerShadow = pArgument->pEffect_->Get( _T( "SkinMeshShadow.fx" ) );
	pEffectMarkerParaboloid = pArgument->pEffect_->Get( _T( "SkinMeshParaboloid.fx" ) );
	markers = new ObjectSkinMesh[ 4 ];
	for( int counterMarker = 0; counterMarker < 4; ++counterMarker )
	{
		markers[ counterMarker ].Initialize( 0, 0 );
		markers[ counterMarker ].CreateGraphic( 0, pModelMarker, pArgument->pEffectParameter_,
			pEffectMarkerGeneral, pEffectMarkerReflect, pEffectMarkerShadow, pEffectMarkerParaboloid );
	}
	markers[ 0 ].SetPosition( 620.0f, 0.0f, 4550.0f );
	markers[ 0 ].SetRotationY( 0.0f );
	markers[ 1 ].SetPosition( -1920.0f, 0.0f, 610.0f );
	markers[ 1 ].SetRotationY( 0.0f );
	markers[ 2 ].SetPosition( 1230.0f, 0.0f, 990.0f );
	markers[ 2 ].SetRotationY( 0.0f );
	markers[ 3 ].SetPosition( 490.0f, 0.0f, 470.0f );
	markers[ 3 ].SetRotationY( 0.0f );
*/
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
	result = managerPoint->Initialize( 25600, 17, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pEffectPointReflect, pTexturePoint->pTexture_ );
	if( result != 0 )
	{
		//return result;
	}

	//	�ΉԃI�u�W�F�N�g�̃X�e�[�g������
	Fire::InitializeState();

	//	�ԉΊǗ��I�u�W�F�N�g����
	managerFireworks = new ManagerFireworks;
	managerFireworks->Initialize(managerPoint);
	managerFireworks->loadSound(pArgument_);

	// ���C�g�̐���
	managerFireworks->setManagerLight(pArgument->pLight_);


	//	�v���C���[�I�u�W�F�N�g(Pos�̓J�����Ƃ̑��΍��W)
	player = new Player;
	player->Initialize(
		//D3DXVECTOR3(0.0f, 150.0f, -2000.0f),
		D3DXVECTOR3(0.0f, -100.0f, 400.0f),
		pArgument);

/*
	// �X�L�����b�V���̐���
	Effect*	pEffectSkinMesh = nullptr;					// �G�t�F�N�g
	Effect*	pEffectSkinMeshReflect = nullptr;			// �G�t�F�N�g
	Effect*	pEffectSkinMeshShadow = nullptr;			// �G�t�F�N�g
	Effect*	pEffectSkinMeshParaboloid = nullptr;		// �G�t�F�N�g
	Model*	pModelSkinMesh = nullptr;					// ���f��
	pEffectSkinMesh = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pEffectSkinMeshReflect = pArgument->pEffect_->Get( _T( "SkinMeshReflect.fx" ) );
	pEffectSkinMeshShadow = pArgument->pEffect_->Get( _T( "SkinMeshShadow.fx" ) );
	pEffectSkinMeshParaboloid = pArgument->pEffect_->Get( _T( "SkinMeshParaboloid.fx" ) );
	pModelSkinMesh = pArgument_->pModel_->Get( _T( "test.model" ) );
	pObjectSkinMesh_[0] = new ObjectSkinMesh();
	pObjectSkinMesh_[0]->Initialize( 0, 1 );
	pObjectSkinMesh_[0]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_,
		pEffectSkinMesh, pEffectSkinMeshReflect, pEffectSkinMeshShadow, pEffectSkinMeshParaboloid );
	pObjectSkinMesh_[0]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[0]->SetPosition( 300.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[1] = new ObjectSkinMesh();
	pObjectSkinMesh_[1]->Initialize( 0, 1 );
	pObjectSkinMesh_[1]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_,
		pEffectSkinMesh, pEffectSkinMeshReflect, pEffectSkinMeshShadow, pEffectSkinMeshParaboloid );
	pObjectSkinMesh_[1]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[1]->SetPosition( 0.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[2] = new ObjectSkinMesh();
	pObjectSkinMesh_[2]->Initialize( 0, 1 );
	pObjectSkinMesh_[2]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_,
		pEffectSkinMesh, pEffectSkinMeshReflect, pEffectSkinMeshShadow, pEffectSkinMeshParaboloid );
	pObjectSkinMesh_[2]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[2]->SetPosition( -300.0f, 100.0f, 0.0f );
*/



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
	pTexture = pArgument_->pTexture_->Get( _T( "title/pushAKey.png" ) );
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
	pTexture = pArgument_->pTexture_->Get( _T( "common/font_edge.png" ) );

	startGame = new Object2D;
	startGame->Initialize(0);

	startGame->CreateGraphic(
	0,
	pArgument_->pEffectParameter_,
	pEffect,
	pTexture);

	startGame->SetPosition(-300.0f, -212.0f, 0.0f);
	startGame->SetScaleX(startXX_NormalSizeX);
	startGame->SetScaleY(startXX_NormalSizeY);
	startGame->SetEnableGraphic(false);


	startGame->SetScaleTexture(4.0f, 16.0f);
	startGame->SetPositionTexture(0.0f, 1.0f / 16.0f * 2.0f);


	//	�u���K�J�n�v�����I�u�W�F�N�g�̐���
	pTexture = pArgument_->pTexture_->Get( _T( "common/font_edge.png" ) );

	startTutorial = new Object2D;
	startTutorial->Initialize(0);

	startTutorial->CreateGraphic(
	0,
	pArgument_->pEffectParameter_,
	pEffect,
	pTexture);

	startTutorial->SetPosition(300.0f, -212.0f, 0.0f);
	startTutorial->SetScaleX(startXX_NormalSizeX);
	startTutorial->SetScaleY(startXX_NormalSizeY);
	startTutorial->SetEnableGraphic(false);

	startTutorial->SetScaleTexture(4.0f, 16.0f);
	startTutorial->SetPositionTexture(0.0f, 1.0f / 16.0f * 3.0f);

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







	//	���֘A�̓ǂݍ���
	bgmSound = pArgument_->pSound_->Get("bgm/title.wav");
	bgmSound->Play(-1);

	desideSound = pArgument_->pSound_->Get("se/deside.wav");
	selectSound = pArgument_->pSound_->Get("se/select.wav");
	cancelSound = pArgument_->pSound_->Get("se/cancel.wav");


	DebugProc::SetIsVisible(false);


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
	bgmSound->Stop();
	desideSound->Stop();
	selectSound->Stop();
	cancelSound->Stop();

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
/*
	delete pObjectSkinMesh_[2];
	delete pObjectSkinMesh_[1];
	delete pObjectSkinMesh_[0];
	pObjectSkinMesh_[2] = nullptr;
	pObjectSkinMesh_[1] = nullptr;
	pObjectSkinMesh_[0] = nullptr;
*/
	delete player;
	player = nullptr;

	delete managerFireworks;
	managerFireworks = nullptr;

	Fire::FinalizeState();

	delete managerPoint;
	managerPoint = nullptr;

	// �ꏊ�ڈ�I�u�W�F�N�g�̊J��
//	delete[] markers;
//	markers = nullptr;

	// �����I�u�W�F�N�g�̊J��
	delete gate;
	gate = nullptr;

	// �ƃI�u�W�F�N�g�̊J��
	delete[] houses;
	houses = nullptr;

	// ���ԃI�u�W�F�N�g�̊J��
	delete waterwheel;
	waterwheel = nullptr;

	// ���I�u�W�F�N�g�̊J��
	delete bridge;
	bridge = nullptr;

	// �n�`�I�u�W�F�N�g�̊J��
	delete field;
	field = nullptr;

	// ��I�u�W�F�N�g�̊J��
	delete river;
	river = nullptr;

	// ��I�u�W�F�N�g�̊J��
	delete sky;
	sky = nullptr;

	// ���C�g�̊J��
	if( pLight_ != nullptr )
	{
		pLight_->Release();
		pLight_ = nullptr;
	}

	// �e�p�J�����_�̊J��
	for( int counterLightPoint = 0; counterLightPoint < GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW; ++counterLightPoint )
	{
		if( ppCameraShadowPoint_[ counterLightPoint ] != nullptr )
		{
			ppCameraShadowPoint_[ counterLightPoint ]->SetState( nullptr );
			ppCameraShadowPoint_[ counterLightPoint ] = nullptr;
		}
	}
	delete[] ppCameraShadowPoint_;
	ppCameraShadowPoint_ = nullptr;

	// �e�p�J�������̊J��
	if( pCameraShadowFar_ != nullptr )
	{
		pCameraShadowFar_->SetState( nullptr );
		pCameraShadowFar_ = nullptr;
	}

	// �e�p�J�����߂̊J��
	if( pCameraShadowNear_ != nullptr )
	{
		pCameraShadowNear_->SetState( nullptr );
		pCameraShadowNear_ = nullptr;
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

	// �œ_�����̍X�V
	D3DXVECTOR3	positionLookAt;		// �����_
	pCamera_->GetPositionLookAt( &positionLookAt );
	pArgument_->pEffectParameter_->SetForcus( 2.5f * pCamera_->GetViewZ( positionLookAt ) );

	// �e�p�J�����߂̍X�V
	D3DXVECTOR3	vectorLight;		// ���C�g�x�N�g��
	positionLookAt.y = 0.0f;
	pLight_->GetVector( &vectorLight );
	vectorLight *= -3500.0f;
	pCameraShadowNear_->SetPositionCamera( positionLookAt + vectorLight );
	pCameraShadowNear_->SetPositionLookAt( positionLookAt );

	// �e�p�J�������̍X�V
	pLight_->GetVector( &vectorLight );
	vectorLight *= -10000.0f;
	pCameraShadowFar_->SetPositionCamera( positionLookAt + vectorLight );
	pCameraShadowFar_->SetPositionLookAt( positionLookAt );

	// �e�p�J�����_�̍X�V
	const LightPoint*	pLightPoint = nullptr;		// �_����
	for( int counterLightPoint = 0; counterLightPoint < GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW; ++counterLightPoint )
	{
		pLightPoint = pArgument_->pEffectParameter_->GetLightPointLightness( counterLightPoint );
		if( pLightPoint != nullptr )
		{
			D3DXVECTOR3	positionLightPointCamera;		// �_�����̎��_���W
			D3DXVECTOR3	positionLightPointLookAt;		// �_�����̒����_���W
			pLightPoint->GetPosition( &positionLightPointCamera );
			positionLightPointLookAt = positionLightPointCamera;
			positionLightPointLookAt.y -= 1000.0f;
			ppCameraShadowPoint_[ counterLightPoint ]->SetPositionCamera( positionLightPointCamera );
			ppCameraShadowPoint_[ counterLightPoint ]->SetPositionLookAt( positionLightPointLookAt );
		}
	}

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

	//	�f���ֈڍs
	/*ManagerSceneMain::demoCount++;
	//if(ManagerSceneMain::demoCount == ManagerSceneMain::demoCountMax / 2)
	if(ManagerSceneMain::demoCount == 60)
	{
		ManagerSceneMain::demoCount = 0;

		//	���̍X�V�֐���
		fpUpdate = &SceneTitle::fadeUpdateDemo;

		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
		}
	}*/


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

		//	���Đ�
		desideSound->Play();

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

			//	���Đ�
			desideSound->Play();

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

		//	���Đ�
		selectSound->Play();

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

		//	���Đ�
		selectSound->Play();

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
void SceneTitle::fadeUpdateDemo( void )
{
	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;

	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );//�ق�Ƃ̓`���[�g���A��
		ManagerSceneMain::demoFlag = true;

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

		//	���Đ�
		desideSound->Play();

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

		//	���Đ�
		desideSound->Play();

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

		//	���Đ�
		cancelSound->Play();

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

		//	���Đ�
		cancelSound->Play();

		return false;
	}

	return true;
}
