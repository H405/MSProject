//==============================================================================
// 
// File   : Debug.h
// Brief  : �f�o�b�O����
// Author : Taiga Shirakawa
// Date   : 2014/03/26 thr �F Taiga Shirakawa �F create
// 
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DEBUG_H
#define MY_DEBUG_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <tchar.h>
#include <windows.h>

//******************************************************************************
// ���C�u����
//******************************************************************************
#pragma comment( lib, "winmm.lib" )

//******************************************************************************
// enumeration
//******************************************************************************
// ���Ԍv���\�����@
typedef enum
{
	DEBUG_MEASURE_DISP_TYPE_NONE = 0,	// �\���Ȃ�
	DEBUG_MEASURE_DISP_TYPE_MSGBOX,		// ���b�Z�[�W�{�b�N�X
	DEBUG_MEASURE_DISP_TYPE_DEBUGWND,	// �f�o�b�O�E�B���h�E
	DEBUG_MEASURE_DISP_TYPE_MAX			// �ő�l
} DEBUG_MEASURE_DISP_TYPE;

//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEBUG_OUTPUT_DIRECTORY		"data/debug/"		// �f�o�b�O�����o���p�f�B���N�g��

//******************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************
void PrintMessageToMessageBox( TCHAR *pFormat, ... );									// ���b�Z�[�W�\��
#ifdef _DEVELOP
void DebugInitDebug( HWND hWnd, BOOL bWndMode );										// ����������
void PrintMessageToDebugWindow( TCHAR *pFormat, ... );									// �f�o�b�O���b�Z�[�W�\��
void DebugWarning( TCHAR *pFileName, int nLine, TCHAR *pFormat, ... );					// �x��
void DebugAssert( TCHAR *pExp, TCHAR *pFileName, int nLine, TCHAR *pFormat, ... );		// �A�T�[�g
void DebugBeginMeasureTime( void );														// ���Ԍv���J�n
DWORD DebugEndMeasureTime( DEBUG_MEASURE_DISP_TYPE type );								// ���Ԍv���I��
#endif

//******************************************************************************
// �֐��}�N����`
//******************************************************************************
#define PrintMsgBox						PrintMessageToMessageBox

#ifdef _DEVELOP

#define InitDebug( hWnd, bWndMode )		DebugInitDebug( hWnd, bWndMode )
#define PrintDebugWnd( pFormat, ... )	PrintMessageToDebugWindow( pFormat, __VA_ARGS__ )
#define Warning( pFormat, ... )			DebugWarning( _T( __FILE__ ), __LINE__, pFormat, __VA_ARGS__ )
#define Assert( exp, pFormat, ... )		if( !( exp ) ){ DebugAssert( _T( #exp ), _T( __FILE__ ), __LINE__, pFormat, __VA_ARGS__ ); __asm int 3 }
#define BeginMeasureTime()				DebugBeginMeasureTime()
#define EndMeasureTime( type )			DebugEndMeasureTime( type )

#else

#define InitDebug( hWnd, bWndMode )		static_cast< void >( 0 )
#define PrintDebugWnd( format, ... )	static_cast< void >( 0 )
#define Warning( format, ... )			static_cast< void >( 0 )
#define Assert( exp, pFormat, ... )		static_cast< void >( 0 )
#define BeginMeasureTime(  )			static_cast< void >( 0 )
#define EndMeasureTime( type )			static_cast< void >( 0 )

#endif

#endif // MY_DEBUG_H
