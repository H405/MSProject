//==============================================================================
//
// File   : PolygonMeshDomeInside.cpp
// Brief  : �������b�V���h�[���|���S��
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "PolygonMeshDomeInside.h"
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
PolygonMeshDomeInside::PolygonMeshDomeInside( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
PolygonMeshDomeInside::~PolygonMeshDomeInside( void )
{
	// �I������
	Finalize();
}

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
int PolygonMeshDomeInside::Initialize( IDirect3DDevice9* pDevice, int countCellX, int countCellY,
	float radius, float lengthTextureX, float lengthTextureY )
{
	// �����o�ϐ��̐ݒ�
	pDevice_ = pDevice;
	countCellX_ = countCellX;
	countCellY_ = countCellY;
	radius_ = radius;
	lengthTextureX_ = lengthTextureX;
	lengthTextureY_ = lengthTextureY;

	// ���_�ƃC���f�b�N�X�̐����v�Z
	int		countVertexX;		// X�������_��
	int		countVertexY;		// Y�������_��
	countVertexX = countCellX + 1;
	countVertexY = countCellY + 1;
	countVertex_ = countVertexX * countVertexY;
	countIndex_ = 2 * countVertexX * (countVertexY - 1) + 2 * (countVertexY - 2);

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
	for( int counterVertexY = 0; counterVertexY < countVertexY; ++counterVertexY )
	{
		for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
		{
			int		indexVertex;		// ���_�̔ԍ�
			indexVertex = countVertexX * counterVertexY + counterVertexX;
			buffer.SetPositionX( indexVertex, radius * cosf( 0.5f * D3DX_PI * (countVertexY - 1 - counterVertexY) / countCellY ) * cosf( 2.0f * D3DX_PI * counterVertexX / countCellX ) );
			buffer.SetPositionY( indexVertex, radius * cosf( radius * sinf( 0.5f * D3DX_PI * (countVertexY - 1 - counterVertexY) / countCellY ) ) );
			buffer.SetPositionZ( indexVertex, radius * cosf( radius * cosf( 0.5f * D3DX_PI * (countVertexY - 1 - counterVertexY) / countCellY ) * sinf( 2.0f * D3DX_PI * counterVertexX / countCellX ) ) );
			buffer.SetNormal( indexVertex, cosf( 2.0f * D3DX_PI * counterVertexX / countCellX ), 0.0f, -sinf( 2.0f * D3DX_PI * counterVertexX / countCellX ) );
			buffer.SetTextureCoord0( indexVertex, lengthTextureX * counterVertexX, lengthTextureY * counterVertexY );
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
		for( int counterVertexY = 0; counterVertexY < countVertexY - 1; ++counterVertexY )
		{
			for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
			{
				pIndex[ (2 * countVertexX + 2) * counterVertexY + 2 * counterVertexX + 0 ] = static_cast< DWORD >( countVertexX * (counterVertexY + 0) + counterVertexX );
				pIndex[ (2 * countVertexX + 2) * counterVertexY + 2 * counterVertexX + 1 ] = static_cast< DWORD >( countVertexX * (counterVertexY + 1) + counterVertexX );
			}
		}
		for( int counterVertexY = 0; counterVertexY < countVertexY - 2; ++counterVertexY )
		{
			pIndex[ (2 * countVertexX + 2) * (counterVertexY + 1) - 2 ] = static_cast< DWORD >( countVertexX * (counterVertexY + 1) + countVertexX - 1 );
			pIndex[ (2 * countVertexX + 2) * (counterVertexY + 1) - 1 ] = static_cast< DWORD >( countVertexX * (counterVertexY + 1) );
		}
	}
	else
	{
		// �C���f�b�N�X�o�b�t�@�X�V�J�n
		WORD	*pIndex = nullptr;		// ���������p�C���f�b�N�X�o�b�t�@�A�h���X
		pIndexBuffer_->Lock( 0, 0, (void**)&pIndex, 0 );

		// �C���f�b�N�X���ݒ�
		for( int counterVertexY = 0; counterVertexY < countVertexY - 1; ++counterVertexY )
		{
			for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
			{
				pIndex[ (2 * countVertexX + 2) * counterVertexY + 2 * counterVertexX + 0 ] = static_cast< WORD >( countVertexX * (counterVertexY + 0) + counterVertexX );
				pIndex[ (2 * countVertexX + 2) * counterVertexY + 2 * counterVertexX + 1 ] = static_cast< WORD >( countVertexX * (counterVertexY + 1) + counterVertexX );
			}
		}
		for( int counterVertexY = 0; counterVertexY < countVertexY - 2; ++counterVertexY )
		{
			pIndex[ (2 * countVertexX + 2) * (counterVertexY + 1) - 2 ] = static_cast< WORD >( countVertexX * (counterVertexY + 1) + countVertexX - 1 );
			pIndex[ (2 * countVertexX + 2) * (counterVertexY + 1) - 1 ] = static_cast< WORD >( countVertexX * (counterVertexY + 1) );
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
int PolygonMeshDomeInside::Finalize( void )
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
// Arg    : int countCellY						: Y�����Z����
// Arg    : float radius						: ���a
// Arg    : float lengthTextureX				: X�����e�N�X�`������
// Arg    : float lengthTextureY				: Y�����e�N�X�`������
//==============================================================================
int PolygonMeshDomeInside::Reinitialize( IDirect3DDevice9* pDevice, int countCellX, int countCellY,
	float radius, float lengthTextureX, float lengthTextureY )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice, countCellX, countCellY, radius, lengthTextureX, lengthTextureY );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : PolygonMeshDomeInside* pOut					: �R�s�[��A�h���X
//==============================================================================
int PolygonMeshDomeInside::Copy( PolygonMeshDomeInside* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`�揈��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PolygonMeshDomeInside::Draw( void )
{
	// �`��
	pDevice_->SetStreamSource( 0, pVertexBuffer_, 0, pVertex_->GetSize() );
	pDevice_->SetIndices( pIndexBuffer_ );
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pDevice_->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, countVertex_, 0, countIndex_ - 2 );
}

//==============================================================================
// Brief  : ���_���̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int PolygonMeshDomeInside::GetCountVertex( void ) const
{
	// �l�̕ԋp
	return countVertex_;
}

//==============================================================================
// Brief  : �C���f�b�N�X���̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int PolygonMeshDomeInside::GetCountIndex( void ) const
{
	// �l�̕ԋp
	return countIndex_;
}

//==============================================================================
// Brief  : �C���f�b�N�X�̃T�C�Y�̎擾
// Return : void								: �Ȃ�
// Arg    : size_t* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void PolygonMeshDomeInside::GetSizeIndex( size_t* pOut ) const
{
	// �l�̕ԋp
	*pOut = sizeIndex_;
}

//==============================================================================
// Brief  : X�����Z�����̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int PolygonMeshDomeInside::GetCountCellX( void ) const
{
	// �l�̕ԋp
	return countCellX_;
}

//==============================================================================
// Brief  : Y�����Z�����̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int PolygonMeshDomeInside::GetCountCellY( void ) const
{
	// �l�̕ԋp
	return countCellY_;
}

//==============================================================================
// Brief  :���a�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void PolygonMeshDomeInside::SetRadius( float value )
{
	// �l�̐ݒ�
	radius_ = value;
}

//==============================================================================
// Brief  : ���a�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PolygonMeshDomeInside::GetRadius( void ) const
{
	// �l�̕ԋp
	return radius_;
}

//==============================================================================
// Brief  : X�����e�N�X�`�������̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void PolygonMeshDomeInside::SetLengthTextureX( float value )
{
	// �l�̐ݒ�
	lengthTextureX_ = value;
}

//==============================================================================
// Brief  : X�����e�N�X�`�������̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PolygonMeshDomeInside::GetLengthTextureX( void ) const
{
	// �l�̕ԋp
	return lengthTextureX_;
}

//==============================================================================
// Brief  : Y�����e�N�X�`�������̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void PolygonMeshDomeInside::SetLengthTextureY( float value )
{
	// �l�̐ݒ�
	lengthTextureY_ = value;
}

//==============================================================================
// Brief  : Y�����e�N�X�`�������̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PolygonMeshDomeInside::GetLengthTextureY( void ) const
{
	// �l�̕ԋp
	return lengthTextureY_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PolygonMeshDomeInside::InitializeSelf( void )
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
	countCellY_ = 0;
	radius_ = 0.0f;
	lengthTextureX_ = 1.0f;
	lengthTextureY_ = 1.0f;
}
