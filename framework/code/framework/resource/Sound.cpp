//==============================================================================
//
// File   : Sound.cpp
// Brief  : サウンドクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/25 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Sound.h"

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
Sound::Sound( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Sound::~Sound( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IXAudio2SourceVoice* pSourceVoice	: ソースボイス
// Arg    : BYTE* pData							: データ
// Arg    : DWORD size							: データサイズ
//==============================================================================
int Sound::Initialize( IXAudio2SourceVoice* pSourceVoice, BYTE* pData, DWORD size )
{
	// メンバ変数の設定
	pSourceVoice_ = pSourceVoice;
	pData_ = pData;
	size_ = size;
	audioBuffer_.pAudioData = pData;
	audioBuffer_.AudioBytes = size;
	audioBuffer_.Flags = XAUDIO2_END_OF_STREAM;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Sound::Finalize( void )
{
	// ソースボイスの開放
	if( pSourceVoice_ != nullptr )
	{
		// 再生の停止
		pSourceVoice_->Stop( 0 );

		// ソースボイスの開放
		pSourceVoice_->DestroyVoice();
		pSourceVoice_ = nullptr;
	}

	//	オーディオデータの開放
	delete[] pData_;
	pData_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : IXAudio2SourceVoice* pSourceVoice	: ソースボイス
// Arg    : BYTE* pData							: データ
// Arg    : DWORD size							: データサイズ
//==============================================================================
int Sound::Reinitialize( IXAudio2SourceVoice* pSourceVoice, BYTE* pData, DWORD size )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pSourceVoice, pData, size );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Sound* pOut							: コピー先アドレス
//==============================================================================
int Sound::Copy( Sound* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再生
// Return : void								: なし
// Arg    : int countLoop						: ループ回数
//==============================================================================
void Sound::Play( int countLoop )
{
	// ループ回数の設定
	audioBuffer_.LoopCount = (countLoop < 0 ? XAUDIO2_LOOP_INFINITE : countLoop);

	// 状態取得
	XAUDIO2_VOICE_STATE	state;		// 状態
	pSourceVoice_->GetState( &state );

	// オーディオバッファがあるときに停止させる
	if( state.BuffersQueued != 0 )
	{
		pSourceVoice_->Stop( 0 );
		pSourceVoice_->FlushSourceBuffers();
	}

	// 再生
	pSourceVoice_->SubmitSourceBuffer( &audioBuffer_ );
	pSourceVoice_->Start( 0 );
}

//==============================================================================
// Brief  : 一時停止
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Sound::Pause( void )
{
	// 状態取得
	XAUDIO2_VOICE_STATE	state;		// 状態
	pSourceVoice_->GetState( &state );

	// オーディオバッファがあるときに一時停止させる
	if( state.BuffersQueued != 0 )
	{
		pSourceVoice_->Stop( 0 );
	}
}

//==============================================================================
// Brief  : 一時停止解除
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Sound::Unpause( void )
{
	// 状態取得
	XAUDIO2_VOICE_STATE	state;		// 状態
	pSourceVoice_->GetState( &state );

	// オーディオバッファがあるときに一時停止を解除させる
	if( state.BuffersQueued != 0 )
	{
		pSourceVoice_->Start( 0 );
	}
}

//==============================================================================
// Brief  : 停止
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Sound::Stop( void )
{
	// 状態取得
	XAUDIO2_VOICE_STATE	state;		// 状態
	pSourceVoice_->GetState( &state );

	// オーディオバッファがあるときに停止させる
	if( state.BuffersQueued != 0 )
	{
		pSourceVoice_->Stop( 0 );
		pSourceVoice_->FlushSourceBuffers();
	}
}

//==============================================================================
// Brief  : 音量の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void Sound::SetVolume( float value )
{
	// 値の設定
	pSourceVoice_->SetVolume( value );
}

//==============================================================================
// Brief  : 音量の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Sound::GetVolume( void ) const
{
	// 値の返却
	float volume;		// 音量
	pSourceVoice_->GetVolume( &volume );
	return volume;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Sound::InitializeSelf( void )
{
	// メンバ変数の初期化
	pSourceVoice_ = nullptr;
	pData_ = nullptr;
	size_ = 0;
	ZeroMemory( &audioBuffer_, sizeof( XAUDIO2_BUFFER ) );
}
