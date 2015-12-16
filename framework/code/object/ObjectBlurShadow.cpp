//==============================================================================
//
// File   : ObjectBlurShadow.cpp
// Brief  : �e�p�u���[�`��I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/12/08 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectBlurShadow.h"
#include "../framework/resource/Effect.h"
#include "../graphic/graphic/GraphicBlurShadow.h"
#include "../system/EffectParameter.h"

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
ObjectBlurShadow::ObjectBlurShadow( void ) : Object()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectBlurShadow::~ObjectBlurShadow( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int ObjectBlurShadow::Initialize( int priority )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectBlurShadow::Finalize( void )
{
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
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int ObjectBlurShadow::Reinitialize( int priority )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ObjectBlurShadow* pOut				: �R�s�[��A�h���X
//==============================================================================
int ObjectBlurShadow::Copy( ObjectBlurShadow* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Copy( pOut );
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
void ObjectBlurShadow::Update( void )
{
	// ��{�N���X�̏���
	Object::Update();
}

//==============================================================================
// Brief  : �`��N���X�̐���
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTexture			: �u���[���|����e�N�X�`��
//==============================================================================
int ObjectBlurShadow::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTexture )
{
	// �O���t�B�b�N�̐���
	int		result;				// ���s����
	pGraphic_ = new GraphicBlurShadow();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, pTexture );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// �g�k�̐ݒ�
	if( pParameter != nullptr )
	{
		scale_.x = pParameter->GetWidthScreen();
		scale_.y = pParameter->GetHeightScreen();
	}

	// �l�̕ԋp
	return 0;
}

//==============================================================================
// Brief  : �`��N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : GraphicBlurShadow* pValue					: �ݒ肷��l
//==============================================================================
void ObjectBlurShadow::SetGraphic( GraphicBlurShadow* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : GraphicBlurShadow*						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicBlurShadow* ObjectBlurShadow::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectBlurShadow::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pGraphic_ = nullptr;
}