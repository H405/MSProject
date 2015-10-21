//==============================================================================
//
// File   : ObjectMesh.h
// Brief  : メッシュポリゴンオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_MESH_H
#define MY_OBJECT_MESH_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../framework/object/ObjectMovement.h"
#include "../framework/graphic/Material.h"

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
class GraphicMesh;
class PolygonMesh;
class Texture;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectMesh : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectMesh( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectMesh( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : int countCellX						: X方向セル数
	// Arg    : int countCellZ						: Z方向セル数
	// Arg    : float lengthCellX					: X方向セル長さ
	// Arg    : float lengthCellZ					: Z方向セル長さ
	// Arg    : float lengthTextureX				: X方向テクスチャ長さ
	// Arg    : float lengthTextureZ				: Z方向テクスチャ長さ
	//==============================================================================
	int Initialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
		float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ );

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
	// Arg    : int countCellZ						: Z方向セル数
	// Arg    : float lengthCellX					: X方向セル長さ
	// Arg    : float lengthCellZ					: Z方向セル長さ
	// Arg    : float lengthTextureX				: X方向テクスチャ長さ
	// Arg    : float lengthTextureZ				: Z方向テクスチャ長さ
	//==============================================================================
	int Reinitialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
		float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ObjectMesh* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( ObjectMesh* pOut ) const;

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
	// Arg    : Texture* pTexture					: テクスチャ
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicMesh* pValue );
	GraphicMesh* GetGraphic( void ) const;

protected:
	GraphicMesh*	pGraphic_;		// 描画クラス
	PolygonMesh*	pPolygon_;		// メッシュポリゴン
	Material		material_;		// マテリアル

private:
	void InitializeSelf( void );
	ObjectMesh( const ObjectMesh& );
	ObjectMesh operator=( const ObjectMesh& );
};

#endif	// MY_OBJECT_MESH_H
