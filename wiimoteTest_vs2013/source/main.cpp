//*****************************************************************************
//	メイン処理 [main.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード
//*****************************************************************************
#include "main.h"
#include "CManager.h"
#include <time.h>

//*****************************************************************************
//	マクロ定義
//*****************************************************************************
#define CLASS_NAME	"defaultProject"
#define WINDOW_NAME	"defaultProject"

//*****************************************************************************
//	プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND _windowHandle, UINT _msg, WPARAM _wParam, LPARAM _lParam);
HRESULT MainInit(HINSTANCE _instanceHandle, HWND _windowHandle, BOOL _windowMode);

//*****************************************************************************
//	グローバル変数
//*****************************************************************************
#ifdef _DEBUG

int countFPS;	//	FPSカウンタ

#endif

CManager* manager;

//=============================================================================
//	エントリー関数
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
	
	//	ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//	ウィンドウの作成
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

	//	マネージャー作成
	manager = new CManager();

#ifndef _DEBUG

	manager->Init(_instanceHandle, windowHandle, TRUE);

#else
	//	デバッグモード
	manager->Init(_instanceHandle, windowHandle, TRUE);
#endif

	//	フレームカウント初期化
	timeBeginPeriod(1);	//	分解能を設定
	execLastTime = LastTimeFPS = timeGetTime();
	currentTime = flameCount = 0;

	//	ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(windowHandle, _cmdShow);
	UpdateWindow(windowHandle);
	
	//	メッセージループ
	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				//	PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				//	メッセージの翻訳とディスパッチ
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

	//	ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	timeEndPeriod(1);	//	分解能を戻す

	SAFE_DELETE(manager);

	return static_cast<int>(msg.wParam);
}
//=============================================================================
//	ウィンドウズプロシージャ関数
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