//==============================================================================
//
// File   : ObjectMerge.cpp
// Brief  : ����3D�`��I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectMerge.h"
#include "../graphic/graphic/GraphicMerge.h"
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
ObjectMerge::ObjectMerge( void ) : Object()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectMerge::~ObjectMerge( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int ObjectMerge::Initialize( int priority )
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
int ObjectMerge::Finalize( void )
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
int ObjectMerge::Reinitialize( int priority )
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
// Arg    : ObjectMerge* pOut					: �R�s�[��A�h���X
//==============================================================================
int ObjectMerge::Copy( ObjectMerge* pOut ) const
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
void ObjectMerge::Update( void )
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
// Arg    : IDirect3DTexture9* pTextureLight	: ���C�g����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureNotLight	: ���C�g�Ȃ��e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureAdd		: ���Z�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
//==============================================================================
int ObjectMerge::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
	IDirect3DTexture9* pTextureDepth )
{
	// �O���t�B�b�N�̐���
	int		result;				// ���s����
	pGraphic_ = new GraphicMerge();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, pTextureLight, pTextureNotLight, pTextureMask, pTextureAdd, pTextureDepth );
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
// Arg    : GraphicMerge* pValue			: �ݒ肷��l
//==============================================================================
void ObjectMerge::SetGraphic( GraphicMerge* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : GraphicMerge*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicMerge* ObjectMerge::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectMerge::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pGraphic_ = nullptr;
}
