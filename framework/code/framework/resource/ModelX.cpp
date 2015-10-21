//==============================================================================
//
// File   : ModelX.cpp
// Brief  : X�t�@�C�����f���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ModelX.h"
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
ModelX::ModelX( void ) : Model()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ModelX::~ModelX( void )
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
// Arg    : ID3DXMesh* pMesh					: ���b�V��
//==============================================================================
int ModelX::Initialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture, ID3DXMesh* pMesh )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Model::Initialize( pDevice, elementVertex, countMaterial, countTexture );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pMesh_ = pMesh;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ModelX::Finalize( void )
{
	// ���b�V���̊J��
	if( pMesh_ != nullptr )
	{
		pMesh_->Release();
		pMesh_ = nullptr;
	}

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
// Arg    : ID3DXMesh* pMesh					: ���b�V��
//==============================================================================
int ModelX::Reinitialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture, ID3DXMesh* pMesh )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice, elementVertex, countMaterial, countTexture, pMesh );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ModelX* pOut						: �R�s�[��A�h���X
//==============================================================================
int ModelX::Copy( ModelX* pOut ) const
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
void ModelX::Draw( int indexMaterial )
{
	// �`��
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pMesh_->DrawSubset( indexMaterial );
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ModelX::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pMesh_ = nullptr;
}
