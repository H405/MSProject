//==============================================================================
//
// File   : FireState.cpp
// Brief  : �ΉԂ̃X�e�[�g
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "FireState.h"
#include "Fire.h"
#include "../../system/ManagerPoint.h"
#include "../../framework/radianTable/radianTable.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define FIRE_MAX (36)
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define DELETECOUNT_MAX (80)
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

//	��������ΉԃG�t�F�N�g�̑傫��
static const float effectSize = 30.0f;
static const float effectSizeSmall = 5.0f;

//	��������ΉԃG�t�F�N�g�̏�����܂ł̎���
static const int effectExistTime = 5;
static const int effectExistTimeRandom = (int)(effectExistTime * 0.9f);

static const int effectExistTimeSmall = 5;
static const int effectExistTimeRandomSmall = (int)(effectExistTime * 0.9f);

//	��������ΉԃG�t�F�N�g�̑傫���̍���
static const float effectDifferenceSize = -0.5f;
static const float effectDifferenceSizeSmall = -0.01f;

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Fire* pFire						: �Ώ�
//==============================================================================
void FireState::Update( Fire* _fireworks )
{
	// ����
	//if( pFire->GetTime() >= pFire->GetTimeExist() )
	//{
	//	pFire->SetIsEnable( false );
	//}
}





//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Fire* pFire						: �Ώ�
//==============================================================================
void FireStateBig::Update( Fire* _fireworks )
{
	FIRE_PARAM* param = _fireworks->getParam();


	param->pos += param->speed;
	param->speed *= 0.99f;


	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &param->pos, &param->invViewMatrix);
	param->setPos.x = setPos.x;
	param->setPos.y = setPos.y;
	param->setPos.z = setPos.z;


	//	�G�t�F�N�g����
	_fireworks->getManagerPoint()->Add(
		effectExistTime + (int)RANDAM(effectExistTimeRandom),
		D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
		param->color,
		effectSize - ((effectSize / DELETECOUNT_MAX) * param->deleteCount),
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.01f ),
		effectDifferenceSize,
		ManagerPoint::STATE_ADD
		);


	//	�J�E���^�X�V
	param->deleteCount++;
	if(param->deleteCount >= DELETECOUNT_MAX)
	{
		param->enable = false;
	}










	/*���@�@�s���������������Ȃ�Ver
	//------------------------------------------------------------
	//	��]�ʉ��Z
	param->rot += param->rotSpeed;

	if(param->rot < 0.0f)
		param->rot = 0.0f;
	else if(param->rot > 180.0f)
	{
		param->rot = 180.0f;
	}

	//	���x�v�Z
	param->speed *= 0.999f;

	//	�ʒu�����Z
	param->offsetPos.x += (CRadianTable::mySinf((double)param->rot) * param->speed.x);
	param->offsetPos.y += (CRadianTable::myCosf((double)param->rot) * param->speed.y);



	for(int count = 0;count < 2;count++)
	{
		//	�ԉΈړ��p�s�񏉊���
		D3DXMatrixIdentity(&param->matrix);

		//	�s��ňʒu���R�����I�ɉ�]
		D3DXVECTOR4 buffPos;
		D3DXVECTOR3 buffPos3(param->offsetPos.x + FIRE_APPEAR_RANDAM, param->offsetPos.y + FIRE_APPEAR_RANDAM, param->offsetPos.z + FIRE_APPEAR_RANDAM);

		//	���s�ړ�
		D3DXMatrixTranslation(
			&param->matrix,
			param->pos.x,
			param->pos.y,
			param->pos.z);

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
		_fireworks->getManagerPoint()->Add(
			effectExistTime + (int)RANDAM(effectExistTimeRandom),
			D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
			D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
			effectSize - ((effectSize / DELETECOUNT_MAX) * param->deleteCount),
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.01f ),
			effectDifferenceSize,
			ManagerPoint::STATE_ADD
			);
	}

	//	�J�E���^�X�V
	param->deleteCount++;
	if(param->deleteCount >= DELETECOUNT_MAX)
	{
		param->enable = false;
	}
	//------------------------------------------------------------



	/*���@�@�s��ł̈ʒu����O
	//------------------------------------------------------------
	//	�p�����[�^�փA�N�Z�X
	FIRE_PARAM* param = _fireworks->getParam();


	//	�ԉΈړ��p�s�񏉊���
	D3DXMatrixIdentity(&param->matrix);

	//	��]
	D3DXMatrixRotationYawPitchRoll(
		&param->matrix,
		param->matRot.y,
		param->matRot.x,
		param->matRot.z);



	//	��]�ʉ��Z.
	param->rot += param->rotSpeed;

	if(param->rot < 0.0f)
		param->rot = 0.0f;
	else if(param->rot > 180.0f)
	{
		param->rot = 180.0f;
		//param->speed.y -= 0.1f;
	}

	//	���x�v�Z
	param->speed *= 0.999f;

	//	�ʒu�����Z
	param->pos.x += (CRadianTable::mySinf((double)param->rot) * param->speed.x);
	param->pos.y += (CRadianTable::myCosf((double)param->rot) * param->speed.y);
	//param->pos.z += param->speed.z;



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
	_fireworks->getManagerPoint()->Add(
		effectExistTime + (int)RANDAM(effectExistTimeRandom),
		D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
		D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		effectSize - ((effectSize / DELETECOUNT_MAX) * param->deleteCount),
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.01f ),
		effectDifferenceSize,
		ManagerPoint::STATE_ADD
		);

	//	�J�E���^�X�V
	param->deleteCount++;
	if(param->deleteCount >= DELETECOUNT_MAX)
	{
		param->enable = false;
	}
	*/
}











//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Fire* pFire						: �Ώ�
//==============================================================================
void FireStateSmall::Update( Fire* _fireworks )
{
	//	�p�����[�^�փA�N�Z�X
	FIRE_PARAM* param = _fireworks->getParam();


	param->pos += param->speed;
	param->speed *= 0.99f;


	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &param->pos, &param->invViewMatrix);
	param->setPos.x = setPos.x;
	param->setPos.y = setPos.y;
	param->setPos.z = setPos.z;


	//	�G�t�F�N�g����
	_fireworks->getManagerPoint()->Add(
		effectExistTimeSmall + (int)RANDAM(effectExistTimeRandomSmall),
		param->setPos,
		param->color,
		effectSizeSmall - ((effectSizeSmall / DELETECOUNT_MAX) * param->deleteCount),
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ),
		effectDifferenceSizeSmall,
		ManagerPoint::STATE_ADD
		);


	//	�J�E���^�X�V
	param->deleteCount++;
	if(param->deleteCount >= DELETECOUNT_MAX)
	{
		param->enable = false;
	}


	/*���@�@�s���������������Ȃ�Ver
	//------------------------------------------------------------
	//	�ԉΈړ��p�s�񏉊���
	D3DXMatrixIdentity(&param->matrix);

	//	��]
	D3DXMatrixRotationYawPitchRoll(
		&param->matrix,
		param->matRot.y,
		param->matRot.x,
		param->matRot.z);


	//	��]�ʉ��Z
	param->rot -= param->rotSpeed;

	if(param->rot < 180.0f)
		param->rot = 180.0f;
	else if(param->rot > 360.0f)
	{
		param->rot = 360.0f;
		//param->speed.y -= 0.1f;
	}

	//	���x�v�Z
	param->speed *= 0.999f;

	//	�ʒu�����Z
	param->pos.x += (CRadianTable::mySinf((double)param->rot) * param->speed.x);
	param->pos.y += (CRadianTable::myCosf((double)param->rot) * param->speed.y);
	//param->pos.z += param->speed.z;



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
	_fireworks->getManagerPoint()->Add(
		effectExistTime + (int)RANDAM(effectExistTimeRandom),
		D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
		D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ),
		effectSize - ((effectSize / DELETECOUNT_MAX) * param->deleteCount),
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.01f ),
		effectDifferenceSize,
		ManagerPoint::STATE_ADD
		);

	//	�J�E���^�X�V
	param->deleteCount++;
	if(param->deleteCount >= DELETECOUNT_MAX)
	{
		param->enable = false;
	}*/
	//------------------------------------------------------------
}
//	EOF