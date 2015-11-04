//==============================================================================
//
// File   : GraphicLightEffect.cpp
// Brief  : ���C�g�`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicLightEffect.h"
#include "../drawer/DrawerLightEffect.h"

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
GraphicLightEffect::GraphicLightEffect( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicLightEffect::~GraphicLightEffect( void )
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
// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
//==============================================================================
int GraphicLightEffect::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�̐���
	DrawerLightEffect*	pDrawerLightEffect = nullptr;		// �`��N���X
	pDrawerLightEffect = new DrawerLightEffect();
	if( pDrawerLightEffect == nullptr )
	{
		return 1;
	}
	result = pDrawerLightEffect->Initialize( pParameter, pEffectGeneral, pPolygon2D_, pTextureDiffuse, pTextureSpecular, pTextureNormal, pTextureDepth );
	ppDraw_[ GraphicMain::PASS_LIGHT_EFFECT ] = pDrawerLightEffect;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicLightEffect::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
//==============================================================================
int GraphicLightEffect::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffectGeneral, pTextureDiffuse, pTextureSpecular, pTextureNormal, pTextureDepth );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicLightEffect* pOut			: �R�s�[��A�h���X
//==============================================================================
int GraphicLightEffect::Copy( GraphicLightEffect* pOut ) const
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
void GraphicLightEffect::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
