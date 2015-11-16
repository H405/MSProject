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
class CWiiController;
class Effect;
class EffectParameter;
class Fade;
class Graphic;
class InputKeyboard;
class InputMouse;
class InputPad;
class ManagerLight;
class Model;
class Motion;
class Object;
class Sound;
class Texture;
class VirtualController;
class Window;

template < class Graphic > class ManagerDraw;
template < class Effect > class ManagerEffect;
template < class Model > class ManagerModel;
template < class Motion > class ManagerMotion;
template < class Sound > class ManagerSound;
template < class Texture > class ManagerTexture;
template < class Object > class ManagerUpdate;

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

	Window*						pWindow_;				// ウィンドウ
	IDirect3DDevice9*			pDevice_;				// Direct3Dデバイス
	Fade*						pFade_;					// フェード管理クラス
	ManagerLight*				pLight_;				// ライト管理クラス
	EffectParameter*			pEffectParameter_;		// エフェクトパラメータ
	CWiiController*				pWiiController_;		// wiiリモコン入力クラス
	InputKeyboard*				pKeyboard_;				// キーボード入力クラス
	InputMouse*					pMouse_;				// マウス入力クラス
	InputPad*					pPad_;					// ゲームパッド入力クラス
	VirtualController*			pVirtualController_;	// 仮想コントローラ管理クラス
	ManagerTexture< Texture >*	pTexture_;				// テクスチャ管理クラス
	ManagerModel< Model >*		pModel_;				// モデル管理クラス
	ManagerMotion< Motion >*	pMotion_;				// モーション管理クラス
	ManagerEffect< Effect >*	pEffect_;				// エフェクト管理クラス
	ManagerSound< Sound >*		pSound_;				// サウンド管理クラス

	ManagerDraw< Graphic >*		pDraw_;					// 描画管理クラス
	ManagerUpdate< Object >*	pUpdate_;				// 更新管理クラス

protected:

private:
	void InitializeSelf( void );

};

#endif	// MY_SCENE_ARGUMENT_MAIN_H
