//==============================================================================
//
// File   : Light.h
// Brief  : ライトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_LIGHT_H
#define MY_LIGHT_H

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

//******************************************************************************
// クラス定義
//******************************************************************************
class Light
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Light( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	virtual ~Light( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	virtual int Initialize( void );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	virtual int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	virtual int Reinitialize( void );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : Light* pOut							: コピー先アドレス
	//==============================================================================
	virtual int Copy( Light* pOut ) const;

	//==============================================================================
	// Brief  : 使用
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Use( void );

	//==============================================================================
	// Brief  : 開放
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Release( void );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void Set( const D3DXCOLOR& diffuse, const D3DXCOLOR& specular );
	void SetDiffuse( const D3DXCOLOR& value );
	void SetDiffuse( float r, float g, float b, float a );
	void SetDiffuse( float r, float g, float b );
	void SetDiffuseR( float r );
	void SetDiffuseG( float g );
	void SetDiffuseB( float b );
	void SetDiffuseA( float a );
	void SetDiffuseAlpha( float alpha );
	void GetDiffuse( D3DXCOLOR* pOut ) const;
	float GetDiffuseR( void ) const;
	float GetDiffuseG( void ) const;
	float GetDiffuseB( void ) const;
	float GetDiffuseA( void ) const;
	void SetSpecular( const D3DXCOLOR& value );
	void SetSpecular( float r, float g, float b, float a );
	void SetSpecular( float r, float g, float b );
	void SetSpecularR( float r );
	void SetSpecularG( float g );
	void SetSpecularB( float b );
	void SetSpecularA( float a );
	void SetSpecularAlpha( float alpha );
	void GetSpecular( D3DXCOLOR* pOut ) const;
	float GetSpecularR( void ) const;
	float GetSpecularG( void ) const;
	float GetSpecularB( void ) const;
	float GetSpecularA( void ) const;
	void SetCastsShadow( bool value );
	bool GetCastsShadow( void ) const;
	bool CastsShadow( void ) const;
	void SetIsEnable( bool value );
	bool GetIsEnable( void ) const;
	bool IsEnable( void ) const;
	bool GetIsUsed( void ) const;
	bool IsUsed( void ) const;

protected:
	D3DXCOLOR	diffuse_;			// ディフューズカラー
	D3DXCOLOR	specular_;			// スペキュラカラー
	bool		castsShadow_;		// 影を落とすか
	bool		isEnable_;			// 有効フラグ
	bool		isUsed_;			// 使用フラグ

private:
	virtual void InitializeSelf( void );
	Light( const Light& );
	Light operator=( const Light& );

};

#endif	// MY_LIGHT_H
