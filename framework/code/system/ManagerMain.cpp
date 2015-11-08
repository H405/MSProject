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
#include "../framework/develop/DebugMeasure.h"
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
#include "../framework/render/RenderPassParameter.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerMotion.h"
#include "../framework/resource/ManagerSound.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/sound/XAudio.h"
#include "../framework/system/Fade.h"
#include "../framework/system/ManagerDraw.h"
#include "../framework/system/ManagerUpdate.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/ObjectLightEffect.h"
#include "../object/ObjectMerge.h"
#include "../object/ObjectPostEffect.h"
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
	// COM���C�u�����̏�����
	CoInitializeEx( NULL, COINIT_MULTITHREADED );

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

#ifdef _DEBUG
	// �f�o�b�O�p�v���N���X�̏�����
	ManagerDebugMeasure::Initialize();
#endif

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

	// XAudio�C���^�[�t�F�[�X�̐���
	IXAudio2* pXAudio = nullptr;		// XAudio2�C���^�[�t�F�[�X
	pXAudio_ = new XAudio();
	if( pXAudio_ == nullptr )
	{
		return 1;
	}
	result = pXAudio_->Initialize( windowHandle );
	if( result != 0 )
	{
		return result;
	}
	pXAudio = pXAudio_->GetXAudio();

	// �p�X�N���X�̐���
	RenderPassParameter	parameterPass3D;			// 3D�`��p�X�̃p�����[�^
	RenderPassParameter	parameterPassNotLight;		// ���C�e�B���O�Ȃ�3D�`��p�X�̃p�����[�^
	pRenderPass_ = new RenderPass[ GraphicMain::PASS_MAX ];
	if( pRenderPass_ == nullptr )
	{
		return 1;
	}
	parameterPass3D.pFormat_[ GraphicMain::RENDER_PASS_3D_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_3D ].Initialize( pDevice, GraphicMain::RENDER_PASS_3D_MAX, &parameterPass3D );
	if( result != 0 )
	{
		return result;
	}
	parameterPassNotLight.flagClear_ = D3DCLEAR_TARGET;
	parameterPassNotLight.pSurfaceDepth_ = pRenderPass_[ GraphicMain::PASS_3D ].GetSurfaceDepth();
	result = pRenderPass_[ GraphicMain::PASS_3D_NOT_LIGHT ].Initialize( pDevice, GraphicMain::RENDER_PASS_3D_NOT_LIGHT_MAX, &parameterPassNotLight );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_LIGHT_EFFECT ].Initialize( pDevice, GraphicMain::RENDER_PASS_LIGHT_EFFECT_MAX );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_3D_MERGE ].Initialize( pDevice, GraphicMain::RENDER_PASS_3D_MERGE_MAX );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_2D ].Initialize( pDevice, GraphicMain::RENDER_PASS_2D_MAX );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_POST_EFFECT ].Initialize( pDevice, GraphicMain::RENDER_PASS_POST_EFFECT_MAX );
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
	result = pModel_->Initialize( _T( "data/model/" ), _T( "model/" ), 32, pDevice, pTexture_ );
	if( result != 0 )
	{
		return result;
	}

	// ���[�V�����Ǘ��N���X�̐���
	pMotion_ = new ManagerMotion< Motion >();
	if( pMotion_ == nullptr )
	{
		return 1;
	}
	result = pMotion_->Initialize( _T( "data/Motion/" ), 32 );
	if( result != 0 )
	{
		return result;
	}
	pMotion_->Get( _T( "test.motion" ) );

	// �G�t�F�N�g�Ǘ��N���X�̐���
#ifdef _DEBUG
	TCHAR	pPathEffect[] = _T( "code/effect/" );
#else
	TCHAR	pPathEffect[] = _T( "data/effect/" );
#endif
	pEffect_ = new ManagerEffect< Effect >();
	if( pEffect_ == nullptr )
	{
		return 1;
	}
	result = pEffect_->Initialize( pPathEffect, 32, pDevice );
	if( result != 0 )
	{
		return result;
	}

	// �T�E���h�Ǘ��N���X�̐���
	pSound_ = new ManagerSound< Sound >();
	if( pSound_ == nullptr )
	{
		return 1;
	}
	result = pSound_->Initialize( _T( "data/sound/" ), 32, pXAudio );
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

	// ���C�e�B���O�I�u�W�F�N�g�̐���
	Effect*	ppEffectLightEffect[ GraphicMain::LIGHT_POINT_MAX + 1 ];		// ���C�e�B���O�G�t�F�N�g
	TCHAR	pNameFileEffectLight[ _MAX_PATH ];								// ���C�e�B���O�G�t�F�N�g�t�@�C����
	pObjectLightEffect_ = new ObjectLightEffect();
	if( pObjectLightEffect_ == nullptr )
	{
		return 1;
	}
	result = pObjectLightEffect_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	for( int counterEffect = 0; counterEffect <= GraphicMain::LIGHT_POINT_MAX; ++counterEffect )
	{
		_stprintf_s( pNameFileEffectLight, _MAX_PATH, _T( "LightEffect_%02d.fx" ), counterEffect );
		ppEffectLightEffect[ counterEffect ] = pEffect_->Get( pNameFileEffectLight );
	}
	result = pObjectLightEffect_->CreateGraphic( 0, pEffectParameter_, ppEffectLightEffect,
		pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_DIFFUSE ),
		pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_SPECULAR ),
		pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_NORMAL ),
		pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_DEPTH ) );
	if( result != 0 )
	{
		return result;
	}
	pObjectLightEffect_->SetPositionY( 1.0f );

	// ����3D�`��I�u�W�F�N�g�̐���
	Effect*	pEffectMerge = nullptr;		// ���C�e�B���O�G�t�F�N�g
	pObjectMerge_ = new ObjectMerge();
	if( pObjectMerge_ == nullptr )
	{
		return 1;
	}
	result = pObjectMerge_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	pEffectMerge = pEffect_->Get( _T( "Merge.fx" ) );
	result = pObjectMerge_->CreateGraphic( 0, pEffectParameter_, pEffectMerge,
		pRenderPass_[ GraphicMain::PASS_LIGHT_EFFECT ].GetTexture( GraphicMain::RENDER_PASS_LIGHT_EFFECT_COLOR ),
		pRenderPass_[ GraphicMain::PASS_3D_NOT_LIGHT ].GetTexture( GraphicMain::RENDER_PASS_3D_NOT_LIGHT_COLOR ),
		pRenderPass_[ GraphicMain::PASS_3D_NOT_LIGHT ].GetTexture( GraphicMain::RENDER_PASS_3D_NOT_LIGHT_MASK ),
		pRenderPass_[ GraphicMain::PASS_3D_NOT_LIGHT ].GetTexture( GraphicMain::RENDER_PASS_3D_NOT_LIGHT_ADD ) );
	if( result != 0 )
	{
		return result;
	}
	pObjectMerge_->SetPositionY( 1.0f );

	// �|�X�g�G�t�F�N�g�I�u�W�F�N�g�̐���
	Effect*	pEffectPostEffect = nullptr;		// �|�X�g�G�t�F�N�g
	pObjectPostEffect_ = new ObjectPostEffect();
	if( pObjectPostEffect_ == nullptr )
	{
		return 1;
	}
	result = pObjectPostEffect_->Initialize( 0, pFade_ );
	if( result != 0 )
	{
		return result;
	}
	pEffectPostEffect = pEffect_->Get( _T( "PostEffect.fx" ) );
	result = pObjectPostEffect_->CreateGraphic( 0, pEffectParameter_, pEffectPostEffect,
		pRenderPass_[ GraphicMain::PASS_3D_MERGE ].GetTexture( GraphicMain::RENDER_PASS_3D_MERGE_COLOR ),
		pRenderPass_[ GraphicMain::PASS_2D ].GetTexture( GraphicMain::RENDER_PASS_2D_COLOR ),
		pRenderPass_[ GraphicMain::PASS_2D ].GetTexture( GraphicMain::RENDER_PASS_2D_MASK ) );
	if( result != 0 )
	{
		return result;
	}
	pObjectPostEffect_->SetPositionY( 1.0f );

	// �V�[�������N���X�̐���
	pArgument_ = new SceneArgumentMain();
	if( pArgument_ == nullptr )
	{
		return 1;
	}
	pArgument_->pWindow_ = pWindow_;
	pArgument_->pDevice_ = pDevice;
	pArgument_->pFade_ = pFade_;
	pArgument_->pEffectParameter_ = pEffectParameter_;
	pArgument_->pWiiController_ = pWiiController_;
	pArgument_->pKeyboard_ = pKeyboard_;
	pArgument_->pMouse_ = pMouse_;
	pArgument_->pPad_ = pPad_;
	pArgument_->pVirtualController_ = pVirtualController_;
	pArgument_->pTexture_ = pTexture_;
	pArgument_->pModel_ = pModel_;
	pArgument_->pMotion_ = pMotion_;
	pArgument_->pEffect_ = pEffect_;
	pArgument_->pSound_ = pSound_;

	// �V�[���Ǘ��N���X�̐���
	pScene_ = new ManagerSceneMain();
	if( pScene_ == nullptr )
	{
		return 1;
	}
#ifdef _DEBUG
	result = pScene_->Initialize( ManagerSceneMain::TYPE_SPLASH, pArgument_ );
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

	// �|�X�g�G�t�F�N�g�I�u�W�F�N�g�̊J��
	delete pObjectPostEffect_;
	pObjectPostEffect_ = nullptr;

	// ����3D�`��I�u�W�F�N�g�̊J��
	delete pObjectMerge_;
	pObjectMerge_ = nullptr;

	// ���C�e�B���O�I�u�W�F�N�g�̊J��
	delete pObjectLightEffect_;
	pObjectLightEffect_ = nullptr;

	// 3D�|���S���̊J��
	delete pPolygon3D_;
	pPolygon3D_ = nullptr;

	// 2D�|���S���̊J��
	delete pPolygon2D_;
	pPolygon2D_ = nullptr;

	// �G�t�F�N�g�p�����[�^�̊J��
	delete pEffectParameter_;
	pEffectParameter_ = nullptr;

	// �T�E���h�Ǘ��N���X�̊J��
	delete pSound_;
	pSound_ = nullptr;

	// �G�t�F�N�g�Ǘ��N���X�̊J��
	delete pEffect_;
	pEffect_ = nullptr;

	// ���[�V�����Ǘ��N���X�̊J��
	delete pMotion_;
	pMotion_ = nullptr;

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

	// XAudio2�C���^�[�t�F�X�̊J��
	delete pXAudio_;
	pXAudio_ = nullptr;

	// Direct3D�f�o�C�X�̊J��
	delete pDevice_;
	pDevice_ = nullptr;

#ifdef _DEBUG
	// �f�o�b�O�p�v���N���X�̏I��
	ManagerDebugMeasure::Finalize();
#endif

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Manager::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// COM���C�u�����̏I������
	CoUninitialize();

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
	{
		MeasureTime( _T( "�V�[���̍X�V" ) );
		pScene_->Update();
	}
	if( pScene_->IsEnd() )
	{
		isEnd_ = true;
	}

	if( pScene_->IsUpdate() )
	{
		// �I�u�W�F�N�g�̍X�V
		pUpdate_->Execute();
	}

#ifdef _DEBUG
	// �f�o�b�O�p�v���N���X�̍X�V
	ManagerDebugMeasure::Update();
#endif
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
	{
		MeasureTime( _T( "�`��" ) );
		pDraw_->Execute();
	}
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
	pXAudio_ = nullptr;
	pFade_ = nullptr;
	pEffectParameter_ = nullptr;
	pObjectLightEffect_ = nullptr;
	pObjectMerge_ = nullptr;
	pObjectPostEffect_ = nullptr;
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
	pMotion_ = nullptr;
	pEffect_ = nullptr;
	pPolygon2D_ = nullptr;
	pPolygon3D_ = nullptr;
}
