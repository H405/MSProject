//==============================================================================
//
// File   : DrawerPoint.cpp
// Brief  : �|�C���g�X�v���C�g�`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerPoint.h"
#include "../graphic/GraphicMain.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/polygon/PolygonPoint.h"
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
DrawerPoint::DrawerPoint( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerPoint::~DrawerPoint( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : PolygonPoint* pPolygon				: �|�C���g�X�v���C�g�|���S��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int DrawerPoint::Initialize( const EffectParameter* pParameter, Effect* pEffect, PolygonPoint* pPolygon, IDirect3DTexture9* pTexture )
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
int DrawerPoint::Finalize( void )
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
// Arg    : PolygonPoint* pPolygon				: �|�C���g�X�v���C�g�|���S��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int DrawerPoint::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, PolygonPoint* pPolygon, IDirect3DTexture9* pTexture )
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
// Arg    : DrawerPoint* pOut					: �R�s�[��A�h���X
//==============================================================================
int DrawerPoint::Copy( DrawerPoint* pOut ) const
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
void DrawerPoint::Draw( const D3DXMATRIX& matrixWorld )
{
	// �r���[�ϊ��s��
	D3DXMATRIX		matrixView;						// �r���[�ϊ��s��
	const Camera*	pCamera = nullptr;				// �J����
	RenderMatrix*	pRenderMatrix = nullptr;		// �����_�[�}�g���N�X
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixView( &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW, matrixView );

	// �v���W�F�N�V�����ϊ��s��
	D3DXMATRIX	matrixProjection;		// �v���W�F�N�V�����ϊ��s��
	pRenderMatrix->GetMatrixProjection( &matrixProjection );
	pEffect_->SetMatrix( PARAMETER_MATRIX_PROJECTION, matrixProjection );

	// �e�N�X�`���̐ݒ�
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
void DrawerPoint::SetTexture( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : �e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerPoint::GetTexture( void ) const
{
	// �l�̕ԋp
	return pTexture_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerPoint::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTexture_ = nullptr;
	pPolygon_ = nullptr;
}
