//==============================================================================
//
// File   : ModelX.h
// Brief  : Xファイルモデルクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_MODEL_X_H
#define MY_MODEL_X_H

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

//******************************************************************************
// クラス定義
//******************************************************************************
class ModelX : public Model
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ModelX( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ModelX( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : unsigned int elementVertex			: 頂点の要素
	// Arg    : unsigned int countMaterial			: マテリアル数
	// Arg    : unsigned int countTexture			: テクスチャ数
	// Arg    : ID3DXMesh* pMesh					: メッシュ
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture, ID3DXMesh* pMesh );

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
	// Arg    : ID3DXMesh* pMesh					: メッシュ
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture, ID3DXMesh* pMesh );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ModelX* pOut						: コピー先アドレス
	//==============================================================================
	int Copy( ModelX* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : int indexMaterial					: 描画マテリアル番号
	//==============================================================================
	void Draw( int indexMaterial );

protected:
	ID3DXMesh*	pMesh_;		// メッシュ

private:
	void InitializeSelf( void );
	ModelX( const ModelX& );
	ModelX operator=( const ModelX& );
};

#endif	// MY_MODEL_X_H
