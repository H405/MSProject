//*****************************************************************************
//	 [ game.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "wiiRemote/CWiiController.h"

#include "game.h"
#include "CManager.h"
#include "CRenderer.h"
#include "CFadeIn.h"
#include "CKeyboard.h"
#include "objects.h"

#include "CFireWork.h"

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CSceneGame::CSceneGame() : CSceneObject()
{
	counter = 0;
}

//=============================================================================
//	����������
//=============================================================================
void CSceneGame::Init(CRenderer* _renderer,
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

	obj2D = CObj2D::Create(device,
		D3DXVECTOR3(75.0f, 75.0f, 0.0f),
		3,
		D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	obj2D->setTexture("data/texture/bullete.png");
}
//=============================================================================
//	�I������
//=============================================================================
void CSceneGame::Uninit()
{

}
//=============================================================================
//	�X�V����
//=============================================================================
void CSceneGame::Update()
{
	InputUpdate();


	obj2D->setPos(D3DXVECTOR3(wiiController->getIR().x * SCREEN_WIDTH, wiiController->getIR().y * SCREEN_HEIGHT, 0.0f));
	if (wiiController->getTrigger(WC_A))
		obj2D->setColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	if (wiiController->getRelease(WC_A))
		obj2D->setColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	if (wiiController->getTrigger(WC_B))
	{
		CObj* obj = CObj::getInstans(CObj::OBJTYPE_FIREWORK);
		if (obj != nullptr)
			obj->Fire();
	}

	if (counter == 0)
	{
		if (wiiController->getAccelerationZ() >= 2.0f)
		{
			float f = wiiController->getChangeRotZ();

			if (f <= -3.0f)
			{
				CFireWork::Create(
					device,
					D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT, 0.0f),
					D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
					0);
			}
			else if (f >= 3.0f)
			{
				CFireWork::Create(
					device,
					D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT, 0.0f),
					D3DXVECTOR3(1.0f, -1.0f, 0.0f),
					0);
			}
			else
			{
				CFireWork::Create(
					device,
					D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT, 0.0f),
					D3DXVECTOR3(0.0f, -1.0f, 0.0f),
					0);
			}

			//wiiController->rumble(true);
			counter = 50;
		}
	}

	counter--;

	if (counter <= 0)
		counter = 0;


	renderer->Update();
}
//=============================================================================
//	���̓f�o�C�X�̍X�V����
//=============================================================================
void CSceneGame::InputUpdate()
{
	if (keyboard != nullptr)
		keyboard->Update();

	wiiController->update();

#ifdef _DEBUG
	{
		//	�{��
		{
			CDebug::SetDebug("�{�̂̉����xX [%f]\n", wiiController->getAccelerationX());
			CDebug::SetDebug("�{�̂̉����xY [%f]\n", wiiController->getAccelerationY());
			CDebug::SetDebug("�{�̂̉����xZ [%f]\n", wiiController->getAccelerationZ());

			CDebug::SetDebug("�{�̂̉����xRawX [%f]\n", wiiController->getAccelerationRawX());
			CDebug::SetDebug("�{�̂̉����xRawY [%f]\n", wiiController->getAccelerationRawY());
			CDebug::SetDebug("�{�̂̉����xRawZ [%f]\n", wiiController->getAccelerationRawZ());

			CDebug::SetDebug("�덷���m [%d]\n", wiiController->getUpdateAge());

			CDebug::SetDebug("�{�̂̉�]�pX [%f]\n", wiiController->getRotX());
			CDebug::SetDebug("�{�̂̉�]�pY [%f]\n", wiiController->getRotY());
			CDebug::SetDebug("�{�̂̉�]�pZ [%f]\n", wiiController->getRotZ());
			CDebug::SetDebug("�{�̂̉�]�pRawX [%f]\n", wiiController->getRotRawX());
			CDebug::SetDebug("�{�̂̉�]�pRawY [%f]\n", wiiController->getRotRawY());
			CDebug::SetDebug("�{�̂̉�]�pRawZ [%f]\n", wiiController->getRotRawZ());

			CDebug::SetDebug("�{�̂̉�]�p�̕ψ�X [%f]\n", wiiController->getChangeRotX());
			CDebug::SetDebug("�{�̂̉�]�p�̕ψ�Y [%f]\n", wiiController->getChangeRotY());
			CDebug::SetDebug("�{�̂̉�]�p�̕ψ�Z [%f]\n", wiiController->getChangeRotZ());
			CDebug::SetDebug("�{�̂̉�]�p�̕ψ�RawX [%f]\n", wiiController->getChangeRotRawX());
			CDebug::SetDebug("�{�̂̉�]�p�̕ψ�RawY [%f]\n", wiiController->getChangeRotRawY());
			CDebug::SetDebug("�{�̂̉�]�p�̕ψ�RawZ [%f]\n", wiiController->getChangeRotRawZ());

			CDebug::SetDebug("�{�̂̊p���xX [%f]\n", wiiController->getRotSpeedX());
			CDebug::SetDebug("�{�̂̊p���xY [%f]\n", wiiController->getRotSpeedY());
			CDebug::SetDebug("�{�̂̊p���xZ [%f]\n", wiiController->getRotSpeedZ());

			CDebug::SetDebug("�{�̂̊p���xRawX [%f]\n", wiiController->getRotSpeedRawX());
			CDebug::SetDebug("�{�̂̊p���xRawY [%f]\n", wiiController->getRotSpeedRawY());
			CDebug::SetDebug("�{�̂̊p���xRawZ [%f]\n", wiiController->getRotSpeedRawZ());
		}

		//	�k���`���N
		{
			//CDebug::SetDebug("�k���`���N�̉����xX [%f]\n", wiiController->getAccelerationNX());
			//CDebug::SetDebug("�k���`���N�̉����xY [%f]\n", wiiController->getAccelerationNY());
			//CDebug::SetDebug("�k���`���N�̉����xZ [%f]\n", wiiController->getAccelerationNZ());
			//
			//CDebug::SetDebug("�k���`���N�̉�]�pX [%f]\n", wiiController->getRotNX());
			//CDebug::SetDebug("�k���`���N�̉�]�pY [%f]\n", wiiController->getRotNY());
			//CDebug::SetDebug("�k���`���N�̉�]�pZ [%f]\n", wiiController->getRotNZ());
			//
			//CDebug::SetDebug("�k���`���N�̈ʒuX [%f]\n", wiiController->getJoystick().x);
			//CDebug::SetDebug("�k���`���N�̈ʒuY [%f]\n", wiiController->getJoystick().y);
		}

		//	�ԊO��
		{
			CDebug::SetDebug("�ԊO��X [%f]\n", wiiController->getIR().x);
			CDebug::SetDebug("�ԊO��Y [%f]\n", wiiController->getIR().y);
		}

		CDebug::SetDebug("�o�b�e���[�c��[%d��]\n", wiiController->battery());

		CDebug::SetDebug("���[�V����Plus�̐ڑ����[%d]\n", wiiController->getMotionConnect());

		/*if (wiiController->getTrigger(WC_A))
		wiiController->rumble(true);

		if (wiiController->getTrigger(WC_B))
		wiiController->rumble(false);

		if (wiiController->getTrigger(WC_UP))
		wiiController->rumble((unsigned int)1000);*/

		////	A�{�^��
		//{
		//	if (wiiController->getPress(WC_A))
		//		CDebug::SetDebug("A [ON]\n");
		//	else
		//		CDebug::SetDebug("A [OFF]\n");
		//}
		//
		////	B�{�^��
		//			{
		//				if (wiiController->getPress(WC_B))
		//					CDebug::SetDebug("B [ON]\n");
		//				else
		//					CDebug::SetDebug("B [OFF]\n");
		//			}
		//
		////	C�{�^��
		//			{
		//				if (wiiController->getPress(WC_C))
		//					CDebug::SetDebug("C [ON]\n");
		//				else
		//					CDebug::SetDebug("C [OFF]\n");
		//			}
		//
		////	Z�{�^��
		//			{
		//				if (wiiController->getPress(WC_Z))
		//					CDebug::SetDebug("Z [ON]\n");
		//				else
		//					CDebug::SetDebug("Z [OFF]\n");
		//			}
		//
		////	���{�^��
		//			{
		//				if (wiiController->getPress(WC_UP))
		//					CDebug::SetDebug("UP [ON]\n");
		//				else
		//					CDebug::SetDebug("UP [OFF]\n");
		//			}
		//
		////	���{�^��
		//			{
		//				if (wiiController->getPress(WC_DOWN))
		//					CDebug::SetDebug("DOWN [ON]\n");
		//				else
		//					CDebug::SetDebug("DOWN [OFF]\n");
		//			}
		//
		////	���{�^��
		//			{
		//				if (wiiController->getPress(WC_LEFT))
		//					CDebug::SetDebug("LEFT [ON]\n");
		//				else
		//					CDebug::SetDebug("LEFT [OFF]\n");
		//			}
		//
		////	���{�^��
		//			{
		//				if (wiiController->getPress(WC_RIGHT))
		//					CDebug::SetDebug("RIGHT [ON]\n");
		//				else
		//					CDebug::SetDebug("RIGHT [OFF]\n");
		//			}
		//
		////	-�{�^��
		//			{
		//				if (wiiController->getPress(WC_MINUS))
		//					CDebug::SetDebug("MINUS [ON]\n");
		//				else
		//					CDebug::SetDebug("MINUS [OFF]\n");
		//
		//				if (wiiController->getTrigger(WC_MINUS))
		//					wiiController->rotSpeedCalibration();
		//			}
		//
		////	+�{�^��
		//			{
		//				if (wiiController->getPress(WC_PLUS))
		//					CDebug::SetDebug("PLUS [ON]\n");
		//				else
		//					CDebug::SetDebug("PLUS [OFF]\n");
		//
						if (wiiController->getTrigger(WC_PLUS))
							wiiController->rotReset();
		//			}
		//
		////	1�{�^��
		//			{
		//				if (wiiController->getPress(WC_ONE))
		//					CDebug::SetDebug("ONE [ON]\n");
		//				else
		//					CDebug::SetDebug("ONE [OFF]\n");
		//			}
		//
		////	2�{�^��
		//			{
		//				if (wiiController->getPress(WC_TWO))
		//					CDebug::SetDebug("TWO [ON]\n");
		//				else
		//					CDebug::SetDebug("TWO [OFF]\n");
		//			}
		//
		////	HOME�{�^��
		//			{
		//				if (wiiController->getPress(WC_HOME))
		//					CDebug::SetDebug("HOME [ON]\n");
		//				else
		//					CDebug::SetDebug("HOME [OFF]\n");
		//			}
	}
#endif

	//if (joypad != nullptr)
	//joypad->Updata();

	//	ENTER�Ŏ��̃V�[����
	if (keyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (CManager::GetSceneManager()->GetFadeMode() == CSceneManager::FADE_NONE)
		{
			sceneChangeFlag = true;
			changeSceneMode = CSceneManager::SCENE_RESULT;
		}
	}

	//	F2�L�[�ŃX�N���[���V���b�g�B�e
	if (keyboard->GetTrigger(DIK_F2) == true)
	{
		renderer->SetScreenShotFlag(true);
	}
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CSceneGame::Draw()
{
#ifdef _DEBUG
	CDebug::SetDebug("\n\ngame\n\n");
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