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
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define RANDOM(value) (float)((rand() % value) - (rand() % value))
#define SQUARE(_value) (_value * _value)

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
	PrintDebug( _T( "�Q�[���V�[��\n" ) );

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
		fpUpdate = &SceneGame::UpdatePreviousGame;
	}
#endif

	//	�ݒ肳�ꂽ�X�V�֐���
	(this->*fpUpdate)();
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
		pArgument_->pWiiController_->rotReset();
		pArgument_->pWiiController_->calibrationWiiboard();

		calibrationWiimote->SetEnableGraphic(false);

		fpUpdate = &SceneGame::normalUpdate;
	}
}

//==============================================================================
// Brief  : �v���C���[�̈ړ�����
//==============================================================================
void SceneGame::MovePlayer()
{
	//	wii�{�[�h�𗘗p�����A�v���C���[�̈ړ�����1
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


	//	�v���C���[�r�I�u�W�F�N�g�ɉ�]�ʂ��Z�b�g
	D3DXVECTOR3 buffRot = pArgument_->pWiiController_->getRot();
	player->setRotationArm(DEG_TO_RAD(buffRot.x), DEG_TO_RAD(-buffRot.y), DEG_TO_RAD(buffRot.z));
}
//==============================================================================
// Brief  : �ԉΑł��グ����
//==============================================================================
void SceneGame::LaunchFireworks()
{
	if(launchFlag == false)
	{
		//	B�{�^���𗣂�������
		if(pArgument_->pWiiController_->getAccelerationY() >= 1.0f &&
			pArgument_->pWiiController_->getRelease(WC_B))
		{
			buffWiiAccel = pArgument_->pWiiController_->getAcceleration();
			buffWiiRot = pArgument_->pWiiController_->getRot();

			int buff;
			D3DXVECTOR3 buffPos = player->getPosition();

			if(buffWiiAccel.x <= 0.0f)
			{
				//	rot��90�x�Ő^���������
				//	rotSpeed���}�C�i�X�l�Ȃ�E���ɋȂ���
				//	rotSpeed���@�v���X�l�Ȃ獶���ɋȂ���
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
// Brief  : �ʏ�X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::normalUpdate(void)
{
	PrintDebug( _T( "normalUpdate\n" ) );

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
		MeasureTime("managerPoint");
		managerPoint->Update();
	}

	//	�v���C���[�ړ�����
	MovePlayer();

	//	�ԉΑł��グ����
	LaunchFireworks();





	//	�e�X�g�p��������
	//---------------------------------------------------------------------------------------------------------
	PrintDebug( _T( "\nbuffWiiAccel.x = %f\n"), buffWiiAccel.x );
	PrintDebug( _T( "\nbuffWiiAccel.y = %f\n"), buffWiiAccel.y );
	PrintDebug( _T( "\nbuffWiiAccel.z = %f\n"), buffWiiAccel.z );
	PrintDebug( _T( "\nbuffWiiRot.x = %f\n"), buffWiiRot.x );
	PrintDebug( _T( "\nbuffWiiRot.y = %f\n"), buffWiiRot.y );
	PrintDebug( _T( "\nbuffWiiRot.z = %f\n"), buffWiiRot.z );

	//	�^�[�Q�b�g�o��
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
	//	�e�X�g�p�����܂�




	//	wii�����R���̉�]������
	if(pArgument_->pWiiController_->getPress(WC_PLUS) && pArgument_->pWiiController_->getPress(WC_MINUS))
		pArgument_->pWiiController_->rotReset();

	//	A�{�^�������ꂽ��
	if(pArgument_->pVirtualController_->IsTrigger(VC_BURN) == true)
	{
		//	�^�[�Q�b�g�Ɖԉ΂̓����蔻��
		collision_fireworks_target();
	}
	//	�ԉ΂Ɖԉ΂̓����蔻��
	collision_fireworks_fireworks();


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

		if(finger != nullptr)
			finger->SetEnableGraphic(true);
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
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();
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
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();

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
// Brief  : �Đڑ��v�����p�̍X�V����
//==============================================================================
void SceneGame::reConnectWiimoteUpdate(void)
{
	//	�Đڑ��v��
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		pArgument_->pWiiController_->reConnectWiimote();

	//	wii�����R�����Đڑ����I��������
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == false)
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
		pArgument_->pWiiController_->reConnectWiiboard();

	//	wii�����R�����Đڑ����I��������
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == false)
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
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == true)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::reConnectWiimoteUpdate;

		//	�Đڑ��v���I�u�W�F�N�g����
		reConnectWiimote->SetEnableGraphic(true);

		//	Object�̍X�V���~�߂�
		pArgument_->pUpdate_->SetIsEnable( false );

		return false;
	}

	//	wii�{�[�h���Đڑ��v���������ꍇ
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == true)
	{
		//	�X�V�֐��ݒ�
		fpUpdate = &SceneGame::reConnectWiiboardUpdate;

		//	�Đڑ��v���I�u�W�F�N�g����
		reConnectWiiboard->SetEnableGraphic(true);

		//	Object�̍X�V���~�߂�
		pArgument_->pUpdate_->SetIsEnable( false );

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

	//	���݂���ԉ΂̐������[�v
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	�ԉ΂̏��擾
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
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
				int returnValue = buffFireworks->burn(buffTargetSize * buffTargetSize, hitPosLength);

				AddGage((ADD_SCORE_STATE)returnValue);

				//	�^�[�Q�b�g����
				buffTarget->Dissappear();

				//	���̉ԉ΂Ƃ̓����蔻��ֈڍs
				break;
			}
		}
	}

	/*for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	�ԉ΂̏��擾
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		//	�j��
		buffFireworks->burn(0.0f, 0.0f);
	}*/
}
//==============================================================================
// Brief  : �ԉ΂Ɖԉ΂̓����蔻�菈��
//==============================================================================
void SceneGame::collision_fireworks_fireworks()
{
	float hitPosLength = 0.0f;

	//	���݂���ԉ΂̐������[�v
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	�ԉ΂̏��擾
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		//	�ԉ΂̈ʒu���擾
		D3DXVECTOR3 buffFireworksPos = buffFireworks->getPosition();

		//	���݂���ԉ΂̐��{�P�`�ő吔�����[�v
		for(int fireworksCount2 = fireworksCount + 1;fireworksCount2 < fireworksTableIndex;fireworksCount2++)
		{
			Fireworks* buffFireworks2 = managerFireworks->getFireworks(fireworksTable[fireworksCount2]);
			if(buffFireworks2->IsBurnFlag())
				continue;

			//	�ԉ΂̈ʒu���擾
			D3DXVECTOR3 buffFireworksPos2 = buffFireworks2->getPosition();
			
			float hitPosLength;

			//	�����蔻��
			if(hitCheckPointCircle(buffFireworksPos, buffFireworksPos2, fire_fire_collisionSize, &hitPosLength) == true)
			{
				//	�j��
				buffFireworks->burn2();
				buffFireworks2->burn2();

				AddGage(ADD_20);

				//	���̉ԉ΂Ƃ̓����蔻��ֈڍs
				break;
			}
		}
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

