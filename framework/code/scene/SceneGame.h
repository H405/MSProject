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
class CameraStateSpline;
class LightDirection;
class ManagerPoint;
class ManagerFireworks;
class ManagerTarget;
class Object2D;
class ObjectScore;
class Object3D;
class Material;
class ObjectModel;
class ObjectModelMaterial;
class PolygonMesh;
class ObjectMesh;
class ObjectSky;
class ObjectBillboard;

class GraphicPoint;
class PolygonPoint;

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

	CameraObject*		pCamera_;		// カメラ
	LightDirection*		pLight_;		// ライト

	ObjectSky*			pObjectSky_;	// スカイドーム

	//	「スコア」文字
	Object2D* stringScore;

	//	スコアオブジェクト
	ObjectScore* score;

	//	ポーズ時用背景
	Object2D* pauseFrame;

	//	ポーズ時用文字「再開」
	Object2D* stringReturn;

	//	ポーズ時用文字「中止」
	Object2D* stringStop;

	//	ポーズ時用文字「初めから」
	Object2D* stringRetry;

	//	１ステージクリア後文字「次のステージへ」
	Object2D* stringNext;

	//	「wiiリモコン再接続要求」オブジェクト
	Object2D* reConnectWiimote;

	//	「wiiボード再接続要求」オブジェクト
	Object2D* reConnectWiiboard;

	//	wiiリモコンで操作する指
	Object2D* finger;

	//	選択肢のうち、選ばれているオブジェクトのポインタ
	Object2D* chooseObject;
	Object2D* chooseObjectPrev;

	//	テスト用
	ObjectModelMaterial* testArm;
	ObjectModelMaterial* testObj[4];

	//	仮フィールド
	ObjectMesh* field;

	// ポイントスプライト管理クラス
	ManagerPoint* managerPoint;

	//	花火管理クラス
	ManagerFireworks* managerFireworks;

	//	ターゲット管理クラス
	ManagerTarget* managerTarget;

	//	chooseObject点滅用
	int pushChooseObjectFlashingCount;

	//	選択肢の選択方法用のフラグ
	//	true = wiiリモコン（IR）
	//	false = 方向キー	とする
	bool chooseFlag;

	//==============================================================================
	// Brief  : 通常時用の更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void normalUpdate(void);

	//==============================================================================
	// Brief  : ポーズ時用の更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void pauseUpdate(void);

	//==============================================================================
	// Brief  : ポーズ時用の更新処理(ポーズ中のフェード用)
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void pauseFadeUpdate(void);

	//==============================================================================
	// Brief  : 再接続要求時用の更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void reConnectWiimoteUpdate(void);

	//==============================================================================
	// Brief  : 再接続要求時用の更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void reConnectWiiboardUpdate(void);

	//==============================================================================
	// Brief  : wiiリモコンのロストチェック処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	bool wiiLostCheck(void);

	//==============================================================================
	// Brief  : 花火とターゲットの当たり判定処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void collision_fireworks_target();

	//==============================================================================
	// ↓白川追加
	//==============================================================================
	CameraStateSpline*	pStateCameraPrevious_;		// ゲーム開始前カメラ処理
	CameraStateSpline*	pStateCameraResult_;		// リザルト前カメラ処理
	int					timerSceneGame_;			// ゲームシーン経過時間

	int Initialize2( void );
	int Finalize2( void );
	void InitializeSelf2( void );

	// ゲーム開始前更新
	void UpdatePreviousGame( void );

	// ゲーム開始前カウントダウン更新
	void UpdateCountDownGame( void );

	// リザルト待機更新
	void UpdateWaitResult( void );

	// リザルト前更新
	void UpdatePreviousResult( void );

	// リザルト更新
	void UpdateResult( void );

	//==============================================================================
	// ↑白川追加
	//==============================================================================

	//	更新関数格納用ポインタ
	void (SceneGame::*fpUpdate)(void);

	bool buffFlag;
};

#endif	// MY_SCENE_GAME_H
