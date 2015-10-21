//==============================================================================
//
// File   : PolygonMesh.h
// Brief  : メッシュポリゴン
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_POLYGON_MESH_H
#define MY_POLYGON_MESH_H

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
class PolygonMesh
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	PolygonMesh( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~PolygonMesh( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : int countCellX						: X方向セル数
	// Arg    : int countCellZ						: Z方向セル数
	// Arg    : float lengthCellX					: X方向セル長さ
	// Arg    : float lengthCellZ					: Z方向セル長さ
	// Arg    : float lengthTextureX				: X方向テクスチャ長さ
	// Arg    : float lengthTextureZ				: Z方向テクスチャ長さ
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
		float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ );

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
	// Arg    : int countCellX						: X方向セル数
	// Arg    : int countCellZ						: Z方向セル数
	// Arg    : float lengthCellX					: X方向セル長さ
	// Arg    : float lengthCellZ					: Z方向セル長さ
	// Arg    : float lengthTextureX				: X方向テクスチャ長さ
	// Arg    : float lengthTextureZ				: Z方向テクスチャ長さ
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
		float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : PolygonMesh* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( PolygonMesh* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Draw( void );

	//==============================================================================
	// Brief  : 高さの設定
	// Return : int									: 実行結果
	// Arg    : float* pHeight						: 高さ情報
	//==============================================================================
	int SetHeight( float* pHeight );

	//==============================================================================
	// アクセサ
	//==============================================================================
	int GetCountVertex( void ) const;
	int GetCountIndex( void ) const;
	void GetSizeIndex( size_t* pOut ) const;
	int GetCountCellX( void ) const;
	int GetCountCellZ( void ) const;
	void SetLengthCellX( float value );
	float GetLengthCellX( void ) const;
	void SetLengthCellZ( float value );
	float GetLengthCellZ( void ) const;
	void SetLengthTextureX( float value );
	float GetLengthTextureX( void ) const;
	void SetLengthTextureZ( float value );
	float GetLengthTextureZ( void ) const;

protected:

private:
	void InitializeSelf( void );
	PolygonMesh( const PolygonMesh& );
	PolygonMesh operator=( const PolygonMesh& );

	IDirect3DDevice9*		pDevice_;				// Direct3Dデバイス
	IDirect3DVertexBuffer9*	pVertexBuffer_;			// 頂点バッファ
	IDirect3DIndexBuffer9*	pIndexBuffer_;			// インデックスバッファ
	Vertex*					pVertex_;				// 頂点情報
	int						countVertex_;			// 頂点数
	int						countIndex_;			// インデックス数
	size_t					sizeIndex_;				// インデックスのサイズ
	int						countCellX_;			// X方向セル数
	int						countCellZ_;			// Z方向セル数
	float					lengthCellX_;			// X方向セル長さ
	float					lengthCellZ_;			// Z方向セル長さ
	float					lengthTextureX_;		// X方向テクスチャ長さ
	float					lengthTextureZ_;		// Z方向テクスチャ長さ
};

#endif	// MY_POLYGON_MESH_H
