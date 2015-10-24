//==============================================================================
//
// File   : ManagerModel.h
// Brief  : モデル管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_MANAGER_MODEL_H
#define MY_MANAGER_MODEL_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"
#include "ManagerResource.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Model;
class Texture;
template < class Texture > class ManagerTexture;

//******************************************************************************
// クラス定義
//******************************************************************************
template< class TypeItem >
class ManagerModel : public ManagerResource< TypeItem >
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ManagerModel( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ManagerModel( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : TCHAR* pDirectory					: 基準ディレクトリ
	// Arg    : TCHAR* pDirectoryTexture			: テクスチャ基準ディレクトリ
	// Arg    : int maximumItem						: 最大要素数
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : ManagerTexture< Texture >* pTexture	: テクスチャ管理クラス
	//==============================================================================
	int Initialize( TCHAR* pDirectory, TCHAR* pDirectoryTexture, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : TCHAR* pDirectory					: 基準ディレクトリ
	// Arg    : TCHAR* pDirectoryTexture			: テクスチャ基準ディレクトリ
	// Arg    : int maximumItem						: 最大要素数
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : ManagerTexture< Texture >* pTexture	: テクスチャ管理クラス
	//==============================================================================
	int Reinitialize( TCHAR* pDirectory, TCHAR* pDirectoryTexture, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ManagerModel* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( ManagerModel* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	ManagerModel( const ManagerModel& );
	ManagerModel operator=( const ManagerModel& );

	int LoadResource( TCHAR* pPath, int index );
	void ReleaseResource( int index );

	IDirect3DDevice9*			pDevice_;				// Direct3Dデバイス
	ManagerTexture< Texture >*	pTexture_;				// テクスチャ管理クラス
	TCHAR*						pDirectoryTexture_;		// テクスチャ基準ディレクトリ
};

#endif	// MY_MANAGER_MODEL_H
