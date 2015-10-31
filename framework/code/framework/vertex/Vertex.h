//==============================================================================
//
// File   : Vertex.h
// Brief  : ���_�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/14 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_VERTEX_H
#define MY_VERTEX_H

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

//******************************************************************************
// �N���X��`
//******************************************************************************
class Vertex
{
public:
	// ���_�錾�v�f�l
	enum
	{
		ELEMENT_NONE				= 0x00000000,		// �Ȃ�
		ELEMENT_POSITION			= 0x00000001,		// ���W
		ELEMENT_POSITION_TWEENING	= 0x00000002,		// �g�D�E�B�[�j���O�p���W
		ELEMENT_BLEND_WEIGHT		= 0x00000004,		// �u�����h����
		ELEMENT_BLEND_INDICIES		= 0x00000008,		// �u�����h���_�ԍ�
		ELEMENT_NORMAL				= 0x00000010,		// �@��
		ELEMENT_NORMAL_TWEENING		= 0x00000020,		// �g�D�E�B�[�j���O�p�@��
		ELEMENT_POINT_SIZE			= 0x00000040,		// �|�C���g�X�v���C�g�̃T�C�Y
		ELEMENT_TEXTURE_COORD_0		= 0x00000080,		// �e�N�X�`�����W0
		ELEMENT_TEXTURE_COORD_1		= 0x00000100,		// �e�N�X�`�����W1
		ELEMENT_TEXTURE_COORD_2		= 0x00000200,		// �e�N�X�`�����W2
		ELEMENT_TEXTURE_COORD_3		= 0x00000400,		// �e�N�X�`�����W3
		ELEMENT_TANGENT				= 0x00000800,		// �ڐ�
		ELEMENT_BINORMAL			= 0x00001000,		// �]�@��
		ELEMENT_TESSELLATION_FACTOR	= 0x00002000,		// �e�b�Z���[�V�����W��
		ELEMENT_POSITION_TRANSFORM	= 0x00004000,		// �ϊ��ςݒ��_
		ELEMENT_COLOR_DIFFUSE		= 0x00008000,		// �f�B�t���[�Y�J���[
		ELEMENT_COLOR_SPECULAR		= 0x00010000,		// �X�y�L�����J���[
		ELEMENT_FOG					= 0x00020000,		// �t�H�O
		ELEMENT_DEPTH				= 0x00040000,		// �[�x�l
		ELEMENT_SAMPLER				= 0x00080000,		// �T���v�����
		ELEMENT_END					= 0xFFFFFFFF		// �Ō�
	};

	// ���_�錾�v�f�̑g
	enum
	{
		ELEMENT_SET_SIMPLE		= ELEMENT_POSITION | ELEMENT_NORMAL | ELEMENT_TEXTURE_COORD_0 | ELEMENT_COLOR_DIFFUSE,								// �ʏ�Z�b�g
		ELEMENT_SET_NORMAL_MAP	= ELEMENT_POSITION | ELEMENT_NORMAL | ELEMENT_TEXTURE_COORD_0 | ELEMENT_TANGENT | ELEMENT_COLOR_DIFFUSE,			// �@���}�b�v�Z�b�g
		ELEMENT_SET_POINT		= ELEMENT_POSITION | ELEMENT_POINT_SIZE | ELEMENT_COLOR_DIFFUSE,													// �|�C���g�X�v���C�g�Z�b�g
		ELEMENT_SET_SKIN		= ELEMENT_POSITION | ELEMENT_BLEND_WEIGHT | ELEMENT_BLEND_INDICIES | ELEMENT_NORMAL | ELEMENT_TEXTURE_COORD_0,		// �X�L�����b�V���Z�b�g
		ELEMENT_SET_END
	};

	// ���_�錾�v�f�̎��
	enum
	{
		TYPE_POSITION = 0,			// ���W
		TYPE_POSITION_TWEENING,		// �g�D�E�B�[�j���O�p���W
		TYPE_BLEND_WEIGHT,			// �u�����h����
		TYPE_BLEND_INDICIES,		// �u�����h���_�ԍ�
		TYPE_NORMAL,				// �@��
		TYPE_NORMAL_TWEENING,		// �g�D�E�B�[�j���O�p�@��
		TYPE_POINT_SIZE,			// �|�C���g�X�v���C�g�̃T�C�Y
		TYPE_TEXTURE_COORD_0,		// �e�N�X�`�����W0
		TYPE_TEXTURE_COORD_1,		// �e�N�X�`�����W1
		TYPE_TEXTURE_COORD_2,		// �e�N�X�`�����W2
		TYPE_TEXTURE_COORD_3,		// �e�N�X�`�����W3
		TYPE_TANGENT,				// �ڐ�
		TYPE_BINORMAL,				// �]�@��
		TYPE_TESSELLATION_FACTOR,	// �e�b�Z���[�V�����W��
		TYPE_POSITION_TRANSFORM,	// �ϊ��ςݒ��_
		TYPE_COLOR_DIFFUSE,			// �f�B�t���[�Y�J���[
		TYPE_COLOR_SPECULAR,		// �X�y�L�����J���[
		TYPE_FOG,					// �t�H�O
		TYPE_DEPTH,					// �[�x�l
		TYPE_SAMPLER,				// �T���v�����
		TYPE_MAX					// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	Vertex( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~Vertex( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : unsigned int element				: ���_�錾�v�f
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice, unsigned int element );

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
	// Arg    : unsigned int element				: ���_�錾�v�f
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice, unsigned int element );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : Vertex* pOut						: �R�s�[��A�h���X
	//==============================================================================
	int Copy( Vertex* pOut ) const;

	//==============================================================================
	// Brief  : ���_�錾�v�f���܂�ł��邩����
	// Return : bool								: ���茋��
	// Arg    : int type							: ���_�錾�v�f�̎��
	//==============================================================================
	bool IsContent( int type ) const;

	//==============================================================================
	// Brief  : ���_�錾�v�f�̃I�t�Z�b�g���擾
	// Return : int									: �I�t�Z�b�g
	// Arg    : int type							: ���_�錾�v�f�̎��
	//==============================================================================
	int GetOffset( int type ) const;

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	int GetSize( void ) const;
	D3DVERTEXELEMENT9* GetElement( void ) const;
	IDirect3DVertexDeclaration9* GetDeclaration( void ) const;

protected:

private:
	void InitializeSelf( void );
	Vertex( const Vertex& );
	Vertex operator=( const Vertex& );

	int								countElement_;						// ���_�錾�v�f��
	int								size_;								// �\���̂̃T�C�Y
	D3DVERTEXELEMENT9*				pElement_;							// ���_�錾�v�f
	int								pOffsetElement_[ TYPE_MAX ];		// ���_�錾�v�f�̃I�t�Z�b�g
	unsigned int					typeElement_;						// ���_�錾�v�f
	IDirect3DVertexDeclaration9*	pDeclaration_;						// ���_�錾
};

#endif	// MY_VERTEX_H
