//==============================================================================
//
// File   : ObjectSky.cpp
// Brief  : 空オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectSky.h"
#include "../framework/polygon/PolygonMeshDomeInside.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/GraphicSky.h"

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
ObjectSky::ObjectSky( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectSky::~ObjectSky( void )
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
// Arg    : int countCellY						: Z方向セル数
// Arg    : float radius						: 半径
// Arg    : float lengthTextureX				: X方向テクスチャ長さ
// Arg    : float lengthTextureY				: Z方向テクスチャ長さ
//==============================================================================
int ObjectSky::Initialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellY, float radius, float lengthTextureX, float lengthTextureY )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 内部メッシュドームポリゴンの生成
	pPolygonMesh_ = new PolygonMeshDomeInside();
	if( pPolygonMesh_ == nullptr )
	{
		return 1;
	}
	result = pPolygonMesh_->Initialize( pDevice, countCellX, countCellY, radius, lengthTextureX, lengthTextureY );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ObjectSky::Finalize( void )
{
	// 内部メッシュドームポリゴンの開放
	delete pPolygonMesh_;
	pPolygonMesh_ = nullptr;

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
// Arg    : int countCellY						: Z方向セル数
// Arg    : float radius						: 半径
// Arg    : float lengthTextureX				: X方向テクスチャ長さ
// Arg    : float lengthTextureY				: Z方向テクスチャ長さ
//==============================================================================
int ObjectSky::Reinitialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellY, float radius, float lengthTextureX, float lengthTextureY )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pDevice, countCellX, countCellY, radius, lengthTextureX, lengthTextureY );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ObjectSky* pOut						: コピー先アドレス
//==============================================================================
int ObjectSky::Copy( ObjectSky* pOut ) const
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
void ObjectSky::Update( void )
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
int ObjectSky::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture )
{
	// グラフィックの生成
	int					result;				// 実行結果
	IDirect3DTexture9*	pTextureSet;		// 設定するテクスチャ
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}
	pGraphic_ = new GraphicSky();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, pPolygonMesh_, pTextureSet );
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
// Arg    : GraphicSky* pValue					: 設定する値
//==============================================================================
void ObjectSky::SetGraphic( GraphicSky* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicSky*							: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicSky* ObjectSky::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectSky::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
	pPolygonMesh_ = nullptr;
}
