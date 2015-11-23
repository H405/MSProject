//==============================================================================
//
// File   : Drawer2D.cpp
// Brief  : 2D�|���S���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Drawer2D.h"
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
Drawer2D::Drawer2D( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Drawer2D::~Drawer2D( void )
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
// Arg    : D3DXCOLOR* pColor					: �F
// Arg    : D3DXVECTOR2* pPositionTexture		: �e�N�X�`�����W
// Arg    : D3DXVECTOR2* pScaleTexture			: �e�N�X�`���g�k
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int Drawer2D::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture )
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
	pColor_ = pColor;
	pPositionTexture_ = pPositionTexture;
	pScaleTexture_ = pScaleTexture;

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
int Drawer2D::Finalize( void )
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
// Arg    : D3DXCOLOR* pColor					: �F
// Arg    : D3DXVECTOR2* pPositionTexture		: �e�N�X�`�����W
// Arg    : D3DXVECTOR2* pScaleTexture			: �e�N�X�`���g�k
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int Drawer2D::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pParameter, pEffect, pPolygon, pColor, pPositionTexture, pScaleTexture, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : Drawer2D* pOut						: �R�s�[��A�h���X
//==============================================================================
int Drawer2D::Copy( Drawer2D* pOut ) const
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
void Drawer2D::Draw( const D3DXMATRIX& matrixWorld )
{
	// ���[���h�ϊ��s��̐ݒ�
	D3DXMATRIX	matrixWorldSet;		// �ݒ肷�郏�[���h�}�g���N�X
	matrixWorldSet = matrixWorld;
	matrixWorldSet._41 *= 2.0f;
	matrixWorldSet._42 *= 2.0f;
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldSet );

	// ��ʃT�C�Y�̐ݒ�
	float	pSizeScreen[ 2 ];		// ��ʃT�C�Y
	pSizeScreen[ 0 ] = pEffectParameter_->GetWidthScreen();
	pSizeScreen[ 1 ] = pEffectParameter_->GetHeightScreen();
	pEffect_->SetFloatArray( PARAMETER_SIZE_SCREEN, pSizeScreen, 2 );

	// �e�N�X�`���̐ݒ�
	pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture_ );
	pEffect_->SetColor( PARAMETER_COLOR, *pColor_ );
	pEffect_->SetFloatArray( PARAMETER_POSITION_TEXTURE, &pPositionTexture_->x, 2 );
	pEffect_->SetFloatArray( PARAMETER_SCALE_TEXTURE, &pScaleTexture_->x, 2 );

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
void Drawer2D::SetTexture( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : �e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* Drawer2D::GetTexture( void ) const
{
	// �l�̕ԋp
	return pTexture_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Drawer2D::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTexture_ = nullptr;
	pPolygon_ = nullptr;
	pColor_ = nullptr;
	pPositionTexture_ = nullptr;
	pScaleTexture_ = nullptr;
}
