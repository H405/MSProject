//==============================================================================
//
// File   : Graphic3D.cpp
// Brief  : 3D�|���S���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Graphic3D.h"
#include "../drawer/Drawer3D.h"

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
Graphic3D::Graphic3D( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Graphic3D::~Graphic3D( void )
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
// Arg    : Material* pMaterial					: �}�e���A��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int Graphic3D::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	Material* pMaterial, IDirect3DTexture9* pTexture )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�̐���
	Drawer3D*	pDrawer3D = nullptr;		// �`��N���X
	pDrawer3D = new Drawer3D();
	if( pDrawer3D == nullptr )
	{
		return 1;
	}
	result = pDrawer3D->Initialize( pParameter, pEffectGeneral, pPolygon3D_, pMaterial, pTexture );
	ppDraw_[ GraphicMain::PASS_GENERAL ] = pDrawer3D;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Graphic3D::Finalize( void )
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
// Arg    : Material* pMaterial					: �}�e���A��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int Graphic3D::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	Material* pMaterial, IDirect3DTexture9* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffectGeneral, pMaterial, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : Graphic3D* pOut						: �R�s�[��A�h���X
//==============================================================================
int Graphic3D::Copy( Graphic3D* pOut ) const
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
void Graphic3D::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
