//==============================================================================
//
// File   : GraphicSkinMesh.h
// Brief  : スキンメッシュ描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_SKIN_MESH_H
#define MY_GRAPHIC_SKIN_MESH_H

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
class Model;

//******************************************************************************
// クラス定義
//******************************************************************************
class GraphicSkinMesh : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	GraphicSkinMesh( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~GraphicSkinMesh( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : Model* pModel						: モデル
	// Arg    : int countBone						: ボーン数
	// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
	// Arg    : int* pIndexFrame					: フレーム番号参照アドレス
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame );

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
	// Arg    : Model* pModel						: モデル
	// Arg    : int countBone						: ボーン数
	// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
	// Arg    : int* pIndexFrame					: フレーム番号参照アドレス
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicSkinMesh* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( GraphicSkinMesh* pOut ) const;

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicSkinMesh* pValue );
	GraphicSkinMesh* GetGraphic( void ) const;

protected:
	GraphicSkinMesh*	pGraphic_;		// 描画クラス

private:
	void InitializeSelf( void );
	GraphicSkinMesh( const GraphicSkinMesh& );
	GraphicSkinMesh operator=( const GraphicSkinMesh& );

};

#endif	// MY_GRAPHIC_SKIN_MESH_H
