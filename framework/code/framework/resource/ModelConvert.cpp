//==============================================================================
//
// File   : ModelConvert.cpp
// Brief  : �ϊ��ς݃��f��
// Author : Taiga Shirakawa
// Date   : 2015/10/29 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ModelConvert.h"
#include "../graphic/Material.h"
#include "../vertex/Vertex.h"

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
ModelConvert::ModelConvert( void ) : Model()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ModelConvert::~ModelConvert( void )
{
	// �I������
	Finalize();
}

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
int ModelConvert::Initialize( IDirect3DDevice9* pDevice, unsigned int elementVertex,
	unsigned int countMaterial, unsigned int countTexture, unsigned long countMesh, unsigned long countBone,
	void** ppVertexBuffer, const int* pCountVertex, Material* pMaterial, const int* pIndexMaterial,
	IDirect3DTexture9** ppTexture, const int* pIndexTexture, const D3DXMATRIX* pMatrixBone )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Model::Initialize( pDevice, elementVertex, countMaterial, countTexture );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	countMesh_ = countMesh;
	countBone_ = countBone;

	pCountPolygon_ = new unsigned long[ countMesh ];
	if( pCountPolygon_ == nullptr )
	{
		return 1;
	}
	for( unsigned int counterItem = 0; counterItem < countMesh; ++counterItem )
	{
		pCountPolygon_[ counterItem ] = pCountVertex[ counterItem ] / 3;
	}

	ppVertexBuffer_ = new IDirect3DVertexBuffer9*[ countMesh ];
	for( unsigned int counterItem = 0; counterItem < countMesh; ++counterItem )
	{
		ppVertexBuffer_[ counterItem ] = nullptr;
	}

	for( unsigned int counterItem = 0; counterItem < countMaterial; ++counterItem )
	{
		pMaterial_[ counterItem ] = pMaterial[ counterItem ];
	}

	pIndexMaterial_ = new int[ countMesh ];
	for( unsigned int counterItem = 0; counterItem < countMesh; ++counterItem )
	{
		pIndexMaterial_[ counterItem ] = pIndexMaterial[ counterItem ];
	}

	for( unsigned int counterItem = 0; counterItem < countTexture; ++counterItem )
	{
		ppTexture_[ counterItem ] = ppTexture[ counterItem ];
	}

	pIndexTexture_ = new int[ countMesh ];
	for( unsigned int counterItem = 0; counterItem < countMesh; ++counterItem )
	{
		pIndexTexture_[ counterItem ] = pIndexTexture[ counterItem ];
	}

	pMatrixBone_ = new D3DXMATRIX[ countBone ];
	for( unsigned int counterItem = 0; counterItem < countBone; ++counterItem )
	{
		pMatrixBone_[ counterItem ] = pMatrixBone[ counterItem ];
	}

	// ���_�o�b�t�@�̐���
	for( unsigned int counterItem = 0; counterItem < countMesh; ++counterItem )
	{
		// ���_�o�b�t�@�̐���
		int		sizeVertex;		// ���_�̃T�C�Y
		sizeVertex = pVertex_->GetSize();
		result = pDevice->CreateVertexBuffer( sizeVertex * pCountVertex[ counterItem ], D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &ppVertexBuffer_[ counterItem ], nullptr );
		if( result != 0 )
		{
			return result;
		}

		// ���_�o�b�t�@�ɒl��ݒ�
		void*	pBufferAddress = nullptr;		// �o�b�t�@�̃A�h���X
		ppVertexBuffer_[ counterItem ]->Lock( 0, 0, &pBufferAddress, 0 );
		memcpy_s( pBufferAddress, sizeVertex * pCountVertex[ counterItem ], ppVertexBuffer[ counterItem ], sizeVertex * pCountVertex[ counterItem ] );
		ppVertexBuffer_[ counterItem ]->Unlock();
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ModelConvert::Finalize( void )
{
	// ���_�o�b�t�@�̊J��
	for( unsigned int counterItem = 0; counterItem < countMesh_; ++counterItem )
	{
		if( ppVertexBuffer_[ counterItem ] != nullptr )
		{
			ppVertexBuffer_[ counterItem ]->Release();
			ppVertexBuffer_[ counterItem ] = nullptr;
		}
	}
	delete[] ppVertexBuffer_;
	ppVertexBuffer_ = nullptr;

	// �|���S�����i�[�̈�̊J��
	delete[] pCountPolygon_;
	pCountPolygon_ = nullptr;

	// �i�[�̈�̊J��
	delete[] pIndexMaterial_;
	pIndexMaterial_ = nullptr;

	delete[] pIndexTexture_;
	pIndexTexture_ = nullptr;

	delete[] pMatrixBone_;
	pMatrixBone_ = nullptr;

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Model::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

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
int ModelConvert::Reinitialize( IDirect3DDevice9* pDevice, unsigned int elementVertex,
	unsigned int countMaterial, unsigned int countTexture, unsigned long countMesh, unsigned long countBone,
	void** ppVertexBuffer, const int* pCountVertex, Material* pMaterial, const int* pIndexMaterial,
	IDirect3DTexture9** ppTexture, const int* pIndexTexture, const D3DXMATRIX* pMatrixBone )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice, elementVertex, countMaterial, countTexture, countMesh, countBone, ppVertexBuffer, pCountVertex,
		pMaterial, pIndexMaterial, ppTexture, pIndexTexture, pMatrixBone );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ModelConvert* pOut					: �R�s�[��A�h���X
//==============================================================================
int ModelConvert::Copy( ModelConvert* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Model::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`�揈��
// Return : void								: �Ȃ�
// Arg    : int indexMaterial					: �`��}�e���A���ԍ�
//==============================================================================
void ModelConvert::Draw( int indexMaterial )
{
	// �`��
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pDevice_->SetStreamSource( 0, ppVertexBuffer_[ indexMaterial ], 0, pVertex_->GetSize() );
	pDevice_->DrawPrimitive( D3DPT_TRIANGLELIST, 0, pCountPolygon_[ indexMaterial ] );
}

//==============================================================================
// Brief  : �}�e���A���̎擾
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : Material* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void ModelConvert::GetMaterial( int index, Material* pOut ) const
{
	// �l�̕ԋp
	*pOut = pMaterial_[ pIndexMaterial_[ index ] ];
}

//==============================================================================
// Brief  : �e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : int index							: �ݒ肷��ԍ�
//==============================================================================
IDirect3DTexture9* ModelConvert::GetTexture( int index ) const
{
	// �l�̕ԋp
	if( static_cast< unsigned int >( index ) >= countTexture_ )
	{
		return nullptr;
	}
	return ppTexture_[ pIndexTexture_[ index ] ];
}

//==============================================================================
// Brief  : ���b�V�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : unsigned long value					: �ݒ肷��l
//==============================================================================
void ModelConvert::SetCountMesh( unsigned long value )
{
	// �l�̐ݒ�
	countMesh_ = value;
}

//==============================================================================
// Brief  : ���b�V�����̎擾
// Return : unsigned long						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned long ModelConvert::GetCountMesh( void ) const
{
	// �l�̕ԋp
	return countMesh_;
}

//==============================================================================
// Brief  : �{�[�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : unsigned long value					: �ݒ肷��l
//==============================================================================
void ModelConvert::SetCountBone( unsigned long value )
{
	// �l�̐ݒ�
	countBone_ = value;
}

//==============================================================================
// Brief  : �{�[�����̎擾
// Return : unsigned long						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned long ModelConvert::GetCountBone( void ) const
{
	// �l�̕ԋp
	return countBone_;
}

//==============================================================================
// Brief  : ���b�V���̃}�e���A���ԍ��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const int& value					: �ݒ肷��l
//==============================================================================
void ModelConvert::SetIndexMaterial( int index, const int& value )
{
	// �l�̐ݒ�
	pIndexMaterial_[ index ] = value;
}

//==============================================================================
// Brief  : ���b�V���̃}�e���A���ԍ��̎擾
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : int* pOut							: �l�̊i�[�A�h���X
//==============================================================================
void ModelConvert::GetIndexMaterial( int index, int* pOut ) const
{
	// �l�̕ԋp
	*pOut = pIndexMaterial_[ index ];
}

//==============================================================================
// Brief  : ���b�V���̃e�N�X�`���ԍ��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const int& value					: �ݒ肷��l
//==============================================================================
void ModelConvert::SetIndexTexture( int index, const int& value )
{
	// �l�̐ݒ�
	pIndexTexture_[ index ] = value;
}

//==============================================================================
// Brief  : ���b�V���̃e�N�X�`���ԍ��̎擾
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : int* pOut							: �l�̊i�[�A�h���X
//==============================================================================
void ModelConvert::GetIndexTexture( int index, int* pOut ) const
{
	// �l�̕ԋp
	*pOut = pIndexTexture_[ index ];
}

//==============================================================================
// Brief  : �{�[���̏����p���s��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXMATRIX& value				: �ݒ肷��l
//==============================================================================
void ModelConvert::SetMatrixBone( int index, const D3DXMATRIX& value )
{
	// �l�̐ݒ�
	pMatrixBone_[ index ] = value;
}

//==============================================================================
// Brief  : �{�[���̏����p���s��̎擾
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : D3DXMATRIX* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void ModelConvert::GetMatrixBone( int index, D3DXMATRIX* pOut ) const
{
	// �l�̕ԋp
	*pOut = pMatrixBone_[ index ];
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ModelConvert::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	countMesh_ = 0;
	countBone_ = 0;
	pCountPolygon_ = nullptr;
	ppVertexBuffer_ = nullptr;
	pIndexMaterial_ = nullptr;
	pIndexTexture_ = nullptr;
	pMatrixBone_ = nullptr;
}
