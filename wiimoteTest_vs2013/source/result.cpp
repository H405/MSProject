//*****************************************************************************
//	 [ result.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "result.h"
#include "CManager.h"
#include "CRenderer.h"
#include "CFadeIn.h"
#include "CKeyboard.h"
#include "objects.h"

//=============================================================================
//	コンストラクタ
//=============================================================================
CSceneResult::CSceneResult() : CSceneObject()
{
}

//=============================================================================
//	初期化処理
//=============================================================================
void CSceneResult::Init(CRenderer* _renderer,
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
void CSceneResult::Uninit()
{

}
//=============================================================================
//	更新処理
//=============================================================================
void CSceneResult::Update()
{
	InputUpdate();
	renderer->Update();
}
//=============================================================================
//	入力デバイスの更新処理
//=============================================================================
void CSceneResult::InputUpdate()
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
			changeSceneMode = CSceneManager::SCENE_STAGE_SELECT;
		}
	}
}
//=============================================================================
//	描画処理
//=============================================================================
void CSceneResult::Draw()
{
#ifdef _DEBUG
	CDebug::SetDebug("\n\nresult\n\n");
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