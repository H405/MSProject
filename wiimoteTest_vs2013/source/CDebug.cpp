//*****************************************************************************
//	�f�o�b�O���� [CDebug.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "main.h"
#include "CDebug.h"

//*****************************************************************************
//	�ÓI�ϐ���`
//*****************************************************************************
LPD3DXFONT CDebug::direct3DFont;	//	�t�H���g�ւ̃|�C���^
char CDebug::strDebug[1024];		//	�f�o�b�O���p�o�b�t�@
bool CDebug::disp;
clock_t CDebug::start;
clock_t CDebug::end;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CDebug::CDebug()
{
	direct3DFont = nullptr;
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CDebug::~CDebug()
{
	SAFE_RELEASE(direct3DFont);

	//	�f�o�b�O���o�b�t�@�̃N���A
	memset(strDebug, NULL, sizeof(strDebug));
}
//=============================================================================
//	������
//=============================================================================
bool CDebug::Init(LPDIRECT3DDEVICE9 _device)
{
	HRESULT successFlag;

	//	���\���p�t�H���g��ݒ�
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

	//	�f�o�b�O���o�b�t�@�̃N���A
	memset(strDebug, NULL, sizeof(strDebug));

	return (successFlag == S_OK) ? true : false;
}
//=============================================================================
//	�X�V
//=============================================================================
void CDebug::Draw()
{
#ifdef _DEBUG

	if (disp)
	{
		//	�\���͈͐ݒ�
		RECT rect = {5,
					  5,
					  static_cast<long>SCREEN_WIDTH,
					  static_cast<long>SCREEN_HEIGHT};

		//	�\��
		direct3DFont->DrawTextA(nullptr,
								strDebug,
								-1,
								&rect,
								DT_LEFT,
								D3DCOLOR_RGBA(255, 255, 255, 255));
	}

	//	�f�o�b�O���o�b�t�@�̃N���A
	memset(strDebug, NULL, sizeof(strDebug));
#endif
}
//=============================================================================
//	�f�o�b�O�o�^�����֐�
//
//	�����͉ψ����i �����̌^�͖��Ȃ� �j
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
//	�f�o�b�O�\���t���O�Q�b�^�[�����֐�
//=============================================================================
bool CDebug::getDisp()
{
	return disp;
}
//=============================================================================
//	�f�o�b�O�\���t���O�Z�b�^�[�����֐�
//=============================================================================
void CDebug::setDisp(bool _disp)
{
	disp = _disp;
}
//=============================================================================
//	���Ԍv���J�n
//=============================================================================
void CDebug::StartDebugTimer()
{
	//	���Ԍv���J�n
	start = timeGetTime();
}
//=============================================================================
//	���Ԍv���I��
//=============================================================================
void CDebug::EndDebugTimer(char* str)
{
	char timeStr[32];
	char setStr[128];

	//	���Ԍv���I��
	end = timeGetTime();

	//	�������Ԃ𕶎���ϊ�
	double time = ((double)(end - start) / CLOCKS_PER_SEC);
	sprintf(timeStr, "= %f\n", time);

	//	�����Ŏ󂯎����������Ə������Ԃ̕����������
	strcpy(setStr, str);
	strcat(setStr, timeStr);

	//	��������f�o�b�O�p�v���V�[�W���ɃZ�b�g
	CDebug::SetDebug(setStr);
	//CDebug::SetDebug("%d\n", time);
}

//-----------------------------------EOF---------------------------------------