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
// Arg    : IDirect3DTexture9* pTextureLightPoint	: �_�����̐[�x���e�N�X�`��
//==============================================================================
int DrawerShadow::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint )
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
	pTextureLightPoint_ = pTextureLightPoint;
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
// Arg    : IDirect3DTexture9* pTextureLightPoint	: �_�����̐[�x���e�N�X�`��
//==============================================================================
int DrawerShadow::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pParameter, pEffect, pPolygon, pTextureDepth, pTextureLightNear, pTextureLightFar, pTextureLightPoint );
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

	// �_�����̕ϊ��s��
	const Camera*	pCameraShadowPoint = nullptr;		// �J����
	pCameraShadowPoint = pEffectParameter_->GetCamera( GraphicMain::CAMERA_SHADOW_POINT );
	pRenderMatrix = pCameraShadowPoint->GetRenderMatrix();
	pRenderMatrix->GetMatrixView( &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW_LIGHT_POINT, matrixView );

	// �_�����̃e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH_LIGHT_POINT, pTextureLightPoint_ );

	// �_�����̃t�@�[�N���b�v��
	pEffect_->SetFloat( PARAMETER_CLIP_FAR_LIGHT_POINT, pCameraShadowPoint->GetClipFar() );

	// �_�����̌�����
	const LightPoint*	pLightPoint = nullptr;		// �|�C���g���C�g
	D3DXVECTOR3			attenuationLightPoint;		// �_�����̌�����
	if( pEffectParameter_->GetCountLightPoint() > 0 )
	{
		pLightPoint = pEffectParameter_->GetLightPoint( 0 );
		pLightPoint->GetAttenuation( &attenuationLightPoint );
	}
	else
	{
		attenuationLightPoint.x = attenuationLightPoint.y = attenuationLightPoint.z = 10000.0f;
	}
	pEffect_->SetFloatArray( PARAMETER_ATTENUATION_LIGHT_POINT, &attenuationLightPoint.x, 3 );

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
	pTextureLightPoint_ = nullptr;
	pPolygon_ = nullptr;
}
