//==============================================================================
//
// File   : SceneGame.h
// Brief  : ゲームシーンクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_SCENE_GAME_H
#define MY_SCENE_GAME_H

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
class LightDirection;

class Object2D;
class Object3D;
class Material;
class ObjectModel;
class PolygonMesh;
class ObjectMesh;

//******************************************************************************
// クラス定義
//******************************************************************************
class SceneGame : public SceneMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	SceneGame( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~SceneGame( void );

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
	// Arg    : SceneGame* pOut						: コピー先アドレス
	//==============================================================================
	int Copy( SceneGame* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

protected:

private:
	void InitializeSelf( void );
	SceneGame( const SceneGame& );
	SceneGame operator=( const SceneGame& );

	CameraObject*		pCamera_;				// カメラ
	LightDirection*		pLight_;				// ライト

	//	「スコア」文字
	Object2D* stringScore;

	//	ポーズ時用文字「再開」
	Object2D* stringReturn;

	//	ポーズ時用文字「中止」
	Object2D* stringStop;

	//	ポーズ時用文字「初めから」
	Object2D* stringRetry;

	//	１ステージクリア後文字「次のステージへ」
	Object2D* stringNext;

	//==============================================================================
	// Brief  : 通常時用の更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void normalUpdate();

	//==============================================================================
	// Brief  : ポーズ時用の更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void pauseUpdate();

	//	更新関数格納用ポインタ
	void (SceneGame::*fpUpdate)(void);
};

#endif	// MY_SCENE_GAME_H
