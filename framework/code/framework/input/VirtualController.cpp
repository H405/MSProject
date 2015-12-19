//==============================================================================
//
// File   : VirtualController.cpp
// Brief  : 仮想コントローラクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/21 wed : Kotaro Nagasaki : create
//
//==============================================================================

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "VirtualController.h"

//*****************************************************************************
//	静的定数定義
//*****************************************************************************
static const int repeatCountMax = 20;

//=============================================================================
//	コンストラクタ
//=============================================================================
VirtualController::VirtualController():
wiiController(nullptr),
keyboard(nullptr),
mouse(nullptr),
pad(nullptr)
{
	for(int count = 0; count < VC_MAX; count++)
	{
		press[count] = false;
		trigger[count] = false;
		release[count] = false;
		repeat[count] = false;
		repeatCount[count] = 0;
	}
}
//=============================================================================
//	デストラクタ
//=============================================================================
VirtualController::~VirtualController()
{
	wiiController = nullptr;
	keyboard = nullptr;
	mouse = nullptr;
	pad = nullptr;
}
//=============================================================================
//	初期化処理
//=============================================================================
bool VirtualController::initialize(CWiiController* _wiiController, InputKeyboard* _keyboard, InputMouse* _mouse, InputPad* _pad)
{
	wiiController = _wiiController;
	keyboard = _keyboard;
	mouse = _mouse;
	pad = _pad;

	if(wiiController == nullptr)
		return false;

	return true;
}
//=============================================================================
//	更新処理
//=============================================================================
void VirtualController::update()
{
	//	各デバイスの更新
	keyboard->Update();
	mouse->Update();

	if(wiiController->getIsConnectWiimote() == true)
		wiiController->update();

	//	初期化
	for(int count = 0; count < VC_MAX; count++)
	{
		pressOld[count] = press[count];
		press[count] = false;
		trigger[count] = false;
		release[count] = false;
		repeat[count] = false;
	}

	//	決定キー押下情報
	if(wiiController->getPress(WC_A) || keyboard->IsPress(DIK_RETURN))
		press[VC_DESIDE] = true;

	//	キャンセルキー押下情報
	if(wiiController->getPress(WC_B) || keyboard->IsPress(DIK_C))
		press[VC_CANCEL] = true;

	//	方向キーの押下情報
	if(wiiController->getPress(WC_UP) || keyboard->IsPress(DIK_UP))
		press[VC_UP] = true;

	if(wiiController->getPress(WC_DOWN) || keyboard->IsPress(DIK_DOWN))
		press[VC_DOWN] = true;

	if(wiiController->getPress(WC_RIGHT) || keyboard->IsPress(DIK_RIGHT))
		press[VC_RIGHT] = true;

	if(wiiController->getPress(WC_LEFT) || keyboard->IsPress(DIK_LEFT))
		press[VC_LEFT] = true;

	//	ポーズキー押下情報
	if(wiiController->getPress(WC_HOME) || keyboard->IsPress(DIK_P))
		press[VC_PAUSE] = true;

	//	ゲームスタート（キャリブレーション）押下情報
	if((wiiController->getPress(WC_A) && wiiController->getPress(WC_B)) ||
		keyboard->IsPress(DIK_C))
		press[VC_GAME_START] = true;

	//	花火破裂
	if(wiiController->getTrigger(WC_A) || keyboard->IsTrigger(DIK_B))
		press[VC_BURN] = true;

	//	トリガー情報・リリース情報・リピート情報セット
	for(int count = 0;count < VC_MAX;count++)
	{
		if(press[count] == true && pressOld[count] == false)
			trigger[count] = true;

		if(press[count] == false && pressOld[count] == true)
		{
			release[count] = true;
			repeat[count] = false;
			repeatCount[count] = 0;
		}

		if(press[count] == true)
		{
			repeatCount[count]++;

			if(repeatCount[count] >= repeatCountMax)
			{
				repeat[count] = true;
				repeatCount[count] = repeatCountMax;
			}
		}
	}
}

//-----------------------------------EOF---------------------------------------