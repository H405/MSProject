//*****************************************************************************
//	sin,cos�v�Z�p [radianTable.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include <stdlib.h>
#include "radianTable.h"

//*****************************************************************************
//	�ÓI�ϐ���`
//*****************************************************************************
float CRadianTable::sinTable[TABELE_MAX];
float CRadianTable::cosTable[TABELE_MAX];

//=============================================================================
//	������
//	������sin,cos���ꂼ��̃e�[�u�����쐬
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