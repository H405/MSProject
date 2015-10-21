//*****************************************************************************
//	 [ splash.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "splash.h"
#include "CManager.h"
#include "CRenderer.h"
#include "CFadeIn.h"
#include "CKeyboard.h"
#include "objects.h"

//*****************************************************************************
//	定数定義
//*****************************************************************************
#define CHANGE_TIMER_MAX ( 100 )	//	シーン遷移待ち時間

//=============================================================================
//	コンストラクタ
//=============================================================================
CSceneSplash::CSceneSplash() : CSceneObject()
{
	timer = 0;
}

//=============================================================================
//	初期化処理
//=============================================================================
void CSceneSplash::Init(CRenderer* _renderer,
	CSound* _sound,
	CJoypad* _joypad,
	CKeyboard* _keyboard)
{
	renderer = _renderer;
	device = renderer->GetDevice();
	sound = _sound;
	joypad = _joypad;
	keyboard = _keyboard;
}
//=============================================================================
//	終了処理
//=============================================================================
void CSceneSplash::Uninit()
{

}
//=============================================================================
//	更新処理
//=============================================================================
void CSceneSplash::Update()
{
	InputUpdate();
	renderer->Update();
}
//=============================================================================
//	入力デバイスの更新処理
//=============================================================================
void CSceneSplash::InputUpdate()
{
	if (keyboard != nullptr)
		keyboard->Update();

	//if (joypad != nullptr)
		//joypad->Updata();

	//	ENTERで次のシーンへ
	if (keyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (CManager::GetSceneManager()->GetFadeMode() == CSceneManager::FADE_NONE)
		{
			sceneChangeFlag = true;
			changeSceneMode = CSceneManager::SCENE_TITLE;
		}
	}
}
//=============================================================================
//	描画処理
//=============================================================================
void CSceneSplash::Draw()
{
#ifdef _DEBUG
	CDebug::SetDebug("\n\nsplash\n\n");
#endif

	//	レンダラーの描画処理へ
	renderer->Draw();

	//	更新と描画の終了後、指定のシーンへ遷移
	if (sceneChangeFlag == true)
	{
		CManager::GetSceneManager()->SetFadeIn(changeSceneMode);
		sceneChangeFlag = false;
	}
}

//-----------------------------------EOF---------------------------------------