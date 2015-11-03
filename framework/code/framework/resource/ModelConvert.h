//==============================================================================
//
// File   : ModelConvert.h
// Brief  : �ϊ��ς݃��f��
// Author : Taiga Shirakawa
// Date   : 2015/10/29 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_MODEL_CONVERT_H
#define MY_MODEL_CONVERT_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Model.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Vertex;

//******************************************************************************
// �N���X��`
//******************************************************************************
class ModelConvert : public Model
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ModelConvert( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ModelConvert( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : unsigned int elementVertex			: ���_�̗v�f
	// Arg    : unsigned int countMaterial			: �}�e���A����
	// Arg    : unsigned int countTexture			: �e�N�X�`����
	// Arg    : unsigned long countMesh				: ���b�V����
	// Arg    : unsigned long countBone				: �{�[����
	// Arg    : void* pVertexBuffer					: ���b�V���̒��_���
	// Arg    : const int* pCountVertex				: ���b�V���̒��_��
	// Arg    : Material* pMaterial					: ���b�V���̃}�e���A�����
	// Arg    : const int* pIndexMaterial			: ���b�V���̃}�e���A���ԍ�
	// Arg    : IDirect3DTexture9** ppTexture		: ���b�V���̃e�N�X�`�����
	// Arg    : const int* pIndexTexture			: ���b�V���̃e�N�X�`���ԍ�
	// Arg    : const D3DXMATRIX* pMatrixBone		: �{�[���̏����p���s��
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice, unsigned int elementVertex,
		unsigned int countMaterial, unsigned int countTexture, unsigned long countMesh, unsigned long countBone,
		void** ppVertexBuffer, const int* pCountVertex, Material* pMaterial, const int* pIndexMaterial,
		IDirect3DTexture9** ppTexture, const int* pIndexTexture, const D3DXMATRIX* pMatrixBone );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : unsigned int elementVertex			: ���_�̗v�f
	// Arg    : unsigned int countMaterial			: �}�e���A����
	// Arg    : unsigned int countTexture			: �e�N�X�`����
	// Arg    : unsigned long countMesh				: ���b�V����
	// Arg    : unsigned long countBone				: �{�[����
	// Arg    : void* pVertexBuffer					: ���b�V���̒��_���
	// Arg    : const int* pCountVertex				: ���b�V���̒��_��
	// Arg    : Material* pMaterial					: ���b�V���̃}�e���A�����
	// Arg    : const int* pIndexMaterial			: ���b�V���̃}�e���A���ԍ�
	// Arg    : IDirect3DTexture9** ppTexture		: ���b�V���̃e�N�X�`�����
	// Arg    : const int* pIndexTexture			: ���b�V���̃e�N�X�`���ԍ�
	// Arg    : const D3DXMATRIX* pMatrixBone		: �{�[���̏����p���s��
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice, unsigned int elementVertex,
		unsigned int countMaterial, unsigned int countTexture, unsigned long countMesh, unsigned long countBone,
		void** ppVertexBuffer, const int* pCountVertex, Material* pMaterial, const int* pIndexMaterial,
		IDirect3DTexture9** ppTexture, const int* pIndexTexture, const D3DXMATRIX* pMatrixBone );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : ModelConvert* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ModelConvert* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : int indexMaterial					: �`��}�e���A���ԍ�
	//==============================================================================
	void Draw( int indexMaterial );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void GetMaterial( int index, Material* pOut ) const;
	IDirect3DTexture9* GetTexture( int index ) const;
	unsigned long GetCountMesh( void ) const;
	unsigned long GetCountBone( void ) const;
	void SetIndexMaterial( int index, const int& value );
	void GetIndexMaterial( int index, int* pOut ) const;
	void SetIndexTexture( int index, const int& value );
	void GetIndexTexture( int index, int* pOut ) const;
	void SetMatrixBone( int index, const D3DXMATRIX& value );
	void GetMatrixBone( int index, D3DXMATRIX* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	ModelConvert( const ModelConvert& );
	ModelConvert operator=( const ModelConvert& );

	unsigned long				countMesh_;				// ���b�V����
	unsigned long				countBone_;				// �{�[����
	unsigned long*				pCountPolygon_;			// �|���S����
	IDirect3DVertexBuffer9**	ppVertexBuffer_;		// ���_�o�b�t�@
	int*						pIndexMaterial_;		// ���b�V���̃}�e���A���ԍ�
	int*						pIndexTexture_;			// ���b�V���̃e�N�X�`���ԍ�
	D3DXMATRIX*					pMatrixBone_;			// �{�[���̏����p���s��
};

#endif	// MY_MODEL_CONVERT_H
