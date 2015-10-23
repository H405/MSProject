//==============================================================================
//
// File   : Object2D.h
// Brief  : 2D�|���S���I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_2D_H
#define MY_OBJECT_2D_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../framework/object/ObjectMovement.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Effect;
class EffectParameter;
class Graphic2D;
class Texture;

//******************************************************************************
// �N���X��`
//******************************************************************************
class Object2D : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	Object2D( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~Object2D( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	//==============================================================================
	int Initialize( int priority );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	//==============================================================================
	int Reinitialize( int priority );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : Object2D* pOut						: �R�s�[��A�h���X
	//==============================================================================
	int Copy( Object2D* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : �`��N���X�̐���
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : Texture* pTexture					: �e�N�X�`��
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture = nullptr );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetGraphic( Graphic2D* pValue );
	Graphic2D* GetGraphic( void ) const;
	void SetColor( const D3DXCOLOR& value );
	void SetColor( float r, float g, float b, float a );
	void SetColor( float r, float g, float b );
	void SetColorR( float r );
	void SetColorG( float g );
	void SetColorB( float b );
	void SetColorA( float a );
	void SetColorAlpha( float alpha );
	void GetColor( D3DXCOLOR* pOut ) const;
	float GetColorR( void ) const;
	float GetColorG( void ) const;
	float GetColorB( void ) const;
	float GetColorA( void ) const;
	void AddColor( const D3DXCOLOR& value );
	void AddColor( float r, float g, float b, float a );
	void AddColor( float r, float g, float b );
	void AddColorR( float r );
	void AddColorG( float g );
	void AddColorB( float b );
	void AddColorA( float a );
	void AddColorAlpha( float alpha );
	void SetPositionTexture( const D3DXVECTOR2& value );
	void SetPositionTexture( float x, float y );
	void SetPositionTextureX( float x );
	void SetPositionTextureY( float y );
	void GetPositionTexture( D3DXVECTOR2* pOut ) const;
	float GetPositionTextureX( void ) const;
	float GetPositionTextureY( void ) const;
	void AddPositionTexture( const D3DXVECTOR2& value );
	void AddPositionTexture( float x, float y );
	void AddPositionTextureX( float x );
	void AddPositionTextureY( float y );
	void SetScaleTexture( const D3DXVECTOR2& value );
	void SetScaleTexture( float x, float y );
	void SetScaleTextureX( float x );
	void SetScaleTextureY( float y );
	void GetScaleTexture( D3DXVECTOR2* pOut ) const;
	float GetScaleTextureX( void ) const;
	float GetScaleTextureY( void ) const;
	void AddScaleTexture( const D3DXVECTOR2& value );
	void AddScaleTexture( float x, float y );
	void AddScaleTextureX( float x );
	void AddScaleTextureY( float y );

protected:
	Graphic2D*	pGraphic_;				// �`��N���X
	D3DXCOLOR	color_;					// �F
	D3DXVECTOR2	positionTexture_;		// �e�N�X�`�����W
	D3DXVECTOR2	scaleTexture_;			// �e�N�X�`���g�k

private:
	void InitializeSelf( void );
	Object2D( const Object2D& );
	Object2D operator=( const Object2D& );
};

#endif	// MY_OBJECT_2D_H
