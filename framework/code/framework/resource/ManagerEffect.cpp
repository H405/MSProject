//==============================================================================
//
// File   : ManagerEffect.cpp
// Brief  : �G�t�F�N�g�Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/16 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerEffect.h"
#include "Effect.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �e���v���[�g�錾
//******************************************************************************
template class ManagerEffect< class Effect >;

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerEffect< TypeItem >::ManagerEffect( void ) : ManagerResource()
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
ManagerEffect< TypeItem >::~ManagerEffect( void )
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
int ManagerEffect< TypeItem >::Initialize( TCHAR* pDirectory, int maximumItem, IDirect3DDevice9* pDevice )
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
int ManagerEffect< TypeItem >::Finalize( void )
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
int ManagerEffect< TypeItem >::Reinitialize( TCHAR* pDirectory, int maximumItem, IDirect3DDevice9* pDevice )
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
// Arg    : ManagerEffect* pOut					: �R�s�[��A�h���X
//==============================================================================
template< class TypeItem >
int ManagerEffect< TypeItem >::Copy( ManagerEffect* pOut ) const
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
void ManagerEffect< TypeItem >::InitializeSelf( void )
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
int ManagerEffect< TypeItem >::LoadResource( TCHAR* pPath, int index )
{
	// �G�t�F�N�g�̓ǂݍ���
	int				result;					// ���s����
	ID3DXEffect*	pEffect = nullptr;		// �G�t�F�N�g
	DWORD			flagLoad;				// �ǂݍ��݃t���O
#ifdef _DEBUG
	flagLoad = 0;
#else
	flagLoad = D3DXSHADER_SKIPVALIDATION;
#endif
	result = D3DXCreateEffectFromFile( pDevice_, pPath, nullptr, nullptr, flagLoad, nullptr, &pEffect, nullptr );
	if( result != 0 )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"��������܂���" ), pPath );
		MessageBox( NULL, pStringError, _T( "�G���[" ), MB_OK );
		return 1;
	}

	// �G�t�F�N�g�̐���
	pBufferItem_[ index ].pItem_ = new Effect();
	if( pBufferItem_[ index ].pItem_ == nullptr )
	{
		return 1;
	}
	result = pBufferItem_[ index ].pItem_->Initialize( pEffect );
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
void ManagerEffect< TypeItem >::ReleaseResource( int index )
{
	// �G�t�F�N�g�̊J��
	if( pBufferItem_[ index ].pItem_ != nullptr )
	{
		pBufferItem_[ index ].pItem_->pEffect_->Release();
		pBufferItem_[ index ].pItem_->pEffect_ = nullptr;
	}
	delete pBufferItem_[ index ].pItem_;
	pBufferItem_[ index ].pItem_ = nullptr;
}
