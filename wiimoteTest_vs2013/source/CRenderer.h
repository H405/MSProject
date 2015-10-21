//*****************************************************************************
//	レンダラー [CRenderer.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _CRENDERER_H_
#define _CRENDERER_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"
#include "CScreenShot.h"

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CScene;
class CCamera;
class CObj2D;
class CObj2DKeyFrame;
class CObj2DLoop;
class CScreenShot;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	void Init(HWND _windowHandle, BOOL _windowMode);
	void Update();
	void Draw(CCamera* _camara);
	void Draw();

	LPDIRECT3DDEVICE9 GetDevice();

#ifdef SCREENSHOT_ON
	void SetScreenShotFlag(bool _flag){ screenShotFlag = _flag; };
#endif

private:

	void DrawFPS();

	LPDIRECT3D9 direct3D;	//	Direct3D9用デバイス
	LPDIRECT3DDEVICE9 device;	//	_deviceオブジェクト(描画に必要)

#ifdef SCREENSHOT_ON
	static CScreenShot *screenShot;	//	スクリーンショットオブジェクト
	bool screenShotFlag;	//	スクリーンショット撮影ON/OFFフラグ
#endif
};

#endif

//-----------------------------------EOF---------------------------------------