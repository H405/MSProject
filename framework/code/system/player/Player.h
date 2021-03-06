//==============================================================================
//
// File   : Player.h
// Brief  : プレイヤーオブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_PLAYER_H_
#define MY_PLAYER_H_

//******************************************************************************
// インクルード
//******************************************************************************
#include "../../framework/object/ObjectMovement.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class ObjectSkinMesh;
class SceneArgumentMain;

//******************************************************************************
// クラス定義
//******************************************************************************
class Player : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Player( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~Player( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	//==============================================================================
	int Initialize(
		D3DXVECTOR3 _pos,
		SceneArgumentMain* pArgument);

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
	// アクセサ
	//==============================================================================
	D3DXVECTOR3 getPosition(){return pos;}
	D3DXVECTOR3 getWorldPosition(){return worldPos;}
	void setPosition(D3DXVECTOR3 _pos){pos = _pos;}
	void AddPositionX(float _value){pos.x += _value;};
	void setRotationArm(float _x, float _y, float _z);
	void addRotationArm(float _x, float _y, float _z);
	void addPositionArm(float _x, float _y, float _z);

	void setInvViewMatrix(D3DXMATRIX _invViewMatrix){invViewMatrix = _invViewMatrix;};
	void setCameraVec(D3DXVECTOR3 _cameraVec){cameraVec = _cameraVec;}
	void setSpeed(float _value){speed = _value;}
	void addSpeed(float _value){speed += _value;}

	void SetEnableGraphic( bool value );
	void SetIsLimited( bool value )			{ isLimited_ = value; }
	void SetPos2( const D3DXVECTOR3& pos )	{ pos2 = pos; }
	void SetEnableMotion( bool value );

protected:

	//	位置情報
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	D3DXVECTOR3 worldPos;

	//	移動スピード
	float speed;

	//	カメラの逆行列
	D3DXMATRIX invViewMatrix;
	D3DXVECTOR3 cameraVec;

	ObjectSkinMesh* body;
//	ObjectSkinMesh* arm_l;
//	ObjectSkinMesh* arm_r;
//	ObjectSkinMesh* leg_l;
//	ObjectSkinMesh* leg_r;

	bool		isLimited_;
	D3DXVECTOR3	pos2;

private:
	void InitializeSelf( void );
	Player( const Player& );
	Player operator=( const Player& );
};

#endif
