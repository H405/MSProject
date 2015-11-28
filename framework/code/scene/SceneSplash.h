//==============================================================================
//
// File   : SceneSplash.h
// Brief  : スプラッシュシーンクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_SCENE_SPLASH_H
#define MY_SCENE_SPLASH_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../system/SceneMain.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class CameraObject;
class CameraStateSpline;
class LightDirection;
class LightPoint;
class ManagerPoint;
class Material;
class Object2D;
class ObjectBillboard;
class ObjectMesh;
class ObjectModel;
class ObjectModelMaterial;
class ObjectRiver;
class ObjectSkinMesh;
class ObjectSky;

//******************************************************************************
// クラス定義
//******************************************************************************
class SceneSplash : public SceneMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	SceneSplash( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~SceneSplash( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : SceneArgumentMain* pArgument		: シーン引数
	//==============================================================================
	int Initialize( SceneArgumentMain* pArgument );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : SceneArgumentMain* pArgument		: シーン引数
	//==============================================================================
	int Reinitialize( SceneArgumentMain* pArgument );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : SceneSplash* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( SceneSplash* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

protected:

private:
	void InitializeSelf( void );
	SceneSplash( const SceneSplash& );
	SceneSplash operator=( const SceneSplash& );

	CameraObject*				pCamera_;						// 通常カメラ
	CameraObject*				pCameraShadow_;					// 影用カメラ
	LightDirection*				pLight_;						// ライト
	LightPoint**				ppPointLight_;					// ポイントライト

	ManagerPoint*				pPoint_;						// ポイントスプライト管理クラス

	static const int			COUNT_MODEL = 10;				// モデル数

	Object2D*					pObject2D_;						// 2Dオブジェクト
	ObjectMesh*					pObjectMesh_;					// メッシュ
	ObjectSky*					pObjectSky_;					// スカイドーム
	ObjectModel*				pObjectModel_;					// モデル
	ObjectModelMaterial*		pObjectModelMaterial_;			// テクスチャなしモデル
	ObjectBillboard*			pObjectBoard_;					// ビルボード
	ObjectSkinMesh*				pObjectSkinMesh_;				// スキンメッシュ
	ObjectRiver*				pObjectRiver_;					// 川

	int							timerLight_;					// ライト用タイマー

	int							countLight_;					// ライト数

	CameraStateSpline*			pCameraState_;					// カメラ処理
};

#endif	// MY_SCENE_SPLASH_H
