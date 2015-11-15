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
#include "d3dx9.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************
#define FIREWORKS_MAX (16)
#define TARGET_MAX (16)

//******************************************************************************
// 列挙体
//******************************************************************************
typedef enum
{
	CAMERA_STATE_FRONT = 0,
	CAMERA_STATE_LEFT,
	CAMERA_STATE_BACK,
	CAMERA_STATE_RIGHT,
	CAMERA_STATE_MAX
}CAMERA_STATE;

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
class ObjectSkinMesh;
class ObjectWaterwheel;

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

	//	水車オブジェクト
	ObjectWaterwheel* waterWheel[3];

	//	家
	ObjectModelMaterial* house[3];

	//	橋
	ObjectModelMaterial* bridge;

	//	フィールド
	ObjectModel* field;

	//	プレイヤー
	ObjectModelMaterial* player;
	ObjectModelMaterial* playerArm;

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

	// ポイントスプライト管理クラス
	ManagerPoint* managerPoint;

	//	花火管理クラス
	ManagerFireworks* managerFireworks;

	//	ターゲット管理クラス
	ManagerTarget* managerTarget;

	ObjectSkinMesh*		pObjectSkinMesh_[3];		// スキンメッシュ




	//	打ち上げに関するフラグとカウンタ
	bool launchFlag;
	int launchCount;

	//	ターゲットと花火の当たり判定用テーブル
	int fireworksTable[FIREWORKS_MAX];
	int targetTable[TARGET_MAX];
	int fireworksTableIndex;
	int targetTableIndex;

	//	chooseObject点滅用
	int pushChooseObjectFlashingCount;

	//	選択肢の選択方法用のフラグ
	//	true = wiiリモコン（IR）
	//	false = 方向キー	とする
	bool chooseFlag;

	//	カメラの方向
	CAMERA_STATE cameraState;

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
	// Brief  : ステージ関連の読み込み処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void InitializeStage(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : その他３Dオブジェクトの読み込み処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Initialize3DObject(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : UI関連の読み込み処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void InitializeUI(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : 点と円の当たり判定処理
	// Return : bool								: 当たったか当たってないか
	// Arg    : D3DXVECTOR3							: 点の位置
	// Arg    : D3DXVECTOR3							: 円の位置
	// Arg    : D3DXVECTOR3							: 当たってると判定する最大距離
	// Arg    : float								: 円の中心から点への距離
	//==============================================================================
	bool hitCheckPointCircle(D3DXVECTOR3 _pointPos, D3DXVECTOR3 _circlePos, float _hitCheckOffset, float* _hitPosLength);

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

	int targetAppearCount;


	//	一時変数
	D3DXVECTOR3 buffWiiAccel;
	D3DXVECTOR3 buffWiiRot;
};

#endif	// MY_SCENE_GAME_H
