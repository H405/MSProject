//*****************************************************************************
//	 [ CSceneObject.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"
#include "CSceneManager.h"

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CRenderer;
class CSound;
class CKeyboard;
class CJoypad;
//	このクラスは単体で使わない
//	CScene同様に、多態性を上手く使って様々なシーン処理を行う(CSceneManagerに行わせる)
class CSceneObject
{
public:

	//*****************************************************************************
	//	関数定義
	//*****************************************************************************
	CSceneObject();
	virtual ~CSceneObject(){};
	virtual void Init(CRenderer* _renderer,
		CSound* _sound,
		CJoypad* _joypad = nullptr,
		CKeyboard* _keyboard = nullptr) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void SetSceneChange(CSceneManager::SCENE_MODE _changeSceneMode){ sceneChangeFlag = true; changeSceneMode = _changeSceneMode; };

protected:

	//*****************************************************************************
	//	変数定義
	//*****************************************************************************
	LPDIRECT3DDEVICE9 device;
	CRenderer* renderer;
	CSound* sound;
	CKeyboard* keyboard;
	CJoypad* joypad;
	bool sceneChangeFlag;
	CSceneManager::SCENE_MODE changeSceneMode;
};

#endif
//-----------------------------------EOF---------------------------------------