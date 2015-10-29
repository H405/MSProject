//==============================================================================
//
// File   : File.cpp
// Brief  : ファイル読み込みクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/29 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "File.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// テンプレート宣言
//******************************************************************************
template void File::Read( char* pOut, int count );
template void File::Read( unsigned char* pOut, int count );
template void File::Read( short* pOut, int count );
template void File::Read( unsigned short* pOut, int count );
template void File::Read( int* pOut, int count );
template void File::Read( unsigned int* pOut, int count );
template void File::Read( long* pOut, int count );
template void File::Read( unsigned long* pOut, int count );
template void File::Read( long long* pOut, int count );
template void File::Read( unsigned long long* pOut, int count );
template void File::Read( float* pOut, int count );
template void File::Read( double* pOut, int count );

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
File::File( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
File::~File( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : const TCHAR* pNameFile				: ファイル名
//==============================================================================
int File::Initialize( const TCHAR* pNameFile )
{
	// ファイルを開く
	_tfopen_s( &pFile_, pNameFile, "rb" );
	if( pFile_ == nullptr )
	{
		return 1;
	}

	// ヘッダの読み取り
	char	aBufferHeader[ 32 ] = { 0 };
	fread( &aBufferHeader[ 0 ], sizeof( char ), 32, pFile_ );

	// ヘッダ情報の格納
	memcpy( &pType_[ 0 ], &aBufferHeader[ 0x00 ], sizeof( char ) * 4 );
	pType_[ 4 ] = '\0';
	memcpy( &size_, &aBufferHeader[ 0x04 ], sizeof( unsigned long ) );
	memcpy( &version_, &aBufferHeader[ 0x08 ], sizeof( unsigned long ) );
	memcpy( &form_, &aBufferHeader[ 0x0C ], sizeof( unsigned long ) );
	memcpy( &code_, &aBufferHeader[ 0x10 ], sizeof( unsigned short ) );
	memcpy( &compress_, &aBufferHeader[ 0x12 ], sizeof( unsigned short ) );

	// バッファ格納領域の確保
	pBuffer_ = new char[ size_ ];
	if( pBuffer_ == nullptr )
	{
		this->~File();
		return 1;
	}

	// ファイルの読み込み
	if( fread( &pBuffer_[ 0 ], sizeof( char ), size_, pFile_ ) != size_ )
	{
		this->~File();
		return 1;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int File::Finalize( void )
{
	// ファイルを閉じる
	if( pFile_ != nullptr )
	{
		fclose( pFile_ );
		pFile_ = nullptr;
	}

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : const TCHAR* pNameFile				: ファイル名
//==============================================================================
int File::Reinitialize( const TCHAR* pNameFile )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pNameFile );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : File* pOut							: コピー先アドレス
//==============================================================================
int File::Copy( File* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 種類の判定
// Return : bool								: 種類かどうか
// Arg    : const TCHAR* pType					: ファイルの種類
//==============================================================================
bool File::IsType( const TCHAR* pType )
{
	// 比較
	if( !_tcscmp( &pType_ [ 0 ], pType ) )
	{
		return true;
	}
	return false;
}

//==============================================================================
// Brief  : 読み込み
// Return : void								: なし
// Arg    : Type* pOut							: 値の格納先アドレス
// Arg    : int count							: 読み込み要素数
//==============================================================================
template< typename Type >
void File::Read( Type* pOut, int count )
{
	// 出力先へ書き込み
	unsigned long	size = sizeof( Type ) * count;
	memcpy( pOut, &pBuffer_[ cursor_ ], size );

	// カーソルの移動
	cursor_ += size;
}

//==============================================================================
// Brief  : カーソルの設定
// Return : void								: なし
// Arg    : unsigned long value					: 設定する値
//==============================================================================
void File::SetCursor( unsigned long value )
{
	// 値の設定
	cursor_ = value;
}

//==============================================================================
// Brief  : カーソルの取得
// Return : unsigned long						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned long File::GetCursor( void ) const
{
	// 値の返却
	return cursor_;
}

//==============================================================================
// Brief  : カーソルの加算
// Return : void								: なし
// Arg    : unsigned long value					: 加算値
//==============================================================================
void File::AddCursor( unsigned long value )
{
	// 値の加算
	cursor_ += value;
}

//==============================================================================
// Brief  : 種類の取得
// Return : void								: なし
// Arg    : TCHAR* pOut							: 値の格納アドレス
// Arg    : int lengthOut						: 値の格納アドレスのサイズ
//==============================================================================
void File::GetType( TCHAR* pOut, int lengthOut ) const
{
	// 値の返却
	_tcscpy_s( pOut, lengthOut, pType_ );
}

//==============================================================================
// Brief  : ファイルサイズの取得
// Return : unsigned long						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned long File::GetSize( void ) const
{
	// 値の返却
	return size_;
}

//==============================================================================
// Brief  : バージョンの取得
// Return : unsigned long						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned long File::GetVersion( void ) const
{
	// 値の返却
	return version_;
}

//==============================================================================
// Brief  : 保存形式の取得
// Return : unsigned long						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned long File::GetForm( void ) const
{
	// 値の返却
	return form_;
}

//==============================================================================
// Brief  : 暗号化形式の取得
// Return : unsigned short						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned short File::GetCode( void ) const
{
	// 値の返却
	return code_;
}

//==============================================================================
// Brief  : 圧縮形式の取得
// Return : unsigned short						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned short File::GetCompress( void ) const
{
	// 値の返却
	return compress_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void File::InitializeSelf( void )
{
	// メンバ変数の初期化
	pFile_ = nullptr;
	pBuffer_ = nullptr;
	cursor_ = 0;
	for( int counterCharacter = 0; counterCharacter < COUNT_SIZE_TYPE + 1; ++counterCharacter )
	{
		pType_[ counterCharacter ] = _T( '\0' );
	}
	size_ = 0;
	version_ = 0;
	form_ = 0;
	code_ = 0;
	compress_ = 0;
}
