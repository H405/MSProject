//==============================================================================
//
// File   : ObjectBillboard.h
// Brief  : ビルボードポリゴンオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/23 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_BILLBOARD_H
#define MY_OBJECT_BILLBOARD_H

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
class Texture;
class EffectParameter;
class Effect;
class GraphicBillboard;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectBillboard : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectBillboard( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectBillboard( void );

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
	// Arg    : ObjectBillboard* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( ObjectBillboard* pOut ) const;

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
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicBillboard* pValue );
	GraphicBillboard* GetGraphic( void ) const;
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
	GraphicBillboard*	pGraphic_;				// 描画クラス
	D3DXCOLOR			color_;					// 色
	D3DXVECTOR2			positionTexture_;		// テクスチャ座標
	D3DXVECTOR2			scaleTexture_;			// テクスチャ拡縮

private:
	void InitializeSelf( void );
	ObjectBillboard( const ObjectBillboard& );
	ObjectBillboard operator=( const ObjectBillboard& );

};

#endif	// MY_OBJECT_BILLBOARD_H
