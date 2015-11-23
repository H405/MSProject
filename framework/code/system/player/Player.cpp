//==============================================================================
//
// File   : Player.cpp
// Brief  : �v���C���[�I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Player.h"
#include "../../Object/ObjectModelMaterial.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerModel.h"
#include "../../system/SceneArgumentMain.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
static const float offsetPosX = -30.0f;
static const float offsetPosY = -50.0f;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Player::Player( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Player::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	body = nullptr;
	arm = nullptr;
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Player::~Player( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
//==============================================================================
int Player::Initialize(
	D3DXVECTOR3 _pos,
	SceneArgumentMain* pArgument)
{
	pos = _pos;

	//	�I�u�W�F�N�g�̐����J�n
	Effect*		pEffect = nullptr;
	Effect*		pEffectReflect = nullptr;
	Model*		pModel = nullptr;

	//	�v���C���[�Œ�p�̑䐶��
	pEffect = pArgument->pEffect_->Get( _T( "ModelMaterial.fx" ) );
	pEffectReflect = pArgument->pEffect_->Get( _T( "ModelMaterialReflect.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "kuma.x" ) );
	body = new ObjectModelMaterial();
	body->Initialize(0);
	body->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect);
	body->SetPosition(pos);
	body->AddPositionX(offsetPosX);
	body->AddPositionY(offsetPosY);

	//	�v���C���[����
	pEffect = pArgument->pEffect_->Get( _T( "ModelMaterial.fx" ) );
	pEffectReflect = pArgument->pEffect_->Get( _T( "ModelMaterialReflect.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "arm_r.x" ) );
	arm = new ObjectModelMaterial();
	arm->Initialize(0);
	arm->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect);
	arm->SetPosition(pos);


	body->SetScale(2.0f, 2.0f, 2.0f);
	arm->SetScale(2.0f, 2.0f, 2.0f);


	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Player::Finalize( void )
{
	delete body;
	delete arm;

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
void Player::Update( void )
{
}

//==============================================================================
//	�A�N�Z�T
//==============================================================================
void Player::setRotationArm(float _x, float _y, float _z)
{
	arm->SetRotation(_x, _y, _z);
}