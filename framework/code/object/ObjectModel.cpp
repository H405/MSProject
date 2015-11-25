//==============================================================================
//
// File   : ObjectModel.cpp
// Brief  : モデルオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectModel.h"
#include "../framework/resource/Model.h"
#include "../graphic/graphic/GraphicModel.h"

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
ObjectModel::ObjectModel( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectModel::~ObjectModel( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int ObjectModel::Initialize( int priority )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( priority );
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
int ObjectModel::Finalize( void )
{
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
//==============================================================================
int ObjectModel::Reinitialize( int priority )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ObjectModel* pOut					: コピー先アドレス
//==============================================================================
int ObjectModel::Copy( ObjectModel* pOut ) const
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
void ObjectModel::Update( void )
{
	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : 描画クラスの生成
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : Model* pModel						: モデル
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
// Arg    : Effect* pEffectShadow				: 影描画エフェクト
//==============================================================================
int ObjectModel::CreateGraphic( int priority, Model* pModel, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow )
{
	// グラフィックの生成
	int		result;		// 実行結果
	pGraphic_ = new GraphicModel();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pModel, pParameter, pEffectGeneral, pEffectReflect, pEffectShadow );
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
// Arg    : GraphicModel* pValue				: 設定する値
//==============================================================================
void ObjectModel::SetGraphic( GraphicModel* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicModel*						: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicModel* ObjectModel::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectModel::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
}
