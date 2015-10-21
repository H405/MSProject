//*****************************************************************************
//	 [ CSceneManager.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CRenderer;
class CSound;
class CKeyboard;
class CJoypad;
class CSceneObject;
class CSceneManager
{
public:

	//*****************************************************************************
	//	列挙体定義
	//*****************************************************************************
	typedef enum
	{
		SCENE_SPLASH = 0,
		SCENE_TITLE,
		SCENE_STAGE_SELECT,
		SCENE_GAME,
		SCENE_RESULT,
		SCENE_MAX
	}SCENE_MODE;

	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT
	}FADE_MODE;

	//*****************************************************************************
	//	関数定義
	//*****************************************************************************
	CSceneManager(){};
	~CSceneManager();
	void Init(SCENE_MODE _sceneMode,
		CRenderer* _renderer,
		CSound* _sound,
		CJoypad* _joypad = nullptr,
		CKeyboard* _keyboard = nullptr);
	void Uninit();
	void Update();
	void Draw();
	void SetScene();
	void SetFadeIn(SCENE_MODE _nextScene);
	CSceneObject* GetSceneObject(){ return scene; };
	FADE_MODE GetFadeMode(){ return fadeMode; };
	bool GetChangeFlag(){ return changeFlag; };
	void SetChangeFlag(bool _setFlag){ changeFlag = _setFlag; };

	void nowLoading();

	static void setMyAdd(CSceneManager* _add){ myAdd = _add; };
	void setThreadFlag(bool _flag){ threadFlag = _flag; };
	void setThreadEndFlag(bool _flag){ threadEndFlag = _flag; };

private:

	//*****************************************************************************
	//	関数定義
	//*****************************************************************************
	void NormalUpdate();
	void FadeUpdate();
	void ChangeScene();

	//*****************************************************************************
	//	変数定義
	//*****************************************************************************
	SCENE_MODE curScene;	//	今のシーン
	SCENE_MODE prevScene;	//	前のシーン
	SCENE_MODE nextScene;	//	次のシーン
	FADE_MODE fadeMode;	//	フェード状態
	LPDIRECT3DDEVICE9 device;	//	デバイス
	CSceneObject* scene;	//	現在のシーンオブジェクト保存
	CRenderer* renderer;	//	レンダラー
	CSound* sound;	//	サウンド
	CKeyboard* keyboard;	//	キーボード
	CJoypad* joypad;	///	ジョイパッド
	void (CSceneManager::*fpUpdate)(void);	//	更新関数セット用関数ポインタ
	bool changeFlag;	//	シーン切り替えフラグ

	static unsigned __stdcall fpMulti_Fade(void *p);
	HANDLE threadHandle;
	static CSceneManager* myAdd;
	bool threadFlag;
	bool threadEndFlag;
};

#endif
//-----------------------------------EOF---------------------------------------