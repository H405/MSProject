//==============================================================================
//
// File   : ManagerUpdate.cpp
// Brief  : �X�V���s�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerUpdate.h"
#include "../develop/DebugProc.h"
#include "../object/Object.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �e���v���[�g�錾
//******************************************************************************
template class ManagerUpdate< class Object >;

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerUpdate< TypeItem >::ManagerUpdate( void ) : ManagerExector()
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
ManagerUpdate< TypeItem >::~ManagerUpdate( void )
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
int ManagerUpdate< TypeItem >::Initialize( int maximumItem )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerExector::Initialize( maximumItem );
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
template< class TypeItem >
int ManagerUpdate< TypeItem >::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerExector::Finalize();
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
// Arg    : int maximumItem						: �ő�v�f��
//==============================================================================
template< class TypeItem >
int ManagerUpdate< TypeItem >::Reinitialize( int maximumItem )
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
// Arg    : ManagerUpdate* pOut					: �R�s�[��A�h���X
//==============================================================================
template< class TypeItem >
int ManagerUpdate< TypeItem >::Copy( ManagerUpdate* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerExector::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���s
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerUpdate< TypeItem >::Execute( void )
{
	// �I�u�W�F�N�g�̍X�V
	int		indexItemCurrent;		// ���݂̗v�f�ԍ�
	int	a = 0;
	for( indexItemCurrent = indexTop_; indexItemCurrent >= 0; indexItemCurrent = pBufferItem_[ indexItemCurrent ].indexNext_ )
	{
		if( pBufferItem_[ indexItemCurrent ].needsUnregister_ || !pBufferItem_[ indexItemCurrent ].isEnable_ || !pBufferItem_[ indexItemCurrent ].pItem_->IsEnable() )
		{
			continue;
		}
		pBufferItem_[ indexItemCurrent ].pItem_->Update();
		++a;
	}
	PrintDebug( "Update : %d", a );

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerExector::Execute();
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
void ManagerUpdate< TypeItem >::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
