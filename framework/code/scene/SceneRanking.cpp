//==============================================================================
//
// File   : SceneRanking.cpp
// Brief  : �����L���O�V�[���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "SceneRanking.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/system/Fade.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

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
SceneRanking::SceneRanking( void ) : SceneMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneRanking::~SceneRanking( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
int SceneRanking::Initialize( SceneArgumentMain* pArgument )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Initialize( pArgument );
	if( result != 0 )
	{
		return result;
	}

	// �t�F�[�h�C��
	pArgument->pFade_->FadeIn( 20 );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int SceneRanking::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Finalize();
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
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
int SceneRanking::Reinitialize( SceneArgumentMain* pArgument )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pArgument );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : SceneRanking* pOut					: �R�s�[��A�h���X
//==============================================================================
int SceneRanking::Copy( SceneRanking* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Copy( pOut );
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
void SceneRanking::Update( void )
{
	// �e�X�g
	PrintDebug( _T( "�����L���O\n" ) );

	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_TITLE );
		SetIsEnd( true );
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_RETURN ) )
	{
		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
		}
	}
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneRanking::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
