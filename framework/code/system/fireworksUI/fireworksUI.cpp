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
#define MOVE_COUNT_MAX (5)

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
static const float posRate = 160.0f;
static const float rotRate = D3DX_PI / 6.0f;
static const float rotOffset = 0.78399348f;
static const float defaultScale = 64.0f;
static const float addScale = 12.0f;

static const COLOR_STATE stateTable[FIREWORKS_UI_MAX] =
{
	COLOR_STATE_R,
	COLOR_STATE_G,
	COLOR_STATE_B,

	COLOR_STATE_R,
	COLOR_STATE_G,
	COLOR_STATE_B,

	COLOR_STATE_R,
	COLOR_STATE_G,
	COLOR_STATE_B,

	COLOR_STATE_R,
	COLOR_STATE_G,
	COLOR_STATE_B,
};

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
	fireworksUI = nullptr;

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = 0.0f;
	addRot = 0.0f;

	stateNum = 0;
	colorState = stateTable[stateNum];
	stateNumOld = stateNum;
	moveFlag = false;
	moveCount = 0;
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

	fireworksUI = new Object2D[FIREWORKS_UI_MAX];
	for(int count = 0;count < FIREWORKS_UI_MAX;count++)
	{
		fireworksUI[count].Initialize(0);
		fireworksUI[count].CreateGraphic(
			0,
			pParameter,
			pEffectGeneral,
			pFireworksUITex
		);
		fireworksUI[count].SetScale(defaultScale, defaultScale, 0.0f);

		//	setScaleTexture�ŁA��������ݒ�
		fireworksUI[count].SetScaleTexture(3.0f, 1.0f);
	}

	//	setPositionTexture�ŁA0�`1�i�ۂߍ��ޕK�v�����I�j�l��ݒ肵�āAUV�X�N���[������
	fireworksUI[0].SetPositionTexture(0.0f, 0.0f);
	fireworksUI[1].SetPositionTexture(1.0f / 3.0f, 0.0f);
	fireworksUI[2].SetPositionTexture(1.0f / 3.0f * 2.0f, 0.0f);
	fireworksUI[3].SetPositionTexture(0.0f, 0.0f);
	fireworksUI[4].SetPositionTexture(1.0f / 3.0f, 0.0f);
	fireworksUI[5].SetPositionTexture(1.0f / 3.0f * 2.0f, 0.0f);
	fireworksUI[6].SetPositionTexture(0.0f, 0.0f);
	fireworksUI[7].SetPositionTexture(1.0f / 3.0f, 0.0f);
	fireworksUI[8].SetPositionTexture(1.0f / 3.0f * 2.0f, 0.0f);
	fireworksUI[9].SetPositionTexture(0.0f, 0.0f);
	fireworksUI[10].SetPositionTexture(1.0f / 3.0f, 0.0f);
	fireworksUI[11].SetPositionTexture(1.0f / 3.0f * 2.0f, 0.0f);

	fireworksUI[0].AddScale(addScale * MOVE_COUNT_MAX, addScale * MOVE_COUNT_MAX, 0.0f);

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
	delete[] fireworksUI;

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
	if(moveFlag == true)
	{
		moveCount++;
		if(moveCount > MOVE_COUNT_MAX)
		{
			moveCount = 0;
			moveFlag = false;
		}
		else
		{
			rot += addRot;
			fireworksUI[stateNum].AddScale(addScale, addScale, 0.0f);
			fireworksUI[stateNumOld].AddScale(-addScale, -addScale, 0.0f);
		}
	}


	D3DXMATRIX transMatrix, transOffsetMatrix, rotMatrix;
	D3DXMATRIX outMatrix;

	for(int count = 0;count < FIREWORKS_UI_MAX;count++)
	{
		D3DXMatrixIdentity(&outMatrix);
		D3DXMatrixIdentity(&transMatrix);
		D3DXMatrixIdentity(&transOffsetMatrix);
		D3DXMatrixIdentity(&rotMatrix);

		//	�I�t�Z�b�g�l�Ƃ��āA�������炷
		D3DXMatrixTranslation(
			&transOffsetMatrix,
			0.0f,
			posRate,
			0.0f);

		D3DXMatrixMultiply(
			&outMatrix,
			&outMatrix,
			&transOffsetMatrix
			);


		//	�ړ�������ɉ�]
		D3DXMatrixRotationYawPitchRoll(
			&rotMatrix,
			0.0f,
			0.0f,
			rot + (rotRate * count) + rotOffset);

		D3DXMatrixMultiply(
			&outMatrix,
			&outMatrix,
			&rotMatrix
			);


		//	���ʂ̈ʒu�ړ�
		D3DXMatrixTranslation(
			&transMatrix,
			pos.x,
			pos.y,
			pos.z);

		D3DXMatrixMultiply(
			&outMatrix,
			&outMatrix,
			&transMatrix
			);

		fireworksUI[count].SetPosition(outMatrix._41, outMatrix._42, outMatrix._43);
	}

	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : �ʒu�Z�b�g����
//==============================================================================
void FireworksUI::setPosition(float _x, float _y, float _z)
{
	pos.x = _x;
	pos.y = _y;
	pos.z = _z;

	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : �ԉΐF���Z�b�g����
//==============================================================================
void FireworksUI::addRotColor()
{
	if(moveFlag == false)
	{
		stateNumOld = stateNum;

		stateNum--;
		if(stateNum <= -1)
			stateNum = FIREWORKS_UI_MAX - 1;

		colorState = stateTable[stateNum];

		moveFlag = true;

		addRot = (rotRate / (float)MOVE_COUNT_MAX);

	}
}
void FireworksUI::subRotColor()
{
	if(moveFlag == false)
	{
		stateNumOld = stateNum;

		stateNum++;
		if(stateNum >= FIREWORKS_UI_MAX)
			stateNum = 0;

		colorState = stateTable[stateNum];

		moveFlag = true;

		addRot = (-rotRate / (float)MOVE_COUNT_MAX);
	}
}



void FireworksUI::SetEnableGraphic(bool _flag)
{
	fireworksUI[0].SetEnableGraphic(_flag);
	fireworksUI[1].SetEnableGraphic(_flag);
	fireworksUI[2].SetEnableGraphic(_flag);
	fireworksUI[3].SetEnableGraphic(_flag);
	fireworksUI[4].SetEnableGraphic(_flag);
	fireworksUI[5].SetEnableGraphic(_flag);
	fireworksUI[6].SetEnableGraphic(_flag);
	fireworksUI[7].SetEnableGraphic(_flag);
	fireworksUI[8].SetEnableGraphic(_flag);
	fireworksUI[9].SetEnableGraphic(_flag);
	fireworksUI[10].SetEnableGraphic(_flag);
	fireworksUI[11].SetEnableGraphic(_flag);
}