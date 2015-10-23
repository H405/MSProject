//==============================================================================
//
// File   : SceneTitle.cpp
// Brief  : �^�C�g���V�[���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "SceneTitle.h"
#include "../framework/camera/CameraObject.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/VirtualController.h"
#include "../framework/light/LightDirection.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectMesh.h"
#include "../framework/polygon/PolygonMesh.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//******************************************************************************
// �ÓI�ϐ�
//******************************************************************************
//	�_�ŗp�J�E���g��
static const int flashingCountHirf = 20;
static const int flashingCountMax = 40;

//	�����J�n�@�����̃T�C�Y
static const float startXX_NormalSizeX = 400.0f;
static const float startXX_NormalSizeY = 120.0f;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneTitle::SceneTitle( void ) : SceneMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pCamera_ = nullptr;
	pLight_ = nullptr;

	titleLogo = nullptr;
	startGame = nullptr;
	startTutorial = nullptr;
	pushAKey = nullptr;
	finger = nullptr;

	player = nullptr;

	chooseObject = nullptr;

	pushAKeyFlashingCount = -1;
	pushChooseObjectFlashingCount = -1;

	chooseFlag = false;

	fpUpdate = nullptr;
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
SceneTitle::~SceneTitle( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
int SceneTitle::Initialize( SceneArgumentMain* pArgument )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Initialize( pArgument );
	if( result != 0 )
	{
		return result;
	}

	// �J�����̐���
	pCamera_ = new CameraObject();
	if( pCamera_ == nullptr )
	{
		return 1;
	}
	result = pCamera_->Initialize(
		D3DX_PI / 4.0f,
		1280,
		720,
		0.1f,
		1000.0f,
		D3DXVECTOR3( 0.0f, 30.0f, -100.0f ),
		D3DXVECTOR3( 0.0f, 30.0f, 10.0f ),
		D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetCamera( GraphicMain::CAMERA_GENERAL, pCamera_ );

	// ���C�g�̐���
	pLight_ = new LightDirection();
	if( pLight_ == nullptr )
	{
		return 1;
	}
	result = pLight_->Initialize( D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR3( 0.0f, -0.7f, 0.7f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL, pLight_ );

	//	�I�u�W�F�N�g�̐����J�n
	Effect*		pEffect = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;

	//	�v���C���[����
	pEffect = pArgument_->pEffect_->Get( _T( "Model.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "head.x" ) );

	player = new ObjectModel;
	player->Initialize(0);
	player->CreateGraphic(
		0,
		pModel,
		pArgument->pEffectParameter_,
		pEffect );

	player->SetPositionZ(-30.0f);

	//	�Ƃ̐���
	pModel = pArgument->pModel_->Get( _T( "kuma.x" ) );

	for(int count = 0;count < 3;count++)
	{
		house[count] = new ObjectModel;
		house[count]->Initialize(0);
		house[count]->CreateGraphic(
			0,
			pModel,
			pArgument->pEffectParameter_,
			pEffect);
	}

	house[0]->SetPositionX(-50.0f);
	house[2]->SetPositionX(50.0f);

	house[0]->SetPositionZ(100.0f);
	house[1]->SetPositionZ(100.0f);
	house[2]->SetPositionZ(100.0f);

	//	���̃t�B�[���h
	pTexture = pArgument_->pTexture_->Get( _T( "titlelogo.png" ) );
	field = new ObjectMesh();
	field->Initialize( 0, pArgument->pDevice_, 10, 20, 40.0f, 40.0f, 1.0f, 1.0f );
	field->CreateGraphic( 0, pArgument->pEffectParameter_, pEffect, pTexture );


	//	�^�C�g�����S
	titleLogo = new Object2D;
	titleLogo->Initialize(0);
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "titlelogo.png" ) );

	titleLogo->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	titleLogo->SetPosition(350.0f, 100.0f, 0.0f);


	//	A�{�^���������Ă�
	pTexture = pArgument_->pTexture_->Get( _T( "pressAKey.png" ) );
	pushAKey = new Object2D;
	pushAKey->Initialize(0);

	pushAKey->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	pushAKey->SetPosition(0.0f, -200.0f, 0.0f);

	//	�X�V�֐��Z�b�g
	fpUpdate = &SceneTitle::firstUpdate;

	// �t�F�[�h�C��
	pArgument->pFade_->FadeIn( 20 );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int SceneTitle::Finalize( void )
{
	if(finger != nullptr)
		delete finger;
	finger = nullptr;

	if(field != nullptr)
		delete field;
	field = nullptr;

	if(house[0] != nullptr)
		delete house[0];
	house[0] = nullptr;

	if(house[1] != nullptr)
		delete house[1];
	house[1] = nullptr;

	if(house[2] != nullptr)
		delete house[2];
	house[2] = nullptr;

	if(player != nullptr)
		delete player;
	player = nullptr;

	if(startGame != nullptr)
		delete startGame;
	startGame = nullptr;

	if(startTutorial != nullptr)
		delete startTutorial;
	startTutorial = nullptr;

	if(pushAKey != nullptr)
		delete pushAKey;
	pushAKey = nullptr;

	if(titleLogo != nullptr)
		delete titleLogo;
	titleLogo = nullptr;

	// ���C�g�̊J��
	delete pLight_;
	pLight_ = nullptr;
	pArgument_->pEffectParameter_->SetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL, nullptr );

	// �J�����̊J��
	delete pCamera_;
	pCamera_ = nullptr;
	pArgument_->pEffectParameter_->SetCamera( GraphicMain::CAMERA_GENERAL, pCamera_ );

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : SceneArgumentMain* pArgument		: �V�[������
//==============================================================================
int SceneTitle::Reinitialize( SceneArgumentMain* pArgument )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pArgument );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : SceneTitle* pOut					: �R�s�[��A�h���X
//==============================================================================
int SceneTitle::Copy( SceneTitle* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = SceneMain::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::Update( void )
{
	// �e�X�g
	PrintDebug( _T( "�^�C�g��\n" ) );

	//	�J�����X�V
	pCamera_->Update();

	//	wii�����R������������Ă���Ύw�̈ړ�
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();

		finger->SetPosition(IRBuff.x, IRBuff.y, 0.0f);
	}

	//	�ݒ肳�ꂽ�X�V�N���X��
	(this->*fpUpdate)();
}

//==============================================================================
// Brief  : �X�V����1(�uA�{�^���������Ăˁv�̓_��)
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::firstUpdate( void )
{
	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}

	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	�uA�{�^���������Ăˁv�������āA�u�����J�n�v�Ɓu���K�J�n�v�����ꂼ�ꐶ��
		delete pushAKey;
		pushAKey = nullptr;

		startGame = new Object2D;
		startGame->Initialize(0);

		startTutorial = new Object2D;
		startTutorial->Initialize(0);

		Effect*		pEffect = nullptr;
		Texture*	pTexture = nullptr;
		pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
		pTexture = pArgument_->pTexture_->Get( _T( "startGame.png" ) );

		startGame->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		startGame->SetPosition(-300.0f, -100.0f, 0.0f);
		startGame->SetScaleX(startXX_NormalSizeX);
		startGame->SetScaleY(startXX_NormalSizeY);




		pTexture = pArgument_->pTexture_->Get( _T( "startTutorial.png" ) );

		startTutorial->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		startTutorial->SetPosition(300.0f, -100.0f, 0.0f);
		startTutorial->SetScaleX(startXX_NormalSizeX);
		startTutorial->SetScaleY(startXX_NormalSizeY);



		//	wii�����R�����ڑ�����Ă����
		//	�w�̏�����
		if(pArgument_->pWiiController_->getIsConnect() == true)
		{
			pTexture = pArgument_->pTexture_->Get( _T( "finger.png" ) );
			finger = new Object2D;
			finger->Initialize(0);

			finger->CreateGraphic(
			0,
			pArgument_->pEffectParameter_,
			pEffect,
			pTexture);

			finger->SetScale(50.0f, 50.0f, 0.1f);

			//	IR�őI���ɕύX
			chooseFlag = true;
		}


		//	�f�t�H���g�̑I�������u�����J�n�v�ɐݒ�
		chooseObject = startGame;

		//	wii�����R�����o�^����Ă�ꍇ�͓o�^���Ȃ�
		if(pArgument_->pWiiController_->getIsConnect() == true)
			chooseObject = nullptr;

		//	�_�ŃJ�E���g������
		pushAKeyFlashingCount = 0;

		//	���̍X�V�֐���
		fpUpdate = &SceneTitle::secondUpdate;
	}

	//	�uA�{�^���������Ăˁv�̓_�ŏ���
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			pushAKey->SetColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			pushAKey->SetColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}
	}
}
//==============================================================================
// Brief  : �X�V����2(�Q�[���J�n�E�`���[�g���A���J�n�̑I������)
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::secondUpdate( void )
{
	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
		}
	}

	//	�P�t���[���O�̓o�^�I�u�W�F�N�g��ۑ�
	chooseObjectPrev = chooseObject;

	//	����L�[�����ꂽ��
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	�_�ŃJ�E���g������
		pushAKeyFlashingCount = 0;

		//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
		chooseObject->SetColorA(1.0f);

		//	���̍X�V�֐���
		(chooseObject == startGame) ? fpUpdate = &SceneTitle::thirdUpdate : fpUpdate = &SceneTitle::forthUpdate;

		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
		}
	}

	//	���L�[�ňړ�
	if(pArgument_->pVirtualController_->IsTrigger(VC_LEFT))
	{
		//	�_�ŃJ�E���g������
		pushAKeyFlashingCount = 0;

		//	wii�����R���ڑ����͈Ⴄ����
		if(chooseObject == nullptr)
		{
			//	�����L�[�ɕύX
			chooseFlag = false;

			//	�I�u�W�F�N�g�o�^
			chooseObject = startGame;
		}
		else
		{
			//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
			chooseObject->SetColorA(1.0f);

			//	�I�����ړ�
			(chooseObject == startGame) ? chooseObject = startTutorial : chooseObject = startGame;
		}
	}
	if(pArgument_->pVirtualController_->IsTrigger(VC_RIGHT))
	{
		//	�_�ŃJ�E���g������
		pushAKeyFlashingCount = 0;

		//	wii�����R���ڑ����͈Ⴄ����
		if(chooseObject == nullptr)
		{
			//	�����L�[�ɕύX
			chooseFlag = false;

			//	�I�u�W�F�N�g�o�^
			chooseObject = startTutorial;
		}
		else
		{
			//	���݂̃I�u�W�F�N�g��A1.0f�ŕ\��
			chooseObject->SetColorA(1.0f);

			//	�I�����ړ�
			(chooseObject == startGame) ? chooseObject = startTutorial : chooseObject = startGame;
		}
	}


	//	wii�����R������������Ă���Ύw�̈ړ�
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();

		//	�u�����J�n�v�ɓ������Ă��
		if((IRBuff.x <= (startGame->GetPositionX() + (startGame->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (startGame->GetPositionX() - (startGame->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (startGame->GetPositionY() + (startGame->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (startGame->GetPositionY() - (startGame->GetScaleY() * 0.5f))) )
		{
			//	�_�ŃI�u�W�F�N�g�Ƃ��ēo�^
			chooseObject = startGame;

			//	�I����@��IR�ɕύX
			chooseFlag = true;
		}
		//	�u���K�J�n�v�ɓ������Ă��
		else if((IRBuff.x <= (startTutorial->GetPositionX() + (startTutorial->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (startTutorial->GetPositionX() - (startTutorial->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (startTutorial->GetPositionY() + (startTutorial->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (startTutorial->GetPositionY() - (startTutorial->GetScaleY() * 0.5f))) )
		{
			//	�_�ŃI�u�W�F�N�g�Ƃ��ēo�^
			chooseObject = startTutorial;

			//	�I����@��IR�ɕύX
			chooseFlag = true;
		}
		//	���ɂ��������ĂȂ����
		else
		{
			//	�I����@��IR�̏ꍇ�̂�
			if(chooseFlag == true)
			{
				//	�o�^����
				chooseObject = nullptr;
				pushAKeyFlashingCount = 0;
			}
		}
	}


	//	�I�����ڂ̓_�ŏ���
	if(chooseObject != nullptr)
	{
		chooseObject->SetScaleX(startXX_NormalSizeX * 1.3f);
		chooseObject->SetScaleY(startXX_NormalSizeY * 1.3f);

		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			chooseObject->SetColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			chooseObject->SetColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}

		//	�P�t���[���O�̑I���I�u�W�F�N�g�̃T�C�Y��ύX
		if((chooseObjectPrev != nullptr) &&
			(chooseObjectPrev != chooseObject))
		{
			chooseObjectPrev->SetScaleX(startXX_NormalSizeX);
			chooseObjectPrev->SetScaleY(startXX_NormalSizeY);
		}
	}
	else
	{
		startGame->SetScaleX(startXX_NormalSizeX);
		startGame->SetScaleY(startXX_NormalSizeY);

		startTutorial->SetScaleX(startXX_NormalSizeX);
		startTutorial->SetScaleY(startXX_NormalSizeY);
	}
}
//==============================================================================
// Brief  : �X�V����3(����L�[�����ꂽ��̓_�ŏ���-�Q�[���֑J��)
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::thirdUpdate( void )
{
	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}

	//	�I�����ڂ̓_�ŏ���
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			chooseObject->SetColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			chooseObject->SetColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}
	}
}
//==============================================================================
// Brief  : �X�V����4(����L�[�����ꂽ��̓_�ŏ���-�`���[�g���A���֑J��)
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void SceneTitle::forthUpdate( void )
{
	// �V�[���J��
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		//SetSceneNext( ManagerSceneMain::TYPE_TUTORIAL );
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}

	//	�I�����ڂ̓_�ŏ���
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			chooseObject->SetColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			chooseObject->SetColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}
	}
}