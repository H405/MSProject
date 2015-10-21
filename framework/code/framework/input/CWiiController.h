//*****************************************************************************
//	 [ CWiiController.h ]
//	Author : KOTARO NAGASAKI
//
//
//	wii�R���g���[���[�F���p
//	wiiYourself(wiimote)�̃N���X�����āA�F�X�Ǝg���₷�������N���X
//
//	�����ӓ_
//	�Ȃ񂩁A�Q�[���p�b�h�̐ڑ����������Ƃ���Connect�����s����
//	�ǋL	wii�����R����ڑ�������ԂŃQ�[���p�b�h�̐ڑ����ɍs����
//			�Q�[���p�b�h�Ƃ��ĔF�������̂Œ��ӁI
//
//	�ǋL	�k���`���N�ƃ��[�V�����v���X�͓����ɐڑ��ł��Ȃ�
//			�W���C���Z���T�[�i�p���x�Z���T�[�j�̌v���������Ƃ��Ă�
//			����܂萸�x�ǂ��Ȃ��̂ŁA�p�x�̕ψق��Ƃ邮�炢�ɂƂǂ߂���������������
//*****************************************************************************
#ifndef _CWIICONTROLLER_H_
#define _CWIICONTROLLER_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "d3dx9.h"
#include "wiimote.h"

#define OASOBI

//*****************************************************************************
//	�萔��`
//*****************************************************************************

//	�ڑ����s�񐔂̏��
#define CONNECT_TRY_NUM (5)

//	�{�^���̍ő吔
#define WC_BUTTON_MAX (11)

//	���s�[�g�J�E���g�̍ő�l
#define REPEAT_COUNT_MAX (60)

//*****************************************************************************
//	�񋓑̒�`
//*****************************************************************************

//	Wii�����R���̃{�^����
typedef enum
{
	WC_LEFT = 0,	// ���{�^��		0x0001
	WC_RIGHT,		// ���{�^��		0x0002
	WC_DOWN,		// ���{�^��		0x0004
	WC_UP,			// ���{�^��		0x0008
	WC_PLUS,		// �{�{�^��		0x0010

	WC_C,			// C�{�^��		0x0020
	WC_Z,			// Z�{�^��		0x0040

	WC_TWO,			// �Q�{�^��		0x0100
	WC_ONE,			// �P�{�^��		0x0200
	WC_B,			// �a�{�^��		0x0400
	WC_A,			// �`�{�^��		0x0800
	WC_MINUS,		// �|�{�^��		0x1000
	WC_HOME,		// HOME�{�^��	0x8000
	WC_ALL,			// ����
}WC_BUTTON;

//	�_��������LED�̃^�C�v
typedef enum
{
	LED_0 = 0x0000,
	LED_1 = 0x0001,
	LED_2 = 0x0003,
	LED_3 = 0x0007,
	LED_4 = 0x000F,
	LED_MAX
}LED_TYPE;

//	LED�̓_���ɉ�����BIT�z��
//	�������琔����
//	1�Ԗ�		0x0001
//	2�Ԗ�		0x0002
//	1,2�Ԗ�		0x0003
//	3�Ԗ�		0x0004
//	1,3�Ԗ�		0x0005
//	2,3�Ԗ�		0x0006
//	1,2,3�Ԗ�	0x0007
//	4�Ԗ�		0x0008
//	1,4�Ԗ�		0x0009
//	2,4�Ԗ�		0x000A
//	1,2,4�Ԗ�	0x000B
//	3,4�Ԗ�		0x000C
//	1,3,4�Ԗ�	0x000D
//	2,3,4�Ԗ�	0x000E
//	1,2,3,4�Ԗ�	0x000F
//	��
//	0x0010�@�ȏ���w�肷��ƃG���[�Ŏ~�܂�

typedef enum
{
	ROT_RESET_TYPE_X_P_ONE = 0,
	ROT_RESET_TYPE_X_M_ONE,
	ROT_RESET_TYPE_Y_P_ONE,
	ROT_RESET_TYPE_Y_M_ONE,
	ROT_RESET_TYPE_Z_P_ONE,
	ROT_RESET_TYPE_Z_M_ONE,
}ROT_RESET_TYPE;

//=============================================================================
//	�N���X��`
//=============================================================================
class CWiiController
{
public:

	CWiiController();
	~CWiiController();
	void update();

	//	�ڑ���Ԃ̎擾
	bool getConnectFlag(){ return wiiRemote->IsConnected(); }

	//	���[�V�����Z���T�[���q�����Ă邩
	bool getMotionConnect(){ return motionConnect; }

	//	�e��{�^����Ԃ̎擾
	bool getPress(WC_BUTTON _button);
	bool getTrigger(WC_BUTTON _button);
	bool getRelease(WC_BUTTON _button);
	bool getRepeat(WC_BUTTON _button);

	//	�����x�擾
	//------------------------------------------------------------------
	//	���������l�i���x���j
	//	���������A-5.0f �` 5.0f �̊�
	D3DXVECTOR3 getAcceleration(){ return accel; }
	float getAccelerationX(){ return accel.x; }
	float getAccelerationY(){ return accel.y; }
	float getAccelerationZ(){ return accel.z; }

	D3DXVECTOR3 getAccelerationPrev(){ return accelPrev; }
	float getAccelerationPrevX(){ return accelPrev.x; }
	float getAccelerationPrevY(){ return accelPrev.y; }
	float getAccelerationPrevZ(){ return accelPrev.z; }
	
	//	�����l�i���x��j
	D3DXVECTOR3 getAccelerationRaw(){ return accelRaw; }
	float getAccelerationRawX(){ return accelRaw.x; }
	float getAccelerationRawY(){ return accelRaw.y; }
	float getAccelerationRawZ(){ return accelRaw.z; }

	D3DXVECTOR3 getAccelerationRawPrev(){ return accelRawPrev; }
	float getAccelerationRawPrevX(){ return accelRawPrev.x; }
	float getAccelerationRawPrevY(){ return accelRawPrev.y; }
	float getAccelerationRawPrevZ(){ return accelRawPrev.z; }

	D3DXVECTOR3 getAccelerationN(){ return accelN; }
	float getAccelerationNX(){ return accelN.x; }
	float getAccelerationNY(){ return accelN.y; }
	float getAccelerationNZ(){ return accelN.z; }
	//------------------------------------------------------------------

	//	�U���Ă邩�U���Ă��Ȃ���(Yaw�p�͖��Ή�)
	unsigned int getUpdateAge(){ return updateAge; }
	unsigned int getUpdateAgePrev(){ return updateAgePrev; }

	//	��]�p�擾
	//------------------------------------------------------------------
	//	���x��(�덷��)
	D3DXVECTOR3 getRot(){ return rot; }
	float getRotX(){ return rot.x; }
	float getRotY(){ return rot.y; }
	float getRotZ(){ return rot.z; }

	//	���x��(�덷��)
	D3DXVECTOR3 getRotRaw(){ return rotRaw; }
	float getRotRawX(){ return rotRaw.x; }
	float getRotRawY(){ return rotRaw.y; }
	float getRotRawZ(){ return rotRaw.z; }

	D3DXVECTOR3 getRotN(){ return rotN; }
	float getRotNX(){ return rotN.x; }
	float getRotNY(){ return rotN.y; }
	float getRotNZ(){ return rotN.z; }
	//------------------------------------------------------------------

	//	��]�p�̕ψق��擾(1�t���[���O - ����)
	//------------------------------------------------------------------
	//	���x��(�덷��)
	D3DXVECTOR3 getChangeRot(){ return rotPrev - rot; }
	float getChangeRotX(){ return rotPrev.x - rot.x; }
	float getChangeRotY(){ return rotPrev.y - rot.y; }
	float getChangeRotZ(){ return rotPrev.z - rot.z; }

	//	���x��(�덷��)
	D3DXVECTOR3 getChangeRotRaw(){ return rotRawPrev - rotRaw; }
	float getChangeRotRawX(){ return rotRawPrev.x - rotRaw.x; }
	float getChangeRotRawY(){ return rotRawPrev.y - rotRaw.y; }
	float getChangeRotRawZ(){ return rotRawPrev.z - rotRaw.z; }
	//------------------------------------------------------------------

	//	�p���x�擾
	//------------------------------------------------------------------
	//	���x��(�덷��)
	D3DXVECTOR3 getRotSpeed(){ return rotSpeed; }
	float getRotSpeedX(){ return rotSpeed.x; }
	float getRotSpeedY(){ return rotSpeed.y; }
	float getRotSpeedZ(){ return rotSpeed.z; }

	//	���x��(�덷��)
	D3DXVECTOR3 getRotSpeedRaw(){ return rotSpeedRaw; }
	float getRotSpeedRawX(){ return rotSpeedRaw.x; }
	float getRotSpeedRawY(){ return rotSpeedRaw.y; }
	float getRotSpeedRawZ(){ return rotSpeedRaw.z; }
	//------------------------------------------------------------------

	//	�k���`���N�̃W���C�X�e�B�b�N�̒l
	//	���������A-1.0f �` 1.0f �̊�
	D3DXVECTOR2 getJoystick(){return joystick;}

	//	IR�̒l
	//	�擾�ł��Ȃ��ꍇ�� X:0.0f Y:0.0f ���Ԃ�
	//	���X�́A0�`1 �̊Ԃ����ǁA-1 �` 1 �̊Ԃɒ������ĕԂ�
	//	�������āA�擾�ł��Ȃ��ꍇ�� X:-1.0f Y:-1.0f ���Ԃ�
	//	�ԊO���ŔF���ł��Ȃ��ꏊ�ɂ������ꍇ�́A�Ō�ɂƂꂽ�l���Ԃ�
	D3DXVECTOR2 getIR(){return IR;}

	//	true�ŐU���@false�ŐU�����~�߂�
	void rumble(bool _flag){ wiiRemote->SetRumble(_flag); }
	//	�w�肵���b��(�~���b)�U������������
	void rumble(unsigned int _milliseconds){ wiiRemote->RumbleForAsync(_milliseconds); }

	//	�o�b�e���[�̎c�ʂ��擾
	int battery(){ return wiiRemote->BatteryPercent; }

	//	�����o��
	//	�P�ڂ̈����Ɏ��g���A�Q�ڂ̈����ɉ��ʁi0x00 �` 0x10�j���w��
	//	��߂��ɏI��������ƃo�O�邩�璍��

	//	wiimote_common.h���甲���������g��
	/*enum speaker_freq
	//{
	//	FREQ_NONE = 0,
	//	FREQ_4200HZ = 1,
	//	FREQ_3920HZ = 2,
	//	FREQ_3640HZ = 3,
	//	FREQ_3360HZ = 4,
	//	FREQ_3130HZ = 5,
	//	FREQ_2940HZ = 6,
	//	FREQ_2760HZ = 7,
	//	FREQ_2610HZ = 8,
	//	FREQ_2470HZ = 9,
	};*/
	void playSound(speaker_freq _hz, BYTE _volume){ wiiRemote->PlaySquareWave(_hz, _volume); }

	void rotSpeedCalibration(){rotSpeedCalibrationFlag = true;}
	void rotReset(){rotResetFlag = true;}

	bool isConnect;

private:

	//	�o�b�e���[�̏[�d�ʂɉ�����LED��_��������
	void batteryLightingLED();

	//	�p���x���܂�߂�
	void adJustmentRotSpeed();

	//	���V�їp
	void CommonUpdate();
	void NormalUpdate();
	void updateMode1();
	void updateMode2();
	void updateMode3();
	void updateMode4();
	void updateMode5();


	//	�R���g���[���{��
	wiimote* wiiRemote;

	//	�o�����Xwii�{�[�h�{��
	wiimote* wiiBoard;

	//	�{�^���̉������
	WORD buttonState;
	WORD buttonStatePrev;

	//	�{�̂̉����x
	//--------------------------------
	//	���x��
	D3DXVECTOR3 accel;
	D3DXVECTOR3 accelPrev;

	//	���x��
	D3DXVECTOR3 accelRaw;
	D3DXVECTOR3 accelRawPrev;
	//--------------------------------

	//	�{�̂̉�]�p
	//--------------------------------
	//	���x��
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotPrev;

	//	���x��
	D3DXVECTOR3 rotRaw;
	D3DXVECTOR3 rotRawPrev;
	//--------------------------------

	//	�p���x(�W���C���v�Z�p)
	//--------------------------------
	//	���x��
	D3DXVECTOR3 rotSpeed;
	D3DXVECTOR3 rotSpeedPrev;

	//	���x��
	D3DXVECTOR3 rotSpeedRaw;
	D3DXVECTOR3 rotSpeedRawPrev;
	//--------------------------------

	//	�k���`���N�̉����x
	D3DXVECTOR3 accelN;
	D3DXVECTOR3 accelNPrev;

	//	�k���`���N�̉�]�p
	D3DXVECTOR3 rotN;
	D3DXVECTOR3 rotNPrev;

	//	�W���C�X�e�B�b�N
	D3DXVECTOR2 joystick;
	D3DXVECTOR2 joystickPrev;

	//	IR(�ԊO���Z���T�[�̈ʒu)
	D3DXVECTOR2 IR;
	D3DXVECTOR2 IRPrev;

	//	���s�[�g�J�E���g�̊i�[
	int repeatCount[WC_ALL];

	//	�o�b�e���[�^�C�v
	LED_TYPE LEDType;
	LED_TYPE LEDTypePrev;

	//	LED�_�ŗp�̃J�E���^
	int LEDCounter;

	//	�W���C����F�����Ă��邩�ǂ���
	bool motionConnect;
	bool motionConnectPrev;

	//	�W���C���ɂ��p���̃��Z�b�g�t���O
	bool rotResetFlag;

	//	�L�����u���[�V�������s���t���O
	bool rotSpeedCalibrationFlag;

	//	�L�����u���[�V�����p�J�E���^
	int rotSpeedCalibrationCount;

	//	�����x�̌덷���m(�U���Ă邩�U���Ă��Ȃ���)
	unsigned int updateAge;
	unsigned int updateAgePrev;

	void (CWiiController::*fpUpdate)(void);
};

#endif
//-----------------------------------EOF---------------------------------------