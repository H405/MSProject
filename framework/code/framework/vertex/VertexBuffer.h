//==============================================================================
//
// File   : VertexBuffer.h
// Brief  : 頂点バッファへ値を設定するためのバッファ
// Author : Taiga Shirakawa
// Date   : 2015/10/14 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_VERTEX_BUFFER_H
#define MY_VERTEX_BUFFER_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Vertex;

//******************************************************************************
// クラス定義
//******************************************************************************
class VertexBuffer
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	VertexBuffer( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~VertexBuffer( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int count							: 確保する数
	// Arg    : Vertex* pVertex						: 頂点情報
	//==============================================================================
	int Initialize( int count, Vertex* pVertex );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : int count							: 確保する数
	// Arg    : Vertex* pVertex						: 頂点情報
	//==============================================================================
	int Reinitialize( int count, Vertex* pVertex );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : VertexBuffer* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( VertexBuffer* pOut ) const;

	//==============================================================================
	// アクセサ
	//==============================================================================
	void* GetBuffer( void ) const;

	void SetPosition( int index, const D3DXVECTOR3& value );
	void SetPosition( int index, float x, float y, float z );
	void SetPositionX( int index, float x );
	void SetPositionY( int index, float y );
	void SetPositionZ( int index, float z );
	void SetPositionTweening( int index, const D3DXVECTOR3& value );
	void SetPositionTweening( int index, float x, float y, float z );
	void SetPositionTweeningX( int index, float x );
	void SetPositionTweeningY( int index, float y );
	void SetPositionTweeningZ( int index, float z );
	void SetBlendWeight( int index, const D3DXVECTOR3& value );
	void SetBlendWeight( int index, float x, float y, float z );
	void SetBlendWeightX( int index, float x );
	void SetBlendWeightY( int index, float y );
	void SetBlendWeightZ( int index, float z );
	void SetBlendIndecies( int index, unsigned char value0, unsigned char value1, unsigned char value2, unsigned char value3 );
	void SetBlendIndecies0( int index, unsigned char value );
	void SetBlendIndecies1( int index, unsigned char value );
	void SetBlendIndecies2( int index, unsigned char value );
	void SetBlendIndecies3( int index, unsigned char value );
	void SetNormal( int index, const D3DXVECTOR3& value );
	void SetNormal( int index, float x, float y, float z );
	void SetNormalX( int index, float x );
	void SetNormalY( int index, float y );
	void SetNormalZ( int index, float z );
	void SetNormalTweening( int index, const D3DXVECTOR3& value );
	void SetNormalTweening( int index, float x, float y, float z );
	void SetNormalTweeningX( int index, float x );
	void SetNormalTweeningY( int index, float y );
	void SetNormalTweeningZ( int index, float z );
	void SetPointSize( int index, float value );
	void SetTextureCoord0( int index, const D3DXVECTOR2& value );
	void SetTextureCoord0( int index, float x, float y );
	void SetTextureCoord0X( int index, float x );
	void SetTextureCoord0Y( int index, float y );
	void SetTextureCoord1( int index, const D3DXVECTOR2& value );
	void SetTextureCoord1( int index, float x, float y );
	void SetTextureCoord1X( int index, float x );
	void SetTextureCoord1Y( int index, float y );
	void SetTextureCoord2( int index, const D3DXVECTOR2& value );
	void SetTextureCoord2( int index, float x, float y );
	void SetTextureCoord2X( int index, float x );
	void SetTextureCoord2Y( int index, float y );
	void SetTextureCoord3( int index, const D3DXVECTOR2& value );
	void SetTextureCoord3( int index, float x, float y );
	void SetTextureCoord3X( int index, float x );
	void SetTextureCoord3Y( int index, float y );
	void SetTangent( int index, const D3DXVECTOR3& value );
	void SetTangent( int index, float x, float y, float z );
	void SetTangentX( int index, float x );
	void SetTangentY( int index, float y );
	void SetTangentZ( int index, float z );
	void SetBinormal( int index, const D3DXVECTOR3& value );
	void SetBinormal( int index, float x, float y, float z );
	void SetBinormalX( int index, float x );
	void SetBinormalY( int index, float y );
	void SetBinormalZ( int index, float z );
	void SetTessellationFactor( int index, float value );
	void SetPositionTransform( int index, const D3DXVECTOR3& value );
	void SetPositionTransform( int index, float x, float y, float z );
	void SetPositionTransformX( int index, float x );
	void SetPositionTransformY( int index, float y );
	void SetPositionTransformZ( int index, float z );
	void SetColorDiffuse( int index, const D3DXCOLOR& value );
	void SetColorDiffuse( int index, float r, float g, float b, float a );
	void SetColorSpecular( int index, const D3DXCOLOR& value );
	void SetColorSpecular( int index, float r, float g, float b, float a );
	void SetFog( int index, float value );
	void SetDepth( int index, float value );
	void SetSampler( int index, float value );

protected:

private:
	void InitializeSelf( void );
	void SetToBuffer( int type, int index, void* pValue, size_t size, int offset = 0 );

	VertexBuffer( const VertexBuffer& );
	VertexBuffer operator=( const VertexBuffer& );

	char*			pBuffer_;		// バッファ
	unsigned int	size_;			// バッファサイズ
	Vertex*			pVertex_;		// 頂点情報
};

#endif	// MY_VERTEX_BUFFER_H
