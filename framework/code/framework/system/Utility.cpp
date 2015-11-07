//==============================================================================
//
// File   : Utility.cpp
// Brief  : メイン関数
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Utility.h"

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 関数
//******************************************************************************
namespace Utility
{
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ControlPointSpline::ControlPointSpline( void )
	{
		// メンバ変数の初期化
		position_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		vector_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	}

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ControlPointSpline::~ControlPointSpline( void )
	{
	}

	//==============================================================================
	// Brief  : イージング処理
	// Return : float								: 結果
	// Arg    : float begin							: 開始
	// Arg    : float end							: 終了
	// Arg    : float time							: 時間
	//==============================================================================
	float Easing( float begin, float end, float time )
	{
		// 割合を計算
		float	proportion;		// 割合
		if( time < 0.5f )
		{
			proportion = (2 * time) * (2 * time) * 0.5f;
		}
		else
		{
			proportion = -(2 * time - 2) * (2 * time - 2) * 0.5f + 1.0f;
		}

		// 結果を返す
		return begin + (end - begin) * proportion;
	}

	//==============================================================================
	// Brief  : スプライン処理
	// Return : void								: なし
	// Arg    : const ControlPointSpline& begin		: 開始コントロールポイント
	// Arg    : const ControlPointSpline& end		: 終了コントロールポイント
	// Arg    : float time							: 時間
	// Arg    : D3DXVECTOR3* pOut					: 出力先
	//==============================================================================
	void Spline( const ControlPointSpline& begin, const ControlPointSpline& end, float time, D3DXVECTOR3* pOut )
	{
		// スプライン処理
		SplineVector3( begin.position_, begin.vector_, end.position_, end.vector_, time, pOut );
	}

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
		float time, D3DXVECTOR3* pOut )
	{
		// 行列の設定
		D3DXVECTOR4	parameter;			// 媒介変数
		D3DXMATRIX	coefficient;		// 係数
		D3DXMATRIX	terminal;			// 端点
		parameter.x = time * time * time;
		parameter.y = time * time;
		parameter.z = time;
		parameter.w = 1.0f;
		coefficient._11 = 2.0f;
		coefficient._12 = coefficient._23 = -2.0f;
		coefficient._13 = coefficient._14 = coefficient._33 = coefficient._41 = 1.0f;
		coefficient._21 = -3.0f;
		coefficient._22 = 3.0f;
		coefficient._24 = -1.0f;
		coefficient._31 = coefficient._32 = coefficient._34 = coefficient._42 = coefficient._43 = coefficient._44 = 0.0f;
		terminal._11 = positionBegin.x;
		terminal._12 = positionBegin.y;
		terminal._13 = positionBegin.z;
		terminal._14 = 0.0f;
		terminal._21 = positionEnd.x;
		terminal._22 = positionEnd.y;
		terminal._23 = positionEnd.z;
		terminal._24 = 0.0f;
		terminal._31 = vectorBegin.x;
		terminal._32 = vectorBegin.y;
		terminal._33 = vectorBegin.z;
		terminal._34 = 0.0f;
		terminal._41 = vectorEnd.x;
		terminal._42 = vectorEnd.y;
		terminal._43 = vectorEnd.z;
		terminal._44 = 0.0f;

		// 結果の計算
		D3DXVECTOR4	position;		// 結果
		D3DXVec4Transform( &position, &parameter, &coefficient );
		D3DXVec4Transform( &position, &position, &terminal );

		// 結果を返す
		pOut->x = position.x;
		pOut->y = position.y;
		pOut->z = position.z;
	}
};

