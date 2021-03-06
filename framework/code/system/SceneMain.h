//==============================================================================
//
// File   : SceneMain.h
// Brief  : シーンクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_SCENE_MAIN_H
#define MY_SCENE_MAIN_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../framework/scene/Scene.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class SceneArgumentMain;

//******************************************************************************
// クラス定義
//******************************************************************************
class SceneMain : public Scene
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	SceneMain( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	virtual ~SceneMain( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : SceneArgumentMain* pArgument		: シーン引数
	//==============================================================================
	virtual int Initialize( SceneArgumentMain* pArgument );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	virtual int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : SceneArgumentMain* pArgument		: シーン引数
	//==============================================================================
	virtual int Reinitialize( SceneArgumentMain* pArgument );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : SceneMain* pOut						: コピー先アドレス
	//==============================================================================
	virtual int Copy( SceneMain* pOut ) const;

protected:
	SceneArgumentMain*	pArgument_;		// シーン引数

private:
	virtual void InitializeSelf( void );
	SceneMain( const SceneMain& );
	SceneMain operator=( const SceneMain& );

};

#endif	// MY_SCENE_MAIN_H
