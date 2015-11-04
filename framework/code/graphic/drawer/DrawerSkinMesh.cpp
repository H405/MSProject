//==============================================================================
//
// File   : DrawerSkinMesh.cpp
// Brief  : �X�L�����b�V���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerSkinMesh.h"
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
DrawerSkinMesh::DrawerSkinMesh( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerSkinMesh::~DrawerSkinMesh( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : Model* pModel						: ���f��
// Arg    : int countBone						: �{�[����
// Arg    : D3DXMATRIX* pMatrixBone				: �{�[���ϊ��s��Q�ƃA�h���X
// Arg    : int* pIndexFrame					: �t���[���ԍ��Q�ƃA�h���X
//==============================================================================
int DrawerSkinMesh::Initialize( const EffectParameter* pParameter, Effect* pEffect, Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame )
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
	countBone_ = countBone;
	pMatrixBone_ = pMatrixBone;
	pIndexFrame_ = pIndexFrame;

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
int DrawerSkinMesh::Finalize( void )
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
// Arg    : Model* pModel						: ���f��
// Arg    : int countBone						: �{�[����
// Arg    : D3DXMATRIX* pMatrixBone				: �{�[���ϊ��s��Q�ƃA�h���X
// Arg    : int* pIndexFrame					: �t���[���ԍ��Q�ƃA�h���X
//==============================================================================
int DrawerSkinMesh::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pParameter, pEffect, pModel, countBone, pMatrixBone, pIndexFrame );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerSkinMesh* pOut				: �R�s�[��A�h���X
//==============================================================================
int DrawerSkinMesh::Copy( DrawerSkinMesh* pOut ) const
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
void DrawerSkinMesh::Draw( const D3DXMATRIX& matrixWorld )
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

	// �{�[���ϊ��s��
	pEffect_->SetMatrixArray( PARAMETER_MATRIX_BONE, pMatrixBone_, countBone_ );
	pEffect_->SetInteger( PARAMETER_COUNT_BONE, countBone_ );

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

		// �e�N�X�`��
		pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture );

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
void DrawerSkinMesh::SetModel( Model* pValue )
{
	// �l�̐ݒ�
	pModel_ = pValue;
}

//==============================================================================
// Brief  : ���f���̎擾
// Return : Model*								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
Model* DrawerSkinMesh::GetModel( void ) const
{
	// �l�̕ԋp
	return pModel_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerSkinMesh::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pModel_ = nullptr;
	countBone_ = 0;
	pMatrixBone_ = nullptr;
	pIndexFrame_ = nullptr;
}
