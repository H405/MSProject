//==============================================================================
//
// File   : ObjectLightReflect.cpp
// Brief  : ���˃��C�g�`��I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/22 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectLightReflect.h"
#include "../framework/resource/Effect.h"
#include "../graphic/graphic/GraphicLightReflect.h"
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
ObjectLightReflect::ObjectLightReflect( void ) : Object()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectLightReflect::~ObjectLightReflect( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int ObjectLightReflect::Initialize( int priority )
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
int ObjectLightReflect::Finalize( void )
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
int ObjectLightReflect::Reinitialize( int priority )
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
// Arg    : ObjectLightReflect* pOut				: �R�s�[��A�h���X
//==============================================================================
int ObjectLightReflect::Copy( ObjectLightReflect* pOut ) const
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
void ObjectLightReflect::Update( void )
{
	// ��{�N���X�̏���
	Object::Update();
}

//==============================================================================
// Brief  : �`��N���X�̐���
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect** ppEffectGeneral			: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
//==============================================================================
int ObjectLightReflect::CreateGraphic( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
	IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth )
{
	// �O���t�B�b�N�̐���
	int		result;				// ���s����
	pGraphic_ = new GraphicLightReflect();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, ppEffectGeneral, pTextureDiffuse, pTextureSpecular, pTextureNormal, pTextureDepth );
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

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`��N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : GraphicLightReflect* pValue			: �ݒ肷��l
//==============================================================================
void ObjectLightReflect::SetGraphic( GraphicLightReflect* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : GraphicLightReflect*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicLightReflect* ObjectLightReflect::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectLightReflect::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pGraphic_ = nullptr;
}
