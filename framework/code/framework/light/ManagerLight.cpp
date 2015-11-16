//==============================================================================
//
// File   : ManagerLight.cpp
// Brief  : ���C�g�Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/14 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerLight.h"
#include "LightDirection.h"
#include "LightPoint.h"
#include "../develop/Debug.h"

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
ManagerLight::ManagerLight( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerLight::~ManagerLight( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int maximumDirection				: �ő�f�B���N�V���i�����C�g��
// Arg    : int maximumPoint					: �ő�|�C���g���C�g��
//==============================================================================
int ManagerLight::Initialize( int maximumDirection, int maximumPoint )
{
	// �����o�ϐ��̐ݒ�
	maximumDirection_ = maximumDirection;
	maximumPoint_ = maximumPoint;
	if( maximumDirection > 0 )
	{
		pLightDirection_ = new LightDirection[ maximumDirection ];
		for( int counterItem = 0; counterItem < maximumDirection; ++counterItem )
		{
			pLightDirection_[ counterItem ].Initialize();
		}
	}
	if( maximumPoint > 0 )
	{
		pLightPoint_ = new LightPoint[ maximumPoint ];
		for( int counterItem = 0; counterItem < maximumPoint; ++counterItem )
		{
			pLightPoint_[ counterItem ].Initialize();
		}
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerLight::Finalize( void )
{
	// �i�[�̈�̊J��
	delete[] pLightDirection_;
	pLightDirection_ = nullptr;

	delete[] pLightPoint_;
	pLightPoint_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int maximumDirection				: �ő�f�B���N�V���i�����C�g��
// Arg    : int maximumPoint					: �ő�|�C���g���C�g��
//==============================================================================
int ManagerLight::Reinitialize( int maximumDirection, int maximumPoint )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( maximumDirection, maximumPoint );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerLight* pOut					: �R�s�[��A�h���X
//==============================================================================
int ManagerLight::Copy( ManagerLight* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �f�B���N�V���i�����C�g�̎擾
// Return : LightDirection*						: �f�B���N�V���i�����C�g
// Arg    : void								: �Ȃ�
//==============================================================================
LightDirection* ManagerLight::GetLightDirection( void )
{
	// �󂢂Ă��郉�C�g������
	for( int counterLight = 0; counterLight < maximumDirection_; ++counterLight )
	{
		if( !pLightDirection_[ counterLight ].IsUsed() )
		{
			pLightDirection_[ counterLight ].Reinitialize();
			pLightDirection_[ counterLight ].Use();
			return &pLightDirection_[ counterLight ];
		}
	}

	// ������Ȃ�����
	PrintDebugWnd( _T( "�f�B���N�V���i�����C�g�̋󂫂�����܂���ł����B\n" ) );
	return nullptr;
}

//==============================================================================
// Brief  : �|�C���g���C�g�̎擾
// Return : LightPoint*							: �|�C���g���C�g
// Arg    : void								: �Ȃ�
//==============================================================================
LightPoint* ManagerLight::GetLightPoint( void )
{
	// �󂢂Ă��郉�C�g������
	for( int counterLight = 0; counterLight < maximumPoint_; ++counterLight )
	{
		if( !pLightPoint_[ counterLight ].IsUsed() )
		{
			pLightPoint_[ counterLight ].Reinitialize();
			pLightPoint_[ counterLight ].Use();
			return &pLightPoint_[ counterLight ];
		}
	}

	// ������Ȃ�����
	PrintDebugWnd( _T( "�|�C���g���C�g�̋󂫂�����܂���ł����B\n" ) );
	return nullptr;
}

//==============================================================================
// Brief  : �f�B���N�V���i�����C�g���̎擾
// Return : int									: �f�B���N�V���i�����C�g��
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerLight::GetCountLightDirection( void )
{
	// �g�p���Ă��郉�C�g������
	int		countLight;		// ���C�g�̐�
	countLight = 0;
	for( int counterLight = 0; counterLight < maximumDirection_; ++counterLight )
	{
		if( pLightDirection_[ counterLight ].IsUsed() && pLightDirection_[ counterLight ].IsEnable() )
		{
			++countLight;
		}
	}

	// �l�̕ԋp
	return countLight;
}

//==============================================================================
// Brief  : �|�C���g���C�g���̎擾
// Return : int									: �|�C���g���C�g��
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerLight::GetCountLightPoint( void )
{
	// �g�p���Ă��郉�C�g������
	int		countLight;		// ���C�g�̐�
	countLight = 0;
	for( int counterLight = 0; counterLight < maximumPoint_; ++counterLight )
	{
		if( pLightPoint_[ counterLight ].IsUsed() && pLightPoint_[ counterLight ].IsEnable() )
		{
			++countLight;
		}
	}

	// �l�̕ԋp
	return countLight;
}

//==============================================================================
// Brief  : �L���ȃf�B���N�V���i�����C�g�̎擾
// Return : LightDirection*						: �f�B���N�V���i�����C�g
// Arg    : int index							: �ԍ�
//==============================================================================
LightDirection* ManagerLight::GetLightDirectionEnable( int index )
{
	// �g�p���Ă��郉�C�g������
	int		countLight;		// ���C�g�̌�
	countLight = 0;
	for( int counterLight = 0; counterLight < maximumDirection_; ++counterLight )
	{
		if( pLightDirection_[ counterLight ].IsUsed() && pLightDirection_[ counterLight ].IsEnable() )
		{
			if( countLight == index )
			{
				return &pLightDirection_[ counterLight ];
			}
			++countLight;
		}
	}

	// ������Ȃ�����
	PrintDebugWnd( _T( "�L���ȃf�B���N�V���i�����C�g��������܂���ł����B\n" ) );
	return nullptr;
}

//==============================================================================
// Brief  : �L���ȃ|�C���g���C�g�̎擾
// Return : LightPoint*							: �|�C���g���C�g
// Arg    : int index							: �ԍ�
//==============================================================================
LightPoint* ManagerLight::GetLightPointEnable( int index )
{
	// �g�p���Ă��郉�C�g������
	int		countLight;		// ���C�g�̌�
	countLight = 0;
	for( int counterLight = 0; counterLight < maximumPoint_; ++counterLight )
	{
		if( pLightPoint_[ counterLight ].IsUsed() && pLightPoint_[ counterLight ].IsEnable() )
		{
			if( countLight == index )
			{
				return &pLightPoint_[ counterLight ];
			}
			++countLight;
		}
	}

	// ������Ȃ�����
	PrintDebugWnd( _T( "�L���ȃ|�C���g���C�g��������܂���ł����B\n" ) );
	return nullptr;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerLight::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	maximumDirection_ = 0;
	maximumPoint_ = 0;
	pLightDirection_ = nullptr;
	pLightPoint_ = nullptr;
}
