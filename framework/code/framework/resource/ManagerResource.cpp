//==============================================================================
//
// File   : ManagerResource.cpp
// Brief  : ���\�[�X�Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <stdlib.h>
#include <string.h>
#include "ManagerResource.h"
#include "../develop/Debug.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �e���v���[�g�錾
//******************************************************************************
template class ManagerResource< class Effect >;
template class ManagerResource< class Model >;
template class ManagerResource< class Motion >;
template class ManagerResource< class Sound >;
template class ManagerResource< class Texture >;

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerResource< TypeItem >::ManagerResource( void )
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
ManagerResource< TypeItem >::~ManagerResource( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : TCHAR* pDirectory					: ��f�B���N�g��
// Arg    : int maximumItem						: �ő�v�f��
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Initialize( TCHAR* pDirectory, int maximumItem )
{
	// �����o�ϐ��̐ݒ�
	maximumItem_ = maximumItem;

	// ������̊i�[�̈���m��
	pDirectory_ = new TCHAR[ _MAX_PATH ];
	if( pDirectory_ == nullptr )
	{
		return 1;
	}
	memset( pDirectory_, 0x00, sizeof( TCHAR ) * _MAX_PATH );
	_tcscpy_s( pDirectory_, _MAX_PATH, pDirectory );

	// ���\�[�X�i�[�̈�̊m��
	pBufferItem_ = new Item[ maximumItem ];
	if( pBufferItem_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < maximumItem; ++counterItem )
	{
		pBufferItem_[ counterItem ].Initialize();
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Finalize( void )
{
	// ���\�[�X�̊J��
	for( int counterItem = 0; counterItem < maximumItem_; ++counterItem )
	{
		ReleaseResource( counterItem );
	}

	// �i�[�̈�̊J��
	delete[] pDirectory_;
	pDirectory_ = nullptr;

	delete[] pBufferItem_;
	pBufferItem_ = nullptr;

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
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Reinitialize( TCHAR* pDirectory, int maximumItem )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDirectory, maximumItem );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerResource* pOut				: �R�s�[��A�h���X
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Copy( ManagerResource* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���\�[�X�̓ǂݍ���
// Return : int									: ���\�[�XID
// Arg    : TCHAR* pNameFile					: �t�@�C����
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Load( TCHAR* pNameFile )
{
	// �G���[�`�F�b�N
	Assert( pNameFile != nullptr, _T( "�t�@�C���p�X���s���ł��B" ) );

	// �t�@�C���p�X�̍쐬
	TCHAR	pPath[ _MAX_PATH ] = {};		// �t�@�C���p�X
	_tcscpy_s( pPath, _MAX_PATH, pDirectory_ );
	_tcscat_s( pPath, _MAX_PATH, pNameFile );

	// ���ɍ���Ă��Ȃ�������
	int		index;		// �v�f�ԍ�
	index = GetId( pPath );
	if( index != -1 )
	{
		return index;
	}

	// �i�[�ꏊ�̌���
	for( index = 0; index < maximumItem_; ++index )
	{
		if( !pBufferItem_[ index ].isEnable_ )
		{
			break;
		}
	}
	if( index >= maximumItem_ )
	{
		PrintDebugWnd( _T( "���\�[�X�̊i�[�̈�ɋ󂫂�����܂���B" ) );
		return -1;
	}

	// ���\�[�X�̓ǂݍ���
	int		result;		// ���s����
	result = LoadResource( pPath, index );
	if( result != 0 )
	{
		return -1;
	}

	// �v�f�ɒl��ݒ�
	pBufferItem_[ index ].id_ = index;
	_tcscpy_s( pBufferItem_[ index ].pPath_, _MAX_PATH, pPath );
	pBufferItem_[ index ].isEnable_ = true;

	// ���\�[�XID��Ԃ�
	return index;
}

//==============================================================================
// Brief  : ���\�[�X�̎擾
// Return : TypeItem*							: ���\�[�X
// Arg    : TCHAR* pNameFile					: �t�@�C����
//==============================================================================
template< class TypeItem >
TypeItem* ManagerResource< TypeItem >::Get( TCHAR* pNameFile )
{
	// �G���[�`�F�b�N
	Assert( pNameFile != nullptr, _T( "�t�@�C���p�X���s���ł��B" ) );

	// �t�@�C���p�X�̍쐬
	TCHAR	pPath[ _MAX_PATH ] = {};		// �t�@�C���p�X
	_tcscpy_s( pPath, _MAX_PATH, pDirectory_ );
	_tcscat_s( pPath, _MAX_PATH, pNameFile );

	// ���ɍ���Ă��Ȃ�������
	int		index;		// �v�f�ԍ�
	index = GetId( pPath );
	if( index != -1 )
	{
		return pBufferItem_[ index ].pItem_;
	}

	// ����Ă��Ȃ��Ƃ��ǂݍ���
	index = Load( pNameFile );
	if( index == -1 )
	{
		return nullptr;
	}

	// ���\�[�X�̕ԋp
	return pBufferItem_[ index ].pItem_;
}

//==============================================================================
// Brief  : ���\�[�X�̎擾
// Return : TypeItem*							: ���\�[�X
// Arg    : int id								: ���\�[�XID
//==============================================================================
template< class TypeItem >
TypeItem* ManagerResource< TypeItem >::Get( int id )
{
	// �G���[�`�F�b�N
	Assert( id >= 0 && id < maximumItem_, _T( "�w�肵��ID���s���ł��B" ) );

	// ���\�[�X��Ԃ�
	return pBufferItem_[ id ].pItem_;
}

//==============================================================================
// Brief  : ���\�[�X�̊J��
// Return : void								: �Ȃ�
// Arg    : TCHAR* pNameFile					: �t�@�C����
//==============================================================================
template< class TypeItem >
void ManagerResource< TypeItem >::Release( TCHAR* pNameFile )
{
	// �t�@�C���p�X�̍쐬
	TCHAR	pPath[ _MAX_PATH ] = {};		// �t�@�C���p�X
	_tcscpy_s( pPath, _MAX_PATH, pDirectory_ );
	_tcscat_s( pPath, _MAX_PATH, pNameFile );

	// ���݂��Ă��邩����
	int		index;		// �v�f�ԍ�
	index = GetId( pPath );
	if( index == -1 )
	{
		return;
	}

	// ���\�[�X�̊J��
	ReleaseResource( index );
	pBufferItem_[ index ].pItem_ = nullptr;
	pBufferItem_[ index ].Reinitialize();
}

//==============================================================================
// Brief  : ���\�[�X�̊J��
// Return : void								: �Ȃ�
// Arg    : int id								: ���\�[�XID
//==============================================================================
template< class TypeItem >
void ManagerResource< TypeItem >::Release( int id )
{
	// ���\�[�X�����邩�m�F
	if( !pBufferItem_[ id ].isEnable_ )
	{
		return;
	}

	// ���\�[�X�̊J��
	ReleaseResource( id );
	pBufferItem_[ id ].pItem_ = nullptr;
	pBufferItem_[ id ].Reinitialize();
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
void ManagerResource< TypeItem >::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	maximumItem_ = 0;
	pDirectory_ = nullptr;
	pBufferItem_ = nullptr;
}

//==============================================================================
// Brief  : ���łɍ쐬����Ă��邩����
// Return : int									: ���\�[�X��ID
// Arg    : TCHAR* pPath						: �t�@�C���p�X
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::GetId( TCHAR* pPath )
{
	// �쐬����Ă��邩����
	for( int counterItem = 0; counterItem < maximumItem_; ++counterItem )
	{
		if( !_tcscmp( pPath, pBufferItem_[ counterItem ].pPath_ ) )
		{
			return counterItem;
		}
	}

	// �쐬����Ă��Ȃ�����
	return -1;
}

//==============================================================================
// Brief  : ���\�[�X�̓ǂݍ���
// Return : int									: ���s����
// Arg    : TCHAR* pPath						: �t�@�C���p�X
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::LoadResource( TCHAR* pPath, int index )
{
	// �l��Ԃ�
	return 0;
}

//==============================================================================
// Brief  : ���\�[�X�̊J��
// Return : void								: �Ȃ�
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
void ManagerResource< TypeItem >::ReleaseResource( int index )
{
}

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerResource< TypeItem >::Item::Item( void )
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
ManagerResource< TypeItem >::Item::~Item( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Item::Initialize( void )
{
	// ������̊i�[�̈���m��
	pPath_ = new TCHAR[ _MAX_PATH ];
	if( pPath_ == nullptr )
	{
		return 1;
	}
	memset( pPath_, 0x00, sizeof( TCHAR ) * _MAX_PATH );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Item::Finalize( void )
{
	// �i�[�̈�̊J��
	delete[] pPath_;
	pPath_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Item::Reinitialize( void )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize();
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
void ManagerResource< TypeItem >::Item::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	id_ = -1;
	pItem_ = nullptr;
	pPath_ = nullptr;
	isEnable_ = false;
}
