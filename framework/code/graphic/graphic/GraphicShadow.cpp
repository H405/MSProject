//==============================================================================
//
// File   : GraphicShadow.cpp
// Brief  : ���C�g�`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicShadow.h"
#include "../drawer/DrawerShadow.h"
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
GraphicShadow::GraphicShadow( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicShadow::~GraphicShadow( void )
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
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightNear	: ���s����(��)�̐[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightFar		: ���s����(��)�̐[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightPoint	: �_�����̐[�x���e�N�X�`��
//==============================================================================
int GraphicShadow::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pParameter_ = pParameter;

	// �`��N���X�̐���
	DrawerShadow*	pDrawerShadow = nullptr;		// �`��N���X
	pDrawerShadow = new DrawerShadow();
	if( pDrawerShadow == nullptr )
	{
		return 1;
	}
	result = pDrawerShadow->Initialize( pParameter, pEffectGeneral, pPolygon2D_, pTextureDepth, pTextureLightNear, pTextureLightFar, pTextureLightPoint );
	ppDraw_[ GraphicMain::PASS_SHADOW ] = pDrawerShadow;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicShadow::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightNear	: ���s����(��)�̐[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightFar		: ���s����(��)�̐[�x���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureLightPoint	: �_�����̐[�x���e�N�X�`��
//==============================================================================
int GraphicShadow::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffectGeneral, pTextureDepth, pTextureLightNear, pTextureLightFar, pTextureLightPoint );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicShadow* pOut					: �R�s�[��A�h���X
//==============================================================================
int GraphicShadow::Copy( GraphicShadow* pOut ) const
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
void GraphicShadow::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pParameter_ = nullptr;
	pDrawerLight_ = nullptr;
}
