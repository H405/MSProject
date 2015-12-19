//==============================================================================
//
// File   : VirtualController.cpp
// Brief  : ���z�R���g���[���N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/21 wed : Kotaro Nagasaki : create
//
//==============================================================================

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "VirtualController.h"

//*****************************************************************************
//	�ÓI�萔��`
//*****************************************************************************
static const int repeatCountMax = 20;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
VirtualController::VirtualController():
wiiController(nullptr),
keyboard(nullptr),
mouse(nullptr),
pad(nullptr)
{
	for(int count = 0; count < VC_MAX; count++)
	{
		press[count] = false;
		trigger[count] = false;
		release[count] = false;
		repeat[count] = false;
		repeatCount[count] = 0;
	}
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
VirtualController::~VirtualController()
{
	wiiController = nullptr;
	keyboard = nullptr;
	mouse = nullptr;
	pad = nullptr;
}
//=============================================================================
//	����������
//=============================================================================
bool VirtualController::initialize(CWiiController* _wiiController, InputKeyboard* _keyboard, InputMouse* _mouse, InputPad* _pad)
{
	wiiController = _wiiController;
	keyboard = _keyboard;
	mouse = _mouse;
	pad = _pad;

	if(wiiController == nullptr)
		return false;

	return true;
}
//=============================================================================
//	�X�V����
//=============================================================================
void VirtualController::update()
{
	//	�e�f�o�C�X�̍X�V
	keyboard->Update();
	mouse->Update();

	if(wiiController->getIsConnectWiimote() == true)
		wiiController->update();

	//	������
	for(int count = 0; count < VC_MAX; count++)
	{
		pressOld[count] = press[count];
		press[count] = false;
		trigger[count] = false;
		release[count] = false;
		repeat[count] = false;
	}

	//	����L�[�������
	if(wiiController->getPress(WC_A) || keyboard->IsPress(DIK_RETURN))
		press[VC_DESIDE] = true;

	//	�L�����Z���L�[�������
	if(wiiController->getPress(WC_B) || keyboard->IsPress(DIK_C))
		press[VC_CANCEL] = true;

	//	�����L�[�̉������
	if(wiiController->getPress(WC_UP) || keyboard->IsPress(DIK_UP))
		press[VC_UP] = true;

	if(wiiController->getPress(WC_DOWN) || keyboard->IsPress(DIK_DOWN))
		press[VC_DOWN] = true;

	if(wiiController->getPress(WC_RIGHT) || keyboard->IsPress(DIK_RIGHT))
		press[VC_RIGHT] = true;

	if(wiiController->getPress(WC_LEFT) || keyboard->IsPress(DIK_LEFT))
		press[VC_LEFT] = true;

	//	�|�[�Y�L�[�������
	if(wiiController->getPress(WC_HOME) || keyboard->IsPress(DIK_P))
		press[VC_PAUSE] = true;

	//	�Q�[���X�^�[�g�i�L�����u���[�V�����j�������
	if((wiiController->getPress(WC_A) && wiiController->getPress(WC_B)) ||
		keyboard->IsPress(DIK_C))
		press[VC_GAME_START] = true;

	//	�ԉΔj��
	if(wiiController->getTrigger(WC_A) || keyboard->IsTrigger(DIK_B))
		press[VC_BURN] = true;

	//	�g���K�[���E�����[�X���E���s�[�g���Z�b�g
	for(int count = 0;count < VC_MAX;count++)
	{
		if(press[count] == true && pressOld[count] == false)
			trigger[count] = true;

		if(press[count] == false && pressOld[count] == true)
		{
			release[count] = true;
			repeat[count] = false;
			repeatCount[count] = 0;
		}

		if(press[count] == true)
		{
			repeatCount[count]++;

			if(repeatCount[count] >= repeatCountMax)
			{
				repeat[count] = true;
				repeatCount[count] = repeatCountMax;
			}
		}
	}
}

//-----------------------------------EOF---------------------------------------