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

	// ���U���g�摜�I�u�W�F�N�g�̐���
	Effect*	pEffect2D = nullptr;		// 2D�`��G�t�F�N�g
	pEffect2D = pArgument_->pEffect_->Get( "Polygon2D.fx" );
	pObjectResult_ = new Object2D[ IMAGE_RESULT_MAXIMUM ];
	if( pObjectResult_ == nullptr )
	{
		return 1;
	}

	// ���U���g�w�i
	Texture*	pTextureResultBack = nullptr;		// ���U���g�w�i�e�N�X�`��
	pTextureResultBack = pArgument_->pTexture_->Get( _T( "result/back.png" ) );
	result = pObjectResult_[ IMAGE_RESULT_BACK ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_BACK ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureResultBack );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_BACK ].SetPosition( 320.0f, 0.0f, 0.0f );

	// ���U���g���S
	Texture*	pTextureResultLogo = nullptr;		// ���S�e�N�X�`��
	pTextureResultLogo = pArgument_->pTexture_->Get( _T( "result/result_logo.png" ) );
	result = pObjectResult_[ IMAGE_RESULT_LOGO ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_LOGO ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureResultLogo );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_LOGO ].SetPosition( 320.0f, 300.0f, 0.0f );

	// �V���N����
	Texture*	pTextureSyncronize = nullptr;		// ���S�e�N�X�`��
	pTextureSyncronize = pArgument_->pTexture_->Get( _T( "result/synchronize.png" ) );
	result = pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureSyncronize );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].SetPosition( 280.0f, 100.0f, 0.0f );

	// ����
	Texture*	pTextureJudge = nullptr;		// ����e�N�X�`��
	float		heightJudge;					// ����摜�̍���
	pTextureJudge = pArgument_->pTexture_->Get( _T( "result/judge.png" ) );
	for( int counterJudge = 0; counterJudge < 3; ++counterJudge )
	{
		result = pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].Initialize( 0 );
		if( result != 0 )
		{
			return result;
		}
		result = pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureJudge );
		if( result != 0 )
		{
			return result;
		}
		heightJudge = pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].GetScaleY();
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].SetScaleY( heightJudge / 4.0f );
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].SetPositionTextureY( 0.25f * counterJudge );
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].SetScaleTextureY( 4.0f );
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].SetPosition( 200.0f, -100.0f * counterJudge, 0.0f );
	}

	// �����L���O��
	Texture*	pTextureToRanking = nullptr;		// �����L���O�փe�N�X�`��
	pTextureToRanking = pArgument_->pTexture_->Get( _T( "result/to_ranking.png" ) );
	result = pObjectResult_[ IMAGE_RESULT_TO_RANKING ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_TO_RANKING ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureToRanking );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_TO_RANKING ].SetPosition( -500.0f, -305.0f, 0.0f );

	// �^�C�g����
	Texture*	pTextureToTitle = nullptr;		// �^�C�g���փe�N�X�`��
	pTextureToTitle = pArgument_->pTexture_->Get( _T( "result/to_title.png" ) );
	result = pObjectResult_[ IMAGE_RESULT_TO_TITLE ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_TO_TITLE ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureToTitle );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_TO_TITLE ].SetPosition( -220.0f, -305.0f, 0.0f );

	// �����L���O�摜�I�u�W�F�N�g�̐���
	pObjectRanking_ = new Object2D[ IMAGE_RANKING_MAXIMUM ];
	if( pObjectRanking_ == nullptr )
	{
		return 1;
	}

	// �����L���O���S
	Texture*	pTextureRankingLogo = nullptr;		// ���S�e�N�X�`��
	pTextureRankingLogo = pArgument_->pTexture_->Get( _T( "ranking/ranking_logo.png" ) );
	result = pObjectRanking_[ IMAGE_RANKING_LOGO ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectRanking_[ IMAGE_RANKING_LOGO ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureRankingLogo );
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
		pObjectScoreRanking_[ counterRank ].SetEnableGraphic( false );
	}

	// ���U���g�I�u�W�F�N�g�̔�\��
	DisableObjectResult();

	// �����L���O�I�u�W�F�N�g�̔�\��
	DisableObjectRanking();

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

	// ���U���g�摜�I�u�W�F�N�g�̊J��
	delete[] pObjectResult_;
	pObjectResult_ = nullptr;

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
	PrintDebug( _T( "Timer : %05d\n" ), timerSceneGame_ );

	// �J�����̏�����ݒ�
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// �w�i�̕\��
	if( timerSceneGame_ == TIME_RESULT_BEGIN_BACK )
	{
		pObjectResult_[ IMAGE_RESULT_BACK ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_BACK && timerSceneGame_ < TIME_RESULT_BEGIN_BACK + COUNT_RESULT_BEGIN_BACK )
	{
		float	proportion;		// ����
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_BACK) ) / COUNT_RESULT_BEGIN_BACK;
		pObjectResult_[ IMAGE_RESULT_BACK ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
	}

	// ���S�̕\��
	if( timerSceneGame_ == TIME_RESULT_BEGIN_LOGO )
	{
		pObjectResult_[ IMAGE_RESULT_LOGO ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_LOGO && timerSceneGame_ < TIME_RESULT_BEGIN_LOGO + COUNT_RESULT_BEGIN_LOGO )
	{
		float	proportion;		// ����
		float	scale;			// �傫��
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_LOGO) ) / COUNT_RESULT_BEGIN_LOGO;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		pObjectResult_[ IMAGE_RESULT_LOGO ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_LOGO ].SetScale( pObjectResult_[ IMAGE_RESULT_LOGO ].GetWidth() * scale, pObjectResult_[ IMAGE_RESULT_LOGO ].GetHeight() * scale, 1.0f );
	}

	// �V���N�����̕\��
	if( timerSceneGame_ == TIME_RESULT_BEGIN_SYNCRONIZE )
	{
		pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_SYNCRONIZE && timerSceneGame_ < TIME_RESULT_BEGIN_SYNCRONIZE + COUNT_RESULT_BEGIN_SYNCRONIZE )
	{
		float	proportion;		// ����
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_SYNCRONIZE) ) / COUNT_RESULT_BEGIN_SYNCRONIZE;
		pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].SetPositionY( Utility::Easing( 90.0f, 100.0f, proportion ) );
	}

	// ����0�̕\��
	if( timerSceneGame_ == TIME_RESULT_BEGIN_JUDGE_0 )
	{
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_JUDGE_0 && timerSceneGame_ < TIME_RESULT_BEGIN_JUDGE_0 + COUNT_RESULT_BEGIN_JUDGE_0 )
	{
		float	proportion;		// ����
		float	scale;			// �傫��
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_JUDGE_0) ) / COUNT_RESULT_BEGIN_JUDGE_0;
		scale = Utility::Easing( 1.5f, 1.0f, proportion );
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 ].SetScale( pObjectResult_[ IMAGE_RESULT_JUDGE_0 ].GetWidth() * scale, pObjectResult_[ IMAGE_RESULT_JUDGE_0 ].GetHeight() / 4.0f * scale, 1.0f );
	}

	// ����1�̕\��
	if( timerSceneGame_ == TIME_RESULT_BEGIN_JUDGE_1 )
	{
		pObjectResult_[ IMAGE_RESULT_JUDGE_1 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_JUDGE_1 && timerSceneGame_ < TIME_RESULT_BEGIN_JUDGE_1 + COUNT_RESULT_BEGIN_JUDGE_1 )
	{
		float	proportion;		// ����
		float	scale;			// �傫��
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_JUDGE_1) ) / COUNT_RESULT_BEGIN_JUDGE_1;
		scale = Utility::Easing( 1.5f, 1.0f, proportion );
		pObjectResult_[ IMAGE_RESULT_JUDGE_1 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_JUDGE_1 ].SetScale( pObjectResult_[ IMAGE_RESULT_JUDGE_1 ].GetWidth() * scale, pObjectResult_[ IMAGE_RESULT_JUDGE_1 ].GetHeight() / 4.0f * scale, 1.0f );
	}

	// ����2�̕\��
	if( timerSceneGame_ == TIME_RESULT_BEGIN_JUDGE_2 )
	{
		pObjectResult_[ IMAGE_RESULT_JUDGE_2 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_JUDGE_2 && timerSceneGame_ < TIME_RESULT_BEGIN_JUDGE_2 + COUNT_RESULT_BEGIN_JUDGE_2 )
	{
		float	proportion;		// ����
		float	scale;			// �傫��
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_JUDGE_2) ) / COUNT_RESULT_BEGIN_JUDGE_2;
		scale = Utility::Easing( 1.25f, 1.0f, proportion );
		pObjectResult_[ IMAGE_RESULT_JUDGE_2 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_JUDGE_2 ].SetScale( pObjectResult_[ IMAGE_RESULT_JUDGE_2 ].GetWidth() * scale, pObjectResult_[ IMAGE_RESULT_JUDGE_2 ].GetHeight() / 4.0f * scale, 1.0f );
	}


	// �����L���O�ւ̕\��
	if( timerSceneGame_ == TIME_RESULT_BEGIN_TO_RANKING )
	{
		pObjectResult_[ IMAGE_RESULT_TO_RANKING ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_TO_RANKING && timerSceneGame_ < TIME_RESULT_BEGIN_TO_RANKING + COUNT_RESULT_BEGIN_TO_RANKING )
	{
		float	proportion;		// ����
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_TO_RANKING) ) / COUNT_RESULT_BEGIN_TO_RANKING;
		pObjectResult_[ IMAGE_RESULT_TO_RANKING ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
	}

	// �^�C�g���ւ̕\��
	if( timerSceneGame_ == TIME_RESULT_BEGIN_TO_TITLE )
	{
		pObjectResult_[ IMAGE_RESULT_TO_TITLE ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_TO_TITLE && timerSceneGame_ < TIME_RESULT_BEGIN_TO_TITLE + COUNT_RESULT_BEGIN_TO_TITLE )
	{
		float	proportion;		// ����
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_TO_TITLE) ) / COUNT_RESULT_BEGIN_TO_TITLE;
		pObjectResult_[ IMAGE_RESULT_TO_TITLE ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
	}

	// �����L���O�ւ̓_��
	if( timerSceneGame_ >= TIME_RESULT_END )
	{
		float	proportion;		// ����
		proportion = D3DX_PI * 2.0f * static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_TO_RANKING) % 120 ) / 120;
		pObjectResult_[ IMAGE_RESULT_TO_RANKING ].SetColorAlpha( 0.2f * cosf( proportion ) + 0.8f );
	}

	// �^�C�g���ւ̓_��
	if( timerSceneGame_ >= TIME_RESULT_END )
	{
		float	proportion;		// ����
		proportion = D3DX_PI * 2.0f * static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_TO_TITLE) % 120 ) / 120;
		pObjectResult_[ IMAGE_RESULT_TO_TITLE ].SetColorAlpha( 0.2f * cosf( proportion ) + 0.8f );
	}

	// �^�C�}�[�̌o��
	++timerSceneGame_;

	// �X�V�����̐؂�ւ�
	if( pArgument_->pVirtualController_->IsTrigger( VC_DESIDE ) )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::UpdateRanking;
	}
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

	// ���̑��̉摜���\���ɂ���
	if( timerSceneGame_ == 0 )
	{
		DisableObjectResult();
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
				break;
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
			pObjectScoreRanking_[ counterRank ].SetScoreFuture( pRankingScore_[ counterRank ] );
		}
	}

	// �J�����̏�����ݒ�
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// ���S�̕\��
	if( timerSceneGame_ == TIME_RANKING_BEGIN_LOGO )
	{
		pObjectRanking_[ IMAGE_RANKING_LOGO ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_LOGO && timerSceneGame_ < TIME_RANKING_BEGIN_LOGO + COUNT_RANKING_BEGIN_LOGO )
	{
		float	proportion;		// ����
		float	scale;			// �傫��
		float	width;			// ��
		float	height;			// ����
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_LOGO) ) / COUNT_RANKING_BEGIN_LOGO;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_LOGO ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_LOGO ].GetHeight() * scale;
		pObjectRanking_[ IMAGE_RANKING_LOGO ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_LOGO ].SetScale( width, height, 1.0f );
	}

	// �����N5�̕\��
	if( timerSceneGame_ == TIME_RANKING_BEGIN_RANK_5 )
	{
		pObjectRanking_[ IMAGE_RANKING_RANK_5 ].SetEnableGraphic( true );
		pObjectScoreRanking_[ 4 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_RANK_5 && timerSceneGame_ < TIME_RANKING_BEGIN_RANK_5 + COUNT_RANKING_BEGIN_RANK_5 )
	{
		float	proportion;		// ����
		float	scale;			// �傫��
		float	width;			// ��
		float	height;			// ����
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_RANK_5) ) / COUNT_RANKING_BEGIN_RANK_5;
		scale = Utility::Easing( 2.5f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_RANK_5 ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_5 ].GetHeight() / 8.0f * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_5 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_5 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 4 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 4 ].SetPos( -250.0f, 170.0f - 120.0f * 4, 0.0f );
	}

	// �����N4�̕\��
	if( timerSceneGame_ == TIME_RANKING_BEGIN_RANK_4 )
	{
		pObjectRanking_[ IMAGE_RANKING_RANK_4 ].SetEnableGraphic( true );
		pObjectScoreRanking_[ 3 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_RANK_4 && timerSceneGame_ < TIME_RANKING_BEGIN_RANK_4 + COUNT_RANKING_BEGIN_RANK_4 )
	{
		float	proportion;		// ����
		float	scale;			// �傫��
		float	width;			// ��
		float	height;			// ����
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_RANK_4) ) / COUNT_RANKING_BEGIN_RANK_4;
		scale = Utility::Easing( 2.5f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_RANK_4 ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_4 ].GetHeight() / 8.0f * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_4 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_4 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 3 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 3 ].SetPos( -250.0f, 170.0f - 120.0f * 3, 0.0f );
	}

	// �����N3�̕\��
	if( timerSceneGame_ == TIME_RANKING_BEGIN_RANK_3 )
	{
		pObjectRanking_[ IMAGE_RANKING_RANK_3 ].SetEnableGraphic( true );
		pObjectScoreRanking_[ 2 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_RANK_3 && timerSceneGame_ < TIME_RANKING_BEGIN_RANK_3 + COUNT_RANKING_BEGIN_RANK_3 )
	{
		float	proportion;		// ����
		float	scale;			// �傫��
		float	width;			// ��
		float	height;			// ����
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_RANK_3) ) / COUNT_RANKING_BEGIN_RANK_3;
		scale = Utility::Easing( 2.5f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_RANK_3 ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_3 ].GetHeight() / 8.0f * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_3 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_3 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 2 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 2 ].SetPos( -250.0f, 170.0f - 120.0f * 2, 0.0f );
	}

	// �����N2�̕\��
	if( timerSceneGame_ == TIME_RANKING_BEGIN_RANK_2 )
	{
		pObjectRanking_[ IMAGE_RANKING_RANK_2 ].SetEnableGraphic( true );
		pObjectScoreRanking_[ 1 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_RANK_2 && timerSceneGame_ < TIME_RANKING_BEGIN_RANK_2 + COUNT_RANKING_BEGIN_RANK_2 )
	{
		float	proportion;		// ����
		float	scale;			// �傫��
		float	width;			// ��
		float	height;			// ����
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_RANK_2) ) / COUNT_RANKING_BEGIN_RANK_2;
		scale = Utility::Easing( 2.5f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_RANK_2 ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_2 ].GetHeight() / 8.0f * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_2 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_2 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 1 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 1 ].SetPos( -250.0f, 170.0f - 120.0f * 1, 0.0f );
	}

	// �����N1�̕\��
	if( timerSceneGame_ == TIME_RANKING_BEGIN_RANK_1 )
	{
		pObjectRanking_[ IMAGE_RANKING_RANK_1 ].SetEnableGraphic( true );
		pObjectScoreRanking_[ 0 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_RANK_1 && timerSceneGame_ < TIME_RANKING_BEGIN_RANK_1 + COUNT_RANKING_BEGIN_RANK_1 )
	{
		float	proportion;		// ����
		float	scale;			// �傫��
		float	width;			// ��
		float	height;			// ����
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_RANK_1) ) / COUNT_RANKING_BEGIN_RANK_1;
		scale = Utility::Easing( 4.0f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_RANK_1 ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_1 ].GetHeight() / 8.0f * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_1 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 0 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 0 ].SetPos( -250.0f, 170.0f - 120.0f * 0, 0.0f );
	}

	// �^�C�}�[�̌o��
	++timerSceneGame_;
}

//==============================================================================
// Brief  : ���U���g�I�u�W�F�N�g���\���ɂ���
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::DisableObjectResult( void )
{
	// �I�u�W�F�N�g���\���ɂ���
	for( int counterObject = 0; counterObject < IMAGE_RESULT_MAXIMUM; ++counterObject )
	{
		pObjectResult_[ counterObject ].SetEnableGraphic( false );
	}
}

//==============================================================================
// Brief  : �����L���O�I�u�W�F�N�g���\���ɂ���
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneGame::DisableObjectRanking( void )
{
	// �I�u�W�F�N�g���\���ɂ���
	for( int counterObject = 0; counterObject < IMAGE_RANKING_MAXIMUM; ++counterObject )
	{
		pObjectRanking_[ counterObject ].SetEnableGraphic( false );
	}

	// �X�R�A���\���ɂ���
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		pObjectScoreRanking_[ counterRank ].SetPos( 2500.0f, 170.0f - 120.0f * counterRank, 0.0f );
	}
}
