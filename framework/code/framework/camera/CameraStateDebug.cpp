//==============================================================================
//
// File   : CameraStateDebug.cpp
// Brief  : デバッグステート
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "CameraStateDebug.h"
#include "CameraObject.h"
#include "../develop/Debug.h"
#include "../develop/DebugProc.h"
#include "../input/InputMouse.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
InputMouse*	CameraStateDebug::pMouse_ = nullptr;		// マウス入力クラス

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
CameraStateDebug::CameraStateDebug( void ) : CameraState()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
CameraStateDebug::~CameraStateDebug( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int CameraStateDebug::Initialize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = CameraState::Initialize();
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int CameraStateDebug::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = CameraState::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int CameraStateDebug::Reinitialize( void )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize();
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : CameraStateDebug* pOut				: コピー先アドレス
//==============================================================================
int CameraStateDebug::Copy( CameraStateDebug* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = CameraState::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : CameraObject* pCamera				: カメラクラス
//==============================================================================
void CameraStateDebug::Update( CameraObject* pCamera )
{
	// ドラッグ処理
	if( isDraggingLeft_ )
	{
		if( pMouse_->IsRelease( InputMouse::TYPE_LEFT ) )
		{
			isDraggingLeft_ = false;
		}
	}
	else
	{
		if( pMouse_->IsTrigger( InputMouse::TYPE_LEFT ) )
		{
			isDraggingLeft_ = true;
		}
	}
	if( isDraggingRight_ )
	{
		if( pMouse_->IsRelease( InputMouse::TYPE_RIGHT ) )
		{
			isDraggingRight_ = false;
		}
	}
	else
	{
		if( pMouse_->IsTrigger( InputMouse::TYPE_RIGHT ) )
		{
			isDraggingRight_ = true;
		}
	}

#if 0
	// 速度倍率
	if( pMouse_->IsPress( DIK_LSHIFT ) )
	{
		velocity = 5.0f;
	}
#endif

	// カメラの移動
	LONG		positionMouseX;			// マウスX座標
	LONG		positionMouseY;			// マウスY座標
	int			wheel = 0;				// ホイール移動量
	D3DXVECTOR3	vectorMove;				// 移動方向
	float		velocity = 1.0f;		// 速度倍率
	positionMouseX = pMouse_->GetPositionWindowX();
	positionMouseY = pMouse_->GetPositionWindowY();
	if( isDraggingLeft_ )
	{
		vectorMove = D3DXVECTOR3( 1.0f * velocity * ( positionPreviousX_ - positionMouseX ), 1.0f * velocity * ( positionMouseY - positionPreviousY_ ), 0.0f );
		pCamera->Move( vectorMove );
	}
	wheel = pMouse_->GetMoveWheel();
	if( wheel != 0 )
	{
		vectorMove = D3DXVECTOR3( 0.0f, 0.0f, 0.2f * velocity * wheel );
		pCamera->Move( vectorMove );
	}


	// カメラの角度
	if( isDraggingRight_ )
	{
		pCamera->AddRotationCameraX( -0.0075f * (positionPreviousY_ - positionMouseY) );
		pCamera->AddRotationCameraY( 0.0075f * (positionPreviousX_ - positionMouseX) );
	}
#if 0
	// カメラのリセット
	if( pMouse_->IsPress( DIK_O ) )
	{
		pCamera->SetPositionCamera( 0.0f, 30.0f, -100.0f );
		pCamera->SetPositionLookAt( 0.0f, 0.0f, 0.0f );
	}
#endif
	// マウス座標更新
	positionPreviousX_ = positionMouseX;
	positionPreviousY_ = positionMouseY;

	// マニュアル
	D3DXVECTOR3	vectorCamera;		// 視線ベクトル
	pCamera->GetVector( &vectorCamera );
	D3DXVec3Normalize( &vectorCamera, &vectorCamera );
	PrintDebug( "*--------------------------------------*\n" );
	PrintDebug( "| デバッグ用カメラ                     |\n" );
	PrintDebug( "*--------------------------------------*\n" );
	PrintDebug( "視点の座標       ： ( %11.6f, %11.6f, %11.6f )\n", pCamera->GetPositionCameraX(), pCamera->GetPositionCameraY(), pCamera->GetPositionCameraZ() );
	PrintDebug( "注視点の座標     ： ( %11.6f, %11.6f, %11.6f )\n", pCamera->GetPositionLookAtX(), pCamera->GetPositionLookAtY(), pCamera->GetPositionLookAtZ() );
	PrintDebug( "視線ベクトル     ： ( %11.6f, %11.6f, %11.6f )\n", vectorCamera.x, vectorCamera.y, vectorCamera.z );
	PrintDebug( "左ドラッグ       ： 上/下/左/右 移動\n" );
	PrintDebug( "ホイール         ： 前/後       移動\n" );
	PrintDebug( "右ドラッグ       ： 上/下/左/右 回転\n" );
#if 0
	PrintDebug( "左Shiftキー      ： 移動速度上昇\n" );
	PrintDebug( "Oキー            ： 原点へ戻る \n" );
#endif
	PrintDebug( "\n" );
}

#ifdef _DEVELOP
//==============================================================================
// Brief  : マウス入力クラスの設定
// Return : void								: なし
// Arg    : InputMouse* pMouse					: マウス入力クラス
//==============================================================================
void CameraStateDebug::SetInputMouse( InputMouse* pMouse )
{
	// 値の設定
	pMouse_ = pMouse;
}
#endif

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void CameraStateDebug::InitializeSelf( void )
{
	// メンバ変数の初期化
	positionPreviousX_ = 0;
	positionPreviousY_ = 0;
	isDraggingLeft_ = false;
	isDraggingRight_ = false;
}
