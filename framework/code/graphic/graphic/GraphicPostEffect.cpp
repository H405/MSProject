//==============================================================================
//
// File   : GraphicPostEffect.cpp
// Brief  : ��ʃ|���S���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicPostEffect.h"
#include "../drawer/DrawerPostEffect.h"

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
GraphicPostEffect::GraphicPostEffect( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicPostEffect::~GraphicPostEffect( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : const float* pProportionFade		: �t�F�[�h����
// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTexture2D		: 2D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int GraphicPostEffect::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, const float* pProportionFade,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pTexture_ = pTexture;

	// �`��N���X�̐���
	DrawerPostEffect*	pDrawerPostEffect = nullptr;		// �`��N���X
	pDrawerPostEffect = new DrawerPostEffect();
	if( pDrawerPostEffect == nullptr )
	{
		return 1;
	}
	result = pDrawerPostEffect->Initialize( pParameter, pEffectGeneral, pPolygon2D_, pTexture3D, pTexture2D, pTextureMask, pTexture, &colorFade_, pProportionFade );
	ppDraw_[ GraphicMain::PASS_POST_EFFECT ] = pDrawerPostEffect;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicPostEffect::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Finalize();
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
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : const float* pProportionFade		: �t�F�[�h����
// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTexture2D		: 2D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int GraphicPostEffect::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, const float* pProportionFade,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffectGeneral, pProportionFade, pTexture3D, pTexture2D, pTextureMask, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicPostEffect* pOut				: �R�s�[��A�h���X
//==============================================================================
int GraphicPostEffect::Copy( GraphicPostEffect* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void GraphicPostEffect::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pTexture_ = nullptr;
	colorFade_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
}
