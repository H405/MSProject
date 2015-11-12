//==============================================================================
//
// File   : DrawerMerge.cpp
// Brief  : ����3D�`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerMerge.h"
#include "../../framework/polygon/Polygon2D.h"
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
DrawerMerge::DrawerMerge( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerMerge::~DrawerMerge( void )
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
// Arg    : IDirect3DTexture9* pTextureLight	: ���C�g����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureNotLight	: ���C�g�Ȃ��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureAdd		: ���Z�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
//==============================================================================
int DrawerMerge::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
	IDirect3DTexture9* pTextureDepth )
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
	pTextureLight_ = pTextureLight;
	pTextureNotLight_ = pTextureNotLight;
	pTextureMask_ = pTextureMask;
	pTextureAdd_ = pTextureAdd;
	pTextureDepth_ = pTextureDepth;
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
int DrawerMerge::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTextureLight	: ���C�g����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureNotLight	: ���C�g�Ȃ��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureAdd		: ���Z�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
//==============================================================================
int DrawerMerge::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
	IDirect3DTexture9* pTextureDepth )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pParameter, pEffect, pPolygon, pTextureLight, pTextureNotLight, pTextureMask, pTextureAdd, pTextureDepth );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerMerge* pOut					: �R�s�[��A�h���X
//==============================================================================
int DrawerMerge::Copy( DrawerMerge* pOut ) const
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
void DrawerMerge::Draw( const D3DXMATRIX& matrixWorld )
{
	// ���_�V�F�[�_�p�p�����[�^
	D3DXMATRIX	matrixWorldSet;			// �ݒ肷�郏�[���h�}�g���N�X
	float		pSizeScreen[ 2 ];		// ��ʂ̃T�C�Y
	matrixWorldSet = matrixWorld;
	matrixWorldSet._41 -= 0.5f;
	matrixWorldSet._42 -= 0.5f;
	pSizeScreen[ 0 ] = 0.5f * pEffectParameter_->GetWidthScreen();
	pSizeScreen[ 1 ] = 0.5f * pEffectParameter_->GetHeightScreen();
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldSet );
	pEffect_->SetFloatArray( PARAMETER_SIZE_SCREEN_HALF, pSizeScreen, 2 );

	// �œ_�����̐ݒ�
	pEffect_->SetFloat( PARAMETER_FORCUS, pEffectParameter_->GetForcus() );

	// 3D���e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE_LIGHT, pTextureLight_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_NOT_LIGHT, pTextureNotLight_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_MASK, pTextureMask_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_ADD, pTextureAdd_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH, pTextureDepth_ );

	// �`��
	pEffect_->Begin( 0 );
	pPolygon_->Draw();
	pEffect_->End();
}

//==============================================================================
// Brief  : ���C�g����e�N�X�`���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DTexture9* pValue			: �ݒ肷��l
//==============================================================================
void DrawerMerge::SetTextureLight( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTextureLight_ = pValue;
}

//==============================================================================
// Brief  : ���C�g����e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerMerge::GetTextureLight( void ) const
{
	// �l�̕ԋp
	return pTextureLight_;
}

//==============================================================================
// Brief  : ���C�g�Ȃ��e�N�X�`���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DTexture9* pValue			: �ݒ肷��l
//==============================================================================
void DrawerMerge::SetTextureNotLight( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTextureNotLight_ = pValue;
}

//==============================================================================
// Brief  : ���C�g�Ȃ��e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerMerge::GetTextureNotLight( void ) const
{
	// �l�̕ԋp
	return pTextureNotLight_;
}

//==============================================================================
// Brief  : �}�X�N�e�N�X�`���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DTexture9* pValue			: �ݒ肷��l
//==============================================================================
void DrawerMerge::SetTextureMask( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTextureMask_ = pValue;
}

//==============================================================================
// Brief  : �}�X�N�e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerMerge::GetTextureMask( void ) const
{
	// �l�̕ԋp
	return pTextureMask_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerMerge::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTextureLight_ = nullptr;
	pTextureNotLight_ = nullptr;
	pTextureMask_ = nullptr;
	pTextureAdd_ = nullptr;
	pTextureDepth_ = nullptr;
	pPolygon_ = nullptr;
}
