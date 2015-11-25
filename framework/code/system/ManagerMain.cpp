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
#include "../framework/camera/CameraObject.h"
#include "../framework/camera/CameraStateDebug.h"
#include "../framework/camera/ManagerCamera.h"
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
#include "../framework/light/ManagerLight.h"
#include "../framework/object/Object.h"
#include "../framework/polygon/Polygon2D.h"
#include "../framework/polygon/Polygon3D.h"
#include "../framework/polygon/PolygonBillboard.h"
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
#include "../object/ObjectBlur.h"
#include "../object/ObjectLightEffect.h"
#include "../object/ObjectLightReflect.h"
#include "../object/ObjectMerge.h"
#include "../object/ObjectPostEffect.h"
#include "../object/ObjectShadow.h"
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
	int		widthWindow;		// �E�B���h�E��
	int		heightWindow;		// �E�B���h�E����
	pWindow_ = new WindowMain();
	if( pWindow_ == nullptr )
	{
		return 1;
	}
	result = pWindow_->Initialize( instanceHandle, typeShow, 1280, 720, _T( "�Ԓ�����" ), _T( "WindowClass" ) );
	if( result != 0 )
	{
		return result;
	}
	windowHandle = pWindow_->GetWindowHandle();
	widthWindow = pWindow_->GetWidth();
	heightWindow = pWindow_->GetHeight();

#ifdef _DEVELOP
	// �f�o�b�O�p�v���N���X�̏�����
	ManagerDebugMeasure::Initialize();
#endif

	// Direct3D�f�o�C�X�̐���
	IDirect3DDevice9*	pDevice = nullptr;			// Direct3D�f�o�C�X
	bool				isWindowMode = false;		// �E�B���h�E���[�h�t���O
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

	// ���C�g�Ǘ��N���X�̐���
	pLight_ = new ManagerLight();
	if( pLight_ == nullptr )
	{
		return 1;
	}
	result = pLight_->Initialize( GraphicMain::LIGHT_DIRECTIONAL_MAX, GraphicMain::LIGHT_POINT_MAX );
	if( result != 0 )
	{
		return result;
	}
	
	// �J�����Ǘ��N���X�̐���
	pCamera_ = new ManagerCamera();
	if( pCamera_ == nullptr )
	{
		return 1;
	}
	result = pCamera_->Initialize( GraphicMain::CAMERA_MAX );
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
#ifdef _DEVELOP
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
	RenderPassParameter	parameterPassWaveData;			// �g���`��p�X�̃p�����[�^
	RenderPassParameter	parameterPass3D;				// 3D�`��p�X�̃p�����[�^
	RenderPassParameter	parameterPassDepthShadow;		// �e�p�[�x�p�X�̃p�����[�^
	RenderPassParameter	parameterPassShadow;			// �e�p�X�̃p�����[�^
	RenderPassParameter	parameterPassReflect;			// ���˃p�X�̃p�����[�^
	RenderPassParameter	parameterPassReflectLight;		// ���˃��C�e�B���O�p�X�̃p�����[�^
	RenderPassParameter	parameterPassReflectAdd;		// ���ˉ��Z�����p�X�̃p�����[�^
	RenderPassParameter	parameterPassWater;				// ���`��p�X�̃p�����[�^
	RenderPassParameter	parameterPassNotLight;			// ���C�e�B���O�Ȃ�3D�`��p�X�̃p�����[�^
	RenderPassParameter	parameterPassLightEffect;		// ���C�e�B���O�p�X�̃p�����[�^
	RenderPassParameter	parameterPassMerge;				// ����3D�`��p�X�̃p�����[�^
	RenderPassParameter	parameterPassBlur;				// �u���[�p�X�̃p�����[�^
	pRenderPass_ = new RenderPass[ GraphicMain::PASS_MAX ];
	if( pRenderPass_ == nullptr )
	{
		return 1;
	}
	parameterPassWaveData.width_ = 256;
	parameterPassWaveData.height_ = 256;
	parameterPassWaveData.pFormat_[ GraphicMain::RENDER_PASS_WAVE_DATA_HEIGHT ] = D3DFMT_A16B16G16R16F;
	parameterPassWaveData.pCountMultiple_[ GraphicMain::RENDER_PASS_WAVE_DATA_HEIGHT ] = 2;
	result = pRenderPass_[ GraphicMain::PASS_WAVE_DATA ].Initialize( pDevice, GraphicMain::RENDER_PASS_WAVE_DATA_MAX, &parameterPassWaveData );
	if( result != 0 )
	{
		return result;
	}
	parameterPass3D.pFormat_[ GraphicMain::RENDER_PASS_3D_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_3D ].Initialize( pDevice, GraphicMain::RENDER_PASS_3D_MAX, &parameterPass3D );
	if( result != 0 )
	{
		return result;
	}
	parameterPassDepthShadow.pFormat_[ GraphicMain::RENDER_PASS_DEPTH_SHADOW_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_DEPTH_SHADOW ].Initialize( pDevice, GraphicMain::RENDER_PASS_DEPTH_SHADOW_MAX, &parameterPassDepthShadow );
	if( result != 0 )
	{
		return result;
	}
	parameterPassShadow.pFormat_[ GraphicMain::RENDER_PASS_SHADOW_COLOR ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_SHADOW ].Initialize( pDevice, GraphicMain::RENDER_PASS_SHADOW_MAX, &parameterPassShadow );
	if( result != 0 )
	{
		return result;
	}
	parameterPassReflect.width_ = widthWindow / 4;
	parameterPassReflect.height_ = heightWindow / 4;
	parameterPassReflect.pFormat_[ GraphicMain::RENDER_PASS_REFLECT_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_REFLECT ].Initialize( pDevice, GraphicMain::RENDER_PASS_REFLECT_MAX, &parameterPassReflect );
	if( result != 0 )
	{
		return result;
	}
	parameterPassReflectLight.width_ = widthWindow / 4;
	parameterPassReflectLight.height_ = heightWindow / 4;
	result = pRenderPass_[ GraphicMain::PASS_LIGHT_REFLECT ].Initialize( pDevice, GraphicMain::RENDER_PASS_LIGHT_REFLECT_MAX, &parameterPassReflectLight );
	if( result != 0 )
	{
		return result;
	}
	parameterPassReflectAdd.width_ = widthWindow / 4;
	parameterPassReflectAdd.height_ = heightWindow / 4;
	parameterPassReflectAdd.flagClear_ = D3DCLEAR_TARGET;
	parameterPassReflectAdd.pSurfaceDepth_ = pRenderPass_[ GraphicMain::PASS_REFLECT ].GetSurfaceDepth();
	result = pRenderPass_[ GraphicMain::PASS_REFLECT_NOT_LIGHT ].Initialize( pDevice, GraphicMain::RENDER_PASS_REFLECT_NOT_LIGHT_MAX, &parameterPassReflectAdd );
	if( result != 0 )
	{
		return result;
	}
	parameterPassWater.flagClear_ = D3DCLEAR_TARGET;
	parameterPassWater.pSurfaceDepth_ = pRenderPass_[ GraphicMain::PASS_3D ].GetSurfaceDepth();
	parameterPassWater.pFormat_[ GraphicMain::RENDER_PASS_WATER_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_WATER ].Initialize( pDevice, GraphicMain::RENDER_PASS_WATER_MAX, &parameterPassWater );
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
	parameterPassLightEffect.pFormat_[ GraphicMain::RENDER_PASS_LIGHT_EFFECT_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_LIGHT_EFFECT ].Initialize( pDevice, GraphicMain::RENDER_PASS_LIGHT_EFFECT_MAX, &parameterPassLightEffect );
	if( result != 0 )
	{
		return result;
	}
	parameterPassMerge.pFormat_[ GraphicMain::RENDER_PASS_3D_MERGE_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_3D_MERGE ].Initialize( pDevice, GraphicMain::RENDER_PASS_3D_MERGE_MAX, &parameterPassMerge );
	if( result != 0 )
	{
		return result;
	}
	parameterPassBlur.width_ = widthWindow / 4;
	parameterPassBlur.height_ = heightWindow / 4;
	result = pRenderPass_[ GraphicMain::PASS_BLUR_X ].Initialize( pDevice, GraphicMain::RENDER_PASS_BLUR_X_MAX, &parameterPassBlur );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_BLUR_Y ].Initialize( pDevice, GraphicMain::RENDER_PASS_BLUR_Y_MAX, &parameterPassBlur );
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
	result = pDraw_->Initialize( 1024, pDevice, GraphicMain::PASS_MAX, pRenderPass_ );
	if( result != 0 )
	{
		return result;
	}
	Graphic::SetManagerDraw( pDraw_ );

	// �`��\���N���X�̏�����
#ifdef _DEVELOP
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
	result = pUpdate_->Initialize( 1024 );
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
	result = pTexture_->Initialize( _T( "data/texture/" ), 64, pDevice );
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
	result = pEffect_->Initialize( pPathEffect, 64, pDevice );
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
	pEffectParameter_->SetWidthScreen( static_cast< float >( widthWindow ) );
	pEffectParameter_->SetHeightScreen( static_cast< float >( heightWindow ) );

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

	// �r���{�[�h�|���S���̐���
	pPolygonBillboard_ = new PolygonBillboard();
	if( pPolygonBillboard_ == nullptr )
	{
		return 1;
	}
	result = pPolygonBillboard_->Initialize( pDevice );
	if( result != 0 )
	{
		return result;
	}
	GraphicMain::SetPolygonBillboard( pPolygonBillboard_ );

	// �e�I�u�W�F�N�g�̐���
	Effect*	pEffectShadow = nullptr;		// �e�G�t�F�N�g
	pObjectShadow_ = new ObjectShadow();
	if( pObjectShadow_ == nullptr )
	{
		return 1;
	}
	result = pObjectShadow_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	pEffectShadow = pEffect_->Get( _T( "Shadow.fx" ) );
	result = pObjectShadow_->CreateGraphic( 0, pEffectParameter_, pEffectShadow,
		pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_DEPTH ),
		pRenderPass_[ GraphicMain::PASS_DEPTH_SHADOW ].GetTexture( GraphicMain::RENDER_PASS_DEPTH_SHADOW_DEPTH ) );
	if( result != 0 )
	{
		return result;
	}

	// ���˃��C�e�B���O�I�u�W�F�N�g�̐���
	Effect*	ppEffectLightReflect[ GraphicMain::LIGHT_POINT_MAX + 1 ];		// ���C�e�B���O�G�t�F�N�g
	TCHAR	pNameFileEffectLight[ _MAX_PATH ];								// ���C�e�B���O�G�t�F�N�g�t�@�C����
	pObjectLightReflect_ = new ObjectLightReflect();
	if( pObjectLightReflect_ == nullptr )
	{
		return 1;
	}
	result = pObjectLightReflect_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	for( int counterEffect = 0; counterEffect <= GraphicMain::LIGHT_POINT_MAX; ++counterEffect )
	{
		_stprintf_s( pNameFileEffectLight, _MAX_PATH, _T( "LightReflect_%02d.fx" ), counterEffect );
		ppEffectLightReflect[ counterEffect ] = pEffect_->Get( pNameFileEffectLight );
	}
	result = pObjectLightReflect_->CreateGraphic( 0, pEffectParameter_, ppEffectLightReflect,
		pRenderPass_[ GraphicMain::PASS_REFLECT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_DIFFUSE ),
		pRenderPass_[ GraphicMain::PASS_REFLECT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_SPECULAR ),
		pRenderPass_[ GraphicMain::PASS_REFLECT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_NORMAL ),
		pRenderPass_[ GraphicMain::PASS_REFLECT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_DEPTH ) );
	if( result != 0 )
	{
		return result;
	}

	// ���C�e�B���O�I�u�W�F�N�g�̐���
	Effect*	ppEffectLightEffect[ GraphicMain::LIGHT_POINT_MAX + 1 ];		// ���C�e�B���O�G�t�F�N�g
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
		pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_DEPTH ),
		pRenderPass_[ GraphicMain::PASS_WATER ].GetTexture( GraphicMain::RENDER_PASS_WATER_DIFFUSE ),
		pRenderPass_[ GraphicMain::PASS_WATER ].GetTexture( GraphicMain::RENDER_PASS_WATER_SPECULAR ),
		pRenderPass_[ GraphicMain::PASS_WATER ].GetTexture( GraphicMain::RENDER_PASS_WATER_NORMAL ),
		pRenderPass_[ GraphicMain::PASS_WATER ].GetTexture( GraphicMain::RENDER_PASS_WATER_DEPTH ),
		pRenderPass_[ GraphicMain::PASS_SHADOW ].GetTexture( GraphicMain::RENDER_PASS_SHADOW_COLOR ) );
	if( result != 0 )
	{
		return result;
	}

	// ����3D�`��I�u�W�F�N�g�̐���
	Effect*	pEffectMerge = nullptr;		// ����3D�`��G�t�F�N�g
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
		pRenderPass_[ GraphicMain::PASS_3D_NOT_LIGHT ].GetTexture( GraphicMain::RENDER_PASS_3D_NOT_LIGHT_ADD ),
		pRenderPass_[ GraphicMain::PASS_LIGHT_EFFECT ].GetTexture( GraphicMain::RENDER_PASS_LIGHT_EFFECT_DEPTH ) );
	if( result != 0 )
	{
		return result;
	}

	// �u���[�I�u�W�F�N�g�̐���
	Effect*	pBlurX = nullptr;		// X�����u���[�G�t�F�N�g
	Effect*	pBlurY = nullptr;		// Y�����u���[�G�t�F�N�g
	pObjectBlur_ = new ObjectBlur();
	if( pObjectBlur_ == nullptr )
	{
		return 1;
	}
	result = pObjectBlur_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	pBlurX = pEffect_->Get( _T( "BlurX.fx" ) );
	pBlurY = pEffect_->Get( _T( "BlurY.fx" ) );
	result = pObjectBlur_->CreateGraphic( 0, pEffectParameter_, pBlurX, pBlurY,
		pRenderPass_[ GraphicMain::PASS_3D_MERGE ].GetTexture( GraphicMain::RENDER_PASS_3D_MERGE_COLOR ),
		pRenderPass_[ GraphicMain::PASS_BLUR_X ].GetTexture( GraphicMain::RENDER_PASS_BLUR_X_COLOR ) );
	if( result != 0 )
	{
		return result;
	}

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
		pRenderPass_[ GraphicMain::PASS_BLUR_Y ].GetTexture( GraphicMain::RENDER_PASS_BLUR_Y_LUMINANCE ),
		pRenderPass_[ GraphicMain::PASS_BLUR_Y ].GetTexture( GraphicMain::RENDER_PASS_BLUR_Y_COLOR ),
		pRenderPass_[ GraphicMain::PASS_3D_MERGE ].GetTexture( GraphicMain::RENDER_PASS_3D_MERGE_DEPTH ),
		pRenderPass_[ GraphicMain::PASS_2D ].GetTexture( GraphicMain::RENDER_PASS_2D_COLOR ),
		pRenderPass_[ GraphicMain::PASS_2D ].GetTexture( GraphicMain::RENDER_PASS_2D_MASK ) );
	if( result != 0 )
	{
		return result;
	}

	// �V�[�������N���X�̐���
	pArgument_ = new SceneArgumentMain();
	if( pArgument_ == nullptr )
	{
		return 1;
	}
	pArgument_->pWindow_ = pWindow_;
	pArgument_->pDevice_ = pDevice;
	pArgument_->pFade_ = pFade_;
	pArgument_->pLight_ = pLight_;
	pArgument_->pCamera_ = pCamera_;
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
	pArgument_->pDraw_ = pDraw_;
	pArgument_->pUpdate_ = pUpdate_;
	pArgument_->pTextureHeightWave0_ = pRenderPass_[ GraphicMain::PASS_WAVE_DATA ].GetTexture( GraphicMain::RENDER_PASS_WAVE_DATA_HEIGHT, 0 );
	pArgument_->pTextureHeightWave1_ = pRenderPass_[ GraphicMain::PASS_WAVE_DATA ].GetTexture( GraphicMain::RENDER_PASS_WAVE_DATA_HEIGHT, 1 );
	pArgument_->pTextureNormalWave_ = pRenderPass_[ GraphicMain::PASS_WAVE_DATA ].GetTexture( GraphicMain::RENDER_PASS_WAVE_DATA_NORMAL );
	pArgument_->pTextureReflect_ = pRenderPass_[ GraphicMain::PASS_LIGHT_REFLECT ].GetTexture( GraphicMain::RENDER_PASS_LIGHT_REFLECT_COLOR );
	pArgument_->pTextureReflectNotLight_ = pRenderPass_[ GraphicMain::PASS_REFLECT_NOT_LIGHT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_NOT_LIGHT_COLOR );
	pArgument_->pTextureReflectAdd_ = pRenderPass_[ GraphicMain::PASS_REFLECT_NOT_LIGHT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_NOT_LIGHT_ADD );
	pArgument_->pTexture3D_ = pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_DIFFUSE );
	pArgument_->pTextureDepth_ = pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_DEPTH );
	pArgument_->pTextureTest_ = pRenderPass_[ GraphicMain::PASS_SHADOW ].GetTexture( GraphicMain::RENDER_PASS_SHADOW_COLOR );

	// �V�[���Ǘ��N���X�̐���
	pScene_ = new ManagerSceneMain();
	if( pScene_ == nullptr )
	{
		return 1;
	}
#ifdef _DEBUG
	result = pScene_->Initialize( ManagerSceneMain::TYPE_GAME, pArgument_ );
#else
	result = pScene_->Initialize( ManagerSceneMain::TYPE_TITLE, pArgument_ );
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

	// �e�I�u�W�F�N�g�̊J��
	delete pObjectShadow_;
	pObjectShadow_ = nullptr;

	// �|�X�g�G�t�F�N�g�I�u�W�F�N�g�̊J��
	delete pObjectPostEffect_;
	pObjectPostEffect_ = nullptr;

	// �u���[�I�u�W�F�N�g�̊J��
	delete pObjectBlur_;
	pObjectBlur_ = nullptr;

	// ����3D�`��I�u�W�F�N�g�̊J��
	delete pObjectMerge_;
	pObjectMerge_ = nullptr;

	// ���C�e�B���O�I�u�W�F�N�g�̊J��
	delete pObjectLightEffect_;
	pObjectLightEffect_ = nullptr;

	// ���˃��C�e�B���O�I�u�W�F�N�g�̊J��
	delete pObjectLightReflect_;
	pObjectLightReflect_ = nullptr;

	// �r���{�[�h�|���S���̊J��
	delete pPolygonBillboard_;
	pPolygonBillboard_ = nullptr;

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
#ifdef _DEVELOP
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

	// �J�����Ǘ��N���X�̊J��
	delete pCamera_;
	pCamera_ = nullptr;

	// ���C�g�Ǘ��N���X�̊J��
	delete pLight_;
	pLight_ = nullptr;

	// �t�F�[�h�N���X�̊J��
	delete pFade_;
	pFade_ = nullptr;

	// XAudio2�C���^�[�t�F�X�̊J��
	delete pXAudio_;
	pXAudio_ = nullptr;

	// Direct3D�f�o�C�X�̊J��
	delete pDevice_;
	pDevice_ = nullptr;

#ifdef _DEVELOP
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

#ifdef _DEVELOP
	// FPS�̕\��
	DebugProc::Print( _T( "FPS : %2d\n" ), fpsUpdate_ );

	// �f�o�b�O�p�v���N���X�̍X�V
	ManagerDebugMeasure::Update();
#endif

	// ���͂̍X�V
	//pKeyboard_->Update();
	//pMouse_->Update();
	//pPad_->Update();
	pVirtualController_->update();

	// �f�o�b�O�|�[�Y
#ifdef _DEVELOP
	if(pKeyboard_->IsTrigger(DIK_F2))
	{
		pDraw_->screenShotON();
	}
	if( pKeyboard_->IsTrigger( DIK_F11 ) )
	{
		isPausing_ = !isPausing_;
	}
	if( !pKeyboard_->IsTrigger( DIK_F12 ) && isPausing_ )
	{
		return;
	}
	if(isPausing_)
	{
		DebugProc::Print( _T( "�|�[�Y�����FF11\n�P�R�}�i�߂�F12\n" ));
	}
#endif

	// �t�F�[�h�̍X�V
	pFade_->Update();

	// �V�[���̍X�V
	{ MeasureTime( _T( "�V�[���̍X�V" ) );
		pScene_->Update();
	}
	if( pScene_->IsEnd() )
	{
		isEnd_ = true;
	}

	// �I�u�W�F�N�g�̍X�V
	if( pUpdate_->IsEnable() )
	{
		pUpdate_->Execute();
	}

	// �G�t�F�N�g�p�����[�^�Ƀ��C�g��ݒ�
	int		countLightDirection;		// �f�B���N�V���i�����C�g��
	int		countLightPoint;			// �|�C���g���C�g��
	countLightDirection = pLight_->GetCountLightDirection();
	countLightPoint = pLight_->GetCountLightPoint();
	pEffectParameter_->SetCountLightDirection( countLightDirection );
	for( int counterLight = 0; counterLight < countLightDirection; ++counterLight )
	{
		pEffectParameter_->SetLightDirection( counterLight, pLight_->GetLightDirectionEnable( counterLight ) );
	}
	pEffectParameter_->SetCountLightPoint( countLightPoint );
	for( int counterLight = 0; counterLight < countLightPoint; ++counterLight )
	{
		pEffectParameter_->SetLightPoint( counterLight, pLight_->GetLightPointEnable( counterLight ) );
	}

	// �J�����̍X�V
	pCamera_->Update();
	for( int counterCamera = 0; counterCamera < GraphicMain::CAMERA_MAX; ++ counterCamera )
	{
		pEffectParameter_->SetCamera( counterCamera, pCamera_->GetCamera( counterCamera ) );
	}
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
// Brief  : �X�N���[���V���b�g�B�e
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerMain::screenShotON()
{
	pDraw_->screenShotON();
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
	pLight_ = nullptr;
	pCamera_ = nullptr;
	pEffectParameter_ = nullptr;
	pObjectBlur_ = nullptr;
	pObjectLightEffect_ = nullptr;
	pObjectLightReflect_ = nullptr;
	pObjectMerge_ = nullptr;
	pObjectPostEffect_ = nullptr;
	pObjectShadow_ = nullptr;
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
	pPolygonBillboard_ = nullptr;

#ifdef _DEVELOP
	isPausing_ = false;
#endif
}
