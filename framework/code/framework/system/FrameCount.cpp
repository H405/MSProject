//==============================================================================
//
// File   : FrameCount.cpp
// Brief  : �t���[���J�E���g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <time.h>
#include "FrameCount.h"
#include "Manager.h"
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
FrameCount::FrameCount( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
FrameCount::~FrameCount( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : HINSTANCE instanceHandle			: �C���X�^���X�n���h��
// Arg    : int typeShow						: �\���̎��
// Arg    : Manager* pManager					: �}�l�[�W��
// Arg    : int intervalUpdateFps				: FPS�X�V�Ԋu
// Arg    : int destinationFps					: �ڕWFPS
//==============================================================================
int FrameCount::Initialize( HINSTANCE instanceHandle, int typeShow, Manager* pManager, int intervalUpdateFps, int destinationFps )
{
	// �����o�ϐ��̐ݒ�
	instanceHandle_ = instanceHandle;
	typeShow_ = typeShow;
	pManager_ = pManager;
	intervalUpdateFps_ = intervalUpdateFps;
	destinationFps_ = destinationFps;
	intervalUpdateFps_ = 500;
	destinationFps_ = 60;
	for( int counterItem = 0; counterItem < TYPE_FRAME_COUNT_MAX; ++counterItem )
	{
		ppFunctionCountFrame_[ counterItem ] = nullptr;
	}
	ppFunctionCountFrame_[ TYPE_FRAME_COUNT_DRAW ] = CountFrameDraw;
	ppFunctionCountFrame_[ TYPE_FRAME_COUNT_UPDATE ] = CountFrameUpdate;
	pManager_ = pManager;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int FrameCount::Finalize( void )
{
	// �i�[�̈�̊J��
	for( int counterItem = 0; counterItem < TYPE_FRAME_COUNT_MAX; ++counterItem )
	{
		ppFunctionCountFrame_[ counterItem ] = nullptr;
	}

	// �N���X�����̏�����
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : HINSTANCE instanceHandle			: �C���X�^���X�n���h��
// Arg    : int cmdShow							: �\���̎��
// Arg    : Manager* pManager					: �}�l�[�W��
//==============================================================================
int FrameCount::Reinitialize( HINSTANCE instanceHandle, int cmdShow, Manager* pManager )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( instanceHandle, cmdShow, pManager, intervalUpdateFps_, destinationFps_ );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : FrameCount* pOut					: �R�s�[��A�h���X
//==============================================================================
int FrameCount::Copy( FrameCount* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���s
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int FrameCount::Execute( void )
{
	// ����\��ݒ�
	timeBeginPeriod( 1 );

	// ���Z�b�g���[�v
	MSG		message;		// ���b�Z�[�W���ʎq
	while( isLoopingReset_ )
	{
		// �ϐ��̏�����
		isLoopingMain_ = true;
		isLoopingReset_ = false;
		timeLastExecute_ =
		timeLastUpdate_ =
		timeBeginGame_ = timeGetTime();
		countFrameTotal_ =
		countFrameUpdate_ = 
		countFrameDraw_ = 0;
		typeCountFrame_ = TYPE_FRAME_COUNT_DRAW;
#ifdef _DEVELOP
		fpsUpdate_ = 0;
		fpsDraw_ = 0;
#endif

		// �����̏�����
		srand( (unsigned int)time( NULL ) );

		// ����������
		if( pManager_->Initialize( instanceHandle_, typeShow_  ) )
		{
			isLoopingMain_ = false;
		}

		// ���b�Z�[�W���[�v
		while( isLoopingMain_ )
		{
			if( PeekMessage( &message, NULL, 0, 0, PM_REMOVE ) )
			{
				if( message.message == WM_QUIT )
				{	// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
					break;
				}
				else
				{
					// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
					TranslateMessage( &message );
					DispatchMessage( &message );
				}
			}
			else
			{
				// �I������
				if( pManager_->IsEnd() )
				{
					isLoopingMain_ = false;
					break;
				}

				// �t���[���J�E���g
				(*ppFunctionCountFrame_[ typeCountFrame_ ])( this );
			}
		}
	}

	// ����\��߂�
	timeEndPeriod( 1 );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void FrameCount::End( void )
{
}

//==============================================================================
// Brief  : �ċN��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void FrameCount::Restart( void )
{
}

//==============================================================================
// Brief  : FPS�̍X�V�Ԋu�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void FrameCount::SetIntervalUpdateFps( int value )
{
	// �l�̐ݒ�
	intervalUpdateFps_ = value;
}

//==============================================================================
// Brief  : FPS�̍X�V�Ԋu�̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int FrameCount::GetIntervalUpdateFps( void ) const
{
	// �l�̕ԋp
	return intervalUpdateFps_;
}

//==============================================================================
// Brief  : �ڕWFPS�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void FrameCount::SetDestinationFps( int value )
{
	// �l�̐ݒ�
	destinationFps_ = value;
}

//==============================================================================
// Brief  : �ڕWFPS�̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int FrameCount::GetDestinationFps( void ) const
{
	// �l�̕ԋp
	return destinationFps_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void FrameCount::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	instanceHandle_ = NULL;
	typeShow_ = 0;
	isLoopingMain_ = true;
	isLoopingReset_ = true;
	intervalUpdateFps_ = 0;
	destinationFps_ = 0;
	timeLastExecute_ = 0;
	countFrameTotal_ = 0;
	timeBeginGame_ = 0;
	timeLastUpdate_ = 0;
	countFrameUpdate_ = 0;
	countFrameDraw_ = 0;
	typeCountFrame_ = 0;
	for( int counterItem = 0; counterItem < TYPE_FRAME_COUNT_MAX; ++counterItem )
	{
		ppFunctionCountFrame_[ counterItem ] = nullptr;
	}
	pManager_ = nullptr;
#ifdef _DEVELOP
	fpsUpdate_ = 0;
	fpsDraw_ = 0;
#endif
}

//==============================================================================
// Brief  : �t���[���J�E���g�`��D�揈��
// Return : void								: �Ȃ�
// Arg    : FrameCount* pThis					: ��������N���X
//==============================================================================
void FrameCount::CountFrameDraw( FrameCount* pThis )
{
	// FPS�̍X�V
	unsigned long	timeCurrent = timeGetTime();
	timeCurrent = timeGetTime();
	if( (timeCurrent - pThis->timeLastUpdate_) >= static_cast< unsigned int >( pThis->intervalUpdateFps_ ) )
	{
#ifdef _DEVELOP
		pThis->fpsUpdate_ = pThis->countFrameUpdate_ * 1000 / (timeCurrent - pThis->timeLastUpdate_);
		pThis->fpsDraw_ = pThis->countFrameDraw_ * 1000 / (timeCurrent - pThis->timeLastUpdate_);
#endif
		pThis->timeLastUpdate_ = timeCurrent;
		pThis->countFrameUpdate_ = 0;
		pThis->countFrameDraw_ = 0;
	}

	// �t���[���̏���
	if( (timeCurrent - pThis->timeLastExecute_) >= (1000 / 60) )
	{
		// �ŏI���s���Ԃ��X�V
		pThis->timeLastExecute_ = timeCurrent;

		// FPS�̒ʒm
#ifdef _DEVELOP
		pThis->pManager_->SetFpsUpdate( pThis->fpsUpdate_ );
		pThis->pManager_->SetFpsDraw( pThis->fpsDraw_ );
#endif

		// �X�V����
		pThis->pManager_->Update();

		// �`�揈��
		pThis->pManager_->Draw();

		// �X�V�t���[�������Z
		pThis->countFrameUpdate_++;

		// �`��t���[�������Z
		pThis->countFrameDraw_++;

		// ���t���[�������Z
		pThis->countFrameTotal_++;
	}
}

//==============================================================================
// Brief  : �t���[���J�E���g�X�V�D�揈��
// Return : void								: �Ȃ�
// Arg    : FrameCount* pThis					: ��������N���X
//==============================================================================
void FrameCount::CountFrameUpdate( FrameCount* pThis )
{
	// FPS�̍X�V
	unsigned long	timeCurrent = timeGetTime();
	timeCurrent = timeGetTime();
	if( (timeCurrent - pThis->timeLastUpdate_) >= static_cast< unsigned int >( pThis->intervalUpdateFps_ ) )
	{
#ifdef _DEVELOP
		pThis->fpsUpdate_ = pThis->countFrameUpdate_ * 1000 / (timeCurrent - pThis->timeLastUpdate_);
		pThis->fpsDraw_ = pThis->countFrameDraw_ * 1000 / (timeCurrent - pThis->timeLastUpdate_);
#endif
		pThis->timeLastUpdate_ = timeCurrent;
		pThis->countFrameUpdate_ = 0;
		pThis->countFrameDraw_ = 0;
	}

	// �t���[���̏���
	if( (timeCurrent - pThis->timeBeginGame_) >= (1000.0f / pThis->destinationFps_) * pThis->countFrameTotal_ )
	{
		// FPS�̒ʒm
#ifdef _DEVELOP
		pThis->pManager_->SetFpsUpdate( pThis->fpsUpdate_ );
		pThis->pManager_->SetFpsDraw( pThis->fpsDraw_ );
#endif

		// �X�V����
		pThis->pManager_->Update();

		// �X�V�t���[�������Z
		pThis->countFrameUpdate_++;

		// �`�揈��
		if( (timeCurrent - pThis->timeBeginGame_) <= (1000.0f / pThis->destinationFps_) * (pThis->countFrameTotal_ + 1) )
		{
			// �`�揈��
			pThis->pManager_->Draw();

			// �`��t���[�������Z
			pThis->countFrameDraw_++;
		}
		else
		{
			PrintDebugWnd( _T( "��������������(%4d�~���b)\n" ), timeCurrent - pThis->timeBeginGame_ - static_cast< DWORD >( (1000.0f / pThis->destinationFps_) * (pThis->countFrameTotal_ + 1) ) );
		}

		// ���t���[�������Z
		pThis->countFrameTotal_++;
	}
}
