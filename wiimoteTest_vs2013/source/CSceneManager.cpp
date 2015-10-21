//*****************************************************************************
//	 [ CSceneManager.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "CSceneManager.h"
#include "CRenderer.h"
#include "CObj.h"
#include "CSceneObject.h"

#include "splash.h"
#include "title.h"
#include "stageSelect.h"
#include "game.h"
#include "result.h"

#include "CFadeIn.h"
#include "CFadeOut.h"
#include "objects.h"

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
CSceneManager* CSceneManager::myAdd;

//=============================================================================
//	デストラクタ
//=============================================================================
CSceneManager::~CSceneManager()
{
	Uninit();
}
//=============================================================================
//	初期化処理
//=============================================================================
void CSceneManager::Init(SCENE_MODE _sceneMode,
	CRenderer* _renderer,
	CSound* _sound,
	CJoypad* _joypad,
	CKeyboard* _keyboard)
{
	//	各オブジェクトのセット
	renderer = _renderer;
	device = renderer->GetDevice();
	sound = _sound;
	keyboard = _keyboard;
	joypad = _joypad;
	threadHandle = nullptr;
	threadFlag = false;
	threadEndFlag = false;

	//	開始時点のモードをセット
	curScene = _sceneMode;
	prevScene = _sceneMode;
	nextScene = _sceneMode;

	//	更新関数セット
	fpUpdate = &CSceneManager::NormalUpdate;

	//	シーン情報をセット
	SetScene();
}
//=============================================================================
//	終了処理
//=============================================================================
void CSceneManager::Uninit()
{
	SAFE_DELETE(scene);
}
//=============================================================================
//	更新処理
//=============================================================================
void CSceneManager::Update()
{
	//	設定された更新関数へ
	(this->*fpUpdate)();
}
//=============================================================================
//	通常更新処理
//=============================================================================
void CSceneManager::NormalUpdate()
{
	scene->Update();
}
//=============================================================================
//	フェード時更新処理
//=============================================================================
void CSceneManager::FadeUpdate()
{
	CObj::UpdateAll(PRIORIRY_FADE);

	//	シーン切り替えフラグがたったら
	if (changeFlag == true)
	{
		//	シーン変化フラグをOFFに
		changeFlag = false;

		//	フェードインなら
		if (fadeMode == FADE_IN)
		{
			//	シーン切り替え
			ChangeScene();
		}
		//	フェードアウトなら
		else
		{
			//	更新関数セット
			fpUpdate = &CSceneManager::NormalUpdate;
			fadeMode = FADE_NONE;
		}
	}
}
//=============================================================================
//	描画処理
//=============================================================================
void CSceneManager::Draw()
{
	scene->Draw();
}
//=============================================================================
//	シーン切り替え前フェードイン処理
//=============================================================================
void CSceneManager::SetFadeIn(SCENE_MODE _nextScene)
{
	//	フェードイン生成
	CFadeIn::Create(device, PRIORIRY_FADE);

	fadeMode = FADE_IN;

	//	更新関数セット
	fpUpdate = &CSceneManager::FadeUpdate;

	//	次のシーンを保存
	nextScene = _nextScene;
}
//=============================================================================
//	シーン切り替え処理
//=============================================================================
void CSceneManager::ChangeScene()
{
	//	現在のシーンの終了
	SAFE_DELETE(scene);

	//	CSceneの中身を全て削除
	CObj::ReleaseAll();

	//	シーン情報を保存
	prevScene = curScene;
	curScene = nextScene;

	//	threadFlagが立っていた場合
	//	メインスレッドでフェード中のオブジェクト更新・描画を行う
	//	サブスレッドでscene情報の読み込み
	if (threadFlag == true)
	{
		threadFlag = false;

		//	マルチタスクでナウローディング
		unsigned* threadID = nullptr;
		threadHandle = (HANDLE)_beginthreadex(NULL, 0, CSceneManager::fpMulti_Fade, NULL, NULL, threadID);

		//	ナウローディング処理
		nowLoading();
	}
	else
	{
		SetScene();
	}

	threadEndFlag = false;
}
//=============================================================================
//	ナウローディング処理（マルチタスク）
//=============================================================================
void CSceneManager::nowLoading()
{
	DWORD execLastTime = 0;
	DWORD currentTime = 0;
	int countFPS = 0;

	execLastTime = timeGetTime();
	currentTime = 0;




	//	ナウローディング用のオブジェクトを生成
	CObj2D* bg = CObj2D::Create(device,
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
		PRIORIRY_FADE);

	CObj2D* obj2D1 = CObj2D::Create(device,
		D3DXVECTOR3(150.0f, 150.0f, 0.0f),
		PRIORIRY_FADE);
	obj2D1->setTexture(CTextures::TEXTURE_TEST);






	//	ナウローディング処理
	for (;;)
	{
		//	読み込み終了後、ループを抜けて
		if (threadEndFlag == true)
		{
			break;
		}

		//	fps30で更新と描画
		currentTime = timeGetTime();
		if ((currentTime - execLastTime) >= (1000 / 30))
		{
			execLastTime = currentTime;


			//	読み込み中も動かす
			obj2D1->addRot(D3DXVECTOR3(0.0f, 0.0f, 1.0f));


			CObj::UpdateAll();

			renderer->Draw();
		}
	}

	obj2D1->Release();
	bg->Release();
}
//=============================================================================
//	更新処理（マルチタスク）
//=============================================================================
unsigned __stdcall CSceneManager::fpMulti_Fade(void *p)
{
	//	次のシーンを生成
	myAdd->SetScene();

	//	シーン情報の読み込み終了後、フラグを建てる
	myAdd->setThreadEndFlag(true);

	//	マルチタスク終了
	_endthreadex(0);

	return NULL;
}
//=============================================================================
//	シーンセット処理
//=============================================================================
void CSceneManager::SetScene()
{
	switch (curScene)
	{
	case SCENE_SPLASH:

		//	ロゴシーンをセット
		scene = new CSceneSplash();

		break;

	case SCENE_TITLE:

		//	タイトルシーンをセット
		scene = new CSceneTitle();

		break;

	case SCENE_STAGE_SELECT:

		//	ステージセレクトシーンをセット
		scene = new CSceneStageSelect();

		break;


	case SCENE_GAME:

		//	ステージセレクトシーンをセット
		scene = new CSceneGame();

		break;

	case SCENE_RESULT:

		//リザルトシーンをセット
		scene = new CSceneResult();

		break;
	}

	//	シーンの初期化
	scene->Init(renderer, nullptr, nullptr, keyboard);

	//	フェードアウト開始
	CFadeOut::Create(device, PRIORIRY_FADE);
	fadeMode = FADE_OUT;

	//	更新関数セット
	fpUpdate = &CSceneManager::FadeUpdate;
}

//-----------------------------------EOF---------------------------------------