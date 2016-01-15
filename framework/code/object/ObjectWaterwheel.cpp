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
#include "ObjectModel.h"
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
ObjectWaterwheel::ObjectWaterwheel( void ) : ObjectMovement()
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
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}


	pos = _pos;
	rotSpeed = _rotSpeed;

	//	�I�u�W�F�N�g�̐����J�n
	Effect*		pEffect = nullptr;
	Effect*		pEffectReflect = nullptr;
	Effect*		pEffectShadow = nullptr;
	Effect*		pEffectParaboloid = nullptr;
	Model*		pModel = nullptr;

	//	���ԌŒ�p�̑䐶��
	pEffect = pArgument->pEffect_->Get( _T( "Model.fx" ) );
	pEffectReflect = pArgument->pEffect_->Get( _T( "ModelReflect.fx" ) );
	pEffectShadow = pArgument->pEffect_->Get( _T( "ModelShadow.fx" ) );
	pEffectParaboloid = pArgument->pEffect_->Get( _T( "ModelParaboloid.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "suisya_dai_002.x" ) );
	stand = new ObjectModel();
	stand->Initialize(0);
	stand->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect, pEffectShadow, pEffectParaboloid);
	stand->SetPosition(pos);
	stand->SetRotationY(_rotY);

	//	���Ԑ���
	pEffect = pArgument->pEffect_->Get( _T( "Model.fx" ) );
	pEffectReflect = pArgument->pEffect_->Get( _T( "ModelReflect.fx" ) );
	pEffectShadow = pArgument->pEffect_->Get( _T( "ModelShadow.fx" ) );
	pEffectParaboloid = pArgument->pEffect_->Get( _T( "ModelParaboloid.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "suisya_gear_002.x" ) );
	wheel = new ObjectModel();
	wheel->Initialize(0);
	wheel->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect, pEffectShadow, pEffectParaboloid);
	wheel->SetPosition(pos);
	wheel->AddPositionY(offsetPositionY);
	wheel->SetRotationY(_rotY);


	stand->SetScale(170.0f, 170.0f, 170.0f);
	wheel->SetScale(170.0f, 170.0f, 170.0f);


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
void ObjectWaterwheel::Update( void )
{
	wheel->AddRotationZ(rotSpeed);

	// ��{�N���X�̏���
	ObjectMovement::Update();
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
