//==============================================================================
//
// File   : SceneGame.cpp
// Brief  : ゲームシーンクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "SceneGame.h"
#include "../framework/camera/CameraObject.h"
#include "../framework/render/RenderMatrix.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/develop/DebugMeasure.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/VirtualController.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/light/LightDirection.h"
#include "../framework/light/ManagerLight.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/ManagerMotion.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/ManagerUpdate.h"
#include "../framework/system/Window.h"
#include "../system/EffectParameter.h"
#include "../system/point/ManagerPoint.h"
#include "../system/ManagerFireworks.h"
#include "../system/ManagerTarget.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"
#include "../system/fire/Fire.h"
#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectModelMaterial.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectSky.h"
#include "../object/ObjectBillboard.h"
#include "../object/ObjectScore.h"
#include "../object/ObjectSkinMesh.h"
#include "../object/ObjectWaterwheel.h"
#include "../system/gage/gage.h"
#include "../system/player/Player.h"

#include "../framework/system/ManagerDraw.h"
#include "../graphic/graphic/GraphicPoint.h"
#include "../framework/polygon/PolygonPoint.h"

#include "../framework/radianTable/radianTable.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define RANDOM(value) (float)((rand() % value) - (rand() % value))
#define SQUARE(_value) (_value * _value)

//******************************************************************************
// 静的変数
//******************************************************************************
//	点滅用カウント数
static const int flashingCountHirf = 20;
static const int flashingCountMax = 40;

//	○○　文字のサイズ
static const float stringXX_NormalSizeX = 400.0f;
static const float stringXX_NormalSizeY = 120.0f;

//	透明値加算値
static const float addFlashingAlpha = 0.02f;

//	打ち上げ間隔
static const int launchCountMax = 20;

//	花火同士の当たり判定時に、どの程度近づいたら当たりとするか
static const float fire_fire_collisionSize = 5.0f;

static const float targetAppearPosZ = 400.0f;

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
SceneGame::SceneGame( void ) : SceneMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
SceneGame::~SceneGame( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : SceneGame* pOut						: コピー先アドレス
//==============================================================================
int SceneGame::Copy( SceneGame* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = SceneMain::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::Update( void )
{
	// テスト
	PrintDebug( _T( "ゲームシーン\n" ) );

#ifdef _DEVELOP
	// 更新関数の変更
	if( pArgument_->pKeyboard_->IsTrigger( DIK_F5 ) )
	{
		timerSceneGame_ = -1;
		fpUpdate = &SceneGame::UpdateTestCamera;
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_F6 ) )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::UpdatePreviousResult;
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_F7 ) )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::UpdateBetweenSection;
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_F8 ) )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::normalUpdate;
	}
#endif

	// 焦点距離の更新
	D3DXVECTOR3	positionLookAt;		// 注視点
	pCamera_->GetPositionLookAt( &positionLookAt );
	pArgument_->pEffectParameter_->SetForcus( pCamera_->GetViewZ( positionLookAt ) );

	//	設定された更新関数へ
	(this->*fpUpdate)();
}

//==============================================================================
// Brief  : calibration更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::calibrationUpdate(void)
{
	PrintDebug( _T( "calibrationUpdate\n" ) );

	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;


	if(pArgument_->pVirtualController_->IsTrigger(VC_GAME_START))
	{
		pArgument_->pWiiController_->rotReset();
		pArgument_->pWiiController_->calibrationWiiboard();

		calibrationWiimote->SetEnableGraphic(false);

		fpUpdate = &SceneGame::normalUpdate;
	}
}

//==============================================================================
// Brief  : プレイヤーの移動処理
//==============================================================================
void SceneGame::MovePlayer()
{
	//	wiiボードを利用した、プレイヤーの移動処理1
	//---------------------------------------------------------------------------------------------------------
#ifdef _WIIBOARD
	if(pArgument_->pWiiController_->getIsConnectWiiboard())
	{
		float totalCalibKg = pArgument_->pWiiController_->getCalibKg().Total * 0.7f;
		float totalKgR = pArgument_->pWiiController_->getKg().BottomR + pArgument_->pWiiController_->getKg().TopR;
		float totalKgL = pArgument_->pWiiController_->getKg().BottomL + pArgument_->pWiiController_->getKg().TopL;
		if(totalKgL
			>=
			totalCalibKg)
		{
			player->addSpeed((-((totalKgL - totalCalibKg) / pArgument_->pWiiController_->getCalibKg().Total)) * 2.0f);
		}
		if(totalKgR
			>=
			totalCalibKg)
		{
			player->addSpeed((((totalKgR - totalCalibKg) / pArgument_->pWiiController_->getCalibKg().Total)) * 2.0f);
		}
	}
#endif

	if(pArgument_->pKeyboard_->IsPress(DIK_LEFT) == true)
	{
		player->AddPositionX(-1.0f);
	}
	if(pArgument_->pKeyboard_->IsPress(DIK_RIGHT) == true)
	{
		player->AddPositionX(1.0f);
	}

	D3DXVECTOR3 buff = player->getPosition();
	PrintDebug( _T( "\nplayerPos.x = %f\n"), buff.x );
	//---------------------------------------------------------------------------------------------------------


	//	プレイヤー腕オブジェクトに回転量をセット
	D3DXVECTOR3 buffRot = pArgument_->pWiiController_->getRot();
	player->setRotationArm(DEG_TO_RAD(buffRot.x), DEG_TO_RAD(-buffRot.y), DEG_TO_RAD(buffRot.z));
}
//==============================================================================
// Brief  : 花火打ち上げ処理
//==============================================================================
void SceneGame::LaunchFireworks()
{
	if(launchFlag == false)
	{
		//	Bボタンを離した時の
		if(pArgument_->pWiiController_->getAccelerationY() >= 1.0f &&
			pArgument_->pWiiController_->getRelease(WC_B))
		{
			buffWiiAccel = pArgument_->pWiiController_->getAcceleration();
			buffWiiRot = pArgument_->pWiiController_->getRot();

			int buff;
			D3DXVECTOR3 buffPos = player->getPosition();

			if(buffWiiAccel.x <= 0.0f)
			{
				//	rotは90度で真っ直ぐ飛ぶ
				//	rotSpeedがマイナス値なら右側に曲がる
				//	rotSpeedが　プラス値なら左側に曲がる
				buff = managerFireworks->Add(
					ManagerFireworks::STATE_RIGHT,
					managerPoint,
					buffPos,
					D3DXVECTOR3(3.0f, 1.0f, 0.0f),
					90.0f,
					buffWiiAccel.x * 0.3f
					);
			}
			else
			{
				buff = managerFireworks->Add(
					ManagerFireworks::STATE_LEFT,
					managerPoint,
					buffPos,
					D3DXVECTOR3(3.0f, 1.0f, 0.0f),
					90.0f,
					buffWiiAccel.x * 0.5f
					);
			}


			if(buff != -1)
			{
				fireworksTable[fireworksTableIndex] = buff;
				fireworksTableIndex++;
			}

			launchFlag = true;
		}
	}
	else
	{
		launchCount++;
		if(launchCount >= launchCountMax)
		{
			launchCount = 0;
			launchFlag = false;
		}
	}

//#ifdef _DEBUG
	if(pArgument_->pKeyboard_->IsTrigger(DIK_RIGHT))
	{
		int buff;
		D3DXVECTOR3 buffPos = player->getPosition();

		buff = managerFireworks->Add(
					ManagerFireworks::STATE_RIGHT,
					managerPoint,
					buffPos,
					D3DXVECTOR3(3.0, 1.0f, 0.0f),
					90.0f,
					-0.5f
					);

		if(buff != -1)
		{
			fireworksTable[fireworksTableIndex] = buff;
			fireworksTableIndex++;
		}
	}

	if(pArgument_->pKeyboard_->IsTrigger(DIK_LEFT))
	{
		int buff;
		D3DXVECTOR3 buffPos = player->getPosition();

		buff = managerFireworks->Add(
					ManagerFireworks::STATE_LEFT,
					managerPoint,
					buffPos,
					D3DXVECTOR3(3.0, 1.0f, 0.0f),
					90.0f,
					0.5f
					);

		if(buff != -1)
		{
			fireworksTable[fireworksTableIndex] = buff;
			fireworksTableIndex++;
		}
	}

	if(pArgument_->pKeyboard_->IsTrigger(DIK_UP) ||
		pArgument_->pWiiController_->getTrigger(WC_ONE))
	{
		int buff;
		D3DXVECTOR3 buffPos = player->getPosition();
		buffPos.x += 250.0f;
		buffPos.y += 30.0f;

		buff = managerFireworks->Add(
					ManagerFireworks::STATE_LEFT,
					managerPoint,
					buffPos,
					D3DXVECTOR3(3.0, 1.0f, 0.0f),
					90.0f,
					2.0f
					);

		if(buff != -1)
		{
			fireworksTable[fireworksTableIndex] = buff;
			fireworksTableIndex++;
		}



		buffPos = player->getPosition();
		buffPos.x -= 250.0f;
		buffPos.y += 30.0f;

		buff = managerFireworks->Add(
					ManagerFireworks::STATE_RIGHT,
					managerPoint,
					buffPos,
					D3DXVECTOR3(3.0, 1.0f, 0.0f),
					90.0f,
					-2.0f
					);

		if(buff != -1)
		{
			fireworksTable[fireworksTableIndex] = buff;
			fireworksTableIndex++;
		}
	}
//#endif
}
//==============================================================================
// Brief  : 通常更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::normalUpdate(void)
{
	PrintDebug( _T( "normalUpdate\n" ) );

	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;


	//	カメラの逆行列を取得する
	D3DXMATRIX cameraInvMat;
	pCamera_->GetRenderMatrix()->GetMatrixView(&cameraInvMat);
	D3DXMatrixInverse(&cameraInvMat, nullptr, &cameraInvMat);

	//	カメラの逆行列をプレイヤーにセット
	player->setInvViewMatrix(cameraInvMat);


	{
		//	花火管理クラスの更新
		//MeasureTime("managerFireworksUpdate");
		managerFireworks->setInvViewMatrix(cameraInvMat);
		managerFireworks->Update(fireworksTable, &fireworksTableIndex);
	}
	//	ターゲットクラスの更新
	managerTarget->setInvViewMatrix(cameraInvMat);
	managerTarget->Update(targetTable, &targetTableIndex);
	{
		// ポイントスプライト管理クラスの更新
		MeasureTime("managerPoint");
		managerPoint->Update();
	}

	//	プレイヤー移動処理
	MovePlayer();

	//	花火打ち上げ処理
	LaunchFireworks();





	//	テスト用ここから
	//---------------------------------------------------------------------------------------------------------
	PrintDebug( _T( "\nbuffWiiAccel.x = %f\n"), buffWiiAccel.x );
	PrintDebug( _T( "\nbuffWiiAccel.y = %f\n"), buffWiiAccel.y );
	PrintDebug( _T( "\nbuffWiiAccel.z = %f\n"), buffWiiAccel.z );
	PrintDebug( _T( "\nbuffWiiRot.x = %f\n"), buffWiiRot.x );
	PrintDebug( _T( "\nbuffWiiRot.y = %f\n"), buffWiiRot.y );
	PrintDebug( _T( "\nbuffWiiRot.z = %f\n"), buffWiiRot.z );

	//	ターゲット出現
	//targetAppearCount++;
	//if(targetAppearCount == 50)
	//{
	//	int buff;
	//	buff = managerTarget->Add(
	//		D3DXVECTOR3(RANDOM(500), (float)(rand() % 100), targetAppearPosZ)
	//		);
	//	if(buff != -1)
	//	{
	//		targetTable[targetTableIndex] = buff;
	//		targetTableIndex++;
	//	}
	//
	//	targetAppearCount = 0;
	//}
	//---------------------------------------------------------------------------------------------------------
	//	テスト用ここまで




	//	wiiリモコンの回転初期化
	if(pArgument_->pWiiController_->getPress(WC_PLUS) && pArgument_->pWiiController_->getPress(WC_MINUS))
		pArgument_->pWiiController_->rotReset();

	//	Aボタン押されたら
	if(pArgument_->pVirtualController_->IsTrigger(VC_BURN) == true)
	{
		//	ターゲットと花火の当たり判定
		collision_fireworks_target();
	}
	//	花火と花火の当たり判定
	collision_fireworks_fireworks();


	//	ポーズキーが押されたら
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE))
	{
		//	更新関数設定
		fpUpdate = &SceneGame::pauseUpdate;

		//	Objectの更新を止める
		pArgument_->pUpdate_->SetIsEnable( false );

		//	描画再開
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);

		if(finger != nullptr)
			finger->SetEnableGraphic(true);
	}
}
//==============================================================================
// Brief  : ポーズ更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::pauseUpdate(void)
{
	PrintDebug( _T( "pauseUpdate\n" ) );

	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;

	//	wiiリモコンが生成されていれば指の移動
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();
		finger->SetPosition(IRBuff.x, IRBuff.y, 0.0f);
	}

	//	１フレーム前の登録オブジェクトを保存
	chooseObjectPrev = chooseObject;


	//	決定キー押されたら
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	選択されている場合
		if(chooseObject != nullptr)
		{
			//	点滅カウント初期化
			pushChooseObjectFlashingCount = 0;

			//	現在のオブジェクトをA1.0fで表示
			chooseObject->SetColorA(1.0f);

			//	再開が押されたら
			if(chooseObject == stringReturn)
			{
				//	更新関数設定
				fpUpdate = &SceneGame::normalUpdate;

				//	Objectの更新を再開
				pArgument_->pUpdate_->SetIsEnable( true );

				//	描画停止
				pauseFrame->SetEnableGraphic(false);
				stringReturn->SetEnableGraphic(false);
				stringStop->SetEnableGraphic(false);
				stringRetry->SetEnableGraphic(false);

				if(finger != nullptr)
					finger->SetEnableGraphic(false);
			}
			else
			{
				//	更新関数設定
				fpUpdate = &SceneGame::pauseFadeUpdate;

				if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
				{
					pArgument_->pFade_->FadeOut( 20 );
					pArgument_->pUpdate_->SetIsEnable( true );
				}
			}
		}
	}


	//	矢印キーで移動
	if(pArgument_->pVirtualController_->IsTrigger(VC_UP))
	{
		//	点滅カウント初期化
		pushChooseObjectFlashingCount = 0;

		//	wiiリモコン接続時は違う処理
		if(chooseObject == nullptr)
		{
			//	方向キーに変更
			chooseFlag = false;

			//	オブジェクト登録
			chooseObject = stringReturn;
		}
		else
		{
			//	現在のオブジェクトをA1.0fで表示
			chooseObject->SetColorA(1.0f);

			//	選択肢移動
			if(chooseObject == stringReturn)
				chooseObject = stringRetry;
			else if(chooseObject == stringRetry)
				chooseObject = stringStop;
			else
				chooseObject = stringReturn;
		}
	}
	if(pArgument_->pVirtualController_->IsTrigger(VC_DOWN))
	{
		//	点滅カウント初期化
		pushChooseObjectFlashingCount = 0;

		//	wiiリモコン接続時は違う処理
		if(chooseObject == nullptr)
		{
			//	方向キーに変更
			chooseFlag = false;

			//	オブジェクト登録
			chooseObject = stringRetry;
		}
		else
		{
			//	現在のオブジェクトをA1.0fで表示
			chooseObject->SetColorA(1.0f);

			//	選択肢移動
			if(chooseObject == stringReturn)
				chooseObject = stringStop;
			else if(chooseObject == stringStop)
				chooseObject = stringRetry;
			else
				chooseObject = stringReturn;
		}
	}


	//	wiiリモコンが生成されていれば指の移動
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();

		//	「再開」に当たってれば
		if((IRBuff.x <= (stringReturn->GetPositionX() + (stringReturn->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringReturn->GetPositionX() - (stringReturn->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringReturn->GetPositionY() + (stringReturn->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringReturn->GetPositionY() - (stringReturn->GetScaleY() * 0.5f))) )
		{
			//	点滅オブジェクトとして登録
			chooseObject = stringReturn;

			//	選択方法をIRに変更
			chooseFlag = true;
		}
		//	「中止」に当たってれば
		else if((IRBuff.x <= (stringStop->GetPositionX() + (stringStop->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringStop->GetPositionX() - (stringStop->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringStop->GetPositionY() + (stringStop->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringStop->GetPositionY() - (stringStop->GetScaleY() * 0.5f))) )
		{
			//	点滅オブジェクトとして登録
			chooseObject = stringStop;

			//	選択方法をIRに変更
			chooseFlag = true;
		}
		//	「初めから」に当たってれば
		else if((IRBuff.x <= (stringRetry->GetPositionX() + (stringRetry->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringRetry->GetPositionX() - (stringRetry->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringRetry->GetPositionY() + (stringRetry->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringRetry->GetPositionY() - (stringRetry->GetScaleY() * 0.5f))) )
		{
			//	点滅オブジェクトとして登録
			chooseObject = stringRetry;

			//	選択方法をIRに変更
			chooseFlag = true;
		}
		//	何にも当たってなければ
		else
		{
			//	選択方法がIRの場合のみ
			if(chooseFlag == true)
			{
				if(chooseObject != nullptr)
				{
					//	登録解除
					chooseObject->SetColorA(1.0f);
					chooseObject = nullptr;
					pushChooseObjectFlashingCount = 0;
				}
			}
		}
	}


	//	PAUSEキーが押されたら
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE))
	{
		//	更新関数設定
		fpUpdate = &SceneGame::normalUpdate;

		//	Objectの更新を再開
		pArgument_->pUpdate_->SetIsEnable( true );

		//	描画停止
		pauseFrame->SetEnableGraphic(false);
		stringReturn->SetEnableGraphic(false);
		stringStop->SetEnableGraphic(false);
		stringRetry->SetEnableGraphic(false);

		if(finger != nullptr)
			finger->SetEnableGraphic(false);
	}


	//	選択項目の点滅処理
	if(chooseObject != nullptr)
	{
		chooseObject->SetScaleX(stringXX_NormalSizeX * 1.3f);
		chooseObject->SetScaleY(stringXX_NormalSizeY * 1.3f);

		pushChooseObjectFlashingCount++;

		if(pushChooseObjectFlashingCount <= flashingCountHirf)
			chooseObject->AddColorA(-addFlashingAlpha);
		else if(pushChooseObjectFlashingCount <= flashingCountMax)
			chooseObject->AddColorA(addFlashingAlpha);
		else
			pushChooseObjectFlashingCount = 0;

		//	１フレーム前の選択オブジェクトのサイズを変更
		if((chooseObjectPrev != nullptr) &&
			(chooseObjectPrev != chooseObject))
		{
			chooseObjectPrev->SetScaleX(stringXX_NormalSizeX);
			chooseObjectPrev->SetScaleY(stringXX_NormalSizeY);
		}
	}
	else
	{
		stringReturn->SetScaleX(stringXX_NormalSizeX);
		stringReturn->SetScaleY(stringXX_NormalSizeY);

		stringStop->SetScaleX(stringXX_NormalSizeX);
		stringStop->SetScaleY(stringXX_NormalSizeY);

		stringRetry->SetScaleX(stringXX_NormalSizeX);
		stringRetry->SetScaleY(stringXX_NormalSizeY);
	}



	//	Objectクラスの更新が止まってるから、ここで更新処理
	if(finger != nullptr)
		finger->Update();

	stringRetry->Update();
	stringReturn->Update();
	stringStop->Update();
}
//==============================================================================
// Brief  : ポーズ更新処理(フェード用)
//==============================================================================
void SceneGame::pauseFadeUpdate(void)
{
	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;

	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		if(chooseObject == stringStop)
			SetSceneNext( ManagerSceneMain::TYPE_TITLE );
		else
			SetSceneNext( ManagerSceneMain::TYPE_GAME );

		SetIsEnd( true );
	}
}
//==============================================================================
// Brief  : 再接続要求時用の更新処理
//==============================================================================
void SceneGame::reConnectWiimoteUpdate(void)
{
	//	再接続要求
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		pArgument_->pWiiController_->reConnectWiimote();

	//	wiiリモコンが再接続が終了したら
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == false)
	{
		//	更新関数設定
		fpUpdate = &SceneGame::pauseUpdate;

		//	Objectの更新を止める
		pArgument_->pUpdate_->SetIsEnable( false );

		//	描画やめる
		reConnectWiimote->SetEnableGraphic(false);

		//	描画再開
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);
		finger->SetEnableGraphic(true);
	}

	//	Objectクラスの更新が止まってるから、ここで更新処理
	reConnectWiimote->Update();
}
//==============================================================================
// Brief  : 再接続要求時用の更新処理
//==============================================================================
void SceneGame::reConnectWiiboardUpdate(void)
{
	//	再接続要求
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		pArgument_->pWiiController_->reConnectWiiboard();

	//	wiiリモコンが再接続が終了したら
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == false)
	{
		//	更新関数設定
		fpUpdate = &SceneGame::pauseUpdate;

		//	Objectの更新を止める
		pArgument_->pUpdate_->SetIsEnable( false );

		//	描画やめる
		reConnectWiiboard->SetEnableGraphic(false);

		//	描画再開
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);
		finger->SetEnableGraphic(true);
	}

	//	Objectクラスの更新が止まってるから、ここで更新処理
	reConnectWiiboard->Update();
}
//==============================================================================
// Brief  : wiiリモコンのロストチェック処理
// Return : bool								: true = 問題無し false = ロスト
// Arg    : void								: なし
//==============================================================================
bool SceneGame::wiiLostCheck(void)
{
	//	wiiリモコンが再接続要求をした場合
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == true)
	{
		//	更新関数設定
		fpUpdate = &SceneGame::reConnectWiimoteUpdate;

		//	再接続要求オブジェクト可視化
		reConnectWiimote->SetEnableGraphic(true);

		//	Objectの更新を止める
		pArgument_->pUpdate_->SetIsEnable( false );

		return false;
	}

	//	wiiボードが再接続要求をした場合
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == true)
	{
		//	更新関数設定
		fpUpdate = &SceneGame::reConnectWiiboardUpdate;

		//	再接続要求オブジェクト可視化
		reConnectWiiboard->SetEnableGraphic(true);

		//	Objectの更新を止める
		pArgument_->pUpdate_->SetIsEnable( false );

		return false;
	}

	return true;
}
//==============================================================================
// Brief  : 花火とターゲットの当たり判定処理
//==============================================================================
void SceneGame::collision_fireworks_target()
{
	float hitPosLength = 0.0f;

	//	存在する花火の数分ループ
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	花火の情報取得
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		//	花火の位置情報取得
		D3DXVECTOR3 buffFireworksPos = buffFireworks->getPosition();

		//	存在するターゲットの数分ループ
		for(int targetCount = 0;targetCount < targetTableIndex;targetCount++)
		{
			//	ターゲットの位置情報取得
			Target* buffTarget = managerTarget->getTarget(targetTable[targetCount]);
			D3DXVECTOR3 buffTargetPos = buffTarget->getPosition();

			//	ターゲットのサイズ取得
			float buffTargetSize = (managerTarget->getTarget(targetCount)->getScale() * 0.5f);

			//	当たり判定
			if(hitCheckPointCircle(buffFireworksPos, buffTargetPos, buffTargetSize, &hitPosLength) == true)
			{
				//	破裂
				int returnValue = buffFireworks->burn(buffTargetSize * buffTargetSize, hitPosLength);

				AddGage((ADD_SCORE_STATE)returnValue);

				//	ターゲット消去
				buffTarget->Dissappear();

				//	次の花火との当たり判定へ移行
				break;
			}
		}
	}

	/*for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	花火の情報取得
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		//	破裂
		buffFireworks->burn(0.0f, 0.0f);
	}*/
}
//==============================================================================
// Brief  : 花火と花火の当たり判定処理
//==============================================================================
void SceneGame::collision_fireworks_fireworks()
{
	float hitPosLength = 0.0f;

	//	存在する花火の数分ループ
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	花火の情報取得
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		//	花火の位置情報取得
		D3DXVECTOR3 buffFireworksPos = buffFireworks->getPosition();

		//	存在する花火の数＋１〜最大数分ループ
		for(int fireworksCount2 = fireworksCount + 1;fireworksCount2 < fireworksTableIndex;fireworksCount2++)
		{
			Fireworks* buffFireworks2 = managerFireworks->getFireworks(fireworksTable[fireworksCount2]);
			if(buffFireworks2->IsBurnFlag())
				continue;

			//	花火の位置情報取得
			D3DXVECTOR3 buffFireworksPos2 = buffFireworks2->getPosition();
			
			float hitPosLength;

			//	当たり判定
			if(hitCheckPointCircle(buffFireworksPos, buffFireworksPos2, fire_fire_collisionSize, &hitPosLength) == true)
			{
				//	破裂
				buffFireworks->burn2();
				buffFireworks2->burn2();

				AddGage(ADD_20);

				//	次の花火との当たり判定へ移行
				break;
			}
		}
	}
}
//==============================================================================
// Brief  : 点と円の当たり判定処理
// Return : bool								: 当たったか当たってないか
// Arg    : D3DXVECTOR3							: 点の位置
// Arg    : D3DXVECTOR3							: 円の位置
// Arg    : D3DXVECTOR3							: 当たってると判定する最大距離
// Arg    : float								: 円の中心から点への距離
//==============================================================================
bool SceneGame::hitCheckPointCircle(D3DXVECTOR3 _pointPos, D3DXVECTOR3 _circlePos, float _hitCheckOffset, float* _hitPosLength)
{
	//	位置関係計算
	float lengthX = _pointPos.x - _circlePos.x;
	float lengthY = _pointPos.y - _circlePos.y;

	float returnLength = SQUARE(lengthX) + SQUARE(lengthY);

	//	判定
	if(returnLength <= (_hitCheckOffset * _hitCheckOffset))
	{
		//	どのくらい離れたかを保存
		*_hitPosLength = returnLength;

		return true;
	}

	return false;
}
//==============================================================================
// Brief  : シンクロゲージの加算処理処理
//==============================================================================
void SceneGame::AddGage(ADD_SCORE_STATE _state)
{
	switch(_state)
	{
	case ADD_1:
		gage->addPercentFuture(1.0f);

		break;

	case ADD_5:
		gage->addPercentFuture(5.0f);

		break;

	case ADD_10:
		gage->addPercentFuture(10.0f);

		break;

	case ADD_20:
		gage->addPercentFuture(20.0f);

		break;
	}
}

