//==============================================================================
//
// File   : EffectParameter.h
// Brief  : エフェクトファイル用のパラメータクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_EFFECT_PARAMETER_H
#define MY_EFFECT_PARAMETER_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Camera;
class LightDirection;
class LightPoint;

//******************************************************************************
// クラス定義
//******************************************************************************
class EffectParameter
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	EffectParameter( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~EffectParameter( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int maximumLightDirection			: ディレクショナルライト最大数
	// Arg    : int maximumLightPoint				: ポイントライト最大数
	// Arg    : int maximumCamera					: カメラ最大数
	//==============================================================================
	int Initialize( int maximumLightDirection, int maximumLightPoint, int maximumCamera );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : int maximumLightDirection			: ディレクショナルライト最大数
	// Arg    : int maximumLightPoint				: ポイントライト最大数
	// Arg    : int maximumCamera					: カメラ最大数
	//==============================================================================
	int Reinitialize( int maximumLightDirection, int maximumLightPoint, int maximumCamera );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : EffectParameter* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( EffectParameter* pOut ) const;

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetCountLightDirection( int value );
	int GetCountLightDirection( void ) const;
	void SetLightDirection( int index, const LightDirection* pValue );
	const LightDirection* GetLightDirection( int index ) const;
	void SetCountLightPoint( int value );
	int GetCountLightPoint( void ) const;
	void SetLightPoint( int index, const LightPoint* pValue );
	const LightPoint* GetLightPoint( int index ) const;
	void SetCountCamera( int value );
	int GetCountCamera( void ) const;
	void SetCamera( int index, const Camera* pValue );
	const Camera* GetCamera( int index ) const;
	void SetColorAmbient( const D3DXCOLOR& value );
	void SetColorAmbient( float r, float g, float b, float a );
	void SetColorAmbient( float r, float g, float b );
	void SetColorAmbientR( float r );
	void SetColorAmbientG( float g );
	void SetColorAmbientB( float b );
	void SetColorAmbientA( float a );
	void SetColorAmbientAlpha( float alpha );
	void GetColorAmbient( D3DXCOLOR* pOut ) const;
	float GetColorAmbientR( void ) const;
	float GetColorAmbientG( void ) const;
	float GetColorAmbientB( void ) const;
	float GetColorAmbientA( void ) const;
	void SetWidthScreen( float value );
	float GetWidthScreen( void ) const;
	void SetHeightScreen( float value );
	float GetHeightScreen( void ) const;
	void SetForcus( float value );
	float GetForcus( void ) const;
	void SetHeightReflect( float value );
	float GetHeightReflect( void ) const;

protected:

private:
	void InitializeSelf( void );
	EffectParameter( const EffectParameter& );
	EffectParameter operator=( const EffectParameter& );

	int						maximumLightDirection_;		// ディレクショナルライト最大数
	int						countLightDirection_;		// ディレクショナルライト数
	const LightDirection**	ppLightDirection_;			// ディレクショナルライト
	int						maximumLightPoint_;			// ポイントライト最大数
	int						countLightPoint_;			// ポイントライト数
	const LightPoint**		ppLightPoint_;				// ポイントライト
	int						maximumCamera_;				// カメラ最大数
	int						countCamera_;				// カメラ数
	const Camera**			ppCamera_;					// カメラ
	D3DXCOLOR				colorAmbient_;				// 環境光
	float					widthScreen_;				// 画面幅
	float					heightScreen_;				// 画面高さ
	float					forcus_;					// 焦点距離
	float					heightReflect_;				// 反射面の高さ
};

#endif	// MY_EFFECT_PARAMETER_H
