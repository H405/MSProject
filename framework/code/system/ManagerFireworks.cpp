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
#include "../framework/develop/DebugProc.h"
#include "../framework/develop/DebugMeasure.h"
#include "fireworks/FireworksState.h"

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

	for(int count = 0;count < FIREWORKS_MAX;count++)
		enableOld[count] = false;
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
	fireworksList = new Fireworks*[FIREWORKS_MAX];

	// �X�e�[�g�e�[�u���̍쐬
	//	FireworksStateArrange�ɃN���X�ǉ�������A����̃w�b�_�[�ɃX�e�[�g�ienum�j���₵��
	//	�����Ƀe�[�u����ǉ����邱�ƁI
	ppState_[ STATE_RIGHT ] = new FireworksStateRight();
	ppState_[ STATE_LEFT ] = new FireworksStateLeft();
	Fireworks::SetState( ppState_ );

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
	// �X�e�[�g�e�[�u���̊J��
	for( int count = 0; count < STATE_MAX; ++count )
	{
		delete ppState_[ count ];
		ppState_[ count ] = nullptr;
	}

	delete[] fireworksList;
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
void ManagerFireworks::Update(int* _table , int* _fireworksTableIndex)
{
	int countFireworks = 0;

	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		//	�������u�Ԃ𔻒肵�āA�e�[�u�����č\�z
		if(enableOld[count] == true &&
			fireworks[count].IsEnable() == false)
		{
			Sort(_table, count);
			*_fireworksTableIndex -= 1;
		}

		//	�g�p��Ԃ̑O����ۑ�
		enableOld[ count ] = fireworks[ count ].IsEnable();

		// �g�p����Ă��Ȃ��Ƃ�����
		if( !fireworks[ count ].IsEnable() )
		{
			continue;
		}

		fireworks[count].setInvViewMatrix(invViewMatrix);
		fireworks[count].Update();

		countFireworks++;
	}

	PrintDebug( _T( "\ncountFireworks = %d\n"), countFireworks );
}
//==============================================================================
// Brief  : �e�[�u���̃\�[�g����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerFireworks::Sort(int* _table, int _deleteIndex)
{
	//	��������e�[�u���ԍ��̈ꎞ�ۑ�
	int tempIndex;

	//	�e�[�u����S�Ĉꎞ�ۑ�
	int tempTable[FIREWORKS_MAX];

	for(int count = 0;count < FIREWORKS_MAX;count++)
	{
		//	�e�[�u����S�Ĉꎞ�ۑ�
		tempTable[count] = _table[count];

		//	��������e�[�u���ԍ��̈ꎞ�ۑ�
		if(_table[count] == _deleteIndex)
			tempIndex = count;
	}

	//	�z��ۑ��p�̈ꎞ�J�E���^
	int tempCount = 0;

	for(int count = 0;count < FIREWORKS_MAX;count++)
	{
		//	�폜����ԍ��ȊO
		if(count != tempIndex)
		{
			_table[tempCount] = tempTable[count];
			tempCount++;
		}
	}

	//	�Ō��-1�ǉ�
	_table[FIREWORKS_MAX - 1] = -1;
}
//==============================================================================
// Brief  : �ԉΔ��ˏ���
// Return : void								: �Ȃ�
// Arg    : int indexState						: �X�e�[�g�ԍ�
// Arg   : ManagerPoint*						: �|�C���g�X�v���C�g�����p�}�l�[�W��
// Arg   : D3DXVECTOR3							: �����ʒu
// Arg   : D3DXVECTOR3							: ���x
// Arg   : float								: �X�V���Ƃ̉�]��
// Arg   : float								: ���ɉ��Z�����]�ʁi�傫������ƕςɂȂ邩�璍�Ӂj
//==============================================================================
int ManagerFireworks::Add(
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

	//	�ԉ΂̃Z�b�g
	fireworks[index].Set(
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
int ManagerFireworks::GetIndex()
{
	// �󂫔ԍ���T��
	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		if( !fireworks[ count ].IsEnable() )
		{
			return count;
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
}

void ManagerFireworks::setManagerLight(ManagerLight* _managerLight)
{
	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		fireworks[count].setManagerLight(_managerLight);
	}
}
