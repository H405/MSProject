//*****************************************************************************
//	マネージャー [CManager.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _CMANAGER_H_
#define _CMANAGER_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CRenderer;
class CSceneManager;
class CKeyboard;
class CMovie;
class CWiiController;
class CManager
{
public:

	CManager();
	~CManager();
	void Init(HINSTANCE _instanceHandle, HWND _windowHandle, bool _windowMode);
	void Update();
	void Draw();

	static CRenderer* GetRenderer(void){return renderer;};
	static CSceneManager* GetSceneManager(){ return sceneManager; };

	static CWiiController* getWiiController(){ return wiiController; }

private:

	static CRenderer* renderer;
	static CSceneManager* sceneManager;
	static CKeyboard* keyboard;
	static CMovie* movie;

	static CWiiController* wiiController;

#ifdef _DEBUG
	static CDebug* debug;
#endif
};
#endif

//-----------------------------------EOF---------------------------------------