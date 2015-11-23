//==============================================================================
//
// File   : DrawerLightEffect.h
// Brief  : ���C�g�`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_LIGHT_EFFECT_H
#define MY_DRAWER_LIGHT_EFFECT_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../../framework/graphic/drawer.h"

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
class Polygon2D;

//******************************************************************************
// �N���X��`
//******************************************************************************
class DrawerLightEffect : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_OFFET_TEXEL = 0,					// �e�N�Z���I�t�Z�b�g

		PARAMETER_TEXTURE_DIFFUSE,					// �f�B�t���[�Y�e�N�X�`��
		PARAMETER_TEXTURE_SPECULAR,					// �X�y�L�����e�N�X�`��
		PARAMETER_TEXTURE_NORMAL,					// �@���e�N�X�`��
		PARAMETER_TEXTURE_DEPTH,					// �[�x�e�N�X�`��
		PARAMETER_TEXTURE_DIFFUSE_RIVER,			// ��̃f�B�t���[�Y�e�N�X�`��
		PARAMETER_TEXTURE_SPECULAR_RIVER,			// ��̃X�y�L�����e�N�X�`��
		PARAMETER_TEXTURE_NORMAL_RIVER,				// ��̖@���e�N�X�`��
		PARAMETER_TEXTURE_DEPTH_RIVER,				// ��̐[�x�e�N�X�`��

		PARAMETER_MATRIX_PROJECTION_INVERSE,		// �v���W�F�N�V�����ϊ��t�s��
		PARAMETER_MATRIX_VIEW_INVERSE,				// �r���[�ϊ��t�s��
		PARAMETER_POSITION_EYE,						// ���_���W
		PARAMETER_CLIP_CAMERA,						// �J�����̃N���b�v�l
		PARAMETER_COLOR_AMBIENT,					// �����F
		PARAMETER_VECTOR_LIGHT_DIRECTION,			// �f�B���N�V���i�����C�g�̃x�N�g��
		PARAMETER_COLOR_LIGHT_DIRECTION,			// �f�B���N�V���i�����C�g�̐F
		PARAMETER_POSITION_LIGHT_POINT,				// �|�C���g���C�g�̍��W
		PARAMETER_COLOR_LIGHT_POINT,				// �|�C���g���C�g�̐F
		PARAMETER_ATTENUATION_LIGHT_POINT,			// �|�C���g���C�g�̌�����

		PARAMETER_MAX								// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerLightEffect( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerLightEffect( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : Polygon2D* pPolygon					: 2D�|���S��
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDiffuseRiver		: �f�B�t���[�Y���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureSpecularRiver	: �X�y�L�������e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNormalRiver		: �@�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepthRiver		: �[�x���e�N�X�`��
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth,
		IDirect3DTexture9* pTextureDiffuseRiver, IDirect3DTexture9* pTextureSpecularRiver, IDirect3DTexture9* pTextureNormalRiver, IDirect3DTexture9* pTextureDepthRiver );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : Polygon2D* pPolygon					: 2D�|���S��
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDiffuseRiver		: �f�B�t���[�Y���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureSpecularRiver	: �X�y�L�������e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNormalRiver		: �@�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepthRiver		: �[�x���e�N�X�`��
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth,
		IDirect3DTexture9* pTextureDiffuseRiver, IDirect3DTexture9* pTextureSpecularRiver, IDirect3DTexture9* pTextureNormalRiver, IDirect3DTexture9* pTextureDepthRiver );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerLightEffect* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerLightEffect* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : const D3DXMATRIX& matrixWorld		: ���[���h�}�g���N�X
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetTextureDiffuse( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureDiffuse( void ) const;
	void SetTextureSpecular( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureSpecular( void ) const;
	void SetTextureNormal( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureNormal( void ) const;
	void SetTextureDepth( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureDepth( void ) const;

protected:
	const EffectParameter*	pEffectParameter_;			// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;					// �G�t�F�N�g
	IDirect3DTexture9*		pTextureDiffuse_;			// �f�B�t���[�Y���e�N�X�`��
	IDirect3DTexture9*		pTextureSpecular_;			// �X�y�L�������e�N�X�`��
	IDirect3DTexture9*		pTextureNormal_;			// �@�����e�N�X�`��
	IDirect3DTexture9*		pTextureDepth_;				// �[�x���e�N�X�`��
	IDirect3DTexture9*		pTextureDiffuseRiver_;		// �f�B�t���[�Y���e�N�X�`��
	IDirect3DTexture9*		pTextureSpecularRiver_;		// �X�y�L�������e�N�X�`��
	IDirect3DTexture9*		pTextureNormalRiver_;		// �@�����e�N�X�`��
	IDirect3DTexture9*		pTextureDepthRiver_;		// �[�x���e�N�X�`��
	Polygon2D*				pPolygon_;					// �|���S��

private:
	void InitializeSelf( void );
	DrawerLightEffect( const DrawerLightEffect& );
	DrawerLightEffect operator=( const DrawerLightEffect& );

};

#endif	// MY_DRAWER_LIGHT_EFFECT_H
