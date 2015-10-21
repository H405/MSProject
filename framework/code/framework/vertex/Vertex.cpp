//==============================================================================
//
// File   : Vertex.cpp
// Brief  : ���_�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/14 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Vertex.h"

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
Vertex::Vertex( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Vertex::~Vertex( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : unsigned int element				: ���_�錾�v�f
//==============================================================================
int Vertex::Initialize( IDirect3DDevice9* pDevice, unsigned int element )
{
	// �����o�ϐ��̐ݒ�
	typeElement_ = element;

	// �v�f���𐔂���
	unsigned int	bitCheck;		// �m�F�p�r�b�g
	bitCheck = 1;
	for( int counterElement = 0; counterElement < TYPE_MAX; ++counterElement )
	{
		if( (element & bitCheck) != 0 )
		{
			++countElement_;
		}
		bitCheck <<= 1;
	}

	// �v�f���Ȃ���ΏI��
	if( countElement_ <= 0 )
	{
		return 0;
	}

	// ���_�錾�v�f�̊i�[�̈���m��
	pElement_ = new D3DVERTEXELEMENT9[ countElement_ + 1 ];
	for( int counterElement = 0; counterElement < countElement_ + 1; ++counterElement )
	{
		pElement_[ counterElement ].Stream = 0;
		pElement_[ counterElement ].Method = D3DDECLMETHOD_DEFAULT;
	}
	pElement_[ countElement_ ].Stream = 0xFF;
	pElement_[ countElement_ ].Offset = 0;
	pElement_[ countElement_ ].Type = D3DDECLTYPE_UNUSED;
	pElement_[ countElement_ ].Usage = 0;
	pElement_[ countElement_ ].UsageIndex = 0;

	// �I�t�Z�b�g�ƒ��_�錾�v�f�̐���
	int		indexCurrent;					// ���݂̔ԍ�
	int		offsetCurrent;					// ���݂̃I�t�Z�b�g
	int		pType[ TYPE_MAX ] =				// �f�[�^�^
	{
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_UBYTE4,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT1,
		D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT1,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_D3DCOLOR,
		D3DDECLTYPE_D3DCOLOR,
		D3DDECLTYPE_FLOAT1,
		D3DDECLTYPE_FLOAT1,
		D3DDECLTYPE_FLOAT1
	};
	int		pUsage[ TYPE_MAX ] =			// �g�p���@
	{
		D3DDECLUSAGE_POSITION,
		D3DDECLUSAGE_POSITION,
		D3DDECLUSAGE_BLENDWEIGHT,
		D3DDECLUSAGE_BLENDINDICES,
		D3DDECLUSAGE_NORMAL,
		D3DDECLUSAGE_NORMAL,
		D3DDECLUSAGE_PSIZE,
		D3DDECLUSAGE_TEXCOORD,
		D3DDECLUSAGE_TEXCOORD,
		D3DDECLUSAGE_TEXCOORD,
		D3DDECLUSAGE_TEXCOORD,
		D3DDECLUSAGE_TANGENT,
		D3DDECLUSAGE_BINORMAL,
		D3DDECLUSAGE_TESSFACTOR,
		D3DDECLUSAGE_POSITIONT,
		D3DDECLUSAGE_COLOR,
		D3DDECLUSAGE_COLOR,
		D3DDECLUSAGE_FOG,
		D3DDECLUSAGE_DEPTH,
		D3DDECLUSAGE_SAMPLE
	};
	int		pUsageIndex[ TYPE_MAX ] =		// �g�p���@�ԍ�
	{
		0,
		1,
		0,
		0,
		0,
		1,
		0,
		0,
		1,
		2,
		3,
		0,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0
	};
	int		pOffset[ TYPE_MAX ] =			// �I�t�Z�b�g��
	{
		12,
		12,
		12,
		4,
		12,
		12,
		4,
		8,
		8,
		8,
		8,
		12,
		12,
		4,
		12,
		4,
		4,
		4,
		4,
		4
	};
	indexCurrent = 0;
	offsetCurrent = 0;
	bitCheck = 1;
	for( int counterElement = 0; counterElement < TYPE_MAX; ++counterElement, bitCheck <<= 1 )
	{
		// �v�f���܂܂�Ă��Ȃ��Ȃ玟��
		if( (element & bitCheck) == 0 )
		{
			continue;
		}

		// �v�f�̐ݒ�
		pElement_[ indexCurrent ].Offset = offsetCurrent;
		pElement_[ indexCurrent ].Type = pType[ counterElement ];
		pElement_[ indexCurrent ].Usage = pUsage[ counterElement ];
		pElement_[ indexCurrent ].UsageIndex = pUsageIndex[ counterElement ];

		// �i�[����v�f�ԍ������֐i�߂�
		++indexCurrent;

		// �I�t�Z�b�g���v�Z
		pOffsetElement_[ counterElement ] = offsetCurrent;
		offsetCurrent += pOffset[ counterElement ];
	}
	size_ = offsetCurrent;

	// ���_�錾
	HRESULT	result;		// ���s����
	result = pDevice->CreateVertexDeclaration( pElement_, &pDeclaration_ );
	if( result != S_OK )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Vertex::Finalize( void )
{
	// ���_�錾�̊J��
	if( pDeclaration_ != nullptr )
	{
		pDeclaration_->Release();
		pDeclaration_ = nullptr;
	}

	// �i�[�̈�̊J��
	delete[] pElement_;
	pElement_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : unsigned int element				: ���_�錾�v�f
//==============================================================================
int Vertex::Reinitialize( IDirect3DDevice9* pDevice, unsigned int element )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice, element );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : Vertex* pOut						: �R�s�[��A�h���X
//==============================================================================
int Vertex::Copy( Vertex* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���_�錾�v�f���܂�ł��邩����
// Return : bool								: ���茋��
// Arg    : int type							: ���_�錾�v�f�̎��
//==============================================================================
bool Vertex::IsContent( int type ) const
{
	// �r�b�g�̐���
	int		bitCheck;		// �m�F�p�r�b�g
	bitCheck = 1;
	for( int loop = 0; loop < type; ++loop )
	{
		bitCheck <<= 1;
	}

	// �l�̕ԋp
	return (typeElement_ & bitCheck) != 0;
}

//==============================================================================
// Brief  : ���_�錾�v�f�̃I�t�Z�b�g���擾
// Return : int									: �I�t�Z�b�g
// Arg    : int type							: ���_�錾�v�f�̎��
//==============================================================================
int Vertex::GetOffset( int type ) const
{
	// �l�̕ԋp
	return pOffsetElement_[ type ];
}

//==============================================================================
// Brief  : �\���̂̃T�C�Y�̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int Vertex::GetSize( void ) const
{
	// �l�̕ԋp
	return size_;
}

//==============================================================================
// Brief  : ���_�錾�v�f�̎擾
// Return : D3DVERTEXELEMENT9*					: ���_�錾�̐擪�A�h���X
// Arg    : void								: �Ȃ�
//==============================================================================
D3DVERTEXELEMENT9* Vertex::GetElement( void ) const
{
	// �l�̕ԋp
	return pElement_;
}

//==============================================================================
// Brief  : ���_�錾�̎擾
// Return : IDirect3DVertexDeclaration9*		: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DVertexDeclaration9* Vertex::GetDeclaration( void ) const
{
	// �l�̕ԋp
	return pDeclaration_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Vertex::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	countElement_ = 0;
	size_ = 0;
	pElement_ = nullptr;
	for( int counterElement = 0; counterElement < TYPE_MAX; ++counterElement )
	{
		pOffsetElement_[ counterElement ] = 0;
	}
	typeElement_ = 0;
	pDeclaration_ = nullptr;
}
