//==============================================================================
//
// File   : Fireworks.cpp
// Brief  : �ԉ΃I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Fireworks.h"
#include "FireworksState.h"
#include "../../system/point/ManagerPoint.h"
#include "../../system/point/PointMain.h"
#include "../../system/ManagerFireworks.h"
#include "../fire/Fire.h"
#include "../../framework/radianTable/radianTable.h"
#include "../../framework/light/ManagerLight.h"
#include "../../framework/light/LightPoint.h"
#include "../../framework/develop/DebugProc.h"
#include "../../framework/develop/DebugMeasure.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
//	�X�e�[�g�e�[�u��
FireworksState** Fireworks::ppState_ = nullptr;

static const int bigFireFirstSpeed = 10;
static const int fireBGExistTime = 50;
static const float fireBGAddSize = 5.0f;

static int createFireNum = 0;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Fireworks::Fireworks( void )
{
	// �N���X���̏���������
	InitializeSelf();

	//	�ΉԐ���
	param.fire = new Fire[FIRE_MAX * SMALL_FIREWORKS_MAX];
	param.smallFire = new Fire[FIRE_MAX * SMALL_FIREWORKS_MAX];
}
//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Fireworks::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	param.managerPoint = nullptr;
	param.pos = D3DXVECTOR3(createFireNum * 10.0f, 0.0f, 0.0f);
	param.setPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for(int count = 0;count < SMALL_FIREWORKS_MAX;count++)
		param.posOld[count] = D3DXVECTOR3(0.0f, -100.0f, 0.0f);

	param.rot = 0.0f;
	param.rotSpeed = 0.0f;
	param.speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = false;
	param.disappear = 0;
	param.appear = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	lightPoint = nullptr;

	indexState = 0;
	D3DXMatrixIdentity(&param.matrix);
	D3DXMatrixIdentity(&param.invViewMatrix);
}
//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Fireworks::~Fireworks( void )
{
	// �I������
	Finalize();
}
//==============================================================================
// Brief  : �X�e�[�g�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : FireworksState** ppState				: �X�e�[�g�e�[�u��
//==============================================================================
void Fireworks::SetState( FireworksState** ppState )
{
	// �X�e�[�g�e�[�u���̐ݒ�
	ppState_ = ppState;
}
//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
//==============================================================================
int Fireworks::Set(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _speed,
	float _rot,
	float _rotSpeed )
{
	//	�ϐ��̕ۑ��Ə�����
	param.managerPoint = _managerPoint;
	param.pos = _pos;
	param.matRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.speed = _speed;
	param.rot = _rot;
	param.rotSpeed = _rotSpeed;

	param.enable = true;
	param.burnFlag = false;
	param.disappear = 0;
	param.fireMax = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	indexState = _indexState;

	if(lightPoint == nullptr)
	{
		lightPoint = managerLight->GetLightPoint();
		lightPoint->SetDiffuse(1.0f, 0.0f, 1.0f);
		lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
		lightPoint->SetAttemuation(0.00f, 0.0006f, 0.00006f);
	}
	lightPoint->SetIsEnable(true);

	//	�X�V�֐��ݒ�
	fpUpdate = &Fireworks::NormalUpdate;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Fireworks::Finalize( void )
{
	if(lightPoint != nullptr)
		lightPoint->Release();

	lightPoint = nullptr;

	delete[] param.smallFire;
	delete[] param.fire;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}
//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Fireworks::Update( void )
{
	MeasureTime("fireworksUpdate");

	//	�ݒ肳�ꂽ�X�V�֐���
	(this->*fpUpdate)();

	lightPoint->SetPosition(param.setPos.x, param.setPos.y, param.setPos.z);
}
//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Fireworks::NormalUpdate( void )
{
	//	�X�e�[�g���̍X�V������
	ppState_[indexState]->Update(this);
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Fireworks::BurnUpdate( void )
{
	int buffCount = 0;

	for(int count = 0;count < param.fireMax;count++)
	{
		if(!param.fire[count].IsEnable())
		{
			buffCount++;
			continue;
		}

		param.fire[count].setInvViewMatrix(param.invViewMatrix);
		param.smallFire[count].setInvViewMatrix(param.invViewMatrix);
		param.fire[count].Update();
		param.smallFire[count].Update();
	}

	PrintDebug( _T( "\ncountFire:Burn1 = %d\n"), param.fireMax - buffCount );

	if(buffCount == param.fireMax)
	{
		param.enable = false;
		lightPoint->SetIsEnable(false);
	}
}
//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Fireworks::Burn2Update( void )
{
	int buffCount = 0;

	for(int count = 0;count < param.fireMax * param.setSmallFireIndex;count++)
	{
		if(!param.fire[count].IsEnable())
		{
			buffCount++;
			continue;
		}

		param.fire[count].setInvViewMatrix(param.invViewMatrix);
		param.smallFire[count].setInvViewMatrix(param.invViewMatrix);
		param.fire[count].Update();
		param.smallFire[count].Update();
	}

	PrintDebug( _T( "\ncountFire:Burn2 = %d\n"), param.fireMax * SMALL_FIREWORKS_MAX - buffCount );

	if(buffCount == param.fireMax * SMALL_FIREWORKS_MAX)
	{
		param.enable = false;
		lightPoint->SetIsEnable(false);
	}
}

//==============================================================================
// Brief  : �ԉ΂̔�������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Fireworks::burn(
	float _hitCheckOffset,
	float _hitPosLength)
{
	//	�J�����̋t�s��������āA��Ɉ��̏ꏊ�ɏo��悤�ɂ��鏈��
	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &param.pos, &param.invViewMatrix);
	param.setPos.x = setPos.x;
	param.setPos.y = setPos.y;
	param.setPos.z = setPos.z;

	//	�ԉ΂̐��ɉ������A�P�̉ΉԂ̊p�x�Ԋu
	float buffValue = 0.0f;

	//	�ΉԂ̍ő吔
	float fireSize;

	//	��
	if(_hitPosLength <= (_hitCheckOffset * 0.1f))
	{
		param.fireMax = FIRE_MAX;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 15.0f;
	}
	//	��
	else if(_hitPosLength <= (_hitCheckOffset * 0.3f))
	{
		param.fireMax = FIRE_MAX / 2;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 30.0f;
	}
	//	�D
	else
	{
		param.fireMax = FIRE_MAX / 3;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 45.0f;
	}



	//	�ԉ΂̔w�i�p����
	param.managerPoint->Add(
		fireBGExistTime,
		param.setPos,
		D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f),
		fireSize,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.02f ),
		fireBGAddSize,
		PointMain::STATE_ADD
		);

	//	�ΉԂ̐��������[�v
	for(int count = 0;count < param.fireMax;count++)
	{
		//	�X�s�[�h��sin cos�Ōv�Z
		float speedX = CRadianTable::mySinf((buffValue * count) + ((rand() % (int)buffValue) + (rand() % (int)buffValue)) * 0.5f);
		float speedY = CRadianTable::myCosf((buffValue * count) + ((rand() % (int)buffValue) + (rand() % (int)buffValue)) * 0.5f);

		//	���[�J�����_���W���v�Z
		D3DXVECTOR3 buffSetPos = D3DXVECTOR3(param.pos.x + speedX, param.pos.y + speedY, param.pos.z);

		//	�傫���ΉԐ���
		param.fire[count].Set(
			Fire::STATE_BIG,
			param.managerPoint,
			buffSetPos,
			D3DXVECTOR3((speedX * (float)(rand() % bigFireFirstSpeed) * 0.1f),
						(speedY * (float)(rand() % bigFireFirstSpeed) * 0.1f),
						0.0f),
			D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f));


		//	�������ΉԐ���
		param.smallFire[count].Set(
			Fire::STATE_SMALL,
			param.managerPoint,
			buffSetPos,
			D3DXVECTOR3((speedX * (float)(rand() % bigFireFirstSpeed) * 0.13f),
						(speedY * (float)(rand() % bigFireFirstSpeed) * 0.13f),
						0.0f),
			D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f));
	}



	//	�X�V�֐��ݒ�
	fpUpdate = &Fireworks::BurnUpdate;

	//	�j��t���OON
	param.burnFlag = true;
}

//==============================================================================
// Brief  : �ԉ΂̔�������(�\���E�OVer)
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Fireworks::burn2()
{
	for(int smallFireCount = 0;smallFireCount < param.setSmallFireIndex;smallFireCount++)
	{
		//	�J�����̋t�s��������āA��Ɉ��̏ꏊ�ɏo��悤�ɂ��鏈��
		D3DXVECTOR4 setPos;
		D3DXVECTOR3 buffPos = param.posOld[smallFireCount];
		D3DXVec3Transform(&setPos, &buffPos, &param.invViewMatrix);
		param.setPos.x = setPos.x;
		param.setPos.y = setPos.y;
		param.setPos.z = setPos.z;

		//	�ԉ΂̐��ɉ������A�P�̉ΉԂ̊p�x�Ԋu
		float buffValue = 0.0f;

		//	�ΉԂ̍ő吔
		float fireSize;


		//	�����I�ɗD�ɐݒ�
		param.fireMax = FIRE_MAX;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 15.0f;


		//	�ԉ΂̔w�i�p����
		param.managerPoint->Add(
			fireBGExistTime,
			param.setPos,
			D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f),
			fireSize,
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.02f ),
			fireBGAddSize,
			PointMain::STATE_ADD
			);


		//	�ΉԂ̐��������[�v
		for(int count = 0;count < param.fireMax;count++)
		{
			//	�X�s�[�h��sin cos�Ōv�Z
			float speedX = CRadianTable::mySinf((buffValue * count) + ((rand() % (int)buffValue) + (rand() % (int)buffValue)) * 0.5f);
			float speedY = CRadianTable::myCosf((buffValue * count) + ((rand() % (int)buffValue) + (rand() % (int)buffValue)) * 0.5f);

			//	���[�J�����_���W���v�Z
			D3DXVECTOR3 buffSetPos = D3DXVECTOR3(buffPos.x + speedX, buffPos.y + speedY, buffPos.z);

			//	�傫���ΉԐ���
			param.fire[count + (FIRE_MAX * smallFireCount)].Set(
				Fire::STATE_BIG,
				param.managerPoint,
				buffSetPos,
				D3DXVECTOR3((speedX * (float)(rand() % bigFireFirstSpeed) * 0.1f),
							(speedY * (float)(rand() % bigFireFirstSpeed) * 0.1f),
							0.0f),
				D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f));


			//	�������ΉԐ���
			param.smallFire[count + (FIRE_MAX * smallFireCount)].Set(
				Fire::STATE_SMALL,
				param.managerPoint,
				buffSetPos,
				D3DXVECTOR3((speedX * (float)(rand() % bigFireFirstSpeed) * 0.13f),
							(speedY * (float)(rand() % bigFireFirstSpeed) * 0.13f),
							0.0f),
				D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f));
		}
	}


	//	�X�V�֐��ݒ�
	fpUpdate = &Fireworks::Burn2Update;

	//	�j��t���OON
	param.burnFlag = true;
}

void Fireworks::setManagerLight(ManagerLight* _managerLight)
{
	managerLight = _managerLight;
}
