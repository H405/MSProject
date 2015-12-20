//*****************************************************************************
//	 [ CWiiController.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "CWiiController.h"
#include <iostream>

#include "../develop/Debug.h"
#include "../develop/DebugProc.h"
#include "../develop/DebugMeasure.h"

//*****************************************************************************
//	定数定義
//*****************************************************************************
#define UPDATE_NORMAL
//#define UPDATE_SAVE
//#define UPDATE_READ

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
CWiiController::CWiiController()
{
	//	変数初期化
	initializeSelf();

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
#ifdef _DEBUG
					MessageBox(NULL, "wiiリモコンの接続はされませんでした", "Message", MB_ICONWARNING);
#endif
					delete buff;

					//	更新関数セット
					fpUpdate = &CWiiController::NormalUpdate;
					fpCommonUpdate = &CWiiController::CommonUpdate;

					return;
				}
				//	wiiリモコンは接続されてる
				else if (wiiBoard == nullptr)
				{
#ifdef _DEBUG
					MessageBox(NULL, "wiiボードの接続はされませんでした", "Message", MB_ICONWARNING);
#endif
					delete buff;

					//	リピートカウンタの初期化
					for (int count = 0; count < WC_ALL; count++)
						repeatCount[count] = 0;

					//	更新関数セット
					fpUpdate = &CWiiController::NormalUpdate;
					fpCommonUpdate = &CWiiController::CommonUpdate;


					//wiimote_sample sample;
					//bool b = wiiRemote->Load16bitMonoSampleWAV("Produce__.wav", sample);

					//wiiRemote->PlaySample(sample,0x10, FREQ_4200HZ);
					//playSound(FREQ_2760HZ, 0x10);

					return;
				}
			}
			connectTryCount++;
		}

		if (!buff->IsBalanceBoard())
		{
			//	接続状態セット
			isConnectWiimote = true;

			//	一時バッファを本体として登録
			wiiRemote = buff;

#ifdef _REMOTE_MPLUS_
			// 使用するセンサを設定（ボタン、加速度、IR、エクステンション（外部接続-ヌンチャクとか））
			wiiRemote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);
#else
			// 使用するセンサを設定（ボタン、加速度、IR）
			wiiRemote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
#endif

			//	スピーカーを有効にする
			wiiRemote->MuteSpeaker(false);
			wiiRemote->EnableSpeaker(true);

			//	LEDをとりあえず全部点灯させる
			wiiRemote->SetLEDs(0x000F);
		}
		else
		{
			//	接続状態セット
			isConnectWiiboard = true;

			//	一時バッファをバランスボードとして登録
			wiiBoard = buff;

			// 使用するセンサを設定（wiiボード）
			wiiBoard->SetReportType(wiimote::IN_BUTTONS_BALANCE_BOARD, false);

			//	初期値格納
			wiiBoard->RefreshState();
			calibrationWiiboard();
		}
	}

	//	リピートカウンタの初期化
	for (int count = 0; count < WC_ALL; count++)
		repeatCount[count] = 0;

	//	更新関数セット
	fpUpdate = &CWiiController::NormalUpdate;
	fpCommonUpdate = &CWiiController::CommonUpdate;
}
void CWiiController::startGame()
{
	//	通常の更新関数
	//--------------------------------------------------
#ifdef UPDATE_NORMAL
	fpCommonUpdate = &CWiiController::CommonUpdate;
#endif
	//--------------------------------------------------

	//	セーブ用の更新関数
	//--------------------------------------------------
#ifdef UPDATE_SAVE
	fpCommonUpdate = &CWiiController::SaveUpdate;
	saveDataNumMax = WIIMOTE_SAVE_DATA_MAX;
#endif
	//--------------------------------------------------

	//	読み込み用の更新関数
	//--------------------------------------------------
#ifdef UPDATE_READ
	saveDataNumMax = 0;
	saveDataNum = 0;
	Read();
	fpCommonUpdate = &CWiiController::ReadUpdate;
#endif
	//--------------------------------------------------
}
void CWiiController::endGame()
{
	//	通常の更新関数
	//--------------------------------------------------
#ifdef UPDATE_NORMAL
	fpCommonUpdate = &CWiiController::CommonUpdate;
#endif
	//--------------------------------------------------

	//	セーブ用の更新関数
	//--------------------------------------------------
#ifdef UPDATE_SAVE
	//	書き込み
	Save();
	fpCommonUpdate = &CWiiController::CommonUpdate;
#endif
	//--------------------------------------------------

	//	読み込み用の更新関数
	//--------------------------------------------------
#ifdef UPDATE_READ
	fpCommonUpdate = &CWiiController::CommonUpdate;
#endif
	//--------------------------------------------------
}

//=============================================================================
//	変数初期化
//=============================================================================
void CWiiController::initializeSelfWiiRemote()
{
	wiiRemote = nullptr;

	accel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	accelPrev = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	accelRaw = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	accelRawPrev = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	accelN = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	accelNPrev = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotPrev = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	rotN = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotNPrev = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	rotRaw = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotRawPrev = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	rotSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotSpeedPrev = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	rotSpeedRaw = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotSpeedRawPrev = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	joystick = D3DXVECTOR2(0.0f, 0.0f);
	joystickPrev = D3DXVECTOR2(0.0f, 0.0f);

	IR = D3DXVECTOR2(0.0f, 0.0f);
	IRPrev = D3DXVECTOR2(0.0f, 0.0f);

	IRScreen = D3DXVECTOR2(0.0f, 0.0f);
	IRScreenPrev = D3DXVECTOR2(0.0f, 0.0f);

	LEDType = LED_0;
	LEDTypePrev = LED_0;

	LEDCounter = 0;

	motionConnect = false;
	motionConnectPrev = false;

	rotSpeedCalibrationFlag = false;

	rotResetFlag = false;

	rotSpeedCalibrationCount = 0;

	updateAge = 0;
	updateAgePrev = 0;

	buttonState = 0;
	buttonStatePrev = 0;

	isConnectWiimote = false;
	isReConnectWiimote = false;

	saveDataNum = 0;
}
//=============================================================================
//	変数初期化
//=============================================================================
void CWiiController::initializeSelfWiiBoard()
{
	wiiBoard = nullptr;

	kg.BottomL = 0.0f;
	kg.BottomR = 0.0f;
	kg.TopL = 0.0f;
	kg.TopR = 0.0f;
	kg.Total = 0.0f;

	kgPrev.BottomL = 0.0f;
	kgPrev.BottomR = 0.0f;
	kgPrev.TopL = 0.0f;
	kgPrev.TopR = 0.0f;
	kgPrev.Total = 0.0f;

	calibKg.BottomL = 0.0f;
	calibKg.BottomR = 0.0f;
	calibKg.TopL = 0.0f;
	calibKg.TopR = 0.0f;
	calibKg.Total = 0.0f;

	isConnectWiiboard = false;
	isReConnectWiiboard = false;
}
//=============================================================================
//	変数初期化
//=============================================================================
void CWiiController::initializeSelf()
{
	initializeSelfWiiRemote();
	initializeSelfWiiBoard();
}
//=============================================================================
//	再接続要求
//=============================================================================
void CWiiController::reConnectWiimote()
{
	//	一時オブジェクトを生成
	wiimote* buff = new wiimote();

	//	接続要求
	if(buff->Connect())
	{
		//	wiiリモコンとして接続されれば
		if (!buff->IsBalanceBoard())
		{
			//	変数初期化
			initializeSelfWiiRemote();

			//	接続状態セット
			isConnectWiimote = true;

			//	再接続要求終了
			isReConnectWiimote = false;

			//	一時バッファを本体として登録
			wiiRemote = buff;

#ifdef _REMOTE_MPLUS_
			// 使用するセンサを設定（ボタン、加速度、IR、エクステンション（外部接続-ヌンチャクとか））
			wiiRemote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);
#else
			// 使用するセンサを設定（ボタン、加速度、IR）
			wiiRemote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
#endif

			//	スピーカーを有効にする
			wiiRemote->MuteSpeaker(false);
			wiiRemote->EnableSpeaker(true);

			//	LEDをとりあえず全部点灯させる
			wiiRemote->SetLEDs(0x000F);
		}
	}
	else
		delete buff;
}
//=============================================================================
//	再接続要求
//=============================================================================
void CWiiController::reConnectWiiboard()
{
	//	一時オブジェクトを生成
	wiimote* buff = new wiimote();

	//	接続要求
	if(buff->Connect())
	{
		//	wiiボードとして接続されれば
		if (buff->IsBalanceBoard())
		{
			//	変数初期化
			initializeSelfWiiBoard();

			//	接続状態セット
			isConnectWiiboard = true;

			//	再接続要求終了
			isReConnectWiiboard = false;

			//	一時バッファを本体として登録
			wiiBoard = buff;

			// 使用するセンサを設定（ボタン、加速度、IR、エクステンション（外部接続-ヌンチャクとか））
			wiiBoard->SetReportType(wiimote::IN_BUTTONS_BALANCE_BOARD);

			//	初期値格納
			wiiBoard->RefreshState();
			calibrationWiiboard();
		}
	}
	else
		delete buff;
}
//=============================================================================
//	デストラクタ
//=============================================================================
CWiiController::~CWiiController()
{
	//	セーブ用の更新処理で動いていたら
	if(fpCommonUpdate == &CWiiController::SaveUpdate)
	{
		//	書き込み
		Save();
	}

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
		//	切断
		wiiBoard->Disconnect();

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

void CWiiController::refreshWiiRemote()
{
	wiiRemote->RefreshState();
}

//=============================================================================
//	共通の更新処理
//=============================================================================
void CWiiController::CommonUpdate()
{
	MeasureTime("CWiiContollerUpdate");

	//	wiiリモコンが接続されていれば
	if(wiiRemote != nullptr)
	{
		//	wiiリモコンの接続が切れたら
		if(wiiRemote->IsConnected() == false || isConnectWiimote == false)
		{
			//	接続切れ
			isConnectWiimote = false;

			//	再接続要求
			isReConnectWiimote = true;

			//	オブジェクト破棄
			delete wiiRemote;
			wiiRemote = nullptr;

			//	関数終了
			return;
		}

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
#ifdef _REMOTE_MPLUS_
		motionConnect = wiiRemote->MotionPlusConnected();
		if (motionConnect == true && motionConnectPrev == false)
		{
			wiiRemote->EnableMotionPlus();
			rotResetFlag = true;
		}
#endif

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

		//PrintDebug( _T( "accel.x = %f\n" ), accel.x);
		//PrintDebug( _T( "accel.y = %f\n" ), accel.y);
		//PrintDebug( _T( "accel.z = %f\n" ), accel.z);
		//
		//PrintDebug( _T( "rot.x = %f\n" ), rot.x);
		//PrintDebug( _T( "rot.y = %f\n" ), rot.y);
		//PrintDebug( _T( "rot.z = %f\n" ), rot.z);
	}

	//	バランスwiiボード(以下、wiiボード)が接続されていれば
	if(wiiBoard != nullptr)
	{
		//	wiiボードの接続が切れたら
		if(wiiBoard->IsConnected() == false || isConnectWiiboard == false)
		{
			//	接続切れ
			isConnectWiiboard = false;

			//	再接続要求
			isReConnectWiiboard = true;

			//	オブジェクト破棄
			delete wiiBoard;
			wiiBoard = nullptr;

			//	関数終了
			return;
		}

		//	前フレームの値取得
		kgPrev = kg;

		//	wiiボードの状態を取得...というかリセット
		//	これやらないとステータスが更新されない
		wiiBoard->RefreshState();

		//	値の格納
		kg = wiiBoard->BalanceBoard.Kg;

		//PrintDebug( _T( "atRestKg.BottomL = %f\n" ),	calibKg.BottomL);
		//PrintDebug( _T( "atRestKg.BottomR = %f\n" ),	calibKg.BottomR);
		//PrintDebug( _T( "atRestKg.TopL = %f\n" ),		calibKg.TopL);
		//PrintDebug( _T( "atRestKg.TopR = %f\n" ),		calibKg.TopR);
		//PrintDebug( _T( "atRestKg.Total = %f\n" ),		calibKg.Total);

		//PrintDebug( _T( "Kg.BottomL = %f\n" ),	kg.BottomL);
		//PrintDebug( _T( "Kg.BottomR = %f\n" ),	kg.BottomR);
		//PrintDebug( _T( "Kg.TopL = %f\n" ),		kg.TopL);
		//PrintDebug( _T( "Kg.TopR = %f\n" ),		kg.TopR);
		//PrintDebug( _T( "Kg.Total = %f\n" ),	kg.Total);
	}
}
//=============================================================================
//	操作をセーブする際の更新処理
//=============================================================================
void CWiiController::SaveUpdate()
{
	//	普通に更新
	CommonUpdate();

	if(saveDataNum < WIIMOTE_SAVE_DATA_MAX)
	{
		//	セーブ用のバッファに値を詰めておく
		saveData[saveDataNum].buttonState = buttonState;

		saveData[saveDataNum].rot = rot;

		saveData[saveDataNum].accel = accel;

		saveData[saveDataNum].IRScreen = IRScreen;

		saveData[saveDataNum].kg[0] = kg.BottomL;
		saveData[saveDataNum].kg[1] = kg.BottomR;
		saveData[saveDataNum].kg[2] = kg.TopL;
		saveData[saveDataNum].kg[3] = kg.TopR;

		//	書き込み位置修正
		saveDataNum++;
	}
}
//=============================================================================
//	実際の書き込み処理
//=============================================================================
void CWiiController::Save()
{
	TCHAR fileName[100];	//	ファイル名
	FILE* fp;	//	ファイルポインタ
	char cImageNum[10];	//	読み書き用文字列
	int nImageNum = 0;	//	文字列から数字への変更

	//	ファイルからwiiリモコンセーブデータ数情報読み取り
	//-------------------------------------------------------------------------------
	fopen_s(&fp, "data/wiimoteSave/wiimoteSaveIndex.txt", "r");
	if (fp == NULL)
	{
#ifdef _DEBUG
		PrintDebugWnd("wiiリモコン用ファイルのオープン失敗");
#endif
	}

	fgets(cImageNum, 10, fp);

	fclose(fp);
	//-------------------------------------------------------------------------------

	//	ファイル名設定
	//-------------------------------------------------------------------------------
	//	文字列から数字への変換
	nImageNum = atoi(cImageNum);

	//	ファイル名保存( 識別子もここで保存 )
	sprintf_s(fileName, "data/wiimoteSave/saveData%d.bin", nImageNum);

	nImageNum++;

	//	数字から文字列への変換
	_itoa_s(nImageNum, cImageNum, 10);
	//-------------------------------------------------------------------------------

	//	wiiリモコンセーブデータ数情報書き込み
	//-------------------------------------------------------------------------------
	fopen_s(&fp, "data/wiimoteSave/wiimoteSaveIndex.txt", "w");
	if (fp == NULL)
	{
#ifdef _DEBUG
		PrintDebugWnd("wiiリモコン用ファイルのオープン失敗");
#endif
	}

	fputs(cImageNum, fp);

	fclose(fp);
	//-------------------------------------------------------------------------------

	//	データ書き込み
	//-------------------------------------------------------------------------------
	fopen_s(&fp, fileName, "wb");
	if (fp == NULL)
	{
#ifdef _DEBUG
		PrintDebugWnd("wiiリモコン用ファイルのオープン失敗");
#endif
	}

	//	セーブデータ数書き込み
	//fprintf(fp, "%d ", saveDataNum);
	fwrite(&saveDataNum, sizeof(int), 1, fp);

	for(int count = 0; count < saveDataNum;count++)
	{
		//	ボタン押下状態の書き込み
		//fprintf(fp, "%u ", saveData[count].buttonState);
		fwrite(&saveData[count].buttonState, sizeof(unsigned short), 1, fp);

		//	回転量の書き込み
		//fprintf(fp, "%f %f %f ", saveData[count].rot.x,		saveData[count].rot.y,		saveData[count].rot.z);
		fwrite(&saveData[count].rot.x, sizeof(float), 1, fp);
		fwrite(&saveData[count].rot.y, sizeof(float), 1, fp);
		fwrite(&saveData[count].rot.z, sizeof(float), 1, fp);

		//	加速度の書き込み
		//fprintf(fp, "%f %f %f ", saveData[count].accel.x,		saveData[count].accel.y,			saveData[count].accel.z);
		fwrite(&saveData[count].accel.x, sizeof(float), 1, fp);
		fwrite(&saveData[count].accel.y, sizeof(float), 1, fp);
		fwrite(&saveData[count].accel.z, sizeof(float), 1, fp);

		//	IR情報の書き込み
		//fprintf(fp, "%f %f ", saveData[count].IRScreen.x,		saveData[count].IRScreen.y);
		fwrite(&saveData[count].IRScreen.x, sizeof(float), 1, fp);
		fwrite(&saveData[count].IRScreen.y, sizeof(float), 1, fp);

		//	wiiboard情報書き込み
		fwrite(&saveData[count].kg[0], sizeof(float), 1, fp);
		fwrite(&saveData[count].kg[1], sizeof(float), 1, fp);
		fwrite(&saveData[count].kg[2], sizeof(float), 1, fp);
		fwrite(&saveData[count].kg[3], sizeof(float), 1, fp);
	}

	//	キャリブレーション値を格納
	fwrite(&calibKg.Total, sizeof(float), 1, fp);

	fclose(fp);
	//-------------------------------------------------------------------------------
}
//=============================================================================
//	操作を読み込みする際の更新処理
//=============================================================================
void CWiiController::ReadUpdate()
{
	if(saveDataNum < saveDataNumMax)
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

		//	LED点灯
		batteryLightingLED();

		//	ボタンの押下状態を保存
		buttonState = saveData[saveDataNum].buttonState;

		//	リピートカウントの更新
		for (int count = 0; count < WC_BUTTON_MAX; count++)
		{
			if (buttonState & BUTTON_STATE_BITS[count])
				(repeatCount[count] < REPEAT_COUNT_MAX) ? repeatCount[count]++ : repeatCount[count] = REPEAT_COUNT_MAX;
			else
				repeatCount[count] = 0;
		}

		//	加速度を保存
		accel = D3DXVECTOR3(saveData[saveDataNum].accel.x, saveData[saveDataNum].accel.y, saveData[saveDataNum].accel.z);

		//	回転角を保存（本体のみ）
		rot = D3DXVECTOR3(saveData[saveDataNum].rot.x, saveData[saveDataNum].rot.y, saveData[saveDataNum].rot.z);

		//	スクリーン座標系計算
		IRScreen.x = saveData[saveDataNum].IRScreen.x;
		IRScreen.y = saveData[saveDataNum].IRScreen.y;

		//PrintDebug( _T( "accel.x = %f\n" ), accel.x);
		//PrintDebug( _T( "accel.y = %f\n" ), accel.y);
		//PrintDebug( _T( "accel.z = %f\n" ), accel.z);
		//
		//PrintDebug( _T( "rot.x = %f\n" ), rot.x);
		//PrintDebug( _T( "rot.y = %f\n" ), rot.y);
		//PrintDebug( _T( "rot.z = %f\n" ), rot.z);

		//	前フレームの値取得
		kgPrev = kg;

		//	値の格納
		kg.BottomL = saveData[saveDataNum].kg[0];
		kg.BottomR = saveData[saveDataNum].kg[1];
		kg.TopL = saveData[saveDataNum].kg[2];
		kg.TopR = saveData[saveDataNum].kg[3];
		kg.Total = kg.BottomL + kg.BottomR + kg.TopL + kg.TopR;
	}
	else
	{
		if(wiiBoard != nullptr)
		{
			//	wiiボードの状態を取得...というかリセット
			//	これやらないとステータスが更新されない
			wiiBoard->RefreshState();
			wiiBoard->CalibrateAtRest();calibKg = wiiBoard->BalanceBoard.AtRestKg;
		}

		fpCommonUpdate = &CWiiController::CommonUpdate;
		CommonUpdate();
	}

	saveDataNum++;
}
//=============================================================================
//	実際の読み込み処理
//=============================================================================
void CWiiController::Read()
{
	FILE* fp;	//	ファイルポインタ

	//	データ読み込み
	//-------------------------------------------------------------------------------
	fopen_s(&fp, "data/wiimoteSave/wiimoteSave1.bin", "rb");

	if (fp == NULL)
	{
#ifdef _DEBUG
		PrintDebugWnd("データないお？");
#endif
	}


	//	セーブデータ数読み込み
	//fscanf_s(fp, "%d", &saveDataNumMax);
	fread_s(&saveDataNumMax, sizeof(int), sizeof(int), 1, fp);

	for(int count = 0; count < saveDataNumMax;count++)
	{
		//	ボタン押下状態の書き込み
		//fscanf_s(fp, "%u", &saveData[count].buttonState);
		fread_s(&saveData[count].buttonState, sizeof(unsigned short), sizeof(unsigned short), 1, fp);

		//	回転量の書き込み
		//fscanf_s(fp, "%f %f %f", &saveData[count].rot.x,		&saveData[count].rot.y,		&saveData[count].rot.z);
		fread_s(&saveData[count].rot.x, sizeof(float), sizeof(float), 1, fp);
		fread_s(&saveData[count].rot.y, sizeof(float), sizeof(float), 1, fp);
		fread_s(&saveData[count].rot.z, sizeof(float), sizeof(float), 1, fp);

		//	加速度の書き込み
		//fscanf_s(fp, "%f %f %f", &saveData[count].accel.x,		&saveData[count].accel.y,		&saveData[count].accel.z);
		fread_s(&saveData[count].accel.x, sizeof(float), sizeof(float), 1, fp);
		fread_s(&saveData[count].accel.y, sizeof(float), sizeof(float), 1, fp);
		fread_s(&saveData[count].accel.z, sizeof(float), sizeof(float), 1, fp);

		//	IR情報の書き込み
		//fscanf_s(fp, "%f %f", &saveData[count].IRScreen.x,		&saveData[count].IRScreen.y);
		fread_s(&saveData[count].IRScreen.x, sizeof(float), sizeof(float), 1, fp);
		fread_s(&saveData[count].IRScreen.y, sizeof(float), sizeof(float), 1, fp);

		//	wiiboard情報読み込み
		fread_s(&saveData[count].kg[0], sizeof(float), sizeof(float), 1, fp);
		fread_s(&saveData[count].kg[1], sizeof(float), sizeof(float), 1, fp);
		fread_s(&saveData[count].kg[2], sizeof(float), sizeof(float), 1, fp);
		fread_s(&saveData[count].kg[3], sizeof(float), sizeof(float), 1, fp);
	}

	//	キャリブレーション値の読み込み
	fread_s(&calibKg.Total, sizeof(int), sizeof(int), 1, fp);


	fclose(fp);
}
//=============================================================================
//	更新処理
//=============================================================================
void CWiiController::update()
{
	(this->*fpCommonUpdate)();
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
	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_ONE]) && (buttonState & BUTTON_STATE_BITS[WC_ONE]))
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

	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_ONE]) && (buttonState & BUTTON_STATE_BITS[WC_ONE]))
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

	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_ONE]) && (buttonState & BUTTON_STATE_BITS[WC_ONE]))
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

	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_ONE]) && (buttonState & BUTTON_STATE_BITS[WC_ONE]))
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

	if (!(buttonStatePrev & BUTTON_STATE_BITS[WC_ONE]) && (buttonState & BUTTON_STATE_BITS[WC_ONE]))
	{
		//	更新関数セット
		fpUpdate = &CWiiController::NormalUpdate;
		rumble(false);
		mode5Count = 0;
	}
}
void CWiiController::calibrationWiiboard()
{
#ifndef UPDATE_READ
	if(wiiBoard != nullptr)
	{
		wiiBoard->CalibrateAtRest();calibKg = wiiBoard->BalanceBoard.AtRestKg;
	}
#endif
}
//-----------------------------------EOF---------------------------------------