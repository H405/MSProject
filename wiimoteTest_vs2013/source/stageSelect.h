//*****************************************************************************
//	 [ stageSelect.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "main.h"
#include "CSceneObject.h"

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class CSceneStageSelect : public CSceneObject
{
public:

	CSceneStageSelect();
	~CSceneStageSelect(){};
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