//*****************************************************************************
//	 [ game.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "wiiRemote/CWiiController.h"

#include "game.h"
#include "CManager.h"
#include "CRenderer.h"
#include "CFadeIn.h"
#include "CKeyboard.h"
#include "objects.h"

#include "CFireWork.h"

//=============================================================================
//	コンストラクタ
//=============================================================================
CSceneGame::CSceneGame() : CSceneObject()
{
	counter = 0;
}

//=============================================================================
//	初期化処理
//=============================================================================
void CSceneGame::Init(CRenderer* _renderer,
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

	obj2D = CObj2D::Create(device,
		D3DXVECTOR3(75.0f, 75.0f, 0.0f),
		3,
		D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	obj2D->setTexture("data/texture/bullete.png");
}
//=============================================================================
//	終了処理
//=============================================================================
void CSceneGame::Uninit()
{

}
//=============================================================================
//	更新処理
//=============================================================================
void CSceneGame::Update()
{
	InputUpdate();


	obj2D->setPos(D3DXVECTOR3(wiiController->getIR().x * SCREEN_WIDTH, wiiController->getIR().y * SCREEN_HEIGHT, 0.0f));
	if (wiiController->getTrigger(WC_A))
		obj2D->setColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	if (wiiController->getRelease(WC_A))
		obj2D->setColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	if (wiiController->getTrigger(WC_B))
	{
		CObj* obj = CObj::getInstans(CObj::OBJTYPE_FIREWORK);
		if (obj != nullptr)
			obj->Fire();
	}

	if (counter == 0)
	{
		if (wiiController->getAccelerationZ() >= 2.0f)
		{
			float f = wiiController->getChangeRotZ();

			if (f <= -3.0f)
			{
				CFireWork::Create(
					device,
					D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT, 0.0f),
					D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
					0);
			}
			else if (f >= 3.0f)
			{
				CFireWork::Create(
					device,
					D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT, 0.0f),
					D3DXVECTOR3(1.0f, -1.0f, 0.0f),
					0);
			}
			else
			{
				CFireWork::Create(
					device,
					D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, -1.0f, 0.0f),
					0);
			}

			//wiiController->rumble(true);
			counter = 50;
		}
	}

	counter--;

	if (counter <= 0)
		counter = 0;


	renderer->Update();
}
//=============================================================================
//	入力デバイスの更新処理
//=============================================================================
void CSceneGame::InputUpdate()
{
	if (keyboard != nullptr)
		keyboard->Update();

	wiiController->update();

#ifdef _DEBUG
	{
		//	本体
		{
			CDebug::SetDebug("本体の加速度X [%f]\n", wiiController->getAccelerationX());
			CDebug::SetDebug("本体の加速度Y [%f]\n", wiiController->getAccelerationY());
			CDebug::SetDebug("本体の加速度Z [%f]\n", wiiController->getAccelerationZ());

			CDebug::SetDebug("本体の加速度RawX [%f]\n", wiiController->getAccelerationRawX());
			CDebug::SetDebug("本体の加速度RawY [%f]\n", wiiController->getAccelerationRawY());
			CDebug::SetDebug("本体の加速度RawZ [%f]\n", wiiController->getAccelerationRawZ());

			CDebug::SetDebug("誤差感知 [%d]\n", wiiController->getUpdateAge());

			CDebug::SetDebug("本体の回転角X [%f]\n", wiiController->getRotX());
			CDebug::SetDebug("本体の回転角Y [%f]\n", wiiController->getRotY());
			CDebug::SetDebug("本体の回転角Z [%f]\n", wiiController->getRotZ());
			CDebug::SetDebug("本体の回転角RawX [%f]\n", wiiController->getRotRawX());
			CDebug::SetDebug("本体の回転角RawY [%f]\n", wiiController->getRotRawY());
			CDebug::SetDebug("本体の回転角RawZ [%f]\n", wiiController->getRotRawZ());

			CDebug::SetDebug("本体の回転角の変異X [%f]\n", wiiController->getChangeRotX());
			CDebug::SetDebug("本体の回転角の変異Y [%f]\n", wiiController->getChangeRotY());
			CDebug::SetDebug("本体の回転角の変異Z [%f]\n", wiiController->getChangeRotZ());
			CDebug::SetDebug("本体の回転角の変異RawX [%f]\n", wiiController->getChangeRotRawX());
			CDebug::SetDebug("本体の回転角の変異RawY [%f]\n", wiiController->getChangeRotRawY());
			CDebug::SetDebug("本体の回転角の変異RawZ [%f]\n", wiiController->getChangeRotRawZ());

			CDebug::SetDebug("本体の角速度X [%f]\n", wiiController->getRotSpeedX());
			CDebug::SetDebug("本体の角速度Y [%f]\n", wiiController->getRotSpeedY());
			CDebug::SetDebug("本体の角速度Z [%f]\n", wiiController->getRotSpeedZ());

			CDebug::SetDebug("本体の角速度RawX [%f]\n", wiiController->getRotSpeedRawX());
			CDebug::SetDebug("本体の角速度RawY [%f]\n", wiiController->getRotSpeedRawY());
			CDebug::SetDebug("本体の角速度RawZ [%f]\n", wiiController->getRotSpeedRawZ());
		}

		//	ヌンチャク
		{
			//CDebug::SetDebug("ヌンチャクの加速度X [%f]\n", wiiController->getAccelerationNX());
			//CDebug::SetDebug("ヌンチャクの加速度Y [%f]\n", wiiController->getAccelerationNY());
			//CDebug::SetDebug("ヌンチャクの加速度Z [%f]\n", wiiController->getAccelerationNZ());
			//
			//CDebug::SetDebug("ヌンチャクの回転角X [%f]\n", wiiController->getRotNX());
			//CDebug::SetDebug("ヌンチャクの回転角Y [%f]\n", wiiController->getRotNY());
			//CDebug::SetDebug("ヌンチャクの回転角Z [%f]\n", wiiController->getRotNZ());
			//
			//CDebug::SetDebug("ヌンチャクの位置X [%f]\n", wiiController->getJoystick().x);
			//CDebug::SetDebug("ヌンチャクの位置Y [%f]\n", wiiController->getJoystick().y);
		}

		//	赤外線
		{
			CDebug::SetDebug("赤外線X [%f]\n", wiiController->getIR().x);
			CDebug::SetDebug("赤外線Y [%f]\n", wiiController->getIR().y);
		}

		CDebug::SetDebug("バッテリー残量[%d％]\n", wiiController->battery());

		CDebug::SetDebug("モーションPlusの接続状態[%d]\n", wiiController->getMotionConnect());

		/*if (wiiController->getTrigger(WC_A))
		wiiController->rumble(true);

		if (wiiController->getTrigger(WC_B))
		wiiController->rumble(false);

		if (wiiController->getTrigger(WC_UP))
		wiiController->rumble((unsigned int)1000);*/

		////	Aボタン
		//{
		//	if (wiiController->getPress(WC_A))
		//		CDebug::SetDebug("A [ON]\n");
		//	else
		//		CDebug::SetDebug("A [OFF]\n");
		//}
		//
		////	Bボタン
		//			{
		//				if (wiiController->getPress(WC_B))
		//					CDebug::SetDebug("B [ON]\n");
		//				else
		//					CDebug::SetDebug("B [OFF]\n");
		//			}
		//
		////	Cボタン
		//			{
		//				if (wiiController->getPress(WC_C))
		//					CDebug::SetDebug("C [ON]\n");
		//				else
		//					CDebug::SetDebug("C [OFF]\n");
		//			}
		//
		////	Zボタン
		//			{
		//				if (wiiController->getPress(WC_Z))
		//					CDebug::SetDebug("Z [ON]\n");
		//				else
		//					CDebug::SetDebug("Z [OFF]\n");
		//			}
		//
		////	↑ボタン
		//			{
		//				if (wiiController->getPress(WC_UP))
		//					CDebug::SetDebug("UP [ON]\n");
		//				else
		//					CDebug::SetDebug("UP [OFF]\n");
		//			}
		//
		////	↓ボタン
		//			{
		//				if (wiiController->getPress(WC_DOWN))
		//					CDebug::SetDebug("DOWN [ON]\n");
		//				else
		//					CDebug::SetDebug("DOWN [OFF]\n");
		//			}
		//
		////	←ボタン
		//			{
		//				if (wiiController->getPress(WC_LEFT))
		//					CDebug::SetDebug("LEFT [ON]\n");
		//				else
		//					CDebug::SetDebug("LEFT [OFF]\n");
		//			}
		//
		////	→ボタン
		//			{
		//				if (wiiController->getPress(WC_RIGHT))
		//					CDebug::SetDebug("RIGHT [ON]\n");
		//				else
		//					CDebug::SetDebug("RIGHT [OFF]\n");
		//			}
		//
		////	-ボタン
		//			{
		//				if (wiiController->getPress(WC_MINUS))
		//					CDebug::SetDebug("MINUS [ON]\n");
		//				else
		//					CDebug::SetDebug("MINUS [OFF]\n");
		//
		//				if (wiiController->getTrigger(WC_MINUS))
		//					wiiController->rotSpeedCalibration();
		//			}
		//
		////	+ボタン
		//			{
		//				if (wiiController->getPress(WC_PLUS))
		//					CDebug::SetDebug("PLUS [ON]\n");
		//				else
		//					CDebug::SetDebug("PLUS [OFF]\n");
		//
						if (wiiController->getTrigger(WC_PLUS))
							wiiController->rotReset();
		//			}
		//
		////	1ボタン
		//			{
		//				if (wiiController->getPress(WC_ONE))
		//					CDebug::SetDebug("ONE [ON]\n");
		//				else
		//					CDebug::SetDebug("ONE [OFF]\n");
		//			}
		//
		////	2ボタン
		//			{
		//				if (wiiController->getPress(WC_TWO))
		//					CDebug::SetDebug("TWO [ON]\n");
		//				else
		//					CDebug::SetDebug("TWO [OFF]\n");
		//			}
		//
		////	HOMEボタン
		//			{
		//				if (wiiController->getPress(WC_HOME))
		//					CDebug::SetDebug("HOME [ON]\n");
		//				else
		//					CDebug::SetDebug("HOME [OFF]\n");
		//			}
	}
#endif

	//if (joypad != nullptr)
	//joypad->Updata();

	//	ENTERで次のシーンへ
	if (keyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (CManager::GetSceneManager()->GetFadeMode() == CSceneManager::FADE_NONE)
		{
			sceneChangeFlag = true;
			changeSceneMode = CSceneManager::SCENE_RESULT;
		}
	}

	//	F2キーでスクリーンショット撮影
	if (keyboard->GetTrigger(DIK_F2) == true)
	{
		renderer->SetScreenShotFlag(true);
	}
}
//=============================================================================
//	描画処理
//=============================================================================
void CSceneGame::Draw()
{
#ifdef _DEBUG
	CDebug::SetDebug("\n\ngame\n\n");
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