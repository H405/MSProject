//==============================================================================
//
// File   : DebugMeasure.cpp
// Brief  : �f�o�b�O�v������
// Author : Taiga Shirakawa
// Date   : 2015/11/04 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <stdio.h>
#include <stdarg.h>
#include "DebugMeasure.h"
#include "Debug.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
TCHAR*	ManagerDebugMeasure::pBuffer_ = nullptr;		// ������i�[�p�o�b�t�@

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerDebugMeasure::Initialize( void )
{
	// �o�b�t�@�̊m��
	pBuffer_ = nullptr;
	pBuffer_ = new TCHAR[ MAXIMUM_SIZE_BUFFER ];
	if( pBuffer_ == nullptr )
	{
		return 1;
	}
	ZeroMemory( pBuffer_, sizeof( TCHAR ) * MAXIMUM_SIZE_BUFFER );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerDebugMeasure::Finalize( void )
{
	// �i�[���Ȉ�̊J��
	delete[] pBuffer_;
	pBuffer_ = nullptr;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���O�̐ݒ�
// Return : int									: ���s����
// Arg    : const TCHAR* pLog					: ���O
//==============================================================================
void ManagerDebugMeasure::SetLog( const TCHAR* pLog )
{
	// ��������o�b�t�@�֒ǉ�
	_tcscat_s( pBuffer_, MAXIMUM_SIZE_BUFFER, pLog );
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerDebugMeasure::Update( void )
{
	// ���O�̏o��
	PrintDebug( pBuffer_ );

	// �o�b�t�@����ɂ���
	ZeroMemory( pBuffer_, sizeof( TCHAR ) * MAXIMUM_SIZE_BUFFER );
}

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : int									: ���s����
// Arg    : const TCHAR* pLog					: ���O
//==============================================================================
DebugMeasure::DebugMeasure( TCHAR* pFormat, ... )
{
	// �o�b�t�@�̊m��
	pBuffer_ = nullptr;
	pBuffer_ = new TCHAR[ 256 ];
	if( pBuffer_ == nullptr )
	{
		return;
	}

	ZeroMemory( pBuffer_, sizeof( TCHAR ) * 256 );

	// �\��������쐬
	TCHAR	pStringAdd[ 256 ] = {};		// �ǉ����镶����
	va_list	args;						// ����
	va_start( args, pFormat );
	_vsntprintf_s( pStringAdd, 256, _TRUNCATE, pFormat, args );
	va_end( args );

	// �\��������L�^
	_tcscat_s( pBuffer_, 256, pStringAdd );

	// �v���̊J�n
	timeBegin_ = timeGetTime();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : void								: 
// Arg    : void								: �Ȃ�
//==============================================================================
DebugMeasure::~DebugMeasure( void )
{
	// �v���̏I��
	DWORD	time;		// ����
	time = timeGetTime() - timeBegin_;

	// ���O�̐ݒ�
	TCHAR	pLog[ 256 ] = {};			// ���O
	TCHAR	pMeasure[ 64 ] = {};		// �v�����ʕ�����
	_stprintf_s( pMeasure, 64, _T( " : %5dms\n" ), time );
	_tcscpy_s( pLog, 256, pBuffer_ );
	_tcscat_s( pLog, 256, pMeasure );
	ManagerDebugMeasure::SetLog( pLog );

	// �o�b�t�@�̊J��
	delete[] pBuffer_;
	pBuffer_ = nullptr;
}
