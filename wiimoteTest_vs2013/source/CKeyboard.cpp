//*****************************************************************************
//	�L�[�{�[�h���� [CKeyboard.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "main.h"
#include "CKeyboard.h"

//*****************************************************************************
//	�萔��`
//*****************************************************************************
const int repeatOnTimer = 50;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CKeyboard::CKeyboard()
{
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CKeyboard::~CKeyboard()
{
}
//=============================================================================
//	������
//=============================================================================
bool CKeyboard::Init(HINSTANCE _instanceHandle, HWND _windowHandle)
{
	HRESULT hr;

#ifndef KEYBOARD_ON
	return false;
#endif

	//	�C���v�b�g�f�o�C�X�̐���
	if (CInput::Init(_instanceHandle, _windowHandle) == false)
	{
		return false;
	}

	//	�f�o�C�X�I�u�W�F�N�g���쐬
	hr = input->CreateDevice(GUID_SysKeyboard ,
							  &inputDevice ,
							  NULL);

	if(hr == E_FAIL)
	{
		ASSERT("�f�o�C�X�I�u�W�F�N�g�̐������s");
		return false;
	}

	//	�f�[�^�t�H�[�}�b�g��ݒ�
	hr = inputDevice->SetDataFormat(&c_dfDIKeyboard);

	if(hr == E_FAIL)
	{
		ASSERT("�f�[�^�t�H�[�}�b�g�̐ݒ莸�s");
		return false;
	}

	//	�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = inputDevice->SetCooperativeLevel(_windowHandle ,
										  (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	if(hr == E_FAIL)
	{
		ASSERT("�������[�h�̐ݒ莸�s");
		return false;
	}

	//	�L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	inputDevice->Acquire();

	//	�L�[�{�[�h������ԃJ�E���^�̏�����
	for(int count = 0 ; count < 256 ; count++)
	{
		repeatCount[count] = 0;
	}

	return true;
}
//=============================================================================
//	�X�V
//=============================================================================
void CKeyboard::Update()
{
	BYTE state[256];	//	�L�[�{�[�h������Ԋi�[�p�ϐ�

	//	�A�N�Z�X���������
	if(SUCCEEDED(inputDevice->GetDeviceState(sizeof(state) ,
											&state[0])))
	{
		for(int countKey = 0 ; countKey < 256 ; countKey++)
		{
			//	�g���K�[��OFF��
			trigger[countKey] = 0x00;

			//	�����[�X��OFF��
			release[countKey] = 0x00;

			//	���s�[�g��OFF��
			repeat[countKey] = 0x00;

			//	------------�����[�X���擾-------------------------------------------------
			//	�L�[�{�[�h�������[�X���ꂽ��
			if((press[countKey] == 0x00) && (pressOld[countKey] != press[countKey]))
			{
				//	�����[�X��ON��
				release[countKey] = 0x80;

				//	���s�[�g�p�̃J�E���g��������
				repeatCount[countKey] = 0;
			}
			//-----------------------------------------------------------------------------

			//	------------���s�[�g���擾-------------------------------------------------
			//	������ĂÂ��Ă�����
			if(state[countKey] == 0x80)
			{	
				//	�J�E���g�����l�𒴂�����true��Ԃ�(��莞�ԉ�����Ă�����)
				if (repeatCount[countKey] == repeatOnTimer || repeatCount[countKey] == 0)
				{
					//	���s�[�g�̃t���O��ON��
					repeat[countKey] = 0x80;			
				}

				//	�J�E���^�[���I�[�o�[�t���[���Ȃ��悤�ɊǗ����C���N�������g
				if(repeatCount[countKey] < 50)
				{
					repeatCount[countKey]++;
				}
			}
			//-----------------------------------------------------------------------------

			//	------------�g���K�[���擾-------------------------------------------------
			//	�����ꂽ�u��(���݉����Ă��āA�P�t���[���O�͉�����Ă��Ȃ������Ƃ�)
			if((press[countKey] == 0x80) && (pressOld[countKey] != press[countKey]))
			{
				//	�g���K�[�̃t���O��ON��
				trigger[countKey] = 0x80;
			}
			//-----------------------------------------------------------------------------

			//	�P�t���[���O�̃L�[�����i�[
			pressOld[countKey] = press[countKey];

			//	���݂̃t���[���̃L�[�����i�[
			press[countKey] = state[countKey];
		}
	}
	else
	{
		//	�A�N�Z�X���擾
		inputDevice->Acquire();
	}
}
//=============================================================================
//	���̃L�[�������ꂽ�����Q�b�g
//=============================================================================
int CKeyboard::GetTrigger()
{
	int returnKey = -1;

	for(int countKey = 0 ; countKey < 256 ; countKey++)
	{
		if(trigger[countKey] == 0x80)
		{
			returnKey = countKey;

			break;
		}
	}

	return returnKey;
}

//-----------------------------------EOF---------------------------------------