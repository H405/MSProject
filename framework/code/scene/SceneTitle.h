//==============================================================================
//
// File   : SceneTitle.h
// Brief  : タイトルシーンクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_SCENE_TITLE_H
#define MY_SCENE_TITLE_H

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
#define FIREWORKS_MAX (16)
#define TARGET_MAX (16)

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class CameraObject;
class LightDirection;
class ManagerPoint;
class ManagerFireworks;
class Object2D;
class Object3D;
class Material;
class ObjectModel;
class ObjectModelMaterial;
class PolygonMesh;
class ObjectSky;
class ObjectSkinMesh;
class ObjectMesh;
class ObjectRiver;
class ObjectWaterwheel;
class Player;
class Sound;

//******************************************************************************
// クラス定義
//******************************************************************************
class SceneTitle : public SceneMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	SceneTitle( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~SceneTitle( void );

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
	// Arg    : SceneTitle* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( SceneTitle* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

protected:

private:
	void InitializeSelf( void );
	SceneTitle( const SceneTitle& );
	SceneTitle operator=( const SceneTitle& );
	
	CameraObject*	pCamera_;					// カメラ
	CameraObject*	pCameraShadowNear_;			// 影用カメラ近
	CameraObject*	pCameraShadowFar_;			// 影用カメラ遠
	CameraObject**	ppCameraShadowPoint_;		// 影用カメラ点
	LightDirection*	pLight_;					// ライト


	//	タイトルUI関係
	//----------------------------------------------------------
	//	タイトルロゴ
	Object2D* titleLogo;

	//	「Aボタンを押してね」文字
	Object2D* pushAKey;

	//	「演舞開始」文字
	Object2D* startGame;

	//	「練習開始」文字
	Object2D* startTutorial;

	//	wiiリモコンで操作する指
	Object2D* finger;

	//	「wiiリモコン再接続要求」オブジェクト
	Object2D* reConnectWiimote;

	//	「wiiボード再接続要求」オブジェクト
	Object2D* reConnectWiiboard;

	//	選択肢のうち、選ばれているオブジェクトのポインタ
	Object2D* chooseObject;
	Object2D* chooseObjectPrev;

	//	pushAKey点滅用
	int pushAKeyFlashingCount;

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

//	ObjectSkinMesh*			markers;		// 場所の目印

	//	プレイヤー
	Player* player;

	// ポイントスプライト管理クラス
	ManagerPoint* managerPoint;

	//	花火管理クラス
	ManagerFireworks* managerFireworks;

//	ObjectSkinMesh*		pObjectSkinMesh_[3];		// スキンメッシュ

	//	打ち上げに関するフラグとカウンタ
	bool launchFlag;
	int launchCount;

	//	ターゲットと花火の当たり判定用テーブル
	int fireworksTable[FIREWORKS_MAX];
	int fireworksTableIndex;

	static const int	COUNT_HOUSE = 11;		// 家の数
	//----------------------------------------------------------

	//	音関連
	//----------------------------------------------------------
	Sound* bgmSound;
	Sound* desideSound;
	Sound* selectSound;
	Sound* cancelSound;
	//----------------------------------------------------------

	//==============================================================================
	// Brief  : 更新処理1(「Aボタンを押してね」の点滅)
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void firstUpdate( void );

	//==============================================================================
	// Brief  : 更新処理2(ゲーム開始・チュートリアル開始の選択処理)
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void secondUpdate( void );

	//==============================================================================
	// Brief  : 更新処理(決定キー押された後の遷移処理)
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void fadeUpdate( void );
	void fadeUpdateDemo( void );

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

	//	更新関数格納用ポインタ
	void (SceneTitle::*fpUpdate)(void);
	void (SceneTitle::*fpUpdatePrev)(void);
};

#endif	// MY_SCENE_TITLE_H
