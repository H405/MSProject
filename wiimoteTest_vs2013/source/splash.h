//*****************************************************************************
//	 [ splash.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _SPLASH_H_
#define _SPLASH_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "main.h"
#include "CSceneObject.h"

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class CSceneSplash : public CSceneObject
{
public:

	CSceneSplash();
	~CSceneSplash(){};
	void Init(CRenderer* _renderer,
		CSound* _sound,
		CJoypad* _joypad = nullptr,
		CKeyboard* _keyboard = nullptr);
	void Uninit();
	void Update();
	void Draw();


	void InputUpdate();

private:

	int timer;	//	�����J�ڗp�^�C�}�[
};
#endif
//-----------------------------------EOF---------------------------------------