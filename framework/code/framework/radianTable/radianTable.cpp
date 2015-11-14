//*****************************************************************************
//	sin,cos計算用 [radianTable.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include <stdlib.h>
#include "radianTable.h"

//*****************************************************************************
//	静的変数定義
//*****************************************************************************
float CRadianTable::sinTable[TABELE_MAX];
float CRadianTable::cosTable[TABELE_MAX];

//=============================================================================
//	初期化
//	ここでsin,cosそれぞれのテーブルを作成
//=============================================================================
void CRadianTable::Init()
{
	CFileReader* sinReader = new CFileReader();
	CFileReader* cosReader = new CFileReader();

	cosReader->FileOpen("data/radianTable/cosTable.txt", "r");
	sinReader->FileOpen("data/radianTable/sinTable.txt", "r");

	char* sinBuff = new char[256];
	char* cosBuff = new char[256];

	for (int count = 0; count < TABELE_MAX; count++)
	{
		sinReader->GetLine(sinBuff);
		cosReader->GetLine(cosBuff);

		sinTable[count] = (float)atof(sinBuff);
		cosTable[count] = (float)atof(cosBuff);
	}

	delete sinBuff;
	delete cosBuff;
	delete sinReader;
	delete cosReader;
}

//-----------------------------------EOF---------------------------------------