//==============================================================================
//
// File   : GraphicBillboard.cpp
// Brief  : �r���{�[�h�|���S���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/23 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicBillboard.h"
#include "../drawer/DrawerBillboard.h"

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
GraphicBillboard::GraphicBillboard( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicBillboard::~GraphicBillboard( void )
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
// Arg    : D3DXCOLOR* pColor					: �F
// Arg    : D3DXVECTOR2* pPositionTexture		: �e�N�X�`�����W
// Arg    : D3DXVECTOR2* pScaleTexture			: �e�N�X�`���g�k
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int GraphicBillboard::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�̐���
	DrawerBillboard*	pDrawerBillboard = nullptr;		// �`��N���X
	pDrawerBillboard = new DrawerBillboard();
	if( pDrawerBillboard == nullptr )
	{
		return 1;
	}
	result = pDrawerBillboard->Initialize( pParameter, pEffectGeneral, pPolygonBillboard_, pColor, pPositionTexture, pScaleTexture, pTexture );
	ppDraw_[ GraphicMain::PASS_3D_NOT_LIGHT ] = pDrawerBillboard;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicBillboard::Finalize( void )
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
// Arg    : D3DXCOLOR* pColor					: �F
// Arg    : D3DXVECTOR2* pPositionTexture		: �e�N�X�`�����W
// Arg    : D3DXVECTOR2* pScaleTexture			: �e�N�X�`���g�k
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int GraphicBillboard::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
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
	return Initialize( priority, pParameter, pEffectGeneral, pColor, pPositionTexture, pScaleTexture, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicBillboard* pOut				: �R�s�[��A�h���X
//==============================================================================
int GraphicBillboard::Copy( GraphicBillboard* pOut ) const
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
void GraphicBillboard::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
