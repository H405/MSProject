//*****************************************************************************
// ファイル読み込みクラス [fileReader.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "fileReader.h"
#include <assert.h>
#include <string.h>

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
//	アサートメッセージ
#define ASSERT(message) printf(message); assert(false); getchar();

//=============================================================================
//	コンストラクタ
//=============================================================================
CFileReader::CFileReader()
{
	filePointer = nullptr;
	skipIndex = 0;
}

//=============================================================================
//	デストラクタ
//=============================================================================
CFileReader::~CFileReader()
{
	if (filePointer != nullptr)
	{
		fclose(filePointer);
	}
}

//=============================================================================
//	ファイルを開く
//=============================================================================
void CFileReader::FileOpen(char* _fileName, char* _openType)
{
	if (filePointer != nullptr)
	{
		ASSERT("fileCloseされてません");
		fclose(filePointer);
	}

	filePointer = fopen(_fileName, _openType);

	if (filePointer == nullptr)
	{
		ASSERT("fileOpen失敗");
	}
}

//=============================================================================
//	ファイルを閉じる
//=============================================================================
void CFileReader::FileClose()
{
	if (filePointer != nullptr)
	{
		fclose(filePointer);
	}
}

//=============================================================================
//	１行取得処理
//=============================================================================
void CFileReader::GetLine(char* _getLine)
{
	char line[LINE_MAX_LENGTH];

	fgets(line, sizeof(line), filePointer);

	int i = strlen(line);
	strcpy(_getLine, line);
}

//=============================================================================
//	文字列の読み飛ばし処理
//=============================================================================
int CFileReader::SkipToWords(char* _skipWord)
{
	int returnLength = 0;

	return returnLength;
}

//=============================================================================
//	文字列長さ取得処理
//=============================================================================
int CFileReader::myStrLength(char* _skipWord)
{
	int returnLength = 0;

	int skipWordLength = strlen(_skipWord);

	//_ismbblead();

	return returnLength;
}

//=============================================================================
//	文字列の長さ取得処理
//=============================================================================
int CFileReader::myStrLength(char* _readWords, char* _skipWord)
{
	if (_skipWord == nullptr)
		return strlen(_readWords);


	int returnLength = 0;

	int readWordCount = 0;
	int skipWordCount = 0;
	for (;;)
	{
		if (_readWords[readWordCount] == '\0')
		{
			returnLength = -1;
			break;
		}

		if (_readWords[readWordCount] == _skipWord[skipWordCount])
		{
			if (skipWordCount == 0)
				returnLength = readWordCount;

			readWordCount++;
			skipWordCount++;

			if (_skipWord[skipWordCount] == '\0')
				break;
			else
				continue;
		}
		else
		{
			readWordCount++;
			skipWordCount = 0;
			continue;
		}
	}

	return returnLength;
}

//-----------------------------------EOF---------------------------------------