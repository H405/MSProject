//*****************************************************************************
//	�����_���[ [CRenderer.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _CRENDERER_H_
#define _CRENDERER_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "main.h"
#include "CScreenShot.h"

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class CScene;
class CCamera;
class CObj2D;
class CObj2DKeyFrame;
class CObj2DLoop;
class CScreenShot;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	void Init(HWND _windowHandle, BOOL _windowMode);
	void Update();
	void Draw(CCamera* _camara);
	void Draw();

	LPDIRECT3DDEVICE9 GetDevice();

#ifdef SCREENSHOT_ON
	void SetScreenShotFlag(bool _flag){ screenShotFlag = _flag; };
#endif

private:

	void DrawFPS();

	LPDIRECT3D9 direct3D;	//	Direct3D9�p�f�o�C�X
	LPDIRECT3DDEVICE9 device;	//	_device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef SCREENSHOT_ON
	static CScreenShot *screenShot;	//	�X�N���[���V���b�g�I�u�W�F�N�g
	bool screenShotFlag;	//	�X�N���[���V���b�g�B�eON/OFF�t���O
#endif
};

#endif

//-----------------------------------EOF---------------------------------------