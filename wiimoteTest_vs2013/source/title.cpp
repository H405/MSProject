//*****************************************************************************
//	 [ title.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************

#include "wiiRemote/CWiiController.h"

#include "title.h"
#include "CManager.h"
#include "CRenderer.h"
#include "CFadeIn.h"
#include "CKeyboard.h"
#include "objects.h"

//=============================================================================
//	コンストラクタ
//=============================================================================
CSceneTitle::CSceneTitle() : CSceneObject()
{
}

//=============================================================================
//	初期化処理
//=============================================================================
void CSceneTitle::Init(CRenderer* _renderer,
	CSound* _sound,
	CJoypad* _joypad,
	CKeyboard* _keyboard)
{
	renderer = _renderer;
	device = renderer->GetDevice();
	sound = _sound;
	joypad = _joypad;
	keyboard = _keyboard;

	wiiController = CManager::getWiiController();
}
//=============================================================================
//	終了処理
//=============================================================================
void CSceneTitle::Uninit()
{

}
//=============================================================================
//	更新処理
//=============================================================================
void CSceneTitle::Update()
{
	InputUpdate();
	renderer->Update();
}
//=============================================================================
//	入力デバイスの更新処理
//=============================================================================
void CSceneTitle::InputUpdate()
{
	if (keyboard != nullptr)
		keyboard->Update();

	wiiController->update();

	//if (joypad != nullptr)
	//joypad->Updata();

	//	ENTERで次のシーンへ
	if (keyboard->GetTrigger(DIK_RETURN) == true ||
		wiiController->getTrigger(WC_A))
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
void CSceneTitle::Draw()
{
#ifdef _DEBUG
	CDebug::SetDebug("\n\ntitle\n\n");
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