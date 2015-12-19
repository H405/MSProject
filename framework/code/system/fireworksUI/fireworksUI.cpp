//==============================================================================
//
// File   : FireworksUI.cpp
// Brief  : �ԉ�UI�I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "fireworksUI.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerTexture.h"
#include "../../object/Object2D.h"
#include "../../framework/develop/DebugProc.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
FireworksUI::FireworksUI( void ) : ObjectMovement()
{
	// �N���X���̏���������
	InitializeSelf();
}
//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void FireworksUI::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	fpUpdate = nullptr;
}
//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
FireworksUI::~FireworksUI( void )
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
int FireworksUI::Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Texture* pFireworksUITex)
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}

	fireworksUI1 = new Object2D();
	fireworksUI1->Initialize(0);
	fireworksUI1->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pFireworksUITex
		);
	fireworksUI1->SetScale(100.0f, 100.0f, 0.0f);

	//	setScaleTexture�ŁA��������ݒ�
	fireworksUI1->SetScaleTexture(3.0f, 1.0f);

	//	setPositionTexture�ŁA0�`1�i�ۂߍ��ޕK�v�����I�j�l��ݒ肵�āAUV�X�N���[������
	fireworksUI1->SetPositionTexture(0.0f, 0.0f);


	fireworksUI2 = new Object2D();
	fireworksUI2->Initialize(0);
	fireworksUI2->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pFireworksUITex
		);
	fireworksUI2->SetScale(180.0f, 180.0f, 0.0f);

	fireworksUI2->SetScaleTexture(3.0f, 1.0f);
	fireworksUI2->SetPositionTexture(1.0f / 3.0f, 0.0f);

	fireworksUI3 = new Object2D();
	fireworksUI3->Initialize(0);
	fireworksUI3->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pFireworksUITex
		);
	fireworksUI3->SetScale(100.0f, 100.0f, 0.0f);

	fireworksUI3->SetScaleTexture(3.0f, 1.0f);
	fireworksUI3->SetPositionTexture(1.0f / 3.0f * 2.0f, 0.0f);

	// ����I��
	return 0;
}
//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int FireworksUI::Finalize( void )
{
	delete fireworksUI1;
	delete fireworksUI2;
	delete fireworksUI3;

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
void FireworksUI::Update( void )
{
	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : �ʒu�Z�b�g����
//==============================================================================
void FireworksUI::setPosition(float _x, float _y, float _z)
{
	fireworksUI1->SetPosition(_x + 100.0f, _y, _z);
	fireworksUI2->SetPosition(_x, _y, _z);
	fireworksUI3->SetPosition(_x - 100.0f, _y, _z);

	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : �F�̃Z�b�g
//==============================================================================
void FireworksUI::setColorState(COLOR_STATE _colorState)
{
	switch(_colorState)
	{
	case COLOR_STATE_R:

		fireworksUI1->SetPositionTextureX(-1.0f / 3.0f);
		fireworksUI2->SetPositionTextureX(0.0f);
		fireworksUI3->SetPositionTextureX(1.0f / 3.0f);

		break;

	case COLOR_STATE_G:

		fireworksUI1->SetPositionTextureX(0.0f);
		fireworksUI2->SetPositionTextureX(1.0f / 3.0f);
		fireworksUI3->SetPositionTextureX(-1.0f / 3.0f);

		break;

	case COLOR_STATE_B:

		fireworksUI1->SetPositionTextureX(1.0f / 3.0f);
		fireworksUI2->SetPositionTextureX(-1.0f / 3.0f);
		fireworksUI3->SetPositionTextureX(0.0f);

		break;
	}
}