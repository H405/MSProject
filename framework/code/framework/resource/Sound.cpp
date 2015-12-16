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
// Arg    : int countSourceVoice				: ソースボイス数
// Arg    : IXAudio2SourceVoice** ppSourceVoice	: ソースボイス
// Arg    : BYTE* pData							: データ
// Arg    : DWORD size							: データサイズ
//==============================================================================
int Sound::Initialize( int countSourceVoice, IXAudio2SourceVoice** ppSourceVoice, BYTE* pData, DWORD size )
{
	// メンバ変数の設定
	countSourceVoice_ = countSourceVoice;
	ppSourceVoice_ = new IXAudio2SourceVoice*[ countSourceVoice ];
	if( ppSourceVoice_ == nullptr )
	{
		return 1;
	}
	for( int counterSourceVoice = 0; counterSourceVoice < countSourceVoice; ++counterSourceVoice )
	{
		ppSourceVoice_[ counterSourceVoice ] = ppSourceVoice[ counterSourceVoice ];
	}
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
	if( ppSourceVoice_ != nullptr )
	{
		for( int counterSourceVoice = 0; counterSourceVoice < countSourceVoice_; ++counterSourceVoice )
		{
			if( ppSourceVoice_[ counterSourceVoice ] != nullptr )
			{
				// 再生の停止
				ppSourceVoice_[ counterSourceVoice ]->Stop( 0 );

				// ソースボイスの開放
				ppSourceVoice_[ counterSourceVoice ]->DestroyVoice();
				ppSourceVoice_[ counterSourceVoice ] = nullptr;
			}
		}
	}
	delete[] ppSourceVoice_;
	ppSourceVoice_ = nullptr;

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
// Arg    : int countSourceVoice				: ソースボイス数
// Arg    : IXAudio2SourceVoice** ppSourceVoice	: ソースボイス
// Arg    : BYTE* pData							: データ
// Arg    : DWORD size							: データサイズ
//==============================================================================
int Sound::Reinitialize( int countSourceVoice, IXAudio2SourceVoice** ppSourceVoice, BYTE* pData, DWORD size )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( countSourceVoice, ppSourceVoice, pData, size );
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
// Return : int									: ソースボイス番号
// Arg    : int countLoop						: ループ回数
// Arg    : int indexSourceVoice				: ソースボイス番号
//==============================================================================
int Sound::Play( int countLoop, int indexSourceVoice )
{
	// ソースボイス番号を決定
	int		index;		// ソースボイス番号
	if( indexSourceVoice < 0 )
	{
		++indexSource_;
		if( indexSource_ >= countSourceVoice_ )
		{
			indexSource_ = 0;
		}
		index = indexSource_;
	}
	else
	{
		index = indexSourceVoice;
	}

	// ループ回数の設定
	audioBuffer_.LoopCount = (countLoop < 0 ? XAUDIO2_LOOP_INFINITE : countLoop);

	// 状態取得
	XAUDIO2_VOICE_STATE	state;		// 状態
	ppSourceVoice_[ index ]->GetState( &state );

	// オーディオバッファがあるときに停止させる
	if( state.BuffersQueued != 0 )
	{
		ppSourceVoice_[ index ]->Stop( 0 );
		ppSourceVoice_[ index ]->FlushSourceBuffers();
	}

	// 再生
	ppSourceVoice_[ index ]->SubmitSourceBuffer( &audioBuffer_ );
	ppSourceVoice_[ index ]->Start( 0 );

	// ソースボイス番号を返す
	return index;
}

//==============================================================================
// Brief  : 一時停止
// Return : int									: ソースボイス番号
// Arg    : int indexSourceVoice				: ソースボイス番号
//==============================================================================
int Sound::Pause( int indexSourceVoice )
{
	// ソースボイス番号を決定
	int		index;		// ソースボイス番号
	index = (indexSourceVoice < 0 ? indexSource_ : indexSourceVoice);

	// 状態取得
	XAUDIO2_VOICE_STATE	state;		// 状態
	ppSourceVoice_[ index ]->GetState( &state );

	// オーディオバッファがあるときに一時停止させる
	if( state.BuffersQueued != 0 )
	{
		ppSourceVoice_[ index ]->Stop( 0 );
	}

	// ソースボイス番号を返す
	return index;
}

//==============================================================================
// Brief  : 一時停止解除
// Return : int									: ソースボイス番号
// Arg    : int indexSourceVoice				: ソースボイス番号
//==============================================================================
int Sound::Unpause( int indexSourceVoice )
{
	// ソースボイス番号を決定
	int		index;		// ソースボイス番号
	index = (indexSourceVoice < 0 ? indexSource_ : indexSourceVoice);

	// 状態取得
	XAUDIO2_VOICE_STATE	state;		// 状態
	ppSourceVoice_[ index ]->GetState( &state );

	// オーディオバッファがあるときに一時停止を解除させる
	if( state.BuffersQueued != 0 )
	{
		ppSourceVoice_[ index ]->Start( 0 );
	}

	// ソースボイス番号を返す
	return index;
}

//==============================================================================
// Brief  : 停止
// Return : int									: ソースボイス番号
// Arg    : int indexSourceVoice				: ソースボイス番号
//==============================================================================
int Sound::Stop( int indexSourceVoice )
{
	// ソースボイス番号を決定
	int		index;		// ソースボイス番号
	index = (indexSourceVoice < 0 ? indexSource_ : indexSourceVoice);

	// 状態取得
	XAUDIO2_VOICE_STATE	state;		// 状態
	ppSourceVoice_[ index ]->GetState( &state );

	// オーディオバッファがあるときに停止させる
	if( state.BuffersQueued != 0 )
	{
		ppSourceVoice_[ index ]->Stop( 0 );
		ppSourceVoice_[ index ]->FlushSourceBuffers();
	}

	// ソースボイス番号を返す
	return index;
}

//==============================================================================
// Brief  : 音量の設定
// Return : int									: ソースボイス番号
// Arg    : int indexSourceVoice				: ソースボイス番号
//==============================================================================
int Sound::SetVolume( float value, int indexSourceVoice )
{
	// ソースボイス番号を決定
	int		index;		// ソースボイス番号
	index = (indexSourceVoice < 0 ? indexSource_ : indexSourceVoice);

	// 値の設定
	ppSourceVoice_[ index ]->SetVolume( value );

	// ソースボイス番号を返す
	return index;
}

//==============================================================================
// Brief  : 音量の取得
// Return : float								: 返却する値
// Arg    : int indexSourceVoice				: ソースボイス番号
//==============================================================================
float Sound::GetVolume( int indexSourceVoice ) const
{
	// ソースボイス番号を決定
	int		index;		// ソースボイス番号
	index = (indexSourceVoice < 0 ? indexSource_ : indexSourceVoice);

	// 値の返却
	float volume;		// 音量
	ppSourceVoice_[ index ]->GetVolume( &volume );
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
	countSourceVoice_ = 0;
	indexSource_ = 0;
	ppSourceVoice_ = nullptr;
	pData_ = nullptr;
	size_ = 0;
	ZeroMemory( &audioBuffer_, sizeof( XAUDIO2_BUFFER ) );
}
