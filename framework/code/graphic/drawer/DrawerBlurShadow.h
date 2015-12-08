//==============================================================================
//
// File   : DrawerBlurShadow.h
// Brief  : �e�p�u���[�`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/12/08 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_BLUR_SHADOW_H
#define MY_DRAWER_BLUR_SHADOW_H

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
class DrawerBlurShadow : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_OFFET_TEXEL = 0,		// �e�N�Z���I�t�Z�b�g
		PARAMETER_TEXTURE,				// �u���[���|����e�N�X�`��
		PARAMETER_MAX					// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerBlurShadow( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerBlurShadow( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : Polygon2D* pPolygon					: 2D�|���S��
	// Arg    : IDirect3DTexture9* pTexture			: �u���[���|����e�N�X�`��
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTexture );

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
	// Arg    : IDirect3DTexture9* pTexture			: �u���[���|����e�N�X�`��
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerBlurShadow* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerBlurShadow* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : const D3DXMATRIX& matrixWorld		: ���[���h�}�g���N�X
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetTexture( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTexture( void ) const;

protected:
	const EffectParameter*	pEffectParameter_;		// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;				// �G�t�F�N�g
	IDirect3DTexture9*		pTexture_;				// �u���[���|����e�N�X�`��
	Polygon2D*				pPolygon_;				// �|���S��

private:
	void InitializeSelf( void );
	DrawerBlurShadow( const DrawerBlurShadow& );
	DrawerBlurShadow operator=( const DrawerBlurShadow& );

};

#endif	// MY_DRAWER_BLUR_SHADOW_H
