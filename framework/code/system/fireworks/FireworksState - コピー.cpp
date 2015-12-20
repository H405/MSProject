//==============================================================================
//
// File   : FireworksState.cpp
// Brief  : �ԉ΂̃X�e�[�g
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "FireworksState.h"
#include "Fireworks.h"
#include "../../system/point/ManagerPoint.h"
#include "../../system/point/PointMain.h"
#include "../../framework/radianTable/radianTable.h"
#include "../../framework/light/LightPoint.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define RANDAM(value) (float)((rand() % value) - (rand() % value))
#define FIRE_APPEAR_RANDAM (RANDAM(100) * 0.01f)

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//	��������ΉԂ̐�
static const int fireNum[] =
{
	FIRE_MAX,	//	�D
	FIRE_MAX / 2,	//	��
	FIRE_MAX / 4	//	��
};

//	��������ԉ΃G�t�F�N�g�̑傫��
static const float effectSize = 20.0f;

//	��������傫�ȉԉ΃G�t�F�N�g�̑傫��
static const float effectBigSize = 30.0f;

//	��������ԉ΃G�t�F�N�g�̏�����܂ł̎���
static const TIME effectDisappear = 30;

//	��������ԉ΃G�t�F�N�g�����������Ԋu
static const TIME effectAppear = 3;

//	��������ԉ΃G�t�F�N�g�̑傫���̍���
static const float effectDifferenceSize = -effectSize / effectDisappear;

//	��������ԉ΃G�t�F�N�g�̑傫���̍���
static const float effectDifferenceBigSize = (-effectBigSize / DELETECOUNT_MAX) * 0.5f;

//	�O�̈ʒu���擾���鎞��
static const int setPosOldMax = 20;

//	�����l�̕ω���
static const float differensAlpha = -1.0f / effectDisappear;

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Fireworks* pFireworks						: �Ώ�
//==============================================================================
void FireworksState::Update( Fireworks* _fireworks )
{
}


//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Fireworks* pFireworks						: �Ώ�
//==============================================================================
void FireworksStateRightSP::Update( Fireworks* _fireworks )
{
	//	�p�����[�^�փA�N�Z�X
	FIREWORKS_PARAM* param = _fireworks->getParam();

	//	�ԉΈړ��p�s�񏉊���
	D3DXMatrixIdentity(&param->matrix);

	//	�x�W�F�Ȑ��̌v�Z
	float buffTime = (1.0f / (float)DELETECOUNT_MAX) * (float)param->disappear;
	D3DXVECTOR3 f1 = (1.0f - buffTime) * (1.0f - buffTime) * param->startPos;
	D3DXVECTOR3 f2 = (1.0f - buffTime) * buffTime * 2.0f * param->buffPos1;
	D3DXVECTOR3 f3 = buffTime * buffTime * param->endPos;
	param->pos = f1 + f2 + f3;


	//	�����Ă��鎞�Ԃ��v�����āA�Z�b�g���鎞�ԂɂȂ�����
	param->setPosOld++;
	if(param->setPosOld == setPosOldMax)
	{
		//	�Z�b�g����������t��������
		if(param->setSmallFireIndex == SMALL_FIREWORKS_MAX)
		{
			//	�ꎞ�ϐ���posOld����
			D3DXVECTOR3 buff[SMALL_FIREWORKS_MAX];
			for(int count = 0;count < SMALL_FIREWORKS_MAX;count++)
				buff[count] = param->posOld[count];

			//	�ŐV�̏����X�V
			param->posOld[param->setSmallFireIndex - 1] = param->pos;

			//	�\�[�g����
			for(int count = 0;count < param->setSmallFireIndex - 1;count++)
				param->posOld[count] = buff[count + 1];
		}
		//	�Z�b�g����������t����Ȃ�������
		else
		{
			//	�ʒu���Z�b�g
			param->posOld[param->setSmallFireIndex] = param->pos;

			//	�C���f�b�N�X���C���N�������g
			param->setSmallFireIndex++;
		}

		//	�J�E���^������
		param->setPosOld = 0;
	}



	//	�s��ňʒu���R�����I�ɉ�]
	D3DXVECTOR4 buffPos;
	D3DXVECTOR3 buffPos3(param->pos.x + FIRE_APPEAR_RANDAM, param->pos.y + FIRE_APPEAR_RANDAM, param->pos.z + FIRE_APPEAR_RANDAM);
	D3DXVec3Transform(&buffPos, &buffPos3, &param->matrix);
	buffPos3.x = buffPos.x;
	buffPos3.y = buffPos.y;
	buffPos3.z = buffPos.z;


	//	�J�����̋t�s��������āA��Ɉ��̏ꏊ�ɏo��悤�ɂ��鏈��
	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &buffPos3, &param->invViewMatrix);
	param->setPos.x = setPos.x;
	param->setPos.y = setPos.y;
	param->setPos.z = setPos.z;



	//	�G�t�F�N�g����
	param->managerPoint->Add(
		effectDisappear,
		D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
		param->color,
		effectSize,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, differensAlpha ),
		effectDifferenceSize,
		PointMain::STATE_ADD
		);

	//	���ŃJ�E���^�X�V
	param->disappear++;
	if(param->disappear >= DELETECOUNT_MAX)
	{
		param->enable = false;
		param->burnFlag = true;
		param->lightPoint->SetIsEnable(false);
	}

	//	�����J�E���^�X�V
	param->appear++;
	if(param->appear <= effectAppear)
	{
		//	�G�t�F�N�g����
		param->managerPoint->Add(
			1,
			D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			effectBigSize,
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, 0.1f ),
			effectDifferenceBigSize,
			PointMain::STATE_ADD
			);
	}
	else
		param->appear = 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Fireworks* pFireworks						: �Ώ�
//==============================================================================
void FireworksStateLeftSP::Update( Fireworks* _fireworks )
{
	//	�p�����[�^�փA�N�Z�X
	FIREWORKS_PARAM* param = _fireworks->getParam();


	//	�ԉΈړ��p�s�񏉊���
	D3DXMatrixIdentity(&param->matrix);

	//	��]
	D3DXMatrixRotationYawPitchRoll(
		&param->matrix,
		param->matRot.y,
		param->matRot.x,
		param->matRot.z);


	//	���̌����Ƃ����Ƃ��̈ړ������C������
	param->rot += param->rotSpeed;

	//	�ʒu�����Z(90�x���^�������オ��Ƃ���)
	param->pos.x += CRadianTable::myCosf((double)param->rot) * param->speed.x;
	param->pos.y += CRadianTable::mySinf((double)param->rot) * param->speed.y + 1.0f;
	param->pos.z += param->speed.z;



	//	�����Ă��鎞�Ԃ��v�����āA�Z�b�g���鎞�ԂɂȂ�����
	param->setPosOld++;
	if(param->setPosOld == setPosOldMax)
	{
		//	�Z�b�g����������t��������
		if(param->setSmallFireIndex == SMALL_FIREWORKS_MAX)
		{
			//	�ꎞ�ϐ���posOld����
			D3DXVECTOR3 buff[SMALL_FIREWORKS_MAX];
			for(int count = 0;count < SMALL_FIREWORKS_MAX;count++)
				buff[count] = param->posOld[count];

			//	�ŐV�̏����X�V
			param->posOld[param->setSmallFireIndex - 1] = param->pos;

			//	�\�[�g����
			for(int count = 0;count < param->setSmallFireIndex - 1;count++)
				param->posOld[count] = buff[count + 1];
		}
		//	�Z�b�g����������t����Ȃ�������
		else
		{
			//	�ʒu���Z�b�g
			param->posOld[param->setSmallFireIndex] = param->pos;

			//	�C���f�b�N�X���C���N�������g
			param->setSmallFireIndex++;
		}

		//	�J�E���^������
		param->setPosOld = 0;
	}



	//	�s��ňʒu���R�����I�ɉ�]
	D3DXVECTOR4 buffPos;
	D3DXVECTOR3 buffPos3(param->pos.x + FIRE_APPEAR_RANDAM, param->pos.y + FIRE_APPEAR_RANDAM, param->pos.z + FIRE_APPEAR_RANDAM);
	D3DXVec3Transform(&buffPos, &buffPos3, &param->matrix);
	buffPos3.x = buffPos.x;
	buffPos3.y = buffPos.y;
	buffPos3.z = buffPos.z;


	//	�J�����̋t�s��������āA��Ɉ��̏ꏊ�ɏo��悤�ɂ��鏈��
	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &buffPos3, &param->invViewMatrix);
	param->setPos.x = setPos.x;
	param->setPos.y = setPos.y;
	param->setPos.z = setPos.z;



	//	�G�t�F�N�g����
	param->managerPoint->Add(
		effectDisappear,
		D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
		D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		effectSize,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, differensAlpha ),
		effectDifferenceSize,
		PointMain::STATE_ADD
		);

	//	���ŃJ�E���^�X�V
	param->disappear++;
	if(param->disappear >= DELETECOUNT_MAX)
	{
		param->enable = false;
		param->burnFlag = true;
		param->lightPoint->SetIsEnable(false);
	}

	//	�����J�E���^�X�V
	param->appear++;
	if(param->appear <= effectAppear)
	{
		//	�G�t�F�N�g����
		param->managerPoint->Add(
			1,
			D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
			D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
			effectBigSize,
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, differensAlpha ),
			effectDifferenceBigSize,
			PointMain::STATE_ADD
			);
	}
	else
		param->appear = 0;
}










//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Fireworks* pFireworks						: �Ώ�
//==============================================================================
void FireworksStateRight::Update( Fireworks* _fireworks )
{
	//	�p�����[�^�փA�N�Z�X
	FIREWORKS_PARAM* param = _fireworks->getParam();


	//	�ԉΈړ��p�s�񏉊���
	D3DXMatrixIdentity(&param->matrix);

	//	��]
	D3DXMatrixRotationYawPitchRoll(
		&param->matrix,
		param->matRot.y,
		param->matRot.x,
		param->matRot.z);


	//	���̌����Ƃ����Ƃ��̈ړ������C������
	param->rot += param->rotSpeed;


	//	�ʒu�����Z(90�x���^�������オ��Ƃ���)
	param->pos.x += CRadianTable::myCosf((double)param->rot) * param->speed.x;
	param->pos.y += CRadianTable::mySinf((double)param->rot) * param->speed.y + 1.0f;
	param->pos.z += param->speed.z;

	//	�����Ă��鎞�Ԃ��v�����āA�Z�b�g���鎞�ԂɂȂ�����
	param->setPosOld++;
	if(param->setPosOld == setPosOldMax)
	{
		//	�Z�b�g����������t��������
		if(param->setSmallFireIndex == SMALL_FIREWORKS_MAX)
		{
			//	�ꎞ�ϐ���posOld����
			D3DXVECTOR3 buff[SMALL_FIREWORKS_MAX];
			for(int count = 0;count < SMALL_FIREWORKS_MAX;count++)
				buff[count] = param->posOld[count];

			//	�ŐV�̏����X�V
			param->posOld[param->setSmallFireIndex - 1] = param->pos;

			//	�\�[�g����
			for(int count = 0;count < param->setSmallFireIndex - 1;count++)
				param->posOld[count] = buff[count + 1];
		}
		//	�Z�b�g����������t����Ȃ�������
		else
		{
			//	�ʒu���Z�b�g
			param->posOld[param->setSmallFireIndex] = param->pos;

			//	�C���f�b�N�X���C���N�������g
			param->setSmallFireIndex++;
		}

		//	�J�E���^������
		param->setPosOld = 0;
	}


	//	�s��ňʒu���R�����I�ɉ�]
	D3DXVECTOR4 buffPos;
	D3DXVECTOR3 buffPos3(param->pos.x + FIRE_APPEAR_RANDAM, param->pos.y + FIRE_APPEAR_RANDAM, param->pos.z + FIRE_APPEAR_RANDAM);
	D3DXVec3Transform(&buffPos, &buffPos3, &param->matrix);
	buffPos3.x = buffPos.x;
	buffPos3.y = buffPos.y;
	buffPos3.z = buffPos.z;


	//	�J�����̋t�s��������āA��Ɉ��̏ꏊ�ɏo��悤�ɂ��鏈��
	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &buffPos3, &param->invViewMatrix);
	param->setPos.x = setPos.x;
	param->setPos.y = setPos.y;
	param->setPos.z = setPos.z;



	//	�G�t�F�N�g����
	param->managerPoint->Add(
		effectDisappear,
		D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
		D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		effectSize,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, differensAlpha),
		effectDifferenceSize,
		PointMain::STATE_ADD
		);

	//	���ŃJ�E���^�X�V
	param->disappear++;
	if(param->disappear >= DELETECOUNT_MAX)
	{
		param->enable = false;
		param->burnFlag = true;
		param->lightPoint->SetIsEnable(false);
	}

	//	�����J�E���^�X�V
	param->appear++;
	if(param->appear <= effectAppear)
	{
		//	�G�t�F�N�g����
		param->managerPoint->Add(
			1,
			D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
			D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
			effectBigSize,
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, differensAlpha ),
			effectDifferenceBigSize,
			PointMain::STATE_ADD
			);
	}
	else
		param->appear = 0;
}
//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Fireworks* pFireworks						: �Ώ�
//==============================================================================
void FireworksStateLeft::Update( Fireworks* _fireworks )
{
	//	�p�����[�^�փA�N�Z�X
	FIREWORKS_PARAM* param = _fireworks->getParam();


	//	�ԉΈړ��p�s�񏉊���
	D3DXMatrixIdentity(&param->matrix);

	//	��]
	D3DXMatrixRotationYawPitchRoll(
		&param->matrix,
		param->matRot.y,
		param->matRot.x,
		param->matRot.z);


	//	���̌����Ƃ����Ƃ��̈ړ������C������
	param->rot += param->rotSpeed;

	//	�ʒu�����Z(90�x���^�������オ��Ƃ���)
	param->pos.x += CRadianTable::myCosf((double)param->rot) * param->speed.x;
	param->pos.y += CRadianTable::mySinf((double)param->rot) * param->speed.y + 1.0f;
	param->pos.z += param->speed.z;



	//	�����Ă��鎞�Ԃ��v�����āA�Z�b�g���鎞�ԂɂȂ�����
	param->setPosOld++;
	if(param->setPosOld == setPosOldMax)
	{
		//	�Z�b�g����������t��������
		if(param->setSmallFireIndex == SMALL_FIREWORKS_MAX)
		{
			//	�ꎞ�ϐ���posOld����
			D3DXVECTOR3 buff[SMALL_FIREWORKS_MAX];
			for(int count = 0;count < SMALL_FIREWORKS_MAX;count++)
				buff[count] = param->posOld[count];

			//	�ŐV�̏����X�V
			param->posOld[param->setSmallFireIndex - 1] = param->pos;

			//	�\�[�g����
			for(int count = 0;count < param->setSmallFireIndex - 1;count++)
				param->posOld[count] = buff[count + 1];
		}
		//	�Z�b�g����������t����Ȃ�������
		else
		{
			//	�ʒu���Z�b�g
			param->posOld[param->setSmallFireIndex] = param->pos;

			//	�C���f�b�N�X���C���N�������g
			param->setSmallFireIndex++;
		}

		//	�J�E���^������
		param->setPosOld = 0;
	}



	//	�s��ňʒu���R�����I�ɉ�]
	D3DXVECTOR4 buffPos;
	D3DXVECTOR3 buffPos3(param->pos.x + FIRE_APPEAR_RANDAM, param->pos.y + FIRE_APPEAR_RANDAM, param->pos.z + FIRE_APPEAR_RANDAM);
	D3DXVec3Transform(&buffPos, &buffPos3, &param->matrix);
	buffPos3.x = buffPos.x;
	buffPos3.y = buffPos.y;
	buffPos3.z = buffPos.z;


	//	�J�����̋t�s��������āA��Ɉ��̏ꏊ�ɏo��悤�ɂ��鏈��
	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &buffPos3, &param->invViewMatrix);
	param->setPos.x = setPos.x;
	param->setPos.y = setPos.y;
	param->setPos.z = setPos.z;



	//	�G�t�F�N�g����
	param->managerPoint->Add(
		effectDisappear,
		D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
		D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		effectSize,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, differensAlpha ),
		effectDifferenceSize,
		PointMain::STATE_ADD
		);

	//	���ŃJ�E���^�X�V
	param->disappear++;
	if(param->disappear >= DELETECOUNT_MAX)
	{
		param->enable = false;
		param->burnFlag = true;
		param->lightPoint->SetIsEnable(false);
	}

	//	�����J�E���^�X�V
	param->appear++;
	if(param->appear <= effectAppear)
	{
		//	�G�t�F�N�g����
		param->managerPoint->Add(
			1,
			D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
			D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
			effectBigSize,
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, differensAlpha ),
			effectDifferenceBigSize,
			PointMain::STATE_ADD
			);
	}
	else
		param->appear = 0;
}
