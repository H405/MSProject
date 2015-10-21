//==============================================================================
//
// File   : GraphicMesh.h
// Brief  : ���b�V���|���S���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_MESH_H
#define MY_GRAPHIC_MESH_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicMain.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Effect;
class EffectParameter;
class Material;
class PolygonMesh;

//******************************************************************************
// �N���X��`
//******************************************************************************
class GraphicMesh : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicMesh( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicMesh( void );

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
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

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
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicMesh* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicMesh* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicMesh( const GraphicMesh& );
	GraphicMesh operator=( const GraphicMesh& );
};

#endif	// MY_GRAPHIC_MESH_H
