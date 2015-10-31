//==============================================================================
//
// File   : Motion.cpp
// Brief  : ���[�V�����N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Motion.h"

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
Motion::Motion( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Motion::~Motion( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : unsigned int countFrame				: �t���[����
// Arg    : unsigned int countBone				: �{�[����
//==============================================================================
int Motion::Initialize( unsigned int countFrame, unsigned int countBone )
{
	// �����o�ϐ��̐ݒ�
	countFrame_ = countFrame;
	countBone_ = countBone;
	pMatrixBone_ = new D3DXMATRIX[ countFrame * countBone ];
	for( unsigned int counterItem = 0; counterItem < countFrame * countBone; ++counterItem )
	{
		D3DXMatrixIdentity( &pMatrixBone_[ counterItem ] );
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Motion::Finalize( void )
{
	// �i�[�̈�̊J��
	delete[] pMatrixBone_;
	pMatrixBone_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : unsigned int countFrame				: �t���[����
// Arg    : unsigned int countBone				: �{�[����
//==============================================================================
int Motion::Reinitialize( unsigned int countFrame, unsigned int countBone )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( countFrame, countBone );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : Motion* pOut						: �R�s�[��A�h���X
//==============================================================================
int Motion::Copy( Motion* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �t���[�����̎擾
// Return : unsigned int						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned int Motion::GetCountFrame( void ) const
{
	// �l�̕ԋp
	return countFrame_;
}

//==============================================================================
// Brief  : �{�[�����̎擾
// Return : unsigned int						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned int Motion::GetCountBone( void ) const
{
	// �l�̕ԋp
	return countBone_;
}

//==============================================================================
// Brief  : �{�[���ϊ��s��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int indexFrame						: �ݒ肷��t���[���ԍ�
// Arg    : int indexBone						: �ݒ肷��{�[���ԍ�
// Arg    : const D3DXMATRIX& value				: �ݒ肷��l
//==============================================================================
void Motion::SetMatrixBone( int indexFrame, int indexBone, const D3DXMATRIX& value )
{
	// �l�̐ݒ�
	pMatrixBone_[ countBone_ * indexFrame + indexBone ] = value;
}

//==============================================================================
// Brief  : �{�[���ϊ��s��̎擾
// Return : void								: �Ȃ�
// Arg    : int indexFrame						: �ݒ肷��t���[���ԍ�
// Arg    : int indexBone						: �ݒ肷��{�[���ԍ�
// Arg    : D3DXMATRIX* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Motion::GetMatrixBone( int indexFrame, int indexBone, D3DXMATRIX* pOut ) const
{
	// �l�̕ԋp
	*pOut = pMatrixBone_[ countBone_ * indexFrame + indexBone ];
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Motion::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	countFrame_ = 0;
	countBone_ = 0;
	pMatrixBone_ = nullptr;
}
