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
class PolygonBillboard;

//******************************************************************************
// クラス定義
//******************************************************************************
class GraphicMain : public Graphic
{
public:
	// パス
	enum
	{
		PASS_WAVE_DATA = 0,				// 波情報
		PASS_3D,						// 3D描画
		PASS_DEPTH_SHADOW_NEAR,			// 影用深度(近)
		PASS_DEPTH_SHADOW_FAR,			// 影用深度(遠)
		PASS_DEPTH_SHADOW_POINT_0,		// 影用深度(点0)
		PASS_DEPTH_SHADOW_POINT_1,		// 影用深度(点1)
		PASS_SHADOW,					// 影
		PASS_BLUR_SHADOW,				// 影用ブラー
		PASS_REFLECT,					// 反射
		PASS_LIGHT_REFLECT,				// 反射のライティング
		PASS_REFLECT_NOT_LIGHT,			// 反射ライティングなし
		PASS_WATER,						// 水
		PASS_3D_NOT_LIGHT,				// ライティングなし3D描画
		PASS_LIGHT_EFFECT,				// ライティング
		PASS_3D_MERGE,					// 総合3D描画
		PASS_BLUR_X,					// X方向ブラー
		PASS_BLUR_Y,					// Y方向ブラー
		PASS_2D,						// 2D描画
		PASS_POST_EFFECT,				// ポストエフェクト
		PASS_MAX						// 最大数
	};

	// 波
	enum
	{
		RENDER_PASS_WAVE_DATA_HEIGHT = 0,				// 高さ
		RENDER_PASS_WAVE_DATA_NORMAL,					// 法線
		RENDER_PASS_WAVE_DATA_MAX						// 最大値
	};

	// 3D描画
	enum
	{
		RENDER_PASS_3D_DIFFUSE = 0,						// ディフューズ色
		RENDER_PASS_3D_SPECULAR,						// スペキュラ色
		RENDER_PASS_3D_NORMAL,							// 法線
		RENDER_PASS_3D_DEPTH,							// 深度
		RENDER_PASS_3D_MAX								// 最大値
	};

	// 影用深度(近)
	enum
	{
		RENDER_PASS_DEPTH_SHADOW_NEAR_DEPTH = 0,		// 深度
		RENDER_PASS_DEPTH_SHADOW_NEAR_MAX				// 最大値
	};

	// 影用深度(遠)
	enum
	{
		RENDER_PASS_DEPTH_SHADOW_FAR_DEPTH = 0,			// 深度
		RENDER_PASS_DEPTH_SHADOW_FAR_MAX				// 最大値
	};

	// 影用深度(点0)
	enum
	{
		RENDER_PASS_DEPTH_SHADOW_POINT_0_DEPTH = 0,		// 深度
		RENDER_PASS_DEPTH_SHADOW_POINT_0_MAX			// 最大値
	};

	// 影用深度(点1)
	enum
	{
		RENDER_PASS_DEPTH_SHADOW_POINT_1_DEPTH = 0,		// 深度
		RENDER_PASS_DEPTH_SHADOW_POINT_1_MAX			// 最大値
	};

	// 影
	enum
	{
		RENDER_PASS_SHADOW_COLOR = 0,					// 色
		RENDER_PASS_SHADOW_MAX							// 最大値
	};

	// 影用ブラー
	enum
	{
		RENDER_PASS_BLUR_SHADOW_COLOR = 0,				// 色
		RENDER_PASS_BLUR_SHADOW_MAX						// 最大値
	};

	// 反射
	enum
	{
		RENDER_PASS_REFLECT_DIFFUSE = 0,				// ディフューズ色
		RENDER_PASS_REFLECT_SPECULAR,					// スペキュラ色
		RENDER_PASS_REFLECT_NORMAL,						// 法線
		RENDER_PASS_REFLECT_DEPTH,						// 深度
		RENDER_PASS_REFLECT_MAX							// 最大値
	};

	// 反射のライティング
	enum
	{
		RENDER_PASS_LIGHT_REFLECT_COLOR = 0,			// 色
		RENDER_PASS_LIGHT_REFLECT_MAX					// 最大値
	};

	// 反射ライティングなし
	enum
	{
		RENDER_PASS_REFLECT_NOT_LIGHT_COLOR = 0,		// 色
		RENDER_PASS_REFLECT_NOT_LIGHT_ADD,				// 加算合成
		RENDER_PASS_REFLECT_NOT_LIGHT_MAX				// 最大値
	};

	// 水
	enum
	{
		RENDER_PASS_WATER_DIFFUSE = 0,					// ディフューズ色
		RENDER_PASS_WATER_SPECULAR,						// スペキュラ色
		RENDER_PASS_WATER_NORMAL,						// 法線
		RENDER_PASS_WATER_DEPTH,						// 深度
		RENDER_PASS_WATER_MAX							// 最大値
	};

	// ライティングなし3D描画
	enum
	{
		RENDER_PASS_3D_NOT_LIGHT_COLOR = 0,				// 色
		RENDER_PASS_3D_NOT_LIGHT_MASK,					// マスク
		RENDER_PASS_3D_NOT_LIGHT_ADD,					// 加算合成
		RENDER_PASS_3D_NOT_LIGHT_MAX					// 最大値
	};

	// ライティング
	enum
	{
		RENDER_PASS_LIGHT_EFFECT_COLOR = 0,				// 色
		RENDER_PASS_LIGHT_EFFECT_DEPTH,					// 深度
		RENDER_PASS_LIGHT_EFFECT_MAX					// 最大値
	};

	// 総合3D描画
	enum
	{
		RENDER_PASS_3D_MERGE_COLOR = 0,					// 色
		RENDER_PASS_3D_MERGE_DEPTH,						// 深度
		RENDER_PASS_3D_MERGE_MAX						// 最大値
	};

	// X方向ブラー
	enum
	{
		RENDER_PASS_BLUR_X_COLOR = 0,					// 色
		RENDER_PASS_BLUR_X_MAX							// 最大値
	};

	// Y方向ブラー
	enum
	{
		RENDER_PASS_BLUR_Y_COLOR = 0,					// 色
		RENDER_PASS_BLUR_Y_LUMINANCE,					// 輝度
		RENDER_PASS_BLUR_Y_MAX							// 最大値
	};

	// 2D描画
	enum
	{
		RENDER_PASS_2D_COLOR = 0,						// 色
		RENDER_PASS_2D_MASK,							// マスク
		RENDER_PASS_2D_MAX								// 最大値
	};

	// 画面描画
	enum
	{
		RENDER_PASS_POST_EFFECT_COLOR = 0,				// 色
		RENDER_PASS_POST_EFFECT_MAX						// 最大値
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
		LIGHT_POINT_MAX = 16				// 最大値
	};

	// カメラ
	enum
	{
		CAMERA_GENERAL = 0,					// 通常カメラ
		CAMERA_SHADOW_NEAR,					// 影用カメラ近
		CAMERA_SHADOW_FAR,					// 影用カメラ遠
		CAMERA_SHADOW_POINT_0,				// 影用カメラ点0
		CAMERA_SHADOW_POINT_1,				// 影用カメラ点1
		CAMERA_MAX							// 最大値
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
	
	//==============================================================================
	// Brief  : ビルボードポリゴンクラスの設定
	// Return : void								: なし
	// Arg    : PolygonBillboard* pValue			: 設定する値
	//==============================================================================
	static void SetPolygonBillboard( PolygonBillboard* pValue );

	static const int	MAXIMUM_LIGHT_POINT_SHADOW = 2;		// 影を落とす点光源最大数

protected:
	static Polygon2D*			pPolygon2D_;			// 2Dポリゴン
	static Polygon3D*			pPolygon3D_;			// 3Dポリゴン
	static PolygonBillboard*	pPolygonBillboard_;		// ビルボードポリゴン

private:
	void InitializeSelf( void );
	GraphicMain( const GraphicMain& );
	GraphicMain operator=( const GraphicMain& );
};

#endif	// MY_GRAPHIC_MAIN_H
