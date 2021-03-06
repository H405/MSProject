//==============================================================================
//
// File   : XAudio.cpp
// Brief  : XAudio2クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/25 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "XAudio.h"
#include "../develop/Debug.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
XAudio::XAudio( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
XAudio::~XAudio( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : HWND windowHandle					: ウィンドウハンドル
//==============================================================================
int XAudio::Initialize( HWND windowHandle )
{
	// XAudio2オブジェクトの作成
	HRESULT	result;		// 実行結果
	result = XAudio2Create( &pXAudio_ );
	if( result != S_OK )
	{
		// エラーメッセージ
		PrintMsgBox( _T( "XAudio2の初期化に失敗しました。" ) );

		// 終了
		return result;
	}

	// マスターボイスの生成
	result = pXAudio_->CreateMasteringVoice( &pMasteringVoice_ );
	if( result != S_OK )
	{
		// エラーメッセージ
		PrintMsgBox( _T( "マスターボイスの生成に失敗しました。" ) );

		// 終了
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
int XAudio::Finalize( void )
{
	// マスターボイスの開放
	if( pMasteringVoice_ != nullptr )
	{
		pMasteringVoice_->DestroyVoice();
		pMasteringVoice_ = nullptr;
	}

	// XAudio2オブジェクトの開放
	if( pXAudio_ != nullptr )
	{
		pXAudio_->Release();
		pXAudio_ = nullptr;
	}

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : HWND windowHandle					: ウィンドウハンドル
//==============================================================================
int XAudio::Reinitialize( HWND windowHandle )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( windowHandle );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : XAudio* pOut						: コピー先アドレス
//==============================================================================
int XAudio::Copy( XAudio* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : XAudio2インターフェースの設定
// Return : void								: なし
// Arg    : IXAudio2* pValue					: 設定する値
//==============================================================================
void XAudio::SetXAudio( IXAudio2* pValue )
{
	// 値の設定
	pXAudio_ = pValue;
}

//==============================================================================
// Brief  : XAudio2インターフェースの取得
// Return : IXAudio2*							: 返却する値
// Arg    : void								: なし
//==============================================================================
IXAudio2* XAudio::GetXAudio( void ) const
{
	// 値の返却
	return pXAudio_;
}

//==============================================================================
// Brief  : マスターボイスの設定
// Return : void								: なし
// Arg    : IXAudio2MasteringVoice* pValue		: 設定する値
//==============================================================================
void XAudio::SetMasteringVoice( IXAudio2MasteringVoice* pValue )
{
	// 値の設定
	pMasteringVoice_ = pValue;
}

//==============================================================================
// Brief  : マスターボイスの取得
// Return : IXAudio2MasteringVoice*				: 返却する値
// Arg    : void								: なし
//==============================================================================
IXAudio2MasteringVoice* XAudio::GetMasteringVoice( void ) const
{
	// 値の返却
	return pMasteringVoice_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void XAudio::InitializeSelf( void )
{
	// メンバ変数の初期化
	pXAudio_ = nullptr;
	pMasteringVoice_ = nullptr;
}
