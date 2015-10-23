//*****************************************************************************
//	 [ CWiiController.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "CWiiController.h"
#include <iostream>

//*****************************************************************************
//	�萔��`
//*****************************************************************************

//SlowMode�i�ᑬ�����[�h�j�� 1.45[deg / s]
//FastMode�i���������[�h�j�� 6.59[deg / s]

//	�{�^���̎��ʎq
const int BUTTON_STATE_BITS[WC_ALL] = {
	wiimote_state::buttons::LEFT,	//	0x0001
	wiimote_state::buttons::RIGHT,	//	0x0002
	wiimote_state::buttons::DOWN,	//	0x0004
	wiimote_state::buttons::UP,		//	0x0008
	wiimote_state::buttons::PLUS,	//	0x0010
	/*�k���`���NC�{�^��*/				0x0020,
	/*�k���`���NZ�{�^��*/				0x0040,
	wiimote_state::buttons::TWO,	//	0x0100
	wiimote_state::buttons::ONE,	//	0x0200
	wiimote_state::buttons::_B,		//	0x0400
	wiimote_state::buttons::_A,		//	0x0800
	wiimote_state::buttons::MINUS,	//	0x1000
	wiimote_state::buttons::HOME	//	0x8000
};

//	�o�b�e���[�c�ʂ̍ő�l�i���j
const float batteryMax = 100.0f;

//	LED�̓_�Ŏ��p�J�E���^
const int LEDCounterMax = 50;

//	�k���`���N�̃W���C�X�e�B�b�N�p�������l�i�ŏ��l�j
const float joyStickDeadZone = 0.03f;

//	�k���`���N�̃W���C�X�e�B�b�N�p�������l�i�ő�l�j
const float joyStickMax = 1.0f;

// �L�����u���[�V�����̍ۂ̃T���v�����O��
const int rotSpeedCalibrationCountMax = 100;

//	�p���x�̃J�b�g�I�t���g���i����ȉ��̕ω��͖���������Ă��Ɓj
//	�v����
const float cutOffHZ_X = 7.5f;
const float cutOffHZ_Y = 7.6f;
const float cutOffHZ_Z = 4.0f;

const float cutOffHZ_XRaw = -8200.0f;
const float cutOffHZ_YRaw = -8200.0f;
const float cutOffHZ_ZRaw = -8150.0f;

const float cuttOffHZ = 1.5f;
const float cuttOffHZRaw = 1.5f;

//	�P�t���[���̊ԂŌv���ł���p���x�̍ő�l��ݒ�
const float rotSpeedMax = 1200.0f;
const float rotSpeedRawMax = 1200.0f;

//	�X�N���[���T�C�Y�������Őݒ�
const float screenWidth = 1280.0f;
const float screenHeight = 720.0f;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CWiiController::CWiiController() :
wiiRemote(nullptr),
wiiBoard(nullptr),

accel(0.0f, 0.0f, 0.0f),
accelPrev(0.0f, 0.0f, 0.0f),

accelRaw(0.0f, 0.0f, 0.0f),
accelRawPrev(0.0f, 0.0f, 0.0f),

accelN(0.0f, 0.0f, 0.0f),
accelNPrev(0.0f, 0.0f, 0.0f),

rot(0.0f, 0.0f, 0.0f),
rotPrev(0.0f, 0.0f, 0.0f),

rotN(0.0f, 0.0f, 0.0f),
rotNPrev(0.0f, 0.0f, 0.0f),

rotRaw(0.0f, 0.0f, 0.0f),
rotRawPrev(0.0f, 0.0f, 0.0f),

rotSpeed(0.0f, 0.0f, 0.0f),
rotSpeedPrev(0.0f, 0.0f, 0.0f),

rotSpeedRaw(0.0f, 0.0f, 0.0f),
rotSpeedRawPrev(0.0f, 0.0f, 0.0f),

joystick(0.0f, 0.0f),
joystickPrev(0.0f, 0.0f),

IR(0.0f, 0.0f),
IRPrev(0.0f, 0.0f),

IRScreen(0.0f, 0.0f),
IRScreenPrev(0.0f, 0.0f),

LEDType(LED_0),
LEDTypePrev(LED_0),

LEDCounter(0),

motionConnect(false),
motionConnectPrev(false),

rotSpeedCalibrationFlag(false),

rotResetFlag(false),

rotSpeedCalibrationCount(0),

updateAge(0),
updateAgePrev(0),

buttonState(0),
buttonStatePrev(0),

isConnect(false)
{
	for (int count = 0; count < 2; count++)
	{
		//	�{�̂𐶐�
		wiimote* buff = new wiimote();

		//	���s��
		int connectTryCount = 0;
		std::cerr << "waiting connection... \t";

		//	�R���g���[���̖{�̂��A�ڑ��ł���܂Ń��[�v�i�񐔐�������j
		while (!buff->Connect())
		{
			Sleep(10);

			//	���񐔁A�ڑ��Ɏ��s������
			if (connectTryCount >= CONNECT_TRY_NUM)
			{
				//	�G���[�l�i�[
				connectTryCount = -1;

				//	wii�����R�����ڑ�����ĂȂ�
				if (wiiRemote == nullptr)
				{
					MessageBox(NULL, "wii�����R���̐ڑ��͂���܂���ł���", "Message", MB_ICONWARNING);
					delete buff;

					//	�X�V�֐��Z�b�g
					fpUpdate = &CWiiController::NormalUpdate;

					return;
				}
				//	wii�����R���͐ڑ�����Ă�
				else if (wiiBoard == nullptr)
				{
					MessageBox(NULL, "wii�{�[�h�̐ڑ��͂���܂���ł���", "Message", MB_ICONWARNING);
					delete buff;

					//	���s�[�g�J�E���^�̏�����
					for (int count = 0; count < WC_ALL; count++)
						repeatCount[count] = 0;

					//	�X�V�֐��Z�b�g
					fpUpdate = &CWiiController::NormalUpdate;

					return;
				}
			}
			connectTryCount++;
		}

		if (!buff->IsBalanceBoard())
		{
			//	�ڑ���ԃZ�b�g
			isConnect = true;

			//	�ꎞ�o�b�t�@��{�̂Ƃ��ēo�^
			wiiRemote = buff;

			// �g�p����Z���T��ݒ�i�{�^���A�����x�AIR�A�G�N�X�e���V�����i�O���ڑ�-�k���`���N�Ƃ��j�j
			wiiRemote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);

			//	�X�s�[�J�[��L���ɂ���
			wiiRemote->MuteSpeaker(false);
			wiiRemote->EnableSpeaker(true);

			//	LED���Ƃ肠�����S���_��������
			wiiRemote->SetLEDs(0x000F);
		}
		else
		{
			//	�ꎞ�o�b�t�@���o�����X�{�[�h�Ƃ��ēo�^
			wiiBoard = buff;

			// �g�p����Z���T��ݒ�iwii�{�[�h�j
			wiiBoard->SetReportType(wiimote::IN_BUTTONS_BALANCE_BOARD);
		}
	}

	//	���s�[�g�J�E���^�̏�����
	for (int count = 0; count < WC_ALL; count++)
		repeatCount[count] = 0;

	//	�X�V�֐��Z�b�g
	fpUpdate = &CWiiController::NormalUpdate;
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CWiiController::~CWiiController()
{
	if(wiiRemote != nullptr)
	{
		//	LED����
		wiiRemote->SetLEDs(0x0000);

		//	��������
		wiiRemote->MuteSpeaker(false);

		//	�ؒf
		wiiRemote->Disconnect();

		delete wiiRemote;
	}

	if(wiiBoard != nullptr)
	{
		delete wiiBoard;
	}
}

//=============================================================================
//	�[�d�ʂɉ�����LED��_��������
//=============================================================================
void CWiiController::batteryLightingLED()
{
	//	�O��̏�Ԃ�ۑ�
	LEDTypePrev = LEDType;

	//	���݂̃o�b�e���[�ʎ擾
	float currentBattery = (float)wiiRemote->BatteryPercent;

	//	�������Z�o
	float percentage = currentBattery / batteryMax;

	//	�����ɉ����ē_��������LED�̌�������
	if(percentage < 0.1f)
		LEDType = LED_0;
	else if(percentage < 0.2f)
		LEDType = LED_1;
	else if(percentage < 0.3f)
		LEDType = LED_2;
	else if(percentage < 0.5f)
		LEDType = LED_3;
	else
		LEDType = LED_4;

	//	�[�d�ʂ�10%�ȉ��̏ꍇ
	if(LEDType == LED_0)
	{
		LEDCounter++;

		//	�_��
		if(LEDCounter < LEDCounterMax * 0.5)
			wiiRemote->SetLEDs(0x0001);
		else
			wiiRemote->SetLEDs(0x0000);

		//	�J�E���^�[������
		if(LEDCounter == LEDCounterMax)
			LEDCounter = 0;
	}
	else
	{
		//	�������ύX���ꂽ��
		if(LEDType != LEDTypePrev)
			wiiRemote->SetLEDs(LEDType);
	}
}

//=============================================================================
//	���ʂ̍X�V����
//=============================================================================
void CWiiController::CommonUpdate()
{
	//	wii�����R�����ڑ�����Ă����
	if(wiiRemote != nullptr)
	{
		//	�O��̏�Ԃ�ۑ�
		buttonStatePrev = buttonState;

		accelPrev = accel;
		accelRawPrev = accelRaw;

		rotPrev = rot;
		rotRawPrev = rotRaw;

		rotSpeedPrev = rotSpeed;
		rotSpeedRawPrev = rotSpeedRaw;

		joystickPrev = joystick;

		IRPrev = IR;
		IRScreenPrev = IRScreen;

		motionConnectPrev = motionConnect;

		updateAgePrev = updateAge;

		//	���[�V�����Z���T�[���F�����ꂽ��L����
		motionConnect = wiiRemote->MotionPlusConnected();
		if (motionConnect == true && motionConnectPrev == false)
		{
			wiiRemote->EnableMotionPlus();
			rotResetFlag = true;
		}

		//	LED�_��
		batteryLightingLED();

		//	wii�����R���̏�Ԃ��擾...�Ƃ��������Z�b�g
		//	������Ȃ��ƃX�e�[�^�X���X�V����Ȃ�
		wiiRemote->RefreshState();

		//	�{�^���̉�����Ԃ�ۑ�
		buttonState = wiiRemote->Button.Bits;

		//	�k���`���N�̉�����Ԃ�ۑ�
		buttonState += wiiRemote->Nunchuk.C * 0x0020;
		buttonState += wiiRemote->Nunchuk.Z * 0x0040;

		//	���s�[�g�J�E���g�̍X�V
		for (int count = 0; count < WC_BUTTON_MAX; count++)
		{
			if (buttonState & BUTTON_STATE_BITS[count])
				(repeatCount[count] < REPEAT_COUNT_MAX) ? repeatCount[count]++ : repeatCount[count] = REPEAT_COUNT_MAX;
			else
				repeatCount[count] = 0;
		}

		//	�����x��ۑ�
		accel = D3DXVECTOR3(wiiRemote->Acceleration.X, wiiRemote->Acceleration.Y, wiiRemote->Acceleration.Z);
		accelRaw = D3DXVECTOR3(wiiRemote->Acceleration.RawX, wiiRemote->Acceleration.RawY, wiiRemote->Acceleration.RawZ);
		updateAge = wiiRemote->Acceleration.Orientation.UpdateAge;

		//	�����[�V�����v���X�̐ڑ��󋵂ɂ���ď�����ύX
		//	���[�V�����v���X�ڑ����̏���
		if (motionConnect == true)
		{
			//	�p���x��ۑ�
			rotSpeedRaw = D3DXVECTOR3(wiiRemote->MotionPlus.Raw.Pitch + cutOffHZ_XRaw, wiiRemote->MotionPlus.Raw.Yaw + cutOffHZ_YRaw, wiiRemote->MotionPlus.Raw.Roll + cutOffHZ_ZRaw);
			rotSpeedRaw /= 100.0f;
			rotSpeed = D3DXVECTOR3(wiiRemote->MotionPlus.Speed.Pitch + cutOffHZ_X, wiiRemote->MotionPlus.Speed.Yaw + cutOffHZ_Y, wiiRemote->MotionPlus.Speed.Roll + cutOffHZ_Z);

			//	����
			adJustmentRotSpeed();

			//	�Z�o�p�x(Yaw Pitch Roll)
			D3DXVECTOR3 YPR(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 YPRRaw(0.0f, 0.0f, 0.0f);

			//	�I�t�Z�b�g�l(�����l�������Ă���)
			//	���{���̓L�����u���[�V�����i�����ȂƂ��Ɉ�莞�Ԓu���Ă��Ă�j�̒l�����邱��
			//	���̒l��wii�����R���Ԑ�p�̒l
			static D3DXVECTOR3 offset_YPR(168.0f, 168.0f, 66.0f);
			static D3DXVECTOR3 offset_YPRRaw(168.0f, 168.0f, 66.0f);

			//	�ꎞ�ϐ�(�L�����u���[�V�����̍ۂɎg��)
			static D3DXVECTOR3 temp_YPR(0.0f, 0.0f, 0.0f);
			static D3DXVECTOR3 temp_YPRRaw(0.0f, 0.0f, 0.0f);

			//	�L�����u���[�V�����v�Z���s��
			if (rotSpeedCalibrationFlag == true)
			{
				temp_YPR += rotSpeed;
				temp_YPRRaw += rotSpeedRaw;

				rotSpeedCalibrationCount++;

				//	�w��̉񐔃T���v�����O������
				if (rotSpeedCalibrationCount >= rotSpeedCalibrationCountMax)
				{
					//	�I�t�Z�b�g�l���Z�o
					offset_YPR = temp_YPR / (float)rotSpeedCalibrationCountMax;
					offset_YPRRaw = temp_YPRRaw / (float)rotSpeedCalibrationCountMax;

					//	�ϐ�������
					temp_YPR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					temp_YPRRaw = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					rotSpeedCalibrationCount = 0;
					rotSpeedCalibrationFlag = false;
				}
			}

			//	�p���x�␳
			rotSpeed -= temp_YPR;
			rotSpeedRaw -= temp_YPRRaw;

			//	�t���[�����[�g�v��
			static DWORD time = timeGetTime();
			//	1�t���[��������̎��Ԍv��
			DWORD frametime = timeGetTime() - time;
			time = timeGetTime();

			//	�p�x���v�Z(�P���ϕ�)
			//	�p�x = �p���x[deg/sec] * ����[sec]
			/*if( rotSpeed.x > cutOffHZ_X || rotSpeed.x < -cutOffHZ_X )
			{
			YPR.x = rotSpeed.x * frametime / 1000.0f;
			rot.x += YPR.x;
			}
			if( rotSpeed.y > cutOffHZ_Y || rotSpeed.y < -cutOffHZ_Y )
			{
			YPR.y = rotSpeed.y * frametime / 1000.0f;
			rot.y += YPR.y;
			}
			if( rotSpeed.z > cutOffHZ_Z || rotSpeed.z < -cutOffHZ_Z )
			{
			YPR.z = rotSpeed.z * frametime / 1000.0f;
			rot.z += YPR.z;
			}*/

			//	�p�x���v�Z(��`���)
			//	�p�x = ((�P�O�̊p���x[deg/sec] + ���̊p���x[deg/sec]) * 0.5) * ����[sec]
			//	�������ĕ�Ԃ���ˁ[�����E�E�E
			//	cutOffHZ�𒲐�����K�v����
			if (rotSpeed.x > cuttOffHZ || rotSpeed.x < -cuttOffHZ)
			{
				YPR.x = ((rotSpeed.x + rotSpeedPrev.x) * 0.5f) * (frametime / 1000.0f);
				rot.x += YPR.x;
			}
			if (rotSpeed.y > cuttOffHZ || rotSpeed.y < -cuttOffHZ)
			{
				YPR.y = ((rotSpeed.y + rotSpeedPrev.y) * 0.5f) * (frametime / 1000.0f);
				rot.y += YPR.y;
			}
			if (rotSpeed.z > cuttOffHZ || rotSpeed.z < -cuttOffHZ)
			{
				YPR.z = ((rotSpeed.z + rotSpeedPrev.z) * 0.5f) * (frametime / 1000.0f);
				rot.z += YPR.z;
			}

			if (rotSpeedRaw.x > cuttOffHZRaw || rotSpeedRaw.x < -cuttOffHZRaw)
			{
				YPRRaw.x = ((rotSpeedRaw.x + rotSpeedRawPrev.x) * 0.5f) * (frametime / 1000.0f);
				rotRaw.x += YPRRaw.x;
			}
			if (rotSpeedRaw.y > cuttOffHZRaw || rotSpeedRaw.y < -cuttOffHZRaw)
			{
				YPRRaw.y = ((rotSpeedRaw.y + rotSpeedRawPrev.y) * 0.5f) * (frametime / 1000.0f);
				rotRaw.y += YPRRaw.y;
			}
			if (rotSpeedRaw.z > cuttOffHZRaw || rotSpeedRaw.z < -cuttOffHZRaw)
			{
				YPRRaw.z = ((rotSpeedRaw.z + rotSpeedRawPrev.z) * 0.5f) * (frametime / 1000.0f);
				rotRaw.z += YPRRaw.z;
			}


			//	�p�������Z�b�g
			if (rotResetFlag == true)
			{
				rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				rotRaw = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				rotResetFlag = false;
			}

			//	�I�[�o�[�t���[�΍�
			if (rot.x <= -180.0f)
				rot.x = 180.0f;
			if (rot.x > 180.0f)
				rot.x = -180.0f;
			if (rot.y <= -180.0f)
				rot.y = 180.0f;
			if (rot.y > 180.0f)
				rot.y = -180.0f;
			if (rot.z <= -180.0f)
				rot.z = 180.0f;
			if (rot.z > 180.0f)
				rot.z = -180.0f;

			if (rotRaw.x <= -180.0f)
				rotRaw.x = 180.0f;
			if (rotRaw.x > 180.0f)
				rotRaw.x = -180.0f;
			if (rotRaw.y <= -180.0f)
				rotRaw.y = 180.0f;
			if (rotRaw.y > 180.0f)
				rotRaw.y = -180.0f;
			if (rotRaw.z <= -180.0f)
				rotRaw.z = 180.0f;
			if (rotRaw.z > 180.0f)
				rotRaw.z = -180.0f;
		}
		//	���[�V�����v���X���ڑ����̏���
		else
		{
			//	��]�p��ۑ��i�{�̂̂݁j
			//	�����x�Z���T�[�Ōv�Z���Ă��邽�ߐ��x�Ⴂ�E�E�E�Ƃ������Ԉ���Ă�񂶂�ˁH
			rot = D3DXVECTOR3(wiiRemote->Acceleration.Orientation.X, wiiRemote->Acceleration.Orientation.Y, wiiRemote->Acceleration.Orientation.Z);
		}

		//	IR���̎擾
		if (wiiRemote->IR.Dot[0].bVisible == true)
		{
			//	-1.0 �` 1.0�̊ԂłƂ�ꍇ
			IR = D3DXVECTOR2((wiiRemote->IR.Dot[0].X - 0.5f) * 2.0f, (wiiRemote->IR.Dot[0].Y - 0.5f) * 2.0f);

			//	0.0 �` 1.0�̊ԂłƂ�ꍇ
			//IR = D3DXVECTOR2(wiiRemote->IR.Dot[0].X, wiiRemote->IR.Dot[0].Y);

			//	�X�N���[�����W�n�v�Z
			IRScreen.x = IR.x * (screenWidth * 0.5f);
			IRScreen.y = -IR.y * (screenHeight * 0.5f);
		}

		//	�k���`���N���ڑ�����Ă�����
		if (wiiRemote->NunchukConnected())
		{
			//	�����x�Ɖ����x����Z�o�����p�x��ۑ�
			accelN = D3DXVECTOR3(wiiRemote->Nunchuk.Acceleration.X, wiiRemote->Nunchuk.Acceleration.Y, wiiRemote->Nunchuk.Acceleration.Z);
			rotN = D3DXVECTOR3(wiiRemote->Nunchuk.Acceleration.Orientation.X, wiiRemote->Nunchuk.Acceleration.Orientation.Y, wiiRemote->Nunchuk.Acceleration.Orientation.Z);

			//	�k���`���N�̃W���C�X�e�B�b�N���擾
			joystick = D3DXVECTOR2(wiiRemote->Nunchuk.Joystick.X, wiiRemote->Nunchuk.Joystick.Y);

			//	�����Ə���̒���
			if ((joystick.x < joyStickDeadZone) && (joystick.x > -joyStickDeadZone))
				joystick.x = 0.0f;
			if ((joystick.y < joyStickDeadZone) && (joystick.y > -joyStickDeadZone))
				joystick.y = 0.0f;

			if (joystick.x > joyStickMax)
				joystick.x = joyStickMax;
			if (joystick.x < -joyStickMax)
				joystick.x = -joyStickMax;

			if (joystick.y > joyStickMax)
				joystick.y = joyStickMax;
			if (joystick.y < -joyStickMax)
				joystick.y = -joyStickMax;
		}
	}

	//	�o�����Xwii�{�[�h(�ȉ��Awii�{�[�h)���ڑ�����Ă����
	if(wiiBoard != nullptr)
	{
		//	wii�{�[�h�̏�Ԃ��擾...�Ƃ��������Z�b�g
		//	������Ȃ��ƃX�e�[�^�X���X�V����Ȃ�
		wiiBoard->RefreshState();
	}
}
//=============================================================================
//	������Ԃ̍X�V����
//=============================================================================
void CWiiController::NormalUpdate()
{
#ifdef OASOBI
	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_ONE]) && (buttonState & BUTTON_STATE_BITS[WC_ONE]))
	{
		//	�X�V�֐��Z�b�g
		fpUpdate = &CWiiController::updateMode1;
		rumble(true);
	}
#endif
}

//=============================================================================
//	�X�V�������[�h�P
//
//	�k�����ςȂ�
//=============================================================================
void CWiiController::updateMode1()
{
	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_HOME]) && (buttonState & BUTTON_STATE_BITS[WC_HOME]))
	{
		//	�X�V�֐��Z�b�g
		fpUpdate = &CWiiController::updateMode2;
		rumble(false);
	}
}
//=============================================================================
//	�X�V�������[�h�Q
//
//	�K���I�ȓ_�łP
//=============================================================================
void CWiiController::updateMode2()
{
	static int mode2Count = 0;

	if (mode2Count == 0)
	{
		rumble(true);
	}
	else if (mode2Count == 20)
	{
		rumble(false);
	}
	else if (mode2Count == 40)
	{
		mode2Count = -1;
	}

	mode2Count++;

	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_HOME]) && (buttonState & BUTTON_STATE_BITS[WC_HOME]))
	{
		//	�X�V�֐��Z�b�g
		fpUpdate = &CWiiController::updateMode3;
		rumble(false);
		mode2Count = 0;
	}
}
//=============================================================================
//	�X�V�������[�h�R
//
//	�K���I�ȓ_�łQ
//=============================================================================
void CWiiController::updateMode3()
{
	static int mode3Count = 0;

	if (mode3Count == 0)
	{
		rumble(true);
	}
	else if (mode3Count == 30)
	{
		rumble(false);
	}
	else if (mode3Count == 50)
	{
		mode3Count = -1;
	}

	mode3Count++;

	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_HOME]) && (buttonState & BUTTON_STATE_BITS[WC_HOME]))
	{
		//	�X�V�֐��Z�b�g
		fpUpdate = &CWiiController::updateMode4;
		rumble(false);
		mode3Count = 0;
	}
}
//=============================================================================
//	�X�V�������[�h�S
//
//	�K���I�ȓ_�łR
//=============================================================================
void CWiiController::updateMode4()
{
	static int mode4Count = 0;

	if (mode4Count == 0)
	{
		rumble(true);
	}
	else if (mode4Count == 40)
	{
		rumble(false);
	}
	else if (mode4Count == 60)
	{
		mode4Count = -1;
	}

	mode4Count++;

	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_HOME]) && (buttonState & BUTTON_STATE_BITS[WC_HOME]))
	{
		//	�X�V�֐��Z�b�g
		fpUpdate = &CWiiController::NormalUpdate;
		rumble(false);
		mode4Count = 0;
	}
}
//=============================================================================
//	�X�V�������[�h�T
//
//	�K���I�ȓ_�łS
//=============================================================================
void CWiiController::updateMode5()
{
	static int mode5Count = 0;
	static int mode5RandamTrue = rand() % 50;
	static int mode5RandamFalse = rand() % 20;

	if (mode5Count == 0)
	{
		rumble(true);
	}
	else if (mode5Count == mode5RandamTrue)
	{
		rumble(false);
	}
	else if (mode5Count == mode5RandamFalse + 50)
	{
		mode5Count = -1;

		mode5RandamTrue = rand() % 50;
		mode5RandamFalse = rand() % 20;
	}

	mode5Count++;

	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_HOME]) && (buttonState & BUTTON_STATE_BITS[WC_HOME]))
	{
		//	�X�V�֐��Z�b�g
		fpUpdate = &CWiiController::NormalUpdate;
		rumble(false);
		mode5Count = 0;
	}
}

//=============================================================================
//	�X�V����
//=============================================================================
void CWiiController::update()
{
	CommonUpdate();
	(this->*fpUpdate)();
}
//=============================================================================
//	�p���x�̂܂�ߑ���i�����j
//=============================================================================
void CWiiController::adJustmentRotSpeed()
{
	if(rotSpeed.x > rotSpeedMax)
		rotSpeed.x = rotSpeedMax;
	if(rotSpeed.y > rotSpeedMax)
		rotSpeed.y = rotSpeedMax;
	if(rotSpeed.z > rotSpeedMax)
		rotSpeed.z = rotSpeedMax;

	if(rotSpeed.x < -rotSpeedMax)
		rotSpeed.x = -rotSpeedMax;
	if(rotSpeed.y < -rotSpeedMax)
		rotSpeed.y = -rotSpeedMax;
	if(rotSpeed.z < -rotSpeedMax)
		rotSpeed.z = -rotSpeedMax;


	if (rotSpeedRaw.x > rotSpeedRawMax)
		rotSpeedRaw.x = rotSpeedRawMax;
	if (rotSpeedRaw.y > rotSpeedRawMax)
		rotSpeedRaw.y = rotSpeedRawMax;
	if (rotSpeedRaw.z > rotSpeedRawMax)
		rotSpeedRaw.z = rotSpeedRawMax;

	if (rotSpeedRaw.x < -rotSpeedRawMax)
		rotSpeedRaw.x = -rotSpeedRawMax;
	if (rotSpeedRaw.y < -rotSpeedRawMax)
		rotSpeedRaw.y = -rotSpeedRawMax;
	if (rotSpeedRaw.z < -rotSpeedRawMax)
		rotSpeedRaw.z = -rotSpeedRawMax;
}
//=============================================================================
//	�e��Q�b�^�[
//=============================================================================
bool CWiiController::getPress(WC_BUTTON _button)
{
	return (buttonState & BUTTON_STATE_BITS[_button]) ? true : false;
}
bool CWiiController::getTrigger(WC_BUTTON _button)
{
	return (!(buttonStatePrev & BUTTON_STATE_BITS[_button]) && (buttonState & BUTTON_STATE_BITS[_button])) ? true : false;
}
bool CWiiController::getRelease(WC_BUTTON _button)
{
	return ((buttonStatePrev & BUTTON_STATE_BITS[_button]) && !(buttonState & BUTTON_STATE_BITS[_button])) ? true : false;
}
bool CWiiController::getRepeat(WC_BUTTON _button)
{
	if (repeatCount[_button] == REPEAT_COUNT_MAX)
		return (buttonState & BUTTON_STATE_BITS[_button]) ? true : false;
	else
		return false;
}

//-----------------------------------EOF---------------------------------------