//*****************************************************************************
// �t�@�C���ǂݍ��݃N���X [fileReader.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "fileReader.h"
#include <assert.h>
#include <string.h>

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
//	�A�T�[�g���b�Z�[�W
#define ASSERT(message) printf(message); assert(false); getchar();

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CFileReader::CFileReader()
{
	filePointer = nullptr;
	skipIndex = 0;
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CFileReader::~CFileReader()
{
	if (filePointer != nullptr)
	{
		fclose(filePointer);
	}
}

//=============================================================================
//	�t�@�C�����J��
//=============================================================================
void CFileReader::FileOpen(char* _fileName, char* _openType)
{
	if (filePointer != nullptr)
	{
		ASSERT("fileClose����Ă܂���");
		fclose(filePointer);
	}

	filePointer = fopen(_fileName, _openType);

	if (filePointer == nullptr)
	{
		ASSERT("fileOpen���s");
	}
}

//=============================================================================
//	�t�@�C�������
//=============================================================================
void CFileReader::FileClose()
{
	if (filePointer != nullptr)
	{
		fclose(filePointer);
	}
}

//=============================================================================
//	�P�s�擾����
//=============================================================================
void CFileReader::GetLine(char* _getLine)
{
	char line[LINE_MAX_LENGTH];

	fgets(line, sizeof(line), filePointer);

	int i = strlen(line);
	strcpy(_getLine, line);
}

//=============================================================================
//	������̓ǂݔ�΂�����
//=============================================================================
int CFileReader::SkipToWords(char* _skipWord)
{
	int returnLength = 0;

	return returnLength;
}

//=============================================================================
//	�����񒷂��擾����
//=============================================================================
int CFileReader::myStrLength(char* _skipWord)
{
	int returnLength = 0;

	int skipWordLength = strlen(_skipWord);

	//_ismbblead();

	return returnLength;
}

//=============================================================================
//	������̒����擾����
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