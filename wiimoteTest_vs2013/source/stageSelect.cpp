//*****************************************************************************
//	 [ stageSelect.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "stageSelect.h"
#include "CManager.h"
#include "CRenderer.h"
#include "CFadeIn.h"
#include "CKeyboard.h"
#include "objects.h"

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CSceneStageSelect::CSceneStageSelect() : CSceneObject()
{
}

//=============================================================================
//	����������
//=============================================================================
void CSceneStageSelect::Init(CRenderer* _renderer,
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
void CSceneStageSelect::Uninit()
{

}
//=============================================================================
//	�X�V����
//=============================================================================
void CSceneStageSelect::Update()
{
	InputUpdate();
	renderer->Update();
}
//=============================================================================
//	���̓f�o�C�X�̍X�V����
//=============================================================================
void CSceneStageSelect::InputUpdate()
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
			changeSceneMode = CSceneManager::SCENE_GAME;
			CManager::GetSceneManager()->setThreadFlag(true);
		}
	}
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CSceneStageSelect::Draw()
{
#ifdef _DEBUG
	CDebug::SetDebug("\n\nstageSelect\n\n");
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