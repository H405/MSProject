//*****************************************************************************
//	 [ CSceneManager.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class CRenderer;
class CSound;
class CKeyboard;
class CJoypad;
class CSceneObject;
class CSceneManager
{
public:

	//*****************************************************************************
	//	�񋓑̒�`
	//*****************************************************************************
	typedef enum
	{
		SCENE_SPLASH = 0,
		SCENE_TITLE,
		SCENE_STAGE_SELECT,
		SCENE_GAME,
		SCENE_RESULT,
		SCENE_MAX
	}SCENE_MODE;

	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT
	}FADE_MODE;

	//*****************************************************************************
	//	�֐���`
	//*****************************************************************************
	CSceneManager(){};
	~CSceneManager();
	void Init(SCENE_MODE _sceneMode,
		CRenderer* _renderer,
		CSound* _sound,
		CJoypad* _joypad = nullptr,
		CKeyboard* _keyboard = nullptr);
	void Uninit();
	void Update();
	void Draw();
	void SetScene();
	void SetFadeIn(SCENE_MODE _nextScene);
	CSceneObject* GetSceneObject(){ return scene; };
	FADE_MODE GetFadeMode(){ return fadeMode; };
	bool GetChangeFlag(){ return changeFlag; };
	void SetChangeFlag(bool _setFlag){ changeFlag = _setFlag; };

	void nowLoading();

	static void setMyAdd(CSceneManager* _add){ myAdd = _add; };
	void setThreadFlag(bool _flag){ threadFlag = _flag; };
	void setThreadEndFlag(bool _flag){ threadEndFlag = _flag; };

private:

	//*****************************************************************************
	//	�֐���`
	//*****************************************************************************
	void NormalUpdate();
	void FadeUpdate();
	void ChangeScene();

	//*****************************************************************************
	//	�ϐ���`
	//*****************************************************************************
	SCENE_MODE curScene;	//	���̃V�[��
	SCENE_MODE prevScene;	//	�O�̃V�[��
	SCENE_MODE nextScene;	//	���̃V�[��
	FADE_MODE fadeMode;	//	�t�F�[�h���
	LPDIRECT3DDEVICE9 device;	//	�f�o�C�X
	CSceneObject* scene;	//	���݂̃V�[���I�u�W�F�N�g�ۑ�
	CRenderer* renderer;	//	�����_���[
	CSound* sound;	//	�T�E���h
	CKeyboard* keyboard;	//	�L�[�{�[�h
	CJoypad* joypad;	///	�W���C�p�b�h
	void (CSceneManager::*fpUpdate)(void);	//	�X�V�֐��Z�b�g�p�֐��|�C���^
	bool changeFlag;	//	�V�[���؂�ւ��t���O

	static unsigned __stdcall fpMulti_Fade(void *p);
	HANDLE threadHandle;
	static CSceneManager* myAdd;
	bool threadFlag;
	bool threadEndFlag;
};

#endif
//-----------------------------------EOF---------------------------------------