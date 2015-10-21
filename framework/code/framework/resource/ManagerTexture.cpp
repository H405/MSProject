//==============================================================================
//
// File   : ManagerTexture.cpp
// Brief  : �e�N�X�`���Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerTexture.h"
#include "Texture.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �e���v���[�g�錾
//******************************************************************************
template class ManagerTexture< class Texture >;

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerTexture< TypeItem >::ManagerTexture( void ) : ManagerResource()
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
ManagerTexture< TypeItem >::~ManagerTexture( void )
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
//==============================================================================
template< class TypeItem >
int ManagerTexture< TypeItem >::Initialize( TCHAR* pDirectory, int maximumItem, IDirect3DDevice9* pDevice )
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

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerTexture< TypeItem >::Finalize( void )
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
//==============================================================================
template< class TypeItem >
int ManagerTexture< TypeItem >::Reinitialize( TCHAR* pDirectory, int maximumItem, IDirect3DDevice9* pDevice )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDirectory, maximumItem, pDevice );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerTexture* pOut				: �R�s�[��A�h���X
//==============================================================================
template< class TypeItem >
int ManagerTexture< TypeItem >::Copy( ManagerTexture* pOut ) const
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
void ManagerTexture< TypeItem >::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pDevice_ = nullptr;
}

//==============================================================================
// Brief  : ���\�[�X�̓ǂݍ���
// Return : int									: ���s����
// Arg    : TCHAR* pPath						: �t�@�C���p�X
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
int ManagerTexture< TypeItem >::LoadResource( TCHAR* pPath, int index )
{
	// �摜���擾
	D3DXIMAGE_INFO	imageInfomation;		// �摜���
	D3DXGetImageInfoFromFile( pPath, &imageInfomation );

	// �e�N�X�`���̓ǂݍ���
	int					result;					// ���s����
	IDirect3DTexture9*	pTexture = nullptr;		// �e�N�X�`��
	result = D3DXCreateTextureFromFileEx( pDevice_, pPath, imageInfomation.Width, imageInfomation.Height,
		1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_POINT, D3DX_FILTER_NONE, 0, nullptr, nullptr, &pTexture );
	if( result != 0 )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"��������܂���" ), pPath );
		MessageBox( NULL, pStringError, _T( "�G���[" ), MB_OK );
		return 1;
	}

	// �e�N�X�`���̐���
	pBufferItem_[ index ].pItem_ = new Texture();
	if( pBufferItem_[ index ].pItem_ == nullptr )
	{
		return 1;
	}
	result = pBufferItem_[ index ].pItem_->Initialize( pTexture, imageInfomation.Width, imageInfomation.Height );
	if( result != 0 )
	{
		return result;
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
void ManagerTexture< TypeItem >::ReleaseResource( int index )
{
	// �e�N�X�`���̊J��
	if( pBufferItem_[ index ].pItem_ != nullptr )
	{
		pBufferItem_[ index ].pItem_->pTexture_->Release();
		pBufferItem_[ index ].pItem_->pTexture_ = nullptr;
	}
	delete pBufferItem_[ index ].pItem_;
	pBufferItem_[ index ].pItem_ = nullptr;
}
