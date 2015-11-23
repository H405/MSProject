//==============================================================================
//
// File   : Fireworks.h
// Brief  : 花火オブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_FIREWORKS_H
#define MY_FIREWORKS_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************
#define FIRE_MAX (12)

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class ManagerPoint;
class FireworksState;
class Fire;

//******************************************************************************
// 構造体定義
//******************************************************************************
typedef struct
{
	//	位置情報
	D3DXVECTOR3 pos;
	D3DXVECTOR3 setPos;

	//	行列変換用回転ベクトル
	D3DXVECTOR3 matRot;

	//	移動の回転方向
	float rot;

	//	Z軸の回転速度（１アップデートでどのくらい回転するか）
	float rotSpeed;

	//	移動速度
	D3DXVECTOR3 speed;

	//	ポイントスプライトクラス管理オブジェクト
	ManagerPoint* managerPoint;

	//	使用可能フラグ
	bool enable;

	//	破裂フラグ
	bool burnFlag;

	//	自然消滅までのカウンタ
	int deleteCount;

	Fire* fire;

	int fireMax;

	D3DXMATRIX matrix;

	//	カメラの逆行列
	D3DXMATRIX invViewMatrix;

}FIREWORKS_PARAM;

//******************************************************************************
// クラス定義
//******************************************************************************
class Fireworks
{
friend class FireworksState;

public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Fireworks( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~Fireworks( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	//==============================================================================
	int Set(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _speed,
		float _rot,
		float _rotSpeed);

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
	void Update( void );

	//==============================================================================
	// Brief  : 花火の爆発処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void burn(
		float _hitCheckOffset,
		float _hitPosLength);

	//==============================================================================
	// Brief  : ステートの設定
	// Return : void								: なし
	// Arg    : FireworksState** ppState				: ステートテーブル
	//==============================================================================
	static void SetState( FireworksState** ppState );

	//==============================================================================
	// アクセサ
	//==============================================================================
	D3DXVECTOR3 getSpeed(){return param.speed;}

	D3DXVECTOR3 getPosition(){return param.pos;}
	void addPosition(float _x, float _y, float _z){param.pos.x += _x;param.pos.y += _y;param.pos.z += _z;}
	void addPositionX(float _x){param.pos.x += _x;}
	void addPositionY(float _y){param.pos.y += _y;}
	void addPositionZ(float _z){param.pos.z += _z;}

	float getRotation(){return param.rot;}
	void addRotationSpeed(float _value){param.rot += _value;}

	float getRotationSpeed(){return param.rotSpeed;}

	bool IsEnable(){return param.enable;}
	void setEnable(bool _flag){param.enable = _flag;}
	bool IsBurnFlag(){return param.burnFlag;}

	ManagerPoint* getManagerPoint(){return param.managerPoint;};

	int getDeleteCount(){return param.deleteCount;}
	void deleteCountPP(){param.deleteCount++;}

	FIREWORKS_PARAM* getParam(){return &param;}
	void setInvViewMatrix(D3DXMATRIX _invViewMatrix){param.invViewMatrix = _invViewMatrix;};

protected:

	// ステート
	static FireworksState**	ppState_;
	int indexState;

	//	花火用パラメータ
	FIREWORKS_PARAM param;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void NormalUpdate( void );

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void BurnUpdate( void );

	//	更新関数格納用ポインタ
	void (Fireworks::*fpUpdate)(void);

private:
	void InitializeSelf( void );
	Fireworks( const Fireworks& );
	Fireworks operator=( const Fireworks& );
};

#endif	// MY_FIREWORKS_H
