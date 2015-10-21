//*****************************************************************************
//	デバッグ処理 [CDebug.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"
#include "CDebug.h"

//*****************************************************************************
//	静的変数定義
//*****************************************************************************
LPD3DXFONT CDebug::direct3DFont;	//	フォントへのポインタ
char CDebug::strDebug[1024];		//	デバッグ情報用バッファ
bool CDebug::disp;
clock_t CDebug::start;
clock_t CDebug::end;

//=============================================================================
//	コンストラクタ
//=============================================================================
CDebug::CDebug()
{
	direct3DFont = nullptr;
}
//=============================================================================
//	デストラクタ
//=============================================================================
CDebug::~CDebug()
{
	SAFE_RELEASE(direct3DFont);

	//	デバッグ情報バッファのクリア
	memset(strDebug, NULL, sizeof(strDebug));
}
//=============================================================================
//	初期化
//=============================================================================
bool CDebug::Init(LPDIRECT3DDEVICE9 _device)
{
	HRESULT successFlag;

	//	情報表示用フォントを設定
	successFlag = 	D3DXCreateFontA(_device,
						18,
						0,
						0,
						0,
						FALSE,
						SHIFTJIS_CHARSET,
						OUT_DEFAULT_PRECIS,
						DEFAULT_QUALITY,
						DEFAULT_PITCH,
						"Terminal",
						&direct3DFont);

	//	デバッグ情報バッファのクリア
	memset(strDebug, NULL, sizeof(strDebug));

	return (successFlag == S_OK) ? true : false;
}
//=============================================================================
//	更新
//=============================================================================
void CDebug::Draw()
{
#ifdef _DEBUG

	if (disp)
	{
		//	表示範囲設定
		RECT rect = {5,
					  5,
					  static_cast<long>SCREEN_WIDTH,
					  static_cast<long>SCREEN_HEIGHT};

		//	表示
		direct3DFont->DrawTextA(nullptr,
								strDebug,
								-1,
								&rect,
								DT_LEFT,
								D3DCOLOR_RGBA(255, 255, 255, 255));
	}

	//	デバッグ情報バッファのクリア
	memset(strDebug, NULL, sizeof(strDebug));
#endif
}
//=============================================================================
//	デバッグ登録処理関数
//
//	引数は可変引数（ 引数の型は問わない ）
//=============================================================================
void CDebug::SetDebug(const char *_fmt, ...)
{
#ifdef _DEBUG
	va_list _s;
	char setStr[256] = {NULL};

	va_start(_s, _fmt);

	_vsnprintf_s(&setStr[0], sizeof(setStr), _TRUNCATE, _fmt, _s);

	va_end(_s);

	strcat_s(strDebug, 1024, setStr);
#endif
}
//=============================================================================
//	デバッグ表示フラグゲッター処理関数
//=============================================================================
bool CDebug::getDisp()
{
	return disp;
}
//=============================================================================
//	デバッグ表示フラグセッター処理関数
//=============================================================================
void CDebug::setDisp(bool _disp)
{
	disp = _disp;
}
//=============================================================================
//	時間計測開始
//=============================================================================
void CDebug::StartDebugTimer()
{
	//	時間計測開始
	start = timeGetTime();
}
//=============================================================================
//	時間計測終了
//=============================================================================
void CDebug::EndDebugTimer(char* str)
{
	char timeStr[32];
	char setStr[128];

	//	時間計測終了
	end = timeGetTime();

	//	処理時間を文字列変換
	double time = ((double)(end - start) / CLOCKS_PER_SEC);
	sprintf(timeStr, "= %f\n", time);

	//	引数で受け取った文字列と処理時間の文字列を結合
	strcpy(setStr, str);
	strcat(setStr, timeStr);

	//	文字列をデバッグ用プロシージャにセット
	CDebug::SetDebug(setStr);
	//CDebug::SetDebug("%d\n", time);
}

//-----------------------------------EOF---------------------------------------