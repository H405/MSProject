//*****************************************************************************
//	 [ CSceneManager.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
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
//	�C���N���[�h��`
//*****************************************************************************
CSceneManager* CSceneManager::myAdd;

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CSceneManager::~CSceneManager()
{
	Uninit();
}
//=============================================================================
//	����������
//=============================================================================
void CSceneManager::Init(SCENE_MODE _sceneMode,
	CRenderer* _renderer,
	CSound* _sound,
	CJoypad* _joypad,
	CKeyboard* _keyboard)
{
	//	�e�I�u�W�F�N�g�̃Z�b�g
	renderer = _renderer;
	device = renderer->GetDevice();
	sound = _sound;
	keyboard = _keyboard;
	joypad = _joypad;
	threadHandle = nullptr;
	threadFlag = false;
	threadEndFlag = false;

	//	�J�n���_�̃��[�h���Z�b�g
	curScene = _sceneMode;
	prevScene = _sceneMode;
	nextScene = _sceneMode;

	//	�X�V�֐��Z�b�g
	fpUpdate = &CSceneManager::NormalUpdate;

	//	�V�[�������Z�b�g
	SetScene();
}
//=============================================================================
//	�I������
//=============================================================================
void CSceneManager::Uninit()
{
	SAFE_DELETE(scene);
}
//=============================================================================
//	�X�V����
//=============================================================================
void CSceneManager::Update()
{
	//	�ݒ肳�ꂽ�X�V�֐���
	(this->*fpUpdate)();
}
//=============================================================================
//	�ʏ�X�V����
//=============================================================================
void CSceneManager::NormalUpdate()
{
	scene->Update();
}
//=============================================================================
//	�t�F�[�h���X�V����
//=============================================================================
void CSceneManager::FadeUpdate()
{
	CObj::UpdateAll(PRIORIRY_FADE);

	//	�V�[���؂�ւ��t���O����������
	if (changeFlag == true)
	{
		//	�V�[���ω��t���O��OFF��
		changeFlag = false;

		//	�t�F�[�h�C���Ȃ�
		if (fadeMode == FADE_IN)
		{
			//	�V�[���؂�ւ�
			ChangeScene();
		}
		//	�t�F�[�h�A�E�g�Ȃ�
		else
		{
			//	�X�V�֐��Z�b�g
			fpUpdate = &CSceneManager::NormalUpdate;
			fadeMode = FADE_NONE;
		}
	}
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CSceneManager::Draw()
{
	scene->Draw();
}
//=============================================================================
//	�V�[���؂�ւ��O�t�F�[�h�C������
//=============================================================================
void CSceneManager::SetFadeIn(SCENE_MODE _nextScene)
{
	//	�t�F�[�h�C������
	CFadeIn::Create(device, PRIORIRY_FADE);

	fadeMode = FADE_IN;

	//	�X�V�֐��Z�b�g
	fpUpdate = &CSceneManager::FadeUpdate;

	//	���̃V�[����ۑ�
	nextScene = _nextScene;
}
//=============================================================================
//	�V�[���؂�ւ�����
//=============================================================================
void CSceneManager::ChangeScene()
{
	//	���݂̃V�[���̏I��
	SAFE_DELETE(scene);

	//	CScene�̒��g��S�č폜
	CObj::ReleaseAll();

	//	�V�[������ۑ�
	prevScene = curScene;
	curScene = nextScene;

	//	threadFlag�������Ă����ꍇ
	//	���C���X���b�h�Ńt�F�[�h���̃I�u�W�F�N�g�X�V�E�`����s��
	//	�T�u�X���b�h��scene���̓ǂݍ���
	if (threadFlag == true)
	{
		threadFlag = false;

		//	�}���`�^�X�N�Ńi�E���[�f�B���O
		unsigned* threadID = nullptr;
		threadHandle = (HANDLE)_beginthreadex(NULL, 0, CSceneManager::fpMulti_Fade, NULL, NULL, threadID);

		//	�i�E���[�f�B���O����
		nowLoading();
	}
	else
	{
		SetScene();
	}

	threadEndFlag = false;
}
//=============================================================================
//	�i�E���[�f�B���O�����i�}���`�^�X�N�j
//=============================================================================
void CSceneManager::nowLoading()
{
	DWORD execLastTime = 0;
	DWORD currentTime = 0;
	int countFPS = 0;

	execLastTime = timeGetTime();
	currentTime = 0;




	//	�i�E���[�f�B���O�p�̃I�u�W�F�N�g�𐶐�
	CObj2D* bg = CObj2D::Create(device,
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
		PRIORIRY_FADE);

	CObj2D* obj2D1 = CObj2D::Create(device,
		D3DXVECTOR3(150.0f, 150.0f, 0.0f),
		PRIORIRY_FADE);
	obj2D1->setTexture(CTextures::TEXTURE_TEST);






	//	�i�E���[�f�B���O����
	for (;;)
	{
		//	�ǂݍ��ݏI����A���[�v�𔲂���
		if (threadEndFlag == true)
		{
			break;
		}

		//	fps30�ōX�V�ƕ`��
		currentTime = timeGetTime();
		if ((currentTime - execLastTime) >= (1000 / 30))
		{
			execLastTime = currentTime;


			//	�ǂݍ��ݒ���������
			obj2D1->addRot(D3DXVECTOR3(0.0f, 0.0f, 1.0f));


			CObj::UpdateAll();

			renderer->Draw();
		}
	}

	obj2D1->Release();
	bg->Release();
}
//=============================================================================
//	�X�V�����i�}���`�^�X�N�j
//=============================================================================
unsigned __stdcall CSceneManager::fpMulti_Fade(void *p)
{
	//	���̃V�[���𐶐�
	myAdd->SetScene();

	//	�V�[�����̓ǂݍ��ݏI����A�t���O�����Ă�
	myAdd->setThreadEndFlag(true);

	//	�}���`�^�X�N�I��
	_endthreadex(0);

	return NULL;
}
//=============================================================================
//	�V�[���Z�b�g����
//=============================================================================
void CSceneManager::SetScene()
{
	switch (curScene)
	{
	case SCENE_SPLASH:

		//	���S�V�[�����Z�b�g
		scene = new CSceneSplash();

		break;

	case SCENE_TITLE:

		//	�^�C�g���V�[�����Z�b�g
		scene = new CSceneTitle();

		break;

	case SCENE_STAGE_SELECT:

		//	�X�e�[�W�Z���N�g�V�[�����Z�b�g
		scene = new CSceneStageSelect();

		break;


	case SCENE_GAME:

		//	�X�e�[�W�Z���N�g�V�[�����Z�b�g
		scene = new CSceneGame();

		break;

	case SCENE_RESULT:

		//���U���g�V�[�����Z�b�g
		scene = new CSceneResult();

		break;
	}

	//	�V�[���̏�����
	scene->Init(renderer, nullptr, nullptr, keyboard);

	//	�t�F�[�h�A�E�g�J�n
	CFadeOut::Create(device, PRIORIRY_FADE);
	fadeMode = FADE_OUT;

	//	�X�V�֐��Z�b�g
	fpUpdate = &CSceneManager::FadeUpdate;
}

//-----------------------------------EOF---------------------------------------