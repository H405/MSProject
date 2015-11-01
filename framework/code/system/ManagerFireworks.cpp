//==============================================================================
//
// File   : ManagerFireworks.cpp
// Brief  : �ԉΊǗ��I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerFireworks.h"
#include "../framework/fireworks/Fireworks.h"
#include "../framework/develop/Debug.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerFireworks::ManagerFireworks( void )
{
	// �N���X���̏���������
	InitializeSelf();
}
//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerFireworks::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	fireworks = nullptr;
	managerPoint = nullptr;
	burnIndex = 0;
}
//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerFireworks::~ManagerFireworks( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
//==============================================================================
int ManagerFireworks::Initialize(ManagerPoint* _managerPoint)
{
	managerPoint = _managerPoint;

	//	�ԉ΂��w������p��
	fireworks = new Fireworks[FIREWORKS_MAX];

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerFireworks::Finalize( void )
{
	delete[] fireworks;

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
void ManagerFireworks::Update( void )
{
	for( int counterPoint = 0; counterPoint < FIREWORKS_MAX; ++counterPoint )
	{
		// �g�p����Ă��Ȃ��Ƃ�����
		if( !fireworks[ counterPoint ].IsEnable() )
		{
			continue;
		}

		fireworks[counterPoint].Update();
	}
}
//==============================================================================
// Brief  : �ԉΔ��ˏ���
// Return : void								: �Ȃ�
// Arg1   : ManagerPoint*						: �|�C���g�X�v���C�g�����p�}�l�[�W��
// Arg2   : D3DXVECTOR3							: �����ʒu
// Arg3   : D3DXVECTOR3							: ���x
// Arg4   : float								: �X�V���Ƃ̉�]��
// Arg5   : float								: ���ɉ��Z�����]�ʁi�傫������ƕςɂȂ邩�璍�Ӂj
//==============================================================================
void ManagerFireworks::Add(
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _speed,
		float _rot,
		float _rotSpeed)
{
	int index = GetIndex();
	if(index < 0)
	{
		PrintDebugWnd( _T( "�|�C���g�ɋ󂫂�����܂���B\n" ) );
		return;
	}

	//	�ԉ΂̃Z�b�g
	fireworks[index].Set(
		_managerPoint,
		_pos,
		_speed,
		_rot,
		_rotSpeed
		);
}
//==============================================================================
// Brief  : �C���f�b�N�X�擾����
// Return : int									: �g�p�\�ȃI�u�W�F�N�g�̔ԍ��i�S���g�p���̏ꍇ�͕��̒l���Ԃ�j
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerFireworks::GetIndex()
{
	// �󂫔ԍ���T��
	for( int counterPoint = burnIndex; counterPoint < FIREWORKS_MAX; ++counterPoint )
	{
		if( !fireworks[ counterPoint ].IsEnable() )
		{
			return counterPoint;
		}
	}
	for( int counterPoint = 0; counterPoint < burnIndex; ++counterPoint )
	{
		if( !fireworks[ counterPoint ].IsEnable() )
		{
			return counterPoint;
		}
	}

	// �󂢂Ă��Ȃ�����
	return -1;
}
//==============================================================================
// Brief  : �ԉ΂̔�������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerFireworks::Burn()
{
	//	�w��̉ԉ΂̔���
	fireworks[burnIndex].burn();

	//	�C���f�b�N�X�̍X�V
	burnIndex++;
	if(burnIndex >= FIREWORKS_MAX)
		burnIndex = 0;
}
