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
#include "../framework/light/LightPoint.h"
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
#include "../system/combo/combo.h"
#include "../system/player/Player.h"
#include "../framework/resource/ManagerSound.h"
#include "../framework/resource/Sound.h"

#include "../framework/system/ManagerDraw.h"
#include "../graphic/graphic/GraphicPoint.h"
#include "../framework/polygon/PolygonPoint.h"

#include "../framework/radianTable/radianTable.h"

#include "../system/fireworksUI/fireworksUI.h"
#include "../system/fireworks/fireworks.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define RANDOM(value) (float)((rand() % value) - (rand() % value))
#define SQUARE(_value) (_value * _value)
#define AUTO_SYNCRO_FIREWORKS (5)

//#define _WIIBOARD
#define FIRE_AUTO
//#define FIRE_MANUAL

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

	synchronizeFlag = false;

#ifdef _TEST
	autoLaunchCount = 0;
	autoLaunchTarget = 0;
	autoLaunchFlag = false;
#endif
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
	//PrintDebug( _T( "ゲームシーン\n" ) );

#ifdef _DEVELOP
	// 更新関数の変更
	if( pArgument_->pKeyboard_->IsTrigger( DIK_F5 ) )
	{
		timerSceneGame_ = -1;
		fpUpdate = &SceneGame::UpdateTest;
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_F6 ) )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::UpdateCountDownGame;
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
	if( fpUpdate == &SceneGame::normalUpdate || fpUpdate == &SceneGame::demoUpdate )
	{
		D3DXVECTOR3	pTablePositionForcus[] =
		{
			D3DXVECTOR3( 620.0f, 0.0f, 4550.0f ),
			D3DXVECTOR3( -1505.0f, 0.0f, 625.0f ),
			D3DXVECTOR3( 1680.0f, 0.0f, 600.0f ),
			D3DXVECTOR3( 5400.0f, 0.0f, -380.0f )
		};
		pArgument_->pEffectParameter_->SetForcus( pCamera_->GetViewZ( pTablePositionForcus[ indexSection_ ] ) );
	}
	else
	{
		pArgument_->pEffectParameter_->SetForcus( 0.5f * pCamera_->GetViewZ( positionLookAt ) );
	}

	// 影用カメラ近の更新
	D3DXVECTOR3	vectorLight;		// ライトベクトル
	positionLookAt.y = 0.0f;
	pLight_->GetVector( &vectorLight );
	vectorLight *= -3500.0f;
	pCameraShadowNear_->SetPositionCamera( positionLookAt + vectorLight );
	pCameraShadowNear_->SetPositionLookAt( positionLookAt );

	// 影用カメラ遠の更新
	pLight_->GetVector( &vectorLight );
	vectorLight *= -10000.0f;
	pCameraShadowFar_->SetPositionCamera( positionLookAt + vectorLight );
	pCameraShadowFar_->SetPositionLookAt( positionLookAt );

	// 影用カメラ点の更新
	const LightPoint*	pLightPoint = nullptr;		// 点光源
	for( int counterLightPoint = 0; counterLightPoint < GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW; ++counterLightPoint )
	{
		pLightPoint = pArgument_->pEffectParameter_->GetLightPointLightness( counterLightPoint );
		if( pLightPoint != nullptr )
		{
			D3DXVECTOR3	positionLightPointCamera;		// 点光源の視点座標
			D3DXVECTOR3	positionLightPointLookAt;		// 点光源の注視点座標
			pLightPoint->GetPosition( &positionLightPointCamera );
			positionLightPointLookAt = positionLightPointCamera;
			positionLightPointLookAt.y -= 1000.0f;
			ppCameraShadowPoint_[ counterLightPoint ]->SetPositionCamera( positionLightPointCamera );
			ppCameraShadowPoint_[ counterLightPoint ]->SetPositionLookAt( positionLightPointLookAt );
		}
	}

	//	設定された更新関数へ
	(this->*fpUpdate)();

	comboPrev = combo->getScore();

	// 最大コンボ数の更新
	if( comboPrev > maximumCombo_ )
	{
		maximumCombo_ = comboPrev;
	}
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
		wiiContoroller->rotReset();
		wiiContoroller->calibrationWiiboard();

		calibrationWiimote->SetEnableGraphic(false);
		calibrationWiimoteIllust->SetEnableGraphic(false);
		combo->setStartFlag(true);

		if(ManagerSceneMain::tutorialFlag == false)
			fpUpdate = &SceneGame::UpdateCountDownGame;
		else
			fpUpdate = &SceneGame::tutorialUpdate;
	}
}

//==============================================================================
// Brief  : プレイヤーの移動処理
//==============================================================================
void SceneGame::MovePlayer()
{
	//	wiiボードを利用した、プレイヤーの移動処理1
	//---------------------------------------------------------------------------------------------------------
	if(wiiContoroller->getIsConnectWiiboard() == true)
	{
		float totalCalibKg = wiiContoroller->getCalibKg().Total * 0.7f;
		float totalKgR = wiiContoroller->getKg().BottomR + wiiContoroller->getKg().TopR;
		float totalKgL = wiiContoroller->getKg().BottomL + wiiContoroller->getKg().TopL;
		if(totalKgL
			>=
			totalCalibKg)
		{
			player->addSpeed((-((totalKgL - totalCalibKg) / wiiContoroller->getCalibKg().Total)) * 2.0f);
		}
		if(totalKgR
			>=
			totalCalibKg)
		{
			player->addSpeed((((totalKgR - totalCalibKg) / wiiContoroller->getCalibKg().Total)) * 2.0f);
		}

		if(pArgument_->pKeyboard_->IsPress(DIK_LEFT) == true)
		{
			player->AddPositionX(-1.0f);
		}
		if(pArgument_->pKeyboard_->IsPress(DIK_RIGHT) == true)
		{
			player->AddPositionX(1.0f);
		}
	}

	//	プレイヤー腕オブジェクトに回転量をセット
	//D3DXVECTOR3 buff = player->getPosition();
	//D3DXVECTOR3 buffRot = wiiContoroller->getRot();
	//player->setRotationArm(DEG_TO_RAD(buffRot.x), DEG_TO_RAD(-buffRot.y), DEG_TO_RAD(buffRot.z));
}
//==============================================================================
// Brief  : 花火打ち上げ処理
//==============================================================================
void SceneGame::LaunchFireworks()
{
	if(launchFlag == false)
	{
		if(fabsf(wiiContoroller->getAccelerationY()) >= 1.0f && wiiContoroller->getRelease(WC_B))
		{
			Launch();
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
}
void SceneGame::Launch()
{
	buffDiffWiiAccel = wiiContoroller->getAcceleration() - wiiContoroller->getAccelerationPrev();
	buffDiffWiiRot = wiiContoroller->getRot() - wiiContoroller->getRotPrev();

	if(buffDiffWiiRot.z > 90.0f)
		buffDiffWiiRot.z = 360.0f - buffDiffWiiRot.z;
	if(buffDiffWiiRot.z < -90.0f)
		buffDiffWiiRot.z = -(360.0f - buffDiffWiiRot.z);


	int buff = -1;
	D3DXVECTOR3 buffPos = player->getPosition();

	buff = managerFireworks->Add(
			ManagerFireworks::STATE_RIGHTSP,
			managerPoint,
			buffPos,
			buffDiffWiiRot,
			colorState);

	if(buff != -1)
	{
		fireworksTable[fireworksTableIndex] = buff;
		fireworksTableIndex++;
	}

	launchFlag = true;
}
void SceneGame::LaunchAuto()
{
	if(fabsf(wiiContoroller->getAccelerationY()) >= 1.0f && wiiContoroller->getRelease(WC_B))
	//if(pArgument_->pKeyboard_->IsTrigger(DIK_U))
	{
		Target* autoTarget = nullptr;
		for(int count = 0;count < targetTableIndex;count++)
		{
			if(autoLaunchTable[targetTable[count]] == false)
			{
				autoTarget = managerTarget->getTarget(targetTable[count]);
				autoLaunchTable[targetTable[count]] = true;

				break;
			}
		}

		if(autoTarget != nullptr)
		{
			int buff = -1;
			D3DXVECTOR3 buffPos = player->getPosition();

			buff = managerFireworks->Add(
					ManagerFireworks::STATE_RIGHTSP,
					managerPoint,
					buffPos,
					buffDiffWiiRot,
					autoTarget);

			if(buff != -1)
			{
				fireworksTable[fireworksTableIndex] = buff;
				fireworksTableIndex++;
			}
		}
	}

	for(int count = 0;count < TARGET_MAX;count++)
	{
		if(targetTable[count] == -1)
			autoLaunchTable[count] = false;
	}
}
void SceneGame::LaunchSP()
{
	int buff = -1;
	D3DXVECTOR3 buffPos = player->getPosition();


	buff = managerFireworks->AddSP(
			ManagerFireworks::STATE_RIGHTSP,
			managerPoint,
			D3DXVECTOR3(350.0f, buffPos.y, buffPos.z),
			D3DXVECTOR3(0.0f, 0.0f, 25.0f),
			COLOR_STATE_W);

	if(buff != -1)
	{
		fireworksTable[fireworksTableIndex] = buff;
		fireworksTableIndex++;
	}

	buff = managerFireworks->AddSP(
			ManagerFireworks::STATE_RIGHTSP,
			managerPoint,
			D3DXVECTOR3(-350.0f, buffPos.y, buffPos.z),
			D3DXVECTOR3(0.0f, 0.0f, -25.0f),
			COLOR_STATE_W);

	if(buff != -1)
	{
		fireworksTable[fireworksTableIndex] = buff;
		fireworksTableIndex++;
	}
}

//==============================================================================
// Brief  : 通常更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::normalUpdate(void)
{
	//PrintDebug( _T( "normalUpdate\n" ) );

	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;


	//	カメラの逆行列を取得する
	D3DXMATRIX cameraInvMat;
	pCamera_->GetRenderMatrix()->GetMatrixView(&cameraInvMat);
	D3DXMatrixInverse(&cameraInvMat, nullptr, &cameraInvMat);

	//	カメラの逆行列をプレイヤーにセット
	player->setInvViewMatrix(cameraInvMat);

	//	カメラの視線ベクトル取得
	D3DXVECTOR3 cameraVec;
	pCamera_->GetVector(&cameraVec);
	player->setCameraVec(cameraVec);


	{
		//	花火管理クラスの更新
		//MeasureTime("managerFireworksUpdate");
		managerFireworks->setInvViewMatrix(cameraInvMat);
		managerFireworks->Update(fireworksTable, &fireworksTableIndex);
	}
	//	ターゲットクラスの更新
	managerTarget->setInvViewMatrix(cameraInvMat);
	managerTarget->Update(targetTable, &targetTableIndex, autoLaunchTable);
	{
		// ポイントスプライト管理クラスの更新
		//MeasureTime("managerPoint");
		managerPoint->Update();
	}




	if(autoFadeTableNum < autoFadeTableMax)
	{
		autoFadeTableCount++;
		if(autoFadeTableCount == autoFadeTable[autoFadeTableNum])
		{
			autoFadeTableNum++;

			fpUpdate = &SceneGame::UpdateBetweenSection;
		}
	}




	//	プレイヤー移動処理
	MovePlayer();


	if(targetAppearFlag == true)
	{
#ifdef FIRE_MANUAL
		//	花火打ち上げ処理
		LaunchFireworks();
#endif

#ifdef FIRE_AUTO
		//	プレゼン直前の悪あがき
		if(selfLaunchFlag == true)
			LaunchFireworks();
		else
			LaunchAuto();

		if(pArgument_->pKeyboard_->IsTrigger(DIK_S))
		{
			if(selfLaunchFlag == true)
				selfLaunchFlag = false;
			else
				selfLaunchFlag = true;
		}
		//	プレゼン直前の悪あがき
#endif
	}
	else
	{
		//	プレゼン直前の悪あがき
		if(selfLaunchFlag == false)
			LaunchAuto();
	}


	PrintDebug( _T( "targetTableIndex = %d\n"), targetTableIndex);
	for(int count = 0;count < TARGET_MAX;count++)
	{
		PrintDebug( _T( "targetTable[%d] = %d\n"), count, targetTable[count]);
		PrintDebug( _T( "autoLaunchTable[%d] = %d\n"), count, autoLaunchTable[count]);
	}


	if(wiiContoroller->getTrigger(WC_TWO))
	{
		if(synchronizeFlag == false)
			synchronizeFlag = true;
		else
			synchronizeFlag = false;
	}

	//	打ち上げる花火色切り替え
	//------------------------------------------------------------------
	if(pArgument_->pVirtualController_->IsTrigger(VC_LEFT))
	{
		fireworksUI->subRotColor();
		colorState = fireworksUI->getColorState();
	}
	if(pArgument_->pVirtualController_->IsTrigger(VC_RIGHT))
	{
		fireworksUI->addRotColor();
		colorState = fireworksUI->getColorState();
	}
	//------------------------------------------------------------------

	//	Aボタン押されたら
	if(pArgument_->pVirtualController_->IsTrigger(VC_BURN) == true)
	{
		//	ターゲットと花火の当たり判定
		collision_fireworks_target();
	}
	collision_fireworks_targetAuto();
	collision_fireworks_fireworks();


	//	コンボが一定数になったら、シンクロ花火発射
	if(combo->getScore() != combo->getScorePrev())
	{
		if(combo->getScore() % AUTO_SYNCRO_FIREWORKS == 0)
		{
			LaunchSP();
		}
	}


#ifdef _TEST

	//	+キーが押されたら
	if(pArgument_->pKeyboard_->IsTrigger(DIK_N))
	{
		gage->addPercentFuture(10);
	}

	//	-キーが押されたら
	if(pArgument_->pKeyboard_->IsTrigger(DIK_M))
	{
		gage->addPercentFuture(-10);
	}

	if(pArgument_->pKeyboard_->IsTrigger(DIK_T))
	{
		if(targetAppearFlag == false)
		{
			targetAppearFlag = true;
			managerTarget->setAutoAppearFlag(true);
		}
		else
		{
			targetAppearFlag = false;
			managerTarget->setAutoAppearFlag(false);
		}
	}

	if(autoLaunchFlag == false)
	{
		if(pArgument_->pKeyboard_->IsTrigger(DIK_R))
		{
			int buff;
			buff = managerTarget->Add(
				D3DXVECTOR3(0.0f, 90.0f, targetAppearPosZ),
				COLOR_STATE_R);
			if(buff != -1)
			{
				targetTable[targetTableIndex] = buff;
				targetTableIndex++;


				autoLaunchFlag = true;
				autoLaunchTarget = buff;
			}
		}

		if(pArgument_->pKeyboard_->IsTrigger(DIK_G))
		{
			int buff;
			buff = managerTarget->Add(
				D3DXVECTOR3(0.0f, 90.0f, targetAppearPosZ),
				COLOR_STATE_G);
			if(buff != -1)
			{
				targetTable[targetTableIndex] = buff;
				targetTableIndex++;

				autoLaunchFlag = true;
				autoLaunchTarget = buff;
			}
		}

		if(pArgument_->pKeyboard_->IsTrigger(DIK_B))
		{
			int buff;
			buff = managerTarget->Add(
				D3DXVECTOR3(0.0f, 90.0f, targetAppearPosZ),
				COLOR_STATE_B);
			if(buff != -1)
			{
				targetTable[targetTableIndex] = buff;
				targetTableIndex++;


				autoLaunchFlag = true;
				autoLaunchTarget = buff;
			}
		}

		if(pArgument_->pKeyboard_->IsTrigger(DIK_W))
		{
			int buff;
			autoLaunchNear = 0;
			buff = managerTarget->Add(
				D3DXVECTOR3(0.0f, 100.0f, targetAppearPosZ),
				COLOR_STATE_W);
			if(buff != -1)
			{
				targetTable[targetTableIndex] = buff;
				targetTableIndex++;


				autoLaunchFlag = true;
				autoLaunchTarget = buff;
			}

			//	数字キーを押しながらWを打ち上げると、優(その他)良(1)可(2)の花火があがる
			if(pArgument_->pKeyboard_->IsPress(DIK_1))
				autoLaunchNear = 1;
			else if(pArgument_->pKeyboard_->IsPress(DIK_2))
				autoLaunchNear = 2;
		}
	}

	if(pArgument_->pKeyboard_->IsTrigger(DIK_D))
	{
		LaunchSP();
	}

	if(autoLaunchFlag == true)
	{
		autoLaunchCount++;
		if(autoLaunchCount >= 150)
		{
			int buff2 = -1;
			D3DXVECTOR3 buffPos = player->getPosition();

			if(managerTarget->getTarget(autoLaunchTarget)->getColorState() == COLOR_STATE_W)
			{
				buff2 = managerFireworks->AddW(
					ManagerFireworks::STATE_RIGHTSP,
					managerPoint,
					buffPos,
					buffDiffWiiRot,
					managerTarget->getTarget(autoLaunchTarget),
					autoLaunchNear);

				if(buff2 != -1)
				{
					fireworksTable[fireworksTableIndex] = buff2;
					fireworksTableIndex++;
				}
			}
			else
			{
				buff2 = managerFireworks->Add(
						ManagerFireworks::STATE_RIGHTSP,
						managerPoint,
						buffPos,
						buffDiffWiiRot,
						managerTarget->getTarget(autoLaunchTarget));

				if(buff2 != -1)
				{
					fireworksTable[fireworksTableIndex] = buff2;
					fireworksTableIndex++;
				}
			}

			autoLaunchCount = 0;
			autoLaunchFlag = false;
		}
	}

#endif



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

		//	音再生
		desideSound->Play();

		if(finger != nullptr)
			finger->SetEnableGraphic(true);
	}
}
//==============================================================================
// Brief  : 通常更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::tutorialUpdate(void)
{
	//PrintDebug( _T( "normalUpdate\n" ) );

	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;


	//	カメラの逆行列を取得する
	D3DXMATRIX cameraInvMat;
	pCamera_->GetRenderMatrix()->GetMatrixView(&cameraInvMat);
	D3DXMatrixInverse(&cameraInvMat, nullptr, &cameraInvMat);

	//	カメラの逆行列をプレイヤーにセット
	player->setInvViewMatrix(cameraInvMat);

	//	カメラの視線ベクトル取得
	D3DXVECTOR3 cameraVec;
	pCamera_->GetVector(&cameraVec);
	player->setCameraVec(cameraVec);


	{
		//	花火管理クラスの更新
		//MeasureTime("managerFireworksUpdate");
		managerFireworks->setInvViewMatrix(cameraInvMat);
		managerFireworks->Update(fireworksTable, &fireworksTableIndex);
	}
	//	ターゲットクラスの更新
	managerTarget->setInvViewMatrix(cameraInvMat);
	managerTarget->Update(targetTable, &targetTableIndex, autoLaunchTable);
	{
		// ポイントスプライト管理クラスの更新
		//MeasureTime("managerPoint");
		managerPoint->Update();
	}

	//	プレイヤー移動処理
	MovePlayer();


	if(targetAppearFlag == true)
	{
#ifdef FIRE_MANUAL
		//	花火打ち上げ処理
		LaunchFireworks();
#endif

#ifdef FIRE_AUTO
		//	プレゼン直前の悪あがき
		if(selfLaunchFlag == true)
			LaunchFireworks();
		else
			LaunchAuto();

		if(pArgument_->pKeyboard_->IsTrigger(DIK_S))
		{
			if(selfLaunchFlag == true)
				selfLaunchFlag = false;
			else
				selfLaunchFlag = true;
		}
		//	プレゼン直前の悪あがき
#endif
	}
	else
	{
		//	プレゼン直前の悪あがき
		if(selfLaunchFlag == false)
			LaunchAuto();
	}

	PrintDebug( _T( "targetTableIndex = %d\n"), targetTableIndex);
	for(int count = 0;count < TARGET_MAX;count++)
	{
		PrintDebug( _T( "targetTable[%d] = %d\n"), count, targetTable[count]);
		PrintDebug( _T( "autoLaunchTable[%d] = %d\n"), count, autoLaunchTable[count]);
	}


	if(wiiContoroller->getTrigger(WC_TWO))
	{
		if(synchronizeFlag == false)
			synchronizeFlag = true;
		else
			synchronizeFlag = false;
	}


	//	テスト用ここから
	//---------------------------------------------------------------------------------------------------------
	//	ターゲット出現
	if(targetAppearFlag == true)
	{
		targetAppearCount++;
		if(targetAppearCount == 150)
		{
			int buff;
			buff = managerTarget->Add(
				//D3DXVECTOR3(RANDOM(400), (float)(rand() % 50) + 50.0f, targetAppearPosZ),
				D3DXVECTOR3(RANDOM(300), 100.0f, targetAppearPosZ),
				(COLOR_STATE)(rand() % COLOR_STATE_S));
			if(buff != -1)
			{
				targetTable[targetTableIndex] = buff;
				targetTableIndex++;
			}
	
			targetAppearCount = 0;
		}
	}
	//---------------------------------------------------------------------------------------------------------
	//	テスト用ここまで



	if(pArgument_->pKeyboard_->IsPress(DIK_LSHIFT))
	{
		if(pArgument_->pKeyboard_->IsPress(DIK_UP))
		{
			player->addRotationArm(0.1f, 0.0f, 0.0f);
		}
		else if(pArgument_->pKeyboard_->IsPress(DIK_DOWN))
		{
			player->addRotationArm(-0.1f, 0.0f, 0.0f);
		}

		if(pArgument_->pKeyboard_->IsPress(DIK_LEFT))
		{
			player->addRotationArm(0.0f, 0.1f, 0.0f);
		}
		else if(pArgument_->pKeyboard_->IsPress(DIK_RIGHT))
		{
			player->addRotationArm(0.0f, -0.1f, 0.0f);
		}

		if(pArgument_->pKeyboard_->IsPress(DIK_Q))
		{
			player->addRotationArm(0.0f, 0.0f, 0.1f);
		}
		else if(pArgument_->pKeyboard_->IsPress(DIK_E))
		{
			player->addRotationArm(0.0f, 0.0f, -0.1f);
		}
	}

	//	打ち上げる花火色切り替え
	//------------------------------------------------------------------
	if(pArgument_->pVirtualController_->IsTrigger(VC_LEFT))
	{
		fireworksUI->subRotColor();
		colorState = fireworksUI->getColorState();
	}
	if(pArgument_->pVirtualController_->IsTrigger(VC_RIGHT))
	{
		fireworksUI->addRotColor();
		colorState = fireworksUI->getColorState();
	}
	//------------------------------------------------------------------

	//	Aボタン押されたら
	if(pArgument_->pVirtualController_->IsTrigger(VC_BURN) == true)
	{
		//	ターゲットと花火の当たり判定
		collision_fireworks_target();
	}
	collision_fireworks_targetAuto();
	collision_fireworks_fireworks();


	//	コンボが一定数になったら、シンクロ花火発射
	if(combo->getScore() != combo->getScorePrev())
	{
		if(combo->getScore() % AUTO_SYNCRO_FIREWORKS == 0)
		{
			LaunchSP();
		}
	}

	//	ポーズキーが押されたら
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE))
	{
		fpUpdate = &SceneGame::UpdateCountDownGame;
		ManagerSceneMain::tutorialFlag = false;
	}
}
//==============================================================================
// Brief  : デモ用更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::demoUpdate(void)
{
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
		//MeasureTime("managerPoint");
		managerPoint->Update();
	}


	//	ターゲット出現
	targetAppearCount++;
	if(targetAppearCount == 90)
	{
		int buff;
		buff = managerTarget->Add(
			D3DXVECTOR3(RANDOM(300), (float)(rand() % 50) + 50.0f, targetAppearPosZ),
			(COLOR_STATE)(rand() % COLOR_STATE_W));
		if(buff != -1)
		{
			targetTable[targetTableIndex] = buff;
			targetTableIndex++;

			autoLaunchFlag = true;
			autoLaunchTarget = buff;
		}
	
		targetAppearCount = 0;
	}


	if(autoLaunchFlag == true)
	{
		autoLaunchCount++;
		if(autoLaunchCount == 80)
		{
			int buff2 = -1;
			D3DXVECTOR3 buffPos = player->getPosition();

			buff2 = managerFireworks->Add(
					ManagerFireworks::STATE_RIGHTSP,
					managerPoint,
					buffPos,
					buffDiffWiiRot,
					managerTarget->getTarget(autoLaunchTarget));

			if(buff2 != -1)
			{
				fireworksTable[fireworksTableIndex] = buff2;
				fireworksTableIndex++;
			}

			autoLaunchCount = 0;
			autoLaunchFlag = false;
		}
	}

	collision_fireworks_fireworks();
	collision_fireworks_targetAuto();

	//	コンボが一定数になったら、シンクロ花火発射
	if(combo->getScore() != combo->getScorePrev())
	{
		if(combo->getScore() % 5 == 0)
		{
			LaunchSP();
		}
	}

	ManagerSceneMain::demoCount++;

	//	ポーズキーが押されたら
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE) ||
		ManagerSceneMain::demoCount >= ManagerSceneMain::demoCountMax)
	{
		ManagerSceneMain::demoCount = 0;

		//	更新関数設定
		fpUpdate = &SceneGame::pauseFadeUpdateDemo;

		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
			pArgument_->pUpdate_->SetIsEnable( true );
		}
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
		D3DXVECTOR2 IRBuff = wiiContoroller->getIRScreen();
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

			//	音再生
			desideSound->Play();

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

		//	音再生
		selectSound->Play();

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

		//	音再生
		selectSound->Play();

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
		D3DXVECTOR2 IRBuff = wiiContoroller->getIRScreen();

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

		//	音再生
		desideSound->Play();

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
// Brief  : ポーズ更新処理(フェード用)
//==============================================================================
void SceneGame::pauseFadeUpdateDemo(void)
{
	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;

	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_TITLE );
		ManagerSceneMain::demoFlag = false;

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
		wiiContoroller->reConnectWiimote();

	//	wiiリモコンが再接続が終了したら
	if(wiiContoroller->getIsReConnectWiimote() == false)
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

		//	音再生
		desideSound->Play();
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
		wiiContoroller->reConnectWiiboard();

	//	wiiリモコンが再接続が終了したら
	if(wiiContoroller->getIsReConnectWiiboard() == false)
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

		//	音再生
		desideSound->Play();
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
	if(wiiContoroller->getIsReConnectWiimote() == true)
	{
		//	更新関数設定
		fpUpdate = &SceneGame::reConnectWiimoteUpdate;

		//	再接続要求オブジェクト可視化
		reConnectWiimote->SetEnableGraphic(true);

		//	Objectの更新を止める
		pArgument_->pUpdate_->SetIsEnable( false );

		//	音再生
		cancelSound->Play();

		return false;
	}

	//	wiiボードが再接続要求をした場合
	if(wiiContoroller->getIsReConnectWiiboard() == true)
	{
		//	更新関数設定
		fpUpdate = &SceneGame::reConnectWiiboardUpdate;

		//	再接続要求オブジェクト可視化
		reConnectWiiboard->SetEnableGraphic(true);

		//	Objectの更新を止める
		pArgument_->pUpdate_->SetIsEnable( false );

		//	音再生
		cancelSound->Play();

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

	int buffIndex = 0;
	bool errorCheckFlag = false;

	//	存在する花火の数分ループ
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	花火の情報取得
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		if(buffFireworks->getBurnSPFlag())
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
				int returnValue = buffFireworks->burnNew151220(buffTargetSize * buffTargetSize, hitPosLength);

				//	ゲージ加算
				//----------------------------------------------------------------------------------
				//	RGBのいずれかと一緒だったら加算（中）
				if(buffFireworks->getColorState() == buffTarget->getColorState())
				{
					AddGage(3.0f);
				}
				//	白色は１００％加算（小）
				else if(buffTarget->getColorState() == COLOR_STATE_W)
				{
					AddGage(1.0f);
				}
				//----------------------------------------------------------------------------------

				//	スペシャル花火の発射
				if(buffTarget->getColorState() == COLOR_STATE_S)
					LaunchSP();

				//	コンボ数加算
				combo->addScore();

				//	スコア値加算
				score->setAddScore((gage->getPercent() + 5));
				score->AddScoreFuture(combo->getScore() * (gage->getPercent() + 5));

				//	ターゲット消去
				buffTarget->Dissappear();

				//	振動
				wiiContoroller->rumble((unsigned int)250);

				//	次の花火との当たり判定へ移行
				break;
			}
		}
	}


	/*
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	花火の情報取得
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		//	コンボ数加算
		combo->addScore();

		//	スコア値加算
		score->setAddScore((gage->getPercent() + 10));
		score->AddScoreFuture(combo->getScore() * (gage->getPercent() + 10));

		//	破裂
		buffFireworks->burn(0.0f, 0.0f);

		//	振動
		wiiContoroller->rumble((unsigned int)300);
	}
	*/
}
void SceneGame::collision_fireworks_targetAuto()
{
	float hitPosLength = 0.0f;

	//	存在する花火の数分ループ
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	花火の情報取得
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);

		if(buffFireworks->IsBurnFlag())
			continue;

		if(buffFireworks->getDeleteCount() != buffFireworks->getParam()->deleteCountMax - 1)
			continue;

		//	花火の位置情報取得
		buffFireworks->posUp1();
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
				int returnValue = buffFireworks->burnNew151220(buffTargetSize * buffTargetSize, hitPosLength);

				autoLaunchTable[targetTable[targetCount]] = false;


				if(synchronizeFlag == true)
				{
					synchronizeFlag = false;
					LaunchSP();
				}


				//	ゲージ加算
				//----------------------------------------------------------------------------------
				//	RGBのいずれかと一緒だったら加算（中）
				if(buffFireworks->getColorState() == buffTarget->getColorState())
				{
					AddGage(3.0f);
				}
				//	白色は１００％加算（小）
				else if(buffTarget->getColorState() == COLOR_STATE_W)
				{
					AddGage(1.0f);
				}
				//----------------------------------------------------------------------------------

				//	コンボ数加算
				combo->addScore();

				//	スコア値加算
				score->setAddScore((gage->getPercent() + 5));
				score->AddScoreFuture(combo->getScore() * (gage->getPercent() + 5));

				//	ターゲット消去
				buffTarget->Dissappear();

				//	振動
				wiiContoroller->rumble((unsigned int)250);

				//	次の花火との当たり判定へ移行
				break;
			}
		}
	}
}
//==============================================================================
// Brief  : 花火と花火の当たり判定処理
//==============================================================================
void SceneGame::collision_fireworks_fireworks()
{
	float hitPosLength = 0.0f;
	int buffIndex = 0;

	bool errorCheckFlag = false;

	//	存在する花火の数分ループ
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	花火の情報取得
		buffIndex = fireworksTable[fireworksCount];
		if(buffIndex >= FIREWORKS_MAX || buffIndex < 0)
			continue;

		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		if(!buffFireworks->getBurnSPFlag())
			continue;

		//	花火の位置情報取得
		D3DXVECTOR3 buffFireworksPos = buffFireworks->getPosition();

		//	存在する花火の数＋１～最大数分ループ
		for(int fireworksCount2 = fireworksCount + 1;fireworksCount2 < fireworksTableIndex;fireworksCount2++)
		{
			buffIndex = fireworksTable[fireworksCount2];
			if(buffIndex >= FIREWORKS_MAX || buffIndex < 0)
				continue;

			Fireworks* buffFireworks2 = managerFireworks->getFireworks(fireworksTable[fireworksCount2]);
			if(buffFireworks2->IsBurnFlag())
				continue;

			if(!buffFireworks2->getBurnSPFlag())
			continue;

			if(buffFireworks == buffFireworks2)
			{
				errorCheckFlag = true;
				continue;
			}

			//	花火の位置情報取得
			D3DXVECTOR3 buffFireworksPos2 = buffFireworks2->getPosition();
			
			float hitPosLength;

			//	当たり判定
			if(hitCheckPointCircle(buffFireworksPos, buffFireworksPos2, fire_fire_collisionSize, &hitPosLength) == true)
			{
				//	破裂
				buffFireworks->burn2New151220();
				buffFireworks2->burn2New151220();

				//	ゲージ加算
				AddGage(ADD_20);

				//	コンボ数加算
				combo->addScore();
				combo->addScore();

				//	スコア値加算
				score->setAddScore((gage->getPercent() + 10));
				score->AddScoreFuture(combo->getScore() * (gage->getPercent() + 10));

				//	振動
				wiiContoroller->rumble((unsigned int)500);

				//	次の花火との当たり判定へ移行
				break;
			}
		}
	}

	if(errorCheckFlag == true)
	{
		for(int count = 0;count < fireworksTableIndex - 1;count++)
		{
			buffIndex = fireworksTable[count + 1];
			fireworksTable[count] = buffIndex;
		}
		fireworksTable[fireworksTableIndex] = -1;
		fireworksTableIndex--;
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
void SceneGame::AddGage(float _value)
{
	gage->addPercentFuture((float)ceil(_value));
}

