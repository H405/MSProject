//==============================================================================
//
// File   : ObjectDrawTexture.cpp
// Brief  : デバッグテクスチャ描画オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/11/27 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectDrawTexture.h"
#include "../framework/camera/Camera.h"
#include "../framework/input/InputKeyboard.h"
#include "../graphic/graphic/GraphicDrawTexture.h"
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
ObjectDrawTexture::ObjectDrawTexture( void ) : Object()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectDrawTexture::~ObjectDrawTexture( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
// Arg    : InputKeyboard* pKeyboard			: キーボード入力
//==============================================================================
int ObjectDrawTexture::Initialize( int priority, InputKeyboard* pKeyboard )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の初期化
	pKeyboard_ = pKeyboard;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ObjectDrawTexture::Finalize( void )
{
	// テクスチャテーブルの開放
	delete[] ppTableTexture_;
	ppTableTexture_ = nullptr;

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
// Arg    : InputKeyboard* pKeyboard			: キーボード入力
//==============================================================================
int ObjectDrawTexture::Reinitialize( int priority, InputKeyboard* pKeyboard )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pKeyboard );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ObjectDrawTexture* pOut				: コピー先アドレス
//==============================================================================
int ObjectDrawTexture::Copy( ObjectDrawTexture* pOut ) const
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
void ObjectDrawTexture::Update( void )
{
	// テクスチャの切り替え
	if( pKeyboard_->IsTrigger( DIK_Z ) )
	{
		--indexTexture_;
		if( indexTexture_ < 0 )
		{
			indexTexture_ = countTexture_ - 1;
		}
	}
	else if( pKeyboard_->IsTrigger( DIK_X ) )
	{
		++indexTexture_;
		if( indexTexture_ >= countTexture_ )
		{
			indexTexture_ = 0;
		}
	}
	if( pKeyboard_->IsTrigger( DIK_LSHIFT ) )
	{
		isEnableDraw_ = !isEnableDraw_;
	}

	// テクスチャの設定
	pTextureCurrent_ = ppTableTexture_[ indexTexture_ ];

	// 描画クラスの有効設定
	bool	isEnableGraphic;		// 描画クラスの有効フラグ
	if( isEnableDraw_ && indexTexture_ != countTexture_ - 1 )
	{
		isEnableGraphic = true;
	}
	else
	{
		isEnableGraphic = false;
	}
	pGraphic_->SetIsEnable( isEnableGraphic );
#if 0
	// 色の倍率の設定
	D3DSURFACE_DESC	description;			// 情報
	const Camera*	pCamera = nullptr;		// カメラ
	if( pParameter_ != nullptr && pTextureCurrent_ != nullptr )
	{
		pTextureCurrent_->GetLevelDesc( 0, &description );
		pCamera = pParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
		if( description.Format == D3DFMT_R32F )
		{
			pMultiply_[ 0 ] = 1.0f / pCamera->GetClipFar();
		}
		else
		{
			pMultiply_[ 0 ] = 1.0f;
		}
	}
#endif
	// 基本クラスの処理
	Object::Update();
}

//==============================================================================
// Brief  : 描画クラスの生成
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : int countTexture					: テクスチャ数
// Arg    : IDirect3DTexture9** ppTexture		: テクスチャ
//==============================================================================
int ObjectDrawTexture::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, int countTexture, IDirect3DTexture9** ppTexture )
{
	// メンバ変数の設定
	countTexture_ = countTexture;
	indexTexture_ = countTexture - 1;
	pParameter_ = pParameter;

	// テクスチャテーブルの生成
	ppTableTexture_ = new IDirect3DTexture9*[ countTexture ];
	if( ppTableTexture_ == nullptr )
	{
		return 1;
	}
	for( int counterTexture = 0; counterTexture < countTexture; ++counterTexture )
	{
		ppTableTexture_[ counterTexture ] = ppTexture[ counterTexture ];
	}

	// グラフィックの生成
	int		result;				// 実行結果
	pGraphic_ = new GraphicDrawTexture();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, &pTextureCurrent_, pMultiply_ );
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

	// 値の返却
	return 0;
}

//==============================================================================
// Brief  : 描画クラスの設定
// Return : void								: なし
// Arg    : GraphicDrawTexture* pValue			: 設定する値
//==============================================================================
void ObjectDrawTexture::SetGraphic( GraphicDrawTexture* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicDrawTexture*					: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicDrawTexture* ObjectDrawTexture::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectDrawTexture::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
	pParameter_ = nullptr;
	countTexture_ = 0;
	indexTexture_ = 0;
	ppTableTexture_ = nullptr;
	pTextureCurrent_ = nullptr;
	pMultiply_[ 0 ] = 1.0f;
	pMultiply_[ 1 ] = 1.0f;
	pMultiply_[ 2 ] = 1.0f;
	pKeyboard_ = nullptr;
	isEnableDraw_ = false;
}
