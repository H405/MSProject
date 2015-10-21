//*****************************************************************************
//	レンダラー [CRenderer.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "CRenderer.h"
#include "CDebug.h"

//*****************************************************************************
//	静的変数定義
//*****************************************************************************
#ifdef SCREENSHOT_ON
CScreenShot* CRenderer::screenShot;	//	スクリーンショット用オブジェクト
#endif

//=============================================================================
//	コンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	direct3D = NULL;
	device = NULL;
}
//=============================================================================
//	デストラクタ
//=============================================================================
CRenderer::~CRenderer()
{
	CObj::ReleaseAll();
	SAFE_DELETE(screenShot);
	SAFE_RELEASE(device);
	SAFE_RELEASE(direct3D);
}
//=============================================================================
//	初期化処理関数
//=============================================================================
void CRenderer::Init(HWND _windowHandle, BOOL _windowMode)
{
	D3DPRESENT_PARAMETERS presentParameter;
	D3DDISPLAYMODE displayMode;
	HRESULT result;

	//	Direct3Dオブジェクトの作成
	direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	
	if (direct3D == nullptr)
	{
		ASSERT("direct3Dがnullptrです")
	}

	//	現在のディスプレイモードを取得
	result = direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);
	if (result == E_FAIL)
	{
		ASSERT("ディスプレイモードの取得失敗")
	}

	//	デバイスのプレゼンテーションパラメータの設定
	//--------------------------------------------------------------------
		//	ワークをゼロクリア
		ZeroMemory(&presentParameter, sizeof(presentParameter));

		//	バックバッファの数をセット
		presentParameter.BackBufferCount = 1;
	
		//ゲーム画面サイズ
		presentParameter.BackBufferWidth = static_cast<int>SCREEN_WIDTH;
		presentParameter.BackBufferHeight = static_cast<int>SCREEN_HEIGHT;

		//	バックバッファフォーマットはディスプレイモードに合わせて使う
		presentParameter.BackBufferFormat = displayMode.Format;

		//	映像信号に同期してフリップする
		presentParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;

		//	ウィンドウモード
		presentParameter.Windowed = _windowMode;

		//	デプスバッファ（Ｚバッファ）とステンシルバッファを作成
		presentParameter.EnableAutoDepthStencil = TRUE;

		//	デプスバッファの利用方法
		//	D3DFMT_D16		デプスバッファのみを16bitとして扱う
		//	D3DFMT_D24S8	デプスバッファを24bit　ステンシルバッファを8bitとして扱う
		presentParameter.AutoDepthStencilFormat = D3DFMT_D24S8;
	//--------------------------------------------------------------------

	if (_windowMode)
	{
		//	ウィンドウモード
		presentParameter.FullScreen_RefreshRateInHz = 0;
		presentParameter.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{
		//	フルスクリーンモード
		presentParameter.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		presentParameter.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	//	デバイスオブジェクトの生成
	//	[デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	result =
		direct3D->CreateDevice(D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL,
								_windowHandle,
								D3DCREATE_HARDWARE_VERTEXPROCESSING,
								&presentParameter,
								&device);
	if (result == E_FAIL)
	{
		ASSERT("デバイスの作成失敗")
	}

	//	レンダーステートパラメータの設定
	//--------------------------------------------------------------------
	//	カリングモード
	//	D3DCULL_CCW		裏面をカリング(頂点のつなぎ順が	逆時計回り)
	//	D3DCULL_CW		表面をカリング(頂点のつなぎ順が	時計回り)
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//	Zバッファを使用するかしないか
	device->SetRenderState(D3DRS_ZENABLE, TRUE);

	//	αブレンドを行うか行わないか
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//	αソースカラーの指定
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//	αデスティネーションカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//	ライティングON/OFF
	device->SetRenderState(D3DRS_LIGHTING, TRUE);

	//	ワイヤーフレーム表示するかしないか
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//--------------------------------------------------------------------

	//	サンプラーステートパラメータの設定
	//--------------------------------------------------------------------
	//	テクスチャアドレッシング方法(U値)を設定
	//	繰り返しに設定
	device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	//	テクスチャアドレッシング方法(V値)を設定
	//	繰り返しに設定
	device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//	テクスチャ縮小フィルタモードを設定
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//	テクスチャ拡大フィルタモードを設定
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//--------------------------------------------------------------------

	//	テクスチャステージステートの設定
	//--------------------------------------------------------------------
	//	アルファブレンディング処理
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//	最初のアルファ引数
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	//	２番目のアルファ引数
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	//--------------------------------------------------------------------


#ifdef SCREENSHOT_ON
	screenShot = new CScreenShot(device, _windowMode, _windowHandle);
#endif

	/*obj2D = CObj2D::Create(device,
		D3DXVECTOR3(75.0f, 75.0f, 0.0f),
		3,
		D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	obj2D->setTexture("data/texture/bullete.png");

	obj2DLoop = CObj2DLoop::Create(device,
		0.0f,
		-0.1f,
		5,
		D3DXVECTOR3(150.0f, 150.0f, 0.0f),
		3);
	obj2DLoop->setTexture(CTextures::TEXTURE_TEST);

	obj2DKeyFrame = CObj2DKeyFrame::Create(device,
		8,
		5,
		D3DXVECTOR3(150.0f, 150.0f, 0.0f),
		3,
		D3DXVECTOR3(150.0f, 250.0f, 0.0f));
	obj2DKeyFrame->setTexture("data/texture/explosion.png");*/
}
//=============================================================================
//	更新処理
//=============================================================================
void CRenderer::Update()
{
	CObj::UpdateAll();
}
//=============================================================================
//	描画処理
//	カメラあり(3D)
//=============================================================================
void CRenderer::Draw(CCamera* pCamera)
{
	//	バックバッファ＆Ｚバッファのクリア
	device->Clear(0,
				NULL,
				(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
				D3DCOLOR_RGBA(0, 0, 0, 0),
				1.0f,
				0);

	//	Direct3Dによる描画の開始
	if (SUCCEEDED(device->BeginScene()))
	{
		CObj::DrawAll();

#ifdef SCREENSHOT_ON
		//	スクリーンショット作成
		if (screenShotFlag == true)
		{
			screenShot->Create();

			screenShotFlag = false;
		}
#endif

#ifdef _DEBUG
		CDebug::Draw();
#endif

		//	Direct3Dによる描画の終了
		device->EndScene();
	}

	//	バックバッファとフロントバッファの入れ替える
	device->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
//	描画処理
//	カメラ無し(2D)
//=============================================================================
void CRenderer::Draw()
{
	//	バックバッファ＆Ｚバッファのクリア
	device->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//	Direct3Dによる描画の開始
	if (SUCCEEDED(device->BeginScene()))
	{
		CObj::DrawAll();

#ifdef SCREENSHOT_ON
		//	スクリーンショット作成
		if (screenShotFlag == true)
		{
			screenShot->Create();

			screenShotFlag = false;
		}
#endif

#ifdef _DEBUG
		CDebug::Draw();
#endif

		//	Direct3Dによる描画の終了
		device->EndScene();
	}

	//	バックバッファとフロントバッファの入れ替える
	device->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
//	デバイスの取得関数
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return device;
}

//-----------------------------------EOF---------------------------------------