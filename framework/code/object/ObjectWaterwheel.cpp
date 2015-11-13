//==============================================================================
//
// File   : ObjectWaterwheel.cpp
// Brief  : ���ԃI�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectWaterwheel.h"
#include "ObjectModelMaterial.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../system/SceneArgumentMain.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
static const float offsetPositionY = 20.0f;

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectWaterwheel::ObjectWaterwheel( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectWaterwheel::~ObjectWaterwheel( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
//==============================================================================
int ObjectWaterwheel::Initialize(
	D3DXVECTOR3 _pos,
	float _rotY,
	float _rotSpeed,
	SceneArgumentMain* pArgument)
{
	pos = _pos;
	rotSpeed = _rotSpeed;

	//	�I�u�W�F�N�g�̐����J�n
	Effect*		pEffect = nullptr;
	Model*		pModel = nullptr;

	//	���ԌŒ�p�̑䐶��
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "suisya_dai_005.x" ) );
	stand = new ObjectModelMaterial();
	stand->Initialize(0);
	stand->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	stand->SetPosition(pos);
	stand->SetRotationY(_rotY);

	//	���Ԑ���
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "suisya_gear_005.x" ) );
	wheel = new ObjectModelMaterial();
	wheel->Initialize(0);
	wheel->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	wheel->SetPosition(pos);
	wheel->AddPositionY(offsetPositionY);
	wheel->SetRotationY(_rotY);


	stand->SetScale(70.0f, 70.0f, 70.0f);
	wheel->SetScale(70.0f, 70.0f, 70.0f);


	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectWaterwheel::Finalize( void )
{
	delete stand;
	delete wheel;

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
void ObjectWaterwheel::Update( void )
{
	wheel->AddRotationZ(rotSpeed);
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectWaterwheel::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotSpeed = 0.0f;

	stand = nullptr;
	wheel = nullptr;
}