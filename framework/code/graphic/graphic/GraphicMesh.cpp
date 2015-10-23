//==============================================================================
//
// File   : GraphicMesh.cpp
// Brief  : ���b�V���|���S���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicMesh.h"
#include "../drawer/DrawerMesh.h"

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
GraphicMesh::GraphicMesh( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicMesh::~GraphicMesh( void )
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
// Arg    : PolygonMesh* pPolygon				: ���b�V���|���S��
// Arg    : Material* pMaterial					: �}�e���A��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int GraphicMesh::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�̐���
	DrawerMesh*	pDrawerMesh = nullptr;		// �`��N���X
	pDrawerMesh = new DrawerMesh();
	if( pDrawerMesh == nullptr )
	{
		return 1;
	}
	result = pDrawerMesh->Initialize( pParameter, pEffectGeneral, pPolygon, pMaterial, pTexture );
	ppDraw_[ GraphicMain::PASS_3D ] = pDrawerMesh;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicMesh::Finalize( void )
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
// Arg    : PolygonMesh* pPolygon				: ���b�V���|���S��
// Arg    : Material* pMaterial					: �}�e���A��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int GraphicMesh::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffectGeneral, pPolygon, pMaterial, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicMesh* pOut					: �R�s�[��A�h���X
//==============================================================================
int GraphicMesh::Copy( GraphicMesh* pOut ) const
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
void GraphicMesh::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
