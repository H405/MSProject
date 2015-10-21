//*****************************************************************************
//	 [ CWiiController.h ]
//	Author : KOTARO NAGASAKI
//
//
//	wiiコントローラー認識用
//	wiiYourself(wiimote)のクラスを内包して、色々と使いやすくしたクラス
//
//	※注意点
//	なんか、ゲームパッドの接続をしたあとだとConnectが失敗する
//	追記	wiiリモコンを接続した状態でゲームパッドの接続を先に行うと
//			ゲームパッドとして認識されるので注意！
//
//	追記	ヌンチャクとモーションプラスは同時に接続できない
//			ジャイロセンサー（角速度センサー）の計測をしたとしても
//			あんまり精度良くないので、角度の変異をとるぐらいにとどめた方がいいかもね
//*****************************************************************************
#ifndef _CWIICONTROLLER_H_
#define _CWIICONTROLLER_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "d3dx9.h"
#include "wiimote.h"

#define OASOBI

//*****************************************************************************
//	定数定義
//*****************************************************************************

//	接続試行回数の上限
#define CONNECT_TRY_NUM (5)

//	ボタンの最大数
#define WC_BUTTON_MAX (11)

//	リピートカウントの最大値
#define REPEAT_COUNT_MAX (60)

//*****************************************************************************
//	列挙体定義
//*****************************************************************************

//	Wiiリモコンのボタン数
typedef enum
{
	WC_LEFT = 0,	// ←ボタン		0x0001
	WC_RIGHT,		// →ボタン		0x0002
	WC_DOWN,		// ↓ボタン		0x0004
	WC_UP,			// ↑ボタン		0x0008
	WC_PLUS,		// ＋ボタン		0x0010

	WC_C,			// Cボタン		0x0020
	WC_Z,			// Zボタン		0x0040

	WC_TWO,			// ２ボタン		0x0100
	WC_ONE,			// １ボタン		0x0200
	WC_B,			// Ｂボタン		0x0400
	WC_A,			// Ａボタン		0x0800
	WC_MINUS,		// －ボタン		0x1000
	WC_HOME,		// HOMEボタン	0x8000
	WC_ALL,			// 総数
}WC_BUTTON;

//	点灯させるLEDのタイプ
typedef enum
{
	LED_0 = 0x0000,
	LED_1 = 0x0001,
	LED_2 = 0x0003,
	LED_3 = 0x0007,
	LED_4 = 0x000F,
	LED_MAX
}LED_TYPE;

//	LEDの点灯に応じたBIT配列
//	※左から数えて
//	1番目		0x0001
//	2番目		0x0002
//	1,2番目		0x0003
//	3番目		0x0004
//	1,3番目		0x0005
//	2,3番目		0x0006
//	1,2,3番目	0x0007
//	4番目		0x0008
//	1,4番目		0x0009
//	2,4番目		0x000A
//	1,2,4番目	0x000B
//	3,4番目		0x000C
//	1,3,4番目	0x000D
//	2,3,4番目	0x000E
//	1,2,3,4番目	0x000F
//	※
//	0x0010　以上を指定するとエラーで止まる

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
//	クラス定義
//=============================================================================
class CWiiController
{
public:

	CWiiController();
	~CWiiController();
	void update();

	//	接続状態の取得
	bool getConnectFlag(){ return wiiRemote->IsConnected(); }

	//	モーションセンサーが繋がってるか
	bool getMotionConnect(){ return motionConnect; }

	//	各種ボタン状態の取得
	bool getPress(WC_BUTTON _button);
	bool getTrigger(WC_BUTTON _button);
	bool getRelease(WC_BUTTON _button);
	bool getRepeat(WC_BUTTON _button);

	//	加速度取得
	//------------------------------------------------------------------
	//	浮動小数値（感度強）
	//	だいたい、-5.0f ～ 5.0f の間
	D3DXVECTOR3 getAcceleration(){ return accel; }
	float getAccelerationX(){ return accel.x; }
	float getAccelerationY(){ return accel.y; }
	float getAccelerationZ(){ return accel.z; }

	D3DXVECTOR3 getAccelerationPrev(){ return accelPrev; }
	float getAccelerationPrevX(){ return accelPrev.x; }
	float getAccelerationPrevY(){ return accelPrev.y; }
	float getAccelerationPrevZ(){ return accelPrev.z; }
	
	//	正数値（感度弱）
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

	//	振ってるか振っていないか(Yaw角は未対応)
	unsigned int getUpdateAge(){ return updateAge; }
	unsigned int getUpdateAgePrev(){ return updateAgePrev; }

	//	回転角取得
	//------------------------------------------------------------------
	//	感度強(誤差小)
	D3DXVECTOR3 getRot(){ return rot; }
	float getRotX(){ return rot.x; }
	float getRotY(){ return rot.y; }
	float getRotZ(){ return rot.z; }

	//	感度弱(誤差大)
	D3DXVECTOR3 getRotRaw(){ return rotRaw; }
	float getRotRawX(){ return rotRaw.x; }
	float getRotRawY(){ return rotRaw.y; }
	float getRotRawZ(){ return rotRaw.z; }

	D3DXVECTOR3 getRotN(){ return rotN; }
	float getRotNX(){ return rotN.x; }
	float getRotNY(){ return rotN.y; }
	float getRotNZ(){ return rotN.z; }
	//------------------------------------------------------------------

	//	回転角の変異を取得(1フレーム前 - 現在)
	//------------------------------------------------------------------
	//	感度強(誤差小)
	D3DXVECTOR3 getChangeRot(){ return rotPrev - rot; }
	float getChangeRotX(){ return rotPrev.x - rot.x; }
	float getChangeRotY(){ return rotPrev.y - rot.y; }
	float getChangeRotZ(){ return rotPrev.z - rot.z; }

	//	感度弱(誤差大)
	D3DXVECTOR3 getChangeRotRaw(){ return rotRawPrev - rotRaw; }
	float getChangeRotRawX(){ return rotRawPrev.x - rotRaw.x; }
	float getChangeRotRawY(){ return rotRawPrev.y - rotRaw.y; }
	float getChangeRotRawZ(){ return rotRawPrev.z - rotRaw.z; }
	//------------------------------------------------------------------

	//	角速度取得
	//------------------------------------------------------------------
	//	感度強(誤差小)
	D3DXVECTOR3 getRotSpeed(){ return rotSpeed; }
	float getRotSpeedX(){ return rotSpeed.x; }
	float getRotSpeedY(){ return rotSpeed.y; }
	float getRotSpeedZ(){ return rotSpeed.z; }

	//	感度弱(誤差大)
	D3DXVECTOR3 getRotSpeedRaw(){ return rotSpeedRaw; }
	float getRotSpeedRawX(){ return rotSpeedRaw.x; }
	float getRotSpeedRawY(){ return rotSpeedRaw.y; }
	float getRotSpeedRawZ(){ return rotSpeedRaw.z; }
	//------------------------------------------------------------------

	//	ヌンチャクのジョイスティックの値
	//	だいたい、-1.0f ～ 1.0f の間
	D3DXVECTOR2 getJoystick(){return joystick;}

	//	IRの値
	//	取得できない場合は X:0.0f Y:0.0f が返る
	//	元々は、0～1 の間だけど、-1 ～ 1 の間に調整して返す
	//	調整して、取得できない場合は X:-1.0f Y:-1.0f が返る
	//	赤外線で認識できない場所にいった場合は、最後にとれた値が返る
	D3DXVECTOR2 getIR(){return IR;}

	//	trueで振動　falseで振動を止める
	void rumble(bool _flag){ wiiRemote->SetRumble(_flag); }
	//	指定した秒数(ミリ秒)振動させ続ける
	void rumble(unsigned int _milliseconds){ wiiRemote->RumbleForAsync(_milliseconds); }

	//	バッテリーの残量を取得
	int battery(){ return wiiRemote->BatteryPercent; }

	//	音を出す
	//	１つ目の引数に周波数、２つ目の引数に音量（0x00 ～ 0x10）を指定
	//	停めずに終了させるとバグるから注意

	//	wiimote_common.hから抜粋した周波数
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

	//	バッテリーの充電量に応じてLEDを点灯させる
	void batteryLightingLED();

	//	角速度をまるめる
	void adJustmentRotSpeed();

	//	お遊び用
	void CommonUpdate();
	void NormalUpdate();
	void updateMode1();
	void updateMode2();
	void updateMode3();
	void updateMode4();
	void updateMode5();


	//	コントローラ本体
	wiimote* wiiRemote;

	//	バランスwiiボード本体
	wiimote* wiiBoard;

	//	ボタンの押下状態
	WORD buttonState;
	WORD buttonStatePrev;

	//	本体の加速度
	//--------------------------------
	//	感度強
	D3DXVECTOR3 accel;
	D3DXVECTOR3 accelPrev;

	//	感度弱
	D3DXVECTOR3 accelRaw;
	D3DXVECTOR3 accelRawPrev;
	//--------------------------------

	//	本体の回転角
	//--------------------------------
	//	感度強
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotPrev;

	//	感度弱
	D3DXVECTOR3 rotRaw;
	D3DXVECTOR3 rotRawPrev;
	//--------------------------------

	//	角速度(ジャイロ計算用)
	//--------------------------------
	//	感度強
	D3DXVECTOR3 rotSpeed;
	D3DXVECTOR3 rotSpeedPrev;

	//	感度弱
	D3DXVECTOR3 rotSpeedRaw;
	D3DXVECTOR3 rotSpeedRawPrev;
	//--------------------------------

	//	ヌンチャクの加速度
	D3DXVECTOR3 accelN;
	D3DXVECTOR3 accelNPrev;

	//	ヌンチャクの回転角
	D3DXVECTOR3 rotN;
	D3DXVECTOR3 rotNPrev;

	//	ジョイスティック
	D3DXVECTOR2 joystick;
	D3DXVECTOR2 joystickPrev;

	//	IR(赤外線センサーの位置)
	D3DXVECTOR2 IR;
	D3DXVECTOR2 IRPrev;

	//	リピートカウントの格納
	int repeatCount[WC_ALL];

	//	バッテリータイプ
	LED_TYPE LEDType;
	LED_TYPE LEDTypePrev;

	//	LED点滅用のカウンタ
	int LEDCounter;

	//	ジャイロを認識しているかどうか
	bool motionConnect;
	bool motionConnectPrev;

	//	ジャイロによる姿勢のリセットフラグ
	bool rotResetFlag;

	//	キャリブレーションを行うフラグ
	bool rotSpeedCalibrationFlag;

	//	キャリブレーション用カウンタ
	int rotSpeedCalibrationCount;

	//	加速度の誤差感知(振ってるか振っていないか)
	unsigned int updateAge;
	unsigned int updateAgePrev;

	void (CWiiController::*fpUpdate)(void);
};

#endif
//-----------------------------------EOF---------------------------------------