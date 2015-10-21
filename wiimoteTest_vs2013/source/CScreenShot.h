//*****************************************************************************
//	�X�N���[���V���b�g���� [ CScreenShot.h ]
//	Author : KOTARO NAGASAKI
//	create : 12/16
//	Update : 12/16
//*****************************************************************************
#ifndef _CSCREENSHOT_H_
#define _CSCREENSHOT_H_


//	��`���Ă���ꍇ�A�X�N���[���V���b�g���B�e�\
#define SCREENSHOT_ON

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class CScreenShot
{
public:

	//*****************************************************************************
	//	�֐���`
	//*****************************************************************************
	CScreenShot(LPDIRECT3DDEVICE9 _device, BOOL _window, HWND _windowHandle);
	~CScreenShot();
	void Init(LPDIRECT3DDEVICE9 _device, BOOL _window, HWND _windowHandle);
	void Create();

private:

	//*****************************************************************************
	//	�ϐ���`
	//*****************************************************************************
	static int index;	//	�X�N���[���V���b�g�摜�̔ԍ�
	LPDIRECT3DDEVICE9 device;	//	�f�o�C�X
	BOOL windowMode;	//	�E�B���h�E���[�h
	HWND windowHandle;	//	�E�B���h�E�n���h��
};
#endif

//	EOF