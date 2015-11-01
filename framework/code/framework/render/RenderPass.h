//==============================================================================
//
// File   : RenderPass.h
// Brief  : パスクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_RENDER_PASS_H
#define MY_RENDER_PASS_H

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
class RenderTarget;
class RenderPassParameter;

//******************************************************************************
// クラス定義
//******************************************************************************
class RenderPass
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	RenderPass( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~RenderPass( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : int countRenderTarget				: レンダーターゲットの数
	// Arg    : const RenderPassParameter* pParameter	: 描画対象パラメータ
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice, int countRenderTarget, const RenderPassParameter* pParameter = nullptr );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : int countRenderTarget				: レンダーターゲットの数
	// Arg    : const RenderPassParameter* pParameter	: 描画対象パラメータ
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice, int countRenderTarget, const RenderPassParameter* pParameter = nullptr );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : RenderPass* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( RenderPass* pOut ) const;

	//==============================================================================
	// Brief  : 描画対象に設定
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Set();

	//==============================================================================
	// アクセサ
	//==============================================================================
	int GetCountRenderTarget( void ) const;
	RenderTarget* GetRenderTarget( int index ) const;
	IDirect3DSurface9* GetSurfaceDepth( void ) const;
	unsigned int GetWidth( void ) const;
	unsigned int GetHeight( void ) const;
	void SetFlagClear( const DWORD& value );
	DWORD GetFlagClear( void ) const;
	void SetClearTarget( const D3DCOLOR& value );
	D3DCOLOR GetClearTarget( void ) const;
	void SetClearZBuffer( float value );
	float GetClearZBuffer( void ) const;
	void SetClearStencil( const DWORD& value );
	DWORD GetClearStencil( void ) const;

protected:

private:
	void InitializeSelf( void );
	RenderPass( const RenderPass& );
	RenderPass operator=( const RenderPass& );

	IDirect3DDevice9*	pDevice_;				// Direct3Dデバイス
	int					countRenderTarget_;		// レンダーターゲット数
	RenderTarget**		ppRenderTarget_;		// レンダーターゲット
	IDirect3DSurface9*	pSurfaceDepth_;			// 深度バッファ
	unsigned int		width_;					// 幅
	unsigned int		height_;				// 高さ
	DWORD				flagClear_;				// クリアフラグ
	D3DCOLOR			clearTarget_;			// レンダーターゲットのクリア値
	float				clearZBuffer_;			// Zバッファのクリア値
	DWORD				clearStencil_;			// ステンシルバッファのクリア値
};

#endif	// MY_RENDER_PASS_H
