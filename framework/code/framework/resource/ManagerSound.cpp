//==============================================================================
//
// File   : ManagerSound.cpp
// Brief  : サウンド管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/25 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerSound.h"
#include "Sound.h"
#include "../develop/Debug.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// テンプレート宣言
//******************************************************************************
template class ManagerSound< class Sound >;

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerSound< TypeItem >::ManagerSound( void ) : ManagerResource()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerSound< TypeItem >::~ManagerSound( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : TCHAR* pDirectory					: 基準ディレクトリ
// Arg    : int maximumItem						: 最大要素数
// Arg    : IXAudio2* pXAudio					: XAudio2インターフェース
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::Initialize( TCHAR* pDirectory, int maximumItem, IXAudio2* pXAudio )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerResource::Initialize( pDirectory, maximumItem );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	pXAudio_ = pXAudio;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerResource::Finalize();
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
// Arg    : TCHAR* pDirectory					: 基準ディレクトリ
// Arg    : int maximumItem						: 最大要素数
// Arg    : IXAudio2* pXAudio					: XAudio2インターフェース
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::Reinitialize( TCHAR* pDirectory, int maximumItem, IXAudio2* pXAudio )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDirectory, maximumItem, pXAudio );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ManagerSound* pOut					: コピー先アドレス
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::Copy( ManagerSound* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerResource::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : リソースの読み込み
// Return : int									: リソースID
// Arg    : TCHAR* pNameFile					: ファイル名
// Arg    : int maximumStack					: 最大同時再生数
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::Load( TCHAR* pNameFile, int maximumStack )
{
	// エラーチェック
	Assert( pNameFile != nullptr, _T( "ファイルパスが不正です。" ) );

	// ファイルパスの作成
	TCHAR	pPath[ _MAX_PATH ] = {};		// ファイルパス
	_tcscpy_s( pPath, _MAX_PATH, pDirectory_ );
	_tcscat_s( pPath, _MAX_PATH, pNameFile );

	// 既に作られていないか検索
	int		index;		// 要素番号
	index = GetId( pPath );
	if( index != -1 )
	{
		return index;
	}

	// 格納場所の決定
	for( index = 0; index < maximumItem_; ++index )
	{
		if( !pBufferItem_[ index ].isEnable_ )
		{
			break;
		}
	}
	if( index >= maximumItem_ )
	{
		PrintDebugWnd( _T( "リソースの格納領域に空きがありません。" ) );
		return -1;
	}

	// リソースの読み込み
	int		result;		// 実行結果
	result = LoadResource( pPath, index, maximumStack );
	if( result != 0 )
	{
		return -1;
	}

	// 要素に値を設定
	pBufferItem_[ index ].id_ = index;
	_tcscpy_s( pBufferItem_[ index ].pPath_, _MAX_PATH, pPath );
	pBufferItem_[ index ].isEnable_ = true;

	// リソースIDを返す
	return index;
}

//==============================================================================
// Brief  : リソースの取得
// Return : TypeItem*							: リソース
// Arg    : TCHAR* pNameFile					: ファイル名
// Arg    : int maximumStack					: 最大同時再生数
//==============================================================================
template< class TypeItem >
TypeItem* ManagerSound< TypeItem >::Get( TCHAR* pNameFile, int maximumStack )
{
	// エラーチェック
	Assert( pNameFile != nullptr, _T( "ファイルパスが不正です。" ) );

	// ファイルパスの作成
	TCHAR	pPath[ _MAX_PATH ] = {};		// ファイルパス
	_tcscpy_s( pPath, _MAX_PATH, pDirectory_ );
	_tcscat_s( pPath, _MAX_PATH, pNameFile );

	// 既に作られていないか検索
	int		index;		// 要素番号
	index = GetId( pPath );
	if( index != -1 )
	{
		return pBufferItem_[ index ].pItem_;
	}

	// 作られていないとき読み込み
	index = Load( pNameFile, maximumStack );
	if( index == -1 )
	{
		return nullptr;
	}

	// リソースの返却
	return pBufferItem_[ index ].pItem_;
}

//==============================================================================
// Brief  : XAudio2インターフェースの取得
// Return : IXAudio2*							: 返却する値
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
IXAudio2* ManagerSound< TypeItem >::GetXAudio( void ) const
{
	// 値の返却
	return pXAudio_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
void ManagerSound< TypeItem >::InitializeSelf( void )
{
	// メンバ変数の初期化
	pXAudio_ = nullptr;
}

//==============================================================================
// Brief  : リソースの読み込み
// Return : int									: 実行結果
// Arg    : TCHAR* pPath						: ファイルパス
// Arg    : int index							: 格納要素番号
// Arg    : int maximumStack					: 最大同時再生数
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::LoadResource( TCHAR* pPath, int index, int maximumStack )
{
	// サウンドデータファイルの生成
	HANDLE	handleFile;		// ファイルハンドル
	handleFile = CreateFile( pPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	if( handleFile == INVALID_HANDLE_VALUE )
	{
		TCHAR	pStringError[ 512 ] = {};		// エラー文字列
		sprintf_s( pStringError, 512, _T( "ファイル\"%s\"が開けません。" ), pPath );
		PrintMsgBox( pStringError );
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	// ファイルポインタを先頭に移動
	if( SetFilePointer( handleFile, 0, NULL, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
	{
		TCHAR	pStringError[ 512 ] = {};		// エラー文字列
		sprintf_s( pStringError, 512, _T( "ファイル\"%s\"を操作できません。" ), pPath );
		PrintMsgBox( pStringError );
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	// 種類の確認
	HRESULT	result;				// 実行結果
	DWORD	sizeChunk;			// チャンクのサイズ
	DWORD	positionChunk;		// チャンクの位置
	DWORD	typeFile;			// ファイルの種類
	result = CheckChunk( handleFile, _T( 'FFIR' ), &sizeChunk, &positionChunk );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// エラー文字列
		sprintf_s( pStringError, 512, _T( "ファイル\"%s\"の種類の確認に失敗しました。" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// 種類の読み込み
	result = ReadChunk( handleFile, &typeFile, positionChunk, sizeof( DWORD ) );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// エラー文字列
		sprintf_s( pStringError, 512, _T( "ファイル\"%s\"の種類の読み込みに失敗しました。" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// 種類の確認
	if( typeFile != _T( 'EVAW' ) )
	{
		TCHAR	pStringError[ 512 ] = {};		// エラー文字列
		sprintf_s( pStringError, 512, _T( "ファイル\"%s\"の種類が不正です。" ), pPath );
		PrintMsgBox( pStringError );
		return 1;
	}

	// フォーマットの確認
	WAVEFORMATEXTENSIBLE	formatWave;		// 音声ファイルフォーマット
	ZeroMemory( &formatWave, sizeof( WAVEFORMATEXTENSIBLE ) );
	result = CheckChunk( handleFile, _T( ' tmf' ), &sizeChunk, &positionChunk );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// エラー文字列
		sprintf_s( pStringError, 512, _T( "ファイル\"%s\"のフォーマットの確認に失敗しました。" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// フォーマットの読み込み
	result = ReadChunk( handleFile, &formatWave, positionChunk, sizeChunk );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// エラー文字列
		sprintf_s( pStringError, 512, _T( "ファイル\"%s\"のフォーマットの読み込みに失敗しました。" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// オーディオデータの確認
	DWORD	sizeData;					// データのサイズ
	BYTE*	pBufferData = nullptr;		// データ格納バッファ
	result = CheckChunk( handleFile, _T( 'atad' ), &sizeData, &positionChunk );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// エラー文字列
		sprintf_s( pStringError, 512, _T( "ファイル\"%s\"の確認に失敗しました。" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// オーディオデータの格納領域を確保
	pBufferData = new BYTE[ sizeData ];
	if( pBufferData == nullptr )
	{
		return 1;
	}

	// オーディオデータの読み込み
	result = ReadChunk( handleFile, pBufferData, positionChunk, sizeData );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// エラー文字列
		sprintf_s( pStringError, 512, _T( "ファイル\"%s\"の読み込みに失敗しました。" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// ソースボイスの生成
	IXAudio2SourceVoice**	ppSourceVoice = nullptr;		// ソースボイス
	ppSourceVoice = new IXAudio2SourceVoice*[ maximumStack ];
	if( ppSourceVoice == nullptr )
	{
		return 1;
	}
	for( int counterSourceVoice = 0; counterSourceVoice < maximumStack; ++counterSourceVoice )
	{
		// ソースボイスの生成
		result = pXAudio_->CreateSourceVoice( &ppSourceVoice[ counterSourceVoice ], &(formatWave.Format) );
		if( result != S_OK )
		{
			PrintMsgBox( _T( "ソースボイスの生成に失敗しました。" ) );
			return result;
		}

		// オーディオバッファの登録
		XAUDIO2_BUFFER	bufferAudio;		// 音声ファイル用バッファ
		ZeroMemory( &bufferAudio, sizeof( XAUDIO2_BUFFER ) );
		bufferAudio.AudioBytes = sizeData;
		bufferAudio.pAudioData = pBufferData;
		bufferAudio.Flags = XAUDIO2_END_OF_STREAM;
		bufferAudio.LoopCount = 0;
		ppSourceVoice[ counterSourceVoice ]->SubmitSourceBuffer( &bufferAudio );
	}

	// サウンドの生成
	pBufferItem_[ index ].pItem_ = new Sound();
	if( pBufferItem_[ index ].pItem_ == nullptr )
	{
		return 1;
	}
	result = pBufferItem_[ index ].pItem_->Initialize( maximumStack, ppSourceVoice, pBufferData, sizeData );
	if( result != 0 )
	{
		return result;
	}

	// ソースボイス格納領域の開放
	delete[] ppSourceVoice;
	ppSourceVoice = nullptr;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : リソースの開放
// Return : void								: なし
// Arg    : int index							: 格納要素番号
//==============================================================================
template< class TypeItem >
void ManagerSound< TypeItem >::ReleaseResource( int index )
{
	// サウンドの開放
	delete pBufferItem_[ index ].pItem_;
	pBufferItem_[ index ].pItem_ = nullptr;
}

//==============================================================================
// Brief  : チャンクの確認
// Return : void								: なし
// Arg    : HANDLE handle						: ファイルハンドル
// Arg    : DWORD format						: フォーマット
// Arg    : DWORD* pSize						: チャンクサイズの格納用
// Arg    : DWORD* pPosition					: チャンク位置の格納用
//==============================================================================
template< class TypeItem >
HRESULT ManagerSound< TypeItem >::CheckChunk( HANDLE handle, DWORD format, DWORD* pSize, DWORD* pPosition )
{
	// ファイルポインタを先頭に移動
	if( SetFilePointer( handle, 0, NULL, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
	{
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	// チャンクの読み込み
	HRESULT result;			// 実行結果
	DWORD	sizeRiff;		// RIFFフォーマットのサイズ
	DWORD	offset;			// オフセット
	result = S_OK;
	sizeRiff = 0;
	offset = 0;
	while( result == S_OK )
	{
		// 種類の読み込み
		DWORD	typeChunk;		// チャンクの種類
		DWORD	byteRead;		// 読み込んだバイト数
		if( ReadFile( handle, &typeChunk, sizeof( DWORD ), &byteRead, NULL ) == 0 )
		{
			result = HRESULT_FROM_WIN32( GetLastError() );
		}

		// データサイズの読み込み
		DWORD	sizeData;		// データのサイズ
		if( ReadFile( handle, &sizeData, sizeof( DWORD ), &byteRead, NULL ) == 0 )
		{
			result = HRESULT_FROM_WIN32( GetLastError() );
		}

		// ファイルの種類の読み込み
		DWORD	typeFile;		// ファイルの種類
		switch( typeChunk )
		{
		case 'FFIR':
			//	ファイルタイプの読み込み
			sizeRiff = sizeData;
			sizeData = 4;
			if( ReadFile( handle, &typeFile, sizeof( DWORD ), &byteRead, NULL ) == 0 )
			{
				result = HRESULT_FROM_WIN32( GetLastError() );
			}
			break;

		default:
			//	ファイルポインタをチャンクデータ分移動
			if( SetFilePointer( handle, sizeData, NULL, FILE_CURRENT ) == INVALID_SET_FILE_POINTER )
			{
				return HRESULT_FROM_WIN32( GetLastError() );
			}
			break;
		}

		// サイズとオフセットを返す
		offset += sizeof( DWORD ) * 2;
		if( typeChunk == format )
		{
			*pSize = sizeData;
			*pPosition = offset;
			return S_OK;
		}

		// 
		offset += sizeData;
		if( sizeRiff <= 0 )
		{
			return S_FALSE;
		}
	}

	// 正常終了
	return S_OK;
}

//==============================================================================
// Brief  : チャンクの読み込み
// Return : void								: なし
// Arg    : HANDLE handle						: ファイルハンドル
// Arg    : void* pBuffer						: 格納バッファ
// Arg    : DWORD offset						: データのオフセット
// Arg    : DWORD size							: データのサイズ
//==============================================================================
template< class TypeItem >
HRESULT ManagerSound< TypeItem >::ReadChunk( HANDLE handle, void* pBuffer, DWORD offset, DWORD size )
{
	// ファイルポインタを指定位置まで移動
	DWORD	byteRead;		// 読み込んだバイト数
	if( SetFilePointer( handle, offset, NULL, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
	{
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	// データの読み込み
	if( ReadFile( handle, pBuffer, size, &byteRead, NULL ) == 0 )
	{
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	// 正常終了
	return S_OK;
}
