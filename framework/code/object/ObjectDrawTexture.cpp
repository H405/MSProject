//==============================================================================
//
// File   : ObjectDrawTexture.cpp
// Brief  : �f�o�b�O�e�N�X�`���`��I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/27 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectDrawTexture.h"
#include "../framework/camera/Camera.h"
#include "../framework/input/InputKeyboard.h"
#include "../graphic/graphic/GraphicDrawTexture.h"
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
ObjectDrawTexture::ObjectDrawTexture( void ) : Object()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectDrawTexture::~ObjectDrawTexture( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
// Arg    : InputKeyboard* pKeyboard			: �L�[�{�[�h����
//==============================================================================
int ObjectDrawTexture::Initialize( int priority, InputKeyboard* pKeyboard )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̏�����
	pKeyboard_ = pKeyboard;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectDrawTexture::Finalize( void )
{
	// �e�N�X�`���e�[�u���̊J��
	delete[] ppTableTexture_;
	ppTableTexture_ = nullptr;

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
// Arg    : InputKeyboard* pKeyboard			: �L�[�{�[�h����
//==============================================================================
int ObjectDrawTexture::Reinitialize( int priority, InputKeyboard* pKeyboard )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pKeyboard );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ObjectDrawTexture* pOut				: �R�s�[��A�h���X
//==============================================================================
int ObjectDrawTexture::Copy( ObjectDrawTexture* pOut ) const
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
void ObjectDrawTexture::Update( void )
{
	// �e�N�X�`���̐؂�ւ�
	if( pKeyboard_->IsTrigger( DIK_Z ) )
	{
		--indexTexture_;
		if( indexTexture_ < 0 )
		{
			indexTexture_ = countTexture_ - 1;
		}
	}
	else if( pKeyboard_->IsTrigger( DIK_X ) )
	{
		++indexTexture_;
		if( indexTexture_ >= countTexture_ )
		{
			indexTexture_ = 0;
		}
	}
	if( pKeyboard_->IsTrigger( DIK_LSHIFT ) )
	{
		isEnableDraw_ = !isEnableDraw_;
	}

	// �e�N�X�`���̐ݒ�
	pTextureCurrent_ = ppTableTexture_[ indexTexture_ ];

	// �`��N���X�̗L���ݒ�
	bool	isEnableGraphic;		// �`��N���X�̗L���t���O
	if( isEnableDraw_ && indexTexture_ != countTexture_ - 1 )
	{
		isEnableGraphic = true;
	}
	else
	{
		isEnableGraphic = false;
	}
	pGraphic_->SetIsEnable( isEnableGraphic );
#if 0
	// �F�̔{���̐ݒ�
	D3DSURFACE_DESC	description;			// ���
	const Camera*	pCamera = nullptr;		// �J����
	if( pParameter_ != nullptr && pTextureCurrent_ != nullptr )
	{
		pTextureCurrent_->GetLevelDesc( 0, &description );
		pCamera = pParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
		if( description.Format == D3DFMT_R32F )
		{
			pMultiply_[ 0 ] = 1.0f / pCamera->GetClipFar();
		}
		else
		{
			pMultiply_[ 0 ] = 1.0f;
		}
	}
#endif
	// ��{�N���X�̏���
	Object::Update();
}

//==============================================================================
// Brief  : �`��N���X�̐���
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : int countTexture					: �e�N�X�`����
// Arg    : IDirect3DTexture9** ppTexture		: �e�N�X�`��
//==============================================================================
int ObjectDrawTexture::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, int countTexture, IDirect3DTexture9** ppTexture )
{
	// �����o�ϐ��̐ݒ�
	countTexture_ = countTexture;
	indexTexture_ = countTexture - 1;
	pParameter_ = pParameter;

	// �e�N�X�`���e�[�u���̐���
	ppTableTexture_ = new IDirect3DTexture9*[ countTexture ];
	if( ppTableTexture_ == nullptr )
	{
		return 1;
	}
	for( int counterTexture = 0; counterTexture < countTexture; ++counterTexture )
	{
		ppTableTexture_[ counterTexture ] = ppTexture[ counterTexture ];
	}

	// �O���t�B�b�N�̐���
	int		result;				// ���s����
	pGraphic_ = new GraphicDrawTexture();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, &pTextureCurrent_, pMultiply_ );
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
// Arg    : GraphicDrawTexture* pValue			: �ݒ肷��l
//==============================================================================
void ObjectDrawTexture::SetGraphic( GraphicDrawTexture* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : GraphicDrawTexture*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicDrawTexture* ObjectDrawTexture::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectDrawTexture::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pGraphic_ = nullptr;
	pParameter_ = nullptr;
	countTexture_ = 0;
	indexTexture_ = 0;
	ppTableTexture_ = nullptr;
	pTextureCurrent_ = nullptr;
	pMultiply_[ 0 ] = 1.0f;
	pMultiply_[ 1 ] = 1.0f;
	pMultiply_[ 2 ] = 1.0f;
	pKeyboard_ = nullptr;
	isEnableDraw_ = false;
}
