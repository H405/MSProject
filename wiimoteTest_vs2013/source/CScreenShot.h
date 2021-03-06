//*****************************************************************************
//	スクリーンショット処理 [ CScreenShot.h ]
//	Author : KOTARO NAGASAKI
//	create : 12/16
//	Update : 12/16
//*****************************************************************************
#ifndef _CSCREENSHOT_H_
#define _CSCREENSHOT_H_


//	定義している場合、スクリーンショットが撮影可能
#define SCREENSHOT_ON

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CScreenShot
{
public:

	//*****************************************************************************
	//	関数定義
	//*****************************************************************************
	CScreenShot(LPDIRECT3DDEVICE9 _device, BOOL _window, HWND _windowHandle);
	~CScreenShot();
	void Init(LPDIRECT3DDEVICE9 _device, BOOL _window, HWND _windowHandle);
	void Create();

private:

	//*****************************************************************************
	//	変数定義
	//*****************************************************************************
	static int index;	//	スクリーンショット画像の番号
	LPDIRECT3DDEVICE9 device;	//	デバイス
	BOOL windowMode;	//	ウィンドウモード
	HWND windowHandle;	//	ウィンドウハンドル
};
#endif

//	EOF