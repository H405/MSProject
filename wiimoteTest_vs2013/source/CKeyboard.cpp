//*****************************************************************************
//	キーボード処理 [CKeyboard.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"
#include "CKeyboard.h"

//*****************************************************************************
//	定数定義
//*****************************************************************************
const int repeatOnTimer = 50;

//=============================================================================
//	コンストラクタ
//=============================================================================
CKeyboard::CKeyboard()
{
}
//=============================================================================
//	デストラクタ
//=============================================================================
CKeyboard::~CKeyboard()
{
}
//=============================================================================
//	初期化
//=============================================================================
bool CKeyboard::Init(HINSTANCE _instanceHandle, HWND _windowHandle)
{
	HRESULT hr;

#ifndef KEYBOARD_ON
	return false;
#endif

	//	インプットデバイスの生成
	if (CInput::Init(_instanceHandle, _windowHandle) == false)
	{
		return false;
	}

	//	デバイスオブジェクトを作成
	hr = input->CreateDevice(GUID_SysKeyboard ,
							  &inputDevice ,
							  NULL);

	if(hr == E_FAIL)
	{
		ASSERT("デバイスオブジェクトの生成失敗");
		return false;
	}

	//	データフォーマットを設定
	hr = inputDevice->SetDataFormat(&c_dfDIKeyboard);

	if(hr == E_FAIL)
	{
		ASSERT("データフォーマットの設定失敗");
		return false;
	}

	//	協調モードを設定（フォアグラウンド＆非排他モード）
	hr = inputDevice->SetCooperativeLevel(_windowHandle ,
										  (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	if(hr == E_FAIL)
	{
		ASSERT("協調モードの設定失敗");
		return false;
	}

	//	キーボードへのアクセス権を獲得(入力制御開始)
	inputDevice->Acquire();

	//	キーボード押下状態カウンタの初期化
	for(int count = 0 ; count < 256 ; count++)
	{
		repeatCount[count] = 0;
	}

	return true;
}
//=============================================================================
//	更新
//=============================================================================
void CKeyboard::Update()
{
	BYTE state[256];	//	キーボード押下状態格納用変数

	//	アクセス権があれば
	if(SUCCEEDED(inputDevice->GetDeviceState(sizeof(state) ,
											&state[0])))
	{
		for(int countKey = 0 ; countKey < 256 ; countKey++)
		{
			//	トリガーをOFFに
			trigger[countKey] = 0x00;

			//	リリースをOFFに
			release[countKey] = 0x00;

			//	リピートをOFFに
			repeat[countKey] = 0x00;

			//	------------リリース情報取得-------------------------------------------------
			//	キーボードがリリースされたら
			if((press[countKey] == 0x00) && (pressOld[countKey] != press[countKey]))
			{
				//	リリースをONに
				release[countKey] = 0x80;

				//	リピート用のカウントを初期化
				repeatCount[countKey] = 0;
			}
			//-----------------------------------------------------------------------------

			//	------------リピート情報取得-------------------------------------------------
			//	押されてつづけていたら
			if(state[countKey] == 0x80)
			{	
				//	カウントが一定値を超えたらtrueを返す(一定時間押されていたら)
				if (repeatCount[countKey] == repeatOnTimer || repeatCount[countKey] == 0)
				{
					//	リピートのフラグをONに
					repeat[countKey] = 0x80;			
				}

				//	カウンターがオーバーフローしないように管理しつつインクリメント
				if(repeatCount[countKey] < 50)
				{
					repeatCount[countKey]++;
				}
			}
			//-----------------------------------------------------------------------------

			//	------------トリガー情報取得-------------------------------------------------
			//	押された瞬間(現在押さていて、１フレーム前は押されていなかったとき)
			if((press[countKey] == 0x80) && (pressOld[countKey] != press[countKey]))
			{
				//	トリガーのフラグにONに
				trigger[countKey] = 0x80;
			}
			//-----------------------------------------------------------------------------

			//	１フレーム前のキー情報を格納
			pressOld[countKey] = press[countKey];

			//	現在のフレームのキー情報を格納
			press[countKey] = state[countKey];
		}
	}
	else
	{
		//	アクセス権取得
		inputDevice->Acquire();
	}
}
//=============================================================================
//	何のキーが押されたかをゲット
//=============================================================================
int CKeyboard::GetTrigger()
{
	int returnKey = -1;

	for(int countKey = 0 ; countKey < 256 ; countKey++)
	{
		if(trigger[countKey] == 0x80)
		{
			returnKey = countKey;

			break;
		}
	}

	return returnKey;
}

//-----------------------------------EOF---------------------------------------