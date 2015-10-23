//==============================================================================
//
// File   : Object2D.h
// Brief  : 2Dポリゴンオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_2D_H
#define MY_OBJECT_2D_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../framework/object/ObjectMovement.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Effect;
class EffectParameter;
class Graphic2D;
class Texture;

//******************************************************************************
// クラス定義
//******************************************************************************
class Object2D : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Object2D( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~Object2D( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	//==============================================================================
	int Initialize( int priority );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	//==============================================================================
	int Reinitialize( int priority );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : Object2D* pOut						: コピー先アドレス
	//==============================================================================
	int Copy( Object2D* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : 描画クラスの生成
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : Texture* pTexture					: テクスチャ
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture = nullptr );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( Graphic2D* pValue );
	Graphic2D* GetGraphic( void ) const;
	void SetColor( const D3DXCOLOR& value );
	void SetColor( float r, float g, float b, float a );
	void SetColor( float r, float g, float b );
	void SetColorR( float r );
	void SetColorG( float g );
	void SetColorB( float b );
	void SetColorA( float a );
	void SetColorAlpha( float alpha );
	void GetColor( D3DXCOLOR* pOut ) const;
	float GetColorR( void ) const;
	float GetColorG( void ) const;
	float GetColorB( void ) const;
	float GetColorA( void ) const;
	void AddColor( const D3DXCOLOR& value );
	void AddColor( float r, float g, float b, float a );
	void AddColor( float r, float g, float b );
	void AddColorR( float r );
	void AddColorG( float g );
	void AddColorB( float b );
	void AddColorA( float a );
	void AddColorAlpha( float alpha );
	void SetPositionTexture( const D3DXVECTOR2& value );
	void SetPositionTexture( float x, float y );
	void SetPositionTextureX( float x );
	void SetPositionTextureY( float y );
	void GetPositionTexture( D3DXVECTOR2* pOut ) const;
	float GetPositionTextureX( void ) const;
	float GetPositionTextureY( void ) const;
	void AddPositionTexture( const D3DXVECTOR2& value );
	void AddPositionTexture( float x, float y );
	void AddPositionTextureX( float x );
	void AddPositionTextureY( float y );
	void SetScaleTexture( const D3DXVECTOR2& value );
	void SetScaleTexture( float x, float y );
	void SetScaleTextureX( float x );
	void SetScaleTextureY( float y );
	void GetScaleTexture( D3DXVECTOR2* pOut ) const;
	float GetScaleTextureX( void ) const;
	float GetScaleTextureY( void ) const;
	void AddScaleTexture( const D3DXVECTOR2& value );
	void AddScaleTexture( float x, float y );
	void AddScaleTextureX( float x );
	void AddScaleTextureY( float y );

protected:
	Graphic2D*	pGraphic_;				// 描画クラス
	D3DXCOLOR	color_;					// 色
	D3DXVECTOR2	positionTexture_;		// テクスチャ座標
	D3DXVECTOR2	scaleTexture_;			// テクスチャ拡縮

private:
	void InitializeSelf( void );
	Object2D( const Object2D& );
	Object2D operator=( const Object2D& );
};

#endif	// MY_OBJECT_2D_H
