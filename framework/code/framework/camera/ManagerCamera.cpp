//==============================================================================
//
// File   : ManagerCamera.cpp
// Brief  : �J�����Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/20 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerCamera.h"
#include "CameraObject.h"
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
ManagerCamera::ManagerCamera( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerCamera::~ManagerCamera( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int countCamera						: �J������
//==============================================================================
int ManagerCamera::Initialize( int countCamera )
{
	// �����o�ϐ��̐ݒ�
	countCamera_ = countCamera;
	if( countCamera_ > 0 )
	{
		pCamera_ = new CameraObject[ countCamera ];
		for( int counterItem = 0; counterItem < countCamera; ++counterItem )
		{
			pCamera_[ counterItem ].Initialize();
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
int ManagerCamera::Finalize( void )
{
	// �i�[�̈�̊J��
	delete[] pCamera_;
	pCamera_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int countCamera						: �J������
//==============================================================================
int ManagerCamera::Reinitialize( int countCamera )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( countCamera );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerCamera* pOut					: �R�s�[��A�h���X
//==============================================================================
int ManagerCamera::Copy( ManagerCamera* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerCamera::Update( void )
{
#ifdef _DEVELOP
	// �f�o�b�O�ؑ�
	if( (GetKeyState( VK_F3 ) & 0x80) != 0 )
	{
		if( !isPressingKey_ )
		{
			pCamera_[ indexDebug_ ].ToggleDebug();
		}
		isPressingKey_ = true;
	}
	else
	{
		isPressingKey_ = false;
	}
#endif

	// �J�����̍X�V
	for( int counterCamera = 0; counterCamera < countCamera_; ++counterCamera )
	{
		pCamera_[ counterCamera ].Update();
	}
}

//==============================================================================
// Brief  : �J�����̎擾
// Return : CameraObject*						: �J����
// Arg    : int index							: �ԍ�
//==============================================================================
CameraObject* ManagerCamera::GetCamera( int index )
{
	// �J�����̃A�h���X��Ԃ�
	return &pCamera_[ index ];
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerCamera::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	countCamera_ = 0;
	pCamera_ = nullptr;
#ifdef _DEVELOP
	indexDebug_ = 0;
	isPressingKey_ = false;
#endif
}
