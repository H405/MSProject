//*****************************************************************************
//	 [ CSceneObject.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "CSceneObject.h"

//=============================================================================
//	コンストラクタ
//=============================================================================
CSceneObject::CSceneObject()
{
	sceneChangeFlag = false;
	changeSceneMode = CSceneManager::SCENE_SPLASH;
}
//-----------------------------------EOF---------------------------------------