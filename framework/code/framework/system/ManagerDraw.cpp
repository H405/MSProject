//==============================================================================
//
// File   : ManagerDraw.cpp
// Brief  : 描画実行クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/10 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerDraw.h"
#include "../develop/Debug.h"
#include "../develop/DebugProc.h"
#include "../graphic/Graphic.h"
#include "../render/RenderPass.h"
#include "../render/RenderTarget.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// テンプレート宣言
//******************************************************************************
template class ManagerDraw< class Graphic >;

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerDraw< TypeItem >::ManagerDraw( void ) : ManagerExector()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerDraw< TypeItem >::~ManagerDraw( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int maximumItem						: 最大要素数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : int countPass						: 描画パス数
// Arg    : RenderPass* pRenderPass				: 描画パス
//==============================================================================
template< class TypeItem >
int ManagerDraw< TypeItem >::Initialize( int maximumItem, IDirect3DDevice9* pDevice, int countPass, RenderPass* pRenderPass )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerExector::Initialize( maximumItem );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	pDevice_ = pDevice;
	countPass_ = countPass;
	pRenderPass_ = pRenderPass;

	// 最大レンダーターゲット数の取得
	D3DCAPS9	capacity;		// 性能
	pDevice->GetDeviceCaps( &capacity );
	maximumRenderTarget_ = capacity.NumSimultaneousRTs;

//	NAGASAKI変更
#ifdef SCREENSHOT_ON
	screenShot = new CScreenShot(pDevice);
#endif
//	NAGASAKI変更

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerDraw< TypeItem >::Finalize( void )
{
//	NAGASAKI変更
	delete screenShot;
//	NAGASAKI変更

	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerExector::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// クラス内部の初期化
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : int maximumItem						: 最大要素数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : int countPass						: 描画パス数
// Arg    : RenderPass* pRenderPass				: 描画パス
//==============================================================================
template< class TypeItem >
int ManagerDraw< TypeItem >::Reinitialize( int maximumItem, IDirect3DDevice9* pDevice, int countPass, RenderPass* pRenderPass )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( maximumItem, pDevice, countPass, pRenderPass );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ManagerDraw* pOut					: コピー先アドレス
//==============================================================================
template< class TypeItem >
int ManagerDraw< TypeItem >::Copy( ManagerDraw* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerExector::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 実行
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerDraw< TypeItem >::Execute( void )
{
	// 有効なときのみ処理
	if( !isEnable_ )
	{
		return 0;
	}

	// Direct3Dによる描画の開始
	IDirect3DSurface9*	pSurfaceRenderOrigin;		// 元の描画サーフェイス
	IDirect3DSurface9*	pSurfaceDepthOrigin;		// 元の深度サーフェイス
	if( SUCCEEDED( pDevice_->BeginScene() ) )
	{
		// 元の描画対象を記録
		pDevice_->GetRenderTarget( 0, &pSurfaceRenderOrigin );
		pDevice_->GetDepthStencilSurface( &pSurfaceDepthOrigin );

		// パスの描画
		for( int counterPass = 0; counterPass < countPass_; ++counterPass )
		{
			// レンダーターゲットの設定
			int			countRenderTarget;		// レンダーターゲット数
			DWORD		flagClear;				// クリアフラグ
			D3DCOLOR	clearTarget;			// レンダーターゲットのクリア値
			float		clearZBuffer;			// Zバッファのクリア値
			DWORD		clearStencil;			// ステンシルバッファのクリア値
			if( counterPass < countPass_ - 1 )
			{
				countRenderTarget = pRenderPass_[ counterPass ].GetCountRenderTarget();
				pRenderPass_[ counterPass ].Set();
				flagClear = pRenderPass_[ counterPass ].GetFlagClear();
				clearTarget = pRenderPass_[ counterPass ].GetClearTarget();
				clearZBuffer = pRenderPass_[ counterPass ].GetClearZBuffer();
				clearStencil = pRenderPass_[ counterPass ].GetClearStencil();
			}
			else
			{
				countRenderTarget = 1;
				pDevice_->SetRenderTarget( 0, pSurfaceRenderOrigin );
				pDevice_->SetDepthStencilSurface( pSurfaceDepthOrigin );
				flagClear = (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
				clearTarget = D3DCOLOR_RGBA( 0, 0, 0, 0 );
				clearZBuffer = 1.0f;
				clearStencil = 0;
			}
			for( int counterRenderTarget = countRenderTarget; counterRenderTarget < maximumRenderTarget_; ++counterRenderTarget )
			{
				pDevice_->SetRenderTarget( counterRenderTarget, nullptr );
			}

			// バッファのクリア
			pDevice_->Clear( 0, NULL, flagClear, clearTarget, clearZBuffer, clearStencil );

			// オブジェクトの描画
			int		indexItemCurrent;		// 現在の要素番号
			for( indexItemCurrent = indexTop_; indexItemCurrent >= 0; indexItemCurrent = pBufferItem_[ indexItemCurrent ].indexNext_ )
			{
				if( pBufferItem_[ indexItemCurrent ].needsUnregister_ || !pBufferItem_[ indexItemCurrent ].isEnable_ || !pBufferItem_[ indexItemCurrent ].pItem_->IsEnable() )
				{
					continue;
				}
				pBufferItem_[ indexItemCurrent ].pItem_->Draw( counterPass );
			}
		}

//	NAGASAKI変更
#ifdef SCREENSHOT_ON
		//	スクリーンショット作成
		if (screenShotFlag == true)
		{
			screenShot->Create();
			screenShotFlag = false;
		}
#endif
//	NAGASAKI変更

#ifdef _DEVELOP
		// デバッグ文字の描画
		DebugProc::Draw();
		DebugProc::ClearBuffer();
#endif

		// Direct3Dによる描画の終了
		pDevice_->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	pDevice_->Present( NULL, NULL, NULL, NULL );

	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerExector::Execute();
	if( result != 0 )
	{
		return result;
	}

	// 値の返却
	return 0;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
void ManagerDraw< TypeItem >::InitializeSelf( void )
{
	// メンバ変数の初期化
	pDevice_ = nullptr;
	countPass_ = 0;
	pRenderPass_ = nullptr;

//	NAGASAKI変更
	screenShotFlag = false;
	screenShot = nullptr;
//	NAGASAKI変更
}
