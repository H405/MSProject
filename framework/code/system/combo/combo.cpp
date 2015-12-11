//==============================================================================
//
// File   : Combo.cpp
// Brief  : �R���{�I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "combo.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerTexture.h"
#include "../../object/Object2D.h"
#include "../../object/ObjectScore.h"
#include "../../framework/develop/DebugProc.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define FLASHING_COUNT_MAX (10)
#define RANDAM(value) ((rand() % value) - (rand() % value))

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
static const float addAlpha = -0.005f;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Combo::Combo( void ) : ObjectMovement()
{
	// �N���X���̏���������
	InitializeSelf();
}
//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Combo::InitializeSelf( void )
{
	comboString = nullptr;
	comboScore = nullptr;

	score = 0;
	scoreMax = 0;
	flashingCount = 0;
	alpha = 1.0f;

	// �����o�ϐ��̏�����
	fpUpdate = nullptr;
}
//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Combo::~Combo( void )
{
	// �I������
	Finalize();
}
//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int Combo::Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Texture* pComboString,
	Texture* pComboScore)
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}


	//	�u�A���v�����e�N�X�`��
	comboString = new Object2D();
	comboString->Initialize(0);
	comboString->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pComboString
		);
	comboString->SetScale(150.0f, 80.0f, 0.0f);

	comboScore = new ObjectScore();
	comboScore->Initialize(0, 2);
	comboScore->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pComboScore);
	comboScore->SetSizeX(32.0f);
	comboScore->SetSizeY(32.0f);

	// ����I��
	return 0;
}
//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Combo::Finalize( void )
{
	delete comboScore;
	delete comboString;

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Finalize();
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
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Combo::Update( void )
{
	if(alpha > 0.0f)
	{
		flashingCount++;
		alpha += addAlpha;

		if(flashingCount == (FLASHING_COUNT_MAX / 2))
		{
			comboString->SetColorA(0.0f);
			comboScore->SetColorA(0.0f);
		}
		else if(flashingCount == FLASHING_COUNT_MAX)
		{
			flashingCount = 0;
			comboString->SetColorA(alpha);
			comboScore->SetColorA(alpha);
		}
	}

	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : �ʒu�Z�b�g����
//==============================================================================
void Combo::setPosition(float _x, float _y, float _z)
{
	comboString->SetPosition(_x + 100.0f, _y, _z);

	comboScore->SetPos(_x, _y, _z);

	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : �A�N�Z�T
//==============================================================================
void Combo::addScore()
{
	if(alpha <= 0.0f)
	{
		flashingCount = 0;
		score = 0;
	}

	alpha = 1.0f;
	score++;

	if(score > scoreMax)
		scoreMax = score;

	comboScore->SetScore(score);
	comboScore->SetScoreFuture(score);

	// ��{�N���X�̏���
	ObjectMovement::Update();
}
