//==============================================================================
//
// File   : ObjectWaterwheel.cpp
// Brief  : 水車オブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectWaterwheel.h"
#include "ObjectModelMaterial.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../system/SceneArgumentMain.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
static const float offsetPositionY = 20.0f;

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectWaterwheel::ObjectWaterwheel( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectWaterwheel::~ObjectWaterwheel( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
//==============================================================================
int ObjectWaterwheel::Initialize(
	D3DXVECTOR3 _pos,
	float _rotY,
	float _rotSpeed,
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
	rotSpeed = _rotSpeed;

	//	オブジェクトの生成開始
	Effect*		pEffect = nullptr;
	Effect*		pEffectReflect = nullptr;
	Model*		pModel = nullptr;

	//	水車固定用の台生成
	pEffect = pArgument->pEffect_->Get( _T( "ModelMaterial.fx" ) );
	pEffectReflect = pArgument->pEffect_->Get( _T( "ModelMaterialReflect.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "suisya_dai_005.x" ) );
	stand = new ObjectModelMaterial();
	stand->Initialize(0);
	stand->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect);
	stand->SetPosition(pos);
	stand->SetRotationY(_rotY);

	//	水車生成
	pEffect = pArgument->pEffect_->Get( _T( "ModelMaterial.fx" ) );
	pEffectReflect = pArgument->pEffect_->Get( _T( "ModelMaterialReflect.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "suisya_gear_005.x" ) );
	wheel = new ObjectModelMaterial();
	wheel->Initialize(0);
	wheel->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect);
	wheel->SetPosition(pos);
	wheel->AddPositionY(offsetPositionY);
	wheel->SetRotationY(_rotY);


	stand->SetScale(170.0f, 170.0f, 170.0f);
	wheel->SetScale(170.0f, 170.0f, 170.0f);


	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ObjectWaterwheel::Finalize( void )
{
	delete stand;
	delete wheel;

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
void ObjectWaterwheel::Update( void )
{
	wheel->AddRotationZ(rotSpeed);

	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectWaterwheel::InitializeSelf( void )
{
	// メンバ変数の初期化
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotSpeed = 0.0f;

	stand = nullptr;
	wheel = nullptr;
}
