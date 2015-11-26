//==============================================================================
//
// File   : PointMain.h
// Brief  : ポイントスプライトの一点
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_POINT_MAIN_H
#define MY_POINT_MAIN_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class PointMainState;

//******************************************************************************
// クラス定義
//******************************************************************************
class PointMain
{
friend class PointMainState;

public:
	// ステート
	enum
	{
		STATE_NONE = 0,		// なし
		STATE_ADD,			// 加算
		STATE_MULTIPLY,		// 乗算
		STATE_MAX			// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	PointMain( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~PointMain( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Initialize( void );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Reinitialize( void );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : PointMain* pOut						: コピー先アドレス
	//==============================================================================
	int Copy( PointMain* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : 設定
	// Return : void								: なし
	// Arg    : int indexState						: ステート番号
	// Arg    : const D3DXVECTOR3& position			: 座標
	// Arg    : const D3DXCOLOR& color				: 色
	// Arg    : float size							: 大きさ
	//==============================================================================
	void Set( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size );

	//==============================================================================
	// Brief  : 設定
	// Return : void								: なし
	// Arg    : int timeExist						: 残存時間
	// Arg    : const D3DXVECTOR3& position			: 座標
	// Arg    : const D3DXCOLOR& color				: 色
	// Arg    : float size							: 大きさ
	// Arg    : const D3DXVECTOR3& differencePosition	: 座標の変化量
	// Arg    : const D3DXCOLOR& differenceColor	: 色の変化量
	// Arg    : float differenceSize				: 大きさの変化量
	// Arg    : int indexState						: ステート番号
	//==============================================================================
	void Set( int timeExist, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size,
		const D3DXVECTOR3& differencePosition, const D3DXCOLOR& differenceColor, float differenceSize, int indexState );

	//==============================================================================
	// アクセサ
	//==============================================================================
	int GetTime( void ) const;
	void SetTimeExist( int value );
	int GetTimeExist( void ) const;
	void SetPosition( const D3DXVECTOR3& value );
	void SetPosition( float x, float y, float z );
	void SetPositionX( float x );
	void SetPositionY( float y );
	void SetPositionZ( float z );
	void GetPosition( D3DXVECTOR3* pOut ) const;
	float GetPositionX( void ) const;
	float GetPositionY( void ) const;
	float GetPositionZ( void ) const;
	void AddPosition( const D3DXVECTOR3& value );
	void AddPosition( float x, float y, float z );
	void AddPositionX( float x );
	void AddPositionY( float y );
	void AddPositionZ( float z );
	void MultiplyPosition( const D3DXVECTOR3& value );
	void MultiplyPosition( float x, float y, float z );
	void MultiplyPositionX( float x );
	void MultiplyPositionY( float y );
	void MultiplyPositionZ( float z );
	void SetSize( float value );
	float GetSize( void ) const;
	void AddSize( float value );
	void MultiplySize( float value );
	void SetColor( const D3DXCOLOR& value );
	void SetColor( float r, float g, float b, float a );
	void SetColor( float r, float g, float b );
	void SetColorR( float r );
	void SetColorG( float g );
	void SetColorB( float b );
	void SetColorA( float a );
	void SetColorAlpha( float alpha );
	void GetColor( D3DXCOLOR* pOut ) const;
	float GetColorR( void ) const;
	float GetColorG( void ) const;
	float GetColorB( void ) const;
	float GetColorA( void ) const;
	void AddColor( const D3DXCOLOR& value );
	void AddColor( float r, float g, float b, float a );
	void AddColor( float r, float g, float b );
	void AddColorR( float r );
	void AddColorG( float g );
	void AddColorB( float b );
	void AddColorA( float a );
	void AddColorAlpha( float alpha );
	void MultiplyColor( const D3DXCOLOR& value );
	void MultiplyColor( float r, float g, float b, float a );
	void MultiplyColor( float r, float g, float b );
	void MultiplyColorR( float r );
	void MultiplyColorG( float g );
	void MultiplyColorB( float b );
	void MultiplyColorA( float a );
	void MultiplyColorAlpha( float alpha );
	void SetDifferencePosition( const D3DXVECTOR3& value );
	void SetDifferencePosition( float x, float y, float z );
	void SetDifferencePositionX( float x );
	void SetDifferencePositionY( float y );
	void SetDifferencePositionZ( float z );
	void GetDifferencePosition( D3DXVECTOR3* pOut ) const;
	float GetDifferencePositionX( void ) const;
	float GetDifferencePositionY( void ) const;
	float GetDifferencePositionZ( void ) const;
	void SetDifferenceSize( float value );
	float GetDifferenceSize( void ) const;
	void SetDifferenceColor( const D3DXCOLOR& value );
	void SetDifferenceColor( float r, float g, float b, float a );
	void SetDifferenceColor( float r, float g, float b );
	void SetDifferenceColorR( float r );
	void SetDifferenceColorG( float g );
	void SetDifferenceColorB( float b );
	void SetDifferenceColorA( float a );
	void SetDifferenceColorAlpha( float alpha );
	void GetDifferenceColor( D3DXCOLOR* pOut ) const;
	float GetDifferenceColorR( void ) const;
	float GetDifferenceColorG( void ) const;
	float GetDifferenceColorB( void ) const;
	float GetDifferenceColorA( void ) const;
	void SetIsEnable( bool value );
	bool GetIsEnable( void ) const;
	bool IsEnable( void ) const;

protected:

private:
	PointMain( const PointMain& );
	PointMain operator=( const PointMain& );

	void InitializeSelf( void );
	void SetState( int index );

	void UpdateNone( void );
	void UpdateAdd( void );
	void UpdateMultiply( void );

	void (PointMain::*pFunctionState)( void );		// ステート

	int			time_;						// 経過時間
	int			timeExist_;					// 残存時間
	D3DXVECTOR3	position_;					// 座標
	float		size_;						// 大きさ
	D3DXCOLOR	color_;						// 色
	D3DXVECTOR3	differencePosition_;		// 座標の変化量
	float		differenceSize_;			// 大きさの変化量
	D3DXCOLOR	differenceColor_;			// 色の変化量
	bool		isEnable_;					// 有効フラグ
};

#endif	// MY_POINT_MAIN_H
