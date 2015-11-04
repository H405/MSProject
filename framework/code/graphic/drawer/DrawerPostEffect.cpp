//==============================================================================
//
// File   : DrawerPostEffect.cpp
// Brief  : ��ʃ|���S���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerPostEffect.h"
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
DrawerPostEffect::DrawerPostEffect( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerPostEffect::~DrawerPostEffect( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : Polygon2D* pPolygon					: ��ʃ|���S��
// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTexture2D		: 2D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
// Arg    : const D3DXCOLOR* pColorFade			: �t�F�[�h�̐F
// Arg    : const float* pProportionFade		: �t�F�[�h�̊���
//==============================================================================
int DrawerPostEffect::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture,
	const D3DXCOLOR* pColorFade, const float* pProportionFade )
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
	pTexture3D_ = pTexture3D;
	pTexture2D_ = pTexture2D;
	pTextureMask_ = pTextureMask;
	pPolygon_ = pPolygon;
	pColorFade_ = pColorFade;
	pProportionFade_ = pProportionFade;

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
int DrawerPostEffect::Finalize( void )
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
// Arg    : Polygon2D* pPolygon					: ��ʃ|���S��
// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTexture2D		: 2D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
// Arg    : const D3DXCOLOR* pColorFade			: �t�F�[�h�̐F
// Arg    : const float* pProportionFade		: �t�F�[�h�̊���
//==============================================================================
int DrawerPostEffect::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture,
	const D3DXCOLOR* pColorFade, const float* pProportionFade )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pParameter, pEffect, pPolygon, pTexture, pTexture3D_, pTexture2D, pTextureMask, pColorFade, pProportionFade );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerPostEffect* pOut				: �R�s�[��A�h���X
//==============================================================================
int DrawerPostEffect::Copy( DrawerPostEffect* pOut ) const
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
void DrawerPostEffect::Draw( const D3DXMATRIX& matrixWorld )
{
	// �p�����[�^�̐ݒ�
	D3DXMATRIX	matrixWorldSet;		// �ݒ肷�郏�[���h�}�g���N�X
	D3DCOLOR	colorFade;			// �t�F�[�h�F
	matrixWorldSet = matrixWorld;
	matrixWorldSet._41 -= 0.5f;
	matrixWorldSet._42 -= 0.5f;
	colorFade = *pColorFade_;
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldSet );
	pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_3D, pTexture3D_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_2D, pTexture2D_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_MASK, pTextureMask_ );
	pEffect_->SetColor( PARAMETER_COLOR_FADE, colorFade );
	pEffect_->SetFloat( PARAMETER_WIDTH_SCREEN_HALF, pEffectParameter_->GetWidthScreen() * 0.5f );
	pEffect_->SetFloat( PARAMETER_HEIGHT_SCREEN_HALF, pEffectParameter_->GetHeightScreen() * 0.5f );
	pEffect_->SetFloat( PARAMETER_PROPORTION_FADE, *pProportionFade_ );

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
void DrawerPostEffect::SetTexture( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : �e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerPostEffect::GetTexture( void ) const
{
	// �l�̕ԋp
	return pTexture_;
}

//==============================================================================
// Brief  : �|���S���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : Polygon2D* pValue					: �ݒ肷��l
//==============================================================================
void DrawerPostEffect::SetPolygon( Polygon2D* pValue )
{
	// �l�̐ݒ�
	pPolygon_ = pValue;
}

//==============================================================================
// Brief  : �|���S���̎擾
// Return : Polygon2D*							: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
Polygon2D* DrawerPostEffect::GetPolygon( void ) const
{
	// �l�̕ԋp
	return pPolygon_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerPostEffect::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTexture_ = nullptr;
	pTexture3D_ = nullptr;
	pTexture2D_ = nullptr;
	pTextureMask_ = nullptr;
	pPolygon_ = nullptr;
	pColorFade_ = nullptr;
	pProportionFade_ = nullptr;
}
