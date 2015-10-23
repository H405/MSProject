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
#include "../framework/input/InputKeyboard.h"
#include "../framework/light/LightDirection.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerPoint.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

// �e�X�g
#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectSky.h"

#include "../graphic/graphic/GraphicPoint.h"
#include "../framework/polygon/PolygonPoint.h"

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
SceneGame::SceneGame( void ) : SceneMain()
{
	// �N���X���̏���������
	InitializeSelf();
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
	result = pCamera_->Initialize( D3DX_PI / 4.0f, 1280, 720, 0.1f, 1000.0f,
		D3DXVECTOR3( 0.0f, 20.0f, -100.0f ), D3DXVECTOR3( 0.0f, 0.0f, 10.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
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

	// �|�C���g�X�v���C�g�Ǘ��N���X�̐���
	Effect*		pEffectPoint = nullptr;			// �|�C���g�G�t�F�N�g
	Texture*	pTexturePoint = nullptr;		// �|�C���g�e�N�X�`��
	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pTexturePoint = pArgument->pTexture_->Get( _T( "effect000.jpg" ) );
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

	// �e�X�g������
	Effect*		pEffect = pArgument->pEffect_->Get( _T( "Polygon3D.fx" ) );
	Texture*	pTexture = pArgument->pTexture_->Get( _T( "title_logo.png" ) );;
	pObject_ = new Object2D[ 100 ];
	countObject_ = 0;
	pObject3D_ = new Object3D();
	pObject3D_->Initialize( 0 );
	pObject3D_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffect, pTexture );
	pObject3D_->SetScale( 1000.0f, 1.0f, 1000.0f );
	pObject3D_->SetPositionY( -40.0f );

	Effect*	pEffectModel = pArgument->pEffect_->Get( _T( "Model.fx" ) );
	Model*	pModel = pArgument->pModel_->Get( _T( "kuma.x" ) );
	pObjectModel_ = new ObjectModel();
	pObjectModel_->Initialize( 0 );
	pObjectModel_->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel );

	Effect*	pEffectMesh = pArgument->pEffect_->Get( _T( "Mesh.fx" ) );
	pObjectMesh_ = new ObjectMesh();
	pObjectMesh_->Initialize( 0, pArgument->pDevice_, 10, 10, 100.0f, 100.0f, 1.0f, 1.0f );
	pObjectMesh_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectMesh, pTexture );

	Effect*	pEffectSky = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	pObjectSky_ = new ObjectSky();
	pObjectSky_->Initialize( 0, pArgument->pDevice_, 32, 32, 500.0f, 1.0f, 1.0f );
	pObjectSky_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSky, pTexture );
#if 0
	pPolygonPoint_ = new PolygonPoint();
	pPolygonPoint_->Initialize( 32, pArgument->pDevice_ );

	Effect*	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pGraphicPoint_ = new GraphicPoint();
	pGraphicPoint_->Initialize( 0, pArgument->pEffectParameter_, pEffectPoint, pPolygonPoint_, pTexture->pTexture_ );
#endif
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
	// �e�X�g�I��
	delete pObjectSky_;
	pObjectSky_ = nullptr;
	delete pObjectMesh_;
	pObjectMesh_ = nullptr;
	delete pObjectModel_;
	pObjectModel_ = nullptr;
	delete pObject3D_;
	pObject3D_ = nullptr;
	delete[] pObject_;
	pObject_ = nullptr;

	// �|�C���g�X�v���C�g�Ǘ��N���X�̊J��
	delete pPoint_;
	pPoint_ = nullptr;

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

	// �|�C���g�X�v���C�g�Ǘ��N���X�̍X�V
	pPoint_->Update();

	// �e�X�g
	for( int i = 0; i < 10; ++i )
	{
		D3DXVECTOR3	velocityPoint;
		float		angleY = 2.0f * D3DX_PI * (static_cast< float >( rand() ) / RAND_MAX);
		float		angleZ = 2.0f * D3DX_PI * (static_cast< float >( rand() ) / RAND_MAX);
		velocityPoint.x = cosf( angleY ) * sinf( angleZ );
		velocityPoint.y = cosf( angleZ );
		velocityPoint.z = sinf( angleY ) * sinf( angleZ );
		pPoint_->Add( 100, D3DXVECTOR3( 0.0f, 10.0f, 0.0f ), D3DXCOLOR( 1.0f, 0.2f, 0.2f, 0.9f ), 100.0f,
			velocityPoint, D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.01f ), 0.0f, ManagerPoint::STATE_ADD );
	}

	// �e�X�g
	PrintDebug( _T( "�Q�[���V�[��\n" ) );
	if( pArgument_->pKeyboard_->IsTrigger( DIK_A ) && countObject_ < 100 )
	{
		Effect*		pEffect = nullptr;
		Texture*	pTexture = nullptr;
		pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
		pTexture = pArgument_->pTexture_->Get( _T( "title_logo.png" ) );
		pObject_[ countObject_ ].Initialize( 0 );
		pObject_[ countObject_ ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect, pTexture );
		pObject_[ countObject_ ].SetColor( 0.5f, 1.0f, 0.5f, 0.8f );
		++countObject_;
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_D ) && countObject_ > 0 )
	{
		pObject_[ countObject_ - 1 ].Finalize();
		--countObject_;
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_C ) )
	{
		pCamera_->SetDebug( true );
	}
	pObjectModel_->AddRotationY( 0.1f );

	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_RESULT );
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
void SceneGame::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pCamera_ = nullptr;
	pLight_ = nullptr;
	pPoint_ = nullptr;
}
