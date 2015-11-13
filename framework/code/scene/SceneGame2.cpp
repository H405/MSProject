//==============================================================================
//
// File   : SceneGame2.cpp
// Brief  : �Q�[���V�[���N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/11 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "SceneGame.h"
#include "../framework/camera/CameraObject.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/input/VirtualController.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../system/camera/CameraStateSpline.h"
#include "../system/SceneArgumentMain.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int SceneGame::Initialize2( void )
{
	// �Q�[���J�n�O�J���������̐���
	int		result;		// ���s����
	pStateCameraPrevious_ = new CameraStateSpline();
	if( pStateCameraPrevious_ == nullptr )
	{
		return 1;
	}
	result = pStateCameraPrevious_->Initialize( _T( "data/camera/PreviousGame.txt" ) );
	if( result != 0 )
	{
		return result;
	}

	// ���U���g�O�J���������̐���
	pStateCameraResult_ = new CameraStateSpline();
	if( pStateCameraResult_ == nullptr )
	{
		return 1;
	}
	result = pStateCameraResult_->Initialize( _T( "data/camera/PreviousResult.txt" ) );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int SceneGame::Finalize2( void )
{
	// ���U���g�O�J���������̊J��
	delete pStateCameraResult_;
	pStateCameraResult_ = nullptr;

	// �Q�[���J�n�O�J���������̊J��
	delete pStateCameraPrevious_;
	pStateCameraPrevious_ = nullptr;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::InitializeSelf2( void )
{
	// �����o�ϐ��̏�����
	pStateCameraPrevious_ = nullptr;
	pStateCameraResult_ = nullptr;
	timerSceneGame_ = 0;
}

//==============================================================================
// Brief  : �Q�[���J�n�O�X�V
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::UpdatePreviousGame( void )
{
	// �e�X�g
	PrintDebug( _T( "UpdatePreviousGame\n" ) );

	// �J�����̏�����ݒ�
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( pStateCameraPrevious_ );
	}

	// �^�C�}�[�̌o��
	++timerSceneGame_;

	// �X�V�����̐؂�ւ�
	if( timerSceneGame_ >= pStateCameraPrevious_->GetCountFrame() )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::UpdateCountDownGame;
	}
}

//==============================================================================
// Brief  : �Q�[���J�n�O�J�E���g�_�E���X�V
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::UpdateCountDownGame( void )
{
	// �e�X�g
	PrintDebug( _T( "UpdateCountDownGame\n" ) );
	PrintDebug( _T( "Timer : %05d\n" ), timerSceneGame_ );

	// �J�����̏�����ݒ�
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// �^�C�}�[�̌o��
	++timerSceneGame_;

	// �X�V�����̐؂�ւ�
	if( timerSceneGame_ >= 240 )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::normalUpdate;
	}
}

//==============================================================================
// Brief  : ���U���g�ҋ@�X�V
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::UpdateWaitResult( void )
{
	// �e�X�g
	PrintDebug( _T( "UpdateWaitResult\n" ) );

	// �J�����̏�����ݒ�
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// �^�C�}�[�̌o��
	++timerSceneGame_;

	// �X�V�����̐؂�ւ�
	if( pArgument_->pVirtualController_->IsTrigger( VC_DESIDE ) )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::UpdatePreviousResult;
	}
}

//==============================================================================
// Brief  : ���U���g�O�X�V
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::UpdatePreviousResult( void )
{
	// �e�X�g
	PrintDebug( _T( "UpdatePreviousResult\n" ) );

	// �J�����̏�����ݒ�
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( pStateCameraResult_ );
	}

	// �^�C�}�[�̌o��
	++timerSceneGame_;
}

//==============================================================================
// Brief  : ���U���g�X�V
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::UpdateResult( void )
{
	// �e�X�g
	PrintDebug( _T( "UpdateResult\n" ) );

	// �J�����̏�����ݒ�
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// �^�C�}�[�̌o��
	++timerSceneGame_;
}
