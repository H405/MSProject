//==============================================================================
//
// File   : ManagerMain.cpp
// Brief  : ���C���v���O�����Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <tchar.h>
#include "ManagerMain.h"
#include "ManagerSceneMain.h"
#include "SceneArgumentMain.h"
#include "WindowMain.h"
#include "../framework/camera/CameraStateDebug.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/graphic/Graphic.h"
#include "../framework/input/DirectInput.h"
#include "../framework/input/CWiiController.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/InputMouse.h"
#include "../framework/input/InputPad.h"
#include "../framework/input/VirtualController.h"
#include "../framework/object/Object.h"
#include "../framework/polygon/Polygon2D.h"
#include "../framework/polygon/Polygon3D.h"
#include "../framework/render/DirectDevice.h"
#include "../framework/render/RenderPass.h"
#include "../framework/render/RenderTarget.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/ManagerDraw.h"
#include "../framework/system/ManagerUpdate.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/ObjectScreen.h"
#include "../system/EffectParameter.h"

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
ManagerMain::ManagerMain( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerMain::~ManagerMain( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : HINSTANCE instanceHandle			: �C���X�^���X�n���h��
// Arg    : int typeShow						: �\���̎��
//==============================================================================
int ManagerMain::Initialize( HINSTANCE instanceHandle, int typeShow )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Manager::Initialize( instanceHandle, typeShow );
	if( result != 0 )
	{
		return result;
	}

	// �E�B���h�E�̐���
	HWND	windowHandle;		// �E�B���h�E�n���h��
	pWindow_ = new WindowMain();
	if( pWindow_ == nullptr )
	{
		return 1;
	}
	result = pWindow_->Initialize( instanceHandle, typeShow, 1280, 720, _T( "Framework" ), _T( "WindowClass" ) );
	if( result != 0 )
	{
		return result;
	}
	windowHandle = pWindow_->GetWindowHandle();

	// Direct3D�f�o�C�X�̐���
	IDirect3DDevice9*	pDevice = nullptr;			// Direct3D�f�o�C�X
	bool				isWindowMode = true;		// �E�B���h�E���[�h�t���O
#ifdef _DEBUG
	isWindowMode = true;
#endif
	pDevice_ = new DirectDevice();
	if( pDevice_ == nullptr )
	{
		return 1;
	}
	result = pDevice_->Initialize( pWindow_->GetWindowHandle(), pWindow_->GetWidth(), pWindow_->GetHeight(), isWindowMode );
	if( result != 0 )
	{
		return result;
	}
	pDevice = pDevice_->GetDevice();

	// �t�F�[�h�N���X�̐���
	pFade_ = new Fade();
	if( pFade_ == nullptr )
	{
		return 1;
	}
	result = pFade_->Initialize();
	if( result != 0 )
	{
		return result;
	}

	//	wii�����R�����̓N���X�̐����iDirectInput�����O�ɍs�����ƁI�j
	pWiiController_ = new CWiiController;

	// DirectInput�I�u�W�F�N�g�̐���
	IDirectInput8*	pDirectInput;		// DirectInput�I�u�W�F�N�g
	pDirectInput_ = new DirectInput();
	if( pDirectInput_ == nullptr )
	{
		return 1;
	}
	result = pDirectInput_->Initialize( instanceHandle );
	if( result != 0 )
	{
		return result;
	}
	pDirectInput = pDirectInput_->GetDirectInput();

	// �L�[�{�[�h���̓N���X�̐���
	pKeyboard_ = new InputKeyboard();
	if( pKeyboard_ == nullptr )
	{
		return 1;
	}
	result = pKeyboard_->Initialize( pDirectInput, windowHandle );
	if( result != 0 )
	{
		return result;
	}

	// �}�E�X���̓N���X�̐���
	pMouse_ = new InputMouse();
	if( pMouse_ == nullptr )
	{
		return 1;
	}
	result = pMouse_->Initialize( pDirectInput, windowHandle, pWindow_->GetWidth(), pWindow_->GetHeight() );
	if( result != 0 )
	{
		return result;
	}
#ifdef _DEBUG
	CameraStateDebug::SetInputMouse( pMouse_ );
#endif

	// �Q�[���p�b�h���̓N���X�̐���
	pPad_ = new InputPad();
	if( pPad_ == nullptr )
	{
		return 1;
	}
	result = pPad_->Initialize( pDirectInput, windowHandle );
	if( result != 0 )
	{
		return result;
	}

	//	���z�R���g���[���Ǘ��N���X�̐���
	pVirtualController_ = new VirtualController;
	pVirtualController_->initialize(pWiiController_, pKeyboard_, pMouse_, pPad_);

	// �p�X�N���X�̐���
	pRenderPass_ = new RenderPass[ GraphicMain::PASS_MAX ];
	if( pRenderPass_ == nullptr )
	{
		return 1;
	}
	result = pRenderPass_[ GraphicMain::PASS_3D ].Initialize( pDevice, GraphicMain::PASS_3D_RENDER_MAX );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_2D ].Initialize( pDevice, GraphicMain::PASS_2D_RENDER_MAX );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_SCREEN ].Initialize( pDevice, GraphicMain::PASS_SCREEN_RENDER_MAX );
	if( result != 0 )
	{
		return result;
	}

	// �`��Ǘ��N���X�̐���
	pDraw_ = new ManagerDraw< Graphic >();
	if( pDraw_ == nullptr )
	{
		return 1;
	}
	result = pDraw_->Initialize( 256, pDevice, GraphicMain::PASS_MAX, pRenderPass_ );
	if( result != 0 )
	{
		return result;
	}
	Graphic::SetManagerDraw( pDraw_ );

	// �`��\���N���X�̏�����
#ifdef _DEBUG
	result = DebugProc::Initialize( pDevice );
#endif
	if( result != 0 )
	{
		return result;
	}

	// �X�V�Ǘ��N���X�̐���
	pUpdate_ = new ManagerUpdate< Object >();
	if( pUpdate_ == nullptr )
	{
		return 1;
	}
	result = pUpdate_->Initialize( 256 );
	if( result != 0 )
	{
		return result;
	}
	Object::SetManagerUpdate( pUpdate_ );

	// �e�N�X�`���Ǘ��N���X�̐���
	pTexture_ = new ManagerTexture< Texture >();
	if( pTexture_ == nullptr )
	{
		return 1;
	}
	result = pTexture_->Initialize( _T( "data/texture/" ), 32, pDevice );
	if( result != 0 )
	{
		return result;
	}

	// ���f���Ǘ��N���X�̐���
	pModel_ = new ManagerModel< Model >();
	if( pModel_ == nullptr )
	{
		return 1;
	}
	result = pModel_->Initialize( _T( "data/model/" ), 32, pDevice, pTexture_ );
	if( result != 0 )
	{
		return result;
	}

	// �G�t�F�N�g�Ǘ��N���X�̐���
	pEffect_ = new ManagerEffect< Effect >();
	if( pEffect_ == nullptr )
	{
		return 1;
	}
	result = pEffect_->Initialize( _T( "data/effect/" ), 32, pDevice );
	if( result != 0 )
	{
		return result;
	}

	// �G�t�F�N�g�p�����[�^�̐���
	pEffectParameter_ = new EffectParameter();
	if( pEffectParameter_ == nullptr )
	{
		return 1;
	}
	result = pEffectParameter_->Initialize( GraphicMain::LIGHT_DIRECTIONAL_MAX, GraphicMain::LIGHT_POINT_MAX, GraphicMain::CAMERA_MAX );
	if( result != 0 )
	{
		return result;
	}
	pEffectParameter_->SetWidthScreen( static_cast< float >( pWindow_->GetWidth() ) );
	pEffectParameter_->SetHeightScreen( static_cast< float >( pWindow_->GetHeight() ) );

	// �����̐ݒ�
	pEffectParameter_->SetColorAmbient( 0.1f, 0.1f, 0.1f );

	// 2D�|���S���̐���
	pPolygon2D_ = new Polygon2D();
	if( pPolygon2D_ == nullptr )
	{
		return 1;
	}
	result = pPolygon2D_->Initialize( pDevice );
	if( result != 0 )
	{
		return result;
	}
	GraphicMain::SetPolygon2D( pPolygon2D_ );

	// 3D�|���S���̐���
	pPolygon3D_ = new Polygon3D();
	if( pPolygon3D_ == nullptr )
	{
		return 1;
	}
	result = pPolygon3D_->Initialize( pDevice );
	if( result != 0 )
	{
		return result;
	}
	GraphicMain::SetPolygon3D( pPolygon3D_ );

	// ��ʃI�u�W�F�N�g�̐���
	Effect*			pEffectScreen = nullptr;			// ��ʃG�t�F�N�g
	RenderTarget*	pRenderTarget3D = nullptr;			// 3D��ʕ`��Ώ�
	RenderTarget*	pRenderTarget2D = nullptr;			// 2D��ʕ`��Ώ�
	RenderTarget*	pRenderTargetMask = nullptr;		// �}�X�N�`��Ώ�
	pObjectScreen_ = new ObjectScreen();
	if( pObjectScreen_ == nullptr )
	{
		return 1;
	}
	result = pObjectScreen_->Initialize( 0, pFade_ );
	if( result != 0 )
	{
		return result;
	}
	pEffectScreen = pEffect_->Get( _T( "Screen.fx" ) );
	pRenderTarget3D = pRenderPass_[ GraphicMain::PASS_3D ].GetRenderTarget( GraphicMain::PASS_3D_RENDER_COLOR );
	pRenderTarget2D = pRenderPass_[ GraphicMain::PASS_2D ].GetRenderTarget( GraphicMain::PASS_2D_RENDER_COLOR );
	pRenderTargetMask = pRenderPass_[ GraphicMain::PASS_2D ].GetRenderTarget( GraphicMain::PASS_2D_RENDER_MASK );
	result = pObjectScreen_->CreateGraphic( 0, pEffectParameter_, pEffectScreen,
		pRenderTarget3D->GetTexture(), pRenderTarget2D->GetTexture(), pRenderTargetMask->GetTexture() );
	if( result != 0 )
	{
		return result;
	}
	pObjectScreen_->SetPositionY( 1.0f );

	// �V�[�������N���X�̐���
	pArgument_ = new SceneArgumentMain();
	if( pArgument_ == nullptr )
	{
		return 1;
	}
	pArgument_->pDevice_ = pDevice;
	pArgument_->pFade_ = pFade_;
	pArgument_->pEffectParameter_ = pEffectParameter_;
	pArgument_->pObjectScreen_ = pObjectScreen_;
	pArgument_->pWiiController_ = pWiiController_;
	pArgument_->pKeyboard_ = pKeyboard_;
	pArgument_->pMouse_ = pMouse_;
	pArgument_->pPad_ = pPad_;
	pArgument_->pVirtualController_ = pVirtualController_;
	pArgument_->pTexture_ = pTexture_;
	pArgument_->pModel_ = pModel_;
	pArgument_->pEffect_ = pEffect_;

	// �V�[���Ǘ��N���X�̐���
	pScene_ = new ManagerSceneMain();
	if( pScene_ == nullptr )
	{
		return 1;
	}
#ifdef _DEBUG
	result = pScene_->Initialize( ManagerSceneMain::TYPE_TITLE, pArgument_ );
#else
	result = pScene_->Initialize( ManagerSceneMain::TYPE_SPLASH, pArgument_ );
#endif
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerMain::Finalize( void )
{
	// �V�[���Ǘ��N���X�̊J��
	delete pScene_;
	pScene_ = nullptr;

	// �V�[�������N���X�̊J��
	delete pArgument_;
	pArgument_ = nullptr;

	// ��ʃI�u�W�F�N�g�̊J��
	delete pObjectScreen_;
	pObjectScreen_ = nullptr;

	// 3D�|���S���̊J��
	delete pPolygon3D_;
	pPolygon3D_ = nullptr;

	// 2D�|���S���̊J��
	delete pPolygon2D_;
	pPolygon2D_ = nullptr;

	// �G�t�F�N�g�p�����[�^�̊J��
	delete pEffectParameter_;
	pEffectParameter_ = nullptr;

	// �G�t�F�N�g�Ǘ��N���X�̊J��
	delete pEffect_;
	pEffect_ = nullptr;

	// ���f���Ǘ��N���X�̊J��
	delete pModel_;
	pModel_ = nullptr;

	// �e�N�X�`���Ǘ��N���X�̊J��
	delete pTexture_;
	pTexture_ = nullptr;

	// �X�V�Ǘ��N���X�̏I��
	delete pUpdate_;
	pUpdate_ = nullptr;

	// �`��\���N���X�̏I��
#ifdef _DEBUG
	DebugProc::Finalize();
#endif

	// �`��Ǘ��N���X�̊J��
	delete pDraw_;
	pDraw_ = nullptr;

	// �p�X�N���X�̔j��
	delete[] pRenderPass_;
	pRenderPass_ = nullptr;

	//	���z�R���g���[���Ǘ��N���X�̉��
	delete pVirtualController_;
	pVirtualController_ = nullptr;

	// �Q�[���p�b�h���̓N���X�̊J��
	delete pPad_;
	pPad_ = nullptr;

	// �}�E�X���̓N���X�̊J��
	delete pMouse_;
	pMouse_ = nullptr;

	// �L�[�{�[�h���̓N���X�̊J��
	delete pKeyboard_;
	pKeyboard_ = nullptr;

	// DirectInput�I�u�W�F�N�g�̊J��
	delete pDirectInput_;
	pDirectInput_ = nullptr;

	//	wii�����R�����̓N���X�̉��
	delete pWiiController_;
	pWiiController_ = nullptr;

	// �t�F�[�h�N���X�̊J��
	delete pFade_;
	pFade_ = nullptr;

	// Direct3D�f�o�C�X�̊J��
	delete pDevice_;
	pDevice_ = nullptr;

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Manager::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// �N���X�����̏�����
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : HINSTANCE instanceHandle			: �C���X�^���X�n���h��
// Arg    : int typeShow						: �\���̎��
//==============================================================================
int ManagerMain::Reinitialize( HINSTANCE instanceHandle, int typeShow )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( instanceHandle, typeShow );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerMain* pOut					: �R�s�[��A�h���X
//==============================================================================
int ManagerMain::Copy( ManagerMain* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerMain::Update( void )
{
	// �G���[�`�F�b�N
	Assert( pScene_ != nullptr, _T( "�V�[���Ǘ��N���X����������Ă��܂���B" ) );

	// FPS�̕\��
#ifdef _DEBUG
	DebugProc::Print( _T( "FPS : %2d\n" ), fpsUpdate_ );
#endif

	// ���͂̍X�V
	//pKeyboard_->Update();
	//pMouse_->Update();
	//pPad_->Update();
	pVirtualController_->update();

	// �t�F�[�h�̍X�V
	pFade_->Update();

	// �V�[���̍X�V
	pScene_->Update();
	if( pScene_->IsEnd() )
	{
		isEnd_ = true;
	}

	// �I�u�W�F�N�g�̍X�V
	pUpdate_->Execute();
}

//==============================================================================
// Brief  : �`�揈��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerMain::Draw( void )
{
	// �G���[�`�F�b�N
	Assert( pDraw_ != nullptr, _T( "�����o�ϐ����s���ł��B" ) );

	// �`�揈��
	pDraw_->Execute();
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerMain::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pScene_ = nullptr;
	pArgument_ = nullptr;
	pDevice_ = nullptr;
	pFade_ = nullptr;
	pEffectParameter_ = nullptr;
	pObjectScreen_ = nullptr;
	pDraw_ = nullptr;
	pUpdate_ = nullptr;
	pRenderPass_ = nullptr;
	pDirectInput_ = nullptr;
	pWiiController_ = nullptr;
	pKeyboard_ = nullptr;
	pMouse_ = nullptr;
	pPad_ = nullptr;
	pVirtualController_ = nullptr;
	pTexture_ = nullptr;
	pModel_ = nullptr;
	pEffect_ = nullptr;
	pPolygon2D_ = nullptr;
	pPolygon3D_ = nullptr;
}
