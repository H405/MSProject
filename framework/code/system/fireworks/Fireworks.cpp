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
#include "../../scene/SceneGame.h"
#include "../../framework/system/Utility.h"
#include "../target/Target.h"

#include "../SceneArgumentMain.h"
#include "../../framework/resource/ManagerSound.h"
#include "../../framework/resource/Sound.h"

#include <stdio.h>

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

static const D3DXVECTOR3 attenuationValue = D3DXVECTOR3(0.0f, 0.0028f, 0.0000005f);

static const TIME compAppear = (int)(DELETECOUNT_MAX * 0.9f);
static const TIME compDisppear = (int)(DELETECOUNT_MAX);


static const TIME compLaunchAppear = (int)(DELETECOUNT_MAX * 0.5f);
static const TIME compLaunchDisppear = (int)(DELETECOUNT_MAX);

static const float diffRotMul = 16.0f;

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

	burnSoundIndex = -1;
	launchSoundIndex = -1;
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

	param.lightPoint = nullptr;

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

	if(param.lightPoint == nullptr)
	{
		param.lightPoint = managerLight->GetLightPoint();
		param.lightPoint->SetDiffuse(1.0f, 1.0f, 0.5f);
		param.lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
	}
	param.lightPoint->SetAttenuation(0.0f, 0.0028f, 0.00005f);
	//param.lightPoint->SetIsEnable(true);


	//	���Đ�
	burnSoundIndex = -1;
	launchSoundIndex = -1;
	launchSoundIndex = param.launchSound->Play();


	//	�X�V�֐��ݒ�
	fpUpdate = &Fireworks::NormalUpdate;

	// ����I��
	return 0;
}
//==============================================================================
// Brief  : �ԉ΂����鏈��(wii�����R���̏��ɉ�����)
// Return : int									: ���s����
//==============================================================================
int Fireworks::Set(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _diffRot,
	COLOR_STATE _colorState)
{
	//	�ϐ��̕ۑ��Ə�����
	param.managerPoint = _managerPoint;
	param.pos = _pos;
	param.matRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = true;
	param.burnFlag = false;
	param.disappear = 0;
	param.fireMax = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	//	�F���
	param.colorState = _colorState;
	if(param.colorState == COLOR_STATE_R)
		param.color = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
	else if(param.colorState == COLOR_STATE_G)
		param.color = D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f);
	else if(param.colorState == COLOR_STATE_B)
		param.color = D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_W)
		param.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_S)
		param.color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

	indexState = _indexState;

	if(param.lightPoint == nullptr)
	{
		param.lightPoint = managerLight->GetLightPoint();
		param.lightPoint->SetDiffuse(param.color);
		param.lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
	}
	param.lightPoint->SetDiffuse(param.color);
	param.lightPoint->SetAttenuation(0.0f, 0.00028f, 0.0000005f);
	param.lightPoint->SetIsEnable(true);

	//	���Đ�
	burnSoundIndex = -1;
	launchSoundIndex = -1;
	launchSoundIndex = param.launchSound->Play();

	//	�X�V�֐��ݒ�
	fpUpdate = &Fireworks::NormalUpdate;



	//	end�̏���l�́Ay��200���炢�Ax��-200�`200���炢�H
	param.startPos = _pos;
	//param.buffPos1 = D3DXVECTOR3(_pos.x - (_diffRot.z * (diffRotMul * 0.25f)), 450.0f, _pos.z + 2000.0f);
	//param.endPos = D3DXVECTOR3(_pos.x - (_diffRot.z * diffRotMul), 650.0f, _pos.z + 4500.0f);
	param.buffPos1 = D3DXVECTOR3(_pos.x - (_diffRot.z * (diffRotMul * 0.3f)), 140.0f, _pos.z);
	param.endPos = D3DXVECTOR3(_pos.x - (_diffRot.z * diffRotMul), 200.0f, _pos.z);

	param.count = 0;

	// ����I��
	return 0;
}
//==============================================================================
// Brief  : �ԉ΂����鏈��(�R���{���ɉ�����)
// Return : int									: ���s����
//==============================================================================
int Fireworks::SetSP(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _diffRot,
	COLOR_STATE _colorState)
{
	//	�ϐ��̕ۑ��Ə�����
	param.managerPoint = _managerPoint;
	param.pos = _pos;
	param.matRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = true;
	param.burnFlag = false;
	param.disappear = 0;
	param.fireMax = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	//	�F���
	param.colorState = _colorState;
	if(param.colorState == COLOR_STATE_R)
		param.color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_G)
		param.color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_B)
		param.color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_W)
		param.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_S)
		param.color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

	indexState = _indexState;

	if(param.lightPoint == nullptr)
	{
		param.lightPoint = managerLight->GetLightPoint();
		param.lightPoint->SetDiffuse(param.color);
		param.lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
	}
	param.lightPoint->SetDiffuse(param.color);
	param.lightPoint->SetAttenuation(0.0f, 0.0028f, 0.0000005f);
	param.lightPoint->SetIsEnable(true);

	//	���Đ�
	burnSoundIndex = -1;
	launchSoundIndex = -1;
	launchSoundIndex = param.launchSound->Play();

	//	�X�V�֐��ݒ�
	fpUpdate = &Fireworks::NormalUpdate;



	//	end�̏���l�́Ay��200���炢�Ax��-200�`200���炢�H
	param.startPos = _pos;
	param.buffPos1 = D3DXVECTOR3(_pos.x - (_diffRot.z * (diffRotMul * 0.25f)), 100.0f, _pos.z);
	param.endPos = D3DXVECTOR3(_pos.x - (_diffRot.z * diffRotMul), 130.0f, _pos.z);

	param.count = 0;

	// ����I��
	return 0;
}
//==============================================================================
// Brief  : �ԉ΂����鏈��(�^�[�Q�b�g�֌�������)
// Return : int									: ���s����
//==============================================================================
int Fireworks::Set(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _diffRot,
	Target* _target)
{
	//	�ϐ��̕ۑ��Ə�����
	param.managerPoint = _managerPoint;
	param.pos = _pos;
	param.matRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = true;
	param.burnFlag = false;
	param.disappear = 0;
	param.fireMax = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	//	�F���
	param.colorState = _target->getColorState();
	if(param.colorState == COLOR_STATE_R)
		param.color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_G)
		param.color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_B)
		param.color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_W)
		param.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_S)
		param.color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

	indexState = _indexState;

	if(param.lightPoint == nullptr)
	{
		param.lightPoint = managerLight->GetLightPoint();
		param.lightPoint->SetDiffuse(param.color);
		param.lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
	}
	param.lightPoint->SetDiffuse(param.color);
	param.lightPoint->SetAttenuation(0.0f, 0.0028f, 0.0000005f);
	param.lightPoint->SetIsEnable(true);

	//	���Đ�
	burnSoundIndex = -1;
	launchSoundIndex = -1;
	launchSoundIndex = param.launchSound->Play();

	//	�X�V�֐��ݒ�
	fpUpdate = &Fireworks::NormalUpdate;



	//	end�̏���l�́Ay��200���炢�Ax��-200�`200���炢�H
	param.startPos = _pos;
	param.buffPos1 = D3DXVECTOR3(_pos.x + (_target->getPosition().x - _pos.x) * 0.3f, _pos.y + (_target->getPosition().y - _pos.y) * 0.7f, _pos.z);
	param.endPos = D3DXVECTOR3(_target->getPosition().x, _target->getPosition().y, _pos.z);

	param.count = 0;

	// ����I��
	return 0;
}
// Return : int									: ���s����
//==============================================================================
int Fireworks::SetW(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _diffRot,
	Target* _target)
{
	//	�ϐ��̕ۑ��Ə�����
	param.managerPoint = _managerPoint;
	param.pos = _pos;
	param.matRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = true;
	param.burnFlag = false;
	param.disappear = 0;
	param.fireMax = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	//	�F���
	param.colorState = (COLOR_STATE)(rand() % COLOR_STATE_W);
	if(param.colorState == COLOR_STATE_R)
		param.color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_G)
		param.color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_B)
		param.color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_W)
		param.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_S)
		param.color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

	indexState = _indexState;

	if(param.lightPoint == nullptr)
	{
		param.lightPoint = managerLight->GetLightPoint();
		param.lightPoint->SetDiffuse(param.color);
		param.lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
	}
	param.lightPoint->SetDiffuse(param.color);
	param.lightPoint->SetAttenuation(0.0f, 0.0028f, 0.0000005f);
	param.lightPoint->SetIsEnable(true);

	//	���Đ�
	burnSoundIndex = -1;
	launchSoundIndex = -1;
	launchSoundIndex = param.launchSound->Play();

	//	�X�V�֐��ݒ�
	fpUpdate = &Fireworks::NormalUpdate;



	//	end�̏���l�́Ay��200���炢�Ax��-200�`200���炢�H
	param.startPos = _pos;
	param.buffPos1 = D3DXVECTOR3(_pos.x + (_target->getPosition().x - _pos.x) * 0.3f, _pos.y + (_target->getPosition().y - _pos.y) * 0.7f, _pos.z + 250.0f);
	param.endPos = D3DXVECTOR3(_target->getPosition().x, _target->getPosition().y, _pos.z + 500.0f);

	param.count = 0;

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
	//	��
	param.launchSound->Stop(launchSoundIndex);
	param.burnSound->Stop(burnSoundIndex);

	if(param.lightPoint != nullptr)
		param.lightPoint->Release();

	param.lightPoint = nullptr;

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

	param.lightPoint->SetPosition(param.setPos.x, param.setPos.y, param.setPos.z);
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

	//PrintDebug( _T( "\ncountFire:Burn1 = %d\n"), param.fireMax - buffCount );

	if(buffCount == param.fireMax)
	{
		param.enable = false;
		param.lightPoint->SetIsEnable(false);
	}


	// �����̌���
	float	proportion;		// ����
	int counter = param.fire[0].getDeleteCount();

	if( counter < compAppear )
	{
		proportion = Utility::Easing( 0.0f, 1.0f, (float)counter / (float)compAppear);
	}
	else
	{
		proportion = Utility::Easing( 1.0f, 0.0f, (float)(counter - compAppear) / (float)compDisppear);
	}

	// �������̐ݒ�
	D3DXVECTOR3	attenuation;		// ������0.00028f, 0.00000005f     0.0005f, 0.00005f
	attenuation = attenuationValue + D3DXVECTOR3( 0.0f, 0.00028f * proportion, 0.0000005f * proportion );
	//param.lightPoint->SetAttenuation(0.0f, 0.00028f, 0.0000005f);
	param.lightPoint->SetAttenuation( attenuation );
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

	//PrintDebug( _T( "\ncountFire:Burn2 = %d\n"), param.fireMax * SMALL_FIREWORKS_MAX - buffCount );

	if(buffCount == param.fireMax * param.setSmallFireIndex)
	{
		param.enable = false;
		param.lightPoint->SetIsEnable(false);
	}


	// �����̌���
	float	proportion;		// ����
	int counter = param.fire[0].getDeleteCount();

	if( counter < compAppear )
	{
		proportion = Utility::Easing( 0.0f, 1.0f, (float)counter / (float)compAppear);
	}
	else
	{
		proportion = Utility::Easing( 1.0f, 0.0f, (float)(counter - compAppear) / (float)compDisppear);
	}

	// �������̐ݒ�
	D3DXVECTOR3	attenuation;		// ������0.00028f, 0.00000005f     0.0005f, 0.00005f
	attenuation = attenuationValue + D3DXVECTOR3( 0.0f, 0.0028f * proportion, 0.0000005f * proportion );
	param.lightPoint->SetAttenuation( attenuation );
}

//==============================================================================
// Brief  : �ԉ΂̔�������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
int Fireworks::burn(
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

	//	�Ԃ�l
	int returnValue;

	//	�D
	if(_hitPosLength <= (_hitCheckOffset * 0.1f))
	{
		param.fireMax = FIRE_MAX;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 45.0f;

		returnValue = ADD_10;
	}
	//	��
	else if(_hitPosLength <= (_hitCheckOffset * 0.3f))
	{
		param.fireMax = FIRE_MAX / 3;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 15.0f;

		returnValue = ADD_5;
	}
	//	��
	else
	{
		param.fireMax = FIRE_MAX / 6;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 5.0f;

		returnValue = ADD_1;
	}


	//	�ԉ΂̔w�i�p����
	param.managerPoint->Add(
		fireBGExistTime,
		param.setPos,
		param.color,
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
			param.color);


		//	�������ΉԐ���
		param.smallFire[count].Set(
			Fire::STATE_SMALL,
			param.managerPoint,
			buffSetPos,
			D3DXVECTOR3((speedX * (float)(rand() % bigFireFirstSpeed) * 0.13f),
						(speedY * (float)(rand() % bigFireFirstSpeed) * 0.13f),
						0.0f),
			param.color);
	}



	//	�X�V�֐��ݒ�
	fpUpdate = &Fireworks::BurnUpdate;

	//	�j��t���OON
	param.burnFlag = true;

	//	���Đ�
	param.launchSound->Stop(launchSoundIndex);
	burnSoundIndex = param.burnSound->Play();

	return returnValue;
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
			param.color,
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
				param.color);


			//	�������ΉԐ���
			param.smallFire[count + (FIRE_MAX * smallFireCount)].Set(
				Fire::STATE_SMALL,
				param.managerPoint,
				buffSetPos,
				D3DXVECTOR3((speedX * (float)(rand() % bigFireFirstSpeed) * 0.13f),
							(speedY * (float)(rand() % bigFireFirstSpeed) * 0.13f),
							0.0f),
				param.color);
		}
	}


	//	�X�V�֐��ݒ�
	fpUpdate = &Fireworks::Burn2Update;

	//	�j��t���OON
	param.burnFlag = true;

	//	���Đ�
	param.launchSound->Stop(launchSoundIndex);
	burnSoundIndex = param.burnSound->Play();
}

//==============================================================================
// Brief  : �ԉ΂̉���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Fireworks::setSound(Sound* _burnSound, Sound* _launchSound)
{
	param.burnSound = _burnSound;
	param.launchSound = _launchSound;
}

void Fireworks::setManagerLight(ManagerLight* _managerLight)
{
	managerLight = _managerLight;
}
