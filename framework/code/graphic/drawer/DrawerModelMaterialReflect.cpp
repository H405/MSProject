//==============================================================================
//
// File   : DrawerModelMaterialReflect.cpp
// Brief  : ���˃��f���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/21 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerModelMaterialReflect.h"
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
DrawerModelMaterialReflect::DrawerModelMaterialReflect( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerModelMaterialReflect::~DrawerModelMaterialReflect( void )
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
//==============================================================================
int DrawerModelMaterialReflect::Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect )
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
int DrawerModelMaterialReflect::Finalize( void )
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
//==============================================================================
int DrawerModelMaterialReflect::Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pModel, pParameter, pEffect );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerModelMaterialReflect* pOut	: �R�s�[��A�h���X
//==============================================================================
int DrawerModelMaterialReflect::Copy( DrawerModelMaterialReflect* pOut ) const
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
void DrawerModelMaterialReflect::Draw( const D3DXMATRIX& matrixWorld )
{
	// ���˃��[���h�ϊ��s��̍쐬
	D3DXMATRIX		matrixReflect;					// ���ˍs��
	D3DXMATRIX		matrixWorldReflect;				// ���˃��[���h�s��
	D3DXVECTOR3		positionReflect;				// ���˖ʍ��W
	D3DXVECTOR3		normalReflect;					// ���˖ʖ@��
	D3DXPLANE		planeReflect;					// ���˖�
	positionReflect.x = positionReflect.z = normalReflect.x = normalReflect.z = 0.0f;
	positionReflect.y = pEffectParameter_->GetHeightReflect();
	normalReflect.y = 1.0f;
	D3DXPlaneFromPointNormal( &planeReflect, &positionReflect, &normalReflect );
	D3DXMatrixReflect( &matrixReflect, &planeReflect );
	D3DXMatrixMultiply( &matrixWorldReflect, &matrixWorld, &matrixReflect );

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
	D3DXMatrixMultiply( &matrixTransform, &matrixWorldReflect, &matrixViewProjection );
	D3DXMatrixMultiply( &matrixWorldView, &matrixWorldReflect, &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM, matrixTransform );
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldReflect );
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD_VIEW, matrixWorldView );

	// ���˖ʂ̍���
	pEffect_->SetFloat( PARAMETER_HEIGHT, positionReflect.y );

	// �`��
	unsigned int		countMaterial;			// �}�e���A����
	Material			material;				// �}�e���A��
	countMaterial = pModel_->GetCountMaterial();
	for( unsigned int counterMaterial = 0; counterMaterial < countMaterial; ++counterMaterial )
	{
		// ���b�V�����̎擾
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
void DrawerModelMaterialReflect::SetModel( Model* pValue )
{
	// �l�̐ݒ�
	pModel_ = pValue;
}

//==============================================================================
// Brief  : ���f���̎擾
// Return : Model*								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
Model* DrawerModelMaterialReflect::GetModel( void ) const
{
	// �l�̕ԋp
	return pModel_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerModelMaterialReflect::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pModel_ = nullptr;
}
