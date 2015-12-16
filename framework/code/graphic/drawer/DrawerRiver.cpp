//==============================================================================
//
// File   : DrawerRiver.cpp
// Brief  : ��`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerRiver.h"
#include "../graphic/GraphicMain.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/graphic/Material.h"
#include "../../framework/render/RenderMatrix.h"
#include "../../framework/resource/Effect.h"
#include "../../framework/resource/Model.h"
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
DrawerRiver::DrawerRiver( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerRiver::~DrawerRiver( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : Model* pModel						: ���f��
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTextureNormal	: �@���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureReflect	: ���˃e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: ���˃��C�e�B���O�Ȃ��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureReflectAdd		: ���ˉ��Z�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
//==============================================================================
int DrawerRiver::Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTextureNormal,
	IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth )
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
	pModel_ = pModel;
	pTextureNormal_ = pTextureNormal;
	pTextureReflect_ = pTextureReflect;
	pTextureReflectNotLight_ = pTextureReflectNotLight;
	pTextureReflectAdd_ = pTextureReflectAdd;
	pTexture3D_ = pTexture3D;
	pTextureDepth_ = pTextureDepth;

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
int DrawerRiver::Finalize( void )
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
// Arg    : Model* pModel						: ���f��
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTextureNormal	: �@���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureReflect	: ���˃e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: ���˃��C�e�B���O�Ȃ��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureReflectAdd		: ���ˉ��Z�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
//==============================================================================
int DrawerRiver::Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTextureNormal,
	IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pModel, pParameter, pEffect, pTextureNormal, pTextureReflect, pTextureReflectNotLight, pTextureReflectAdd,
		pTexture3D, pTextureDepth );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerRiver* pOut					: �R�s�[��A�h���X
//==============================================================================
int DrawerRiver::Copy( DrawerRiver* pOut ) const
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
void DrawerRiver::Draw( const D3DXMATRIX& matrixWorld )
{
	// �ϊ��s��
	D3DXMATRIX		matrixTransform;				// �ϊ��s��
	D3DXMATRIX		matrixViewProjection;			// �r���[�v���W�F�N�V�����ϊ��s��
	D3DXMATRIX		matrixWorldView;				// ���[���h�r���[�ϊ��s��
	D3DXMATRIX		matrixView;						// �r���[�ϊ��s��
	const Camera*	pCamera = nullptr;				// �J����
	RenderMatrix*	pRenderMatrix = nullptr;		// �����_�[�}�g���N�X
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );
	pRenderMatrix->GetMatrixView( &matrixView );
	D3DXMatrixMultiply( &matrixTransform, &matrixWorld, &matrixViewProjection );
	D3DXMatrixMultiply( &matrixWorldView, &matrixWorld, &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM, matrixTransform );
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorld );
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD_VIEW, matrixWorldView );

	// �e�N�X�`�����W�ϊ��s��
	D3DXMATRIX	matrixTransformTexture;			// �e�N�X�`�����W�ϊ��s��
	D3DXMATRIX	matrixSaclingTexture;			// �e�N�X�`�����W�ϊ��s��g�k
	D3DXMATRIX	matrixTranslationTexture;		// �e�N�X�`�����W�ϊ��s��ړ�
	matrixTransformTexture = matrixTransform;
	D3DXMatrixScaling( &matrixSaclingTexture, 0.5f, -0.5f, 1.0f );
	D3DXMatrixTranslation( &matrixTranslationTexture, 0.5f, 0.5f, 0.0f );
	matrixTransformTexture *= matrixSaclingTexture * matrixTranslationTexture;
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM_TEXTURE, matrixTransformTexture );

	// �e�N�Z���I�t�Z�b�g
	float	pOffset[ 2 ];		// �I�t�Z�b�g
	pOffset[ 0 ] = 0.5f / pEffectParameter_->GetWidthScreen();
	pOffset[ 1 ] = 0.5f / pEffectParameter_->GetHeightScreen();
	pEffect_->SetFloatArray( PARAMETER_OFFET_TEXEL, pOffset, 2 );

	// ���[���h�t�]�u�s��
	D3DXMATRIX	matrixWorldInverse;					// ���[���h�t�s��
	D3DXMATRIX	matrixWorldInverseTranspose;		// ���[���h�t�]�u�s��
	D3DXMatrixInverse( &matrixWorldInverse, nullptr, &matrixWorld );
	matrixWorldInverseTranspose._11 = matrixWorldInverse._11;
	matrixWorldInverseTranspose._12 = matrixWorldInverse._21;
	matrixWorldInverseTranspose._13 = matrixWorldInverse._31;
	matrixWorldInverseTranspose._14 = matrixWorldInverse._41;
	matrixWorldInverseTranspose._21 = matrixWorldInverse._12;
	matrixWorldInverseTranspose._22 = matrixWorldInverse._22;
	matrixWorldInverseTranspose._23 = matrixWorldInverse._32;
	matrixWorldInverseTranspose._24 = matrixWorldInverse._42;
	matrixWorldInverseTranspose._31 = matrixWorldInverse._13;
	matrixWorldInverseTranspose._32 = matrixWorldInverse._23;
	matrixWorldInverseTranspose._33 = matrixWorldInverse._33;
	matrixWorldInverseTranspose._34 = matrixWorldInverse._43;
	matrixWorldInverseTranspose._41 = matrixWorldInverse._14;
	matrixWorldInverseTranspose._42 = matrixWorldInverse._24;
	matrixWorldInverseTranspose._43 = matrixWorldInverse._34;
	matrixWorldInverseTranspose._44 = matrixWorldInverse._44;
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD_INVERSE_TRANSPOSE, matrixWorldInverseTranspose );

	// �@���e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE_NORMAL, pTextureNormal_ );

	// ���e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE_REFLECT, pTextureReflect_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_REFLECT_NOT_LIGHT, pTextureReflectNotLight_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_REFLECT_ADD, pTextureReflectAdd_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_3D, pTexture3D_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH, pTextureDepth_ );

	// ���_���W
	D3DXVECTOR3	positionEye;		// ���_���W
	pCamera->GetPositionCamera( &positionEye );
	pEffect_->SetFloatArray( PARAMETER_POSITION_EYE, &positionEye.x, 3 );

	// �J�����̃N���b�v�l
	float	pClipCamera[ 2 ];		// �J�����̃N���b�v�l
	pClipCamera[ 0 ] = pCamera->GetClipNear();
	pClipCamera[ 1 ] = pCamera->GetClipFar();
	pEffect_->SetFloatArray( PARAMETER_CLIP_CAMERA, pClipCamera, 2 );

	// �`��
	unsigned int		countMaterial;			// �}�e���A����
	IDirect3DTexture9*	pTexture = nullptr;		// �e�N�X�`��
	Material			material;				// �}�e���A��
	countMaterial = pModel_->GetCountMaterial();
	for( unsigned int counterMaterial = 0; counterMaterial < countMaterial; ++counterMaterial )
	{
		// ���b�V�����̎擾
		pTexture = pModel_->GetTexture( counterMaterial );
		pModel_->GetMaterial( counterMaterial, &material );

		// �f�B�t���[�Y�F
		pEffect_->SetFloatArray( PARAMETER_COLOR_DIFFUSE, &material.diffuse_.r, 3 );

		// �X�y�L�����F
		pEffect_->SetFloatArray( PARAMETER_COLOR_SPECULAR, &material.specular_.r, 3 );

		// ���˗�
		pEffect_->SetFloat( PARAMETER_REFLECTION, material.reflection_ );

		// ���˂̋���
		pEffect_->SetFloat( PARAMETER_POWER, material.power_ );

		// ���ܗ�
		pEffect_->SetFloat( PARAMETER_REFLACTIVE, material.refractive_ );

		// ���f���̕`��
		pEffect_->Begin( 0 );
		pModel_->Draw( counterMaterial );
		pEffect_->End();
	}
}

//==============================================================================
// Brief  : ���f���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : Model* pValue						: �ݒ肷��l
//==============================================================================
void DrawerRiver::SetModel( Model* pValue )
{
	// �l�̐ݒ�
	pModel_ = pValue;
}

//==============================================================================
// Brief  : ���f���̎擾
// Return : Model*								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
Model* DrawerRiver::GetModel( void ) const
{
	// �l�̕ԋp
	return pModel_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerRiver::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pModel_ = nullptr;
	pTextureNormal_ = nullptr;
	pTextureReflect_ = nullptr;
	pTextureReflectNotLight_ = nullptr;
	pTextureReflectAdd_ = nullptr;
	pTexture3D_ = nullptr;
	pTextureDepth_ = nullptr;

}
