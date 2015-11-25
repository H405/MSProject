//==============================================================================
//
// File   : ObjectSkinMesh.h
// Brief  : スキンメッシュオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_SKIN_MESH_H
#define MY_OBJECT_SKIN_MESH_H

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
class GraphicSkinMesh;
class Model;
class Motion;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectSkinMesh : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectSkinMesh( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectSkinMesh( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	// Arg    : int countMotion						: モーション数
	//==============================================================================
	int Initialize( int priority, int countMotion );

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
	// Arg    : int countMotion						: モーション数
	//==============================================================================
	int Reinitialize( int priority, int countMotion );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ObjectSkinMesh* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( ObjectSkinMesh* pOut ) const;

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
	// Arg    : Model* pModel						: モデル
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
	//==============================================================================
	int CreateGraphic( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral, Effect* pEffectReflect );

	//==============================================================================
	// Brief  : 次のモーションを設定
	// Return : void								: なし
	// Arg    : int indexMotion						: 次のモーション番号
	// Arg    : int timeBeginBlend					: ブレンド開始時間
	// Arg    : int timeBlend						: ブレンド時間
	//==============================================================================
	void SetNextMotion( int indexMotion, int timeBeginBlend, int timeBlend );

	//==============================================================================
	// Brief  : ブレンド中か判定
	// Return : bool								: ブレンド中かどうか
	// Arg    : void								: なし
	//==============================================================================
	bool IsBlending( void );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicSkinMesh* pValue );
	GraphicSkinMesh* GetGraphic( void ) const;
	void SetTableMotion( int index, Motion* pValue );
	Motion* GetTableMotion( int index ) const;
	void SetMatrixBoneCurrent( int index, const D3DXMATRIX& value );
	void GetMatrixBoneCurrent( int index, D3DXMATRIX* pOut ) const;
	int GetIndexMotionCurrent( void ) const;
	int GetIndexMotionNext( void ) const;
	int GetIndexFrame( void ) const;

protected:
	GraphicSkinMesh*	pGraphic_;		// 描画クラス

private:
	void InitializeSelf( void );
	ObjectSkinMesh( const ObjectSkinMesh& );
	ObjectSkinMesh operator=( const ObjectSkinMesh& );

	Model*		pModel_;					// モデル
	Motion**	ppTableMotion_;				// モーションテーブル
	D3DXMATRIX*	pMatrixBoneCurrent_;		// 現在のボーン変換行列
	int			countMotion_;				// モーション数
	int			indexMotionCurrent_;		// 現在のモーション番号
	int			indexMotionNext_;			// 次のモーション番号
	int			indexFrame_;				// フレーム番号
	int			indexFrameBeginBlend_;		// ブレンド開始フレーム番号
	int			countFrameBlend_;			// ブレンドするフレーム数
};

#endif	// MY_OBJECT_SKIN_MESH_H
