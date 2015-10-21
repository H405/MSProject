//*****************************************************************************
//	マネージャー [CManager.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "wiiRemote/CWiiController.h"

#include "CManager.h"
#include "CRenderer.h"
#include "CDebug.h"
#include "textures.h"
#include "CSceneManager.h"
#include "CKeyboard.h"
#include "movie.h"

//*****************************************************************************
//	静的変数定義
//*****************************************************************************
CRenderer* CManager::renderer;
CSceneManager* CManager::sceneManager;
CKeyboard* CManager::keyboard;
CMovie* CManager::movie;
CWiiController* CManager::wiiController;

#ifdef _DEBUG
	CDebug* CManager::debug;
#endif

//=============================================================================
//	コンストラクタ
//=============================================================================
CManager::CManager()
{
}
//=============================================================================
//	デストラクタ
//
//	引数 : 無し
//	返り値 : 無し
//=============================================================================
CManager::~CManager()
{
	SAFE_DELETE(sceneManager);

#ifdef _DEBUG
	SAFE_DELETE(debug);
#endif

	SAFE_DELETE(movie);

	CTextures::Uninit();

	SAFE_DELETE(wiiController);

	SAFE_DELETE(keyboard);

	SAFE_DELETE(renderer);
}
//=============================================================================
//	初期化
//=============================================================================
void CManager::Init(HINSTANCE _instanceHandle, HWND _windowHandle, bool _windowMode)
{
	renderer = new CRenderer();
	renderer->Init(_windowHandle, _windowMode);

	keyboard = new CKeyboard();
	if (keyboard->Init(_instanceHandle, _windowHandle) == false)
		keyboard = nullptr;

	wiiController = new CWiiController;

	CRadianTable::Init();

	CTextures::Init(renderer->GetDevice());

	//movie = new CMovie();
	//movie->Init();

#ifdef _DEBUG
	debug = new CDebug();
	debug->Init(renderer->GetDevice());
	CDebug::setDisp(true);
#endif

	sceneManager = new CSceneManager();
	sceneManager->Init(CSceneManager::SCENE_GAME,
		renderer,
		nullptr,
		nullptr,
		keyboard);
	CSceneManager::setMyAdd(sceneManager);
}
//=============================================================================
//	更新処理
//=============================================================================
void CManager::Update()
{
#ifdef _DEBUG
	CDebug::StartDebugTimer();
#endif

	sceneManager->Update();

#ifdef _DEBUG
	CDebug::EndDebugTimer("Update =");
#endif
}
//=============================================================================
//	描画処理
//=============================================================================
void CManager::Draw()
{
#ifdef _DEBUG
	CDebug::StartDebugTimer();
#endif

	sceneManager->Draw();

#ifdef _DEBUG
	CDebug::EndDebugTimer("Draw =");
#endif
}

//-----------------------------------EOF---------------------------------------