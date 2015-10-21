//*****************************************************************************
//	���C������ [main.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h
//*****************************************************************************
#include "main.h"
#include "CManager.h"
#include <time.h>

//*****************************************************************************
//	�}�N����`
//*****************************************************************************
#define CLASS_NAME	"defaultProject"
#define WINDOW_NAME	"defaultProject"

//*****************************************************************************
//	�v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND _windowHandle, UINT _msg, WPARAM _wParam, LPARAM _lParam);
HRESULT MainInit(HINSTANCE _instanceHandle, HWND _windowHandle, BOOL _windowMode);

//*****************************************************************************
//	�O���[�o���ϐ�
//*****************************************************************************
#ifdef _DEBUG

int countFPS;	//	FPS�J�E���^

#endif

CManager* manager;

//=============================================================================
//	�G���g���[�֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE _instanceHandle ,HINSTANCE _instanceHandlePrev, LPSTR _cmdLine, int _cmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(_instanceHandlePrev);
	UNREFERENCED_PARAMETER(_cmdLine);

	DWORD execLastTime;
	DWORD LastTimeFPS;
	DWORD currentTime;
	DWORD flameCount;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		_instanceHandle,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	HWND windowHandle;
	MSG msg;
	
	//	�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//	�E�B���h�E�̍쐬
	windowHandle = CreateWindowEx(0,
								  CLASS_NAME,
								  WINDOW_NAME,
								  WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
								  CW_USEDEFAULT,
								  CW_USEDEFAULT,
								  static_cast<int>(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
								  static_cast<int>(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
								  NULL,
								  NULL,
								  _instanceHandle,
								  NULL);

	//	�}�l�[�W���[�쐬
	manager = new CManager();

#ifndef _DEBUG

	manager->Init(_instanceHandle, windowHandle, TRUE);

#else
	//	�f�o�b�O���[�h
	manager->Init(_instanceHandle, windowHandle, TRUE);
#endif

	//	�t���[���J�E���g������
	timeBeginPeriod(1);	//	����\��ݒ�
	execLastTime = LastTimeFPS = timeGetTime();
	currentTime = flameCount = 0;

	//	�E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(windowHandle, _cmdShow);
	UpdateWindow(windowHandle);
	
	//	���b�Z�[�W���[�v
	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				//	PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				//	���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			currentTime = timeGetTime();
			if ((currentTime - LastTimeFPS) >= 500)
			{
				#ifdef _DEBUG
					countFPS = flameCount * 1000 / (currentTime - LastTimeFPS);
				#endif

				LastTimeFPS = currentTime;
				flameCount = 0;
			}

			//	30fps
			if ((currentTime - execLastTime) >= (1000 / 60))
			{
				execLastTime = currentTime ;

				manager->Update();

#ifdef _DEBUG
				CDebug::SetDebug("FPS = %d", countFPS);
#endif

				manager->Draw();

				flameCount++;
			}
		}
	}

	//	�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	timeEndPeriod(1);	//	����\��߂�

	SAFE_DELETE(manager);

	return static_cast<int>(msg.wParam);
}
//=============================================================================
//	�E�B���h�E�Y�v���V�[�W���֐�
//=============================================================================
LRESULT CALLBACK WndProc(HWND _windowHandle, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	switch(_msg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);
		
		break;

	case WM_KEYDOWN:

		switch(_wParam)
		{
		case VK_ESCAPE:
			
			DestroyWindow(_windowHandle);
			
			break;
		}
		break;

	default:

		break;
	}

	return DefWindowProc(_windowHandle, _msg, _wParam, _lParam);
}

//-----------------------------------EOF---------------------------------------