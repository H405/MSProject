//==============================================================================
//
// File   : Utility.h
// Brief  : メイン関数
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_UTILITY_H
#define MY_UTILITY_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// プロトタイプ宣言
//******************************************************************************
namespace Utility
{
	// スプライン曲線のコントロールポイント
	class ControlPointSpline
	{
	public:
		ControlPointSpline( void );			// コンストラクタ
		~ControlPointSpline( void );		// デストラクタ

		D3DXVECTOR3	position_;		// 座標
		D3DXVECTOR3	vector_;			// ベクトル
	};

	//==============================================================================
	// Brief  : イージング処理
	// Return : float								: 結果
	// Arg    : float begin							: 開始
	// Arg    : float end							: 終了
	// Arg    : float time							: 時間
	//==============================================================================
	float Easing( float begin, float end, float time );

	//==============================================================================
	// Brief  : スプライン処理
	// Return : void								: なし
	// Arg    : const ControlPointSpline& begin		: 開始コントロールポイント
	// Arg    : const ControlPointSpline& end		: 終了コントロールポイント
	// Arg    : float time							: 時間
	// Arg    : D3DXVECTOR3* pOut					: 出力先
	//==============================================================================
	void Spline( const ControlPointSpline& begin, const ControlPointSpline& end, float time, D3DXVECTOR3* pOut );

	//==============================================================================
	// Brief  : スプライン処理
	// Return : void								: なし
	// Arg    : const D3DXVECTOR3& positionBegin	: 開始座標
	// Arg    : const D3DXVECTOR3& vectorBegin		: 開始ベクトル
	// Arg    : const D3DXVECTOR3& positionEnd		: 終了座標
	// Arg    : const D3DXVECTOR3& vectonEnd		: 終了ベクトル
	// Arg    : float time							: 時間
	// Arg    : D3DXVECTOR3* pOut					: 出力先
	//==============================================================================
	void SplineVector3( const D3DXVECTOR3& positionBegin, const D3DXVECTOR3& vectorBegin, const D3DXVECTOR3& positionEnd, const D3DXVECTOR3& vectorEnd,
		float time, D3DXVECTOR3* pOut );
};

#endif // MY_UTILITY_H
