//==============================================================================
//
// File   : VirtualController.h
// Brief  : ���z�R���g���[���N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/21 wed : Kotaro Nagasaki : create
//
//==============================================================================
#ifndef _VIRTUALCONTROLLER_H_
#define _VIRTUALCONTROLLER_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "CWiiController.h"
#include "InputKeyboard.h"
#include "InputMouse.h"
#include "InputPad.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************

//******************************************************************************
// �񋓑̒�`
//******************************************************************************
typedef enum
{
	VC_DESIDE = 0,
	VC_CANCEL,
	VC_UP,
	VC_DOWN,
	VC_RIGHT,
	VC_LEFT,
	VC_PAUSE,
	VC_GAME_START,
	VC_BURN,
	VC_MAX,
}VC_BUTTON;
//	���̃{�^���𑝂₵����A����Ɋ��蓖�Ă�{�^����update���ō��Ȃ��Ɩ��Ӗ�

//******************************************************************************
// �N���X��`
//******************************************************************************
class VirtualController
{
public:

	VirtualController();
	~VirtualController();

	bool initialize(CWiiController* _wiiController = nullptr, InputKeyboard* _keyboard = nullptr, InputMouse* _mouse = nullptr, InputPad* _pad = nullptr);
	void update();

	bool IsTrigger(VC_BUTTON _button){return trigger[_button];}
	bool IsRelease(VC_BUTTON _button){return release[_button];}
	bool IsPress(VC_BUTTON _button){return press[_button];}
	bool IsRepeat(VC_BUTTON _button){return repeat[_button];}

private:

	CWiiController* wiiController;
	InputKeyboard* keyboard;
	InputMouse* mouse;
	InputPad* pad;

	bool trigger[VC_MAX];
	bool release[VC_MAX];
	bool press[VC_MAX];
	bool pressOld[VC_MAX];
	bool repeat[VC_MAX];
	int repeatCount[VC_MAX];
};

#endif
//-----------------------------------EOF---------------------------------------