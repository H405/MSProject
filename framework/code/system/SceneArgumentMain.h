//==============================================================================
//
// File   : SceneArgumentMain.h
// Brief  : シーンの共通引数
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_SCENE_ARGUMENT_MAIN_H
#define MY_SCENE_ARGUMENT_MAIN_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"
#include "../framework/scene/SceneArgument.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Effect;
class EffectParameter;
class Fade;
class InputKeyboard;
class InputMouse;
class InputPad;
class Model;
class ObjectScreen;
class Texture;
template < class Effect > class ManagerEffect;
template < class Model > class ManagerModel;
template < class Texture > class ManagerTexture;

//******************************************************************************
// クラス定義
//******************************************************************************
class SceneArgumentMain : public SceneArgument
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	SceneArgumentMain( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~SceneArgumentMain( void );

	IDirect3DDevice9*			pDevice_;				// Direct3Dデバイス
	Fade*						pFade_;					// フェード管理クラス
	EffectParameter*			pEffectParameter_;		// エフェクトパラメータ
	ObjectScreen*				pObjectScreen_;			// 画面オブジェクト
	InputKeyboard*				pKeyboard_;				// キーボード入力クラス
	InputMouse*					pMouse_;				// マウス入力クラス
	InputPad*					pPad_;					// ゲームパッド入力クラス
	ManagerTexture< Texture >*	pTexture_;				// テクスチャ管理クラス
	ManagerModel< Model >*		pModel_;				// モデル管理クラス
	ManagerEffect< Effect >*	pEffect_;				// エフェクト管理クラス

protected:

private:
	void InitializeSelf( void );

};

#endif	// MY_SCENE_ARGUMENT_MAIN_H
