//==============================================================================
//
// File   : PolygonBillboard.cpp
// Brief  : �r���{�[�h�|���S��
// Author : Taiga Shirakawa
// Date   : 2015/11/23 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "PolygonBillboard.h"
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
PolygonBillboard::PolygonBillboard( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
PolygonBillboard::~PolygonBillboard( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
//==============================================================================
int PolygonBillboard::Initialize( IDirect3DDevice9* pDevice )
{
	// �����o�ϐ��̐ݒ�
	pDevice_ = pDevice;

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
	buffer.Initialize( COUNT_VERTEX, pVertex_ );
	for( int counterVertex = 0; counterVertex < COUNT_VERTEX; ++counterVertex )
	{
		buffer.SetPosition( counterVertex, 1.0f * (counterVertex % COUNT_VERTEX_LINE) - 0.5f, -1.0f * (counterVertex / COUNT_VERTEX_LINE) + 0.5f, 0.0f );
		buffer.SetNormal( counterVertex, 0.0f, 0.0f, -1.0f );
		buffer.SetTextureCoord0( counterVertex, 1.0f * (counterVertex % COUNT_VERTEX_LINE), 1.0f * (counterVertex / COUNT_VERTEX_LINE) );
		buffer.SetColorDiffuse( counterVertex, 1.0f, 1.0f, 1.0f, 1.0f );
	}

	// ���_�o�b�t�@�̐���
	int		sizeVertex;		// ���_�̃T�C�Y
	sizeVertex = pVertex_->GetSize();
	result = pDevice->CreateVertexBuffer( sizeVertex * COUNT_VERTEX, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &pVertexBuffer_, nullptr );
	if( result != 0 )
	{
		return result;
	}

	// ���_�o�b�t�@�ɒl��ݒ�
	void*	pBufferAddress = nullptr;		// �o�b�t�@�̃A�h���X
	pVertexBuffer_->Lock( 0, 0, &pBufferAddress, 0 );
	memcpy_s( pBufferAddress, sizeVertex * COUNT_VERTEX, buffer.GetBuffer(), sizeVertex * COUNT_VERTEX );
	pVertexBuffer_->Unlock();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int PolygonBillboard::Finalize( void )
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
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
//==============================================================================
int PolygonBillboard::Reinitialize( IDirect3DDevice9* pDevice )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : PolygonBillboard* pOut						: �R�s�[��A�h���X
//==============================================================================
int PolygonBillboard::Copy( PolygonBillboard* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`�揈��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PolygonBillboard::Draw( void )
{
	// �`��
	pDevice_->SetStreamSource( 0, pVertexBuffer_, 0, pVertex_->GetSize() );
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pDevice_->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, COUNT_VERTEX - 2 );
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PolygonBillboard::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pDevice_ = nullptr;
	pVertexBuffer_ = nullptr;
	pVertex_ = nullptr;
}
