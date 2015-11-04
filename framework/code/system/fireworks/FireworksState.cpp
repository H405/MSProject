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
#include "../../system/ManagerPoint.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define FIRE_MAX (36)
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define DELETECOUNT_MAX (200)
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
static const float effectSize = 15.0f;

//	��������ԉ΃G�t�F�N�g�̏�����܂ł̎���
static const int effectExistTime = 50;

//	��������ԉ΃G�t�F�N�g�̑傫���̍���
static const float effectDifferenceSize = -0.2f;

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Fireworks* pFireworks						: �Ώ�
//==============================================================================
void FireworksState::Update( Fireworks* _fireworks )
{
	// ����
	//if( pFireworks->GetTime() >= pFireworks->GetTimeExist() )
	//{
	//	pFireworks->SetIsEnable( false );
	//}
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Fireworks* pFireworks						: �Ώ�
//==============================================================================
void FireworksStateNormal::Update( Fireworks* _fireworks )
{
	//	�p�����[�^�փA�N�Z�X
	FIREWORKS_PARAM* param = _fireworks->getParam();

	//	��]�ʉ��Z.
	param->rot += param->rotSpeed;

	//	�ʒu�����Z.
	param->pos.x += (sinf(param->rot) * param->speed.x);
	param->pos.y += (cosf(param->rot) * param->speed.y) + 1.0f;
	param->pos.z += param->speed.z;

	//	�G�t�F�N�g����
	_fireworks->getManagerPoint()->Add(
		effectExistTime,
		D3DXVECTOR3(param->pos.x + FIRE_APPEAR_RANDAM, param->pos.y + FIRE_APPEAR_RANDAM, param->pos.z + FIRE_APPEAR_RANDAM),
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
	}
}
//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Fireworks* pFireworks						: �Ώ�
//==============================================================================
void FireworksStateSlow::Update( Fireworks* _fireworks )
{
	//	�p�����[�^�փA�N�Z�X
	FIREWORKS_PARAM* param = _fireworks->getParam();

	//	��]�ʉ��Z
	param->rot -= param->rotSpeed;

	//	�ʒu�����Z
	param->pos.x += (sinf(param->rot) * param->speed.x);
	param->pos.y += (cosf(param->rot) * param->speed.y) + 0.5f;
	param->pos.z += param->speed.z;

	//	�G�t�F�N�g����
	_fireworks->getManagerPoint()->Add(
		effectExistTime,
		D3DXVECTOR3(param->pos.x + FIRE_APPEAR_RANDAM, param->pos.y + FIRE_APPEAR_RANDAM, param->pos.z + FIRE_APPEAR_RANDAM),
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
	}
}