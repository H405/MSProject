//==============================================================================
//
// File   : GraphicDrawTexture.cpp
// Brief  :�f�o�b�O�e�N�X�`���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/27 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicDrawTexture.h"
#include "../drawer/DrawerDrawTexture.h"
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
GraphicDrawTexture::GraphicDrawTexture( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicDrawTexture::~GraphicDrawTexture( void )
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
// Arg    : IDirect3DTexture9** pTexture		: �e�N�X�`��
// Arg    : float* pMultiply					: �F�̔{��
//==============================================================================
int GraphicDrawTexture::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9** ppTexture, float* pMultiply )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�̐���
	DrawerDrawTexture*	pDrawerDrawTexture = nullptr;		// �`��N���X
	pDrawerDrawTexture = new DrawerDrawTexture();
	if( pDrawerDrawTexture == nullptr )
	{
		return 1;
	}
	result = pDrawerDrawTexture->Initialize( pParameter, pEffectGeneral, pPolygon2D_, ppTexture, pMultiply );
	ppDraw_[ GraphicMain::PASS_POST_EFFECT ] = pDrawerDrawTexture;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicDrawTexture::Finalize( void )
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
// Arg    : IDirect3DTexture9** pTexture		: �e�N�X�`��
// Arg    : float* pMultiply					: �F�̔{��
//==============================================================================
int GraphicDrawTexture::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9** ppTexture, float* pMultiply )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffectGeneral, ppTexture, pMultiply );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicDrawTexture* pOut					: �R�s�[��A�h���X
//==============================================================================
int GraphicDrawTexture::Copy( GraphicDrawTexture* pOut ) const
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
void GraphicDrawTexture::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
