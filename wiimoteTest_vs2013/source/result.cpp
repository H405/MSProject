//*****************************************************************************
//	 [ result.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "result.h"
#include "CManager.h"
#include "CRenderer.h"
#include "CFadeIn.h"
#include "CKeyboard.h"
#include "objects.h"

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CSceneResult::CSceneResult() : CSceneObject()
{
}

//=============================================================================
//	����������
//=============================================================================
void CSceneResult::Init(CRenderer* _renderer,
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
void CSceneResult::Uninit()
{

}
//=============================================================================
//	�X�V����
//=============================================================================
void CSceneResult::Update()
{
	InputUpdate();
	renderer->Update();
}
//=============================================================================
//	���̓f�o�C�X�̍X�V����
//=============================================================================
void CSceneResult::InputUpdate()
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
			changeSceneMode = CSceneManager::SCENE_STAGE_SELECT;
		}
	}
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CSceneResult::Draw()
{
#ifdef _DEBUG
	CDebug::SetDebug("\n\nresult\n\n");
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