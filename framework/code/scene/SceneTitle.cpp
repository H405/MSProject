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
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/VirtualController.h"
#include "../framework/light/LightDirection.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectMesh.h"
#include "../framework/polygon/PolygonMesh.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
static const int flashingCountHirf = 20;
static const int flashingCountMax = 40;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneTitle::SceneTitle( void ) : SceneMain(),
pushAKeyFlashingCount(-1),
pushChooseObjectFlashingCount(-1),
chooseObject(nullptr)
{
	// �N���X���̏���������
	InitializeSelf();
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

	//	�^�C�g�����S
	titleLogo = new Object2D;
	titleLogo->Initialize(0);

	Effect*		pEffect = nullptr;
	Texture*	pTexture = nullptr;
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "titlelogo.png" ) );

	titleLogo->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	titleLogo->SetPosition(350.0f, 100.0f, 0.0f);

	//	A�{�^���������Ă�
	pTexture = pArgument_->pTexture_->Get( _T( "pressAKey.png" ) );
	pushAKey = new Object2D;
	pushAKey->Initialize(0);

	pushAKey->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	pushAKey->SetPosition(0.0f, -100.0f, 0.0f);

	//	�X�V�֐��Z�b�g
	fpUpdate = &SceneTitle::FirstUpdate;

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
	if(startGame != nullptr)
		delete startGame;
	startGame = nullptr;

	if(startTutorial != nullptr)
		delete startTutorial;
	startTutorial = nullptr;

	if(pushAKey != nullptr)
		delete pushAKey;
	pushAKey = nullptr;

	delete titleLogo;
	titleLogo = nullptr;

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
	PrintDebug( _T( "�^�C�g��\n" ) );

	//	�ݒ肳�ꂽ�X�V�N���X��
	(this->*fpUpdate)();
}

//==============================================================================
// Brief  : �X�V����1(�uA�{�^���������Ăˁv�̓_��)
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::FirstUpdate( void )
{
	// �e�X�g
	PrintDebug( _T( "�^�C�g��\n" ) );

	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	�uA�{�^���������Ăˁv�������āA�u�����J�n�v�Ɓu���K�J�n�v�����ꂼ�ꐶ��
		delete pushAKey;
		pushAKey = nullptr;

		startGame = new Object2D;
		startGame->Initialize(0);

		startTutorial = new Object2D;
		startTutorial->Initialize(0);

		Effect*		pEffect = nullptr;
		Texture*	pTexture = nullptr;
		pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
		pTexture = pArgument_->pTexture_->Get( _T( "startGame.png" ) );

		startGame->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		startGame->SetPosition(-200.0f, -100.0f, 0.0f);

		pTexture = pArgument_->pTexture_->Get( _T( "startTutorial.png" ) );

		startTutorial->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		startTutorial->SetPosition(200.0f, -100.0f, 0.0f);

		//	�f�t�H���g�̑I�������u�����J�n�v�ɐݒ�
		chooseObject = startGame;

		//	���̍X�V�֐���
		fpUpdate = &SceneTitle::SecondUpdate;
	}

	//	�uA�{�^���������Ăˁv�̓_�ŏ���
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			//pushAKey->setColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			//pushAKey->setColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}
	}
}
//==============================================================================
// Brief  : �X�V����2(�Q�[���J�n�E�`���[�g���A���J�n�̑I������)
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::SecondUpdate( void )
{
	// �e�X�g
	PrintDebug( _T( "�^�C�g��\n" ) );

	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
		}
	}

	//	�I�����ڂ̓_�ŏ���
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			//chooseObject->setColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			//chooseObject->setColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}
	}
}
//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
