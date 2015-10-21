//*****************************************************************************
//	�}�l�[�W���[ [CManager.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
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
//	�ÓI�ϐ���`
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
//	�R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}
//=============================================================================
//	�f�X�g���N�^
//
//	���� : ����
//	�Ԃ�l : ����
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
//	������
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
//	�X�V����
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
//	�`�揈��
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