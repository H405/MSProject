//==============================================================================
//
// File   : Vertex.h
// Brief  : 頂点クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/14 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_VERTEX_H
#define MY_VERTEX_H

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

//******************************************************************************
// クラス定義
//******************************************************************************
class Vertex
{
public:
	// 頂点宣言要素値
	enum
	{
		ELEMENT_NONE				= 0x00000000,		// なし
		ELEMENT_POSITION			= 0x00000001,		// 座標
		ELEMENT_POSITION_TWEENING	= 0x00000002,		// トゥウィーニング用座標
		ELEMENT_BLEND_WEIGHT		= 0x00000004,		// ブレンド割合
		ELEMENT_BLEND_INDICIES		= 0x00000008,		// ブレンド頂点番号
		ELEMENT_NORMAL				= 0x00000010,		// 法線
		ELEMENT_NORMAL_TWEENING		= 0x00000020,		// トゥウィーニング用法線
		ELEMENT_POINT_SIZE			= 0x00000040,		// ポイントスプライトのサイズ
		ELEMENT_TEXTURE_COORD_0		= 0x00000080,		// テクスチャ座標0
		ELEMENT_TEXTURE_COORD_1		= 0x00000100,		// テクスチャ座標1
		ELEMENT_TEXTURE_COORD_2		= 0x00000200,		// テクスチャ座標2
		ELEMENT_TEXTURE_COORD_3		= 0x00000400,		// テクスチャ座標3
		ELEMENT_TANGENT				= 0x00000800,		// 接線
		ELEMENT_BINORMAL			= 0x00001000,		// 従法線
		ELEMENT_TESSELLATION_FACTOR	= 0x00002000,		// テッセレーション係数
		ELEMENT_POSITION_TRANSFORM	= 0x00004000,		// 変換済み頂点
		ELEMENT_COLOR_DIFFUSE		= 0x00008000,		// ディフューズカラー
		ELEMENT_COLOR_SPECULAR		= 0x00010000,		// スペキュラカラー
		ELEMENT_FOG					= 0x00020000,		// フォグ
		ELEMENT_DEPTH				= 0x00040000,		// 深度値
		ELEMENT_SAMPLER				= 0x00080000,		// サンプラ情報
		ELEMENT_END					= 0xFFFFFFFF		// 最後
	};

	// 頂点宣言要素の組
	enum
	{
		ELEMENT_SET_SIMPLE		= ELEMENT_POSITION | ELEMENT_NORMAL | ELEMENT_TEXTURE_COORD_0 | ELEMENT_COLOR_DIFFUSE,								// 通常セット
		ELEMENT_SET_NORMAL_MAP	= ELEMENT_POSITION | ELEMENT_NORMAL | ELEMENT_TEXTURE_COORD_0 | ELEMENT_TANGENT | ELEMENT_COLOR_DIFFUSE,			// 法線マップセット
		ELEMENT_SET_POINT		= ELEMENT_POSITION | ELEMENT_POINT_SIZE | ELEMENT_COLOR_DIFFUSE,													// ポイントスプライトセット
		ELEMENT_SET_SKIN		= ELEMENT_POSITION | ELEMENT_BLEND_WEIGHT | ELEMENT_BLEND_INDICIES | ELEMENT_NORMAL | ELEMENT_TEXTURE_COORD_0,		// スキンメッシュセット
		ELEMENT_SET_END
	};

	// 頂点宣言要素の種類
	enum
	{
		TYPE_POSITION = 0,			// 座標
		TYPE_POSITION_TWEENING,		// トゥウィーニング用座標
		TYPE_BLEND_WEIGHT,			// ブレンド割合
		TYPE_BLEND_INDICIES,		// ブレンド頂点番号
		TYPE_NORMAL,				// 法線
		TYPE_NORMAL_TWEENING,		// トゥウィーニング用法線
		TYPE_POINT_SIZE,			// ポイントスプライトのサイズ
		TYPE_TEXTURE_COORD_0,		// テクスチャ座標0
		TYPE_TEXTURE_COORD_1,		// テクスチャ座標1
		TYPE_TEXTURE_COORD_2,		// テクスチャ座標2
		TYPE_TEXTURE_COORD_3,		// テクスチャ座標3
		TYPE_TANGENT,				// 接線
		TYPE_BINORMAL,				// 従法線
		TYPE_TESSELLATION_FACTOR,	// テッセレーション係数
		TYPE_POSITION_TRANSFORM,	// 変換済み頂点
		TYPE_COLOR_DIFFUSE,			// ディフューズカラー
		TYPE_COLOR_SPECULAR,		// スペキュラカラー
		TYPE_FOG,					// フォグ
		TYPE_DEPTH,					// 深度値
		TYPE_SAMPLER,				// サンプラ情報
		TYPE_MAX					// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Vertex( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~Vertex( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : unsigned int element				: 頂点宣言要素
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice, unsigned int element );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : unsigned int element				: 頂点宣言要素
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice, unsigned int element );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : Vertex* pOut						: コピー先アドレス
	//==============================================================================
	int Copy( Vertex* pOut ) const;

	//==============================================================================
	// Brief  : 頂点宣言要素を含んでいるか判定
	// Return : bool								: 判定結果
	// Arg    : int type							: 頂点宣言要素の種類
	//==============================================================================
	bool IsContent( int type ) const;

	//==============================================================================
	// Brief  : 頂点宣言要素のオフセットを取得
	// Return : int									: オフセット
	// Arg    : int type							: 頂点宣言要素の種類
	//==============================================================================
	int GetOffset( int type ) const;

	//==============================================================================
	// アクセサ
	//==============================================================================
	int GetSize( void ) const;
	D3DVERTEXELEMENT9* GetElement( void ) const;
	IDirect3DVertexDeclaration9* GetDeclaration( void ) const;

protected:

private:
	void InitializeSelf( void );
	Vertex( const Vertex& );
	Vertex operator=( const Vertex& );

	int								countElement_;						// 頂点宣言要素数
	int								size_;								// 構造体のサイズ
	D3DVERTEXELEMENT9*				pElement_;							// 頂点宣言要素
	int								pOffsetElement_[ TYPE_MAX ];		// 頂点宣言要素のオフセット
	unsigned int					typeElement_;						// 頂点宣言要素
	IDirect3DVertexDeclaration9*	pDeclaration_;						// 頂点宣言
};

#endif	// MY_VERTEX_H
