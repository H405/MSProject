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
#include "../../framework/light/LightDirection.h"
#include "../../framework/light/LightPoint.h"
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
// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: ���ʊ��}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: �w�ʊ��}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: ���ʉ��Z���}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: �w�ʉ��Z���}�b�v�e�N�X�`��
//==============================================================================
int DrawerRiver::Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect,
	IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
	IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack )
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
	pTextureEnvironmentFront_ = pTextureEnvironmentFront;
	pTextureEnvironmentBack_ = pTextureEnvironmentBack;
	pTextureEnvironmentAddFront_ = pTextureEnvironmentAddFront;
	pTextureEnvironmentAddBack_ = pTextureEnvironmentAddBack;

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
// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: ���ʊ��}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: �w�ʊ��}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: ���ʉ��Z���}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: �w�ʉ��Z���}�b�v�e�N�X�`��
//==============================================================================
int DrawerRiver::Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect,
	IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
	IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pModel, pParameter, pEffect, pTextureNormal,
		pTextureEnvironmentFront, pTextureEnvironmentBack, pTextureEnvironmentAddFront, pTextureEnvironmentAddBack );
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
	pEffect_->SetTexture( PARAMETER_TEXTURE_ENVIRONMENT_FRONT, pTextureEnvironmentFront_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_ENVIRONMENT_BACK, pTextureEnvironmentBack_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_ENVIRONMENT_ADD_FRONT, pTextureEnvironmentAddFront_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_ENVIRONMENT_ADD_BACK, pTextureEnvironmentAddBack_ );

	// ���_���W
	D3DXVECTOR3	positionEye;		// ���_���W
	pCamera->GetPositionCamera( &positionEye );
	pEffect_->SetFloatArray( PARAMETER_POSITION_EYE, &positionEye.x, 3 );

	// �J�����̃N���b�v�l
	float	pClipCamera[ 2 ];		// �J�����̃N���b�v�l
	pClipCamera[ 0 ] = pCamera->GetClipNear();
	pClipCamera[ 1 ] = pCamera->GetClipFar();
	pEffect_->SetFloatArray( PARAMETER_CLIP_CAMERA, pClipCamera, 2 );

	// �����F
	D3DXCOLOR	colorAmbient;		// �����F
	pEffectParameter_->GetColorAmbient( &colorAmbient );
	pEffect_->SetFloatArray( PARAMETER_COLOR_AMBIENT, &colorAmbient.r, 3 );

	// �f�B���N�V���i�����C�g�̃x�N�g��
	const LightDirection*	pLightDirection = nullptr;		// �f�B���N�V���i�����C�g
	D3DXVECTOR3				vectorLight;					// �f�B���N�V���i�����C�g�x�N�g��
	pLightDirection = pEffectParameter_->GetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL );
	if( pLightDirection != nullptr )
	{
		pLightDirection->GetVector( &vectorLight );
		pEffect_->SetFloatArray( PARAMETER_VECTOR_LIGHT_DIRECTION, &vectorLight.x, 3 );
	}

	// �f�B���N�V���i�����C�g�̐F
	D3DXCOLOR	colorLightDirection;		// �f�B���N�V���i�����C�g�̐F
	if( pLightDirection != nullptr )
	{
		pLightDirection->GetDiffuse( &colorLightDirection );
		pEffect_->SetFloatArray( PARAMETER_COLOR_LIGHT_DIRECTION, &colorLightDirection.r, 3 );
	}

	// �|�C���g���C�g�̐ݒ�
	int					countPoint;				// �|�C���g���C�g�̐�
	const LightPoint*	pLightPoint;			// �|�C���g���C�g
	D3DXVECTOR3			positionPoint;			// �|�C���g���C�g�̍��W
	D3DXCOLOR			colorPoint;				// �|�C���g���C�g�̐F
	D3DXVECTOR3			attemuationPoint;		// �|�C���g���C�g�̌�����
	float				pPositionPoint[ 3 * GraphicMain::LIGHT_POINT_MAX ];			// �|�C���g���C�g�̍��W
	float				pColorPoint[ 3 * GraphicMain::LIGHT_POINT_MAX ];			// �|�C���g���C�g�̐F
	float				pAttemuationPoint[ 3 * GraphicMain::LIGHT_POINT_MAX ];		// �|�C���g���C�g�̌�����
	countPoint = pEffectParameter_->GetCountLightPoint();
	for( int counterLight = 0; counterLight < countPoint; ++counterLight )
	{
		// �|�C���g���C�g�̍��W
		pLightPoint = pEffectParameter_->GetLightPoint( counterLight );
		pLightPoint->GetPosition( &positionPoint );
		pPositionPoint[ 3 * counterLight + 0 ] = positionPoint.x;
		pPositionPoint[ 3 * counterLight + 1 ] = positionPoint.y;
		pPositionPoint[ 3 * counterLight + 2 ] = positionPoint.z;

		// �|�C���g���C�g�̐F
		pLightPoint->GetDiffuse( &colorPoint );
		pColorPoint[ 3 * counterLight + 0 ] = colorPoint.r;
		pColorPoint[ 3 * counterLight + 1 ] = colorPoint.g;
		pColorPoint[ 3 * counterLight + 2 ] = colorPoint.b;

		// �|�C���g���C�g�̌�����
		pLightPoint->GetAttemuation( &attemuationPoint );
		pAttemuationPoint[ 3 * counterLight + 0 ] = attemuationPoint.x;
		pAttemuationPoint[ 3 * counterLight + 1 ] = attemuationPoint.y;
		pAttemuationPoint[ 3 * counterLight + 2 ] = attemuationPoint.z;
	}

	// �|�C���g���C�g�̍��W
	pEffect_->SetFloatArray( PARAMETER_POSITION_LIGHT_POINT, pPositionPoint, 3 * countPoint );

	// �|�C���g���C�g�̐F
	pEffect_->SetFloatArray( PARAMETER_COLOR_LIGHT_POINT, pColorPoint, 3 * countPoint );

	// �|�C���g���C�g�̌�����
	pEffect_->SetFloatArray( PARAMETER_ATTENUATION_LIGHT_POINT, pAttemuationPoint, 3 * countPoint );

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
	pTextureEnvironmentFront_ = nullptr;
	pTextureEnvironmentBack_ = nullptr;
	pTextureEnvironmentAddFront_ = nullptr;
	pTextureEnvironmentAddBack_ = nullptr;

}
