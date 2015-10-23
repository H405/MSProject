//*****************************************************************************
//	 [ CWiiController.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "CWiiController.h"
#include <iostream>

//*****************************************************************************
//	定数定義
//*****************************************************************************

//SlowMode（低速時モード）→ 1.45[deg / s]
//FastMode（高速時モード）→ 6.59[deg / s]

//	ボタンの識別子
const int BUTTON_STATE_BITS[WC_ALL] = {
	wiimote_state::buttons::LEFT,	//	0x0001
	wiimote_state::buttons::RIGHT,	//	0x0002
	wiimote_state::buttons::DOWN,	//	0x0004
	wiimote_state::buttons::UP,		//	0x0008
	wiimote_state::buttons::PLUS,	//	0x0010
	/*ヌンチャクCボタン*/				0x0020,
	/*ヌンチャクZボタン*/				0x0040,
	wiimote_state::buttons::TWO,	//	0x0100
	wiimote_state::buttons::ONE,	//	0x0200
	wiimote_state::buttons::_B,		//	0x0400
	wiimote_state::buttons::_A,		//	0x0800
	wiimote_state::buttons::MINUS,	//	0x1000
	wiimote_state::buttons::HOME	//	0x8000
};

//	バッテリー残量の最大値（％）
const float batteryMax = 100.0f;

//	LEDの点滅時用カウンタ
const int LEDCounterMax = 50;

//	ヌンチャクのジョイスティック用しきい値（最小値）
const float joyStickDeadZone = 0.03f;

//	ヌンチャクのジョイスティック用しきい値（最大値）
const float joyStickMax = 1.0f;

// キャリブレーションの際のサンプリング数
const int rotSpeedCalibrationCountMax = 100;

//	角速度のカットオフ周波数（これ以下の変化は無視するってこと）
//	要調整
const float cutOffHZ_X = 7.5f;
const float cutOffHZ_Y = 7.6f;
const float cutOffHZ_Z = 4.0f;

const float cutOffHZ_XRaw = -8200.0f;
const float cutOffHZ_YRaw = -8200.0f;
const float cutOffHZ_ZRaw = -8150.0f;

const float cuttOffHZ = 1.5f;
const float cuttOffHZRaw = 1.5f;

//	１フレームの間で計測できる角速度の最大値を設定
const float rotSpeedMax = 1200.0f;
const float rotSpeedRawMax = 1200.0f;

//	スクリーンサイズをここで設定
const float screenWidth = 1280.0f;
const float screenHeight = 720.0f;

//=============================================================================
//	コンストラクタ
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
		//	本体を生成
		wiimote* buff = new wiimote();

		//	試行回数
		int connectTryCount = 0;
		std::cerr << "waiting connection... \t";

		//	コントローラの本体が、接続できるまでループ（回数制限あり）
		while (!buff->Connect())
		{
			Sleep(10);

			//	一定回数、接続に失敗したら
			if (connectTryCount >= CONNECT_TRY_NUM)
			{
				//	エラー値格納
				connectTryCount = -1;

				//	wiiリモコンが接続されてない
				if (wiiRemote == nullptr)
				{
					MessageBox(NULL, "wiiリモコンの接続はされませんでした", "Message", MB_ICONWARNING);
					delete buff;

					//	更新関数セット
					fpUpdate = &CWiiController::NormalUpdate;

					return;
				}
				//	wiiリモコンは接続されてる
				else if (wiiBoard == nullptr)
				{
					MessageBox(NULL, "wiiボードの接続はされませんでした", "Message", MB_ICONWARNING);
					delete buff;

					//	リピートカウンタの初期化
					for (int count = 0; count < WC_ALL; count++)
						repeatCount[count] = 0;

					//	更新関数セット
					fpUpdate = &CWiiController::NormalUpdate;

					return;
				}
			}
			connectTryCount++;
		}

		if (!buff->IsBalanceBoard())
		{
			//	接続状態セット
			isConnect = true;

			//	一時バッファを本体として登録
			wiiRemote = buff;

			// 使用するセンサを設定（ボタン、加速度、IR、エクステンション（外部接続-ヌンチャクとか））
			wiiRemote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);

			//	スピーカーを有効にする
			wiiRemote->MuteSpeaker(false);
			wiiRemote->EnableSpeaker(true);

			//	LEDをとりあえず全部点灯させる
			wiiRemote->SetLEDs(0x000F);
		}
		else
		{
			//	一時バッファをバランスボードとして登録
			wiiBoard = buff;

			// 使用するセンサを設定（wiiボード）
			wiiBoard->SetReportType(wiimote::IN_BUTTONS_BALANCE_BOARD);
		}
	}

	//	リピートカウンタの初期化
	for (int count = 0; count < WC_ALL; count++)
		repeatCount[count] = 0;

	//	更新関数セット
	fpUpdate = &CWiiController::NormalUpdate;
}

//=============================================================================
//	デストラクタ
//=============================================================================
CWiiController::~CWiiController()
{
	if(wiiRemote != nullptr)
	{
		//	LED消灯
		wiiRemote->SetLEDs(0x0000);

		//	音を消す
		wiiRemote->MuteSpeaker(false);

		//	切断
		wiiRemote->Disconnect();

		delete wiiRemote;
	}

	if(wiiBoard != nullptr)
	{
		delete wiiBoard;
	}
}

//=============================================================================
//	充電量に応じてLEDを点灯させる
//=============================================================================
void CWiiController::batteryLightingLED()
{
	//	前回の状態を保存
	LEDTypePrev = LEDType;

	//	現在のバッテリー量取得
	float currentBattery = (float)wiiRemote->BatteryPercent;

	//	割合を算出
	float percentage = currentBattery / batteryMax;

	//	割合に応じて点灯させるLEDの個数を決定
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

	//	充電量が10%以下の場合
	if(LEDType == LED_0)
	{
		LEDCounter++;

		//	点滅
		if(LEDCounter < LEDCounterMax * 0.5)
			wiiRemote->SetLEDs(0x0001);
		else
			wiiRemote->SetLEDs(0x0000);

		//	カウンター初期化
		if(LEDCounter == LEDCounterMax)
			LEDCounter = 0;
	}
	else
	{
		//	割合が変更されたら
		if(LEDType != LEDTypePrev)
			wiiRemote->SetLEDs(LEDType);
	}
}

//=============================================================================
//	共通の更新処理
//=============================================================================
void CWiiController::CommonUpdate()
{
	//	wiiリモコンが接続されていれば
	if(wiiRemote != nullptr)
	{
		//	前回の状態を保存
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

		//	モーションセンサーが認識されたら有効化
		motionConnect = wiiRemote->MotionPlusConnected();
		if (motionConnect == true && motionConnectPrev == false)
		{
			wiiRemote->EnableMotionPlus();
			rotResetFlag = true;
		}

		//	LED点灯
		batteryLightingLED();

		//	wiiリモコンの状態を取得...というかリセット
		//	これやらないとステータスが更新されない
		wiiRemote->RefreshState();

		//	ボタンの押下状態を保存
		buttonState = wiiRemote->Button.Bits;

		//	ヌンチャクの押下状態を保存
		buttonState += wiiRemote->Nunchuk.C * 0x0020;
		buttonState += wiiRemote->Nunchuk.Z * 0x0040;

		//	リピートカウントの更新
		for (int count = 0; count < WC_BUTTON_MAX; count++)
		{
			if (buttonState & BUTTON_STATE_BITS[count])
				(repeatCount[count] < REPEAT_COUNT_MAX) ? repeatCount[count]++ : repeatCount[count] = REPEAT_COUNT_MAX;
			else
				repeatCount[count] = 0;
		}

		//	加速度を保存
		accel = D3DXVECTOR3(wiiRemote->Acceleration.X, wiiRemote->Acceleration.Y, wiiRemote->Acceleration.Z);
		accelRaw = D3DXVECTOR3(wiiRemote->Acceleration.RawX, wiiRemote->Acceleration.RawY, wiiRemote->Acceleration.RawZ);
		updateAge = wiiRemote->Acceleration.Orientation.UpdateAge;

		//	※モーションプラスの接続状況によって処理を変更
		//	モーションプラス接続時の処理
		if (motionConnect == true)
		{
			//	角速度を保存
			rotSpeedRaw = D3DXVECTOR3(wiiRemote->MotionPlus.Raw.Pitch + cutOffHZ_XRaw, wiiRemote->MotionPlus.Raw.Yaw + cutOffHZ_YRaw, wiiRemote->MotionPlus.Raw.Roll + cutOffHZ_ZRaw);
			rotSpeedRaw /= 100.0f;
			rotSpeed = D3DXVECTOR3(wiiRemote->MotionPlus.Speed.Pitch + cutOffHZ_X, wiiRemote->MotionPlus.Speed.Yaw + cutOffHZ_Y, wiiRemote->MotionPlus.Speed.Roll + cutOffHZ_Z);

			//	調整
			adJustmentRotSpeed();

			//	算出角度(Yaw Pitch Roll)
			D3DXVECTOR3 YPR(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 YPRRaw(0.0f, 0.0f, 0.0f);

			//	オフセット値(初期値を代入しておく)
			//	※本来はキャリブレーション（水平なとこに一定時間置いてってやつ）の値を入れること
			//	この値はwiiリモコン赤専用の値
			static D3DXVECTOR3 offset_YPR(168.0f, 168.0f, 66.0f);
			static D3DXVECTOR3 offset_YPRRaw(168.0f, 168.0f, 66.0f);

			//	一時変数(キャリブレーションの際に使う)
			static D3DXVECTOR3 temp_YPR(0.0f, 0.0f, 0.0f);
			static D3DXVECTOR3 temp_YPRRaw(0.0f, 0.0f, 0.0f);

			//	キャリブレーション計算を行う
			if (rotSpeedCalibrationFlag == true)
			{
				temp_YPR += rotSpeed;
				temp_YPRRaw += rotSpeedRaw;

				rotSpeedCalibrationCount++;

				//	指定の回数サンプリングしたら
				if (rotSpeedCalibrationCount >= rotSpeedCalibrationCountMax)
				{
					//	オフセット値を算出
					offset_YPR = temp_YPR / (float)rotSpeedCalibrationCountMax;
					offset_YPRRaw = temp_YPRRaw / (float)rotSpeedCalibrationCountMax;

					//	変数初期化
					temp_YPR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					temp_YPRRaw = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					rotSpeedCalibrationCount = 0;
					rotSpeedCalibrationFlag = false;
				}
			}

			//	角速度補正
			rotSpeed -= temp_YPR;
			rotSpeedRaw -= temp_YPRRaw;

			//	フレームレート計測
			static DWORD time = timeGetTime();
			//	1フレームあたりの時間計測
			DWORD frametime = timeGetTime() - time;
			time = timeGetTime();

			//	角度を計算(単純積分)
			//	角度 = 角速度[deg/sec] * 時間[sec]
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

			//	角度を計算(台形補間)
			//	角度 = ((１つ前の角速度[deg/sec] + 今の角速度[deg/sec]) * 0.5) * 時間[sec]
			//	たいして補間されねーじゃん・・・
			//	cutOffHZを調整する必要あり
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


			//	姿勢をリセット
			if (rotResetFlag == true)
			{
				rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				rotRaw = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				rotResetFlag = false;
			}

			//	オーバーフロー対策
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
		//	モーションプラス未接続時の処理
		else
		{
			//	回転角を保存（本体のみ）
			//	加速度センサーで計算しているため精度低い・・・というか間違ってるんじゃね？
			rot = D3DXVECTOR3(wiiRemote->Acceleration.Orientation.X, wiiRemote->Acceleration.Orientation.Y, wiiRemote->Acceleration.Orientation.Z);
		}

		//	IR情報の取得
		if (wiiRemote->IR.Dot[0].bVisible == true)
		{
			//	-1.0 ～ 1.0の間でとる場合
			IR = D3DXVECTOR2((wiiRemote->IR.Dot[0].X - 0.5f) * 2.0f, (wiiRemote->IR.Dot[0].Y - 0.5f) * 2.0f);

			//	0.0 ～ 1.0の間でとる場合
			//IR = D3DXVECTOR2(wiiRemote->IR.Dot[0].X, wiiRemote->IR.Dot[0].Y);

			//	スクリーン座標系計算
			IRScreen.x = IR.x * (screenWidth * 0.5f);
			IRScreen.y = -IR.y * (screenHeight * 0.5f);
		}

		//	ヌンチャクが接続されていたら
		if (wiiRemote->NunchukConnected())
		{
			//	加速度と加速度から算出した角度を保存
			accelN = D3DXVECTOR3(wiiRemote->Nunchuk.Acceleration.X, wiiRemote->Nunchuk.Acceleration.Y, wiiRemote->Nunchuk.Acceleration.Z);
			rotN = D3DXVECTOR3(wiiRemote->Nunchuk.Acceleration.Orientation.X, wiiRemote->Nunchuk.Acceleration.Orientation.Y, wiiRemote->Nunchuk.Acceleration.Orientation.Z);

			//	ヌンチャクのジョイスティック情報取得
			joystick = D3DXVECTOR2(wiiRemote->Nunchuk.Joystick.X, wiiRemote->Nunchuk.Joystick.Y);

			//	下限と上限の調整
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

	//	バランスwiiボード(以下、wiiボード)が接続されていれば
	if(wiiBoard != nullptr)
	{
		//	wiiボードの状態を取得...というかリセット
		//	これやらないとステータスが更新されない
		wiiBoard->RefreshState();
	}
}
//=============================================================================
//	初期状態の更新処理
//=============================================================================
void CWiiController::NormalUpdate()
{
#ifdef OASOBI
	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_ONE]) && (buttonState & BUTTON_STATE_BITS[WC_ONE]))
	{
		//	更新関数セット
		fpUpdate = &CWiiController::updateMode1;
		rumble(true);
	}
#endif
}

//=============================================================================
//	更新処理モード１
//
//	震えっぱなし
//=============================================================================
void CWiiController::updateMode1()
{
	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_HOME]) && (buttonState & BUTTON_STATE_BITS[WC_HOME]))
	{
		//	更新関数セット
		fpUpdate = &CWiiController::updateMode2;
		rumble(false);
	}
}
//=============================================================================
//	更新処理モード２
//
//	規則的な点滅１
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
		//	更新関数セット
		fpUpdate = &CWiiController::updateMode3;
		rumble(false);
		mode2Count = 0;
	}
}
//=============================================================================
//	更新処理モード３
//
//	規則的な点滅２
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
		//	更新関数セット
		fpUpdate = &CWiiController::updateMode4;
		rumble(false);
		mode3Count = 0;
	}
}
//=============================================================================
//	更新処理モード４
//
//	規則的な点滅３
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
		//	更新関数セット
		fpUpdate = &CWiiController::NormalUpdate;
		rumble(false);
		mode4Count = 0;
	}
}
//=============================================================================
//	更新処理モード５
//
//	規則的な点滅４
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
		//	更新関数セット
		fpUpdate = &CWiiController::NormalUpdate;
		rumble(false);
		mode5Count = 0;
	}
}

//=============================================================================
//	更新処理
//=============================================================================
void CWiiController::update()
{
	CommonUpdate();
	(this->*fpUpdate)();
}
//=============================================================================
//	角速度のまるめ操作（調整）
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
//	各種ゲッター
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