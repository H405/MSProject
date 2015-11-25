//==============================================================================
//
// File   : ObjectSky.h
// Brief  : 空オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_SKY_H
#define MY_OBJECT_SKY_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../framework/object/ObjectMovement.h"

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
class GraphicSky;
class Material;
class PolygonMeshDomeInside;
class Texture;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectSky : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectSky( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectSky( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : int countCellX						: X方向セル数
	// Arg    : int countCellY						: Z方向セル数
	// Arg    : float radius						: 半径
	// Arg    : float lengthTextureX				: X方向テクスチャ長さ
	// Arg    : float lengthTextureY				: Z方向テクスチャ長さ
	//==============================================================================
	int Initialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellY, float radius, float lengthTextureX, float lengthTextureY );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : int countCellX						: X方向セル数
	// Arg    : int countCellY						: Z方向セル数
	// Arg    : float radius						: 半径
	// Arg    : float lengthTextureX				: X方向テクスチャ長さ
	// Arg    : float lengthTextureY				: Z方向テクスチャ長さ
	//==============================================================================
	int Reinitialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellY, float radius, float lengthTextureX, float lengthTextureY );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ObjectSky* pOut						: コピー先アドレス
	//==============================================================================
	int Copy( ObjectSky* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : 描画クラスの生成
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
	// Arg    : Texture* pTexture					: テクスチャ
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Effect* pEffectReflect, Texture* pTexture );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicSky* pValue );
	GraphicSky* GetGraphic( void ) const;

protected:

private:
	void InitializeSelf( void );
	ObjectSky( const ObjectSky& );
	ObjectSky operator=( const ObjectSky& );

	GraphicSky*				pGraphic_;			// 描画クラス
	PolygonMeshDomeInside*	pPolygonMesh_;		// 内部メッシュドームポリゴン
};

#endif	// MY_OBJECT_SKY_H
