//==============================================================================
//
// File   : ObjectBillboard.cpp
// Brief  : �r���{�[�h�|���S���I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/23 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectBillboard.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/GraphicBillboard.h"
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
ObjectBillboard::ObjectBillboard( void ) : ObjectMovement()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectBillboard::~ObjectBillboard( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int ObjectBillboard::Initialize( int priority )
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
int ObjectBillboard::Finalize( void )
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
int ObjectBillboard::Reinitialize( int priority )
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
// Arg    : ObjectBillboard* pOut				: �R�s�[��A�h���X
//==============================================================================
int ObjectBillboard::Copy( ObjectBillboard* pOut ) const
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
void ObjectBillboard::Update( void )
{
	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : �`��N���X�̐���
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : Texture* pTexture					: �e�N�X�`��
//==============================================================================
int ObjectBillboard::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture )
{
	// �O���t�B�b�N�̐���
	int					result;				// ���s����
	IDirect3DTexture9*	pTextureSet;		// �ݒ肷��e�N�X�`��
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}
	pGraphic_ = new GraphicBillboard();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, &color_, &positionTexture_, &scaleTexture_, pTextureSet );
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

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`��N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : GraphicBillboard* pValue						: �ݒ肷��l
//==============================================================================
void ObjectBillboard::SetGraphic( GraphicBillboard* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : GraphicBillboard*							: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicBillboard* ObjectBillboard::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : �F�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: �ݒ肷��l
//==============================================================================
void ObjectBillboard::SetColor( const D3DXCOLOR& value )
{
	// �l�̐ݒ�
	color_ = value;
}

//==============================================================================
// Brief  : �F��RGBA�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void ObjectBillboard::SetColor( float r, float g, float b, float a )
{
	// �l�̐ݒ�
	color_.r = r;
	color_.g = g;
	color_.b = b;
	color_.a = a;
}

//==============================================================================
// Brief  : �F��RGB�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
//==============================================================================
void ObjectBillboard::SetColor( float r, float g, float b )
{
	// �l�̐ݒ�
	color_.r = r;
	color_.g = g;
	color_.b = b;
}

//==============================================================================
// Brief  : �F��R�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
//==============================================================================
void ObjectBillboard::SetColorR( float r )
{
	// �l�̐ݒ�
	color_.r = r;
}

//==============================================================================
// Brief  : �F��G�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void ObjectBillboard::SetColorG( float g )
{
	// �l�̐ݒ�
	color_.g = g;
}

//==============================================================================
// Brief  : �F��B�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void ObjectBillboard::SetColorB( float b )
{
	// �l�̐ݒ�
	color_.b = b;
}

//==============================================================================
// Brief  : �F��A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void ObjectBillboard::SetColorA( float a )
{
	// �l�̐ݒ�
	color_.a = a;
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void ObjectBillboard::SetColorAlpha( float alpha )
{
	// �l�̐ݒ�
	color_.a = alpha;
}

//==============================================================================
// Brief  : �F�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXCOLOR* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void ObjectBillboard::GetColor( D3DXCOLOR* pOut ) const
{
	// �l�̕ԋp
	*pOut = color_;
}

//==============================================================================
// Brief  : �F��R�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectBillboard::GetColorR( void ) const
{
	// �l�̕ԋp
	return color_.r;
}

//==============================================================================
// Brief  : �F��G�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectBillboard::GetColorG( void ) const
{
	// �l�̕ԋp
	return color_.g;
}

//==============================================================================
// Brief  : �F��B�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectBillboard::GetColorB( void ) const
{
	// �l�̕ԋp
	return color_.b;
}

//==============================================================================
// Brief  : �F��A�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectBillboard::GetColorA( void ) const
{
	// �l�̕ԋp
	return color_.a;
}

//==============================================================================
// Brief  : �F�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: ���Z����l
//==============================================================================
void ObjectBillboard::AddColor( const D3DXCOLOR& value )
{
	// �l�̉��Z
	color_ += value;
}

//==============================================================================
// Brief  : �F��RGBA�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void ObjectBillboard::AddColor( float r, float g, float b, float a )
{
	// �l�̉��Z
	color_.r += r;
	color_.g += g;
	color_.b += b;
	color_.a += a;
}

//==============================================================================
// Brief  : �F��RGB�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
//==============================================================================
void ObjectBillboard::AddColor( float r, float g, float b )
{
	// �l�̉��Z
	color_.r += r;
	color_.g += g;
	color_.b += b;
}

//==============================================================================
// Brief  : �F��R�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
//==============================================================================
void ObjectBillboard::AddColorR( float r )
{
	// �l�̉��Z
	color_.r += r;
}

//==============================================================================
// Brief  : �F��G�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void ObjectBillboard::AddColorG( float g )
{
	// �l�̉��Z
	color_.g += g;
}

//==============================================================================
// Brief  : �F��B�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void ObjectBillboard::AddColorB( float b )
{
	// �l�̉��Z
	color_.b += b;
}

//==============================================================================
// Brief  : �F��A�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void ObjectBillboard::AddColorA( float a )
{
	// �l�̉��Z
	color_.a += a;
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void ObjectBillboard::AddColorAlpha( float alpha )
{
	// �l�̉��Z
	color_.a += alpha;
}

//==============================================================================
// Brief  : �e�N�X�`�����W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR2& value			: �ݒ肷��l
//==============================================================================
void ObjectBillboard::SetPositionTexture( const D3DXVECTOR2& value )
{
	// �l�̐ݒ�
	positionTexture_ = value;
}

//==============================================================================
// Brief  : �e�N�X�`�����W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
//==============================================================================
void ObjectBillboard::SetPositionTexture( float x, float y )
{
	// �l�̐ݒ�
	positionTexture_.x = x;
	positionTexture_.y = y;
}

//==============================================================================
// Brief  : �e�N�X�`�����W��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectBillboard::SetPositionTextureX( float x )
{
	// �l�̐ݒ�
	positionTexture_.x = x;
}

//==============================================================================
// Brief  : �e�N�X�`�����W��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectBillboard::SetPositionTextureY( float y )
{
	// �l�̐ݒ�
	positionTexture_.y = y;
}

//==============================================================================
// Brief  : �e�N�X�`�����W�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR2* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void ObjectBillboard::GetPositionTexture( D3DXVECTOR2* pOut ) const
{
	// �l�̕ԋp
	*pOut = positionTexture_;
}

//==============================================================================
// Brief  : �e�N�X�`�����W��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectBillboard::GetPositionTextureX( void ) const
{
	// �l�̕ԋp
	return positionTexture_.x;
}

//==============================================================================
// Brief  : �e�N�X�`�����W��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectBillboard::GetPositionTextureY( void ) const
{
	// �l�̕ԋp
	return positionTexture_.y;
}

//==============================================================================
// Brief  : �e�N�X�`�����W�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR2& value			: ���Z����l
//==============================================================================
void ObjectBillboard::AddPositionTexture( const D3DXVECTOR2& value )
{
	// �l�̉��Z
	positionTexture_ += value;
}

//==============================================================================
// Brief  : �e�N�X�`�����W�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
//==============================================================================
void ObjectBillboard::AddPositionTexture( float x, float y )
{
	// �l�̉��Z
	positionTexture_.x += x;
	positionTexture_.y += y;
}

//==============================================================================
// Brief  : �e�N�X�`�����W��X�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectBillboard::AddPositionTextureX( float x )
{
	// �l�̉��Z
	positionTexture_.x += x;
}

//==============================================================================
// Brief  : �e�N�X�`�����W��Y�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectBillboard::AddPositionTextureY( float y )
{
	// �l�̉��Z
	positionTexture_.y += y;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR2& value			: �ݒ肷��l
//==============================================================================
void ObjectBillboard::SetScaleTexture( const D3DXVECTOR2& value )
{
	// �l�̐ݒ�
	scaleTexture_ = value;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
//==============================================================================
void ObjectBillboard::SetScaleTexture( float x, float y )
{
	// �l�̐ݒ�
	scaleTexture_.x = x;
	scaleTexture_.y = y;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectBillboard::SetScaleTextureX( float x )
{
	// �l�̐ݒ�
	scaleTexture_.x = x;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectBillboard::SetScaleTextureY( float y )
{
	// �l�̐ݒ�
	scaleTexture_.y = y;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR2* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void ObjectBillboard::GetScaleTexture( D3DXVECTOR2* pOut ) const
{
	// �l�̕ԋp
	*pOut = scaleTexture_;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectBillboard::GetScaleTextureX( void ) const
{
	// �l�̕ԋp
	return scaleTexture_.x;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectBillboard::GetScaleTextureY( void ) const
{
	// �l�̕ԋp
	return scaleTexture_.y;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR2& value			: ���Z����l
//==============================================================================
void ObjectBillboard::AddScaleTexture( const D3DXVECTOR2& value )
{
	// �l�̉��Z
	scaleTexture_ += value;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
//==============================================================================
void ObjectBillboard::AddScaleTexture( float x, float y )
{
	// �l�̉��Z
	scaleTexture_.x += x;
	scaleTexture_.y += y;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k��X�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectBillboard::AddScaleTextureX( float x )
{
	// �l�̉��Z
	scaleTexture_.x += x;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k��Y�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectBillboard::AddScaleTextureY( float y )
{
	// �l�̉��Z
	scaleTexture_.y += y;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectBillboard::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pGraphic_ = nullptr;
	color_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	positionTexture_ = D3DXVECTOR2( 0.0f, 0.0f );
	scaleTexture_ = D3DXVECTOR2( 1.0f, 1.0f );
}
