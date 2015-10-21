//==============================================================================
//
// File   : VertexBuffer.cpp
// Brief  : ���_�o�b�t�@�֒l��ݒ肷�邽�߂̃o�b�t�@
// Author : Taiga Shirakawa
// Date   : 2015/10/14 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "VertexBuffer.h"
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
VertexBuffer::VertexBuffer( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
VertexBuffer::~VertexBuffer( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int count							: �m�ۂ��鐔
// Arg    : Vertex* pVertex						: ���_���
//==============================================================================
int VertexBuffer::Initialize( int count, Vertex* pVertex )
{
	// �����o�ϐ��̐ݒ�
	pVertex_ = pVertex;

	// �o�b�t�@�̊m��
	int		sizeItem;		// �\���̂̃T�C�Y
	sizeItem = pVertex->GetSize();
	size_ = static_cast< unsigned int >( sizeItem * count );
	pBuffer_ = new char[ size_ ];
	if( pBuffer_ == nullptr )
	{
		return 1;
	}
	ZeroMemory( pBuffer_, size_ );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int VertexBuffer::Finalize( void )
{
	// �o�b�t�@�̊J��
	delete[] pBuffer_;
	pBuffer_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int count							: �m�ۂ��鐔
// Arg    : Vertex* pVertex						: ���_���
//==============================================================================
int VertexBuffer::Reinitialize( int count, Vertex* pVertex )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( count, pVertex );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : VertexBuffer* pOut					: �R�s�[��A�h���X
//==============================================================================
int VertexBuffer::Copy( VertexBuffer* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �o�b�t�@�̎擾
// Return : void*								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
void* VertexBuffer::GetBuffer( void ) const
{
	// �l�̕ԋp
	return pBuffer_;
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetPosition( int index, const D3DXVECTOR3& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_POSITION, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetPosition( int index, float x, float y, float z )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_POSITION, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : ���W��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetPositionX( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_POSITION, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : ���W��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetPositionY( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_POSITION, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : ���W��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetPositionZ( int index, float z )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_POSITION, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �g�D�E�B�[�j���O�p���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetPositionTweening( int index, const D3DXVECTOR3& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_POSITION_TWEENING, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �g�D�E�B�[�j���O�p���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetPositionTweening( int index, float x, float y, float z )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_POSITION_TWEENING, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �g�D�E�B�[�j���O�p���W��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetPositionTweeningX( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_POSITION_TWEENING, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : �g�D�E�B�[�j���O�p���W��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetPositionTweeningY( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_POSITION_TWEENING, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : �g�D�E�B�[�j���O�p���W��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetPositionTweeningZ( int index, float z )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_POSITION_TWEENING, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �u�����h�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetBlendWeight( int index, const D3DXVECTOR3& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_BLEND_WEIGHT, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �u�����h�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetBlendWeight( int index, float x, float y, float z )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_BLEND_WEIGHT, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �u�����h������X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetBlendWeightX( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_BLEND_WEIGHT, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : �u�����h������Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetBlendWeightY( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_BLEND_WEIGHT, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : �u�����h������Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetBlendWeightZ( int index, float z )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_BLEND_WEIGHT, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �u�����h���_�ԍ��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : unsigned long value					: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetBlendIndecies( int index, unsigned char value0, unsigned char value1, unsigned char value2, unsigned char value3 )
{
	// �o�b�t�@�ɐݒ�
	unsigned char	pBufferSet[ 4 ];
	pBufferSet[ 0 ] = value0;
	pBufferSet[ 1 ] = value1;
	pBufferSet[ 2 ] = value2;
	pBufferSet[ 3 ] = value3;
	SetToBuffer( index, Vertex::TYPE_BLEND_INDICIES, pBufferSet, sizeof( unsigned char ) * 4 );
}

//==============================================================================
// Brief  : �u�����h���_�ԍ��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : unsigned char value					: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetBlendIndecies0( int index, unsigned char value )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_BLEND_INDICIES, &value, sizeof( unsigned char ) );
}

//==============================================================================
// Brief  : �u�����h���_�ԍ��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : unsigned char value					: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetBlendIndecies1( int index, unsigned char value )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_BLEND_INDICIES, &value, sizeof( unsigned char ), sizeof( unsigned char ) );
}

//==============================================================================
// Brief  : �u�����h���_�ԍ��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : unsigned char value					: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetBlendIndecies2( int index, unsigned char value )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_BLEND_INDICIES, &value, sizeof( unsigned char ), sizeof( unsigned char ) * 2 );
}

//==============================================================================
// Brief  : �u�����h���_�ԍ��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : unsigned char value					: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetBlendIndecies3( int index, unsigned char value )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_BLEND_INDICIES, &value, sizeof( unsigned char ), sizeof( unsigned char ) * 3 );
}

//==============================================================================
// Brief  : �@���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetNormal( int index, const D3DXVECTOR3& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_NORMAL, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �@���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetNormal( int index, float x, float y, float z )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_NORMAL, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �@����X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetNormalX( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_NORMAL, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : �@����Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetNormalY( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_NORMAL, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : �@����Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetNormalZ( int index, float z )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_NORMAL, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �g�D�E�B�[�j���O�p�@���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetNormalTweening( int index, const D3DXVECTOR3& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_NORMAL_TWEENING, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �g�D�E�B�[�j���O�p�@���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetNormalTweening( int index, float x, float y, float z )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_NORMAL_TWEENING, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �g�D�E�B�[�j���O�p�@����X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetNormalTweeningX( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_NORMAL_TWEENING, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : �g�D�E�B�[�j���O�p�@����Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetNormalTweeningY( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_NORMAL_TWEENING, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : �g�D�E�B�[�j���O�p�@����Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetNormalTweeningZ( int index, float z )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_NORMAL_TWEENING, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �|�C���g�X�v���C�g�T�C�Y�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetPointSize( int index, float value )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_POINT_SIZE, &value, sizeof( float ) );
}

//==============================================================================
// Brief  : �e�N�X�`�����W0�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR2& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetTextureCoord0( int index, const D3DXVECTOR2& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_0, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �e�N�X�`�����W0�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetTextureCoord0( int index, float x, float y )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_0, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �e�N�X�`�����W0��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetTextureCoord0X( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_0, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : �e�N�X�`�����W0��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetTextureCoord0Y( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_0, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : �e�N�X�`�����W1�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR2& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetTextureCoord1( int index, const D3DXVECTOR2& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_1, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �e�N�X�`�����W1�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetTextureCoord1( int index, float x, float y )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_1, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �e�N�X�`�����W1��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetTextureCoord1X( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_1, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : �e�N�X�`�����W1��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetTextureCoord1Y( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_1, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : �e�N�X�`�����W2�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR2& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetTextureCoord2( int index, const D3DXVECTOR2& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_2, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �e�N�X�`�����W2�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetTextureCoord2( int index, float x, float y )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_2, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �e�N�X�`�����W2��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetTextureCoord2X( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_2, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : �e�N�X�`�����W2��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetTextureCoord2Y( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_2, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : �e�N�X�`�����W3�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR2& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetTextureCoord3( int index, const D3DXVECTOR2& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_3, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �e�N�X�`�����W3�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetTextureCoord3( int index, float x, float y )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_3, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �e�N�X�`�����W3��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetTextureCoord3X( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_3, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : �e�N�X�`�����W3��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetTextureCoord3Y( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_3, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : �ڐ��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetTangent( int index, const D3DXVECTOR3& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_TANGENT, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �ڐ��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetTangent( int index, float x, float y, float z )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_TANGENT, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �ڐ���X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetTangentX( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TANGENT, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : �ڐ���Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetTangentY( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TANGENT, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : �ڐ���Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetTangentZ( int index, float z )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TANGENT, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �]�@���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetBinormal( int index, const D3DXVECTOR3& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_BINORMAL, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �]�@���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetBinormal( int index, float x, float y, float z )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_BINORMAL, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �]�@����X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetBinormalX( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_BINORMAL, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : �]�@����Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetBinormalY( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_BINORMAL, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : �]�@����Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetBinormalZ( int index, float z )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_BINORMAL, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �e�b�Z���[�V�����W���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetTessellationFactor( int index, float value )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_TESSELLATION_FACTOR, &value, sizeof( float ) );
}

//==============================================================================
// Brief  : �ϊ��ςݒ��_�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetPositionTransform( int index, const D3DXVECTOR3& value )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_POSITION_TRANSFORM, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �ϊ��ςݒ��_�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetPositionTransform( int index, float x, float y, float z )
{
	// �o�b�t�@�ɐݒ�
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_POSITION_TRANSFORM, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : �ϊ��ςݒ��_��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float x								: X�l
//==============================================================================
void VertexBuffer::SetPositionTransformX( int index, float x )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_POSITION_TRANSFORM, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : �ϊ��ςݒ��_��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float y								: Y�l
//==============================================================================
void VertexBuffer::SetPositionTransformY( int index, float y )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_POSITION_TRANSFORM, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : �ϊ��ςݒ��_��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float z								: Z�l
//==============================================================================
void VertexBuffer::SetPositionTransformZ( int index, float z )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_POSITION_TRANSFORM, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : �f�B�t���[�Y�J���[�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXCOLOR& value				: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetColorDiffuse( int index, const D3DXCOLOR& value )
{
	// �o�b�t�@�ɐݒ�
	D3DXCOLOR	color;			// �F
	D3DCOLOR	colorSet;		// �ݒ肷��F
	color.r = value.r;
	color.g = value.g;
	color.b = value.b;
	color.a = value.a;
	colorSet = color;
	SetToBuffer( index, Vertex::TYPE_COLOR_DIFFUSE, &colorSet, sizeof( DWORD ) );
}

//==============================================================================
// Brief  : �f�B�t���[�Y�J���[��RGBA�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void VertexBuffer::SetColorDiffuse( int index, float r, float g, float b, float a )
{
	// �o�b�t�@�ɐݒ�
	D3DXCOLOR	color;			// �F
	D3DCOLOR	colorSet;		// �ݒ肷��F
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	colorSet = color;
	SetToBuffer( index, Vertex::TYPE_COLOR_DIFFUSE, &colorSet, sizeof( DWORD ) );
}

//==============================================================================
// Brief  : �X�y�L�����J���[�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXCOLOR& value				: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetColorSpecular( int index, const D3DXCOLOR& value )
{
	// �o�b�t�@�ɐݒ�
	D3DXCOLOR	color;			// �F
	D3DCOLOR	colorSet;		// �ݒ肷��F
	color.r = value.r;
	color.g = value.g;
	color.b = value.b;
	color.a = value.a;
	colorSet = color;
	SetToBuffer( index, Vertex::TYPE_COLOR_SPECULAR, &colorSet, sizeof( DWORD ) );
}

//==============================================================================
// Brief  : �X�y�L�����J���[��RGBA�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void VertexBuffer::SetColorSpecular( int index, float r, float g, float b, float a )
{
	// �o�b�t�@�ɐݒ�
	D3DXCOLOR	color;			// �F
	D3DCOLOR	colorSet;		// �ݒ肷��F
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	colorSet = color;
	SetToBuffer( index, Vertex::TYPE_COLOR_SPECULAR, &colorSet, sizeof( DWORD ) );
}

//==============================================================================
// Brief  : �t�H�O���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetFog( int index, float value )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_FOG, &value, sizeof( float ) );
}

//==============================================================================
// Brief  : �[�x���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetDepth( int index, float value )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_DEPTH, &value, sizeof( float ) );
}

//==============================================================================
// Brief  : �T���v�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void VertexBuffer::SetSampler( int index, float value )
{
	// �o�b�t�@�ɐݒ�
	SetToBuffer( index, Vertex::TYPE_SAMPLER, &value, sizeof( float ) );
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void VertexBuffer::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pBuffer_ = nullptr;
	size_ = 0;
	pVertex_ = nullptr;
}

//==============================================================================
// Brief  : �o�b�t�@�֒l��ݒ�
// Return : void								: �Ȃ�
// Arg    : int type							: �v�f�̎��
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : void* pValue						: �ݒ肷��l
// Arg    : size_t size							: �ݒ肷��T�C�Y
// Arg    : int offset							: �ǉ��̃I�t�Z�b�g
//==============================================================================
void VertexBuffer::SetToBuffer( int index, int type, void* pValue, size_t size, int offset )
{
	// �v�f���܂܂�Ă��邩�m�F
	if( !pVertex_->IsContent( type ) )
	{
		return;
	}

	// �ݒ肷�邽�߂̏����擾
	int		sizeItem;			// �\���̂̃T�C�Y
	int		offsetBegin;		// �J�n�I�t�Z�b�g
	sizeItem = pVertex_->GetSize();
	offsetBegin = pVertex_->GetOffset( type );

	// �o�b�t�@�ɐݒ�
	unsigned int	offsetTotal;		// ���I�t�Z�b�g
	offsetTotal = sizeItem * index + offsetBegin + offset;
	memcpy_s( &pBuffer_[ offsetTotal ], size_ - offsetTotal, pValue, size );
}
