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
#include "../target/Target.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************
#define FIRE_MAX (150)	//	１つの花火から生成される火花の数(6の倍数にすること)
#define SMALL_FIREWORKS_MAX (5)
#define DELETECOUNT_MAX (100)
typedef int TIME;


//******************************************************************************
// クラス前方宣言
//******************************************************************************
class ManagerPoint;
class FireworksState;
class Fire;
class ManagerLight;
class LightPoint;
class LightDirection;
class Sound;
class SceneArgumentMain;
class Target;

//******************************************************************************
// 構造体定義
//******************************************************************************
typedef struct
{
	D3DXVECTOR3 startPos;
	D3DXVECTOR3 buffPos1;
	D3DXVECTOR3 buffPos2;
	D3DXVECTOR3 endPos;
	int count;


	//	位置情報
	D3DXVECTOR3 pos;
	D3DXVECTOR3 setPos;
	D3DXVECTOR3 posOld[SMALL_FIREWORKS_MAX];

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
	TIME disappear;

	//	生成用カウンタ
	TIME appear;

	//	位置情報をセットする時間
	TIME setPosOld;

	Fire* fire;
	Fire* smallFire;

	//	弾ける火花の総数
	int fireMax;

	//	分裂した花火の総数
	int smallFireMax;
	int setSmallFireIndex;

	D3DXMATRIX matrix;

	//	カメラの逆行列
	D3DXMATRIX invViewMatrix;

	//	光源
	LightPoint* lightPoint;

	//	音
	Sound* launchSound;
	Sound* burnSound;

	//	色情報
	COLOR_STATE colorState;
	D3DXCOLOR color;

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
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	//==============================================================================
	int Set(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		COLOR_STATE _colorState = COLOR_STATE_W);
	int Set(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		Target* _target);
	int SetSP(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		COLOR_STATE _colorState = COLOR_STATE_W);
	int SetW(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		Target* _target);

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
	int burn(
		float _hitCheckOffset,
		float _hitPosLength);

	//==============================================================================
	// Brief  : 花火の爆発処理(予備・前Ver)
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void burn2();

	//==============================================================================
	// Brief  : ステートの設定
	// Return : void								: なし
	// Arg    : FireworksState** ppState				: ステートテーブル
	//==============================================================================
	static void SetState( FireworksState** ppState );

	//==============================================================================
	// Brief  : 花火の音生成処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void setSound(Sound* _burnSound, Sound* _launchSound);

	//==============================================================================
	// アクセサ
	//==============================================================================
	D3DXVECTOR3 getSpeed(){return param.speed;}

	D3DXVECTOR3 getPosition(){return param.pos;}
	D3DXVECTOR3 getSetPosition(){return param.setPos;}
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

	int getDeleteCount(){return param.disappear;}
	void disappearPP(){param.disappear++;}

	FIREWORKS_PARAM* getParam(){return &param;}
	void setInvViewMatrix(D3DXMATRIX _invViewMatrix){param.invViewMatrix = _invViewMatrix;};

	void setManagerLight(ManagerLight* _managerLight);

	COLOR_STATE getColorState(){return param.colorState;}

protected:

	// ステート
	static FireworksState**	ppState_;
	int indexState;

	//	花火用パラメータ
	FIREWORKS_PARAM param;

	ManagerLight* managerLight;

	int burnSoundIndex;
	int launchSoundIndex;

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

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Burn2Update( void );

	//	更新関数格納用ポインタ
	void (Fireworks::*fpUpdate)(void);

private:
	void InitializeSelf( void );
	Fireworks( const Fireworks& );
	Fireworks operator=( const Fireworks& );
};

#endif	// MY_FIREWORKS_H
