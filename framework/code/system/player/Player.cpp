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
#include "../../Object/ObjectModelMaterial.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerModel.h"
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
	body = nullptr;
	arm = nullptr;
	D3DXMatrixIdentity(&invViewMatrix);
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

	//	オブジェクトの生成開始
	Effect*		pEffect = nullptr;
	Model*		pModel = nullptr;

	//	プレイヤー固定用の台生成
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "kuma.x" ) );
	body = new ObjectModelMaterial();
	body->Initialize(0);
	body->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	body->SetPosition(pos);
	body->AddPositionX(offsetPosX);
	body->AddPositionY(offsetPosY);
	//body->SetPosition(0.0f, 50.0f, 300.0f);

	//	プレイヤー生成
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "arm_r.x" ) );
	arm = new ObjectModelMaterial();
	arm->Initialize(0);
	arm->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	arm->SetPosition(pos);
	//arm->SetPosition(0.0f, 50.0f, 300.0f);

	body->SetScale(1.0f, 1.0f, 1.0f);
	arm->SetScale(1.0f, 1.0f, 1.0f);

	//	親オブジェクト登録
	arm->SetParent(body);


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
	delete arm;

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
	//	カメラの逆行列をかけて、常に一定の場所に出るようにする処理
	D3DXVECTOR4 setPos;

	D3DXVec3Transform(&setPos, &pos, &invViewMatrix);

	//	腕にセット
	arm->SetPosition(setPos.x, setPos.y, setPos.z);

	//	オフセット値を加味してもう一度
	D3DXVECTOR3 buffPos = pos;
	buffPos.x += offsetPosX;
	buffPos.y += offsetPosY;
	D3DXVec3Transform(&setPos, &buffPos, &invViewMatrix);

	//	身体にセット
	body->SetPosition(setPos.x, setPos.y, setPos.z);

	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
//	アクセサ
//==============================================================================
void Player::setRotationArm(float _x, float _y, float _z)
{
	arm->SetRotation(_x, _y, _z);
}