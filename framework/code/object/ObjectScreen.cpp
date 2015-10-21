//==============================================================================
//
// File   : ObjectScreen.cpp
// Brief  : 画面ポリゴンオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectScreen.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../graphic/graphic/GraphicScreen.h"
#include "../system/EffectParameter.h"

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
ObjectScreen::ObjectScreen( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectScreen::~ObjectScreen( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
// Arg    : Fade* pFade							: フェード
//==============================================================================
int ObjectScreen::Initialize( int priority, Fade* pFade )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	pFade_ = pFade;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ObjectScreen::Finalize( void )
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
// Arg    : Fade* pFade							: フェード
//==============================================================================
int ObjectScreen::Reinitialize( int priority, Fade* pFade )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pFade );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ObjectScreen* pOut						: コピー先アドレス
//==============================================================================
int ObjectScreen::Copy( ObjectScreen* pOut ) const
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
void ObjectScreen::Update( void )
{
	// フェードの更新
	proportionFade_ = pFade_->GetProportion();

	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : 描画クラスの生成
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTextureGeneral	: 通常描画テクスチャ
// Arg    : Texture* pTexture					: テクスチャ
//==============================================================================
int ObjectScreen::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTextureGeneral, Texture* pTexture )
{
	// グラフィックの生成
	int					result;				// 実行結果
	IDirect3DTexture9*	pTextureSet;		// 設定するテクスチャ
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}
	pGraphic_ = new GraphicScreen();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, &proportionFade_, pTextureGeneral, pTextureSet );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// 拡縮の設定
	if( pParameter != nullptr )
	{
		scale_.x = pParameter->GetWidthScreen();
		scale_.y = pParameter->GetHeightScreen();
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画クラスの設定
// Return : void								: なし
// Arg    : GraphicScreen* pValue						: 設定する値
//==============================================================================
void ObjectScreen::SetGraphic( GraphicScreen* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicScreen*							: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicScreen* ObjectScreen::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectScreen::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
	pFade_ = nullptr;
	proportionFade_ = 0.0f;
}
