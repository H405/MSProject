//*****************************************************************************
//	 [ title.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************

#include "wiiRemote/CWiiController.h"

#include "title.h"
#include "CManager.h"
#include "CRenderer.h"
#include "CFadeIn.h"
#include "CKeyboard.h"
#include "objects.h"

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CSceneTitle::CSceneTitle() : CSceneObject()
{
}

//=============================================================================
//	����������
//=============================================================================
void CSceneTitle::Init(CRenderer* _renderer,
	CSound* _sound,
	CJoypad* _joypad,
	CKeyboard* _keyboard)
{
	renderer = _renderer;
	device = renderer->GetDevice();
	sound = _sound;
	joypad = _joypad;
	keyboard = _keyboard;

	wiiController = CManager::getWiiController();
}
//=============================================================================
//	�I������
//=============================================================================
void CSceneTitle::Uninit()
{

}
//=============================================================================
//	�X�V����
//=============================================================================
void CSceneTitle::Update()
{
	InputUpdate();
	renderer->Update();
}
//=============================================================================
//	���̓f�o�C�X�̍X�V����
//=============================================================================
void CSceneTitle::InputUpdate()
{
	if (keyboard != nullptr)
		keyboard->Update();

	wiiController->update();

	//if (joypad != nullptr)
	//joypad->Updata();

	//	ENTER�Ŏ��̃V�[����
	if (keyboard->GetTrigger(DIK_RETURN) == true ||
		wiiController->getTrigger(WC_A))
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
void CSceneTitle::Draw()
{
#ifdef _DEBUG
	CDebug::SetDebug("\n\ntitle\n\n");
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