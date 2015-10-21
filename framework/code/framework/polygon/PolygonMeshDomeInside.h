//==============================================================================
//
// File   : PolygonMeshDomeInside.h
// Brief  : �������b�V���h�[���|���S��
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_POLYGON_MESH_DOME_INSIDE_H
#define MY_POLYGON_MESH_DOME_INSIDE_H

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
class PolygonMeshDomeInside
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	PolygonMeshDomeInside( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~PolygonMeshDomeInside( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : int countCellX						: X�����Z����
	// Arg    : int countCellY						: Y�����Z����
	// Arg    : float radius						: ���a
	// Arg    : float lengthTextureX				: X�����e�N�X�`������
	// Arg    : float lengthTextureY				: Y�����e�N�X�`������
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice, int countCellX, int countCellY,
		float radius, float lengthTextureX, float lengthTextureY );

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
	// Arg    : int countCellY						: Y�����Z����
	// Arg    : float radius						: ���a
	// Arg    : float lengthTextureX				: X�����e�N�X�`������
	// Arg    : float lengthTextureY				: Y�����e�N�X�`������
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice, int countCellX, int countCellY,
		float radius, float lengthTextureX, float lengthTextureY );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : PolygonMeshDomeInside* pOut			: �R�s�[��A�h���X
	//==============================================================================
	int Copy( PolygonMeshDomeInside* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Draw( void );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	int GetCountVertex( void ) const;
	int GetCountIndex( void ) const;
	void GetSizeIndex( size_t* pOut ) const;
	int GetCountCellX( void ) const;
	int GetCountCellY( void ) const;
	void SetRadius( float value );
	float GetRadius( void ) const;
	void SetLengthTextureX( float value );
	float GetLengthTextureX( void ) const;
	void SetLengthTextureY( float value );
	float GetLengthTextureY( void ) const;

protected:

private:
	void InitializeSelf( void );
	PolygonMeshDomeInside( const PolygonMeshDomeInside& );
	PolygonMeshDomeInside operator=( const PolygonMeshDomeInside& );

	IDirect3DDevice9*		pDevice_;				// Direct3D�f�o�C�X
	IDirect3DVertexBuffer9*	pVertexBuffer_;			// ���_�o�b�t�@
	IDirect3DIndexBuffer9*	pIndexBuffer_;			// �C���f�b�N�X�o�b�t�@
	Vertex*					pVertex_;				// ���_���
	int						countVertex_;			// ���_��
	int						countIndex_;			// �C���f�b�N�X��
	size_t					sizeIndex_;				// �C���f�b�N�X�̃T�C�Y
	int						countCellX_;			// X�����Z����
	int						countCellY_;			// Y�����Z����
	float					radius_;				// ���a
	float					lengthTextureX_;		// X�����e�N�X�`������
	float					lengthTextureY_;		// Y�����e�N�X�`������
};

#endif	// MY_POLYGON_MESH_DOME_INSIDE_H
