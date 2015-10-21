//==============================================================================
//
// File   : DrawerModel.cpp
// Brief  : ���f���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerModel.h"
#include "../graphic/GraphicMain.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/graphic/Material.h"
#include "../../framework/light/LightDirection.h"
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
DrawerModel::DrawerModel( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerModel::~DrawerModel( void )
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
int DrawerModel::Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect )
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
int DrawerModel::Finalize( void )
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
int DrawerModel::Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect )
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
// Arg    : DrawerModel* pOut					: �R�s�[��A�h���X
//==============================================================================
int DrawerModel::Copy( DrawerModel* pOut ) const
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
void DrawerModel::Draw( const D3DXMATRIX& matrixWorld )
{
	// �ϊ��s��
	D3DXMATRIX		matrixTransform;				// �ϊ��s��
	D3DXMATRIX		matrixViewProjection;			// �r���[�v���W�F�N�V�����s��
	const Camera*	pCamera = nullptr;				// �J����
	RenderMatrix*	pRenderMatrix = nullptr;		// �����_�[�}�g���N�X
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );
	D3DXMatrixMultiply( &matrixTransform, &matrixWorld, &matrixViewProjection );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM, matrixTransform );

	// ���[���h�}�g���N�X
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorld );

	// ���C�g�x�N�g��
	const LightDirection*	pLight = nullptr;		// ���C�g
	D3DXVECTOR3				vectorLightWorld;		// ���C�g�x�N�g��
	pLight = pEffectParameter_->GetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL );
	pLight->GetVector( &vectorLightWorld );
	pEffect_->SetFloatArray( PARAMETER_VECTOR_LIGHT, &vectorLightWorld.x, 3 );

	// ���_���W
	D3DXVECTOR3	positionEye;		// ���_���W
	pCamera->GetPositionCamera( &positionEye );
	pEffect_->SetFloatArray( PARAMETER_POSITION_EYE, &positionEye.x, 3 );

	// �A���r�G���g�F
	D3DXCOLOR	colorAmbient;		// �A���r�G���g�F
	pEffectParameter_->GetColorAmbient( &colorAmbient );
	pEffect_->SetColor( PARAMETER_COLOR_AMBIENT, colorAmbient );

	// ���C�g�̐F
	D3DXCOLOR	colorLight;		// ���C�g�̐F
	pLight->GetDiffuse( &colorLight );
	pEffect_->SetColor( PARAMETER_COLOR_LIGHT, colorLight );

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

		// �f�B�t���[�Y�F
		pEffect_->SetColor( PARAMETER_COLOR_DIFFUSE, material.diffuse_ );

		// �X�y�L�����F
		pEffect_->SetColor( PARAMETER_COLOR_SPECULAR, material.specular_ );

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
void DrawerModel::SetModel( Model* pValue )
{
	// �l�̐ݒ�
	pModel_ = pValue;
}

//==============================================================================
// Brief  : ���f���̎擾
// Return : Model*								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
Model* DrawerModel::GetModel( void ) const
{
	// �l�̕ԋp
	return pModel_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerModel::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pModel_ = nullptr;
}
