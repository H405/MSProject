//==============================================================================
//
// File   : ManagerSceneMain.cpp
// Brief  : �V�[���Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerSceneMain.h"
#include "SceneMain.h"
#include "SceneArgumentMain.h"
#include "../scene/SceneGame.h"
#include "../scene/SceneRanking.h"
#include "../scene/SceneResult.h"
#include "../scene/SceneSplash.h"
#include "../scene/SceneTitle.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
bool ManagerSceneMain::demoFlag = false;
bool ManagerSceneMain::tutorialFlag = false;
bool ManagerSceneMain::reTutorialFlag = false;
int ManagerSceneMain::demoCount = 0;
int ManagerSceneMain::demoCountMax = 780;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerSceneMain::ManagerSceneMain( void ) : ManagerScene()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerSceneMain::~ManagerSceneMain( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int typeSceneBegin					: �J�n�V�[��
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
int ManagerSceneMain::Initialize( int typeSceneBegin, SceneArgumentMain* pArgument )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerScene::Initialize( typeSceneBegin, pArgument );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pArgument_ = pArgument;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerSceneMain::Finalize( void )
{
	// �V�[���̔j��
	delete pScene_;
	pScene_ = nullptr;

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerScene::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int typeSceneBegin					: �J�n�V�[��
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
int ManagerSceneMain::Reinitialize( int typeSceneBegin, SceneArgumentMain* pArgument )
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
// Arg    : ManagerSceneMain* pOut				: �R�s�[��A�h���X
//==============================================================================
int ManagerSceneMain::Copy( ManagerSceneMain* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerScene::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerSceneMain::Update( void )
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
		case TYPE_NONE:
			isEnd_ = true;
			break;

		// �X�v���b�V��
		case TYPE_SPLASH:
			pScene_ = new SceneSplash();
			break;

		// �^�C�g��
		case TYPE_TITLE:
			pScene_ = new SceneTitle();
			break;

		// �Q�[��
		case TYPE_GAME:
			pScene_ = new SceneGame();
			break;

		// ���U���g
		case TYPE_RESULT:
			pScene_ = new SceneResult();
			break;

		// �����L���O
		case TYPE_RANKING:
			pScene_ = new SceneRanking();
			break;

		// ���̑�
		default:
			isEnd_ = true;
			break;
		}
		if( pScene_ == nullptr )
		{
			isEnd_ = true;
		}
		else
		{
			pScene_->Initialize( pArgument_ );
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
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerSceneMain::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pArgument_ = nullptr;
	pScene_ = nullptr;
}
