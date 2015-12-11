//==============================================================================
//
// File   : PolygonSignboard.h
// Brief  : 足元基準ビルボードポリゴン
// Author : Taiga Shirakawa
// Date   : 2015/12/10 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_POLYGON_SIGNBOARD_H
#define MY_POLYGON_SIGNBOARD_H

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
class PolygonSignboard
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	PolygonSignboard( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~PolygonSignboard( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice );

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
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : PolygonSignboard* pOut						: コピー先アドレス
	//==============================================================================
	int Copy( PolygonSignboard* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Draw( void );

protected:

private:
	void InitializeSelf( void );
	PolygonSignboard( const PolygonSignboard& );
	PolygonSignboard operator=( const PolygonSignboard& );

	static const int	COUNT_VERTEX = 4;			// 頂点数
	static const int	COUNT_VERTEX_LINE = 2;		// 一列の頂点数

	IDirect3DDevice9*		pDevice_;			// Direct3Dデバイス
	IDirect3DVertexBuffer9*	pVertexBuffer_;		// 頂点バッファ
	Vertex*					pVertex_;			// 頂点情報
};

#endif	// MY_POLYGON_SIGNBOARD_H
