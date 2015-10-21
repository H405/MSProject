//*****************************************************************************
//	メイン処理 [main.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
//	インクルードファイル
//*****************************************************************************
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#define _AFX_SECURE_NO_WARNINGS
#define _ATL_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>
#include <Windowsx.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//	警告対策用
#include "dinput.h"
#include <stdio.h>
#include <mmsystem.h>
#include <process.h>
#include <assert.h>
#include <dshow.h>
#include "radianTable.h"
#include "texUV.h"
#include "CObj.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif

#ifdef _DEBUG

#include "CDebug.h"

#endif

//*****************************************************************************
//	ライブラリのリンク
//*****************************************************************************
#pragma comment (lib , "d3d9.lib")
#pragma comment (lib , "d3dx9.lib")
#pragma comment (lib , "dxguid.lib")
#pragma comment (lib , "dinput8.lib")
#pragma comment (lib , "winmm.lib")
#pragma comment (lib, "Strmiids.lib")

//*****************************************************************************
//	マクロ定義
//*****************************************************************************
//	２Ｄポリゴン頂点フォーマット(頂点座標[2D] / 反射光 / テクスチャ座標)
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//	３Ｄポリゴン頂点フォーマット(頂点座標[3D] / 法線 / 反射光 / テクスチャ座標)
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//	int値180→float値1.57...への変換
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)

//	float値1.57→int値180...への変換
#define RAD_TO_DEG(_rad)	((_rad * 180.0f) / D3DX_PI)

#define SQUARE(_num)	(_num * _num)
#define CUBE(_num)	(_num * _num * _num)


//	ランダムで　(-_num <= 計算値 <= num)　を返すマクロ
//	渡す値は　1以上を指定すること
#define RANDAM(_num)	((rand() % _num) - (rand() % _num))

#define VEC3_0	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
#define VEC4_0	(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))
#define COL4_0	(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))
#define COL4_1	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))


#define SCREEN_WIDTH	(1024.0f)
#define SCREEN_HEIGHT	(768.0f)

#define SAFE_RELEASE(p)	{if (p != nullptr) {(p)->Release();(p) = nullptr;}}
#define SAFE_RELEASE_ARRAY(p)\\
				{\\
		if (p != nullptr)\\
						{\\
			for (int arrayCount = 0; arrayCount < sizeof(p) / 4; arrayCount++)\\
									{\\
				(p[arrayCount])->Release();\\
				(p[arrayCount]) = nullptr;\\
									}\\
						}\\
				}

#define SAFE_DELETE(p)	{if (p != nullptr) {delete (p);(p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)\\
				{\\
		if (p != nullptr)\\
						{\\
			for (int arrayCount = 0; arrayCount < sizeof(p) / 4; arrayCount++)\\
									{\\
				delete (p[arrayCount]);\\
				(p[arrayCount]) = nullptr;\\
									}\\
						}\\
				}

//	メッセージボックスの簡易作成
//	表示するテキストをセットする
#define MESSAGE(message) MessageBox(NULL, message, "Message", MB_ICONWARNING);

//	アサートメッセージ
#define ASSERT(message) MessageBoxA(NULL, message, "Message", MB_ICONWARNING); assert(false);

//*****************************************************************************
//	構造体定義
//*****************************************************************************
//	上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 vtx;	//	頂点座標
	float rhw;			//	テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;	//	反射光
	D3DXVECTOR2 tex;	//	テクスチャ座標
}VERTEX_2D;
//-----------------------------------------------------------------------------

//	上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 vtx;	//	頂点座標
	D3DXVECTOR3 nor;	//	法線ベクトル
	D3DCOLOR diffuse;	//	反射光
	D3DXVECTOR2 tex;	//	テクスチャ座標
}VERTEX_3D;
//-----------------------------------------------------------------------------

#endif

//-----------------------------------EOF---------------------------------------