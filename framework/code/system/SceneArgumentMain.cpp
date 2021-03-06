//==============================================================================
//
// File   : SceneArgumentMain.cpp
// Brief  : シーンの共通引数
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "SceneArgumentMain.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
SceneArgumentMain::SceneArgumentMain( void ) : SceneArgument()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
SceneArgumentMain::~SceneArgumentMain( void )
{
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneArgumentMain::InitializeSelf( void )
{
	// メンバ変数の初期化
	pWindow_ = nullptr;
	pDevice_ = nullptr;
	pFade_ = nullptr;
	pLight_ = nullptr;
	pCamera_ = nullptr;
	pEffectParameter_ = nullptr;
	pWiiController_ = nullptr;
	pKeyboard_ = nullptr;
	pMouse_ = nullptr;
	pPad_ = nullptr;
	pVirtualController_ = nullptr;
	pTexture_ = nullptr;
	pModel_ = nullptr;
	pMotion_ = nullptr;
	pEffect_ = nullptr;
	pSound_ = nullptr;
	pDraw_ = nullptr;
	pUpdate_ = nullptr;
	pTextureNormalWave_ = nullptr;
	pTextureReflect_ = nullptr;
	pTextureReflectNotLight_ = nullptr;
	pTextureReflectAdd_ = nullptr;
	pTexture3D_ = nullptr;
	pTextureDepth_ = nullptr;
	pTextureTest_ = nullptr;
}
