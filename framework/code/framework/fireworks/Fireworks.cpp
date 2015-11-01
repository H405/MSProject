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
#include "../../system/ManagerPoint.h"
#include "../../system/ManagerFireworks.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define FIRE_MAX (36)
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define DELETECOUNT_MAX (1000)
#define RANDAM(value) ((rand() % value) - (rand() % value))

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
static const int effectExistTime = 200;

//	��������ԉ΃G�t�F�N�g�̑傫���̍���
static const float effectDifferenceSize = -0.2f;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Fireworks::Fireworks( void )
{
	// �N���X���̏���������
	InitializeSelf();
}
//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Fireworks::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	managerPoint = nullptr;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = 0.0f;
	rotSpeed = 0.0f;
	speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enable = false;
	deleteCount = 0;
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
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int Fireworks::Set(
					ManagerPoint* _managerPoint,
					D3DXVECTOR3 _pos,
					D3DXVECTOR3 _speed,
					float _rot,
					float _rotSpeed )
{
	managerPoint = _managerPoint;
	pos = _pos;
	speed = _speed;
	rot = _rot;
	rotSpeed = _rotSpeed;

	enable = true;
	deleteCount = 0;

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
	//	��]�ʉ��Z
	rot += rotSpeed;

	pos.y++;

	//	�ʒu�����Z
	pos.x += sinf(rot) * speed.x;
	pos.y += cosf(rot) * speed.y;
	pos.z += speed.z;

	managerPoint->Add(
			effectExistTime,
			D3DXVECTOR3(pos.x + (RANDAM(100) * 0.01f), pos.y + (RANDAM(100) * 0.01f), pos.z + (RANDAM(100) * 0.01f)),
			D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ),
			effectSize - ((effectSize / DELETECOUNT_MAX) * deleteCount),
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.01f ),
			effectDifferenceSize,
			ManagerPoint::STATE_ADD
			);

	deleteCount++;
	if(deleteCount >= DELETECOUNT_MAX)
	{
		enable = false;
	}
}
//==============================================================================
// Brief  : �ԉ΂̔�������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Fireworks::burn()
{
	Finalize();
}
