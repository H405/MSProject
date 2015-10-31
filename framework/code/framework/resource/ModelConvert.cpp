//==============================================================================
//
// File   : ModelConvert.cpp
// Brief  : 変換済みモデル
// Author : Taiga Shirakawa
// Date   : 2015/10/29 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ModelConvert.h"
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
ModelConvert::ModelConvert( void ) : Model()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ModelConvert::~ModelConvert( void )
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
int ModelConvert::Initialize( IDirect3DDevice9* pDevice, unsigned int elementVertex,
	unsigned int countMaterial, unsigned int countTexture, unsigned long countMesh, unsigned long countBone,
	void** ppVertexBuffer, const int* pCountVertex, Material* pMaterial, const int* pIndexMaterial,
	IDirect3DTexture9** ppTexture, const int* pIndexTexture, const D3DXMATRIX* pMatrixBone )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Model::Initialize( pDevice, elementVertex, countMaterial, countTexture );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	countMesh_ = countMesh;
	countBone_ = countBone;

	pCountPolygon_ = new unsigned long[ countMesh ];
	if( pCountPolygon_ == nullptr )
	{
		return 1;
	}
	for( unsigned int counterItem = 0; counterItem < countMesh; ++counterItem )
	{
		pCountPolygon_[ counterItem ] = pCountVertex[ counterItem ] / 3;
	}

	ppVertexBuffer_ = new IDirect3DVertexBuffer9*[ countMesh ];
	for( unsigned int counterItem = 0; counterItem < countMesh; ++counterItem )
	{
		ppVertexBuffer_[ counterItem ] = nullptr;
	}

	for( unsigned int counterItem = 0; counterItem < countMaterial; ++counterItem )
	{
		pMaterial_[ counterItem ] = pMaterial[ counterItem ];
	}

	pIndexMaterial_ = new int[ countMesh ];
	for( unsigned int counterItem = 0; counterItem < countMesh; ++counterItem )
	{
		pIndexMaterial_[ counterItem ] = pIndexMaterial[ counterItem ];
	}

	for( unsigned int counterItem = 0; counterItem < countTexture; ++counterItem )
	{
		ppTexture_[ counterItem ] = ppTexture[ counterItem ];
	}

	pIndexTexture_ = new int[ countMesh ];
	for( unsigned int counterItem = 0; counterItem < countMesh; ++counterItem )
	{
		pIndexTexture_[ counterItem ] = pIndexTexture[ counterItem ];
	}

	pMatrixBone_ = new D3DXMATRIX[ countBone ];
	for( unsigned int counterItem = 0; counterItem < countBone; ++counterItem )
	{
		pMatrixBone_[ counterItem ] = pMatrixBone[ counterItem ];
	}

	// 頂点バッファの生成
	for( unsigned int counterItem = 0; counterItem < countMesh; ++counterItem )
	{
		// 頂点バッファの生成
		int		sizeVertex;		// 頂点のサイズ
		sizeVertex = pVertex_->GetSize();
		result = pDevice->CreateVertexBuffer( sizeVertex * pCountVertex[ counterItem ], D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &ppVertexBuffer_[ counterItem ], nullptr );
		if( result != 0 )
		{
			return result;
		}

		// 頂点バッファに値を設定
		void*	pBufferAddress = nullptr;		// バッファのアドレス
		ppVertexBuffer_[ counterItem ]->Lock( 0, 0, &pBufferAddress, 0 );
		memcpy_s( pBufferAddress, sizeVertex * pCountVertex[ counterItem ], ppVertexBuffer[ counterItem ], sizeVertex * pCountVertex[ counterItem ] );
		ppVertexBuffer_[ counterItem ]->Unlock();
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ModelConvert::Finalize( void )
{
	// 頂点バッファの開放
	for( unsigned int counterItem = 0; counterItem < countMesh_; ++counterItem )
	{
		if( ppVertexBuffer_[ counterItem ] != nullptr )
		{
			ppVertexBuffer_[ counterItem ]->Release();
			ppVertexBuffer_[ counterItem ] = nullptr;
		}
	}
	delete[] ppVertexBuffer_;
	ppVertexBuffer_ = nullptr;

	// ポリゴン数格納領域の開放
	delete[] pCountPolygon_;
	pCountPolygon_ = nullptr;

	// 格納領域の開放
	delete[] pIndexMaterial_;
	pIndexMaterial_ = nullptr;

	delete[] pIndexTexture_;
	pIndexTexture_ = nullptr;

	delete[] pMatrixBone_;
	pMatrixBone_ = nullptr;

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
int ModelConvert::Reinitialize( IDirect3DDevice9* pDevice, unsigned int elementVertex,
	unsigned int countMaterial, unsigned int countTexture, unsigned long countMesh, unsigned long countBone,
	void** ppVertexBuffer, const int* pCountVertex, Material* pMaterial, const int* pIndexMaterial,
	IDirect3DTexture9** ppTexture, const int* pIndexTexture, const D3DXMATRIX* pMatrixBone )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice, elementVertex, countMaterial, countTexture, countMesh, countBone, ppVertexBuffer, pCountVertex,
		pMaterial, pIndexMaterial, ppTexture, pIndexTexture, pMatrixBone );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ModelConvert* pOut					: コピー先アドレス
//==============================================================================
int ModelConvert::Copy( ModelConvert* pOut ) const
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
void ModelConvert::Draw( int indexMaterial )
{
	// 描画
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pDevice_->SetStreamSource( 0, ppVertexBuffer_[ indexMaterial ], 0, pVertex_->GetSize() );
	pDevice_->DrawPrimitive( D3DPT_TRIANGLELIST, 0, pCountPolygon_[ indexMaterial ] );
}

//==============================================================================
// Brief  : マテリアルの取得
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : Material* pOut						: 値の格納アドレス
//==============================================================================
void ModelConvert::GetMaterial( int index, Material* pOut ) const
{
	// 値の返却
	*pOut = pMaterial_[ pIndexMaterial_[ index ] ];
}

//==============================================================================
// Brief  : テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : int index							: 設定する番号
//==============================================================================
IDirect3DTexture9* ModelConvert::GetTexture( int index ) const
{
	// 値の返却
	if( static_cast< unsigned int >( index ) >= countTexture_ )
	{
		return nullptr;
	}
	return ppTexture_[ pIndexTexture_[ index ] ];
}

//==============================================================================
// Brief  : メッシュ数の設定
// Return : void								: なし
// Arg    : unsigned long value					: 設定する値
//==============================================================================
void ModelConvert::SetCountMesh( unsigned long value )
{
	// 値の設定
	countMesh_ = value;
}

//==============================================================================
// Brief  : メッシュ数の取得
// Return : unsigned long						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned long ModelConvert::GetCountMesh( void ) const
{
	// 値の返却
	return countMesh_;
}

//==============================================================================
// Brief  : ボーン数の設定
// Return : void								: なし
// Arg    : unsigned long value					: 設定する値
//==============================================================================
void ModelConvert::SetCountBone( unsigned long value )
{
	// 値の設定
	countBone_ = value;
}

//==============================================================================
// Brief  : ボーン数の取得
// Return : unsigned long						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned long ModelConvert::GetCountBone( void ) const
{
	// 値の返却
	return countBone_;
}

//==============================================================================
// Brief  : メッシュのマテリアル番号の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const int& value					: 設定する値
//==============================================================================
void ModelConvert::SetIndexMaterial( int index, const int& value )
{
	// 値の設定
	pIndexMaterial_[ index ] = value;
}

//==============================================================================
// Brief  : メッシュのマテリアル番号の取得
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : int* pOut							: 値の格納アドレス
//==============================================================================
void ModelConvert::GetIndexMaterial( int index, int* pOut ) const
{
	// 値の返却
	*pOut = pIndexMaterial_[ index ];
}

//==============================================================================
// Brief  : メッシュのテクスチャ番号の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const int& value					: 設定する値
//==============================================================================
void ModelConvert::SetIndexTexture( int index, const int& value )
{
	// 値の設定
	pIndexTexture_[ index ] = value;
}

//==============================================================================
// Brief  : メッシュのテクスチャ番号の取得
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : int* pOut							: 値の格納アドレス
//==============================================================================
void ModelConvert::GetIndexTexture( int index, int* pOut ) const
{
	// 値の返却
	*pOut = pIndexTexture_[ index ];
}

//==============================================================================
// Brief  : ボーンの初期姿勢行列の設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXMATRIX& value				: 設定する値
//==============================================================================
void ModelConvert::SetMatrixBone( int index, const D3DXMATRIX& value )
{
	// 値の設定
	pMatrixBone_[ index ] = value;
}

//==============================================================================
// Brief  : ボーンの初期姿勢行列の取得
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : D3DXMATRIX* pOut					: 値の格納アドレス
//==============================================================================
void ModelConvert::GetMatrixBone( int index, D3DXMATRIX* pOut ) const
{
	// 値の返却
	*pOut = pMatrixBone_[ index ];
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ModelConvert::InitializeSelf( void )
{
	// メンバ変数の初期化
	countMesh_ = 0;
	countBone_ = 0;
	pCountPolygon_ = nullptr;
	ppVertexBuffer_ = nullptr;
	pIndexMaterial_ = nullptr;
	pIndexTexture_ = nullptr;
	pMatrixBone_ = nullptr;
}
