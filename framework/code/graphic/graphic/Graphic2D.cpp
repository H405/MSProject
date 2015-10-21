//==============================================================================
//
// File   : Graphic2D.cpp
// Brief  : 2D�|���S���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Graphic2D.h"
#include "../drawer/Drawer2D.h"

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
Graphic2D::Graphic2D( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Graphic2D::~Graphic2D( void )
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
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int Graphic2D::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, D3DXCOLOR* pColor, IDirect3DTexture9* pTexture )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�̐���
	Drawer2D*	pDrawer2D = nullptr;		// �`��N���X
	pDrawer2D = new Drawer2D();
	if( pDrawer2D == nullptr )
	{
		return 1;
	}
	result = pDrawer2D->Initialize( pParameter, pEffectGeneral, pPolygon2D_, pColor, pTexture );
	ppDraw_[ GraphicMain::PASS_GENERAL ] = pDrawer2D;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Graphic2D::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int Graphic2D::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, D3DXCOLOR* pColor, IDirect3DTexture9* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffectGeneral, pColor, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : Graphic2D* pOut						: �R�s�[��A�h���X
//==============================================================================
int Graphic2D::Copy( Graphic2D* pOut ) const
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
void Graphic2D::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
