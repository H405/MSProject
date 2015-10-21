//*****************************************************************************
//	 [ game.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"
#include "CSceneObject.h"

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CWiiController;
class CObj2D;
class CSceneGame : public CSceneObject
{
public:

	CSceneGame();
	~CSceneGame(){};
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
	CObj2D* obj2D;

	int counter;

};
#endif
//-----------------------------------EOF---------------------------------------