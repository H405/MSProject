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
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

#include "../framework/camera/CameraObject.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/VirtualController.h"
#include "../framework/light/LightDirection.h"
#include "../framework/light/LightPoint.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/Window.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/ObjectBillboard.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectSky.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerPoint.h"

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
		D3DXVECTOR3( 0.0f, 30.0f, -150.0f ),
		D3DXVECTOR3( 0.0f, 0.0f, 20.0f ),
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
	result = pLight_->Initialize( D3DXCOLOR( 0.25f, 0.3f, 0.4f, 1.0f ), D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR3( -1.0f, -1.0f, 1.0f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL, pLight_ );

	// �|�C���g���C�g�̐���
	pPointLight_ = new LightPoint[ GraphicMain::LIGHT_POINT_MAX ];
	if( pPointLight_ == nullptr )
	{
		return 1;
	}

	result = pPointLight_[ 0 ].Initialize( D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( -20.0f, 10.0f, 0.0f ),  D3DXVECTOR3( 0.0f, 0.02f, 0.001f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightPoint( 0, &pPointLight_[ 0 ] );

	result = pPointLight_[ 1 ].Initialize( D3DXCOLOR( 0.25f, 0.25f, 1.0f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( 20.0f, 10.0f, 0.0f ),  D3DXVECTOR3( 0.0f, 0.02f, 0.001f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightPoint( 1, &pPointLight_[ 1 ] );

	result = pPointLight_[ 2 ].Initialize( D3DXCOLOR( 0.25f, 1.0f, 0.25f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( 0.0f, 10.0f, -100.0f ),  D3DXVECTOR3( 0.0f, 0.01f, 0.002f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightPoint( 2, &pPointLight_[ 2 ] );

	// �|�C���g���C�g�̌���ݒ�
	pArgument->pEffectParameter_->SetCountLightPoint( 3 );

	// �����̐ݒ�
	pArgument->pEffectParameter_->SetColorAmbient( 0.1f, 0.15f, 0.2f );

	// �|�C���g�X�v���C�g�Ǘ��N���X�̐���
	Effect*		pEffectPoint = nullptr;			// �|�C���g�G�t�F�N�g
	Texture*	pTexturePoint = nullptr;		// �|�C���g�e�N�X�`��
	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pTexturePoint = pArgument->pTexture_->Get( _T( "common/effect000.jpg" ) );
	pPoint_ = new ManagerPoint();
	if( pPoint_ == nullptr )
	{
		return 1;
	}
	result = pPoint_->Initialize( 4096, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pTexturePoint->pTexture_ );
	if( result != 0 )
	{
		return result;
	}

	// 2D�I�u�W�F�N�g�̐���
	Effect*		pEffect2D = nullptr;		// �G�t�F�N�g
	Texture*	pTexture2D = nullptr;		// �e�N�X�`��
	pEffect2D = pArgument->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture2D = pArgument_->pTexture_->Get( _T( "test/title_logo.png" ) );
	pObject2D_ = new Object2D();
	pObject2D_->Initialize( 0 );
	pObject2D_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffect2D, pTexture2D );
	pObject2D_->SetPosition( 430.0f, 310.0f, 0.0f );

	// ���b�V���̐���
	Effect*		pEffectMesh = nullptr;		// �G�t�F�N�g
	Texture*	pTextureMesh = nullptr;		// ���b�V��
	pEffectMesh = pArgument->pEffect_->Get( _T( "Mesh.fx" ) );
	pTextureMesh = pArgument_->pTexture_->Get( _T( "test/field001.jpg" ) );
	pObjectMesh_ = new ObjectMesh();
	pObjectMesh_->Initialize( 0, pArgument->pDevice_, 20, 20, 50.0f, 50.0f, 1.0f, 1.0f );
	pObjectMesh_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectMesh, pTextureMesh );

	// �X�J�C�h�[���̐���
	Effect*		pEffectSky = nullptr;		// �G�t�F�N�g
	Texture*	pTextureSky = nullptr;		// �e�N�X�`��
	pEffectSky = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	pTextureSky = pArgument_->pTexture_->Get( _T( "test/night.png" ) );
	pObjectSky_ = new ObjectSky();
	pObjectSky_->Initialize( 0, pArgument->pDevice_, 32, 32, 500.0f, 1.0f, 1.0f );
	pObjectSky_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSky, pTextureSky );

	// ���f���̐���
	Effect*	pEffectModel = nullptr;		// �G�t�F�N�g
	Model*	pModel = nullptr;			// ���f��
	pEffectModel = pArgument->pEffect_->Get( _T( "Model.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "kuma.x" ) );
	pObjectModel_ = new ObjectModel[ COUNT_MODEL ];
	pObjectModel_[ 0 ].Initialize( 0 );
	pObjectModel_[ 0 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel );
	pObjectModel_[ 1 ].Initialize( 0 );
	pObjectModel_[ 1 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel );
	pObjectModel_[ 1 ].SetPositionX( 50.0f );
	pObjectModel_[ 2 ].Initialize( 0 );
	pObjectModel_[ 2 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel );
	pObjectModel_[ 2 ].SetPositionX( -50.0f );

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
	// �|�C���g���C�g�̌���ݒ�
	pArgument_->pEffectParameter_->SetCountLightPoint( 0 );

	// ���f���̔j��
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
	delete[] pPointLight_;
	pPointLight_ = nullptr;

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

	// �J�����̍X�V
	pCamera_->Update();

	// �|�C���g�X�v���C�g�Ǘ��N���X�̍X�V
	pPoint_->Update();

	// ���f���̉�]
	pObjectModel_[ 0 ].AddRotationY( 0.01f );

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
	pPointLight_[ 0 ].GetPosition( &positionPointR );
	positionPointR.x = 30.0f * cosf( angleLight );
	positionPointR.z = 30.0f * sinf( angleLight );
	pPointLight_[ 0 ].SetPosition( positionPointR );

	// �|�C���g���C�g�̈ړ�
	D3DXVECTOR3	positionPointB;		// �|�C���g���C�g�̍��W
	pPointLight_[ 1 ].GetPosition( &positionPointB );
	positionPointB.x = 30.0f * cosf( angleLight + D3DX_PI );
	positionPointB.z = 30.0f * sinf( angleLight + D3DX_PI );
	pPointLight_[ 1 ].SetPosition( positionPointB );

	// �΃|�C���g���C�g�̈ړ�
	D3DXVECTOR3	positionPointG;		// �|�C���g���C�g�̍��W
	pPointLight_[ 2 ].GetPosition( &positionPointG );
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
	pPointLight_[ 2 ].SetPosition( positionPointG );

	// �G�t�F�N�g�̔���
	pPoint_->Add( 20, positionPointR, D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, ManagerPoint::STATE_ADD );
	pPoint_->Add( 20, positionPointB, D3DXCOLOR( 0.25f, 0.25f, 1.0f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, ManagerPoint::STATE_ADD );
	pPoint_->Add( 20, positionPointG, D3DXCOLOR( 0.25f, 1.0f, 0.25f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, ManagerPoint::STATE_ADD );

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
	pLight_ = nullptr;
	pPointLight_ = nullptr;
	pPoint_ = nullptr;
	pObject2D_ = nullptr;
	pObjectMesh_ = nullptr;
	pObjectSky_ = nullptr;
	pObjectModel_ = nullptr;
	timerLight_ = 0;
}
