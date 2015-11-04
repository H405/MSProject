//==============================================================================
//
// File   : ModelConvert.h
// Brief  : 変換済みモデル
// Author : Taiga Shirakawa
// Date   : 2015/10/29 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_MODEL_CONVERT_H
#define MY_MODEL_CONVERT_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "Model.h"

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
class ModelConvert : public Model
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ModelConvert( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ModelConvert( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : unsigned int elementVertex			: 頂点の要素
	// Arg    : unsigned int countMaterial			: マテリアル数
	// Arg    : unsigned int countTexture			: テクスチャ数
	// Arg    : unsigned long countMesh				: メッシュ数
	// Arg    : unsigned long countBone				: ボーン数
	// Arg    : void* pVertexBuffer					: メッシュの頂点情報
	// Arg    : const int* pCountVertex				: メッシュの頂点数
	// Arg    : Material* pMaterial					: メッシュのマテリアル情報
	// Arg    : const int* pIndexMaterial			: メッシュのマテリアル番号
	// Arg    : IDirect3DTexture9** ppTexture		: メッシュのテクスチャ情報
	// Arg    : const int* pIndexTexture			: メッシュのテクスチャ番号
	// Arg    : const D3DXMATRIX* pMatrixBone		: ボーンの初期姿勢行列
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice, unsigned int elementVertex,
		unsigned int countMaterial, unsigned int countTexture, unsigned long countMesh, unsigned long countBone,
		void** ppVertexBuffer, const int* pCountVertex, Material* pMaterial, const int* pIndexMaterial,
		IDirect3DTexture9** ppTexture, const int* pIndexTexture, const D3DXMATRIX* pMatrixBone );

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
	// Arg    : unsigned int elementVertex			: 頂点の要素
	// Arg    : unsigned int countMaterial			: マテリアル数
	// Arg    : unsigned int countTexture			: テクスチャ数
	// Arg    : unsigned long countMesh				: メッシュ数
	// Arg    : unsigned long countBone				: ボーン数
	// Arg    : void* pVertexBuffer					: メッシュの頂点情報
	// Arg    : const int* pCountVertex				: メッシュの頂点数
	// Arg    : Material* pMaterial					: メッシュのマテリアル情報
	// Arg    : const int* pIndexMaterial			: メッシュのマテリアル番号
	// Arg    : IDirect3DTexture9** ppTexture		: メッシュのテクスチャ情報
	// Arg    : const int* pIndexTexture			: メッシュのテクスチャ番号
	// Arg    : const D3DXMATRIX* pMatrixBone		: ボーンの初期姿勢行列
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice, unsigned int elementVertex,
		unsigned int countMaterial, unsigned int countTexture, unsigned long countMesh, unsigned long countBone,
		void** ppVertexBuffer, const int* pCountVertex, Material* pMaterial, const int* pIndexMaterial,
		IDirect3DTexture9** ppTexture, const int* pIndexTexture, const D3DXMATRIX* pMatrixBone );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ModelConvert* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( ModelConvert* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : int indexMaterial					: 描画マテリアル番号
	//==============================================================================
	void Draw( int indexMaterial );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void GetMaterial( int index, Material* pOut ) const;
	IDirect3DTexture9* GetTexture( int index ) const;
	unsigned long GetCountMesh( void ) const;
	unsigned long GetCountBone( void ) const;
	void SetIndexMaterial( int index, const int& value );
	void GetIndexMaterial( int index, int* pOut ) const;
	void SetIndexTexture( int index, const int& value );
	void GetIndexTexture( int index, int* pOut ) const;
	void SetMatrixBone( int index, const D3DXMATRIX& value );
	void GetMatrixBone( int index, D3DXMATRIX* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	ModelConvert( const ModelConvert& );
	ModelConvert operator=( const ModelConvert& );

	unsigned long				countMesh_;				// メッシュ数
	unsigned long				countBone_;				// ボーン数
	unsigned long*				pCountPolygon_;			// ポリゴン数
	IDirect3DVertexBuffer9**	ppVertexBuffer_;		// 頂点バッファ
	int*						pIndexMaterial_;		// メッシュのマテリアル番号
	int*						pIndexTexture_;			// メッシュのテクスチャ番号
	D3DXMATRIX*					pMatrixBone_;			// ボーンの初期姿勢行列
};

#endif	// MY_MODEL_CONVERT_H
