//==============================================================================
//
// File   : FireState.h
// Brief  : 火花のステート
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_FIRE_STATE_H
#define MY_FIRE_STATE_H

//******************************************************************************
// インクルード
//******************************************************************************

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Fire;

//******************************************************************************
// クラス定義
//******************************************************************************
class FireState
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	FireState( void ) {}

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	virtual ~FireState( void ) {}

	//==============================================================================
	// Brief  : 設定
	// Return : void								: なし
	// Arg    : Fire* pFire						: 対象
	//==============================================================================
	virtual void Update( Fire* _fireworks );

protected:

private:
};

//******************************************************************************
// クラス定義
//******************************************************************************
class FireStateRight : public FireState
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	FireStateRight( void ) {}

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~FireStateRight( void ) {}

	//==============================================================================
	// Brief  : 設定
	// Return : void								: なし
	// Arg    : Fire* pFire						: 対象
	//==============================================================================
	void Update( Fire* pFire );

protected:

private:
};

//******************************************************************************
// クラス定義
//******************************************************************************
class FireStateLeft : public FireState
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	FireStateLeft( void ) {}

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~FireStateLeft( void ) {}

	//==============================================================================
	// Brief  : 設定
	// Return : void								: なし
	// Arg    : Fire* pFire						: 対象
	//==============================================================================
	void Update( Fire* pFire );

protected:

private:
};

//******************************************************************************
// クラス定義
//******************************************************************************
class FireStateUp : public FireState
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	FireStateUp( void ) {}

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~FireStateUp( void ) {}

	//==============================================================================
	// Brief  : 設定
	// Return : void								: なし
	// Arg    : Fire* pFire						: 対象
	//==============================================================================
	void Update( Fire* pFire );

protected:

private:
};

//******************************************************************************
// クラス定義
//******************************************************************************
class FireStateDown : public FireState
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	FireStateDown( void ) {}

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~FireStateDown( void ) {}

	//==============================================================================
	// Brief  : 設定
	// Return : void								: なし
	// Arg    : Fire* pFire						: 対象
	//==============================================================================
	void Update( Fire* pFire );

protected:

private:
};

#endif	// MY_FIRE_STATE_H
