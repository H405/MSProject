//==============================================================================
//
// File   : Vertex.cpp
// Brief  : 頂点クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/14 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
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
Vertex::Vertex( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Vertex::~Vertex( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : unsigned int element				: 頂点宣言要素
//==============================================================================
int Vertex::Initialize( IDirect3DDevice9* pDevice, unsigned int element )
{
	// メンバ変数の設定
	typeElement_ = element;

	// 要素数を数える
	unsigned int	bitCheck;		// 確認用ビット
	bitCheck = 1;
	for( int counterElement = 0; counterElement < TYPE_MAX; ++counterElement )
	{
		if( (element & bitCheck) != 0 )
		{
			++countElement_;
		}
		bitCheck <<= 1;
	}

	// 要素がなければ終了
	if( countElement_ <= 0 )
	{
		return 0;
	}

	// 頂点宣言要素の格納領域を確保
	pElement_ = new D3DVERTEXELEMENT9[ countElement_ + 1 ];
	for( int counterElement = 0; counterElement < countElement_ + 1; ++counterElement )
	{
		pElement_[ counterElement ].Stream = 0;
		pElement_[ counterElement ].Method = D3DDECLMETHOD_DEFAULT;
	}
	pElement_[ countElement_ ].Stream = 0xFF;
	pElement_[ countElement_ ].Offset = 0;
	pElement_[ countElement_ ].Type = D3DDECLTYPE_UNUSED;
	pElement_[ countElement_ ].Usage = 0;
	pElement_[ countElement_ ].UsageIndex = 0;

	// オフセットと頂点宣言要素の生成
	int		indexCurrent;					// 現在の番号
	int		offsetCurrent;					// 現在のオフセット
	int		pType[ TYPE_MAX ] =				// データ型
	{
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_UBYTE4,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT1,
		D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT1,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_D3DCOLOR,
		D3DDECLTYPE_D3DCOLOR,
		D3DDECLTYPE_FLOAT1,
		D3DDECLTYPE_FLOAT1,
		D3DDECLTYPE_FLOAT1
	};
	int		pUsage[ TYPE_MAX ] =			// 使用方法
	{
		D3DDECLUSAGE_POSITION,
		D3DDECLUSAGE_POSITION,
		D3DDECLUSAGE_BLENDWEIGHT,
		D3DDECLUSAGE_BLENDINDICES,
		D3DDECLUSAGE_NORMAL,
		D3DDECLUSAGE_NORMAL,
		D3DDECLUSAGE_PSIZE,
		D3DDECLUSAGE_TEXCOORD,
		D3DDECLUSAGE_TEXCOORD,
		D3DDECLUSAGE_TEXCOORD,
		D3DDECLUSAGE_TEXCOORD,
		D3DDECLUSAGE_TANGENT,
		D3DDECLUSAGE_BINORMAL,
		D3DDECLUSAGE_TESSFACTOR,
		D3DDECLUSAGE_POSITIONT,
		D3DDECLUSAGE_COLOR,
		D3DDECLUSAGE_COLOR,
		D3DDECLUSAGE_FOG,
		D3DDECLUSAGE_DEPTH,
		D3DDECLUSAGE_SAMPLE
	};
	int		pUsageIndex[ TYPE_MAX ] =		// 使用方法番号
	{
		0,
		1,
		0,
		0,
		0,
		1,
		0,
		0,
		1,
		2,
		3,
		0,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0
	};
	int		pOffset[ TYPE_MAX ] =			// オフセット量
	{
		12,
		12,
		12,
		4,
		12,
		12,
		4,
		8,
		8,
		8,
		8,
		12,
		12,
		4,
		12,
		4,
		4,
		4,
		4,
		4
	};
	indexCurrent = 0;
	offsetCurrent = 0;
	bitCheck = 1;
	for( int counterElement = 0; counterElement < TYPE_MAX; ++counterElement, bitCheck <<= 1 )
	{
		// 要素が含まれていないなら次へ
		if( (element & bitCheck) == 0 )
		{
			continue;
		}

		// 要素の設定
		pElement_[ indexCurrent ].Offset = offsetCurrent;
		pElement_[ indexCurrent ].Type = pType[ counterElement ];
		pElement_[ indexCurrent ].Usage = pUsage[ counterElement ];
		pElement_[ indexCurrent ].UsageIndex = pUsageIndex[ counterElement ];

		// 格納する要素番号を次へ進める
		++indexCurrent;

		// オフセットを計算
		pOffsetElement_[ counterElement ] = offsetCurrent;
		offsetCurrent += pOffset[ counterElement ];
	}
	size_ = offsetCurrent;

	// 頂点宣言
	HRESULT	result;		// 実行結果
	result = pDevice->CreateVertexDeclaration( pElement_, &pDeclaration_ );
	if( result != S_OK )
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
int Vertex::Finalize( void )
{
	// 頂点宣言の開放
	if( pDeclaration_ != nullptr )
	{
		pDeclaration_->Release();
		pDeclaration_ = nullptr;
	}

	// 格納領域の開放
	delete[] pElement_;
	pElement_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : unsigned int element				: 頂点宣言要素
//==============================================================================
int Vertex::Reinitialize( IDirect3DDevice9* pDevice, unsigned int element )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice, element );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Vertex* pOut						: コピー先アドレス
//==============================================================================
int Vertex::Copy( Vertex* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 頂点宣言要素を含んでいるか判定
// Return : bool								: 判定結果
// Arg    : int type							: 頂点宣言要素の種類
//==============================================================================
bool Vertex::IsContent( int type ) const
{
	// ビットの生成
	int		bitCheck;		// 確認用ビット
	bitCheck = 1;
	for( int loop = 0; loop < type; ++loop )
	{
		bitCheck <<= 1;
	}

	// 値の返却
	return (typeElement_ & bitCheck) != 0;
}

//==============================================================================
// Brief  : 頂点宣言要素のオフセットを取得
// Return : int									: オフセット
// Arg    : int type							: 頂点宣言要素の種類
//==============================================================================
int Vertex::GetOffset( int type ) const
{
	// 値の返却
	return pOffsetElement_[ type ];
}

//==============================================================================
// Brief  : 構造体のサイズの取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int Vertex::GetSize( void ) const
{
	// 値の返却
	return size_;
}

//==============================================================================
// Brief  : 頂点宣言要素の取得
// Return : D3DVERTEXELEMENT9*					: 頂点宣言の先頭アドレス
// Arg    : void								: なし
//==============================================================================
D3DVERTEXELEMENT9* Vertex::GetElement( void ) const
{
	// 値の返却
	return pElement_;
}

//==============================================================================
// Brief  : 頂点宣言の取得
// Return : IDirect3DVertexDeclaration9*		: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DVertexDeclaration9* Vertex::GetDeclaration( void ) const
{
	// 値の返却
	return pDeclaration_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Vertex::InitializeSelf( void )
{
	// メンバ変数の初期化
	countElement_ = 0;
	size_ = 0;
	pElement_ = nullptr;
	for( int counterElement = 0; counterElement < TYPE_MAX; ++counterElement )
	{
		pOffsetElement_[ counterElement ] = 0;
	}
	typeElement_ = 0;
	pDeclaration_ = nullptr;
}
