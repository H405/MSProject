//==============================================================================
//
// File   : DrawerSkyReflect.cpp
// Brief  : ��`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerSkyReflect.h"
#include "../graphic/GraphicMain.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/polygon/PolygonMeshDomeInside.h"
#include "../../framework/render/RenderMatrix.h"
#include "../../framework/resource/Effect.h"
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
DrawerSkyReflect::DrawerSkyReflect( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerSkyReflect::~DrawerSkyReflect( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : PolygonMeshDomeInside* pPolygon		: �������b�V���h�[���|���S��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int DrawerSkyReflect::Initialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMeshDomeInside* pPolygon, IDirect3DTexture9* pTexture )
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
	pTexture_ = pTexture;
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
int DrawerSkyReflect::Finalize( void )
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
// Arg    : PolygonMeshDomeInside* pPolygon		: �������b�V���h�[���|���S��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int DrawerSkyReflect::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMeshDomeInside* pPolygon, IDirect3DTexture9* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pParameter, pEffect, pPolygon, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerSkyReflect* pOut						: �R�s�[��A�h���X
//==============================================================================
int DrawerSkyReflect::Copy( DrawerSkyReflect* pOut ) const
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
void DrawerSkyReflect::Draw( const D3DXMATRIX& matrixWorld )
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
	D3DXMATRIX		matrixViewProjection;			// �r���[�v���W�F�N�V�����s��
	const Camera*	pCamera = nullptr;				// �J����
	RenderMatrix*	pRenderMatrix = nullptr;		// �����_�[�}�g���N�X
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );
	D3DXMatrixMultiply( &matrixTransform, &matrixWorldReflect, &matrixViewProjection );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM, matrixTransform );

	// �e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture_ );

	// �`��
	pEffect_->Begin( 0 );
	pPolygon_->Draw();
	pEffect_->End();
}

//==============================================================================
// Brief  : �e�N�X�`���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DTexture9* pValue			: �ݒ肷��l
//==============================================================================
void DrawerSkyReflect::SetTexture( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : �e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerSkyReflect::GetTexture( void ) const
{
	// �l�̕ԋp
	return pTexture_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerSkyReflect::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTexture_ = nullptr;
	pPolygon_ = nullptr;
}