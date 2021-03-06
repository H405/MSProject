//==============================================================================
//
// File   : Manager.h
// Brief  : プログラム管理クラスの基本クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_MANAGER_H
#define MY_MANAGER_H

//******************************************************************************
// インクルード
//******************************************************************************
#include <windows.h>

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Window;

//******************************************************************************
// クラス定義
//******************************************************************************
class Manager
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Manager( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	virtual ~Manager( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : HINSTANCE instanceHandle			: インスタンスハンドル
	// Arg    : int typeShow						: 表示の種類
	//==============================================================================
	virtual int Initialize( HINSTANCE instanceHandle, int typeShow );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	virtual int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : HINSTANCE instanceHandle			: インスタンスハンドル
	// Arg    : int typeShow						: 表示の種類
	//==============================================================================
	virtual int Reinitialize( HINSTANCE instanceHandle, int typeShow );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : Manager* pOut						: コピー先アドレス
	//==============================================================================
	virtual int Copy( Manager* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	virtual void Update( void );

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	virtual void Draw( void );

	//==============================================================================
	// アクセサ
	//==============================================================================
	bool GetIsEnd( void ) const;
	bool IsEnd( void ) const;
	void SetWindow( Window* pValue );
	Window* GetWindow( void ) const;
#ifdef _DEVELOP
	void SetFpsUpdate( unsigned long value );
	void SetFpsDraw( unsigned long value );
#endif

protected:
	bool	isEnd_;			// 終了フラグ
	Window*	pWindow_;		// ウィンドウ

#ifdef _DEVELOP
	int		fpsUpdate_;		// 更新FPS
	int		fpsDraw_;		// 描画FPS
#endif

private:
	virtual void InitializeSelf( void );
	Manager( const Manager& );
	Manager operator=( const Manager& );
};

#endif	// MY_MANAGER_H
