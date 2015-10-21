//*****************************************************************************
//	 [ CSceneObject.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "main.h"
#include "CSceneManager.h"

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class CRenderer;
class CSound;
class CKeyboard;
class CJoypad;
//	���̃N���X�͒P�̂Ŏg��Ȃ�
//	CScene���l�ɁA���Ԑ�����肭�g���ėl�X�ȃV�[���������s��(CSceneManager�ɍs�킹��)
class CSceneObject
{
public:

	//*****************************************************************************
	//	�֐���`
	//*****************************************************************************
	CSceneObject();
	virtual ~CSceneObject(){};
	virtual void Init(CRenderer* _renderer,
		CSound* _sound,
		CJoypad* _joypad = nullptr,
		CKeyboard* _keyboard = nullptr) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void SetSceneChange(CSceneManager::SCENE_MODE _changeSceneMode){ sceneChangeFlag = true; changeSceneMode = _changeSceneMode; };

protected:

	//*****************************************************************************
	//	�ϐ���`
	//*****************************************************************************
	LPDIRECT3DDEVICE9 device;
	CRenderer* renderer;
	CSound* sound;
	CKeyboard* keyboard;
	CJoypad* joypad;
	bool sceneChangeFlag;
	CSceneManager::SCENE_MODE changeSceneMode;
};

#endif
//-----------------------------------EOF---------------------------------------