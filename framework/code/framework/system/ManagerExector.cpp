//==============================================================================
//
// File   : ManagerExector.cpp
// Brief  : ���s�N���X�̊�{�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/10 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerExector.h"
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
template class ManagerExector< class Graphic >;
template class ManagerExector< class Object >;

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerExector< TypeItem >::ManagerExector( void )
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
ManagerExector< TypeItem >::~ManagerExector( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int maximumItem						: �ő�v�f��
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Initialize( int maximumItem )
{
	// �����o�ϐ��̐ݒ�
	countItem_ = maximumItem;
	pBufferItem_ = new Item[ maximumItem ];
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
int ManagerExector< TypeItem >::Finalize( void )
{
	// �i�[�̈�̊J��
	delete[] pBufferItem_;
	pBufferItem_ = nullptr;

	// �N���X�����̏�����
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int maximumItem						: �ő�v�f��
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Reinitialize( int maximumItem )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( maximumItem );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerExector* pOut				: �R�s�[��A�h���X
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Copy( ManagerExector* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���s
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Execute( void )
{
	// �o�^�����t���O�̗����Ă���v�f�̓o�^������
	UnregisterNeed();

	// �l�̕ԋp
	return 0;
}

//==============================================================================
// Brief  : �o�^
// Return : int									: �o�^ID
// Arg    : TypeItem* pItem						: �o�^����v�f
// Arg    : int priority						: �D��x
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Register( TypeItem* pItem, int priority )
{
	// �󂢂Ă���ꏊ�̌���
	int		id;		// �ݒ肷��ID
	for( id = 0; id < countItem_; ++id )
	{
		if( !pBufferItem_[ id ].isEnable_ && !pBufferItem_[ id ].needsUnregister_ )
		{
			break;
		}
	}
	if( id >= countItem_ )
	{
		PrintDebugWnd( _T( "�`��Ǘ��N���X�̗v�f�ɋ󂫂�����܂���B" ) );
		return -1;
	}

	// �v�f�̕��т�����
	int		indexNext = -1;			// ���̗v�f�ԍ�
	int		indexPrevious = -1;		// �O�̗v�f�ԍ�
	int		indexCurrent;			// ���݂̔ԍ�
	for( indexCurrent = indexTop_; indexCurrent >= 0; indexCurrent = pBufferItem_[ indexCurrent ].indexNext_ )
	{
		if( pBufferItem_[ indexCurrent ].priority_ < priority )
		{
			indexPrevious = pBufferItem_[ indexCurrent ].indexPrevious_;
			indexNext = indexCurrent;
			break;
		}
		if( pBufferItem_[ indexCurrent ].indexNext_ < 0 )
		{
			indexPrevious = indexCurrent;
			indexNext = -1;
			break;
		}
	}

	// �[�̐ݒ�
	if( indexPrevious < 0 )
	{
		indexTop_ = id;
	}
	if( indexNext < 0 )
	{
		indexTail_ = id;
	}

	// �v�f�̐ݒ�
	pBufferItem_[ id ].id_ = id;
	pBufferItem_[ id ].priority_ = priority;
	pBufferItem_[ id ].indexNext_ = indexNext;
	pBufferItem_[ id ].indexPrevious_ = indexPrevious;
	pBufferItem_[ id ].pItem_ = pItem;
	pBufferItem_[ id ].needsUnregister_ = false;
	pBufferItem_[ id ].isEnable_ = true;

	// �O��̗v�f�̕��т�ݒ�
	if( indexNext != -1 )
	{
		pBufferItem_[ indexNext ].indexPrevious_ = id;
	}
	if( indexPrevious != -1 )
	{
		pBufferItem_[ indexPrevious ].indexNext_ = id;
	}

	// ID�̕ԋp
	return id;
}

//==============================================================================
// Brief  : �o�^����
// Return : void								: �Ȃ�
// Arg    : int id								: �Ώ�ID
//==============================================================================
template< class TypeItem >
void ManagerExector< TypeItem >::Unregister( int id )
{
	// �G���[�`�F�b�N
	Assert( id >= -1 && id < countItem_, _T( "�����̒l���s���ł��B" ) );
	if( id == -1 )
	{
		return;
	}

	// �o�^�����t���O�𗧂Ă�
	pBufferItem_[ id ].isEnable_ = false;
	pBufferItem_[ id ].needsUnregister_ = true;
}

//==============================================================================
// Brief  : �L���t���O�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : bool value							: �ݒ肷��l
//==============================================================================
template< class TypeItem >
void ManagerExector< TypeItem >::SetIsEnable( bool value )
{
	// �l�̐ݒ�
	isEnable_ = value;
}

//==============================================================================
// Brief  : �L���t���O�̎擾
// Return : bool								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
bool ManagerExector< TypeItem >::GetIsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �L���t���O�̔���
// Return : bool								: ���茋��
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
bool ManagerExector< TypeItem >::IsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
void ManagerExector< TypeItem >::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pBufferItem_ = nullptr;
	indexTop_ = -1;
	indexTail_ = -1;
	isEnable_ = true;
}

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerExector< TypeItem >::Item::Item( void )
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
ManagerExector< TypeItem >::Item::~Item( void )
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
int ManagerExector< TypeItem >::Item::Initialize( void )
{
	// �N���X�����̏�����
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Item::Finalize( void )
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Item::Reinitialize( void )
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
void ManagerExector< TypeItem >::Item::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	id_ = -1;
	priority_ = 0;
	indexNext_ = -1;
	indexPrevious_ = -1;
	pItem_ = nullptr;
	needsUnregister_ = false;
	isEnable_ = false;
}

//==============================================================================
// Brief  : �v�f�̓o�^����
// Return : void								: �Ȃ�
// Arg    : int id								: �Ώ�ID
//==============================================================================
template< class TypeItem >
void ManagerExector< TypeItem >::UnregisterItem( int id )
{
	// �G���[�`�F�b�N
	Assert( id >= 0 && id < countItem_, _T( "�����̒l���s���ł��B" ) );

	// �[�̐ݒ�
	if( id == indexTop_ )
	{
		indexTop_ = pBufferItem_[ id ].indexNext_;
	}
	if( id == indexTail_ )
	{
		indexTail_ = pBufferItem_[ id ].indexPrevious_;
	}

	// �O��̕��т�ݒ�
	if( pBufferItem_[ id ].indexNext_ != -1 )
	{
		pBufferItem_[ pBufferItem_[ id ].indexNext_ ].indexPrevious_ = pBufferItem_[ id ].indexPrevious_;
	}
	if( pBufferItem_[ id ].indexPrevious_ != -1 )
	{
		pBufferItem_[ pBufferItem_[ id ].indexPrevious_ ].indexNext_ = pBufferItem_[ id ].indexNext_;
	}

	// �v�f�̍ď�����
	pBufferItem_[ id ].Reinitialize();
}

//==============================================================================
// Brief  : �o�^�����t���O�̗����Ă���v�f�̓o�^����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
void ManagerExector< TypeItem >::UnregisterNeed( void )
{
	// �o�^�̉���
	int		indexItemCurrent;		// ���݂̗v�f�ԍ�
	int		indexItemNext;			// ���̗v�f�ԍ�
	indexItemNext = -1;
	for( indexItemCurrent = indexTop_; indexItemCurrent >= 0; indexItemCurrent = indexItemNext )
	{
		indexItemNext = pBufferItem_[ indexItemCurrent ].indexNext_;
		if( pBufferItem_[ indexItemCurrent ].needsUnregister_ )
		{
			UnregisterItem( indexItemCurrent );
		}
	}
}
