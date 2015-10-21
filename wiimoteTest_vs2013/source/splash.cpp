//*****************************************************************************
//	 [ splash.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "splash.h"
#include "CManager.h"
#include "CRenderer.h"
#include "CFadeIn.h"
#include "CKeyboard.h"
#include "objects.h"

//*****************************************************************************
//	�萔��`
//*****************************************************************************
#define CHANGE_TIMER_MAX ( 100 )	//	�V�[���J�ڑ҂�����

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CSceneSplash::CSceneSplash() : CSceneObject()
{
	timer = 0;
}

//=============================================================================
//	����������
//=============================================================================
void CSceneSplash::Init(CRenderer* _renderer,
	CSound* _sound,
	CJoypad* _joypad,
	CKeyboard* _keyboard)
{
	renderer = _renderer;
	device = renderer->GetDevice();
	sound = _sound;
	joypad = _joypad;
	keyboard = _keyboard;
}
//=============================================================================
//	�I������
//=============================================================================
void CSceneSplash::Uninit()
{

}
//=============================================================================
//	�X�V����
//=============================================================================
void CSceneSplash::Update()
{
	InputUpdate();
	renderer->Update();
}
//=============================================================================
//	���̓f�o�C�X�̍X�V����
//=============================================================================
void CSceneSplash::InputUpdate()
{
	if (keyboard != nullptr)
		keyboard->Update();

	//if (joypad != nullptr)
		//joypad->Updata();

	//	ENTER�Ŏ��̃V�[����
	if (keyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (CManager::GetSceneManager()->GetFadeMode() == CSceneManager::FADE_NONE)
		{
			sceneChangeFlag = true;
			changeSceneMode = CSceneManager::SCENE_TITLE;
		}
	}
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CSceneSplash::Draw()
{
#ifdef _DEBUG
	CDebug::SetDebug("\n\nsplash\n\n");
#endif

	//	�����_���[�̕`�揈����
	renderer->Draw();

	//	�X�V�ƕ`��̏I����A�w��̃V�[���֑J��
	if (sceneChangeFlag == true)
	{
		CManager::GetSceneManager()->SetFadeIn(changeSceneMode);
		sceneChangeFlag = false;
	}
}

//-----------------------------------EOF---------------------------------------