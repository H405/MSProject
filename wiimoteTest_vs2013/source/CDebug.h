//*****************************************************************************
//	デバッグ処理 [CDebug.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _CDEBUG_H_
#define _CDEBUG_H_

//*****************************************************************************
//	インクルード
//*****************************************************************************
#include <stdarg.h>
#include <assert.h>
#include <time.h>

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CDebug
{
public:

	CDebug();
	~CDebug();

	bool Init(LPDIRECT3DDEVICE9 _device);
	static void Draw();

	//	デバッグ文字をセット(printfの感覚で使う)
	//	※文字列の最後に改行文字を使わないと改行されない
	static void SetDebug(const char *_fmt, ...);

	//	表示
	static bool getDisp(void);
	static void setDisp(bool _disp);

	//
	static void StartDebugTimer();
	static void EndDebugTimer(char* str);

private:

	static LPD3DXFONT direct3DFont;	//	フォントへのポインタ
	static char strDebug[1024];	//	デバッグ情報用バッファ
	static bool disp;
	static clock_t start;	//	開始時間
	static clock_t end;	//	終了時間
};

#endif

//-----------------------------------EOF---------------------------------------