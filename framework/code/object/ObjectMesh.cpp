//==============================================================================
//
// File   : ObjectMesh.cpp
// Brief  : ���b�V���|���S���I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectMesh.h"
#include "../framework/polygon/PolygonMesh.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/GraphicMesh.h"

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
ObjectMesh::ObjectMesh( void ) : ObjectMovement()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectMesh::~ObjectMesh( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : int countCellX						: X�����Z����
// Arg    : int countCellZ						: Z�����Z����
// Arg    : float lengthCellX					: X�����Z������
// Arg    : float lengthCellZ					: Z�����Z������
// Arg    : float lengthTextureX				: X�����e�N�X�`������
// Arg    : float lengthTextureZ				: Z�����e�N�X�`������
//==============================================================================
int ObjectMesh::Initialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
	float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// ���b�V���|���S���̐���
	pPolygon_ = new PolygonMesh();
	if( pPolygon_ == nullptr )
	{
		return 1;
	}
	result = pPolygon_->Initialize( pDevice, countCellX, countCellZ, lengthCellX, lengthCellZ, lengthTextureX, lengthTextureZ );
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
int ObjectMesh::Finalize( void )
{
	// ���b�V���|���S���̊J��
	delete pPolygon_;
	pPolygon_ = nullptr;

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Finalize();
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
// Arg    : int priority						: �X�V�D��x
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : int countCellX						: X�����Z����
// Arg    : int countCellZ						: Z�����Z����
// Arg    : float lengthCellX					: X�����Z������
// Arg    : float lengthCellZ					: Z�����Z������
// Arg    : float lengthTextureX				: X�����e�N�X�`������
// Arg    : float lengthTextureZ				: Z�����e�N�X�`������
//==============================================================================
int ObjectMesh::Reinitialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
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
	return Initialize( priority, pDevice, countCellX, countCellZ, lengthCellX, lengthCellZ, lengthTextureX, lengthTextureZ );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ObjectMesh* pOut					: �R�s�[��A�h���X
//==============================================================================
int ObjectMesh::Copy( ObjectMesh* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectMesh::Update( void )
{
	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : �`��N���X�̐���
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : Texture* pTexture					: �e�N�X�`��
//==============================================================================
int ObjectMesh::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture )
{
	// �O���t�B�b�N�̐���
	int					result;				// ���s����
	IDirect3DTexture9*	pTextureSet;		// �ݒ肷��e�N�X�`��
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}
	pGraphic_ = new GraphicMesh();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, pPolygon_, &material_, pTextureSet );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`��N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : GraphicMesh* pValue					: �ݒ肷��l
//==============================================================================
void ObjectMesh::SetGraphic( GraphicMesh* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : GraphicMesh*						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicMesh* ObjectMesh::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectMesh::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pPolygon_ = nullptr;
}
