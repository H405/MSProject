//==============================================================================
//
// File   : PointState.cpp
// Brief  : ポイントスプライトのステート
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "PointState.h"
#include "Point.h"

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
// Brief  : 更新処理
// Return : void								: なし
// Arg    : Point* pPoint						: 対象
//==============================================================================
void PointState::Update( Point* pPoint )
{
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : Point* pPoint						: 対象
//==============================================================================
void PointStateNone::Update( Point* pPoint )
{
	// 消滅
	if( pPoint->GetTime() >= pPoint->GetTimeExist() )
	{
		pPoint->SetIsEnable( false );
	}
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : Point* pPoint						: 対象
//==============================================================================
void PointStateAdd::Update( Point* pPoint )
{
	// 変化量を加算
	D3DXVECTOR3	position;		// 座標
	D3DXCOLOR	color;			// 色
	pPoint->GetDifferencePosition( &position );
	pPoint->AddPosition( position );
	pPoint->GetDifferenceColor( &color );
	pPoint->AddColor( color );
	pPoint->AddSize( pPoint->GetDifferenceSize() );

	// 消滅
	if( pPoint->GetTime() >= pPoint->GetTimeExist() )
	{
		pPoint->SetIsEnable( false );
	}
}
//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : Point* pPoint						: 対象
//==============================================================================
void PointStateMultiply::Update( Point* pPoint )
{
	// 変化量を乗算
	D3DXVECTOR3	position;		// 座標
	D3DXCOLOR	color;			// 色
	pPoint->GetDifferencePosition( &position );
	pPoint->MultiplyPosition( position );
	pPoint->GetDifferenceColor( &color );
	pPoint->MultiplyColor( color );
	pPoint->MultiplySize( pPoint->GetDifferenceSize() );

	// 消滅
	if( pPoint->GetTime() >= pPoint->GetTimeExist() )
	{
		pPoint->SetIsEnable( false );
	}
}
