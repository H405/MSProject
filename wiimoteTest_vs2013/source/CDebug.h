//*****************************************************************************
//	�f�o�b�O���� [CDebug.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _CDEBUG_H_
#define _CDEBUG_H_

//*****************************************************************************
//	�C���N���[�h
//*****************************************************************************
#include <stdarg.h>
#include <assert.h>
#include <time.h>

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class CDebug
{
public:

	CDebug();
	~CDebug();

	bool Init(LPDIRECT3DDEVICE9 _device);
	static void Draw();

	//	�f�o�b�O�������Z�b�g(printf�̊��o�Ŏg��)
	//	��������̍Ō�ɉ��s�������g��Ȃ��Ɖ��s����Ȃ�
	static void SetDebug(const char *_fmt, ...);

	//	�\��
	static bool getDisp(void);
	static void setDisp(bool _disp);

	//
	static void StartDebugTimer();
	static void EndDebugTimer(char* str);

private:

	static LPD3DXFONT direct3DFont;	//	�t�H���g�ւ̃|�C���^
	static char strDebug[1024];	//	�f�o�b�O���p�o�b�t�@
	static bool disp;
	static clock_t start;	//	�J�n����
	static clock_t end;	//	�I������
};

#endif

//-----------------------------------EOF---------------------------------------