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
class VertexBuffer;

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
	// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize( int maximumItem, IDirect3DDevice9* pDevice, const EffectParameter* pParameter,
		Effect* pEffectGeneral, Effect* pEffectReflect, IDirect3DTexture9* pTexture );

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
	// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Reinitialize( int maximumItem, IDirect3DDevice9* pDevice, const EffectParameter* pParameter,
		Effect* pEffectGeneral, Effect* pEffectReflect, IDirect3DTexture9* pTexture );

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

	//==============================================================================
	// Brief  : ポイントの追加
	// Return : void								: なし
	// Arg    : int indexState						: ステート番号
	// Arg    : const D3DXVECTOR3& position			: 座標
	// Arg    : const D3DXCOLOR& color				: 色
	// Arg    : float size							: 大きさ
	//==============================================================================
	void Add( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size );

	//==============================================================================
	// Brief  : ポイントの追加
	// Return : void								: なし
	// Arg    : int indexState						: ステート番号
	// Arg    : const D3DXVECTOR3& position			: 座標
	// Arg    : const D3DXCOLOR& color				: 色
	// Arg    : float size							: 大きさ
	//==============================================================================
	Point* AddR( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size );

	//==============================================================================
	// Brief  : ポイントの追加
	// Return : void								: なし
	// Arg    : int timeExist						: 残存時間
	// Arg    : const D3DXVECTOR3& position			: 座標
	// Arg    : const D3DXCOLOR& color				: 色
	// Arg    : float size							: 大きさ
	// Arg    : const D3DXVECTOR3& differencePosition	: 座標の変化量
	// Arg    : const D3DXCOLOR& differenceColor	: 色の変化量
	// Arg    : float differenceSize				: 大きさの変化量
	// Arg    : int indexState						: ステート番号
	//==============================================================================
	void Add( int timeExist, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size,
		const D3DXVECTOR3& differencePosition, const D3DXCOLOR& differenceColor, float differenceSize,
		int indexState = STATE_ADD );

protected:

private:
	ManagerPoint( const ManagerPoint& );
	ManagerPoint operator=( const ManagerPoint& );

	void InitializeSelf( void );
	int GetIndex( void );

	PointState*		ppState_[ STATE_MAX ];		// ステートテーブル
	int				maximumItem_;				// 最大要素数
	int				indexCurrent_;				// 現在の要素番号
	Point*			pPoint_;					// ポイント情報
	PolygonPoint*	pPolygon_;					// ポリゴン
	GraphicPoint*	pGraphic_;					// 描画クラス
	VertexBuffer*	pVertexBuffer_;				// 頂点バッファ
};

#endif	// MY_MANAGER_POINT_H
