//==============================================================================
//
// File   : ObjectWaveDataInitialize.cpp
// Brief  : �g���`��I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectWaveDataInitialize.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/GraphicWaveDataInitialize.h"
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
ObjectWaveDataInitialize::ObjectWaveDataInitialize( void ) : Object()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectWaveDataInitialize::~ObjectWaveDataInitialize( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int ObjectWaveDataInitialize::Initialize( int priority )
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
int ObjectWaveDataInitialize::Finalize( void )
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
int ObjectWaveDataInitialize::Reinitialize( int priority )
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
// Arg    : ObjectWaveDataInitialize* pOut		: �R�s�[��A�h���X
//==============================================================================
int ObjectWaveDataInitialize::Copy( ObjectWaveDataInitialize* pOut ) const
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
void ObjectWaveDataInitialize::Update( void )
{
	// �O���t�B�b�N�̊Ǘ�
	++timerGraphic_;
	if( timerGraphic_ > 1 )
	{
		pGraphic_->SetIsEnable( false );
	}

	// ��{�N���X�̏���
	Object::Update();
}

//==============================================================================
// Brief  : �`��N���X�̐���
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �G�t�F�N�g
// Arg    : Texture* pTexture					: �e�N�X�`��
//==============================================================================
int ObjectWaveDataInitialize::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffect, Texture* pTexture )
{
	// �O���t�B�b�N�̐���
	int		result;				// ���s����
	pGraphic_ = new GraphicWaveDataInitialize();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffect, pTexture->pTexture_ );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// �g�k�̐ݒ�
	if( pTexture != nullptr )
	{
		scale_.x = static_cast< float >( pTexture->width_ );
		scale_.y = static_cast< float >( pTexture->height_ );
	}

	// �l�̕ԋp
	return 0;
}

//==============================================================================
// Brief  : �`��N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : GraphicWaveDataInitialize* pValue					: �ݒ肷��l
//==============================================================================
void ObjectWaveDataInitialize::SetGraphic( GraphicWaveDataInitialize* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : GraphicWaveDataInitialize*						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicWaveDataInitialize* ObjectWaveDataInitialize::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectWaveDataInitialize::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pGraphic_ = nullptr;
	timerGraphic_ = 0;
}