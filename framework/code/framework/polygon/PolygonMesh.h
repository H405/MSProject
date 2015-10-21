//==============================================================================
//
// File   : PolygonMesh.h
// Brief  : ���b�V���|���S��
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_POLYGON_MESH_H
#define MY_POLYGON_MESH_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "d3dx9.h"

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
class PolygonMesh
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	PolygonMesh( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~PolygonMesh( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : int countCellX						: X�����Z����
	// Arg    : int countCellZ						: Z�����Z����
	// Arg    : float lengthCellX					: X�����Z������
	// Arg    : float lengthCellZ					: Z�����Z������
	// Arg    : float lengthTextureX				: X�����e�N�X�`������
	// Arg    : float lengthTextureZ				: Z�����e�N�X�`������
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
		float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ );

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
	// Arg    : int countCellX						: X�����Z����
	// Arg    : int countCellZ						: Z�����Z����
	// Arg    : float lengthCellX					: X�����Z������
	// Arg    : float lengthCellZ					: Z�����Z������
	// Arg    : float lengthTextureX				: X�����e�N�X�`������
	// Arg    : float lengthTextureZ				: Z�����e�N�X�`������
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
		float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : PolygonMesh* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( PolygonMesh* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Draw( void );

	//==============================================================================
	// Brief  : �����̐ݒ�
	// Return : int									: ���s����
	// Arg    : float* pHeight						: �������
	//==============================================================================
	int SetHeight( float* pHeight );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	int GetCountVertex( void ) const;
	int GetCountIndex( void ) const;
	void GetSizeIndex( size_t* pOut ) const;
	int GetCountCellX( void ) const;
	int GetCountCellZ( void ) const;
	void SetLengthCellX( float value );
	float GetLengthCellX( void ) const;
	void SetLengthCellZ( float value );
	float GetLengthCellZ( void ) const;
	void SetLengthTextureX( float value );
	float GetLengthTextureX( void ) const;
	void SetLengthTextureZ( float value );
	float GetLengthTextureZ( void ) const;

protected:

private:
	void InitializeSelf( void );
	PolygonMesh( const PolygonMesh& );
	PolygonMesh operator=( const PolygonMesh& );

	IDirect3DDevice9*		pDevice_;				// Direct3D�f�o�C�X
	IDirect3DVertexBuffer9*	pVertexBuffer_;			// ���_�o�b�t�@
	IDirect3DIndexBuffer9*	pIndexBuffer_;			// �C���f�b�N�X�o�b�t�@
	Vertex*					pVertex_;				// ���_���
	int						countVertex_;			// ���_��
	int						countIndex_;			// �C���f�b�N�X��
	size_t					sizeIndex_;				// �C���f�b�N�X�̃T�C�Y
	int						countCellX_;			// X�����Z����
	int						countCellZ_;			// Z�����Z����
	float					lengthCellX_;			// X�����Z������
	float					lengthCellZ_;			// Z�����Z������
	float					lengthTextureX_;		// X�����e�N�X�`������
	float					lengthTextureZ_;		// Z�����e�N�X�`������
};

#endif	// MY_POLYGON_MESH_H
