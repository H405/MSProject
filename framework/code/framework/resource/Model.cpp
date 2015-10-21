//==============================================================================
//
// File   : Model.cpp
// Brief  : ���f���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Model.h"
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
Model::Model( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Model::~Model( void )
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
//==============================================================================
int Model::Initialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture )
{
	// �����o�ϐ��̐ݒ�
	pDevice_ = pDevice;
	countMaterial_ = countMaterial;
	countTexture_ = countTexture;

	// �i�[�̈�̊m��
	pMaterial_ = new Material[ countMaterial ];
	if( pMaterial_ == nullptr )
	{
		return 1;
	}

	ppTexture_ = new IDirect3DTexture9*[ countTexture ];
	if( ppTexture_ == nullptr )
	{
		return 1;
	}
	for( unsigned int counterItem = 0; counterItem < countTexture; ++counterItem )
	{
		ppTexture_[ counterItem ] = nullptr;
	}

	// ���_���̐���
	int		result;		// ���s����
	pVertex_ = new Vertex();
	if( pVertex_ == nullptr )
	{
		return 1;
	}
	result = pVertex_->Initialize( pDevice, elementVertex );
	if( result != 0 )
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
int Model::Finalize( void )
{
	// ���_���̔j��
	delete pVertex_;
	pVertex_ = nullptr;

	// �i�[�̈�̊J��
	delete[] pMaterial_;
	pMaterial_ = nullptr;
	delete[] ppTexture_;
	ppTexture_ = nullptr;

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
//==============================================================================
int Model::Reinitialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice, elementVertex, countMaterial, countTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : Model* pOut							: �R�s�[��A�h���X
//==============================================================================
int Model::Copy( Model* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`�揈��
// Return : void								: �Ȃ�
// Arg    : int indexMaterial					: �`��}�e���A���ԍ�
//==============================================================================
void Model::Draw( int indexMaterial )
{
}

//==============================================================================
// Brief  : �}�e���A�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : unsigned int value					: �ݒ肷��l
//==============================================================================
void Model::SetCountMaterial( unsigned int value )
{
	// �l�̐ݒ�
	countMaterial_ = value;
}

//==============================================================================
// Brief  : �}�e���A�����̎擾
// Return : unsigned int						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned int Model::GetCountMaterial( void ) const
{
	// �l�̕ԋp
	return countMaterial_;
}

//==============================================================================
// Brief  : �}�e���A���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const Material& value				: �ݒ肷��l
//==============================================================================
void Model::SetMaterial( int index, const Material& value )
{
	// �l�̐ݒ�
	pMaterial_[ index ] = value;
}

//==============================================================================
// Brief  : �}�e���A���̎擾
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : Material* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void Model::GetMaterial( int index, Material* pOut ) const
{
	// �l�̕ԋp
	*pOut = pMaterial_[ index ];
}

//==============================================================================
// Brief  : �e�N�X�`�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : unsigned int value					: �ݒ肷��l
//==============================================================================
void Model::SetCountTexture( unsigned int value )
{
	// �l�̐ݒ�
	countTexture_ = value;
}

//==============================================================================
// Brief  : �e�N�X�`�����̎擾
// Return : unsigned int						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned int Model::GetCountTexture( void ) const
{
	// �l�̕ԋp
	return countTexture_;
}

//==============================================================================
// Brief  : �e�N�X�`���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : IDirect3DTexture9* pValue			: �ݒ肷��l
//==============================================================================
void Model::SetTexture( int index, IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	ppTexture_[ index ] = pValue;
}

//==============================================================================
// Brief  : �e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : int index							: �ݒ肷��ԍ�
//==============================================================================
IDirect3DTexture9* Model::GetTexture( int index ) const
{
	// �l�̕ԋp
	return ppTexture_[ index ];
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Model::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pDevice_ = nullptr;
	pVertex_ = nullptr;
	countMaterial_ = 0;
	pMaterial_ = nullptr;
	countTexture_ = 0;
	ppTexture_ = nullptr;
}
