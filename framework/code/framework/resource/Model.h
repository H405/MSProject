//==============================================================================
//
// File   : Model.h
// Brief  : モデルクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_MODEL_H
#define MY_MODEL_H

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
class Material;
class Vertex;

//******************************************************************************
// クラス定義
//******************************************************************************
class Model
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Model( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	virtual ~Model( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : unsigned int elementVertex			: 頂点の要素
	// Arg    : unsigned int countMaterial			: マテリアル数
	// Arg    : unsigned int countTexture			: テクスチャ数
	//==============================================================================
	virtual int Initialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	virtual int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : unsigned int elementVertex			: 頂点の要素
	// Arg    : unsigned int countMaterial			: マテリアル数
	// Arg    : unsigned int countTexture			: テクスチャ数
	//==============================================================================
	virtual int Reinitialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : Model* pOut							: コピー先アドレス
	//==============================================================================
	virtual int Copy( Model* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : int indexMaterial					: 描画マテリアル番号
	//==============================================================================
	virtual void Draw( int indexMaterial );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetCountMaterial( unsigned int value );
	unsigned int GetCountMaterial( void ) const;
	void SetMaterial( int index, const Material& value );
	virtual void GetMaterial( int index, Material* pOut ) const;
	void SetCountTexture( unsigned int value );
	unsigned int GetCountTexture( void ) const;
	void SetTexture( int index, IDirect3DTexture9* pValue );
	virtual IDirect3DTexture9* GetTexture( int index ) const;
	virtual unsigned long GetCountBone( void ) const;

protected:
	IDirect3DDevice9*	pDevice_;			// Direct3Dデバイス
	Vertex*				pVertex_;			// 頂点情報
	unsigned int		countMaterial_;		// マテリアル数
	Material*			pMaterial_;			// マテリアル
	unsigned int		countTexture_;		// テクスチャ数
	IDirect3DTexture9**	ppTexture_;			// テクスチャ

private:
	virtual void InitializeSelf( void );
	Model( const Model& );
	Model operator=( const Model& );
};

#endif	// MY_MODEL_H
