//*****************************************************************************
//	 [ result.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "main.h"
#include "CSceneObject.h"

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class CSceneResult : public CSceneObject
{
public:

	CSceneResult();
	~CSceneResult(){};
	void Init(CRenderer* _renderer,
		CSound* _sound,
		CJoypad* _joypad = nullptr,
		CKeyboard* _keyboard = nullptr);
	void Uninit();
	void Update();
	void Draw();


	void InputUpdate();

private:

};
#endif
//-----------------------------------EOF---------------------------------------