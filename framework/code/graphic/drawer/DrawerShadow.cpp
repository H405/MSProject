//==============================================================================
//
// File   : DrawerShadow.cpp
// Brief  : ���C�g�`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerShadow.h"
#include "../graphic/GraphicMain.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/develop/DebugMeasure.h"
#include "../../framework/graphic/Material.h"
#include "../../framework/light/LightDirection.h"
#include "../../framework/light/LightPoint.h"
#include "../../framework/render/RenderMatrix.h"
#include "../../framework/resource/Effect.h"
#include "../../framework/polygon/Polygon2D.h"
#include "../../system/EffectParameter.h"

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
DrawerShadow::DrawerShadow( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerShadow::~DrawerShadow( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : Polygon2D* pPolygon					: 2D�|���S��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightNear	: ���s����(��)�̐[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightFar		: ���s����(��)�̐[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightPoint0	: �_����0�̐[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightPoint1	: �_����1�̐[�x���e�N�X�`��
//==============================================================================
int DrawerShadow::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar,
	IDirect3DTexture9* pTextureLightPoint0, IDirect3DTexture9* pTextureLightPoint1 )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Drawer::Initialize();
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pEffectParameter_ = pParameter;
	pEffect_ = pEffect;
	pTextureDepth_ = pTextureDepth;
	pTextureLightNear_ = pTextureLightNear;
	pTextureLightFar_ = pTextureLightFar;
	pTextureLightPoint0_ = pTextureLightPoint0;
	pTextureLightPoint1_ = pTextureLightPoint1;
	pPolygon_ = pPolygon;

	// �n���h���̓ǂݍ���
	result = pEffect_->LoadHandle( 1, PARAMETER_MAX );
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
int DrawerShadow::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Drawer::Finalize();
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
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : Polygon2D* pPolygon					: 2D�|���S��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightNear	: ���s����(��)�̐[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightFar		: ���s����(��)�̐[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightPoint0	: �_����0�̐[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightPoint1	: �_����1�̐[�x���e�N�X�`��
//==============================================================================
int DrawerShadow::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar,
	IDirect3DTexture9* pTextureLightPoint0, IDirect3DTexture9* pTextureLightPoint1 )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pParameter, pEffect, pPolygon, pTextureDepth, pTextureLightNear, pTextureLightFar, pTextureLightPoint0, pTextureLightPoint1 );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerShadow* pOut					: �R�s�[��A�h���X
//==============================================================================
int DrawerShadow::Copy( DrawerShadow* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Drawer::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`�揈��
// Return : void								: �Ȃ�
// Arg    : const D3DXMATRIX& matrixWorld		: ���[���h�}�g���N�X
//==============================================================================
void DrawerShadow::Draw( const D3DXMATRIX& matrixWorld )
{
	// ���_�V�F�[�_�p�p�����[�^
	float	pOffset[ 2 ];		// �I�t�Z�b�g
	pOffset[ 0 ] = 0.5f / pEffectParameter_->GetWidthScreen();
	pOffset[ 1 ] = 0.5f / pEffectParameter_->GetHeightScreen();
	pEffect_->SetFloatArray( PARAMETER_OFFET_TEXEL, pOffset, 2 );

	// �v���W�F�N�V�����ϊ��t�s��
	const Camera*	pCamera = nullptr;				// �J����
	RenderMatrix*	pRenderMatrix = nullptr;		// �`��ϊ��s��
	D3DXMATRIX		matrixProjectionInverse;		// �v���W�F�N�V�����ϊ��t�s��
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixProjection( &matrixProjectionInverse );
	D3DXMatrixInverse( &matrixProjectionInverse, nullptr, &matrixProjectionInverse );
	pEffect_->SetMatrix( PARAMETER_MATRIX_PROJECTION_INVERSE, matrixProjectionInverse );

	// �r���[�ϊ��t�s��
	D3DXMATRIX	matrixViewInverse;		// �r���[�ϊ��t�s��
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixView( &matrixViewInverse );
	D3DXMatrixInverse( &matrixViewInverse, nullptr, &matrixViewInverse );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW_INVERSE, matrixViewInverse );

	// �[�x�e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH, pTextureDepth_ );

	// ���s�����̒����_
	const Camera*	pCameraShadowNear = nullptr;		// �J����
	D3DXVECTOR3		positionLookAtLight;				// ���s�����̒����_
	pCameraShadowNear = pEffectParameter_->GetCamera( GraphicMain::CAMERA_SHADOW_NEAR );
	pCameraShadowNear->GetPositionLookAt( &positionLookAtLight );
	pEffect_->SetFloatArray( PARAMETER_POSITION_LOOK_AT_LIGHT, &positionLookAtLight.x, 3 );

	// ���s����(��)�̕ϊ��s��
	D3DXMATRIX	matrixViewProjection;		// �r���[�v���W�F�N�V�����ϊ��s��
	D3DXMATRIX	matrixView;					// �r���[�ϊ��s��
	pRenderMatrix = pCameraShadowNear->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );
	pRenderMatrix->GetMatrixView( &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM_LIGHT_NEAR, matrixViewProjection );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW_LIGHT_NEAR, matrixView );

	// ���s����(��)�̃e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH_LIGHT_NEAR, pTextureLightNear_ );

	// ���s����(��)�̃t�@�[�N���b�v��
	pEffect_->SetFloat( PARAMETER_CLIP_FAR_LIGHT_NEAR, pCameraShadowNear->GetClipFar() );

	// ���s����(��)�̕ϊ��s��
	const Camera*	pCameraShadowFar = nullptr;		// �J����
	pCameraShadowFar = pEffectParameter_->GetCamera( GraphicMain::CAMERA_SHADOW_FAR );
	pRenderMatrix = pCameraShadowFar->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );
	pRenderMatrix->GetMatrixView( &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM_LIGHT_FAR, matrixViewProjection );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW_LIGHT_FAR, matrixView );

	// ���s����(��)�̃e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH_LIGHT_FAR, pTextureLightFar_ );

	// ���s����(��)�̃t�@�[�N���b�v��
	pEffect_->SetFloat( PARAMETER_CLIP_FAR_LIGHT_FAR, pCameraShadowFar->GetClipFar() );

	// �_����0�̕ϊ��s��
	const Camera*	pCameraShadowPoint0 = nullptr;		// �J����
	pCameraShadowPoint0 = pEffectParameter_->GetCamera( GraphicMain::CAMERA_SHADOW_POINT_0 );
	pRenderMatrix = pCameraShadowPoint0->GetRenderMatrix();
	pRenderMatrix->GetMatrixView( &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW_LIGHT_POINT_0, matrixView );

	// �_����0�̃e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH_LIGHT_POINT_0, pTextureLightPoint0_ );

	// �_����0�̃t�@�[�N���b�v��
	pEffect_->SetFloat( PARAMETER_CLIP_FAR_LIGHT_POINT_0, pCameraShadowPoint0->GetClipFar() );

	// �_����0�̌�����
	const LightPoint*	pLightPoint0 = nullptr;		// �|�C���g���C�g
	D3DXVECTOR3			attenuationLightPoint0;		// �_�����̌�����
	pLightPoint0 = pEffectParameter_->GetLightPointLightness( 0 );
	if( pLightPoint0 != nullptr )
	{
		pLightPoint0->GetAttenuation( &attenuationLightPoint0 );
	}
	else
	{
		attenuationLightPoint0.x = attenuationLightPoint0.y = attenuationLightPoint0.z = 10000.0f;
	}
	pEffect_->SetFloatArray( PARAMETER_ATTENUATION_LIGHT_POINT_0, &attenuationLightPoint0.x, 3 );

	// �_����1�̕ϊ��s��
	const Camera*	pCameraShadowPoint1 = nullptr;		// �J����
	pCameraShadowPoint1 = pEffectParameter_->GetCamera( GraphicMain::CAMERA_SHADOW_POINT_1 );
	pRenderMatrix = pCameraShadowPoint1->GetRenderMatrix();
	pRenderMatrix->GetMatrixView( &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW_LIGHT_POINT_1, matrixView );

	// �_����1�̃e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH_LIGHT_POINT_1, pTextureLightPoint1_ );

	// �_����1�̃t�@�[�N���b�v��
	pEffect_->SetFloat( PARAMETER_CLIP_FAR_LIGHT_POINT_1, pCameraShadowPoint1->GetClipFar() );

	// �_����1�̌�����
	const LightPoint*	pLightPoint1 = nullptr;		// �|�C���g���C�g
	D3DXVECTOR3			attenuationLightPoint1;		// �_�����̌�����
	pLightPoint1 = pEffectParameter_->GetLightPointLightness( 1 );
	if( pLightPoint1 != nullptr )
	{
		pLightPoint1->GetAttenuation( &attenuationLightPoint1 );
	}
	else
	{
		attenuationLightPoint1.x = attenuationLightPoint1.y = attenuationLightPoint1.z = 10000.0f;
	}
	pEffect_->SetFloatArray( PARAMETER_ATTENUATION_LIGHT_POINT_1, &attenuationLightPoint1.x, 3 );

	// �`��
	pEffect_->Begin( 0 );
	pPolygon_->Draw();
	pEffect_->End();
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerShadow::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTextureDepth_ = nullptr;
	pTextureLightNear_ = nullptr;
	pTextureLightFar_ = nullptr;
	pTextureLightPoint0_ = nullptr;
	pTextureLightPoint1_ = nullptr;
	pPolygon_ = nullptr;
}
