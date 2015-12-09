//==============================================================================
//
// File   : DrawerModelParaboloid.cpp
// Brief  : ���f���e�`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/24 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerModelParaboloid.h"
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
DrawerModelParaboloid::DrawerModelParaboloid( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerModelParaboloid::~DrawerModelParaboloid( void )
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
// Arg    : int indexCamera						: �J�����ԍ�
//==============================================================================
int DrawerModelParaboloid::Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, int indexCamera )
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
	indexCamera_ = indexCamera;

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
int DrawerModelParaboloid::Finalize( void )
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
// Arg    : int indexCamera						: �J�����ԍ�
//==============================================================================
int DrawerModelParaboloid::Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, int indexCamera )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pModel, pParameter, pEffect, indexCamera );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerModelParaboloid* pOut			: �R�s�[��A�h���X
//==============================================================================
int DrawerModelParaboloid::Copy( DrawerModelParaboloid* pOut ) const
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
void DrawerModelParaboloid::Draw( const D3DXMATRIX& matrixWorld )
{
	// �ϊ��s��
	D3DXMATRIX		matrixWorldView;				// ���[���h�r���[�ϊ��s��
	D3DXMATRIX		matrixView;						// �r���[�ϊ��s��
	const Camera*	pCamera = nullptr;				// �J����
	RenderMatrix*	pRenderMatrix = nullptr;		// �����_�[�}�g���N�X
	pCamera = pEffectParameter_->GetCamera( indexCamera_ );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixView( &matrixView );
	D3DXMatrixMultiply( &matrixWorldView, &matrixWorld, &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD_VIEW, matrixWorldView );

	// �J�����̃N���b�v��
	float	pClipCamera[ 2 ];		// �J�����̃N���b�v��
	pClipCamera[ 0 ] = pCamera->GetClipNear();
	pClipCamera[ 1 ] = pCamera->GetClipFar();
	pEffect_->SetFloatArray( PARAMETER_CLIP_CAMERA, pClipCamera, 2 );

	// �`��
	unsigned int	countMaterial;		// �}�e���A����
	countMaterial = pModel_->GetCountMaterial();
	for( unsigned int counterMaterial = 0; counterMaterial < countMaterial; ++counterMaterial )
	{
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
void DrawerModelParaboloid::SetModel( Model* pValue )
{
	// �l�̐ݒ�
	pModel_ = pValue;
}

//==============================================================================
// Brief  : ���f���̎擾
// Return : Model*								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
Model* DrawerModelParaboloid::GetModel( void ) const
{
	// �l�̕ԋp
	return pModel_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerModelParaboloid::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pModel_ = nullptr;
	indexCamera_ = 0;
}
