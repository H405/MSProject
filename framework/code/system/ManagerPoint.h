//==============================================================================
//
// File   : ManagerPoint.h
// Brief  : ポイントスプライトの管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_MANAGER_POINT_H
#define MY_MANAGER_POINT_H

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
class Effect;
class EffectParameter;
class GraphicPoint;
class Point;
class PointState;
class PolygonPoint;
class Texture;

//******************************************************************************
// クラス定義
//******************************************************************************
class ManagerPoint
{
public:
	// ステート
	enum
	{
		STATE_NONE = 0,		// なし
		STATE_ADD,			// 加算
		STATE_MULTIPLY,		// 乗算
		STATE_MAX			// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ManagerPoint( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ManagerPoint( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int maximumItem						: 最大要素数
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize( int maximumItem, IDirect3DDevice9* pDevice, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : int maximumItem						: 最大要素数
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Reinitialize( int maximumItem, IDirect3DDevice9* pDevice, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ManagerPoint* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( ManagerPoint* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

protected:

private:
	void InitializeSelf( void );
	ManagerPoint( const ManagerPoint& );
	ManagerPoint operator=( const ManagerPoint& );

	PointState*		ppState_[ STATE_MAX ];		// ステートテーブル
	int				maximumItem_;				// 最大要素数
	Point*			pPoint_;					// ポイント情報
	PolygonPoint*	pPolygon_;					// 頂点バッファ
	GraphicPoint*	pGraphic_;					// 描画クラス
};

#endif	// MY_MANAGER_POINT_H
