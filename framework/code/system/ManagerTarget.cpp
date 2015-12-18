//==============================================================================
//
// File   : ManagerTarget.cpp
// Brief  : �^�[�Q�b�g�Ǘ��I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerTarget.h"
#include "../framework/develop/Debug.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerTexture.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define _CRT_SECURE_NO_WARNINGS
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerTarget::ManagerTarget( void )
{
	// �N���X���̏���������
	InitializeSelf();
}
//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerTarget::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	target = nullptr;
	targetAppearData = nullptr;
	targetAppearDataMax = 0;
	targetAppearCount = 0;
	targetAppearIndex = 0;

	for(int count = 0;count < TARGET_MAX;count++)
		enableOld[count] = false;
}
//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerTarget::~ManagerTarget( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int ManagerTarget::Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Texture* pTextureCross,
	Texture* pTextureArrow,
	Texture* pTextureCircle
	)
{
	//	�^�[�Q�b�g���w������p��
	target = new Target[TARGET_MAX];
	for(int count = 0;count < TARGET_MAX;count++)
	{
		target[count].Initialize(
			pDevice,
			pParameter,
			pEffectGeneral,
			pTextureCross,
			pTextureArrow,
			pTextureCircle);
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerTarget::Finalize( void )
{
	delete targetAppearData;
	delete[] target;

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
void ManagerTarget::Update(int* _table , int* _targetTableIndex)
{
	//	�����Ő���
	//autoAppear(_table, _targetTableIndex);

	for( int counterPoint = 0; counterPoint < TARGET_MAX; ++counterPoint )
	{
		//	�������u�Ԃ𔻒肵�āA�e�[�u�����č\�z
		if(enableOld[counterPoint] == true &&
			target[counterPoint].IsEnable() == false)
		{
			Sort(_table, counterPoint);
			*_targetTableIndex -= 1;
		}

		//	�g�p��Ԃ̑O����ۑ�
		enableOld[ counterPoint ] = target[ counterPoint ].IsEnable();

		// �g�p����Ă��Ȃ��Ƃ�����
		if( !target[ counterPoint ].IsEnable() )
		{
			continue;
		}
		target[counterPoint].setInvViewMatrix(invViewMatrix);
		target[counterPoint].Update();
	}
}
//==============================================================================
// Brief  : ������������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerTarget::autoAppear(int* _table , int* _targetTableIndex)
{
	//	�o���J�E���g���Z
	if(targetAppearIndex < targetAppearDataMax)
		targetAppearCount++;

	//	���݂̏o���f�[�^�́A�o�����Ԃ��J�E���^�ƈ�v������
	if(targetAppearData[targetAppearIndex].appearTime == targetAppearCount)
	{
		//	����
		int buff = Add(targetAppearData[targetAppearIndex].appearPos, targetAppearData[targetAppearIndex].colorState);
		targetAppearIndex++;

		//	�e�[�u���֒ǉ�
		if(buff != -1)
		{
			_table[*_targetTableIndex] = buff;
			*_targetTableIndex += 1;
		}

		//	�������Ԃɕ������������ꍇ������̂ŁA���̔���
		int tempIndex = targetAppearIndex;

		//	�J�E���^�������ł�����葱����
		while(targetAppearData[tempIndex].appearTime == targetAppearCount)
		{
			//	����
			buff = Add(targetAppearData[tempIndex].appearPos, targetAppearData[tempIndex].colorState);

			//	�e�[�u���֒ǉ�
			if(buff != -1)
			{
				_table[*_targetTableIndex] = buff;
				*_targetTableIndex += 1;
			}


			//	����Ɏ��̃C���f�b�N�X�Ɣ���
			tempIndex++;

			if(tempIndex >= targetAppearDataMax)
				break;
		}

		//	�C���f�b�N�X�l���Z�b�g������
		targetAppearIndex = tempIndex;
	}
}
//==============================================================================
// Brief  : �e�[�u���̃\�[�g����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerTarget::Sort(int* _table, int _deleteIndex)
{
	//	��������e�[�u���ԍ��̈ꎞ�ۑ�
	int tempIndex;

	//	�e�[�u����S�Ĉꎞ�ۑ�
	int tempTable[TARGET_MAX];

	for(int count = 0;count < TARGET_MAX;count++)
	{
		//	�e�[�u����S�Ĉꎞ�ۑ�
		tempTable[count] = _table[count];

		//	��������e�[�u���ԍ��̈ꎞ�ۑ�
		if(_table[count] == _deleteIndex)
			tempIndex = count;
	}

	//	�z��ۑ��p�̈ꎞ�J�E���^
	int tempCount = 0;

	for(int count = 0;count < TARGET_MAX;count++)
	{
		//	�폜����ԍ��ȊO
		if(count != tempIndex)
		{
			_table[tempCount] = tempTable[count];
			tempCount++;
		}
	}

	//	�Ō��-1�ǉ�
	_table[TARGET_MAX - 1] = -1;
}
//==============================================================================
// Brief  : �^�[�Q�b�g���ˏ���
// Return : void								: �Ȃ�
// Arg2   : D3DXVECTOR3							: �����ʒu
//==============================================================================
int ManagerTarget::Add(D3DXVECTOR3 _pos, COLOR_STATE _colorState)
{
	int index = GetIndex();
	if(index < 0)
	{
		//PrintDebugWnd( _T( "�|�C���g�ɋ󂫂�����܂���B\n" ) );
		return -1;
	}

	//	�^�[�Q�b�g�̃Z�b�g
	target[index].Set(_pos, _colorState);

	return index;
}
//==============================================================================
// Brief  : �C���f�b�N�X�擾����
// Return : int									: �g�p�\�ȃI�u�W�F�N�g�̔ԍ��i�S���g�p���̏ꍇ�͕��̒l���Ԃ�j
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerTarget::GetIndex()
{
	// �󂫔ԍ���T��
	for( int counterPoint = 0; counterPoint < TARGET_MAX; ++counterPoint )
	{
		if( !target[ counterPoint ].IsEnable() )
		{
			return counterPoint;
		}
	}

	// �󂢂Ă��Ȃ�����
	return -1;
}

//==============================================================================
// Brief  : �^�[�Q�b�g�����X�N���v�g�ǂݍ��ݏ���
//==============================================================================
void ManagerTarget::ReadTargetScriptFromFile(const char* _fileName)
{
	//	�t�@�C���ǂݍ��݊J�n
	FILE* fp;

	if(fopen_s(&fp, _fileName, "r") != NULL)
		return;

	char readBuff[256];
	int readDataIndex = 0;

	//	��������^�[�Q�b�g����ǂݍ���
	ReadAppearTargetMax(fp);

	//	�ǂݍ��݈ʒu��߂�
	fseek(fp, 0, SEEK_SET);

	//	��s�ǂݍ����
	while(fgets(readBuff, sizeof(readBuff), fp) != NULL)
	{
		//	�ȉ��A�ŏ��̂R�����ɂ���ĕ��򂵂ēǂݍ��݂��s��
		//-----------------------------------------------------------------------
		//	�����s�R�����g��F��������
		if(readBuff[0] == '/' && readBuff[1] == '-' && readBuff[2] == '-')
		{
			//	�R�����g�X�L�b�v
			SkipComment(fp);
		}
		//	�P�s�R�����g��F��������
		else if(readBuff[0] == 'C' && readBuff[1] == 'O' && readBuff[2] == 'M')
		{
			continue;
		}
		//	�I�u�W�F�N�g�̖��O��F��������
		else if(readBuff[0] == 'N' && readBuff[1] == 'A' && readBuff[2] == 'M')
		{
			//	NAM ��ǂݔ�΂�
			char* setName;
			char* ctx;
			ctx = strtok_s(readBuff, " ", &setName);

			//	���O�ۑ�
			strcpy_s(targetAppearData[readDataIndex].name, setName);

			//	�o�����Ԃƈʒu�̓ǂݍ���
			Read_TIM_POS_COL(fp, readDataIndex);
			readDataIndex++;
		}
		//-----------------------------------------------------------------------
	}

	fclose(fp);


	//	�f�[�^�̃\�[�g
	SortAppearTargetData();
}

void ManagerTarget::ReadAppearTargetMax(FILE* _fp)
{
	char readBuff[256];
	targetAppearDataMax = 0;

	//	��s�ǂݍ����
	while(fgets(readBuff, sizeof(readBuff), _fp) != NULL)
	{
		//	�ȉ��A�ŏ��̂R�����ɂ���ĕ��򂵂ēǂݍ��݂��s��
		//-----------------------------------------------------------------------
		//	�����s�R�����g��F��������
		if(readBuff[0] == '/' && readBuff[1] == '-' && readBuff[2] == '-')
		{
			//	�R�����g�X�L�b�v
			SkipComment(_fp);
		}
		//	�P�s�R�����g��F��������
		else if(readBuff[0] == 'C' && readBuff[1] == 'O' && readBuff[2] == 'M')
		{
			continue;
		}
		//	�I�u�W�F�N�g�̖��O��F��������
		else if(readBuff[0] == 'N' && readBuff[1] == 'A' && readBuff[2] == 'M')
		{
			targetAppearDataMax++;
		}
		//-----------------------------------------------------------------------
	}

	//	�f�[�^����
	targetAppearData = new TARGET_APPEAR_DATA[targetAppearDataMax];
}

void ManagerTarget::Read_TIM_POS_COL(FILE* _fp, int _readDataIndex)
{
	//	TIM �̓ǂݔ�΂�
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);
	//	�����l�ǂݍ���
	fscanf_s(_fp, "%d", &targetAppearData[_readDataIndex].appearTime);

	//	POS �̓ǂݔ�΂�
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);

	//	�����l�ǂݍ���
	//fread_s(targetAppearData[_readDataIndex].appearPos, sizeof(float) * 3, sizeof(float), 3, _fp);
	fscanf_s(_fp, "%f %f %f", &targetAppearData[_readDataIndex].appearPos.x, &targetAppearData[_readDataIndex].appearPos.y, &targetAppearData[_readDataIndex].appearPos.z);
	//-----------------------------------------------------------------------

	//	COL �̓ǂݔ�΂�
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);

	//	R G B W���Âꂩ�̓ǂݍ���
	char c = fgetc(_fp);
	if(c == 'R')
		targetAppearData[_readDataIndex].colorState = COLOR_STATE_R;
	else if(c == 'G')
		targetAppearData[_readDataIndex].colorState = COLOR_STATE_G;
	else if(c == 'B')
		targetAppearData[_readDataIndex].colorState = COLOR_STATE_B;
	else if(c == 'W')
		targetAppearData[_readDataIndex].colorState = COLOR_STATE_W;
	else if(c == 'S')
		targetAppearData[_readDataIndex].colorState = COLOR_STATE_S;
}

void ManagerTarget::SkipComment(FILE* _fp)
{
	char readBuff[512];
	while(fgets(readBuff, sizeof(readBuff), _fp) != NULL)
	{
		//	�ȉ��A�ŏ��̂R�����ɂ���ĕ��򂵂ēǂݍ��݂��s��
		//-----------------------------------------------------------------------
		//	�R�����g�̏I����F��������
		if(readBuff[0] == '-' && readBuff[1] == '-' && readBuff[2] == '/')
		{
			return;
		}
		//-----------------------------------------------------------------------
	}

	//	�R�����g�̏I����F���ł��Ȃ�������
	return;
}

void ManagerTarget::SortAppearTargetData()
{
	for(int i = 0;i < targetAppearDataMax - 1;i++)
	{
		for(int j = targetAppearDataMax - 1; j > i;j--)
		{
			if(targetAppearData[j - 1].appearTime >= targetAppearData[j].appearTime)
			{
				TARGET_APPEAR_DATA temp = targetAppearData[j];
				targetAppearData[j] = targetAppearData[j - 1];
				targetAppearData[j - 1] = temp;
			}
		}
	}
}
