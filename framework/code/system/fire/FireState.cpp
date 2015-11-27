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
static const float effectSize = 15.0f;
static const float effectSizeSmall = 5.0f;

//	��������ΉԃG�t�F�N�g�̏�����܂ł̎���
static const int effectExistTime = 5;
static const int effectExistTimeRandom = (int)(effectExistTime * 0.9f);

static const int effectExistTimeSmall = 30;
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
		0.0f,
		ManagerPoint::STATE_ADD
		);


	//	�J�E���^�X�V
	param->deleteCount++;
	if(param->deleteCount >= DELETECOUNT_MAX)
	{
		param->enable = false;
	}
}
//	EOF