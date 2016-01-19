//==============================================================================
//
// File   : Player.cpp
// Brief  : プレイヤーオブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Player.h"
#include "../../Object/ObjectSkinMesh.h"
#include "../../framework/develop/DebugProc.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerModel.h"
#include "../../framework/resource/ManagerMotion.h"
#include "../../system/SceneArgumentMain.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
static const float offsetPosX = -10.0f;
static const float offsetPosY = -20.0f;

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Player::Player( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Player::InitializeSelf( void )
{
	// メンバ変数の初期化
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	speed = 0.0f;
	body = nullptr;
//	arm_l = nullptr;
	D3DXMatrixIdentity(&invViewMatrix);
	isLimited_ = true;
	pos2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Player::~Player( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
//==============================================================================
int Player::Initialize(
	D3DXVECTOR3 _pos,
	SceneArgumentMain* pArgument)
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}


	pos = _pos;
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	オブジェクトの生成開始
	Effect*		pEffect = nullptr;
	Effect*		pEffectReflect = nullptr;
	Effect*		pEffectShadow = nullptr;
	Effect*		pEffectParaboloid = nullptr;
	Model*		pModel = nullptr;
	Motion*		pMotion = nullptr;

	//	プレイヤー固定用の台生成
	pEffect = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pEffectReflect = pArgument->pEffect_->Get( _T( "SkinMeshReflect.fx" ) );
	pEffectShadow = pArgument->pEffect_->Get( _T( "SkinMeshShadow.fx" ) );
	pEffectParaboloid = pArgument->pEffect_->Get( _T( "SkinMeshParaboloid.fx" ) );


	pModel = pArgument->pModel_->Get( _T( "back_dancer.model" ) );
	pMotion = pArgument->pMotion_->Get( _T( "back_dancer.motion" ) );
	body = new ObjectSkinMesh();
	body->Initialize(0, 1);
	body->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect, pEffectShadow, pEffectParaboloid);
	body->SetTableMotion(0, pMotion);
	body->SetPosition(pos);
#if 0
	pModel = pArgument->pModel_->Get( _T( "player_hand_l.model" ) );
	arm_l = new ObjectSkinMesh();
	arm_l->Initialize(0, 0);
	arm_l->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect, pEffectShadow, pEffectParaboloid);

	pModel = pArgument->pModel_->Get( _T( "player_hand_l.model" ) );
	arm_r = new ObjectSkinMesh();
	arm_r->Initialize(0, 0);
	arm_r->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect, pEffectShadow, pEffectParaboloid);
	arm_r->AddPosition(0.0f, 0.0f, 0.0f);
	arm_r->SetRotationY(D3DX_PI);

	pModel = pArgument->pModel_->Get( _T( "player_foot_l.model" ) );
	leg_l = new ObjectSkinMesh();
	leg_l->Initialize(0, 0);
	leg_l->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect, pEffectShadow, pEffectParaboloid);

	pModel = pArgument->pModel_->Get( _T( "player_foot_l.model" ) );
	leg_r = new ObjectSkinMesh();
	leg_r->Initialize(0, 0);
	leg_r->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect, pEffectShadow, pEffectParaboloid);
	leg_r->AddPosition(-15.0f, 0.0f, 0.0f);

	body->SetScale(0.5f, 0.5f, 0.5f);
	arm_l->SetScale(1.0f, 1.0f, 1.0f);
	arm_r->SetScale(1.0f, 1.0f, 1.0f);
	leg_l->SetScale(1.0f, 1.0f, 1.0f);
	leg_r->SetScale(1.0f, 1.0f, 1.0f);
#else
	body->SetScale(0.5f, 0.5f, 0.5f);
#endif
#if 0
	//	親オブジェクト登録
	arm_l->SetParent(body);
	arm_r->SetParent(body);
	leg_l->SetParent(body);
	leg_r->SetParent(body);
#endif

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Player::Finalize( void )
{
	delete body;
//	delete arm_l;
//	delete arm_r;
//	delete leg_l;
//	delete leg_r;

	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Player::Update( void )
{
	pos.x += speed;
	speed *= 0.9f;

	if( isLimited_ )
	{
		if(pos.x <= -250.0f)
			pos.x = -250.0f;
		else if(pos.x >= 250.0f)
			pos.x = 250.0f;
	}

	//	オフセット値を加味してもう一度
	D3DXVECTOR4 buffPos;
	if( isLimited_ )
	{
		D3DXVec3Transform(&buffPos, &pos, &invViewMatrix);
	}
	else
	{
		D3DXVec3Transform(&buffPos, &pos2, &invViewMatrix);
	}

	//	身体にセット
	body->SetPosition(buffPos.x, buffPos.y, buffPos.z);
	body->SetRotation(0.0f, atan2f(-cameraVec.x, -cameraVec.z), 0.0f);
	//body->AddRotationX(0.01f);
	//body->AddRotationY(0.01f);
	//body->AddRotationZ(0.01f);

	// 基本クラスの処理
	ObjectMovement::Update();

	// テスト
	D3DXVECTOR3	positionBody;
	body->GetPosition( &positionBody );
	PrintDebug( _T( "PLAYER : %9.3f, %9.3f, %9.3f\n" ), positionBody.x, positionBody.y, positionBody.z );
}

//==============================================================================
//	アクセサ
//==============================================================================
void Player::setRotationArm(float _x, float _y, float _z)
{
	rot.x = _x;
	rot.y = _y;
	rot.z = _z;
}
void Player::addRotationArm(float _x, float _y, float _z)
{
	rot.x += _x;
	rot.y += _y;
	rot.z += _z;
}
void Player::addPositionArm(float _x, float _y, float _z)
{
//	arm_l->AddPosition(_x, _y, _z);
}

//==============================================================================
// Brief  : 描画クラスの有効設定
// Return : void								: なし
// Arg    : bool value							: 設定する値
//==============================================================================
void Player::SetEnableGraphic( bool value )
{
	body->SetEnableGraphic( value );
}

//==============================================================================
// Brief  : モーションの有効設定
// Return : void								: なし
// Arg    : bool value							: 設定する値
//==============================================================================
void Player::SetEnableMotion( bool value )
{
	// 有効フラグの設定
	body->SetEnableMotion( value );
}
