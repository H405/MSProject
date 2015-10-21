//==============================================================================
//
// File   : ManagerScene.cpp
// Brief  : �V�[���Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerScene.h"
#include "Scene.h"
#include "SceneArgument.h"

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
ManagerScene::ManagerScene( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerScene::~ManagerScene( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int typeSceneBegin					: �J�n�V�[��
// Arg    : SceneArgument* pArgument			: �V�[������
//==============================================================================
int ManagerScene::Initialize( int typeSceneBegin, SceneArgument* pArgument )
{
	// �����o�ϐ��̐ݒ�
	pArgument_ = pArgument;

	// �V�[���̐؂�ւ�
	ShiftScene( typeSceneBegin );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerScene::Finalize( void )
{
	// �V�[���̍폜
	delete pScene_;
	pScene_ = nullptr;

	// �N���X�����̏�����
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int typeSceneBegin					: �J�n�V�[��
// Arg    : SceneArgument* pArgument			: �V�[������
//==============================================================================
int ManagerScene::Reinitialize( int typeSceneBegin, SceneArgument* pArgument )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( typeSceneBegin, pArgument );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerScene* pOut					: �R�s�[��A�h���X
//==============================================================================
int ManagerScene::Copy( ManagerScene* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerScene::Update( void )
{
	// �V�[���폜�t���OOFF
	needsDelete_ = false;

	// �V�[���؂�ւ��v�����
	if( pScene_ != nullptr )
	{
		if( pScene_->IsEnd() )
		{
			isShifting_ = true;
			typeSceneNext_ = pScene_->GetSceneNext();
		}
	}

	// �V�[���ؑ֎�
	if( isShifting_ )
	{
		// �V�[���؂�ւ�
		if( pScene_ != nullptr )
		{
			needsDelete_ = true;
		}
		delete pScene_;
		pScene_ = nullptr;
		switch( typeSceneNext_ )
		{
		// �V�[���Ȃ�
		case 0:
			isEnd_ = true;
			break;

		// ���̑�
		default:
			isEnd_ = true;
			break;
		}

		// �t���O��OFF�ɖ߂�
		isShifting_ = false;
		if( isEnd_ )
		{
			return;
		}
	}

	// �V�[���X�V����
	if( pScene_ != nullptr )
	{
		pScene_->Update();
	}
}

//==============================================================================
// Brief  : �V�[���̐؂�ւ�
// Return : void								: �Ȃ�
// Arg    : int typeScene						: �؂�ւ���V�[��
//==============================================================================
void ManagerScene::ShiftScene( int typeScene )
{
	// �V�[���̐؂�ւ�
	typeSceneNext_ = typeScene;
	isShifting_ = true;
}

//==============================================================================
// Brief  : ���݂̃V�[���̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerScene::GetTypeSceneCurrent( void ) const
{
	// �l�̕ԋp
	return typeSceneCurrent_;
}

//==============================================================================
// Brief  : ���̃V�[���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void ManagerScene::SetTypeSceneNext( int value )
{
	// �l�̐ݒ�
	typeSceneNext_ = value;
}

//==============================================================================
// Brief  : �V�[���؂�ւ����t���O�̎擾
// Return : bool								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
bool ManagerScene::GetIsShifting( void ) const
{
	// �l�̕ԋp
	return isShifting_;
}

//==============================================================================
// Brief  : �V�[���؂�ւ����t���O�̔���
// Return : bool								: ���茋��
// Arg    : void								: �Ȃ�
//==============================================================================
bool ManagerScene::IsShifting( void ) const
{
	// �l�̕ԋp
	return isShifting_;
}

//==============================================================================
// Brief  : �V�[���I���t���O�̎擾
// Return : bool								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
bool ManagerScene::GetIsEnd( void ) const
{
	// �l�̕ԋp
	return isEnd_;
}

//==============================================================================
// Brief  : �V�[���I���t���O�̔���
// Return : bool								: ���茋��
// Arg    : void								: �Ȃ�
//==============================================================================
bool ManagerScene::IsEnd( void ) const
{
	// �l�̕ԋp
	return isEnd_;
}

//==============================================================================
// Brief  : �V�[���Ǘ��N���X�j���t���O�̎擾
// Return : bool								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
bool ManagerScene::GetNeedsDelete( void ) const
{
	// �l�̕ԋp
	return needsDelete_;
}

//==============================================================================
// Brief  : �V�[���Ǘ��N���X�j���t���O�̔���
// Return : bool								: ���茋��
// Arg    : void								: �Ȃ�
//==============================================================================
bool ManagerScene::NeedsDelete( void ) const
{
	// �l�̕ԋp
	return needsDelete_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerScene::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pArgument_ = nullptr;
	pScene_ = nullptr;
	typeSceneCurrent_ = 0;
	typeSceneNext_ = 0;
	isShifting_ = false;
	isEnd_ = false;
	needsDelete_ = false;
}
