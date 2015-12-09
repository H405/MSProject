//==============================================================================
//
// File   : DrawerShadow.h
// Brief  : ���C�g�`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_SHADOW_H
#define MY_DRAWER_SHADOW_H

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
class DrawerShadow : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_OFFET_TEXEL = 0,					// �e�N�Z���I�t�Z�b�g

		PARAMETER_MATRIX_PROJECTION_INVERSE,		// �v���W�F�N�V�����ϊ��t�s��
		PARAMETER_MATRIX_VIEW_INVERSE,				// �r���[�ϊ��t�s��
		PARAMETER_TEXTURE_DEPTH,					// �[�x�e�N�X�`��

		PARAMETER_POSITION_LOOK_AT_LIGHT,			// ���s�����̒����_

		PARAMETER_MATRIX_TRANSFORM_LIGHT_NEAR,		// ���s����(��)�̕ϊ��s��
		PARAMETER_MATRIX_VIEW_LIGHT_NEAR,			// ���s����(��)�̃r���[�ϊ��s��
		PARAMETER_TEXTURE_DEPTH_LIGHT_NEAR,			// ���s����(��)�̐[�x�e�N�X�`��
		PARAMETER_CLIP_FAR_LIGHT_NEAR,				// ���s����(��)�̃t�@�[�N���b�v��

		PARAMETER_MATRIX_TRANSFORM_LIGHT_FAR,		// ���s����(��)�̕ϊ��s��
		PARAMETER_MATRIX_VIEW_LIGHT_FAR,			// ���s����(��)�̃r���[�ϊ��s��
		PARAMETER_TEXTURE_DEPTH_LIGHT_FAR,			// ���s����(��)�̐[�x�e�N�X�`��
		PARAMETER_CLIP_FAR_LIGHT_FAR,				// ���s����(��)�̃t�@�[�N���b�v��

		PARAMETER_MATRIX_VIEW_LIGHT_POINT,			// �_�����̃r���[�ϊ��s��
		PARAMETER_TEXTURE_DEPTH_LIGHT_POINT,		// �_�����̐[�x�e�N�X�`��
		PARAMETER_CLIP_FAR_LIGHT_POINT,				// �_�����̃t�@�[�N���b�v��
		PARAMETER_ATTENUATION_LIGHT_POINT,			// �_�����̌�����

		PARAMETER_MAX								// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerShadow( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerShadow( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : Polygon2D* pPolygon					: 2D�|���S��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureLightNear	: ���s����(��)�̐[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureLightFar		: ���s����(��)�̐[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureLightPoint	: �_�����̐[�x���e�N�X�`��
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint );

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
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureLightNear	: ���s����(��)�̐[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureLightFar		: ���s����(��)�̐[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureLightPoint	: �_�����̐[�x���e�N�X�`��
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerShadow* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerShadow* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : const D3DXMATRIX& matrixWorld		: ���[���h�}�g���N�X
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

protected:
	const EffectParameter*	pEffectParameter_;			// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;					// �G�t�F�N�g
	IDirect3DTexture9*		pTextureDepth_;				// �[�x���e�N�X�`��
	IDirect3DTexture9*		pTextureLightNear_;			// ���s����(��)�̐[�x���e�N�X�`��
	IDirect3DTexture9*		pTextureLightFar_;			// ���s����(��)�̐[�x���e�N�X�`��
	IDirect3DTexture9*		pTextureLightPoint_;		// �_�����̐[�x���e�N�X�`��
	Polygon2D*				pPolygon_;					// �|���S��

private:
	void InitializeSelf( void );
	DrawerShadow( const DrawerShadow& );
	DrawerShadow operator=( const DrawerShadow& );

};

#endif	// MY_DRAWER_SHADOW_H
