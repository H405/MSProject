//==============================================================================
//
// File   : ObjectMesh.cpp
// Brief  : メッシュポリゴンオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectMesh.h"
#include "../framework/polygon/PolygonMesh.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/GraphicMesh.h"

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
ObjectMesh::ObjectMesh( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectMesh::~ObjectMesh( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : int countCellX						: X方向セル数
// Arg    : int countCellZ						: Z方向セル数
// Arg    : float lengthCellX					: X方向セル長さ
// Arg    : float lengthCellZ					: Z方向セル長さ
// Arg    : float lengthTextureX				: X方向テクスチャ長さ
// Arg    : float lengthTextureZ				: Z方向テクスチャ長さ
//==============================================================================
int ObjectMesh::Initialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
	float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// メッシュポリゴンの生成
	pPolygon_ = new PolygonMesh();
	if( pPolygon_ == nullptr )
	{
		return 1;
	}
	result = pPolygon_->Initialize( pDevice, countCellX, countCellZ, lengthCellX, lengthCellZ, lengthTextureX, lengthTextureZ );
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
int ObjectMesh::Finalize( void )
{
	// メッシュポリゴンの開放
	delete pPolygon_;
	pPolygon_ = nullptr;

	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Finalize();
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
// Arg    : int priority						: 更新優先度
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : int countCellX						: X方向セル数
// Arg    : int countCellZ						: Z方向セル数
// Arg    : float lengthCellX					: X方向セル長さ
// Arg    : float lengthCellZ					: Z方向セル長さ
// Arg    : float lengthTextureX				: X方向テクスチャ長さ
// Arg    : float lengthTextureZ				: Z方向テクスチャ長さ
//==============================================================================
int ObjectMesh::Reinitialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
	float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pDevice, countCellX, countCellZ, lengthCellX, lengthCellZ, lengthTextureX, lengthTextureZ );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ObjectMesh* pOut					: コピー先アドレス
//==============================================================================
int ObjectMesh::Copy( ObjectMesh* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectMesh::Update( void )
{
	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : 描画クラスの生成
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : Texture* pTexture					: テクスチャ
//==============================================================================
int ObjectMesh::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture )
{
	// グラフィックの生成
	int					result;				// 実行結果
	IDirect3DTexture9*	pTextureSet;		// 設定するテクスチャ
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}
	pGraphic_ = new GraphicMesh();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, pPolygon_, &material_, pTextureSet );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画クラスの設定
// Return : void								: なし
// Arg    : GraphicMesh* pValue					: 設定する値
//==============================================================================
void ObjectMesh::SetGraphic( GraphicMesh* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicMesh*						: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicMesh* ObjectMesh::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectMesh::InitializeSelf( void )
{
	// メンバ変数の初期化
	pPolygon_ = nullptr;
}
