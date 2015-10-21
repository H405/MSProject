//*****************************************************************************
//	 [ stageSelect.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"
#include "CSceneObject.h"

//*****************************************************************************
//	クラス定義
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