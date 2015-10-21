//==============================================================================
//
// File   : ManagerModel.cpp
// Brief  : ���f���Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerModel.h"
#include "ManagerTexture.h"
#include "ModelX.h"
#include "Texture.h"
#include "../graphic/Material.h"
#include "../vertex/Vertex.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �e���v���[�g�錾
//******************************************************************************
template class ManagerModel< class Model >;

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerModel< TypeItem >::ManagerModel( void ) : ManagerResource()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerModel< TypeItem >::~ManagerModel( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : TCHAR* pDirectory					: ��f�B���N�g��
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : ManagerTexture< Texture >* pTexture	: �e�N�X�`���Ǘ��N���X
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Initialize( TCHAR* pDirectory, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerResource::Initialize( pDirectory, maximumItem );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pDevice_ = pDevice;
	pTexture_ = pTexture;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerResource::Finalize();
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
// Arg    : TCHAR* pDirectory					: ��f�B���N�g��
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : ManagerTexture< Texture >* pTexture	: �e�N�X�`���Ǘ��N���X
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Reinitialize( TCHAR* pDirectory, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDirectory, maximumItem, pDevice, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerModel* pOut					: �R�s�[��A�h���X
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Copy( ManagerModel* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerResource::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
void ManagerModel< TypeItem >::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pDevice_ = nullptr;
	pTexture_ = nullptr;
}

//==============================================================================
// Brief  : ���\�[�X�̓ǂݍ���
// Return : int									: ���s����
// Arg    : TCHAR* pPath						: �t�@�C���p�X
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::LoadResource( TCHAR* pPath, int index )
{
	// ���f������
	DWORD				countMaterial;				// �}�e���A�����̐�
	ID3DXMesh*			pMesh = nullptr;			// ���b�V�����ւ̃A�h���X
	ID3DXBuffer*		pMaterial = nullptr;		// �}�e���A�����ւ̃A�h���X
	HRESULT				result;						// ���s����
	result = D3DXLoadMeshFromX( pPath, D3DXMESH_SYSTEMMEM, pDevice_, NULL, &pMaterial, NULL, &countMaterial, &pMesh );
	if( result != 0 )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"��������܂���" ), pPath );
		MessageBox( NULL, pStringError, _T( "�G���[" ), MB_OK );
		return 1;
	}

	// ���f���̐���
	ModelX*	pModel = nullptr;		// ���f��
	pModel= new ModelX();
	if( pModel == nullptr )
	{
		return 1;
	}
	result = pModel->Initialize( pDevice_, Vertex::ELEMENT_SET_SIMPLE, countMaterial, countMaterial, pMesh );
	if( result != 0 )
	{
		return result;
	}
	pBufferItem_[ index ].pItem_ = pModel;

	// �e�N�X�`���̐ݒ�
	D3DXMATERIAL*	pMaterialPointer = nullptr;		// �}�e���A�����̐擪�A�h���X
	Texture*		pTexture = nullptr;				// �e�N�X�`��
	pMaterialPointer = static_cast< D3DXMATERIAL* >( pMaterial->GetBufferPointer() );
	for( unsigned long counterMaterial = 0; counterMaterial < countMaterial; ++counterMaterial )
	{
		if( pMaterialPointer[ counterMaterial ].pTextureFilename == nullptr )
		{
			continue;
		}
		pTexture = nullptr;
		pTexture = pTexture_->Get( pMaterialPointer[ counterMaterial ].pTextureFilename );
		if( pTexture != nullptr )
		{
			pBufferItem_[ index ].pItem_->SetTexture( counterMaterial, pTexture->pTexture_ );
		}
	}

	// �}�e���A���̐ݒ�
	Material		materialSet;		// �ݒ肷��}�e���A��
	D3DMATERIAL9	materialGet;		// �擾�����}�e���A��
	for( unsigned long counterMaterial = 0; counterMaterial < countMaterial; ++counterMaterial )
	{
		materialGet = pMaterialPointer[ counterMaterial ].MatD3D;
		materialSet.diffuse_ = materialGet.Diffuse;
		materialSet.specular_ = materialGet.Specular;
		materialSet.ambient_ = materialGet.Ambient;
		materialSet.emmisive_ = materialGet.Emissive;
		materialSet.power_ = materialGet.Power;
		materialSet.reflection_ = 1.0f;
		materialSet.refractive_ = 0.1f;
		pBufferItem_[ index ].pItem_->SetMaterial( counterMaterial, materialSet );
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���\�[�X�̊J��
// Return : void								: �Ȃ�
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
void ManagerModel< TypeItem >::ReleaseResource( int index )
{
	// ���f���̊J��
	delete pBufferItem_[ index ].pItem_;
	pBufferItem_[ index ].pItem_ = nullptr;
}
