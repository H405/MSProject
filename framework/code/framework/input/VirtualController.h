//==============================================================================
//
// File   : VirtualController.h
// Brief  : 仮想コントローラクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/21 wed : Kotaro Nagasaki : create
//
//==============================================================================
#ifndef _VIRTUALCONTROLLER_H_
#define _VIRTUALCONTROLLER_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "CWiiController.h"
#include "InputKeyboard.h"
#include "InputMouse.h"
#include "InputPad.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************

//******************************************************************************
// 列挙体定義
//******************************************************************************
typedef enum
{
	VC_DESIDE = 0,
	VC_CANCEL,
	VC_UP,
	VC_DOWN,
	VC_RIGHT,
	VC_LEFT,
	VC_PAUSE,
	VC_GAME_START,
	VC_BURN,
	VC_MAX,
}VC_BUTTON;
//	↑のボタンを増やしたら、それに割り当てるボタンをupdate内で作らないと無意味

//******************************************************************************
// クラス定義
//******************************************************************************
class VirtualController
{
public:

	VirtualController();
	~VirtualController();

	bool initialize(CWiiController* _wiiController = nullptr, InputKeyboard* _keyboard = nullptr, InputMouse* _mouse = nullptr, InputPad* _pad = nullptr);
	void update();

	bool IsTrigger(VC_BUTTON _button){return trigger[_button];}
	bool IsRelease(VC_BUTTON _button){return release[_button];}
	bool IsPress(VC_BUTTON _button){return press[_button];}
	bool IsRepeat(VC_BUTTON _button){return repeat[_button];}

private:

	CWiiController* wiiController;
	InputKeyboard* keyboard;
	InputMouse* mouse;
	InputPad* pad;

	bool trigger[VC_MAX];
	bool release[VC_MAX];
	bool press[VC_MAX];
	bool pressOld[VC_MAX];
	bool repeat[VC_MAX];
	int repeatCount[VC_MAX];
};

#endif
//-----------------------------------EOF---------------------------------------