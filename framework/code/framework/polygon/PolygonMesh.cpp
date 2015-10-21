//==============================================================================
//
// File   : PolygonMesh.cpp
// Brief  : ���b�V���|���S��
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "PolygonMesh.h"
#include "../vertex/Vertex.h"
#include "../vertex/VertexBuffer.h"

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
PolygonMesh::PolygonMesh( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
PolygonMesh::~PolygonMesh( void )
{
	// �I������
	Finalize();
}

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
int PolygonMesh::Initialize( IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
	float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ )
{
	// �����o�ϐ��̐ݒ�
	pDevice_ = pDevice;
	countCellX_ = countCellX;
	countCellZ_ = countCellZ;
	lengthCellX_ = lengthCellX;
	lengthCellZ_ = lengthCellZ;
	lengthTextureX_ = lengthTextureX;
	lengthTextureZ_ = lengthTextureZ;

	// ���_�ƃC���f�b�N�X�̐����v�Z
	int		countVertexX;		// X�������_��
	int		countVertexZ;		// Z�������_��
	countVertexX = countCellX + 1;
	countVertexZ = countCellZ + 1;
	countVertex_ = countVertexX * countVertexZ;
	countIndex_ = 2 * countVertexX * (countVertexZ - 1) + 2 * (countVertexZ - 2);

	// �C���f�b�N�X�̃T�C�Y������
	sizeIndex_ = (countVertexX > USHRT_MAX ? sizeof( DWORD ) : sizeof( WORD ));

	// ���_���̐���
	int		result;		// ���s����
	pVertex_ = new Vertex();
	if( pVertex_ == nullptr )
	{
		return 1;
	}
	result = pVertex_->Initialize( pDevice, Vertex::ELEMENT_SET_SIMPLE );
	if( result != 0 )
	{
		return result;
	}

	// ���_�o�b�t�@�����쐬
	VertexBuffer	buffer;		// ���_�o�b�t�@���
	buffer.Initialize( countVertex_, pVertex_ );
	for( int counterVertexZ = 0; counterVertexZ < countVertexZ; ++counterVertexZ )
	{
		for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
		{
			int		indexVertex;		// ���_�̔ԍ�
			indexVertex = countVertexX * counterVertexZ + counterVertexX;
			buffer.SetPosition( indexVertex, lengthCellX * (counterVertexX - countCellX / 2.0f), 0.0f, lengthCellZ * (counterVertexZ - countCellZ / 2.0f) );
			buffer.SetNormal( indexVertex, 0.0f, 1.0f, 0.0f );
			buffer.SetTextureCoord0( indexVertex, lengthTextureX * counterVertexX, lengthTextureZ * counterVertexZ );
			buffer.SetColorDiffuse( indexVertex, 1.0f, 1.0f, 1.0f, 1.0f );
		}
	}

	// ���_�o�b�t�@�̐���
	int		sizeVertex;		// ���_�̃T�C�Y
	sizeVertex = pVertex_->GetSize();
	result = pDevice->CreateVertexBuffer( sizeVertex * countVertex_, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &pVertexBuffer_, nullptr );
	if( result != 0 )
	{
		return result;
	}

	// ���_�o�b�t�@�ɒl��ݒ�
	void*	pBufferAddress = nullptr;		// �o�b�t�@�̃A�h���X
	pVertexBuffer_->Lock( 0, 0, &pBufferAddress, 0 );
	memcpy_s( pBufferAddress, sizeVertex * countVertex_, buffer.GetBuffer(), sizeVertex * countVertex_ );
	pVertexBuffer_->Unlock();

	// �C���f�b�N�X�o�b�t�@�̍쐬
	result = pDevice->CreateIndexBuffer( sizeIndex_ * countIndex_, D3DUSAGE_WRITEONLY,
		(sizeIndex_ == sizeof( DWORD ) ? D3DFMT_INDEX32 : D3DFMT_INDEX16), D3DPOOL_MANAGED, &pIndexBuffer_, NULL );
	if( result != S_OK )
	{
		return result;
	}

	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	if( sizeIndex_ == sizeof( DWORD ) )
	{
		// �C���f�b�N�X�o�b�t�@�X�V�J�n
		DWORD	*pIndex = nullptr;	// ���������p�C���f�b�N�X�o�b�t�@�A�h���X
		pIndexBuffer_->Lock( 0, 0, (void**)&pIndex, 0 );

		// �C���f�b�N�X���ݒ�
		for( int counterVertexZ = 0; counterVertexZ < countVertexZ - 1; ++counterVertexZ )
		{
			for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
			{
				pIndex[ (2 * countVertexX + 2) * counterVertexZ + 2 * counterVertexX + 0 ] = static_cast< DWORD >( countVertexX * (counterVertexZ + 0) + counterVertexX );
				pIndex[ (2 * countVertexX + 2) * counterVertexZ + 2 * counterVertexX + 1 ] = static_cast< DWORD >( countVertexX * (counterVertexZ + 1) + counterVertexX );
			}
		}
		for( int counterVertexZ = 0; counterVertexZ < countVertexZ - 2; ++counterVertexZ )
		{
			pIndex[ (2 * countVertexX + 2) * (counterVertexZ + 1) - 2 ] = static_cast< DWORD >( countVertexX * (counterVertexZ + 1) + countVertexX - 1 );
			pIndex[ (2 * countVertexX + 2) * (counterVertexZ + 1) - 1 ] = static_cast< DWORD >( countVertexX * (counterVertexZ + 1) );
		}
	}
	else
	{
		// �C���f�b�N�X�o�b�t�@�X�V�J�n
		WORD	*pIndex = nullptr;		// ���������p�C���f�b�N�X�o�b�t�@�A�h���X
		pIndexBuffer_->Lock( 0, 0, (void**)&pIndex, 0 );

		// �C���f�b�N�X���ݒ�
		for( int counterVertexZ = 0; counterVertexZ < countVertexZ - 1; ++counterVertexZ )
		{
			for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
			{
				pIndex[ (2 * countVertexX + 2) * counterVertexZ + 2 * counterVertexX + 0 ] = static_cast< WORD >( countVertexX * (counterVertexZ + 0) + counterVertexX );
				pIndex[ (2 * countVertexX + 2) * counterVertexZ + 2 * counterVertexX + 1 ] = static_cast< WORD >( countVertexX * (counterVertexZ + 1) + counterVertexX );
			}
		}
		for( int counterVertexZ = 0; counterVertexZ < countVertexZ - 2; ++counterVertexZ )
		{
			pIndex[ (2 * countVertexX + 2) * (counterVertexZ + 1) - 2 ] = static_cast< WORD >( countVertexX * (counterVertexZ + 1) + countVertexX - 1 );
			pIndex[ (2 * countVertexX + 2) * (counterVertexZ + 1) - 1 ] = static_cast< WORD >( countVertexX * (counterVertexZ + 1) );
		}
	}

	// �C���f�b�N�X�o�b�t�@�X�V�I��
	pIndexBuffer_->Unlock();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int PolygonMesh::Finalize( void )
{
	// ���_�o�b�t�@�̊J��
	if( pVertexBuffer_ != nullptr )
	{
		pVertexBuffer_->Release();
		pVertexBuffer_ = nullptr;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if( pIndexBuffer_ != nullptr )
	{
		pIndexBuffer_->Release();
		pIndexBuffer_ = nullptr;
	}

	// ���_���̊J��
	delete pVertex_;
	pVertex_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

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
int PolygonMesh::Reinitialize( IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
	float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice, countCellX, countCellZ, lengthCellX, lengthCellZ, lengthTextureX, lengthTextureZ );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : PolygonMesh* pOut					: �R�s�[��A�h���X
//==============================================================================
int PolygonMesh::Copy( PolygonMesh* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`�揈��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PolygonMesh::Draw( void )
{
	// �`��
	pDevice_->SetStreamSource( 0, pVertexBuffer_, 0, pVertex_->GetSize() );
	pDevice_->SetIndices( pIndexBuffer_ );
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pDevice_->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, countVertex_, 0, countIndex_ - 2 );
}

//==============================================================================
// Brief  : �����̐ݒ�
// Return : int									: ���s����
// Arg    : float* pHeight						: �������
//==============================================================================
int PolygonMesh::SetHeight( float* pHeight )
{
	// ���_�̐����v�Z
	int		countVertexX;		// X�������_��
	int		countVertexZ;		// Z�������_��
	countVertexX = countCellX_ + 1;
	countVertexZ = countCellZ_ + 1;

	// �@���o�b�t�@�m��
	D3DXVECTOR3*	pVectorNormal = nullptr;
	pVectorNormal = new D3DXVECTOR3[ countVertex_ ];
	if( pVectorNormal == NULL )
	{
		return 1;
	}
	ZeroMemory( pVectorNormal, sizeof( D3DXVECTOR3 ) * countVertex_ );

	// �@���̐ݒ�
	D3DXVECTOR3	pVectorNormalPlane[ 2 ];		// �@���x�N�g��
	D3DXVECTOR3	pVectorPlaneX[ 2 ];				// X�����x�N�g��
	D3DXVECTOR3	pVectorPlaneZ[ 2 ];				// Z�����x�N�g��
	for( int counterVertexZ = 1; counterVertexZ < countVertexZ - 1; ++counterVertexZ )
	{
		for( int counterVertexX = 1; counterVertexX < countVertexX - 1; ++counterVertexX )
		{
			pVectorPlaneX[ 0 ].x = -lengthCellX_;
			pVectorPlaneX[ 0 ].z = 0.0f;
			pVectorPlaneX[ 0 ].y = pHeight[ countVertexX * counterVertexZ + (counterVertexX + 1) ];
			pVectorPlaneZ[ 0 ].x = 0.0f;
			pVectorPlaneZ[ 0 ].z = lengthCellZ_;
			pVectorPlaneZ[ 0 ].y = pHeight[ countVertexX * (counterVertexZ + 1) + counterVertexX ];
			pVectorPlaneX[ 1 ].x = lengthCellX_;
			pVectorPlaneX[ 1 ].z = 0.0f;
			pVectorPlaneX[ 1 ].y = pHeight[ countVertexX * counterVertexZ + (counterVertexX - 1) ];
			pVectorPlaneZ[ 1 ].x = 0.0f;
			pVectorPlaneZ[ 1 ].z = -lengthCellZ_;
			pVectorPlaneZ[ 1 ].y = pHeight[ countVertexX * (counterVertexZ - 1) + counterVertexX ];
			pVectorPlaneX[ 0 ].y -= pHeight[ countVertexX * counterVertexZ + counterVertexX ];
			pVectorPlaneX[ 1 ].y -= pHeight[ countVertexX * counterVertexZ + counterVertexX ];
			pVectorPlaneZ[ 0 ].y -= pHeight[ countVertexX * counterVertexZ + counterVertexX ];
			pVectorPlaneZ[ 1 ].y -= pHeight[ countVertexX * counterVertexZ + counterVertexX ];
			D3DXVec3Normalize( &pVectorPlaneX[ 0 ], &pVectorPlaneX[ 0 ] );
			D3DXVec3Normalize( &pVectorPlaneX[ 1 ], &pVectorPlaneX[ 1 ] );
			D3DXVec3Normalize( &pVectorPlaneZ[ 0 ], &pVectorPlaneZ[ 0 ] );
			D3DXVec3Normalize( &pVectorPlaneZ[ 1 ], &pVectorPlaneZ[ 1 ] );
			D3DXVec3Cross( &pVectorNormalPlane[ 0 ], &pVectorPlaneX[ 0 ], &pVectorPlaneZ[ 0 ] );
			D3DXVec3Cross( &pVectorNormalPlane[ 1 ], &pVectorPlaneX[ 1 ], &pVectorPlaneZ[ 1 ] );
			D3DXVec3Normalize( &pVectorNormalPlane[ 0 ], &pVectorNormalPlane[ 0 ] );
			D3DXVec3Normalize( &pVectorNormalPlane[ 1 ], &pVectorNormalPlane[ 1 ] );
			pVectorNormalPlane[ 0 ] += pVectorNormalPlane[ 1 ];
			D3DXVec3Normalize( &pVectorNormalPlane[ 0 ], &pVectorNormalPlane[ 0 ] );
			pVectorNormal[ countVertexX * counterVertexZ + counterVertexX ] = pVectorNormalPlane[ 0 ];
		}
	}

	// �[�̖@���̐ݒ�
	for( int counterVertexZ = 1; counterVertexZ < countVertexZ - 1; ++counterVertexZ )
	{
		pVectorNormal[ countVertexX * counterVertexZ ] = pVectorNormal[ countVertexX * counterVertexZ + 1 ];
		pVectorNormal[ countVertexX * counterVertexZ + countVertexX - 1 ] = pVectorNormal[ countVertexX * counterVertexZ + countVertexX - 2 ];
	}
	for( int counterVertexX = 1; counterVertexX < countVertexX - 1; ++counterVertexX )
	{
		pVectorNormal[ counterVertexX ] = pVectorNormal[ countVertexX + counterVertexX ];
		pVectorNormal[ countVertexX * (countVertexZ - 1) + counterVertexX ] = pVectorNormal[ countVertexX * (countVertexZ - 2) + counterVertexX ];
	}
	pVectorNormalPlane[ 0 ] = pVectorNormal[ 1 ] + pVectorNormal[ countVertexX ];
	D3DXVec3Normalize( &pVectorNormal[ 0 ], &pVectorNormalPlane[ 0 ] );
	pVectorNormalPlane[ 0 ] = pVectorNormal[ countVertexX - 2 ] + pVectorNormal[ countVertexX * 2 - 1 ];
	D3DXVec3Normalize( &pVectorNormal[ countVertexX - 1 ], &pVectorNormalPlane[ 0 ] );
	pVectorNormalPlane[ 0 ] = pVectorNormal[ countVertexX * (countVertexZ - 1) + 1 ] + pVectorNormal[ countVertexX * (countVertexZ - 2) ];
	D3DXVec3Normalize( &pVectorNormal[ countVertexX * (countVertexZ - 1) ], &pVectorNormalPlane[ 0 ] );
	pVectorNormalPlane[ 0 ] = pVectorNormal[ countVertexX * (countVertexZ - 1) + countVertexX - 2 ] + pVectorNormal[ countVertexX * (countVertexZ - 2) + countVertexX - 1 ];
	D3DXVec3Normalize( &pVectorNormal[ countVertexX * (countVertexZ - 1) + countVertexX - 1 ], &pVectorNormalPlane[ 0 ] );

	// ���_�o�b�t�@�����쐬
	VertexBuffer	buffer;		// ���_�o�b�t�@���
	buffer.Initialize( countVertex_, pVertex_ );
	for( int counterVertexZ = 0; counterVertexZ < countVertexZ; ++counterVertexZ )
	{
		for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
		{
			int		indexVertex;		// ���_�̔ԍ�
			indexVertex = countVertexX * counterVertexZ + counterVertexX;
			buffer.SetPosition( indexVertex, lengthCellX_ * (counterVertexX - countCellX_ / 2.0f), pHeight[ indexVertex ], lengthCellZ_ * (counterVertexZ - countCellZ_ / 2.0f) );
			buffer.SetNormal( indexVertex, pVectorNormal[ indexVertex ] );
			buffer.SetTextureCoord0( indexVertex, lengthTextureX_ * counterVertexX, lengthTextureZ_ * counterVertexZ );
			buffer.SetColorDiffuse( indexVertex, 1.0f, 1.0f, 1.0f, 1.0f );
		}
	}

	// �@���o�b�t�@�̔j��
	delete pVectorNormal;
	pVectorNormal = nullptr;

	// ���_�o�b�t�@�ɒl��ݒ�
	int		sizeVertex;						// ���_�̃T�C�Y
	void*	pBufferAddress = nullptr;		// �o�b�t�@�̃A�h���X
	sizeVertex = pVertex_->GetSize();
	pVertexBuffer_->Lock( 0, 0, &pBufferAddress, 0 );
	memcpy_s( pBufferAddress, sizeVertex * countVertex_, buffer.GetBuffer(), sizeVertex * countVertex_ );
	pVertexBuffer_->Unlock();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���_���̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int PolygonMesh::GetCountVertex( void ) const
{
	// �l�̕ԋp
	return countVertex_;
}

//==============================================================================
// Brief  : �C���f�b�N�X���̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int PolygonMesh::GetCountIndex( void ) const
{
	// �l�̕ԋp
	return countIndex_;
}

//==============================================================================
// Brief  : �C���f�b�N�X�̃T�C�Y�̎擾
// Return : void								: �Ȃ�
// Arg    : size_t* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void PolygonMesh::GetSizeIndex( size_t* pOut ) const
{
	// �l�̕ԋp
	*pOut = sizeIndex_;
}

//==============================================================================
// Brief  : X�����Z�����̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int PolygonMesh::GetCountCellX( void ) const
{
	// �l�̕ԋp
	return countCellX_;
}

//==============================================================================
// Brief  : Z�����Z�����̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int PolygonMesh::GetCountCellZ( void ) const
{
	// �l�̕ԋp
	return countCellZ_;
}

//==============================================================================
// Brief  : X�����Z�������̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void PolygonMesh::SetLengthCellX( float value )
{
	// �l�̐ݒ�
	lengthCellX_ = value;
}

//==============================================================================
// Brief  : X�����Z�������̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PolygonMesh::GetLengthCellX( void ) const
{
	// �l�̕ԋp
	return lengthCellX_;
}

//==============================================================================
// Brief  : Z�����Z�������̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void PolygonMesh::SetLengthCellZ( float value )
{
	// �l�̐ݒ�
	lengthCellZ_ = value;
}

//==============================================================================
// Brief  : Z�����Z�������̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PolygonMesh::GetLengthCellZ( void ) const
{
	// �l�̕ԋp
	return lengthCellZ_;
}

//==============================================================================
// Brief  : X�����e�N�X�`�������̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void PolygonMesh::SetLengthTextureX( float value )
{
	// �l�̐ݒ�
	lengthTextureX_ = value;
}

//==============================================================================
// Brief  : X�����e�N�X�`�������̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PolygonMesh::GetLengthTextureX( void ) const
{
	// �l�̕ԋp
	return lengthTextureX_;
}

//==============================================================================
// Brief  : Z�����e�N�X�`�������̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void PolygonMesh::SetLengthTextureZ( float value )
{
	// �l�̐ݒ�
	lengthTextureZ_ = value;
}

//==============================================================================
// Brief  : Z�����e�N�X�`�������̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PolygonMesh::GetLengthTextureZ( void ) const
{
	// �l�̕ԋp
	return lengthTextureZ_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PolygonMesh::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pDevice_ = nullptr;
	pVertexBuffer_ = nullptr;
	pIndexBuffer_ = nullptr;
	pVertex_ = nullptr;
	countVertex_ = 0;
	countIndex_ = 0;
	sizeIndex_ = 0;
	countCellX_ = 0;
	countCellZ_ = 0;
	lengthCellX_ = 0.0f;
	lengthCellZ_ = 0.0f;
	lengthTextureX_ = 1.0f;
	lengthTextureZ_ = 1.0f;
}
