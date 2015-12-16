//==============================================================================
//
// File   : Gage.cpp
// Brief  : シンクロゲージオブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "gage.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerTexture.h"
#include "../../object/Object2D.h"
#include "../../object/ObjectScore.h"
#include "../../framework/develop/DebugProc.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define DELETECOUNT_MAX (1000)
#define RANDAM(value) ((rand() % value) - (rand() % value))

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
static const int gageBarRedNum = 7;
static const int gageBarGreenNum = 16;
static const int gageBarBlueNum = GAGEBAR_MAX;

static const D3DXCOLOR gageColor[3] =
{
	D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f),
	D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f),
	D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f),
};

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Gage::Gage( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Gage::InitializeSelf( void )
{
	gageBar = nullptr;
	gageBase = nullptr;
	gageBack = nullptr;

	percent = 0.0f;
	percentFuture = 0.0f;
	barNum = 0;
	barNumOld = 0;
	gageBackCount = 0;
	gageBackAddSize = 1.0f;

	// メンバ変数の初期化
	fpUpdate = nullptr;
}
//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Gage::~Gage( void )
{
	// 終了処理
	Finalize();
}
//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int Gage::Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Effect* pEffectGeneral2,
	Texture* pGageBar,
	Texture* pGageBase,
	Texture* pGageBack,
	Texture* pGageScore)
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}


	//	100%の時用の背景
	gageBack = new Object2D();
	gageBack->Initialize(0);
	gageBack->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral2,
		pGageBack
		);

	//	ゲージベースオブジェクト生成
	gageBase = new Object2D;
	gageBase->Initialize(0);
	gageBase->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pGageBase
		);
	//gageBase->SetEnableGraphic(false);

	//	ゲージオブジェクト生成
	gageBar = new Object2D[GAGEBAR_MAX];

	float rotValue = (D3DX_PI * 2.0f) / (float)GAGEBAR_MAX;

	for(int count = 0;count < GAGEBAR_MAX;count++)
	{
		gageBar[count].Initialize(0);
		gageBar[count].CreateGraphic(
			0,
			pParameter,
			pEffectGeneral,
			pGageBar
			);
		gageBar[count].SetRotationZ(count * rotValue);
		//gageBar[count].SetEnableGraphic(false);
	}


	gageScore = new ObjectScore();
	gageScore->Initialize(0, 3);
	gageScore->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pGageScore);
	gageScore->SetSizeX(16.0f);
	gageScore->SetSizeY(16.0f);

	D3DXVECTOR3 buffScale;
	gageBase->GetScale(&buffScale);
	gageBack->SetScale(buffScale * 1.2f);

	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Gage::Finalize( void )
{
	delete gageScore;
	delete[] gageBar;
	delete gageBase;
	delete gageBack;


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
void Gage::Update( void )
{
	if(percentFuture > percent)
		percent += 1.0f;
	else if(percentFuture < percent)
		percent -= 1;

	barNum = (int)ceil((GAGEBAR_MAX * percent) / 100.0f);

	gageScore->SetScore((int)ceil(percent));
	gageScore->SetScoreFuture((int)ceil(percent));

	if(barNum != barNumOld)
	{
		//	一度すべてを白にして
		for(int count = 0;count < GAGEBAR_MAX;count++)
		{
			gageBar[count].SetColor(1.0f, 1.0f, 1.0f);
		}

		//	場所に応じて色をセット
		for(int count = 0;count < barNum;count++)
		{
			if(count <= gageBarRedNum)
				gageBar[count].SetColor(gageColor[0]);
			else if(count <= gageBarGreenNum)
				gageBar[count].SetColor(gageColor[1]);
			else if(count <= gageBarBlueNum)
				gageBar[count].SetColor(gageColor[2]);
		}
	}

	if(percent == 100.0f)
	{
		gageBackCount++;

		gageBack->AddScale( gageBackAddSize,  gageBackAddSize, 0.0f);

		if(gageBackCount == 10)
		{
			gageBackCount = 0;
			gageBackAddSize *= -1.0f;
		}
	}

	PrintDebug( _T( "\nbarNum = %d\n"), barNum );
	PrintDebug( _T( "\npercent = %f\n"), percent );

	barNumOld = barNum;
}

//==============================================================================
// Brief  : 位置セット処理
//==============================================================================
void Gage::setPosition(float _x, float _y, float _z)
{
	gageBack->SetPosition(_x, _y, _z);

	gageBase->SetPosition(_x, _y, _z);

	gageScore->SetPos(_x - 16.0f, _y, _z);

	for(int count = 0;count < GAGEBAR_MAX;count++)
	{
		gageBar[count].SetPosition(_x, _y, _z);
	}

	// 基本クラスの処理
	ObjectMovement::Update();
}