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
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/ObjectScore.h"
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

	// �����L���O�摜�I�u�W�F�N�g�̐���
	Effect*	pEffect2D = nullptr;		// 2D�`��G�t�F�N�g
	pEffect2D = pArgument_->pEffect_->Get( "Polygon2D.fx" );
	pObjectRanking_ = new Object2D[ IMAGE_RANKING_MAXIMUM ];
	if( pObjectRanking_ == nullptr )
	{
		return 1;
	}

	// ���S
	Texture*	pTextureLogo = nullptr;		// ���S�e�N�X�`��
	pTextureLogo = pArgument_->pTexture_->Get( _T( "ranking/ranking_logo.png" ) );
	result = pObjectRanking_[ IMAGE_RANKING_LOGO ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectRanking_[ IMAGE_RANKING_LOGO ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureLogo );
	if( result != 0 )
	{
		return result;
	}
	pObjectRanking_[ IMAGE_RANKING_LOGO ].SetPosition( 0.0f, 300.0f, 0.0f );

	// �����N
	Texture*	pTextureRank = nullptr;		// ���S�e�N�X�`��
	float		heightRank;					// �����L���O�摜����
	pTextureRank = pArgument_->pTexture_->Get( _T( "ranking/rank.png" ) );
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		result = pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].Initialize( 0 );
		if( result != 0 )
		{
			return result;
		}
		result = pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureRank );
		if( result != 0 )
		{
			return result;
		}
		heightRank = pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].GetScaleY();
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetPosition( -500.0f, 170.0f - 120.0f * counterRank, 0.0f );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetScaleY( heightRank / 8.0f );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetScaleTextureY( 8.0f );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetPositionTextureY( 1.0f / 8.0f * counterRank );
	}

	// �����L���O�X�R�A�I�u�W�F�N�g
	Texture*	pTextureNumber = nullptr;		// �����e�N�X�`��
	pTextureNumber = pArgument_->pTexture_->Get( _T( "common/number_white.png" ) );
	pObjectScoreRanking_ = new ObjectScore[ MAXIMUM_RANK ];
	if( pObjectScoreRanking_ == nullptr )
	{
		return 1;
	}
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		result = pObjectScoreRanking_[ counterRank ].Initialize( 0, 10 );
		if( result != 0 )
		{
			return result;
		}
		result = pObjectScoreRanking_[ counterRank ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureNumber );
		if( result != 0 )
		{
			return result;
		}
		pObjectScoreRanking_[ counterRank ].SetSizeX( static_cast< float >( pTextureNumber->width_ ) / 8.0f );
		pObjectScoreRanking_[ counterRank ].SetPos( -250.0f, 170.0f - 120.0f * counterRank, 0.0f );
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
	// �����L���O�X�R�A�I�u�W�F�N�g�̊J��
	delete[] pObjectScoreRanking_;
	pObjectScoreRanking_ = nullptr;

	// �����L���O�摜�I�u�W�F�N�g�̊J��
	delete[] pObjectRanking_;
	pObjectRanking_ = nullptr;

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
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		pRankingScore_[ counterRank ] = 0;
	}
	indexRank_ = 0;
	pObjectRanking_ = nullptr;
	pObjectScoreRanking_ = nullptr;
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

//==============================================================================
// Brief  : �����L���O�X�V
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::UpdateRanking( void )
{
	// �e�X�g
	PrintDebug( _T( "UpdateRanking\n" ) );
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		PrintDebug( _T( "Rank%d : %10d\n" ), counterRank, pRankingScore_[ counterRank ] );
	}

	// �����L���O�f�[�^�̓ǂݍ���
	if( timerSceneGame_ == 0 )
	{
		// �t�@�C�����J��
		FILE*	pFile = nullptr;		// �t�@�C��
		fopen_s( &pFile, _T( "data/ranking/ranking.txt" ), _T( "r+t" ) );

		// �f�[�^�̓ǂݍ���
		if( pFile != nullptr )
		{
			for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
			{
				if( _ftscanf_s( pFile, _T( "%d" ), &pRankingScore_[ counterRank ] ) == EOF )
				{
					break;
				}
			}
		}

		// �t�@�C�������
		if( pFile != nullptr )
		{
			fclose( pFile );
			pFile = nullptr;
		}
	}

	// �����L���O�̍X�V
	if( timerSceneGame_ == 0 )
	{
		int		scoreCurrent;		// ���݂̃X�R�A
		scoreCurrent = score->GetScore();
		for( indexRank_ = 0; indexRank_ < MAXIMUM_RANK; ++indexRank_ )
		{
			if( scoreCurrent >= pRankingScore_[ indexRank_ ] )
			{
				for( int counterRank = MAXIMUM_RANK - 1; counterRank > indexRank_; --counterRank )
				{
					pRankingScore_[ counterRank ] = pRankingScore_[ counterRank - 1 ];
				}
				pRankingScore_[ indexRank_ ] = scoreCurrent;
			}
		}
	}

	// �����L���O�̏�������
	if( timerSceneGame_ == 0 )
	{
		// �t�@�C�����J��
		FILE*	pFile = nullptr;		// �t�@�C��
		fopen_s( &pFile, _T( "data/ranking/ranking.txt" ), _T( "w+t" ) );
		if( pFile == nullptr )
		{
			return;
		}

		// �f�[�^�̏�������
		for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
		{
			_ftprintf_s( pFile, _T( "%d\n" ), pRankingScore_[ counterRank ] );
		}

		// �t�@�C�������
		fclose( pFile );
		pFile = nullptr;
	}

	// �X�R�A�I�u�W�F�N�g�ɐݒ�
	if( timerSceneGame_ == 0 )
	{
		for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
		{
			pObjectScoreRanking_[ counterRank ].SetScore( pRankingScore_[ counterRank ] );
		}
	}

	// �J�����̏�����ݒ�
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// �^�C�}�[�̌o��
	++timerSceneGame_;
}
