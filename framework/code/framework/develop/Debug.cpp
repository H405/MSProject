//==============================================================================
// 
// File   : Debug.h
// Brief  : �f�o�b�O����
// Author : Taiga Shirakawa
// Date   : 2014/03/26 thr �F Taiga Shirakawa �F create
// 
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <stdarg.h>
#include <stdio.h>
#include "debug.h"

//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEBUG_OUTPUT_STRING_LEN		(256)		// �ő�\��������

//******************************************************************************
// value
//******************************************************************************
#ifdef _DEBUG
DWORD	g_dwDebugMeasureStartTime = 0;			// �v���J�n����
BOOL	g_bWindowModeDebug = TRUE;				// �E�B���h�E���[�h
#endif
HWND	g_hWndDebug = NULL;						// ���b�Z�[�W�{�b�N�X�p�E�B���h�E�n���h��

//==============================================================================
// Brief  �F ���b�Z�[�W�\��
// Return �F void							�F �Ȃ�
// Arg    �F TCHAR *pFormat					�F �\�����b�Z�[�W�t�H�[�}�b�g
//==============================================================================
void PrintMessageToMessageBox( TCHAR *pFormat, ... )
{
	TCHAR	aStr[ DEBUG_OUTPUT_STRING_LEN ];		// �\��������
	va_list	args;									// ����
	
	// �\��������쐬
	va_start( args, pFormat );
	_vsntprintf_s( &aStr[ 0 ], DEBUG_OUTPUT_STRING_LEN, _TRUNCATE, pFormat, args );
	va_end( args );

	// ���b�Z�[�W�{�b�N�X�ɏo��
	MessageBox( g_hWndDebug, &aStr[ 0 ], _T( "Message" ), MB_OK );
}

#ifdef _DEBUG
//==============================================================================
// Brief  �F ����������
// Return �F void							�F �Ȃ�
// Arg    �F HWND hWnd						�F �E�B���h�E�n���h��
// Arg    �F BOOL bWndMode					�F �E�B���h�E���[�h�t���O
//==============================================================================
void DebugInitDebug( HWND hWnd, BOOL bWndMode )
{
	g_hWndDebug = hWnd;
	g_bWindowModeDebug = bWndMode;
}

//==============================================================================
// Brief  �F �f�o�b�O���b�Z�[�W�\��
// Return �F void							�F �Ȃ�
// Arg    �F TCHAR *pFormat					�F �\�����b�Z�[�W�t�H�[�}�b�g
//==============================================================================
void PrintMessageToDebugWindow( TCHAR *pFormat, ... )
{
	TCHAR	aStr[ DEBUG_OUTPUT_STRING_LEN ];		// �\��������
	va_list	args;									// ����
	
	// �\��������쐬
	va_start( args, pFormat );
	_vsntprintf_s( &aStr[ 0 ], DEBUG_OUTPUT_STRING_LEN, _TRUNCATE, pFormat, args );
	va_end( args );

	// �f�o�b�O�E�B���h�E�ɏo��
	OutputDebugString( &aStr[ 0 ] );
}

//==============================================================================
// Brief  �F �x��
// Return �F void							�F �Ȃ�
// Arg    �F TCHAR *pFileName				�F �t�@�C����
// Arg    �F int *nLine						�F �s�ԍ�
// Arg    �F TCHAR *pFormat					�F �\�����b�Z�[�W�t�H�[�}�b�g
//==============================================================================
void DebugWarning( TCHAR *pFileName, int nLine, TCHAR *pFormat, ... )
{
	TCHAR	aStr[ DEBUG_OUTPUT_STRING_LEN ];		// �\��������
	va_list	args;									// ����
	
	// �\��������쐬
	va_start( args, pFormat );
	_vsntprintf_s( &aStr[ 0 ], DEBUG_OUTPUT_STRING_LEN, _TRUNCATE, pFormat, args );
	va_end( args );

	// �G���[���b�Z�[�W�o��
	PrintMessageToMessageBox( _T( "����������WARNING����������\n%s��%d�s��\n%s\n" ), pFileName, nLine, &aStr[ 0 ] );
	PrintMessageToDebugWindow( _T( "����������WARNING����������\n%s��%d�s��\n%s\n" ), pFileName, nLine, &aStr[ 0 ] );
}

//==============================================================================
// Brief  �F �A�T�[�g
// Return �F void							�F �Ȃ�
// Arg    �F TCHAR *pExp					�F ���������������
// Arg    �F TCHAR *pFileName				�F �t�@�C����
// Arg    �F int *nLine						�F �s�ԍ�
// Arg    �F TCHAR *pFormat					�F �\�����b�Z�[�W�t�H�[�}�b�g
//==============================================================================
void DebugAssert( TCHAR *pExp, TCHAR *pFileName, int nLine, TCHAR *pFormat, ... )
{
	TCHAR	aStr[ DEBUG_OUTPUT_STRING_LEN ];		// �\��������
	va_list	args;									// ����
	
	// �\��������쐬
	va_start( args, pFormat );
	_vsntprintf_s( &aStr[ 0 ], DEBUG_OUTPUT_STRING_LEN, _TRUNCATE, pFormat, args );
	va_end( args );

	// �G���[���b�Z�[�W�o��
	PrintMessageToMessageBox( _T( "����������ASSERT����������\n%s��%d�s��\n%s\n%s\n" ), pFileName, nLine, pExp, &aStr[ 0 ] );
	PrintMessageToDebugWindow( _T( "\n����������ASSERT����������\n%s��%d�s��\n%s\n%s\n\n" ), pFileName, nLine, pExp, &aStr[ 0 ] );

	// �I��
	if( !g_bWindowModeDebug )
	{	// �t���X�N���[�����[�h�̂Ƃ��̓u���[�N���Ȃ�
		abort(  );
	}
	if( MessageBox( g_hWndDebug, _T( "�f�o�b�O���I�����܂����H\n" ), _T( "�m�F" ), MB_YESNO ) == IDYES )
	{
		abort(  );
	}
}

//==============================================================================
// Brief  �F ���Ԍv���J�n
// Return �F void							�F �Ȃ�
// Arg    �F void							�F �Ȃ�
//==============================================================================
void DebugBeginMeasureTime( void )
{
	g_dwDebugMeasureStartTime = timeGetTime(  );
}

//==============================================================================
// Brief  �F ���Ԍv���I��
// Return �F DWORD							�F �v������
// Arg    �F DEBUG_MEASURE_DISP_TYPE type	�F �v�����ʕ\�����@
//==============================================================================
DWORD DebugEndMeasureTime( DEBUG_MEASURE_DISP_TYPE type )
{
	DWORD	dwMeasureTime = timeGetTime(  ) - g_dwDebugMeasureStartTime;		// �v������

	// �v�����ʂ̕\��
	switch( type )
	{
	case DEBUG_MEASURE_DISP_TYPE_MSGBOX:
		PrintMessageToMessageBox( _T( "�v������ : %d �~���b\n" ), dwMeasureTime );
		break;
	case DEBUG_MEASURE_DISP_TYPE_DEBUGWND:
		PrintMessageToDebugWindow( _T( "�v������ : %d �~���b\n" ), dwMeasureTime );
		break;
	default:
		break;
	}

	// �v�����ʂ�Ԃ�
	return dwMeasureTime;
}
#endif	// _DEBUG
