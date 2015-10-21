//==============================================================================
//
// File   : Main.cpp
// Brief  : ���C���֐�
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
// ���������[�N���o
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "Main.h"
#include "ManagerMain.h"
#include "../framework/system/FrameCount.h"
#include "../framework/develop/Debug.h"

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// prototype
//******************************************************************************

//******************************************************************************
// global member
//******************************************************************************
ManagerMain	g_manager_;			// �}�l�[�W���[
FrameCount	g_frameCount_;		// �t���[���J�E���g

//==============================================================================
// Brief  �F ���C���֐�
// Return �F int							�F ���s����
//        �F APIENTRY						�F Win32AD3DX_PI�֐����Ăяo�����̋K��
// Arg    �F HINSTANCE hInstance			�F ���̃A�v���P�[�V�����̃C���X�^���X�n���h��
// Arg    �F HINSTANCE hPrevInstance		�F ���NULL�i16bit����̖��c��j
// Arg    �F LPTSTR lpCmdLine				�F �R�}���h���C������󂯎���������ւ̃|�C���^
// Arg    �F int nCmdShow					�F �A�v���P�[�V�����̏����E�C���h�E�\�����@�̎w��
//==============================================================================
int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
#ifdef _DEBUG
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetBreakAlloc( 99 );
#endif

	// ���g�p�錾
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	// �t���[���J�E���g�̏�����
	int		result;		// ���s����
	result = g_frameCount_.Initialize( hInstance, nCmdShow, &g_manager_, MAIN_FPS_UPDATE_INTERVAL, MAIN_FPS_NUM_FRAME_DEST );
	if( result != 0 )
	{
		return result;
	}

	// �t���[���J�E���g�̎��s
	int		resultApplication;		// �A�v���P�[�V�����̎��s����
	resultApplication = g_frameCount_.Execute();

	// �I������
	result = g_frameCount_.Finalize();
	if( result != 0 )
	{
		return result;
	}

	result = g_manager_.Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return resultApplication;
}