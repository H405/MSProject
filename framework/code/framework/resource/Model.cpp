//==============================================================================
//
// File   : Model.cpp
// Brief  : モデルクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Model.h"
#include "../graphic/Material.h"
#include "../vertex/Vertex.h"

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
Model::Model( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Model::~Model( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : unsigned int elementVertex			: 頂点の要素
// Arg    : unsigned int countMaterial			: マテリアル数
// Arg    : unsigned int countTexture			: テクスチャ数
//==============================================================================
int Model::Initialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture )
{
	// メンバ変数の設定
	pDevice_ = pDevice;
	countMaterial_ = countMaterial;
	countTexture_ = countTexture;

	// 格納領域の確保
	pMaterial_ = new Material[ countMaterial ];
	if( pMaterial_ == nullptr )
	{
		return 1;
	}

	ppTexture_ = new IDirect3DTexture9*[ countTexture ];
	if( ppTexture_ == nullptr )
	{
		return 1;
	}
	for( unsigned int counterItem = 0; counterItem < countTexture; ++counterItem )
	{
		ppTexture_[ counterItem ] = nullptr;
	}

	// 頂点情報の生成
	int		result;		// 実行結果
	pVertex_ = new Vertex();
	if( pVertex_ == nullptr )
	{
		return 1;
	}
	result = pVertex_->Initialize( pDevice, elementVertex );
	if( result != 0 )
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
int Model::Finalize( void )
{
	// 頂点情報の破棄
	delete pVertex_;
	pVertex_ = nullptr;

	// 格納領域の開放
	delete[] pMaterial_;
	pMaterial_ = nullptr;
	delete[] ppTexture_;
	ppTexture_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : unsigned int elementVertex			: 頂点の要素
// Arg    : unsigned int countMaterial			: マテリアル数
// Arg    : unsigned int countTexture			: テクスチャ数
//==============================================================================
int Model::Reinitialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice, elementVertex, countMaterial, countTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Model* pOut							: コピー先アドレス
//==============================================================================
int Model::Copy( Model* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画処理
// Return : void								: なし
// Arg    : int indexMaterial					: 描画マテリアル番号
//==============================================================================
void Model::Draw( int indexMaterial )
{
}

//==============================================================================
// Brief  : マテリアル数の設定
// Return : void								: なし
// Arg    : unsigned int value					: 設定する値
//==============================================================================
void Model::SetCountMaterial( unsigned int value )
{
	// 値の設定
	countMaterial_ = value;
}

//==============================================================================
// Brief  : マテリアル数の取得
// Return : unsigned int						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned int Model::GetCountMaterial( void ) const
{
	// 値の返却
	return countMaterial_;
}

//==============================================================================
// Brief  : マテリアルの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const Material& value				: 設定する値
//==============================================================================
void Model::SetMaterial( int index, const Material& value )
{
	// 値の設定
	pMaterial_[ index ] = value;
}

//==============================================================================
// Brief  : マテリアルの取得
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : Material* pOut						: 値の格納アドレス
//==============================================================================
void Model::GetMaterial( int index, Material* pOut ) const
{
	// 値の返却
	*pOut = pMaterial_[ index ];
}

//==============================================================================
// Brief  : テクスチャ数の設定
// Return : void								: なし
// Arg    : unsigned int value					: 設定する値
//==============================================================================
void Model::SetCountTexture( unsigned int value )
{
	// 値の設定
	countTexture_ = value;
}

//==============================================================================
// Brief  : テクスチャ数の取得
// Return : unsigned int						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned int Model::GetCountTexture( void ) const
{
	// 値の返却
	return countTexture_;
}

//==============================================================================
// Brief  : テクスチャの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : IDirect3DTexture9* pValue			: 設定する値
//==============================================================================
void Model::SetTexture( int index, IDirect3DTexture9* pValue )
{
	// 値の設定
	ppTexture_[ index ] = pValue;
}

//==============================================================================
// Brief  : テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : int index							: 設定する番号
//==============================================================================
IDirect3DTexture9* Model::GetTexture( int index ) const
{
	// 値の返却
	return ppTexture_[ index ];
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Model::InitializeSelf( void )
{
	// メンバ変数の初期化
	pDevice_ = nullptr;
	pVertex_ = nullptr;
	countMaterial_ = 0;
	pMaterial_ = nullptr;
	countTexture_ = 0;
	ppTexture_ = nullptr;
}
