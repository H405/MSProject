//==============================================================================
//
// File   : ManagerFire.cpp
// Brief  : �ΉԊǗ��I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerFire.h"
#include "../framework/develop/Debug.h"
#include "fire/FireState.h"

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
ManagerFire::ManagerFire( void )
{
	// �N���X���̏���������
	InitializeSelf();
}
//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerFire::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	fire = nullptr;
	managerPoint = nullptr;
}
//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerFire::~ManagerFire( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
//==============================================================================
int ManagerFire::Initialize(ManagerPoint* _managerPoint)
{
	managerPoint = _managerPoint;

	//	�ΉԂ��w������p��
	fire = new Fire[FIRE_MAX];
	fireList = new Fire*[FIRE_MAX];

	// �X�e�[�g�e�[�u���̍쐬
	//	FireStateArrange�ɃN���X�ǉ�������A����̃w�b�_�[�ɃX�e�[�g�ienum�j���₵��
	//	�����Ƀe�[�u����ǉ����邱�ƁI
	ppState_[ STATE_NORMAL ] = new FireStateNormal();
	ppState_[ STATE_SLOW ] = new FireStateSlow();
	Fire::SetState( ppState_ );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerFire::Finalize( void )
{
	// �X�e�[�g�e�[�u���̊J��
	for( int count = 0; count < STATE_MAX; ++count )
	{
		delete ppState_[ count ];
		ppState_[ count ] = nullptr;
	}

	delete[] fireList;
	delete[] fire;


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
void ManagerFire::Update(int* _table , int* _fireTableIndex)
{
	for( int count = 0; count < FIRE_MAX; ++count )
	{
		//	�������u�Ԃ𔻒肵�āA�e�[�u�����č\�z
		if(enableOld[count] == true &&
			fire[count].IsEnable() == false)
		{
			Sort(_table, count);
			*_fireTableIndex -= 1;
		}

		//	�g�p��Ԃ̑O����ۑ�
		enableOld[ count ] = fire[ count ].IsEnable();

		// �g�p����Ă��Ȃ��Ƃ�����
		if( !fire[ count ].IsEnable() )
		{
			continue;
		}

		fire[count].Update();
	}
}
//==============================================================================
// Brief  : �e�[�u���̃\�[�g����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerFire::Sort(int* _table, int _deleteIndex)
{
	//	��������e�[�u���ԍ��̈ꎞ�ۑ�
	int tempIndex;

	//	�e�[�u����S�Ĉꎞ�ۑ�
	int tempTable[FIRE_MAX];

	for(int count = 0;count < FIRE_MAX;count++)
	{
		//	�e�[�u����S�Ĉꎞ�ۑ�
		tempTable[count] = _table[count];

		//	��������e�[�u���ԍ��̈ꎞ�ۑ�
		if(_table[count] == _deleteIndex)
			tempIndex = count;
	}

	//	�z��ۑ��p�̈ꎞ�J�E���^
	int tempCount = 0;

	for(int count = 0;count < FIRE_MAX;count++)
	{
		//	�폜����ԍ��ȊO
		if(count != tempIndex)
		{
			_table[tempCount] = tempTable[count];
			tempCount++;
		}
	}

	//	�Ō��-1�ǉ�
	_table[FIRE_MAX - 1] = -1;
}
//==============================================================================
// Brief  : �ΉԔ��ˏ���
// Return : void								: �Ȃ�
// Arg    : int indexState						: �X�e�[�g�ԍ�
// Arg   : ManagerPoint*						: �|�C���g�X�v���C�g�����p�}�l�[�W��
// Arg   : D3DXVECTOR3							: �����ʒu
// Arg   : D3DXVECTOR3							: ���x
// Arg   : float								: �X�V���Ƃ̉�]��
// Arg   : float								: ���ɉ��Z�����]�ʁi�傫������ƕςɂȂ邩�璍�Ӂj
//==============================================================================
int ManagerFire::Add(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _speed,
	float _rot,
	float _rotSpeed)
{
	int index = GetIndex();
	if(index < 0)
	{
		//PrintDebugWnd( _T( "�|�C���g�ɋ󂫂�����܂���B\n" ) );
		return -1;
	}

	//	�ΉԂ̃Z�b�g
	fire[index].Set(
		_indexState,
		_managerPoint,
		_pos,
		_speed,
		_rot,
		_rotSpeed
		);

	return index;
}
//==============================================================================
// Brief  : �C���f�b�N�X�擾����
// Return : int									: �g�p�\�ȃI�u�W�F�N�g�̔ԍ��i�S���g�p���̏ꍇ�͕��̒l���Ԃ�j
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerFire::GetIndex()
{
	// �󂫔ԍ���T��
	for( int count = 0; count < FIRE_MAX; ++count )
	{
		if( !fire[ count ].IsEnable() )
		{
			return count;
		}
	}

	// �󂢂Ă��Ȃ�����
	return -1;
}
//==============================================================================
// Brief  : �ΉԂ̔�������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerFire::Burn()
{
}
