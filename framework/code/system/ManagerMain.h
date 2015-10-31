//==============================================================================
//
// File   : ManagerMain.h
// Brief  : メインプログラム管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_MANAGER_MAIN_H
#define MY_MANAGER_MAIN_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../framework/system/Manager.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class DirectDevice;
class DirectInput;
class Effect;
class EffectParameter;
class Fade;
class Graphic;
class CWiiController;
class InputKeyboard;
class InputMouse;
class InputPad;
class VirtualController;
class ManagerSceneMain;
class Model;
class Motion;
class Object;
class ObjectScreen;
class Polygon2D;
class Polygon3D;
class RenderPass;
class SceneArgumentMain;
class Sound;
class Texture;
class XAudio;
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
class ManagerMain : public Manager
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ManagerMain( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ManagerMain( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : HINSTANCE instanceHandle			: インスタンスハンドル
	// Arg    : int typeShow						: 表示の種類
	//==============================================================================
	int Initialize( HINSTANCE instanceHandle, int typeShow );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : HINSTANCE instanceHandle			: インスタンスハンドル
	// Arg    : int typeShow						: 表示の種類
	//==============================================================================
	int Reinitialize( HINSTANCE instanceHandle, int typeShow );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ManagerMain* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( ManagerMain* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Draw( void );

	//==============================================================================
	// アクセサ
	//==============================================================================

protected:

private:
	void InitializeSelf( void );
	ManagerMain( const ManagerMain& );
	ManagerMain operator=( const ManagerMain& );

	ManagerSceneMain*			pScene_;				// シーン管理クラス
	SceneArgumentMain*			pArgument_;				// シーン引数
	DirectDevice*				pDevice_;				// Direct3Dデバイス
	XAudio*						pXAudio_;				// XAudio2インターフェース
	Fade*						pFade_;					// フェード
	EffectParameter*			pEffectParameter_;		// エフェクトパラメータ
	ObjectScreen*				pObjectScreen_;			// 画面オブジェクト
	ManagerDraw< Graphic >*		pDraw_;					// 描画管理クラス
	ManagerUpdate< Object >*	pUpdate_;				// 更新管理クラス
	RenderPass*					pRenderPass_;			// パス情報
	DirectInput*				pDirectInput_;			// DirectInputオブジェクト
	CWiiController*				pWiiController_;		// wiiリモコン入力クラス
	InputKeyboard*				pKeyboard_;				// キーボード入力クラス
	InputMouse*					pMouse_;				// マウス入力クラス
	InputPad*					pPad_;					// ゲームパッド入力クラス
	VirtualController*			pVirtualController_;	// 仮想コントローラ管理クラス
	ManagerTexture< Texture >*	pTexture_;				// テクスチャ管理クラス
	ManagerModel< Model >*		pModel_;				// モデル管理クラス
	ManagerMotion< Motion >*		pMotion_;			// モーション管理クラス
	ManagerEffect< Effect >*	pEffect_;				// エフェクト管理クラス
	ManagerSound< Sound >*		pSound_;				// サウンド管理クラス
	Polygon2D*					pPolygon2D_;			// 2Dポリゴン
	Polygon3D*					pPolygon3D_;			// 3Dポリゴン
};

#endif	// MY_MANAGER_MAIN_H
