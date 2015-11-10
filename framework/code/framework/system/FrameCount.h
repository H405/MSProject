//==============================================================================
//
// File   : FrameCount.h
// Brief  : フレームカウントクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_FRAME_COUNT_H
#define MY_FRAME_COUNT_H

//******************************************************************************
// インクルード
//******************************************************************************
#include <windows.h>

//******************************************************************************
// ライブラリ
//******************************************************************************
#pragma comment( lib, "winmm.lib" )

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Manager;

//******************************************************************************
// クラス定義
//******************************************************************************
class FrameCount
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	FrameCount( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~FrameCount( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : HINSTANCE instanceHandle			: インスタンスハンドル
	// Arg    : int typeShow						: 表示の種類
	// Arg    : Manager* pManager					: マネージャ
	// Arg    : int intervalUpdateFps				: FPS更新間隔
	// Arg    : int destinationFps					: 目標FPS
	//==============================================================================
	int Initialize( HINSTANCE instanceHandle, int typeShow, Manager* pManager, int intervalUpdateFps, int destinationFps );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : HINSTANCE instanceHandle			: インスタンスハンドル
	// Arg    : int cmdShow							: 表示の種類
	// Arg    : Manager* pManager					: マネージャ
	//==============================================================================
	int Reinitialize( HINSTANCE instanceHandle, int cmdShow, Manager* pManager );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : FrameCount* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( FrameCount* pOut ) const;

	//==============================================================================
	// Brief  : 実行
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Execute( void );

	//==============================================================================
	// Brief  : 終了
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void End( void );

	//==============================================================================
	// Brief  : 再起動
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Restart( void );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetIntervalUpdateFps( int value );
	int GetIntervalUpdateFps( void ) const;
	void SetDestinationFps( int value );
	int GetDestinationFps( void ) const;

protected:

private:
	// カウントの種類
	enum
	{
		TYPE_FRAME_COUNT_DRAW = 0,		// 描画優先
		TYPE_FRAME_COUNT_UPDATE,		// 更新優先
		TYPE_FRAME_COUNT_MAX			// 最大値
	};

	void InitializeSelf( void );
	FrameCount( const FrameCount& );
	FrameCount operator=( const FrameCount& );
	static void CountFrameDraw( FrameCount* pThis );
	static void CountFrameUpdate( FrameCount* pThis );

	HINSTANCE		instanceHandle_;		// インスタンスハンドル
	int				typeShow_;				// 表示の種類
	bool			isLoopingMain_;			// メインループフラグ
	bool			isLoopingReset_;		// リセットループフラグ
	int				intervalUpdateFps_;		// FPSの更新間隔
	int				destinationFps_;		// 目標FPS
	unsigned long	timeLastExecute_;		// 最終実行時間
	unsigned long	countFrameTotal_;		// 総フレーム数
	unsigned long	timeBeginGame_;			// ゲーム開始時間
	unsigned long	timeLastUpdate_;		// 最終更新時間
	unsigned long	countFrameUpdate_;		// 更新フレーム数
	unsigned long	countFrameDraw_;		// 描画フレーム数
	int				typeCountFrame_;		// フレームカウントの種類
	Manager*		pManager_;				// マネージャクラス格納用
#ifdef _DEVELOP
	unsigned long	fpsUpdate_;				// 更新FPS
	unsigned long	fpsDraw_;				// 描画FPS
#endif

	void (*ppFunctionCountFrame_[ TYPE_FRAME_COUNT_MAX ])( FrameCount* );		// フレームカウント関数テーブル
};

#endif	// MY_FRAME_COUNT_H
