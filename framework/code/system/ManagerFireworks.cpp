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
#include "../framework/develop/Debug.h"
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
	burnIndex = 0;

	//list.top = nullptr;
	//list.cur = nullptr;
	//list.prev = nullptr;
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
	ppState_[ STATE_NORMAL ] = new FireworksStateNormal();
	ppState_[ STATE_SLOW ] = new FireworksStateSlow();
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
void ManagerFireworks::Update( void )
{
	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		// �g�p����Ă��Ȃ��Ƃ�����
		if( !fireworks[ count ].IsEnable() )
		{
			continue;
		}

		fireworks[count].Update();
	}

	//	���X�g�쐬
	sort();
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
void ManagerFireworks::Add(
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
		return;
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
}
//==============================================================================
// Brief  : �C���f�b�N�X�擾����
// Return : int									: �g�p�\�ȃI�u�W�F�N�g�̔ԍ��i�S���g�p���̏ꍇ�͕��̒l���Ԃ�j
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerFireworks::GetIndex()
{
	// �󂫔ԍ���T��
	for( int count = burnIndex; count < FIREWORKS_MAX; ++count )
	{
		if( !fireworks[ count ].IsEnable() )
		{
			return count;
		}
	}
	for( int count = 0; count < burnIndex; ++count )
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
	//	�w��̉ԉ΂̔���
	fireworks[burnIndex].burn();

	//	�C���f�b�N�X�̍X�V
	burnIndex++;
	if(burnIndex >= FIREWORKS_MAX)
		burnIndex = 0;
}
//==============================================================================
// Brief  : �ԉ΂�ł��グ�����Ԓʂ�Ɋi�[����
//			�����������Ƃ��܂����@���邯�ǁA�ǂ肠�����J�E���^�̒l�����ăo�u���\�[�g����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerFireworks::sort()
{
	int sortList[FIREWORKS_MAX];

	//	���X�g��S��������
	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		fireworksList[count] = nullptr;
	}

	//	�ԉ΂��Ƃ̃J�E���^�i�[�p
	int counterList[FIREWORKS_MAX];

	//	�L��������Ă���ԉ΂̃J�E���^���擾
	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		if(fireworks[count].IsEnable() == true)
			counterList[count] = fireworks[count].getDeleteCount();
		else
			counterList[count] = -1;
	}

	//	�\�[�g���ʁi�C���f�b�N�X�ԍ��j�i�[�p
	int counter1 = 0;
	int counter2 = 0;
	int temp = 0;

	//	�o�u���\�[�g
	for(counter1 = 0;counter1 < FIREWORKS_MAX - 1;counter1++)
	{
		for(counter2 = FIREWORKS_MAX - 1;counter2 > counter1;counter2--)
		{
			//	�O�̗v�f�̕����傫����Ό���
			if(counterList[counter2 - 1] > counterList[counter2])
			{
				temp = counterList[counter2];
				counterList[counter2] = counterList[counter2 - 1];
				counterList[counter2 - 1] = temp;


			}
		}
	}
}
