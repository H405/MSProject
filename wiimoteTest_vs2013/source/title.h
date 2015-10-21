//*****************************************************************************
//	 [ title.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"
#include "CSceneObject.h"

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CWiiController;
class CSceneTitle : public CSceneObject
{
public:

	CSceneTitle();
	~CSceneTitle(){};
	void Init(CRenderer* _renderer,
		CSound* _sound,
		CJoypad* _joypad = nullptr,
		CKeyboard* _keyboard = nullptr);
	void Uninit();
	void Update();
	void Draw();

	void InputUpdate();

private:

	CWiiController* wiiController;

};
#endif
//-----------------------------------EOF---------------------------------------