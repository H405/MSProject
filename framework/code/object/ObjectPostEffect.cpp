//==============================================================================
//
// File   : ObjectPostEffect.cpp
// Brief  : ��ʃ|���S���I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectPostEffect.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../graphic/graphic/GraphicPostEffect.h"
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
ObjectPostEffect::ObjectPostEffect( void ) : ObjectMovement()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectPostEffect::~ObjectPostEffect( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
// Arg    : Fade* pFade							: �t�F�[�h
//==============================================================================
int ObjectPostEffect::Initialize( int priority, Fade* pFade )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pFade_ = pFade;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectPostEffect::Finalize( void )
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
// Arg    : Fade* pFade							: �t�F�[�h
//==============================================================================
int ObjectPostEffect::Reinitialize( int priority, Fade* pFade )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pFade );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ObjectPostEffect* pOut				: �R�s�[��A�h���X
//==============================================================================
int ObjectPostEffect::Copy( ObjectPostEffect* pOut ) const
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
void ObjectPostEffect::Update( void )
{
	// �t�F�[�h�̍X�V
	proportionFade_ = pFade_->GetProportion();

	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : �`��N���X�̐���
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTexture2D		: 2D�`��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
// Arg    : Texture* pTexture					: �e�N�X�`��
//==============================================================================
int ObjectPostEffect::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, Texture* pTexture )
{
	// �O���t�B�b�N�̐���
	int					result;				// ���s����
	IDirect3DTexture9*	pTextureSet;		// �ݒ肷��e�N�X�`��
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}
	pGraphic_ = new GraphicPostEffect();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, &proportionFade_, pTexture3D, pTexture2D, pTextureMask, pTextureSet );
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
// Arg    : GraphicPostEffect* pValue			: �ݒ肷��l
//==============================================================================
void ObjectPostEffect::SetGraphic( GraphicPostEffect* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : GraphicPostEffect*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicPostEffect* ObjectPostEffect::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectPostEffect::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pGraphic_ = nullptr;
	pFade_ = nullptr;
	proportionFade_ = 0.0f;
}
