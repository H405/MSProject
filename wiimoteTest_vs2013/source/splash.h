//*****************************************************************************
//	 [ splash.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _SPLASH_H_
#define _SPLASH_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"
#include "CSceneObject.h"

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CSceneSplash : public CSceneObject
{
public:

	CSceneSplash();
	~CSceneSplash(){};
	void Init(CRenderer* _renderer,
		CSound* _sound,
		CJoypad* _joypad = nullptr,
		CKeyboard* _keyboard = nullptr);
	void Uninit();
	void Update();
	void Draw();


	void InputUpdate();

private:

	int timer;	//	自動遷移用タイマー
};
#endif
//-----------------------------------EOF---------------------------------------