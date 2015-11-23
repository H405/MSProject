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
static const float offsetPosX = -10.0f;
static const float offsetPosY = -20.0f;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Player::Player( void ) : ObjectMovement()
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
	D3DXMatrixIdentity(&invViewMatrix);
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
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}


	pos = _pos;

	//	�I�u�W�F�N�g�̐����J�n
	Effect*		pEffect = nullptr;
	Model*		pModel = nullptr;

	//	�v���C���[�Œ�p�̑䐶��
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "kuma.x" ) );
	body = new ObjectModelMaterial();
	body->Initialize(0);
	body->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	body->SetPosition(pos);
	body->AddPositionX(offsetPosX);
	body->AddPositionY(offsetPosY);
	//body->SetPosition(0.0f, 50.0f, 300.0f);

	//	�v���C���[����
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "arm_r.x" ) );
	arm = new ObjectModelMaterial();
	arm->Initialize(0);
	arm->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	arm->SetPosition(pos);
	//arm->SetPosition(0.0f, 50.0f, 300.0f);

	body->SetScale(1.0f, 1.0f, 1.0f);
	arm->SetScale(1.0f, 1.0f, 1.0f);

	//	�e�I�u�W�F�N�g�o�^
	arm->SetParent(body);


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
void Player::Update( void )
{
	//	�J�����̋t�s��������āA��Ɉ��̏ꏊ�ɏo��悤�ɂ��鏈��
	D3DXVECTOR4 setPos;

	D3DXVec3Transform(&setPos, &pos, &invViewMatrix);

	//	�r�ɃZ�b�g
	arm->SetPosition(setPos.x, setPos.y, setPos.z);

	//	�I�t�Z�b�g�l���������Ă�����x
	D3DXVECTOR3 buffPos = pos;
	buffPos.x += offsetPosX;
	buffPos.y += offsetPosY;
	D3DXVec3Transform(&setPos, &buffPos, &invViewMatrix);

	//	�g�̂ɃZ�b�g
	body->SetPosition(setPos.x, setPos.y, setPos.z);

	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
//	�A�N�Z�T
//==============================================================================
void Player::setRotationArm(float _x, float _y, float _z)
{
	arm->SetRotation(_x, _y, _z);
}