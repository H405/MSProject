//==============================================================================
//
// File   : Object2D.cpp
// Brief  : 2D�|���S���I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Object2D.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/Graphic2D.h"

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
Object2D::Object2D( void ) : ObjectMovement()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Object2D::~Object2D( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int Object2D::Initialize( int priority )
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
int Object2D::Finalize( void )
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
int Object2D::Reinitialize( int priority )
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
// Arg    : Object2D* pOut						: �R�s�[��A�h���X
//==============================================================================
int Object2D::Copy( Object2D* pOut ) const
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
void Object2D::Update( void )
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
int Object2D::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture )
{
	// �O���t�B�b�N�̐���
	int					result;				// ���s����
	IDirect3DTexture9*	pTextureSet;		// �ݒ肷��e�N�X�`��
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}
	pGraphic_ = new Graphic2D();
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
// Arg    : Graphic2D* pValue						: �ݒ肷��l
//==============================================================================
void Object2D::SetGraphic( Graphic2D* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : Graphic2D*							: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
Graphic2D* Object2D::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : �F�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: �ݒ肷��l
//==============================================================================
void Object2D::SetColor( const D3DXCOLOR& value )
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
void Object2D::SetColor( float r, float g, float b, float a )
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
void Object2D::SetColor( float r, float g, float b )
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
void Object2D::SetColorR( float r )
{
	// �l�̐ݒ�
	color_.r = r;
}

//==============================================================================
// Brief  : �F��G�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void Object2D::SetColorG( float g )
{
	// �l�̐ݒ�
	color_.g = g;
}

//==============================================================================
// Brief  : �F��B�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void Object2D::SetColorB( float b )
{
	// �l�̐ݒ�
	color_.b = b;
}

//==============================================================================
// Brief  : �F��A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void Object2D::SetColorA( float a )
{
	// �l�̐ݒ�
	color_.a = a;
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void Object2D::SetColorAlpha( float alpha )
{
	// �l�̐ݒ�
	color_.a = alpha;
}

//==============================================================================
// Brief  : �F�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXCOLOR* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void Object2D::GetColor( D3DXCOLOR* pOut ) const
{
	// �l�̕ԋp
	*pOut = color_;
}

//==============================================================================
// Brief  : �F��R�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object2D::GetColorR( void ) const
{
	// �l�̕ԋp
	return color_.r;
}

//==============================================================================
// Brief  : �F��G�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object2D::GetColorG( void ) const
{
	// �l�̕ԋp
	return color_.g;
}

//==============================================================================
// Brief  : �F��B�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object2D::GetColorB( void ) const
{
	// �l�̕ԋp
	return color_.b;
}

//==============================================================================
// Brief  : �F��A�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object2D::GetColorA( void ) const
{
	// �l�̕ԋp
	return color_.a;
}

//==============================================================================
// Brief  : �F�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: ���Z����l
//==============================================================================
void Object2D::AddColor( const D3DXCOLOR& value )
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
void Object2D::AddColor( float r, float g, float b, float a )
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
void Object2D::AddColor( float r, float g, float b )
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
void Object2D::AddColorR( float r )
{
	// �l�̉��Z
	color_.r += r;
}

//==============================================================================
// Brief  : �F��G�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void Object2D::AddColorG( float g )
{
	// �l�̉��Z
	color_.g += g;
}

//==============================================================================
// Brief  : �F��B�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void Object2D::AddColorB( float b )
{
	// �l�̉��Z
	color_.b += b;
}

//==============================================================================
// Brief  : �F��A�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void Object2D::AddColorA( float a )
{
	// �l�̉��Z
	color_.a += a;
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void Object2D::AddColorAlpha( float alpha )
{
	// �l�̉��Z
	color_.a += alpha;
}

//==============================================================================
// Brief  : �e�N�X�`�����W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR2& value			: �ݒ肷��l
//==============================================================================
void Object2D::SetPositionTexture( const D3DXVECTOR2& value )
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
void Object2D::SetPositionTexture( float x, float y )
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
void Object2D::SetPositionTextureX( float x )
{
	// �l�̐ݒ�
	positionTexture_.x = x;
}

//==============================================================================
// Brief  : �e�N�X�`�����W��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Object2D::SetPositionTextureY( float y )
{
	// �l�̐ݒ�
	positionTexture_.y = y;
}

//==============================================================================
// Brief  : �e�N�X�`�����W�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR2* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Object2D::GetPositionTexture( D3DXVECTOR2* pOut ) const
{
	// �l�̕ԋp
	*pOut = positionTexture_;
}

//==============================================================================
// Brief  : �e�N�X�`�����W��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object2D::GetPositionTextureX( void ) const
{
	// �l�̕ԋp
	return positionTexture_.x;
}

//==============================================================================
// Brief  : �e�N�X�`�����W��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object2D::GetPositionTextureY( void ) const
{
	// �l�̕ԋp
	return positionTexture_.y;
}

//==============================================================================
// Brief  : �e�N�X�`�����W�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR2& value			: ���Z����l
//==============================================================================
void Object2D::AddPositionTexture( const D3DXVECTOR2& value )
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
void Object2D::AddPositionTexture( float x, float y )
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
void Object2D::AddPositionTextureX( float x )
{
	// �l�̉��Z
	positionTexture_.x += x;
}

//==============================================================================
// Brief  : �e�N�X�`�����W��Y�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Object2D::AddPositionTextureY( float y )
{
	// �l�̉��Z
	positionTexture_.y += y;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR2& value			: �ݒ肷��l
//==============================================================================
void Object2D::SetScaleTexture( const D3DXVECTOR2& value )
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
void Object2D::SetScaleTexture( float x, float y )
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
void Object2D::SetScaleTextureX( float x )
{
	// �l�̐ݒ�
	scaleTexture_.x = x;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Object2D::SetScaleTextureY( float y )
{
	// �l�̐ݒ�
	scaleTexture_.y = y;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR2* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Object2D::GetScaleTexture( D3DXVECTOR2* pOut ) const
{
	// �l�̕ԋp
	*pOut = scaleTexture_;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object2D::GetScaleTextureX( void ) const
{
	// �l�̕ԋp
	return scaleTexture_.x;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object2D::GetScaleTextureY( void ) const
{
	// �l�̕ԋp
	return scaleTexture_.y;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR2& value			: ���Z����l
//==============================================================================
void Object2D::AddScaleTexture( const D3DXVECTOR2& value )
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
void Object2D::AddScaleTexture( float x, float y )
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
void Object2D::AddScaleTextureX( float x )
{
	// �l�̉��Z
	scaleTexture_.x += x;
}

//==============================================================================
// Brief  : �e�N�X�`���g�k��Y�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Object2D::AddScaleTextureY( float y )
{
	// �l�̉��Z
	scaleTexture_.y += y;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Object2D::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pGraphic_ = nullptr;
	color_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	positionTexture_ = D3DXVECTOR2( 0.0f, 0.0f );
	scaleTexture_ = D3DXVECTOR2( 1.0f, 1.0f );
}
