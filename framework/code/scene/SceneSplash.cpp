//==============================================================================
//
// File   : SceneSplash.cpp
// Brief  : �X�v���b�V���V�[���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "SceneSplash.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/system/Fade.h"
#include "../framework/system/Utility.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

#include "../framework/camera/CameraObject.h"
#include "../framework/camera/ManagerCamera.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/VirtualController.h"
#include "../framework/light/LightDirection.h"
#include "../framework/light/LightPoint.h"
#include "../framework/light/ManagerLight.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerMotion.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/Window.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/ObjectBillboard.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectModelMaterial.h"
#include "../object/ObjectRiver.h"
#include "../object/ObjectSkinMesh.h"
#include "../object/ObjectSky.h"
#include "../system/camera/CameraStateSpline.h"
#include "../system/EffectParameter.h"
#include "../system/point/ManagerPoint.h"
#include "../system/point/PointMain.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneSplash::SceneSplash( void ) : SceneMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneSplash::~SceneSplash( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
int SceneSplash::Initialize( SceneArgumentMain* pArgument )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Initialize( pArgument );
	if( result != 0 )
	{
		return result;
	}

	// �J���������̐���
	pCameraState_ = new CameraStateSpline();
	if( pCameraState_ == nullptr )
	{
		return 1;
	}
	result = pCameraState_->Initialize( 2, 2, 2 );
	if( result != 0 )
	{
		return result;
	}
	pCameraState_->SetControlPointCamera( 0, D3DXVECTOR3( -50.0f, 20.0f, -50.0f ), D3DXVECTOR3( 150.0f, 150.0f, 0.0f ) );
	pCameraState_->SetControlPointCamera( 1, D3DXVECTOR3( 100.0f, 70.0f, 100.0f ), D3DXVECTOR3( 0.0f, 150.0f, 150.0f ) );
	pCameraState_->SetControlPointLookAt( 0, D3DXVECTOR3( 100.0f, 70.0f, 100.0f ), D3DXVECTOR3( 0.0f, 150.0f, 150.0f ) );
	pCameraState_->SetControlPointLookAt( 1, D3DXVECTOR3( -50.0f, 20.0f, -50.0f ), D3DXVECTOR3( 150.0f, 150.0f, 0.0f ) );
	pCameraState_->SetSection( 0, 60, 0, 1, 0, 1 );
	pCameraState_->SetSection( 1, 120, -1, 0, -1, 0 );

	// �J�����̐ݒ�
	pCamera_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pCamera_->Set( D3DX_PI / 4.0f, pArgument->pWindow_->GetWidth(), pArgument->pWindow_->GetHeight(), 0.1f, 1000.0f,
		D3DXVECTOR3( 10.0f, 30.0f, -150.0f ), D3DXVECTOR3( 0.0f, 0.0f, 20.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	if( result != 0 )
	{
		return result;
	}
	pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( pCameraState_ );
	pArgument->pEffectParameter_->SetCamera( GraphicMain::CAMERA_GENERAL, &pCamera_[ GraphicMain::CAMERA_GENERAL ] );

	// ���C�g�̐ݒ�
	pLight_ = pArgument->pLight_->GetLightDirection();
	if( pLight_ == nullptr )
	{
		return 1;
	}
	pLight_->Set( D3DXCOLOR( 0.25f, 0.3f, 0.4f, 1.0f ), D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR3( -1.0f, -1.0f, 1.0f ) );

	// �|�C���g���C�g�̐ݒ�
	ppPointLight_ = new LightPoint*[ GraphicMain::LIGHT_POINT_MAX ];
	if( ppPointLight_ == nullptr )
	{
		return 1;
	}

	ppPointLight_[ 0 ] = pArgument->pLight_->GetLightPoint();
	ppPointLight_[ 0 ]->Set( D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( -20.0f, 10.0f, 0.0f ),  D3DXVECTOR3( 0.0f, 0.02f, 0.001f ) );

	ppPointLight_[ 1 ] = pArgument->pLight_->GetLightPoint();
	ppPointLight_[ 1 ]->Set( D3DXCOLOR( 0.25f, 0.25f, 1.0f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( 20.0f, 10.0f, 0.0f ),  D3DXVECTOR3( 0.0f, 0.02f, 0.001f ) );

	ppPointLight_[ 2 ] = pArgument->pLight_->GetLightPoint();
	ppPointLight_[ 2 ]->Set( D3DXCOLOR( 0.25f, 1.0f, 0.25f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( 0.0f, 10.0f, -100.0f ),  D3DXVECTOR3( 0.0f, 0.01f, 0.002f ) );

	for( int i = 3; i < GraphicMain::LIGHT_POINT_MAX; ++i )
	{
		ppPointLight_[ i ] = pArgument->pLight_->GetLightPoint();
		ppPointLight_[ i ]->Set( D3DXCOLOR( 1.0f, 1.0f, 0.5f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
			D3DXVECTOR3( 1.0f * (rand() % 100) - 50.0f - 100.0f, 10.0f, 1.0f * (rand() % 100) - 50.0f + 100.0f ),  D3DXVECTOR3( 0.0f, 0.01f, 0.002f ) );
		ppPointLight_[ i ]->SetIsEnable( false );
	}
	countLight_ = 3;

	// �e�p�J�����̐ݒ�
	D3DXVECTOR3	vectorLight;		// ���C�g�x�N�g��
	pLight_->GetVector( &vectorLight );
	vectorLight *= -500.0f;
	pCameraShadow_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_SHADOW_NEAR );
	pCameraShadow_->Set( D3DX_PI / 4.0f, pArgument->pWindow_->GetWidth(), pArgument->pWindow_->GetHeight(), 0.1f, 1000.0f,
		vectorLight, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), false );

	// �����̐ݒ�
	pArgument->pEffectParameter_->SetColorAmbient( 0.1f, 0.15f, 0.2f );

	// �|�C���g�X�v���C�g�Ǘ��N���X�̐���
	Effect*		pEffectPoint = nullptr;				// �|�C���g�G�t�F�N�g
	Effect*		pEffectPointReflect = nullptr;		// �|�C���g�G�t�F�N�g
	Texture*	pTexturePoint = nullptr;			// �|�C���g�e�N�X�`��
	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pEffectPointReflect = pArgument->pEffect_->Get( _T( "PointReflect.fx" ) );
	pTexturePoint = pArgument->pTexture_->Get( _T( "common/effect000.jpg" ) );
	pPoint_ = new ManagerPoint();
	if( pPoint_ == nullptr )
	{
		return 1;
	}
	result = pPoint_->Initialize( 4096, 8, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pEffectPointReflect, pTexturePoint->pTexture_ );
	if( result != 0 )
	{
		return result;
	}

	// 2D�I�u�W�F�N�g�̐���
	Effect*		pEffect2D = nullptr;		// �G�t�F�N�g
	Texture*	pTexture2D = nullptr;		// �e�N�X�`��
	Texture		textureTest;				// �e�X�g�e�N�X�`��
	pEffect2D = pArgument->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture2D = pArgument_->pTexture_->Get( _T( "test/title_logo.png" ) );
	textureTest.Initialize( pArgument->pTextureTest_, 320, 180 );
	pObject2D_ = new Object2D();
	pObject2D_->Initialize( 0 );
	pObject2D_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffect2D, &textureTest );
//	pObject2D_->SetPosition( 430.0f, 310.0f, 0.0f );
	pObject2D_->SetPosition( 480.0f, 270.0f, 0.0f );

	// ���b�V���̐���
	Effect*		pEffectMesh = nullptr;		// �G�t�F�N�g
	Texture*	pTextureMesh = nullptr;		// ���b�V��
	pEffectMesh = pArgument->pEffect_->Get( _T( "Mesh.fx" ) );
	pTextureMesh = pArgument_->pTexture_->Get( _T( "test/field001.jpg" ) );
	pObjectMesh_ = new ObjectMesh();
	pObjectMesh_->Initialize( 0, pArgument->pDevice_, 20, 20, 50.0f, 50.0f, 1.0f, 1.0f );
	pObjectMesh_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectMesh, pTextureMesh );

	// �X�J�C�h�[���̐���
	Effect*		pEffectSky = nullptr;				// �G�t�F�N�g
	Effect*		pEffectSkyReflect = nullptr;		// �G�t�F�N�g
	Texture*	pTextureSky = nullptr;				// �e�N�X�`��
	pEffectSky = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	pEffectSkyReflect = pArgument->pEffect_->Get( _T( "SkyReflect.fx" ) );
	pTextureSky = pArgument_->pTexture_->Get( _T( "test/night.png" ) );
	pObjectSky_ = new ObjectSky();
	pObjectSky_->Initialize( 0, pArgument->pDevice_, 32, 32, 500.0f, 1.0f, 1.0f );
	pObjectSky_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSky, pEffectSkyReflect, pTextureSky );

	// ���f���̐���
	Effect*	pEffectModel = nullptr;				// �G�t�F�N�g
	Effect*	pEffectModelReflect = nullptr;		// �G�t�F�N�g
	Effect*	pEffectModelShadow = nullptr;		// �G�t�F�N�g
	Model*	pModel = nullptr;					// ���f��
	pEffectModel = pArgument->pEffect_->Get( _T( "Model.fx" ) );
	pEffectModelReflect = pArgument->pEffect_->Get( _T( "ModelReflect.fx" ) );
	pEffectModelShadow = pArgument->pEffect_->Get( _T( "ModelShadow.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "kuma.x" ) );
	pObjectModel_ = new ObjectModel[ COUNT_MODEL ];
	pObjectModel_[ 0 ].Initialize( 0 );
	pObjectModel_[ 0 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel, pEffectModelReflect, pEffectModelShadow );
	pObjectModel_[ 1 ].Initialize( 0 );
	pObjectModel_[ 1 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel, pEffectModelReflect, pEffectModelShadow );
	pObjectModel_[ 1 ].SetPositionX( 50.0f );
	pObjectModel_[ 2 ].Initialize( 0 );
	pObjectModel_[ 2 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel, pEffectModelReflect, pEffectModelShadow );
	pObjectModel_[ 2 ].SetPositionX( -50.0f );
	pObjectModel_[ 2 ].SetPositionY( 20.0f );

	// �e�N�X�`���Ȃ����f���̐���
	Effect*	pEffectModelMaterial = nullptr;				// �G�t�F�N�g
	Effect*	pEffectModelMaterialReflect = nullptr;		// �G�t�F�N�g
	Effect*	pEffectModelMaterialShadow = nullptr;		// �G�t�F�N�g
	Model*	pModelModelMaterial = nullptr;				// ���f��
	pEffectModelMaterial = pArgument->pEffect_->Get( _T( "ModelMaterial.fx" ) );
	pEffectModelMaterialReflect = pArgument->pEffect_->Get( _T( "ModelMaterialReflect.fx" ) );
	pEffectModelMaterialShadow = pArgument->pEffect_->Get( _T( "ModelShadow.fx" ) );
	pModelModelMaterial = pArgument_->pModel_->Get( _T( "head.x" ) );
	pObjectModelMaterial_ = new ObjectModelMaterial();
	pObjectModelMaterial_->Initialize( 0 );
	pObjectModelMaterial_->CreateGraphic( 0, pModelModelMaterial, pArgument->pEffectParameter_,
		pEffectModelMaterial, pEffectModelMaterialReflect, pEffectModelMaterialShadow );
	pObjectModelMaterial_->SetPosition( -10.0f, 30.0f, 40.0f );

	// �r���{�[�h�̐���
	Effect*		pEffectBillboard = nullptr;			// �G�t�F�N�g
	Texture*	pTextureBillboard = nullptr;		// �e�N�X�`��
	pEffectBillboard = pArgument->pEffect_->Get( _T( "Billboard.fx" ) );
	pTextureBillboard = pArgument_->pTexture_->Get( _T( "common/finger.png" ) );
	pObjectBoard_ = new ObjectBillboard();
	pObjectBoard_->Initialize( 0 );
	pObjectBoard_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectBillboard, pTextureBillboard );
	pObjectBoard_->SetScale( pObjectBoard_->GetScaleX() * 0.1f, pObjectBoard_->GetScaleY() * 0.1f, 1.0f );
	pObjectBoard_->SetPosition( -50.0f, 90.0f, 0.0f );

	// �X�L�����b�V���̐���
	Effect*	pEffectSkinMesh = nullptr;				// �G�t�F�N�g
	Effect*	pEffectSkinMeshReflect = nullptr;		// �G�t�F�N�g
	Model*	pModelSkinMesh = nullptr;				// ���f��
	pEffectSkinMesh = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pEffectSkinMeshReflect = pArgument->pEffect_->Get( _T( "SkinMeshReflect.fx" ) );
	pModelSkinMesh = pArgument_->pModel_->Get( _T( "test.model" ) );
	pObjectSkinMesh_ = new ObjectSkinMesh();
	pObjectSkinMesh_->Initialize( 0, 1 );
	pObjectSkinMesh_->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh, pEffectSkinMeshReflect );
	pObjectSkinMesh_->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_->SetPosition( -100.0f, 0.0f, 100.0f );

	// ��̐���
	Effect*	pEffectRiver = nullptr;		// �G�t�F�N�g
	Model*	pModelRiver = nullptr;		// ���f��
	pEffectRiver = pArgument->pEffect_->Get( "water.fx" );
	pModelRiver = pArgument->pModel_->Get( _T( "river.x" ), Vertex::ELEMENT_SET_NORMAL_MAP );
	pObjectRiver_ = new ObjectRiver();
	result = pObjectRiver_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	pObjectRiver_->CreateGraphic( 0, pModelRiver, pArgument->pEffectParameter_, pEffectRiver, pArgument->pTextureNormalWave_,
		pArgument->pTextureReflect_, pArgument->pTextureReflectNotLight_, pArgument->pTextureReflectAdd_, pArgument->pTexture3D_, pArgument->pTextureDepth_ );
	pObjectRiver_->SetPositionY( 5.0f );
	pArgument->pEffectParameter_->SetHeightReflect( 5.0f );

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
int SceneSplash::Finalize( void )
{
	// ��̊J��
	delete pObjectRiver_;
	pObjectRiver_ = nullptr;

	// �X�L�����b�V���̊J��
	delete pObjectSkinMesh_;
	pObjectSkinMesh_ = nullptr;

	// �r���{�[�h�̊J��
	delete pObjectBoard_;
	pObjectBoard_ = nullptr;

	// �e�N�X�`���Ȃ����f���̊J��
	delete pObjectModelMaterial_;
	pObjectModelMaterial_ = nullptr;

	// ���f���̊J��
	delete[] pObjectModel_;
	pObjectModel_ = nullptr;

	// �X�J�C�h�[���̊J��
	delete pObjectSky_;
	pObjectSky_ = nullptr;

	// ���b�V���̊J��
	delete pObjectMesh_;
	pObjectMesh_ = nullptr;

	// 2D�I�u�W�F�N�g�̊J��
	delete pObject2D_;
	pObject2D_ = nullptr;

	// �|�C���g�X�v���C�g�Ǘ��N���X�̊J��
	delete pPoint_;
	pPoint_ = nullptr;

	// �|�C���g���C�g�̊J��
	for( int counterLight = 0; counterLight < GraphicMain::LIGHT_POINT_MAX; ++counterLight )
	{
		if( ppPointLight_[ counterLight ] != nullptr )
		{
			ppPointLight_[ counterLight ]->Release();
			ppPointLight_[ counterLight ] = nullptr;
		}
	}
	delete[] ppPointLight_;
	ppPointLight_ = nullptr;

	// ���C�g�̊J��
	if( pLight_ != nullptr )
	{
		pLight_->Release();
		pLight_ = nullptr;
	}

	// �J���������̊J��
	pCamera_->SetState( nullptr );
	delete pCameraState_;
	pCameraState_ = nullptr;

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
int SceneSplash::Reinitialize( SceneArgumentMain* pArgument )
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
// Arg    : SceneSplash* pOut					: �R�s�[��A�h���X
//==============================================================================
int SceneSplash::Copy( SceneSplash* pOut ) const
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
void SceneSplash::Update( void )
{
	// �e�X�g
	PrintDebug( _T( "�X�v���b�V��\n" ) );

	// �|�C���g�X�v���C�g�Ǘ��N���X�̍X�V
	pPoint_->Update();

	// �œ_�����̍X�V
	D3DXVECTOR3	positionLookAt;		// �����_
	pCamera_[ GraphicMain::CAMERA_GENERAL ].GetPositionLookAt( &positionLookAt );
	pArgument_->pEffectParameter_->SetForcus( pCamera_[ GraphicMain::CAMERA_GENERAL ].GetViewZ( positionLookAt ) );

	// �e�p�J�����̍X�V
	D3DXVECTOR3	vectorLight;		// ���C�g�x�N�g��
	pLight_->GetVector( &vectorLight );
	vectorLight *= -500.0f;
	pCameraShadow_->SetPositionCamera( positionLookAt + vectorLight );
	pCameraShadow_->SetPositionLookAt( positionLookAt );

	// ���f���̉�]
	pObjectModel_[ 0 ].AddRotationY( 0.01f );
	pObjectBoard_->AddRotationZ( 0.1f );
#if 0
	// ���C�g�̉�]
	static float	rotL = 0.0f;
	D3DXVECTOR3		vecDir;
	vecDir.x = cosf( rotL );
	vecDir.y = -0.5f;
	vecDir.z = sinf( rotL );
	pLight_[ GraphicMain::LIGHT_DIRECTIONAL_GENERAL ].SetVector( vecDir );
	rotL += 0.01f;
	if( rotL > 2.0f * D3DX_PI )
	{
		rotL -= 2.0f * D3DX_PI;
	}
#endif

	// ���C�g�̉�]�p�x������
	float	angleLight;		// ���C�g�̉�]�p�x
	angleLight = D3DX_PI * timerLight_ / 120.0f;
	++timerLight_;

	// �ԃ|�C���g���C�g�̈ړ�
	D3DXVECTOR3	positionPointR;		// �|�C���g���C�g�̍��W
	ppPointLight_[ 0 ]->GetPosition( &positionPointR );
	positionPointR.x = 30.0f * cosf( angleLight );
	positionPointR.z = 30.0f * sinf( angleLight );
	ppPointLight_[ 0 ]->SetPosition( positionPointR );

	// �|�C���g���C�g�̈ړ�
	D3DXVECTOR3	positionPointB;		// �|�C���g���C�g�̍��W
	ppPointLight_[ 1 ]->GetPosition( &positionPointB );
	positionPointB.x = 30.0f * cosf( angleLight + D3DX_PI );
	positionPointB.z = 30.0f * sinf( angleLight + D3DX_PI );
	if( timerLight_ % 240 < 120 )
	{
		Utility::SplineVector3( D3DXVECTOR3( -50.0f, 20.0f, -50.0f ), D3DXVECTOR3( 150.0f, 150.0f, 0.0f ), D3DXVECTOR3( 100.0f, 70.0f, 100.0f ), D3DXVECTOR3( 0.0f, 150.0f, 150.0f ),
			static_cast< float >( timerLight_ % 120 ) / 120.0f, &positionPointB );
	}
	else
	{
		Utility::SplineVector3( D3DXVECTOR3( 100.0f, 70.0f, 100.0f ), D3DXVECTOR3( 0.0f, 150.0f, 150.0f ), D3DXVECTOR3( -50.0f, 20.0f, -50.0f ), D3DXVECTOR3( 150.0f, 150.0f, 0.0f ),
			static_cast< float >( (timerLight_ % 240) - 120 ) / 120.0f, &positionPointB );
	}
	ppPointLight_[ 1 ]->SetPosition( positionPointB );

	// �΃|�C���g���C�g�̈ړ�
	D3DXVECTOR3	positionPointG;		// �|�C���g���C�g�̍��W
	ppPointLight_[ 2 ]->GetPosition( &positionPointG );
	if( pArgument_->pVirtualController_->IsPress( VC_LEFT ) )
	{
		positionPointG.x -= 1.0f;
	}
	else if( pArgument_->pVirtualController_->IsPress( VC_RIGHT ) )
	{
		positionPointG.x += 1.0f;
	}
	if( pArgument_->pVirtualController_->IsPress( VC_DOWN ) )
	{
		positionPointG.z -= 1.0f;
	}
	else if( pArgument_->pVirtualController_->IsPress( VC_UP ) )
	{
		positionPointG.z += 1.0f;
	}
	if( pArgument_->pKeyboard_->IsPress( DIK_COMMA ) )
	{
		positionPointG.y -= 1.0f;
	}
	else if( pArgument_->pKeyboard_->IsPress( DIK_PERIOD ) )
	{
		positionPointG.y += 1.0f;
	}
	ppPointLight_[ 2 ]->SetPosition( positionPointG );

	// �G�t�F�N�g�̔���
	pPoint_->Add( 20, positionPointR, D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, PointMain::STATE_ADD );
	pPoint_->Add( 20, positionPointB, D3DXCOLOR( 0.25f, 0.25f, 1.0f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, PointMain::STATE_ADD );
	pPoint_->Add( 20, positionPointG, D3DXCOLOR( 0.25f, 1.0f, 0.25f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, PointMain::STATE_ADD );

	// �_������L���ɂ���
	if( pArgument_->pKeyboard_->IsTrigger( DIK_LBRACKET ) )
	{
		ppPointLight_[ countLight_ ]->SetIsEnable( true );
		++countLight_;
		if( countLight_ >= GraphicMain::LIGHT_POINT_MAX )
		{
			countLight_ = GraphicMain::LIGHT_POINT_MAX - 1;
		}
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_RBRACKET ) )
	{
		ppPointLight_[ countLight_ ]->SetIsEnable( false );
		--countLight_;
		if( countLight_ < 0 )
		{
			countLight_ = 0;
		}
	}

	// �I�u�W�F�N�g�̈ړ�
	if( pArgument_->pKeyboard_->IsPress( DIK_A ) )
	{
		pObjectModel_[ 0 ].AddPositionX( -1.0f );
	}
	else if( pArgument_->pKeyboard_->IsPress( DIK_D ) )
	{
		pObjectModel_[ 0 ].AddPositionX( 1.0f );
	}
	if( pArgument_->pKeyboard_->IsPress( DIK_S ) )
	{
		pObjectModel_[ 0 ].AddPositionZ( -1.0f );
	}
	else if( pArgument_->pKeyboard_->IsPress( DIK_W ) )
	{
		pObjectModel_[ 0 ].AddPositionZ( 1.0f );
	}

	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_TITLE );
		SetIsEnd( true );
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_RETURN ) )
	{
		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
		}
	}
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneSplash::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pCamera_ = nullptr;
	pCameraShadow_ = nullptr;
	pLight_ = nullptr;
	ppPointLight_ = nullptr;
	pPoint_ = nullptr;
	pObject2D_ = nullptr;
	pObjectMesh_ = nullptr;
	pObjectSky_ = nullptr;
	pObjectModel_ = nullptr;
	pObjectModelMaterial_ = nullptr;
	pObjectBoard_ = nullptr;
	pObjectSkinMesh_ = nullptr;
	pObjectRiver_ = nullptr;
	timerLight_ = 0;
	countLight_ = 0;
	pCameraState_ = nullptr;
}
