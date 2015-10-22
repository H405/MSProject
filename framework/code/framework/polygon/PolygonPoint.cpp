//==============================================================================
//
// File   : PolygonPoint.cpp
// Brief  : �|�C���g�X�v���C�g�|���S��
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "PolygonPoint.h"
#include "../develop/Debug.h"
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
PolygonPoint::PolygonPoint( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
PolygonPoint::~PolygonPoint( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
//==============================================================================
int PolygonPoint::Initialize( int maximumItem, IDirect3DDevice9* pDevice )
{
	// �����o�ϐ��̐ݒ�
	maximumItem_ = maximumItem;
	pDevice_ = pDevice;

	// ���_���̐���
	int		result;		// ���s����
	pVertex_ = new Vertex();
	if( pVertex_ == nullptr )
	{
		return 1;
	}
	result = pVertex_->Initialize( pDevice, Vertex::ELEMENT_SET_POINT );
	if( result != 0 )
	{
		return result;
	}

	// ���_�o�b�t�@�����쐬
	VertexBuffer	buffer;		// ���_�o�b�t�@���
	buffer.Initialize( maximumItem, pVertex_ );
	for( int counterVertex = 0; counterVertex < maximumItem; ++counterVertex )
	{
		buffer.SetPosition( counterVertex, 0.0f, 0.0f, 0.0f );
		buffer.SetPointSize( counterVertex, 100.0f );
		buffer.SetColorDiffuse( counterVertex, 1.0f, 1.0f, 1.0f, 1.0f );
	}

	// ���_�o�b�t�@�̐���
	int		sizeVertex;		// ���_�̃T�C�Y
	sizeVertex = pVertex_->GetSize();
	result = pDevice->CreateVertexBuffer( sizeVertex * maximumItem, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &pVertexBuffer_, nullptr );
	if( result != 0 )
	{
		return result;
	}

	// ���_�o�b�t�@�ɒl��ݒ�
	void*	pBufferAddress = nullptr;		// �o�b�t�@�̃A�h���X
	pVertexBuffer_->Lock( 0, 0, &pBufferAddress, 0 );
	memcpy_s( pBufferAddress, sizeVertex * maximumItem, buffer.GetBuffer(), sizeVertex * maximumItem );
	pVertexBuffer_->Unlock();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int PolygonPoint::Finalize( void )
{
	// ���_�o�b�t�@�̊J��
	if( pVertexBuffer_ != nullptr )
	{
		pVertexBuffer_->Release();
		pVertexBuffer_ = nullptr;
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
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
//==============================================================================
int PolygonPoint::Reinitialize( int maximumItem, IDirect3DDevice9* pDevice )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( maximumItem, pDevice );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : PolygonPoint* pOut					: �R�s�[��A�h���X
//==============================================================================
int PolygonPoint::Copy( PolygonPoint* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`�揈��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PolygonPoint::Draw( void )
{
	// �`�搔�̊m�F
	if( countItem_ <= 0 )
	{
		return;
	}

	// �`��
	pDevice_->SetStreamSource( 0, pVertexBuffer_, 0, pVertex_->GetSize() );
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pDevice_->DrawPrimitive( D3DPT_POINTLIST, 0, countItem_);
}

//==============================================================================
// Brief  : ���_�o�b�t�@�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int count							: ���_�̐�
// Arg    : void* pBuffer						: ���_�o�b�t�@
//==============================================================================
void PolygonPoint::SetVertexBuffer( int count, void* pBuffer )
{
	// �G���[�`�F�b�N
	Assert( pBuffer != nullptr, _T( "�����̃A�h���X���s���ł��B" ) );

	// ���̌���
	countItem_ = count;

	// ���_�o�b�t�@�ɒl��ݒ�
	void*	pBufferAddress = nullptr;		// �o�b�t�@�̃A�h���X
	int		sizeVertex;		// ���_�̃T�C�Y
	sizeVertex = pVertex_->GetSize();
	pVertexBuffer_->Lock( 0, 0, &pBufferAddress, 0 );
	memcpy_s( pBufferAddress, sizeVertex * count, pBuffer, sizeVertex * count );
	pVertexBuffer_->Unlock();
}

//==============================================================================
// Brief  : ���_���̎擾
// Return : Vertex*								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
Vertex* PolygonPoint::GetVertex( void ) const
{
	// �l�̕ԋp
	return pVertex_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PolygonPoint::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	maximumItem_ = 0;
	countItem_ = 0;
	pDevice_ = nullptr;
	pVertexBuffer_ = nullptr;
	pVertex_ = nullptr;
}
