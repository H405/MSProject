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

typedef enum
{
	ADD_1 = 0,
	ADD_5,
	ADD_10,
	ADD_20,
}ADD_SCORE_STATE;

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class CameraObject;
class CameraStateSpline;
class Gage;
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
class ObjectRiver;
class ObjectSkinMesh;
class ObjectWaterwheel;
class Player;

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

	static const int	COUNT_HOUSE = 11;		// 家の数
	static const int	COUNT_GRASS = 500;		// 草の数

	CameraObject*	pCamera_;					// カメラ
	CameraObject*	pCameraShadowNear_;			// 影用カメラ近
	CameraObject*	pCameraShadowFar_;			// 影用カメラ遠
	CameraObject**	ppCameraShadowPoint_;		// 影用カメラ点
	LightDirection*	pLight_;					// ライト


	//	ゲームUI関係
	//----------------------------------------------------------
	//	「スコア」文字
	Object2D* stringScore;

	//	スコアオブジェクト
	ObjectScore* score;

	//	ゲージオブジェクト
	Gage* gage;

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

	//	「この姿勢になってABキーを同時押し」オブジェクト
	Object2D* calibrationWiimote;

	//	wiiリモコンで操作する指
	Object2D* finger;

	//	選択肢のうち、選ばれているオブジェクトのポインタ
	Object2D* chooseObject;
	Object2D* chooseObjectPrev;

	//	chooseObject点滅用
	int pushChooseObjectFlashingCount;

	//	選択肢の選択方法用のフラグ
	//	true = wiiリモコン（IR）
	//	false = 方向キー	とする
	bool chooseFlag;
	//----------------------------------------------------------


	//	ゲーム用ステージ・３Dオブジェクト関係
	//----------------------------------------------------------

	ObjectSky*				sky;			// 空
	ObjectRiver*			river;			// 川
	ObjectModel*			field;			// 地形

	ObjectModelMaterial*	bridge;			// 橋
	ObjectWaterwheel*		waterwheel;		// 水車
	ObjectModelMaterial*	houses;			// 家
	ObjectModelMaterial*	gate;			// 鳥居

	ObjectBillboard*		grasses;		// 草

	ObjectSkinMesh*			markers;		// 場所の目印

	//	プレイヤー
	Player* player;

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
	//----------------------------------------------------------

	//	カメラの方向
	CAMERA_STATE cameraState;

	//==============================================================================
	// Brief  : calibration時用の更新処理
	//==============================================================================
	void calibrationUpdate(void);

	//==============================================================================
	// Brief  : 通常時用の更新処理
	//==============================================================================
	void normalUpdate(void);

	//==============================================================================
	// Brief  : ポーズ時用の更新処理
	//==============================================================================
	void pauseUpdate(void);

	//==============================================================================
	// Brief  : ポーズ時用の更新処理(ポーズ中のフェード用)
	//==============================================================================
	void pauseFadeUpdate(void);

	//==============================================================================
	// Brief  : 再接続要求時用の更新処理
	//==============================================================================
	void reConnectWiimoteUpdate(void);

	//==============================================================================
	// Brief  : 再接続要求時用の更新処理
	//==============================================================================
	void reConnectWiiboardUpdate(void);

	//==============================================================================
	// Brief  : wiiリモコンのロストチェック処理
	//==============================================================================
	bool wiiLostCheck(void);

	//==============================================================================
	// Brief  : 花火とターゲットの当たり判定処理
	//==============================================================================
	void collision_fireworks_target();

	//==============================================================================
	// Brief  : 花火と花火の当たり判定処理
	//==============================================================================
	void collision_fireworks_fireworks();

	//==============================================================================
	// Brief  : ステージ関連の読み込み処理
	//==============================================================================
	void InitializeStage(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : その他３Dオブジェクトの読み込み処理
	//==============================================================================
	void Initialize3DObject(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : UI関連の読み込み処理
	//==============================================================================
	void InitializeUI(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : プレイヤーの移動処理
	//==============================================================================
	void MovePlayer();

	//==============================================================================
	// Brief  : 花火打ち上げ処理
	//==============================================================================
	void LaunchFireworks();

	//==============================================================================
	// Brief  : シンクロゲージの加算処理処理
	//==============================================================================
	void AddGage(ADD_SCORE_STATE _state);

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
	// ゲームセクション
	enum
	{
		SECTION_WATERWHEEL = 0,		// 水車
		SECTION_HOUSE,				// 民家
		SECTION_BRIDGE,				// 橋
		SECTION_MAXIMUM				// 最大値
	};

	// カウントダウン画像
	enum
	{
		IMAGE_COUNT_3 = 0,			// カウント3
		IMAGE_COUNT_2,				// カウント2
		IMAGE_COUNT_1,				// カウント1
		IMAGE_COUNT_START,			// 演武開始
		IMAGE_COUNT_MAXIMUM			// 最大値
	};

	// リザルト画像
	enum
	{
		IMAGE_RESULT_BACK = 0,			// 背景
		IMAGE_RESULT_LOGO,				// ロゴ
		IMAGE_RESULT_SYNCRONIZE,		// シンクロ
		IMAGE_RESULT_JUDGE_0,			// 判定0
		IMAGE_RESULT_JUDGE_1,			// 判定1
		IMAGE_RESULT_JUDGE_2,			// 判定2
		IMAGE_RESULT_TO_RANKING,		// ランキングへ
		IMAGE_RESULT_TO_TITLE,			// タイトルへ
		IMAGE_RESULT_MAXIMUM			// 最大値
	};

	// ランキング画像
	enum
	{
		IMAGE_RANKING_LOGO = 0,			// ロゴ
		IMAGE_RANKING_RANK_1,			// ランク1
		IMAGE_RANKING_RANK_2,			// ランク2
		IMAGE_RANKING_RANK_3,			// ランク3
		IMAGE_RANKING_RANK_4,			// ランク4
		IMAGE_RANKING_RANK_5,			// ランク5
		IMAGE_RANKING_MAXIMUM			// 最大値
	};

	// リザルト演出時間
	enum
	{
		TIME_RESULT_BEGIN				= 0,																		// 開始
		TIME_RESULT_BEGIN_BACK			= 0,																		// 背景開始時間
		COUNT_RESULT_BEGIN_BACK			= 10,																		// 背景開始フレーム数
		TIME_RESULT_BEGIN_LOGO			= TIME_RESULT_BEGIN_BACK + COUNT_RESULT_BEGIN_BACK,							// ロゴ開始時間
		COUNT_RESULT_BEGIN_LOGO			= 20,																		// ロゴ開始フレーム数
		TIME_RESULT_BEGIN_SYNCRONIZE	= TIME_RESULT_BEGIN_LOGO + COUNT_RESULT_BEGIN_LOGO,							// シンクロ率開始時間
		COUNT_RESULT_BEGIN_SYNCRONIZE	= 20,																		// シンクロ率開始フレーム数
		TIME_RESULT_BEGIN_JUDGE_0		= TIME_RESULT_BEGIN_SYNCRONIZE + COUNT_RESULT_BEGIN_SYNCRONIZE + 10,		// 判定0開始時間
		COUNT_RESULT_BEGIN_JUDGE_0		= 15,																		// 判定0開始フレーム数
		TIME_RESULT_BEGIN_JUDGE_1		= TIME_RESULT_BEGIN_JUDGE_0 + 5,											// 判定1開始時間
		COUNT_RESULT_BEGIN_JUDGE_1		= 15,																		// 判定1開始フレーム数
		TIME_RESULT_BEGIN_JUDGE_2		= TIME_RESULT_BEGIN_JUDGE_0 + 10,											// 判定2開始時間
		COUNT_RESULT_BEGIN_JUDGE_2		= 15,																		// 判定2開始フレーム数
		TIME_RESULT_BEGIN_GAUGE			= TIME_RESULT_BEGIN_JUDGE_2 + COUNT_RESULT_BEGIN_JUDGE_2,					// シンクロゲージ開始時間
		COUNT_RESULT_BEGIN_GAUGE		= 120,																		// シンクロゲージ開始フレーム数
		TIME_RESULT_BEGIN_TO_RANKING	= TIME_RESULT_BEGIN_GAUGE + COUNT_RESULT_BEGIN_GAUGE + 30,					// ランキングへ開始開始時間
		COUNT_RESULT_BEGIN_TO_RANKING	= 20,																		// ランキングへ開始開始フレーム数
		TIME_RESULT_BEGIN_TO_TITLE		= TIME_RESULT_BEGIN_GAUGE + COUNT_RESULT_BEGIN_GAUGE + 30,					// タイトルへ開始開始時間
		COUNT_RESULT_BEGIN_TO_TITLE		= 20,																		// タイトルへ開始開始フレーム数
		TIME_RESULT_END					= TIME_RESULT_BEGIN_TO_TITLE + COUNT_RESULT_BEGIN_TO_TITLE					// 終了
	};

	// ランキング演出時間
	enum
	{
		TIME_RANKING_BEGIN				= 0,																		// 開始
		TIME_RANKING_BEGIN_LOGO			= 0,																		// ロゴ開始時間
		COUNT_RANKING_BEGIN_LOGO		= 20,																		// ロゴ開始フレーム数
		TIME_RANKING_BEGIN_RANK_5		= TIME_RANKING_BEGIN_LOGO + COUNT_RANKING_BEGIN_LOGO + 10,					// ランク5開始時間
		COUNT_RANKING_BEGIN_RANK_5		= 20,																		// ランク5開始フレーム数
		TIME_RANKING_BEGIN_RANK_4		= TIME_RANKING_BEGIN_LOGO + COUNT_RANKING_BEGIN_LOGO + 20,					// ランク4開始時間
		COUNT_RANKING_BEGIN_RANK_4		= 20,																		// ランク4開始フレーム数
		TIME_RANKING_BEGIN_RANK_3		= TIME_RANKING_BEGIN_LOGO + COUNT_RANKING_BEGIN_LOGO + 30,					// ランク3開始時間
		COUNT_RANKING_BEGIN_RANK_3		= 20,																		// ランク3開始フレーム数
		TIME_RANKING_BEGIN_RANK_2		= TIME_RANKING_BEGIN_LOGO + COUNT_RANKING_BEGIN_LOGO + 40,					// ランク2開始時間
		COUNT_RANKING_BEGIN_RANK_2		= 20,																		// ランク2開始フレーム数
		TIME_RANKING_BEGIN_RANK_1		= TIME_RANKING_BEGIN_RANK_2 + COUNT_RANKING_BEGIN_RANK_2 + 20,				// ランク1開始時間
		COUNT_RANKING_BEGIN_RANK_1		= 30,																		// ランク1開始フレーム数
		TIME_RANKING_END				= TIME_RANKING_BEGIN_RANK_1 + COUNT_RANKING_BEGIN_RANK_1					// 終了
	};

	static const int	MAXIMUM_RANK = 5;		// ランキング最大数

	CameraStateSpline*	pStateCameraPrevious_;				// ゲーム開始前カメラ処理
	CameraStateSpline*	pStateCameraBetween_;				// ゲームセクション間カメラ処理
	CameraStateSpline*	pStateCameraResult_;				// リザルト前カメラ処理
	int					timerSceneGame_;					// ゲームシーン経過時間

	Object2D*			pObjectCount_;						// カウントダウン画像オブジェクト

	Object2D*			pObjectResult_;						// リザルト画像オブジェクト

	int					pRankingScore_[ MAXIMUM_RANK ];		// ランキングのスコア
	int					indexRank_;							// ランクの番号
	Object2D*			pObjectRanking_;					// ランキング画像オブジェクト
	ObjectScore*		pObjectScoreRanking_;				// ランキングスコアオブジェクト

	int					indexSection_;						// ゲームセクション番号

	ObjectModel*		pObjectTestForShadow_;				// 影確認用

	int Initialize2( void );
	int Finalize2( void );
	void InitializeSelf2( void );

	// ゲーム開始前更新
	void UpdatePreviousGame( void );

	// ゲーム開始前カウントダウン更新
	void UpdateCountDownGame( void );

	// ゲームセクション間更新
	void UpdateBetweenSection( void );

	// リザルト待機更新
	void UpdateWaitResult( void );

	// リザルト前更新
	void UpdatePreviousResult( void );

	// リザルト更新
	void UpdateResult( void );

	// ランキング更新
	void UpdateRanking( void );

	// テスト更新
	void UpdateTest( void );

	// カメラのテスト更新
	void UpdateTestCamera( void );

	// リザルトオブジェクトを非表示にする
	void DisableObjectResult( void );

	// ランキングオブジェクトを非表示にする
	void DisableObjectRanking( void );

	//==============================================================================
	// ↑白川追加
	//==============================================================================

	//	更新関数格納用ポインタ
	void (SceneGame::*fpUpdate)(void);

	//	一時変数
	int targetAppearCount;
	D3DXVECTOR3 buffWiiAccel;
	D3DXVECTOR3 buffWiiRot;
};

#endif	// MY_SCENE_GAME_H
