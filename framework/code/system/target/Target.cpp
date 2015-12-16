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
#define APPEAR_COUNT_ARROW2 (80)
#define APPEAR_COUNT_CIRCLE (50)
#define DISAPPEAR_COUNT_MAX (200)

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
static const float targetSize = 50.0f;
static const float targetSizeBig = targetSize * 1.5f;
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
	targetCrossLocalPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	targetArrowLocalPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	targetCircleLocalPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enable = false;
	counter = 0;
	fpUpdate = nullptr;
	D3DXMatrixIdentity(&invViewMatrix);
	colorState = COLOR_STATE_W;
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
int Target::Set(D3DXVECTOR3 _pos, COLOR_STATE _colorState)
{
	//	�ʒu�Z�b�g
	pos = _pos;
	targetCrossLocalPos = pos;
	targetArrowLocalPos = pos;
	targetCircleLocalPos = D3DXVECTOR3(pos.x + targetCrossDifferentPosition, pos.y + targetCrossDifferentPosition, pos.z);

	switch(0)
	{
	case 0:
		targetCircle->SetPosition(0.0f, 0.0f, 0.0f);
		targetArrow->SetPosition(0.0f, 0.0f, 0.0f);
		targetCross->SetPosition(0.0f, 0.0f, 0.0f);
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

	//	�F�ύX
	colorState = _colorState;
	if(colorState == COLOR_STATE_R)
		targetCircle->SetColor(1.0f, 0.0f, 0.0f, 0.0f);
	else if(colorState == COLOR_STATE_G)
		targetCircle->SetColor(0.0f, 1.0f, 0.0f, 0.0f);
	else if(colorState == COLOR_STATE_B)
		targetCircle->SetColor(0.0f, 0.0f, 1.0f, 0.0f);
	else if(colorState == COLOR_STATE_W)
		targetCircle->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
	else if(colorState == COLOR_STATE_S)
	{
		targetCircle->SetColor(1.0f, 0.5f, 0.0f, 0.0f);

		//	�X�P�[���ύX
		targetCross->SetScale(targetSizeBig, targetSizeBig, targetSizeBig);
		targetArrow->SetScale(targetSizeBig, targetSizeBig, targetSizeBig);
		targetCircle->SetScale(0.0f, 0.0f, 0.0f);
	}

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

	//	�J�����̋t�s��������āA��Ɉ��̏ꏊ�ɏo��悤�ɂ��鏈��
	D3DXVECTOR4 setPos;

	D3DXVec3Transform(&setPos, &targetCrossLocalPos, &invViewMatrix);
	targetCross->SetPosition(setPos.x, setPos.y, setPos.z);

	D3DXVec3Transform(&setPos, &targetArrowLocalPos, &invViewMatrix);
	targetArrow->SetPosition(setPos.x, setPos.y, setPos.z);

	D3DXVec3Transform(&setPos, &targetCircleLocalPos, &invViewMatrix);
	targetCircle->SetPosition(setPos.x, setPos.y, setPos.z);
}
//==============================================================================
// Brief  : cross�o�����̍X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Target::updateAppearCross( void )
{
	//	�ʒu�ύX
	targetCircleLocalPos +=
		D3DXVECTOR3(-targetCrossDifferentPosition / (float)APPEAR_COUNT_CROSS,
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
		if(colorState == COLOR_STATE_S)
			fpUpdate = &Target::updateAppearArrowBig;
		else
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
	if(counter < APPEAR_COUNT_ARROW2 / 2)
	{
		targetArrow->AddColorA(1.0f/ (float)(APPEAR_COUNT_ARROW2 / 2));
		targetArrow->AddRotationZ(D3DX_PI / (float)(APPEAR_COUNT_ARROW2 / 2));
	}
	if(counter > 20)
	{
		//	���񂾂�Əo��
		targetCircle->AddColorA(1.0f / (float)(60));

		//	���񂾂�傫��
		float addSize = targetSize / (float)(60);
		targetCircle->AddScale(addSize, addSize, addSize);
	}

	counter++;
	if(counter == APPEAR_COUNT_ARROW2 / 2)
	{
		//	����
		targetCircle->SetEnableGraphic(true);
	}

	if(counter >= APPEAR_COUNT_ARROW2)
	{
		counter = 0;

		//	�X�V�֐��Z�b�g
		fpUpdate = &Target::updateDisAppear;
	}
}
void Target::updateAppearArrowBig( void )
{
	if(counter < APPEAR_COUNT_ARROW2 / 2)
	{
		targetArrow->AddColorA(1.0f/ (float)(APPEAR_COUNT_ARROW2 / 2));
		targetArrow->AddRotationZ(D3DX_PI / (float)(APPEAR_COUNT_ARROW2 / 2));
	}
	if(counter > 20)
	{
		//	���񂾂�Əo��
		targetCircle->AddColorA(1.0f / (float)(60));

		//	���񂾂�傫��
		float addSize = targetSizeBig / (float)(60);
		targetCircle->AddScale(addSize, addSize, addSize);
	}

	counter++;
	if(counter == APPEAR_COUNT_ARROW2 / 2)
	{
		//	����
		targetCircle->SetEnableGraphic(true);
	}

	if(counter >= APPEAR_COUNT_ARROW2)
	{
		counter = 0;

		//	�X�V�֐��Z�b�g
		fpUpdate = &Target::updateDisAppear;
	}
}
//==============================================================================
// Brief  : Circle�o�����̍X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Target::updateAppearCircle( void )
{
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
void Target::updateAppearCircleBig( void )
{
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
	counter = 0;
	enable = false;

	//	�s����
	targetCross->SetEnableGraphic(false);
	targetArrow->SetEnableGraphic(false);
	targetCircle->SetEnableGraphic(false);
}
//==============================================================================
// �A�N�Z�T
//==============================================================================
float Target::getScale()
{
	return targetSize;
}
