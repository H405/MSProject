//==============================================================================
//
// File   : Target.cpp
// Brief  : �^�[�Q�b�g�I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Target.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerTexture.h"
#include "../../object/ObjectBillboard.h"
#include "../../system/ManagerTarget.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************
#define DELETECOUNT_MAX (1000)
#define RANDAM(value) ((rand() % value) - (rand() % value))

#define APPEAR_COUNT_CROSS (50)
#define APPEAR_COUNT_ARROW (25)
#define APPEAR_COUNT_CIRCLE (50)
#define DISAPPEAR_COUNT_MAX (200)

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
static const float targetSize = 32.0f;
static const float targetCrossDifferentPosition = -50.0f;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Target::Target( void )
{
	// �N���X���̏���������
	InitializeSelf();
}
//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Target::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	targetCross = nullptr;
	targetArrow = nullptr;
	targetCircle = nullptr;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enable = false;
	counter = 0;
	fpUpdate = nullptr;
}
//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Target::~Target( void )
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
int Target::Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Texture* pTextureCross,
	Texture* pTextureArrow,
	Texture* pTextureCircle)
{
	//	�I�u�W�F�N�g�̐����J�n
	targetCircle = new ObjectBillboard;
	targetCircle->Initialize(0);
	targetCircle->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pTextureCircle
		);
	targetCircle->SetEnableGraphic(false);


	targetCross = new ObjectBillboard;
	targetCross->Initialize(0);
	targetCross->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pTextureCross
		);
	targetCross->SetEnableGraphic(false);


	targetArrow = new ObjectBillboard;
	targetArrow->Initialize(0);
	targetArrow->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pTextureArrow
		);
	targetArrow->SetEnableGraphic(false);


	// ����I��
	return 0;
}
//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int Target::Set(D3DXVECTOR3 _pos)
{
	//	�ʒu�Z�b�g
	pos = _pos;

	switch(0)
	{
	case 0:
		targetCircle->SetPosition(pos.x, pos.y, pos.z);
		targetArrow->SetPosition(pos.x, pos.y, pos.z);
		targetCross->SetPosition(pos.x + targetCrossDifferentPosition, pos.y + targetCrossDifferentPosition, pos.z);
		break;
	}

	//	����
	targetCross->SetEnableGraphic(true);

	//	�F������
	targetCircle->SetColorAlpha(0.0f);
	targetArrow->SetColorAlpha(0.0f);
	targetCross->SetColorAlpha(0.0f);

	//	��]�ʏ�����
	targetCircle->SetRotation(0.0f, 0.0f, 0.0f);
	targetArrow->SetRotation(0.0f, 0.0f, 0.0f);
	targetCross->SetRotation(0.0f, 0.0f, 0.0f);

	//	�X�P�[���ύX
	targetCross->SetScale(targetSize, targetSize, targetSize);
	targetArrow->SetScale(targetSize, targetSize, targetSize);
	targetCircle->SetScale(0.0f, 0.0f, 0.0f);

	//	�e��ϐ�������
	enable = true;
	counter = 0;

	//	�X�V�֐��Z�b�g
	fpUpdate = &Target::updateAppearCross;

	// ����I��
	return 0;
}
//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Target::Finalize( void )
{
	delete targetCircle;
	delete targetArrow;
	delete targetCross;

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
void Target::Update( void )
{
	//	�ݒ肳�ꂽ�X�V�֐���
	(this->*fpUpdate)();
}
//==============================================================================
// Brief  : cross�o�����̍X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Target::updateAppearCross( void )
{
	//	�ʒu�ύX
	targetCross->AddPosition(
		-targetCrossDifferentPosition / (float)APPEAR_COUNT_CROSS,
		-targetCrossDifferentPosition / (float)APPEAR_COUNT_CROSS,
		0.0f);

	//	���񂾂�Əo��
	if(counter < APPEAR_COUNT_CROSS / 2)
		targetCross->AddColorAlpha(1.0f / (float)(APPEAR_COUNT_CROSS / 2));

	//	�J�E���^�œ�������
	counter++;
	if(counter >= APPEAR_COUNT_CROSS)
	{
		counter = 0;

		//	����
		targetArrow->SetEnableGraphic(true);

		//	�X�V�֐��Z�b�g
		fpUpdate = &Target::updateAppearArrow;
	}
}
//==============================================================================
// Brief  : Arrow�o�����̍X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Target::updateAppearArrow( void )
{
	targetArrow->AddRotationZ(D3DX_PI / (float)APPEAR_COUNT_ARROW);

	//	���񂾂�Əo��
	if(counter < APPEAR_COUNT_ARROW / 2)
		targetArrow->AddColorA(1.0f/ (float)(APPEAR_COUNT_ARROW / 2));

	//	�J�E���^�œ�������
	counter++;
	if(counter >= APPEAR_COUNT_ARROW)
	{
		counter = 0;

		//	����
		targetCircle->SetEnableGraphic(true);

		//	�X�V�֐��Z�b�g
		fpUpdate = &Target::updateAppearCircle;
	}
}
//==============================================================================
// Brief  : Circle�o�����̍X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Target::updateAppearCircle( void )
{
	//targetCircle->AddRotationZ(D3DX_PI / (float)APPEAR_COUNT_CIRCLE);

	if(counter < APPEAR_COUNT_CIRCLE / 2)
	{
		//	���񂾂�Əo��
		targetCircle->AddColorA(1.0f / (float)(APPEAR_COUNT_CIRCLE / 2));

		//	���񂾂�傫��
		float addSize = targetSize / (float)(APPEAR_COUNT_CIRCLE / 2);
		targetCircle->AddScale(addSize, addSize, addSize);
	}

	//	�J�E���^�œ�������
	counter++;
	if(counter >= APPEAR_COUNT_CIRCLE)
	{
		counter = 0;

		//	�X�V�֐��Z�b�g
		fpUpdate = &Target::updateDisAppear;
	}
}
//==============================================================================
// Brief  : ���Ŏ��̍X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Target::updateDisAppear( void )
{
	//targetCross->AddRotationX(-1.0f / (float)DISAPPEAR_COUNT_MAX);
	//targetArrow->AddRotationY(-1.0f / (float)DISAPPEAR_COUNT_MAX);
	//targetCircle->AddRotationZ(-1.0f / (float)DISAPPEAR_COUNT_MAX);

	//	���񂾂�Ə���
	targetCross->AddColorAlpha(-1.0f / (float)DISAPPEAR_COUNT_MAX);
	targetArrow->AddColorAlpha(-1.0f / (float)DISAPPEAR_COUNT_MAX);
	targetCircle->AddColorAlpha(-1.0f / (float)DISAPPEAR_COUNT_MAX);

	//	�J�E���^�œ�������
	counter++;
	if(counter >= DISAPPEAR_COUNT_MAX)
	{
		counter = 0;
		enable = false;

		//	�s����
		targetCross->SetEnableGraphic(false);
		targetArrow->SetEnableGraphic(false);
		targetCircle->SetEnableGraphic(false);
	}
}
//==============================================================================
// Brief  : �^�[�Q�b�g�̏��ŏ���
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Target::Dissappear()
{
	Finalize();
}
