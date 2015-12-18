//==============================================================================
//
// File   : ManagerFireworks.h
// Brief  : 花火管理オブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_MANAGER_FIREWORKS_H
#define MY_MANAGER_FIREWORKS_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "fireworks/Fireworks.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************
#define FIREWORKS_MAX (16)

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Fireworks;
class ManagerPoint;
class FireworksState;
class ManagerLight;
class LightPoint;
class LightDirection;
class SceneArgumentMain;
class Target;

//******************************************************************************
// クラス定義
//******************************************************************************
class ManagerFireworks
{
public:
	enum
	{
		STATE_RIGHT = 0,
		STATE_LEFT,
		STATE_RIGHTSP,
		STATE_LEFTSP,
		STATE_MAX
	}STATE;

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ManagerFireworks( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ManagerFireworks( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	//==============================================================================
	int Initialize(ManagerPoint* _managerPoint);

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update(int* _table , int* _fireworksTableIndex);

	//==============================================================================
	// Brief  : 花火発射処理
	// Return : int								: 配列番号
	// Arg    : int indexState						: ステート番号
	// Arg   : ManagerPoint*						: ポイントスプライト生成用マネージャ
	// Arg   : D3DXVECTOR3							: 発生位置
	// Arg   : D3DXVECTOR3							: 速度
	// Arg   : float								: 更新ごとの回転量
	// Arg   : float								: ↑に加算する回転量（大きすぎると変になるから注意）
	//==============================================================================
	int Add(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _speed,
		float _rot,
		float _rotSpeed);
	//==============================================================================
	// Brief  : 花火発射処理
	//==============================================================================
	int Add(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		COLOR_STATE _colorState = COLOR_STATE_W);
	int AddSP(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		COLOR_STATE _colorState = COLOR_STATE_W);
	int ManagerFireworks::Add(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		Target* _target)
	{
		int index = GetIndex();
		if(index < 0 || index >= FIREWORKS_MAX)
		{
			//PrintDebugWnd( _T( "ポイントに空きがありません。\n" ) );
			return -1;
		}

		//	花火のセット
		fireworks[index].Set(
			_indexState,
			_managerPoint,
			_pos,
			_diffRot,
			_target);

		return index;
	}
	int ManagerFireworks::AddW(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		Target* _target)
	{
		int index = GetIndex();
		if(index < 0 || index >= FIREWORKS_MAX)
		{
			//PrintDebugWnd( _T( "ポイントに空きがありません。\n" ) );
			return -1;
		}

		//	花火のセット
		fireworks[index].SetW(
			_indexState,
			_managerPoint,
			_pos,
			_diffRot,
			_target);

		return index;
	}

	//==============================================================================
	// Brief  : インデックス取得処理
	// Return : int									: 使用可能なオブジェクトの番号（全部使用中の場合は負の値が返る）
	// Arg    : void								: なし
	//==============================================================================
	int GetIndex();

	//==============================================================================
	// Brief  : 花火の爆発処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Burn();

	//==============================================================================
	// Brief  : テーブルのソート処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Sort(int* _table, int _deleteIndex);

	//==============================================================================
	// Brief  : 花火の音生成処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void loadSound(SceneArgumentMain* pArgument);

	//==============================================================================
	// アクセサ
	//==============================================================================
	Fireworks* getFireworks(int _index){return &fireworks[_index];}
	void setInvViewMatrix(D3DXMATRIX _invViewMatrix){invViewMatrix = _invViewMatrix;};
	void setManagerLight(ManagerLight* _managerLight);

protected:

	//	花火の配列
	Fireworks* fireworks;

	//	カメラの逆行列
	D3DXMATRIX invViewMatrix;

	//	花火の自然消滅認識用フラグ
	bool enableOld[FIREWORKS_MAX];

	// ステートテーブル
	FireworksState* ppState_[ STATE_MAX ];

	//	花火ポインタ格納用リスト
	Fireworks** fireworksList;
private:

	ManagerPoint* managerPoint;

	void InitializeSelf( void );
	ManagerFireworks( const ManagerFireworks& );
	ManagerFireworks operator=( const ManagerFireworks& );
};

#endif	// MY_MANAGER_FIREWORKS_H