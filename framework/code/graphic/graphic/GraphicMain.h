//==============================================================================
//
// File   : GraphicMain.h
// Brief  : 描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_MAIN_H
#define MY_GRAPHIC_MAIN_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../../framework/graphic/graphic.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Polygon2D;
class Polygon3D;

//******************************************************************************
// クラス定義
//******************************************************************************
class GraphicMain : public Graphic
{
public:
	// パス
	enum
	{
		PASS_3D = 0,			// 3D描画
		PASS_3D_NOT_LIGHT,		// ライティングなし3D描画
		PASS_LIGHT_EFFECT,		// ライティング
		PASS_3D_MERGE,			// 総合3D描画
		PASS_BLUR_X,			// X方向ブラー
		PASS_BLUR_Y,			// Y方向ブラー
		PASS_2D,				// 2D描画
		PASS_POST_EFFECT,		// ポストエフェクト
		PASS_MAX				// 最大数
	};

	// 3D描画
	enum
	{
		RENDER_PASS_3D_DIFFUSE = 0,				// ディフューズ色
		RENDER_PASS_3D_SPECULAR,				// スペキュラ色
		RENDER_PASS_3D_NORMAL,					// 法線
		RENDER_PASS_3D_DEPTH,					// 深度
		RENDER_PASS_3D_MAX						// 最大値
	};

	// ライティングなし3D描画
	enum
	{
		RENDER_PASS_3D_NOT_LIGHT_COLOR = 0,		// 色
		RENDER_PASS_3D_NOT_LIGHT_MASK,			// マスク
		RENDER_PASS_3D_NOT_LIGHT_ADD,			// 加算合成
		RENDER_PASS_3D_NOT_LIGHT_MAX			// 最大値
	};

	// ライティング
	enum
	{
		RENDER_PASS_LIGHT_EFFECT_COLOR = 0,		// 色
		RENDER_PASS_LIGHT_EFFECT_MAX			// 最大値
	};

	// 総合3D描画
	enum
	{
		RENDER_PASS_3D_MERGE_COLOR = 0,			// 色
		RENDER_PASS_3D_MERGE_MAX				// 最大値
	};

	// X方向ブラー
	enum
	{
		RENDER_PASS_BLUR_X_COLOR = 0,			// 色
		RENDER_PASS_BLUR_X_MAX					// 最大値
	};

	// Y方向ブラー
	enum
	{
		RENDER_PASS_BLUR_Y_COLOR = 0,			// 色
		RENDER_PASS_BLUR_Y_LUMINANCE,			// 輝度
		RENDER_PASS_BLUR_Y_MAX					// 最大値
	};

	// 2D描画
	enum
	{
		RENDER_PASS_2D_COLOR = 0,				// 色
		RENDER_PASS_2D_MASK,					// マスク
		RENDER_PASS_2D_MAX						// 最大値
	};

	// 画面描画
	enum
	{
		RENDER_PASS_POST_EFFECT_COLOR = 0,		// 色
		RENDER_PASS_POST_EFFECT_MAX				// 最大値
	};

	// ディレクショナルライト
	enum
	{
		LIGHT_DIRECTIONAL_GENERAL = 0,		// 通常ライト
		LIGHT_DIRECTIONAL_MAX				// 最大値
	};

	// ポイントライト
	enum
	{
		LIGHT_POINT_MAX = 10		// 最大値
	};

	// カメラ
	enum
	{
		CAMERA_GENERAL = 0,		// 通常カメラ
		CAMERA_MAX				// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	GraphicMain( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~GraphicMain( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
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
	// Arg    : int priority						: 描画優先度
	//==============================================================================
	int Reinitialize( int priority );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicMain* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( GraphicMain* pOut ) const;
	
	//==============================================================================
	// Brief  : 2Dポリゴンクラスの設定
	// Return : void								: なし
	// Arg    : Polygon2D* pValue					: 設定する値
	//==============================================================================
	static void SetPolygon2D( Polygon2D* pValue );

	//==============================================================================
	// Brief  : 3Dポリゴンクラスの設定
	// Return : void								: なし
	// Arg    : Polygon3D* pValue					: 設定する値
	//==============================================================================
	static void SetPolygon3D( Polygon3D* pValue );

protected:
	static Polygon2D*	pPolygon2D_;		// 2Dポリゴン
	static Polygon3D*	pPolygon3D_;		// 3Dポリゴン

private:
	void InitializeSelf( void );
	GraphicMain( const GraphicMain& );
	GraphicMain operator=( const GraphicMain& );
};

#endif	// MY_GRAPHIC_MAIN_H
