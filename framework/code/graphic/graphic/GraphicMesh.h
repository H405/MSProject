//==============================================================================
//
// File   : GraphicMesh.h
// Brief  : メッシュポリゴン描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_MESH_H
#define MY_GRAPHIC_MESH_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicMain.h"

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
class Material;
class PolygonMesh;

//******************************************************************************
// クラス定義
//******************************************************************************
class GraphicMesh : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	GraphicMesh( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~GraphicMesh( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : PolygonMesh* pPolygon				: メッシュポリゴン
	// Arg    : Material* pMaterial					: マテリアル
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture );

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
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : PolygonMesh* pPolygon				: メッシュポリゴン
	// Arg    : Material* pMaterial					: マテリアル
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicMesh* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( GraphicMesh* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicMesh( const GraphicMesh& );
	GraphicMesh operator=( const GraphicMesh& );
};

#endif	// MY_GRAPHIC_MESH_H
