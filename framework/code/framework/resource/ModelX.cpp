//==============================================================================
//
// File   : ModelX.cpp
// Brief  : Xファイルモデルクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ModelX.h"
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
ModelX::ModelX( void ) : Model()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ModelX::~ModelX( void )
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
// Arg    : ID3DXMesh* pMesh					: メッシュ
//==============================================================================
int ModelX::Initialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture, ID3DXMesh* pMesh )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Model::Initialize( pDevice, elementVertex, countMaterial, countTexture );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	pMesh_ = pMesh;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ModelX::Finalize( void )
{
	// メッシュの開放
	if( pMesh_ != nullptr )
	{
		pMesh_->Release();
		pMesh_ = nullptr;
	}

	// 基本クラスの処理
	int		result;		// 実行結果
	result = Model::Finalize();
	if( result != 0 )
	{
		return result;
	}

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
// Arg    : ID3DXMesh* pMesh					: メッシュ
//==============================================================================
int ModelX::Reinitialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture, ID3DXMesh* pMesh )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice, elementVertex, countMaterial, countTexture, pMesh );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ModelX* pOut						: コピー先アドレス
//==============================================================================
int ModelX::Copy( ModelX* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Model::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画処理
// Return : void								: なし
// Arg    : int indexMaterial					: 描画マテリアル番号
//==============================================================================
void ModelX::Draw( int indexMaterial )
{
	// 描画
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pMesh_->DrawSubset( indexMaterial );
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ModelX::InitializeSelf( void )
{
	// メンバ変数の初期化
	pMesh_ = nullptr;
}
