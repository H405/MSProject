//==============================================================================
//
// File   : DrawerMesh.h
// Brief  : ���b�V���|���S���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_MESH_H
#define MY_DRAWER_MESH_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../../framework/graphic/drawer.h"

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
class DrawerMesh : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// �ϊ��s��
		PARAMETER_MATRIX_WORLD,				// ���[���h�}�g���N�X
		PARAMETER_VECTOR_LIGHT,				// ���C�g�x�N�g��
		PARAMETER_POSITION_EYE,				// ���_���W
		PARAMETER_TEXTURE,					// �e�N�X�`��
		PARAMETER_COLOR_AMBIENT,			// �A���r�G���g�F
		PARAMETER_COLOR_LIGHT,				// ���C�g�̐F
		PARAMETER_COLOR_DIFFUSE,			// �f�B�t���[�Y�F
		PARAMETER_COLOR_SPECULAR,			// �X�y�L�����F
		PARAMETER_REFLECTION,				// ���˗�
		PARAMETER_POWER,					// ���˂̋���
		PARAMETER_REFLACTIVE,				// ���ܗ�
		PARAMETER_MAX						// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerMesh( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerMesh( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : PolygonMesh* pPolygon				: ���b�V���|���S��
	// Arg    : Material* pMaterial					: �}�e���A��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : PolygonMesh* pPolygon				: ���b�V���|���S��
	// Arg    : Material* pMaterial					: �}�e���A��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerMesh* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerMesh* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : const D3DXMATRIX& matrixWorld		: ���[���h�}�g���N�X
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetTexture( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTexture( void ) const;

protected:
	const EffectParameter*	pEffectParameter_;		// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;				// �G�t�F�N�g
	IDirect3DTexture9*		pTexture_;				// �e�N�X�`��
	PolygonMesh*			pPolygon_;				// �|���S��
	Material*				pMaterial_;				// �}�e���A��

private:
	void InitializeSelf( void );
	DrawerMesh( const DrawerMesh& );
	DrawerMesh operator=( const DrawerMesh& );
};

#endif	// MY_DRAWER_MESH_H
