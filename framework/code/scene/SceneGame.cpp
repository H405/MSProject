//==============================================================================
//
// File   : SceneGame.cpp
// Brief  : �Q�[���V�[���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
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
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define RANDOM(value) (float)((rand() % value) - (rand() % value))
#define SQUARE(_value) (_value * _value)
#define AUTO_SYNCRO_FIREWORKS (5)

//#define _WIIBOARD
#define FIRE_AUTO
//#define FIRE_MANUAL

//******************************************************************************
// �ÓI�ϐ�
//******************************************************************************
//	�_�ŗp�J�E���g��
static const int flashingCountHirf = 20;
static const int flashingCountMax = 40;

//	�����@�����̃T�C�Y
static const float stringXX_NormalSizeX = 400.0f;
static const float stringXX_NormalSizeY = 120.0f;

//	�����l���Z�l
static const float addFlashingAlpha = 0.02f;

//	�ł��グ�Ԋu
static const int launchCountMax = 20;

//	�ԉΓ��m�̓����蔻�莞�ɁA�ǂ̒��x�߂Â����瓖����Ƃ��邩
static const float fire_fire_collisionSize = 5.0f;

static const float targetAppearPosZ = 400.0f;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneGame::SceneGame( void ) : SceneMain()
{
	// �N���X���̏���������
	InitializeSelf();

	synchronizeFlag = false;

#ifdef _TEST
	autoLaunchCount = 0;
	autoLaunchTarget = 0;
	autoLaunchFlag = false;
#endif
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneGame::~SceneGame( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : SceneGame* pOut						: �R�s�[��A�h���X
//==============================================================================
int SceneGame::Copy( SceneGame* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::Update( void )
{
	// �e�X�g
	//PrintDebug( _T( "�Q�[���V�[��\n" ) );

#ifdef _DEVELOP
	// �X�V�֐��̕ύX
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

	// �œ_�����̍X�V
	D3DXVECTOR3	positionLookAt;		// �����_
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

	// �e�p�J�����߂̍X�V
	D3DXVECTOR3	vectorLight;		// ���C�g�x�N�g��
	positionLookAt.y = 0.0f;
	pLight_->GetVector( &vectorLight );
	vectorLight *= -3500.0f;
	pCameraShadowNear_->SetPositionCamera( positionLookAt + vectorLight );
	pCameraShadowNear_->SetPositionLookAt( positionLookAt );

	// �e�p�J�������̍X�V
	pLight_->GetVector( &vectorLight );
	vectorLight *= -10000.0f;
	pCameraShadowFar_->SetPositionCamera( positionLookAt + vectorLight );
	pCameraShadowFar_->SetPositionLookAt( positionLookAt );

	// �e�p�J�����_�̍X�V
	const LightPoint*	pLightPoint = nullptr;		// �_����
	for( int counterLightPoint = 0; counterLightPoint < GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW; ++counterLightPoint )
	{
		pLightPoint = pArgument_->pEffectParameter_->GetLightPointLightness( counterLightPoint );
		if( pLightPoint != nullptr )
		{
			D3DXVECTOR3	positionLightPointCamera;		// �_�����̎��_���W
			D3DXVECTOR3	positionLightPointLookAt;		// �_�����̒����_���W
			pLightPoint->GetPosition( &positionLightPointCamera );
			positionLightPointLookAt = positionLightPointCamera;
			positionLightPointLookAt.y -= 1000.0f;
			ppCameraShadowPoint_[ counterLightPoint ]->SetPositionCamera( positionLightPointCamera );
			ppCameraShadowPoint_[ counterLightPoint ]->SetPositionLookAt( positionLightPointLookAt );
		}
	}

	//	�ݒ肳�ꂽ�X�V�֐���
	(this->*fpUpdate)();

	comboPrev = combo->getScore();

	// �ő�R���{���̍X�V
	if( comboPrev > maximumCombo_ )
	{
		maximumCombo_ = comboPrev;
	}
}

//==============================================================================
// Brief  : calibration�X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::calibrationUpdate(void)
{
	PrintDebug( _T( "calibrationUpdate\n" ) );

	//	�ڑ��؂�m�F
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
// Brief  : �v���C���[�̈ړ�����
//==============================================================================
void SceneGame::MovePlayer()
{
	//	wii�{�[�h�𗘗p�����A�v���C���[�̈ړ�����1
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

	//	�v���C���[�r�I�u�W�F�N�g�ɉ�]�ʂ��Z�b�g
	//D3DXVECTOR3 buff = player->getPosition();
	//D3DXVECTOR3 buffRot = wiiContoroller->getRot();
	//player->setRotationArm(DEG_TO_RAD(buffRot.x), DEG_TO_RAD(-buffRot.y), DEG_TO_RAD(buffRot.z));
}
//==============================================================================
// Brief  : �ԉΑł��グ����
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
// Brief  : �ʏ�X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::normalUpdate(void)
{
	//PrintDebug( _T( "normalUpdate\n" ) );

	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;


	//	�J�����̋t�s����擾����
	D3DXMATRIX cameraInvMat;
	pCamera_->GetRenderMatrix()->GetMatrixView(&cameraInvMat);
	D3DXMatrixInverse(&cameraInvMat, nullptr, &cameraInvMat);

	//	�J�����̋t�s����v���C���[�ɃZ�b�g
	player->setInvViewMatrix(cameraInvMat);

	//	�J�����̎����x�N�g���擾
	D3DXVECTOR3 cameraVec;
	pCamera_->GetVector(&cameraVec);
	player->setCameraVec(cameraVec);


	{
		//	�ԉΊǗ��N���X�̍X�V
		//MeasureTime("managerFireworksUpdate");
		managerFireworks->setInvViewMatrix(cameraInvMat);
		managerFireworks->Update(fireworksTable, &fireworksTableIndex);
	}
	//	�^�[�Q�b�g�N���X�̍X�V
	managerTarget->setInvViewMatrix(cameraInvMat);
	managerTarget->Update(targetTable, &targetTableIndex, autoLaunchTable);
	{
		// �|�C���g�X�v���C�g�Ǘ��N���X�̍X�V
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




	//	�v���C���[�ړ�����
	MovePlayer();


	if(targetAppearFlag == true)
	{
#ifdef FIRE_MANUAL
		//	�ԉΑł��グ����
		LaunchFireworks();
#endif

#ifdef FIRE_AUTO
		//	�v���[�����O�̈�������
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
		//	�v���[�����O�̈�������
#endif
	}
	else
	{
		//	�v���[�����O�̈�������
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

	//	�ł��グ��ԉΐF�؂�ւ�
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

	//	A�{�^�������ꂽ��
	if(pArgument_->pVirtualController_->IsTrigger(VC_BURN) == true)
	{
		//	�^�[�Q�b�g�Ɖԉ΂̓����蔻��
		collision_fireworks_target();
	}
	collision_fireworks_targetAuto();
	collision_fireworks_fireworks();


	//	�R���{����萔�ɂȂ�����A�V���N���ԉΔ���
	if(combo->getScore() != combo->getScorePrev())
	{
		if(combo->getScore() % AUTO_SYNCRO_FIREWORKS == 0)
		{
			LaunchSP();
		}
	}


#ifdef _TEST

	//	+�L�[�������ꂽ��
	if(pArgument_->pKeyboard_->IsTrigger(DIK_N))
	{
		gage->addPercentFuture(10);
	}

	//	-�L�[�������ꂽ��
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

			//	�����L�[�������Ȃ���W��ł��グ��ƁA�D(���̑�)��(1)��(2)�̉ԉ΂�������
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



	//	�|�[�Y�L�[�������ꂽ��
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE))
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::pauseUpdate;

		//	Object�̍X�V���~�߂�
		pArgument_->pUpdate_->SetIsEnable( false );

		//	�`��ĊJ
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);

		//	���Đ�
		desideSound->Play();

		if(finger != nullptr)
			finger->SetEnableGraphic(true);
	}
}
//==============================================================================
// Brief  : �ʏ�X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::tutorialUpdate(void)
{
	//PrintDebug( _T( "normalUpdate\n" ) );

	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;


	//	�J�����̋t�s����擾����
	D3DXMATRIX cameraInvMat;
	pCamera_->GetRenderMatrix()->GetMatrixView(&cameraInvMat);
	D3DXMatrixInverse(&cameraInvMat, nullptr, &cameraInvMat);

	//	�J�����̋t�s����v���C���[�ɃZ�b�g
	player->setInvViewMatrix(cameraInvMat);

	//	�J�����̎����x�N�g���擾
	D3DXVECTOR3 cameraVec;
	pCamera_->GetVector(&cameraVec);
	player->setCameraVec(cameraVec);


	{
		//	�ԉΊǗ��N���X�̍X�V
		//MeasureTime("managerFireworksUpdate");
		managerFireworks->setInvViewMatrix(cameraInvMat);
		managerFireworks->Update(fireworksTable, &fireworksTableIndex);
	}
	//	�^�[�Q�b�g�N���X�̍X�V
	managerTarget->setInvViewMatrix(cameraInvMat);
	managerTarget->Update(targetTable, &targetTableIndex, autoLaunchTable);
	{
		// �|�C���g�X�v���C�g�Ǘ��N���X�̍X�V
		//MeasureTime("managerPoint");
		managerPoint->Update();
	}

	//	�v���C���[�ړ�����
	MovePlayer();


	if(targetAppearFlag == true)
	{
#ifdef FIRE_MANUAL
		//	�ԉΑł��グ����
		LaunchFireworks();
#endif

#ifdef FIRE_AUTO
		//	�v���[�����O�̈�������
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
		//	�v���[�����O�̈�������
#endif
	}
	else
	{
		//	�v���[�����O�̈�������
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


	//	�e�X�g�p��������
	//---------------------------------------------------------------------------------------------------------
	//	�^�[�Q�b�g�o��
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
	//	�e�X�g�p�����܂�



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

	//	�ł��グ��ԉΐF�؂�ւ�
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

	//	A�{�^�������ꂽ��
	if(pArgument_->pVirtualController_->IsTrigger(VC_BURN) == true)
	{
		//	�^�[�Q�b�g�Ɖԉ΂̓����蔻��
		collision_fireworks_target();
	}
	collision_fireworks_targetAuto();
	collision_fireworks_fireworks();


	//	�R���{����萔�ɂȂ�����A�V���N���ԉΔ���
	if(combo->getScore() != combo->getScorePrev())
	{
		if(combo->getScore() % AUTO_SYNCRO_FIREWORKS == 0)
		{
			LaunchSP();
		}
	}

	//	�|�[�Y�L�[�������ꂽ��
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE))
	{
		fpUpdate = &SceneGame::UpdateCountDownGame;
		ManagerSceneMain::tutorialFlag = false;
	}
}
//==============================================================================
// Brief  : �f���p�X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::demoUpdate(void)
{
	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;


	//	�J�����̋t�s����擾����
	D3DXMATRIX cameraInvMat;
	pCamera_->GetRenderMatrix()->GetMatrixView(&cameraInvMat);
	D3DXMatrixInverse(&cameraInvMat, nullptr, &cameraInvMat);

	//	�J�����̋t�s����v���C���[�ɃZ�b�g
	player->setInvViewMatrix(cameraInvMat);


	{
		//	�ԉΊǗ��N���X�̍X�V
		//MeasureTime("managerFireworksUpdate");
		managerFireworks->setInvViewMatrix(cameraInvMat);
		managerFireworks->Update(fireworksTable, &fireworksTableIndex);
	}
	//	�^�[�Q�b�g�N���X�̍X�V
	managerTarget->setInvViewMatrix(cameraInvMat);
	managerTarget->Update(targetTable, &targetTableIndex);
	{
		// �|�C���g�X�v���C�g�Ǘ��N���X�̍X�V
		//MeasureTime("managerPoint");
		managerPoint->Update();
	}


	//	�^�[�Q�b�g�o��
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

	//	�R���{����萔�ɂȂ�����A�V���N���ԉΔ���
	if(combo->getScore() != combo->getScorePrev())
	{
		if(combo->getScore() % 5 == 0)
		{
			LaunchSP();
		}
	}

	ManagerSceneMain::demoCount++;

	//	�|�[�Y�L�[�������ꂽ��
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE) ||
		ManagerSceneMain::demoCount >= ManagerSceneMain::demoCountMax)
	{
		ManagerSceneMain::demoCount = 0;

		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::pauseFadeUpdateDemo;

		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
			pArgument_->pUpdate_->SetIsEnable( true );
		}
	}
}
//==============================================================================
// Brief  : �|�[�Y�X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::pauseUpdate(void)
{
	PrintDebug( _T( "pauseUpdate\n" ) );

	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;

	//	wii�����R������������Ă���Ύw�̈ړ�
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = wiiContoroller->getIRScreen();
		finger->SetPosition(IRBuff.x, IRBuff.y, 0.0f);
	}

	//	�P�t���[���O�̓o�^�I�u�W�F�N�g��ۑ�
	chooseObjectPrev = chooseObject;


	//	����L�[�����ꂽ��
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	�I������Ă���ꍇ
		if(chooseObject != nullptr)
		{
			//	�_�ŃJ�E���g������
			pushChooseObjectFlashingCount = 0;

			//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
			chooseObject->SetColorA(1.0f);

			//	���Đ�
			desideSound->Play();

			//	�ĊJ�������ꂽ��
			if(chooseObject == stringReturn)
			{
				//	�X�V�֐��ݒ�
				fpUpdate = &SceneGame::normalUpdate;

				//	Object�̍X�V���ĊJ
				pArgument_->pUpdate_->SetIsEnable( true );

				//	�`���~
				pauseFrame->SetEnableGraphic(false);
				stringReturn->SetEnableGraphic(false);
				stringStop->SetEnableGraphic(false);
				stringRetry->SetEnableGraphic(false);

				if(finger != nullptr)
					finger->SetEnableGraphic(false);
			}
			else
			{
				//	�X�V�֐��ݒ�
				fpUpdate = &SceneGame::pauseFadeUpdate;

				if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
				{
					pArgument_->pFade_->FadeOut( 20 );
					pArgument_->pUpdate_->SetIsEnable( true );
				}
			}
		}
	}


	//	���L�[�ňړ�
	if(pArgument_->pVirtualController_->IsTrigger(VC_UP))
	{
		//	�_�ŃJ�E���g������
		pushChooseObjectFlashingCount = 0;

		//	���Đ�
		selectSound->Play();

		//	wii�����R���ڑ����͈Ⴄ����
		if(chooseObject == nullptr)
		{
			//	�����L�[�ɕύX
			chooseFlag = false;

			//	�I�u�W�F�N�g�o�^
			chooseObject = stringReturn;
		}
		else
		{
			//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
			chooseObject->SetColorA(1.0f);

			//	�I�����ړ�
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
		//	�_�ŃJ�E���g������
		pushChooseObjectFlashingCount = 0;

		//	���Đ�
		selectSound->Play();

		//	wii�����R���ڑ����͈Ⴄ����
		if(chooseObject == nullptr)
		{
			//	�����L�[�ɕύX
			chooseFlag = false;

			//	�I�u�W�F�N�g�o�^
			chooseObject = stringRetry;
		}
		else
		{
			//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
			chooseObject->SetColorA(1.0f);

			//	�I�����ړ�
			if(chooseObject == stringReturn)
				chooseObject = stringStop;
			else if(chooseObject == stringStop)
				chooseObject = stringRetry;
			else
				chooseObject = stringReturn;
		}
	}


	//	wii�����R������������Ă���Ύw�̈ړ�
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = wiiContoroller->getIRScreen();

		//	�u�ĊJ�v�ɓ������Ă��
		if((IRBuff.x <= (stringReturn->GetPositionX() + (stringReturn->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringReturn->GetPositionX() - (stringReturn->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringReturn->GetPositionY() + (stringReturn->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringReturn->GetPositionY() - (stringReturn->GetScaleY() * 0.5f))) )
		{
			//	�_�ŃI�u�W�F�N�g�Ƃ��ēo�^
			chooseObject = stringReturn;

			//	�I����@��IR�ɕύX
			chooseFlag = true;
		}
		//	�u���~�v�ɓ������Ă��
		else if((IRBuff.x <= (stringStop->GetPositionX() + (stringStop->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringStop->GetPositionX() - (stringStop->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringStop->GetPositionY() + (stringStop->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringStop->GetPositionY() - (stringStop->GetScaleY() * 0.5f))) )
		{
			//	�_�ŃI�u�W�F�N�g�Ƃ��ēo�^
			chooseObject = stringStop;

			//	�I����@��IR�ɕύX
			chooseFlag = true;
		}
		//	�u���߂���v�ɓ������Ă��
		else if((IRBuff.x <= (stringRetry->GetPositionX() + (stringRetry->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringRetry->GetPositionX() - (stringRetry->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringRetry->GetPositionY() + (stringRetry->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringRetry->GetPositionY() - (stringRetry->GetScaleY() * 0.5f))) )
		{
			//	�_�ŃI�u�W�F�N�g�Ƃ��ēo�^
			chooseObject = stringRetry;

			//	�I����@��IR�ɕύX
			chooseFlag = true;
		}
		//	���ɂ��������ĂȂ����
		else
		{
			//	�I����@��IR�̏ꍇ�̂�
			if(chooseFlag == true)
			{
				if(chooseObject != nullptr)
				{
					//	�o�^����
					chooseObject->SetColorA(1.0f);
					chooseObject = nullptr;
					pushChooseObjectFlashingCount = 0;
				}
			}
		}
	}


	//	PAUSE�L�[�������ꂽ��
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE))
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::normalUpdate;

		//	Object�̍X�V���ĊJ
		pArgument_->pUpdate_->SetIsEnable( true );

		//	�`���~
		pauseFrame->SetEnableGraphic(false);
		stringReturn->SetEnableGraphic(false);
		stringStop->SetEnableGraphic(false);
		stringRetry->SetEnableGraphic(false);

		//	���Đ�
		desideSound->Play();

		if(finger != nullptr)
			finger->SetEnableGraphic(false);
	}


	//	�I�����ڂ̓_�ŏ���
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

		//	�P�t���[���O�̑I���I�u�W�F�N�g�̃T�C�Y��ύX
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



	//	Object�N���X�̍X�V���~�܂��Ă邩��A�����ōX�V����
	if(finger != nullptr)
		finger->Update();

	stringRetry->Update();
	stringReturn->Update();
	stringStop->Update();
}
//==============================================================================
// Brief  : �|�[�Y�X�V����(�t�F�[�h�p)
//==============================================================================
void SceneGame::pauseFadeUpdate(void)
{
	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;

	// �V�[���J��
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
// Brief  : �|�[�Y�X�V����(�t�F�[�h�p)
//==============================================================================
void SceneGame::pauseFadeUpdateDemo(void)
{
	//	�ڑ��؂�m�F
	if(wiiLostCheck() == false)
		return;

	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_TITLE );
		ManagerSceneMain::demoFlag = false;

		SetIsEnd( true );
	}
}
//==============================================================================
// Brief  : �Đڑ��v�����p�̍X�V����
//==============================================================================
void SceneGame::reConnectWiimoteUpdate(void)
{
	//	�Đڑ��v��
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		wiiContoroller->reConnectWiimote();

	//	wii�����R�����Đڑ����I��������
	if(wiiContoroller->getIsReConnectWiimote() == false)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::pauseUpdate;

		//	Object�̍X�V���~�߂�
		pArgument_->pUpdate_->SetIsEnable( false );

		//	�`���߂�
		reConnectWiimote->SetEnableGraphic(false);

		//	�`��ĊJ
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);
		finger->SetEnableGraphic(true);

		//	���Đ�
		desideSound->Play();
	}

	//	Object�N���X�̍X�V���~�܂��Ă邩��A�����ōX�V����
	reConnectWiimote->Update();
}
//==============================================================================
// Brief  : �Đڑ��v�����p�̍X�V����
//==============================================================================
void SceneGame::reConnectWiiboardUpdate(void)
{
	//	�Đڑ��v��
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		wiiContoroller->reConnectWiiboard();

	//	wii�����R�����Đڑ����I��������
	if(wiiContoroller->getIsReConnectWiiboard() == false)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::pauseUpdate;

		//	Object�̍X�V���~�߂�
		pArgument_->pUpdate_->SetIsEnable( false );

		//	�`���߂�
		reConnectWiiboard->SetEnableGraphic(false);

		//	�`��ĊJ
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);
		finger->SetEnableGraphic(true);

		//	���Đ�
		desideSound->Play();
	}

	//	Object�N���X�̍X�V���~�܂��Ă邩��A�����ōX�V����
	reConnectWiiboard->Update();
}
//==============================================================================
// Brief  : wii�����R���̃��X�g�`�F�b�N����
// Return : bool								: true = ��薳�� false = ���X�g
// Arg    : void								: �Ȃ�
//==============================================================================
bool SceneGame::wiiLostCheck(void)
{
	//	wii�����R�����Đڑ��v���������ꍇ
	if(wiiContoroller->getIsReConnectWiimote() == true)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::reConnectWiimoteUpdate;

		//	�Đڑ��v���I�u�W�F�N�g����
		reConnectWiimote->SetEnableGraphic(true);

		//	Object�̍X�V���~�߂�
		pArgument_->pUpdate_->SetIsEnable( false );

		//	���Đ�
		cancelSound->Play();

		return false;
	}

	//	wii�{�[�h���Đڑ��v���������ꍇ
	if(wiiContoroller->getIsReConnectWiiboard() == true)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::reConnectWiiboardUpdate;

		//	�Đڑ��v���I�u�W�F�N�g����
		reConnectWiiboard->SetEnableGraphic(true);

		//	Object�̍X�V���~�߂�
		pArgument_->pUpdate_->SetIsEnable( false );

		//	���Đ�
		cancelSound->Play();

		return false;
	}

	return true;
}
//==============================================================================
// Brief  : �ԉ΂ƃ^�[�Q�b�g�̓����蔻�菈��
//==============================================================================
void SceneGame::collision_fireworks_target()
{
	float hitPosLength = 0.0f;

	int buffIndex = 0;
	bool errorCheckFlag = false;

	//	���݂���ԉ΂̐������[�v
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	�ԉ΂̏��擾
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		if(buffFireworks->getBurnSPFlag())
			continue;

		//	�ԉ΂̈ʒu���擾
		D3DXVECTOR3 buffFireworksPos = buffFireworks->getPosition();

		//	���݂���^�[�Q�b�g�̐������[�v
		for(int targetCount = 0;targetCount < targetTableIndex;targetCount++)
		{
			//	�^�[�Q�b�g�̈ʒu���擾
			Target* buffTarget = managerTarget->getTarget(targetTable[targetCount]);
			D3DXVECTOR3 buffTargetPos = buffTarget->getPosition();

			//	�^�[�Q�b�g�̃T�C�Y�擾
			float buffTargetSize = (managerTarget->getTarget(targetCount)->getScale() * 0.5f);

			//	�����蔻��
			if(hitCheckPointCircle(buffFireworksPos, buffTargetPos, buffTargetSize, &hitPosLength) == true)
			{
				//	�j��
				int returnValue = buffFireworks->burnNew151220(buffTargetSize * buffTargetSize, hitPosLength);

				//	�Q�[�W���Z
				//----------------------------------------------------------------------------------
				//	RGB�̂����ꂩ�ƈꏏ����������Z�i���j
				if(buffFireworks->getColorState() == buffTarget->getColorState())
				{
					AddGage(3.0f);
				}
				//	���F�͂P�O�O�����Z�i���j
				else if(buffTarget->getColorState() == COLOR_STATE_W)
				{
					AddGage(1.0f);
				}
				//----------------------------------------------------------------------------------

				//	�X�y�V�����ԉ΂̔���
				if(buffTarget->getColorState() == COLOR_STATE_S)
					LaunchSP();

				//	�R���{�����Z
				combo->addScore();

				//	�X�R�A�l���Z
				score->setAddScore((gage->getPercent() + 5));
				score->AddScoreFuture(combo->getScore() * (gage->getPercent() + 5));

				//	�^�[�Q�b�g����
				buffTarget->Dissappear();

				//	�U��
				wiiContoroller->rumble((unsigned int)250);

				//	���̉ԉ΂Ƃ̓����蔻��ֈڍs
				break;
			}
		}
	}


	/*
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	�ԉ΂̏��擾
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		//	�R���{�����Z
		combo->addScore();

		//	�X�R�A�l���Z
		score->setAddScore((gage->getPercent() + 10));
		score->AddScoreFuture(combo->getScore() * (gage->getPercent() + 10));

		//	�j��
		buffFireworks->burn(0.0f, 0.0f);

		//	�U��
		wiiContoroller->rumble((unsigned int)300);
	}
	*/
}
void SceneGame::collision_fireworks_targetAuto()
{
	float hitPosLength = 0.0f;

	//	���݂���ԉ΂̐������[�v
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	�ԉ΂̏��擾
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);

		if(buffFireworks->IsBurnFlag())
			continue;

		if(buffFireworks->getDeleteCount() != buffFireworks->getParam()->deleteCountMax - 1)
			continue;

		//	�ԉ΂̈ʒu���擾
		buffFireworks->posUp1();
		D3DXVECTOR3 buffFireworksPos = buffFireworks->getPosition();

		//	���݂���^�[�Q�b�g�̐������[�v
		for(int targetCount = 0;targetCount < targetTableIndex;targetCount++)
		{
			//	�^�[�Q�b�g�̈ʒu���擾
			Target* buffTarget = managerTarget->getTarget(targetTable[targetCount]);
			D3DXVECTOR3 buffTargetPos = buffTarget->getPosition();

			//	�^�[�Q�b�g�̃T�C�Y�擾
			float buffTargetSize = (managerTarget->getTarget(targetCount)->getScale() * 0.5f);

			//	�����蔻��
			if(hitCheckPointCircle(buffFireworksPos, buffTargetPos, buffTargetSize, &hitPosLength) == true)
			{
				//	�j��
				int returnValue = buffFireworks->burnNew151220(buffTargetSize * buffTargetSize, hitPosLength);

				autoLaunchTable[targetTable[targetCount]] = false;


				if(synchronizeFlag == true)
				{
					synchronizeFlag = false;
					LaunchSP();
				}


				//	�Q�[�W���Z
				//----------------------------------------------------------------------------------
				//	RGB�̂����ꂩ�ƈꏏ����������Z�i���j
				if(buffFireworks->getColorState() == buffTarget->getColorState())
				{
					AddGage(3.0f);
				}
				//	���F�͂P�O�O�����Z�i���j
				else if(buffTarget->getColorState() == COLOR_STATE_W)
				{
					AddGage(1.0f);
				}
				//----------------------------------------------------------------------------------

				//	�R���{�����Z
				combo->addScore();

				//	�X�R�A�l���Z
				score->setAddScore((gage->getPercent() + 5));
				score->AddScoreFuture(combo->getScore() * (gage->getPercent() + 5));

				//	�^�[�Q�b�g����
				buffTarget->Dissappear();

				//	�U��
				wiiContoroller->rumble((unsigned int)250);

				//	���̉ԉ΂Ƃ̓����蔻��ֈڍs
				break;
			}
		}
	}
}
//==============================================================================
// Brief  : �ԉ΂Ɖԉ΂̓����蔻�菈��
//==============================================================================
void SceneGame::collision_fireworks_fireworks()
{
	float hitPosLength = 0.0f;
	int buffIndex = 0;

	bool errorCheckFlag = false;

	//	���݂���ԉ΂̐������[�v
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	�ԉ΂̏��擾
		buffIndex = fireworksTable[fireworksCount];
		if(buffIndex >= FIREWORKS_MAX || buffIndex < 0)
			continue;

		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		if(!buffFireworks->getBurnSPFlag())
			continue;

		//	�ԉ΂̈ʒu���擾
		D3DXVECTOR3 buffFireworksPos = buffFireworks->getPosition();

		//	���݂���ԉ΂̐��{�P�`�ő吔�����[�v
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

			//	�ԉ΂̈ʒu���擾
			D3DXVECTOR3 buffFireworksPos2 = buffFireworks2->getPosition();
			
			float hitPosLength;

			//	�����蔻��
			if(hitCheckPointCircle(buffFireworksPos, buffFireworksPos2, fire_fire_collisionSize, &hitPosLength) == true)
			{
				//	�j��
				buffFireworks->burn2New151220();
				buffFireworks2->burn2New151220();

				//	�Q�[�W���Z
				AddGage(ADD_20);

				//	�R���{�����Z
				combo->addScore();
				combo->addScore();

				//	�X�R�A�l���Z
				score->setAddScore((gage->getPercent() + 10));
				score->AddScoreFuture(combo->getScore() * (gage->getPercent() + 10));

				//	�U��
				wiiContoroller->rumble((unsigned int)500);

				//	���̉ԉ΂Ƃ̓����蔻��ֈڍs
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
// Brief  : �_�Ɖ~�̓����蔻�菈��
// Return : bool								: �����������������ĂȂ���
// Arg    : D3DXVECTOR3							: �_�̈ʒu
// Arg    : D3DXVECTOR3							: �~�̈ʒu
// Arg    : D3DXVECTOR3							: �������Ă�Ɣ��肷��ő勗��
// Arg    : float								: �~�̒��S����_�ւ̋���
//==============================================================================
bool SceneGame::hitCheckPointCircle(D3DXVECTOR3 _pointPos, D3DXVECTOR3 _circlePos, float _hitCheckOffset, float* _hitPosLength)
{
	//	�ʒu�֌W�v�Z
	float lengthX = _pointPos.x - _circlePos.x;
	float lengthY = _pointPos.y - _circlePos.y;

	float returnLength = SQUARE(lengthX) + SQUARE(lengthY);

	//	����
	if(returnLength <= (_hitCheckOffset * _hitCheckOffset))
	{
		//	�ǂ̂��炢���ꂽ����ۑ�
		*_hitPosLength = returnLength;

		return true;
	}

	return false;
}
//==============================================================================
// Brief  : �V���N���Q�[�W�̉��Z��������
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

