//==============================================================================
//
// File   : VertexBuffer.cpp
// Brief  : 頂点バッファへ値を設定するためのバッファ
// Author : Taiga Shirakawa
// Date   : 2015/10/14 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "VertexBuffer.h"
#include "Vertex.h"

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
VertexBuffer::VertexBuffer( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
VertexBuffer::~VertexBuffer( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int count							: 確保する数
// Arg    : Vertex* pVertex						: 頂点情報
//==============================================================================
int VertexBuffer::Initialize( int count, Vertex* pVertex )
{
	// メンバ変数の設定
	pVertex_ = pVertex;

	// バッファの確保
	int		sizeItem;		// 構造体のサイズ
	sizeItem = pVertex->GetSize();
	size_ = static_cast< unsigned int >( sizeItem * count );
	pBuffer_ = new char[ size_ ];
	if( pBuffer_ == nullptr )
	{
		return 1;
	}
	ZeroMemory( pBuffer_, size_ );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int VertexBuffer::Finalize( void )
{
	// バッファの開放
	delete[] pBuffer_;
	pBuffer_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : int count							: 確保する数
// Arg    : Vertex* pVertex						: 頂点情報
//==============================================================================
int VertexBuffer::Reinitialize( int count, Vertex* pVertex )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( count, pVertex );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : VertexBuffer* pOut					: コピー先アドレス
//==============================================================================
int VertexBuffer::Copy( VertexBuffer* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : バッファの取得
// Return : void*								: 返却する値
// Arg    : void								: なし
//==============================================================================
void* VertexBuffer::GetBuffer( void ) const
{
	// 値の返却
	return pBuffer_;
}

//==============================================================================
// Brief  : 座標の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void VertexBuffer::SetPosition( int index, const D3DXVECTOR3& value )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_POSITION, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : 座標の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetPosition( int index, float x, float y, float z )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_POSITION, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : 座標のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetPositionX( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_POSITION, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : 座標のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetPositionY( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_POSITION, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : 座標のZ値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetPositionZ( int index, float z )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_POSITION, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : トゥウィーニング用座標の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void VertexBuffer::SetPositionTweening( int index, const D3DXVECTOR3& value )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_POSITION_TWEENING, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : トゥウィーニング用座標の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetPositionTweening( int index, float x, float y, float z )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_POSITION_TWEENING, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : トゥウィーニング用座標のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetPositionTweeningX( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_POSITION_TWEENING, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : トゥウィーニング用座標のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetPositionTweeningY( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_POSITION_TWEENING, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : トゥウィーニング用座標のZ値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetPositionTweeningZ( int index, float z )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_POSITION_TWEENING, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : ブレンド割合の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void VertexBuffer::SetBlendWeight( int index, const D3DXVECTOR3& value )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_BLEND_WEIGHT, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : ブレンド割合の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetBlendWeight( int index, float x, float y, float z )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_BLEND_WEIGHT, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : ブレンド割合のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetBlendWeightX( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_BLEND_WEIGHT, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : ブレンド割合のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetBlendWeightY( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_BLEND_WEIGHT, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : ブレンド割合のZ値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetBlendWeightZ( int index, float z )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_BLEND_WEIGHT, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : ブレンド頂点番号の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : unsigned long value					: 設定する値
//==============================================================================
void VertexBuffer::SetBlendIndecies( int index, unsigned char value0, unsigned char value1, unsigned char value2, unsigned char value3 )
{
	// バッファに設定
	unsigned char	pBufferSet[ 4 ];
	pBufferSet[ 0 ] = value0;
	pBufferSet[ 1 ] = value1;
	pBufferSet[ 2 ] = value2;
	pBufferSet[ 3 ] = value3;
	SetToBuffer( index, Vertex::TYPE_BLEND_INDICIES, pBufferSet, sizeof( unsigned char ) * 4 );
}

//==============================================================================
// Brief  : ブレンド頂点番号の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : unsigned char value					: 設定する値
//==============================================================================
void VertexBuffer::SetBlendIndecies0( int index, unsigned char value )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_BLEND_INDICIES, &value, sizeof( unsigned char ) );
}

//==============================================================================
// Brief  : ブレンド頂点番号の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : unsigned char value					: 設定する値
//==============================================================================
void VertexBuffer::SetBlendIndecies1( int index, unsigned char value )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_BLEND_INDICIES, &value, sizeof( unsigned char ), sizeof( unsigned char ) );
}

//==============================================================================
// Brief  : ブレンド頂点番号の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : unsigned char value					: 設定する値
//==============================================================================
void VertexBuffer::SetBlendIndecies2( int index, unsigned char value )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_BLEND_INDICIES, &value, sizeof( unsigned char ), sizeof( unsigned char ) * 2 );
}

//==============================================================================
// Brief  : ブレンド頂点番号の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : unsigned char value					: 設定する値
//==============================================================================
void VertexBuffer::SetBlendIndecies3( int index, unsigned char value )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_BLEND_INDICIES, &value, sizeof( unsigned char ), sizeof( unsigned char ) * 3 );
}

//==============================================================================
// Brief  : 法線の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void VertexBuffer::SetNormal( int index, const D3DXVECTOR3& value )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_NORMAL, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : 法線の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetNormal( int index, float x, float y, float z )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_NORMAL, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : 法線のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetNormalX( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_NORMAL, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : 法線のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetNormalY( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_NORMAL, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : 法線のZ値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetNormalZ( int index, float z )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_NORMAL, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : トゥウィーニング用法線の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void VertexBuffer::SetNormalTweening( int index, const D3DXVECTOR3& value )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_NORMAL_TWEENING, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : トゥウィーニング用法線の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetNormalTweening( int index, float x, float y, float z )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_NORMAL_TWEENING, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : トゥウィーニング用法線のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetNormalTweeningX( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_NORMAL_TWEENING, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : トゥウィーニング用法線のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetNormalTweeningY( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_NORMAL_TWEENING, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : トゥウィーニング用法線のZ値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetNormalTweeningZ( int index, float z )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_NORMAL_TWEENING, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : ポイントスプライトサイズの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float value							: 設定する値
//==============================================================================
void VertexBuffer::SetPointSize( int index, float value )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_POINT_SIZE, &value, sizeof( float ) );
}

//==============================================================================
// Brief  : テクスチャ座標0の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR2& value			: 設定する値
//==============================================================================
void VertexBuffer::SetTextureCoord0( int index, const D3DXVECTOR2& value )
{
	// バッファに設定
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_0, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : テクスチャ座標0の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetTextureCoord0( int index, float x, float y )
{
	// バッファに設定
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_0, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : テクスチャ座標0のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetTextureCoord0X( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_0, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : テクスチャ座標0のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetTextureCoord0Y( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_0, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : テクスチャ座標1の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR2& value			: 設定する値
//==============================================================================
void VertexBuffer::SetTextureCoord1( int index, const D3DXVECTOR2& value )
{
	// バッファに設定
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_1, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : テクスチャ座標1の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetTextureCoord1( int index, float x, float y )
{
	// バッファに設定
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_1, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : テクスチャ座標1のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetTextureCoord1X( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_1, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : テクスチャ座標1のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetTextureCoord1Y( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_1, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : テクスチャ座標2の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR2& value			: 設定する値
//==============================================================================
void VertexBuffer::SetTextureCoord2( int index, const D3DXVECTOR2& value )
{
	// バッファに設定
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_2, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : テクスチャ座標2の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetTextureCoord2( int index, float x, float y )
{
	// バッファに設定
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_2, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : テクスチャ座標2のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetTextureCoord2X( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_2, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : テクスチャ座標2のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetTextureCoord2Y( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_2, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : テクスチャ座標3の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR2& value			: 設定する値
//==============================================================================
void VertexBuffer::SetTextureCoord3( int index, const D3DXVECTOR2& value )
{
	// バッファに設定
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_3, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : テクスチャ座標3の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetTextureCoord3( int index, float x, float y )
{
	// バッファに設定
	float	pBufferSet[ 2 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_3, pBufferSet, sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : テクスチャ座標3のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetTextureCoord3X( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_3, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : テクスチャ座標3のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetTextureCoord3Y( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TEXTURE_COORD_3, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : 接線の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void VertexBuffer::SetTangent( int index, const D3DXVECTOR3& value )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_TANGENT, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : 接線の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetTangent( int index, float x, float y, float z )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_TANGENT, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : 接線のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetTangentX( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TANGENT, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : 接線のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetTangentY( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TANGENT, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : 接線のZ値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetTangentZ( int index, float z )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TANGENT, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : 従法線の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void VertexBuffer::SetBinormal( int index, const D3DXVECTOR3& value )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_BINORMAL, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : 従法線の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetBinormal( int index, float x, float y, float z )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_BINORMAL, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : 従法線のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetBinormalX( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_BINORMAL, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : 従法線のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetBinormalY( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_BINORMAL, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : 従法線のZ値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetBinormalZ( int index, float z )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_BINORMAL, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : テッセレーション係数の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float value							: 設定する値
//==============================================================================
void VertexBuffer::SetTessellationFactor( int index, float value )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_TESSELLATION_FACTOR, &value, sizeof( float ) );
}

//==============================================================================
// Brief  : 変換済み頂点の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void VertexBuffer::SetPositionTransform( int index, const D3DXVECTOR3& value )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = value.x;
	pBufferSet[ 1 ] = value.y;
	pBufferSet[ 2 ] = value.z;
	SetToBuffer( index, Vertex::TYPE_POSITION_TRANSFORM, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : 変換済み頂点の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetPositionTransform( int index, float x, float y, float z )
{
	// バッファに設定
	float	pBufferSet[ 3 ];
	pBufferSet[ 0 ] = x;
	pBufferSet[ 1 ] = y;
	pBufferSet[ 2 ] = z;
	SetToBuffer( index, Vertex::TYPE_POSITION_TRANSFORM, pBufferSet, sizeof( float ) * 3 );
}

//==============================================================================
// Brief  : 変換済み頂点のX値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float x								: X値
//==============================================================================
void VertexBuffer::SetPositionTransformX( int index, float x )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_POSITION_TRANSFORM, &x, sizeof( float ) );
}

//==============================================================================
// Brief  : 変換済み頂点のY値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float y								: Y値
//==============================================================================
void VertexBuffer::SetPositionTransformY( int index, float y )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_POSITION_TRANSFORM, &y, sizeof( float ), sizeof( float ) );
}

//==============================================================================
// Brief  : 変換済み頂点のZ値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float z								: Z値
//==============================================================================
void VertexBuffer::SetPositionTransformZ( int index, float z )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_POSITION_TRANSFORM, &z, sizeof( float ), sizeof( float ) * 2 );
}

//==============================================================================
// Brief  : ディフューズカラーの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXCOLOR& value				: 設定する値
//==============================================================================
void VertexBuffer::SetColorDiffuse( int index, const D3DXCOLOR& value )
{
	// バッファに設定
	D3DXCOLOR	color;			// 色
	D3DCOLOR	colorSet;		// 設定する色
	color.r = value.r;
	color.g = value.g;
	color.b = value.b;
	color.a = value.a;
	colorSet = color;
	SetToBuffer( index, Vertex::TYPE_COLOR_DIFFUSE, &colorSet, sizeof( DWORD ) );
}

//==============================================================================
// Brief  : ディフューズカラーのRGBA値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
// Arg    : float a								: A値
//==============================================================================
void VertexBuffer::SetColorDiffuse( int index, float r, float g, float b, float a )
{
	// バッファに設定
	D3DXCOLOR	color;			// 色
	D3DCOLOR	colorSet;		// 設定する色
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	colorSet = color;
	SetToBuffer( index, Vertex::TYPE_COLOR_DIFFUSE, &colorSet, sizeof( DWORD ) );
}

//==============================================================================
// Brief  : スペキュラカラーの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXCOLOR& value				: 設定する値
//==============================================================================
void VertexBuffer::SetColorSpecular( int index, const D3DXCOLOR& value )
{
	// バッファに設定
	D3DXCOLOR	color;			// 色
	D3DCOLOR	colorSet;		// 設定する色
	color.r = value.r;
	color.g = value.g;
	color.b = value.b;
	color.a = value.a;
	colorSet = color;
	SetToBuffer( index, Vertex::TYPE_COLOR_SPECULAR, &colorSet, sizeof( DWORD ) );
}

//==============================================================================
// Brief  : スペキュラカラーのRGBA値の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
// Arg    : float a								: A値
//==============================================================================
void VertexBuffer::SetColorSpecular( int index, float r, float g, float b, float a )
{
	// バッファに設定
	D3DXCOLOR	color;			// 色
	D3DCOLOR	colorSet;		// 設定する色
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	colorSet = color;
	SetToBuffer( index, Vertex::TYPE_COLOR_SPECULAR, &colorSet, sizeof( DWORD ) );
}

//==============================================================================
// Brief  : フォグ情報の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float value							: 設定する値
//==============================================================================
void VertexBuffer::SetFog( int index, float value )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_FOG, &value, sizeof( float ) );
}

//==============================================================================
// Brief  : 深度情報の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float value							: 設定する値
//==============================================================================
void VertexBuffer::SetDepth( int index, float value )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_DEPTH, &value, sizeof( float ) );
}

//==============================================================================
// Brief  : サンプラ情報の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : float value							: 設定する値
//==============================================================================
void VertexBuffer::SetSampler( int index, float value )
{
	// バッファに設定
	SetToBuffer( index, Vertex::TYPE_SAMPLER, &value, sizeof( float ) );
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void VertexBuffer::InitializeSelf( void )
{
	// メンバ変数の初期化
	pBuffer_ = nullptr;
	size_ = 0;
	pVertex_ = nullptr;
}

//==============================================================================
// Brief  : バッファへ値を設定
// Return : void								: なし
// Arg    : int type							: 要素の種類
// Arg    : int index							: 設定する番号
// Arg    : void* pValue						: 設定する値
// Arg    : size_t size							: 設定するサイズ
// Arg    : int offset							: 追加のオフセット
//==============================================================================
void VertexBuffer::SetToBuffer( int index, int type, void* pValue, size_t size, int offset )
{
	// 要素が含まれているか確認
	if( !pVertex_->IsContent( type ) )
	{
		return;
	}

	// 設定するための情報を取得
	int		sizeItem;			// 構造体のサイズ
	int		offsetBegin;		// 開始オフセット
	sizeItem = pVertex_->GetSize();
	offsetBegin = pVertex_->GetOffset( type );

	// バッファに設定
	unsigned int	offsetTotal;		// 総オフセット
	offsetTotal = sizeItem * index + offsetBegin + offset;
	memcpy_s( &pBuffer_[ offsetTotal ], size_ - offsetTotal, pValue, size );
}
