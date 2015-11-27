//==============================================================================
//
// File   : DrawerDrawTexture.h
// Brief  : �f�o�b�O�e�N�X�`���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/27 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_DRAW_TEXTURE_H
#define MY_DRAWER_DRAW_TEXTURE_H

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
class DrawerDrawTexture : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_OFFSET_TEXEL = 0,		// �e�N�Z���I�t�Z�b�g
		PARAMETER_TEXTURE,				// �e�N�X�`��
		PARAMETER_MULTIPLY,				// �F�̔{��
		PARAMETER_MAX					// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerDrawTexture( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerDrawTexture( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : Polygon2D* pPolygon					: 2D�|���S��
	// Arg    : IDirect3DTexture9** pTexture		: �e�N�X�`��
	// Arg    : float* pMultiply					: �F�̔{��
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9** ppTexture, float* pMultiply );

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
	// Arg    : IDirect3DTexture9** pTexture		: �e�N�X�`��
	// Arg    : float* pMultiply					: �F�̔{��
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9** ppTexture, float* pMultiply );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerDrawTexture* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerDrawTexture* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : const D3DXMATRIX& matrixWorld		: ���[���h�}�g���N�X
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

protected:
	const EffectParameter*	pEffectParameter_;		// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;				// �G�t�F�N�g
	IDirect3DTexture9**		ppTexture_;				// �e�N�X�`��
	float*					pMultiply_;				// �F�̔{��
	Polygon2D*				pPolygon_;				// �|���S��

private:
	void InitializeSelf( void );
	DrawerDrawTexture( const DrawerDrawTexture& );
	DrawerDrawTexture operator=( const DrawerDrawTexture& );
};

#endif	// MY_DRAWER_DRAW_TEXTURE_H
