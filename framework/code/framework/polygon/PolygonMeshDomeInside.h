//==============================================================================
//
// File   : PolygonMeshDomeInside.h
// Brief  : 内側メッシュドームポリゴン
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_POLYGON_MESH_DOME_INSIDE_H
#define MY_POLYGON_MESH_DOME_INSIDE_H

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
class PolygonMeshDomeInside
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	PolygonMeshDomeInside( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~PolygonMeshDomeInside( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : int countCellX						: X方向セル数
	// Arg    : int countCellY						: Y方向セル数
	// Arg    : float radius						: 半径
	// Arg    : float lengthTextureX				: X方向テクスチャ長さ
	// Arg    : float lengthTextureY				: Y方向テクスチャ長さ
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice, int countCellX, int countCellY,
		float radius, float lengthTextureX, float lengthTextureY );

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
	// Arg    : int countCellY						: Y方向セル数
	// Arg    : float radius						: 半径
	// Arg    : float lengthTextureX				: X方向テクスチャ長さ
	// Arg    : float lengthTextureY				: Y方向テクスチャ長さ
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice, int countCellX, int countCellY,
		float radius, float lengthTextureX, float lengthTextureY );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : PolygonMeshDomeInside* pOut			: コピー先アドレス
	//==============================================================================
	int Copy( PolygonMeshDomeInside* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Draw( void );

	//==============================================================================
	// アクセサ
	//==============================================================================
	int GetCountVertex( void ) const;
	int GetCountIndex( void ) const;
	void GetSizeIndex( size_t* pOut ) const;
	int GetCountCellX( void ) const;
	int GetCountCellY( void ) const;
	void SetRadius( float value );
	float GetRadius( void ) const;
	void SetLengthTextureX( float value );
	float GetLengthTextureX( void ) const;
	void SetLengthTextureY( float value );
	float GetLengthTextureY( void ) const;

protected:

private:
	void InitializeSelf( void );
	PolygonMeshDomeInside( const PolygonMeshDomeInside& );
	PolygonMeshDomeInside operator=( const PolygonMeshDomeInside& );

	IDirect3DDevice9*		pDevice_;				// Direct3Dデバイス
	IDirect3DVertexBuffer9*	pVertexBuffer_;			// 頂点バッファ
	IDirect3DIndexBuffer9*	pIndexBuffer_;			// インデックスバッファ
	Vertex*					pVertex_;				// 頂点情報
	int						countVertex_;			// 頂点数
	int						countIndex_;			// インデックス数
	size_t					sizeIndex_;				// インデックスのサイズ
	int						countCellX_;			// X方向セル数
	int						countCellY_;			// Y方向セル数
	float					radius_;				// 半径
	float					lengthTextureX_;		// X方向テクスチャ長さ
	float					lengthTextureY_;		// Y方向テクスチャ長さ
};

#endif	// MY_POLYGON_MESH_DOME_INSIDE_H
