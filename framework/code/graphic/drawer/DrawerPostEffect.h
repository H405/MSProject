//==============================================================================
//
// File   : DrawerPostEffect.h
// Brief  : ��ʃ|���S���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_POST_EFFECT_H
#define MY_DRAWER_POST_EFFECT_H

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
class DrawerPostEffect : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_WORLD = 0,			// ���[���h�}�g���N�X
		PARAMETER_TEXTURE,					// �e�N�X�`��
		PARAMETER_TEXTURE_3D,				// 3D�`��e�N�X�`��
		PARAMETER_TEXTURE_2D,				// 2D�`��e�N�X�`��
		PARAMETER_TEXTURE_MASK,				// �}�X�N�e�N�X�`��
		PARAMETER_COLOR_FADE,				// �t�F�[�h�̐F
		PARAMETER_WIDTH_SCREEN_HALF,		// ��ʕ��̔���
		PARAMETER_HEIGHT_SCREEN_HALF,		// ��ʍ����̔���
		PARAMETER_PROPORTION_FADE,			// �t�F�[�h�̊���
		PARAMETER_MAX						// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerPostEffect( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerPostEffect( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : Polygon2D* pPolygon					: ��ʃ|���S��
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture2D		: 2D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	// Arg    : const D3DXCOLOR* pColorFade			: �t�F�[�h�̐F
	// Arg    : const float* pProportionFade		: �t�F�[�h�̊���
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture,
		const D3DXCOLOR* pColorFade, const float* pProportionFade );

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
	// Arg    : Polygon2D* pPolygon					: ��ʃ|���S��
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture2D		: 2D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	// Arg    : const D3DXCOLOR* pColorFade			: �t�F�[�h�̐F
	// Arg    : const float* pProportionFade		: �t�F�[�h�̊���
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture,
		const D3DXCOLOR* pColorFade, const float* pProportionFade );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerPostEffect* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerPostEffect* pOut ) const;

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
	void SetPolygon( Polygon2D* pValue );
	Polygon2D* GetPolygon( void ) const;

protected:
	const EffectParameter*	pEffectParameter_;		// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;				// �G�t�F�N�g
	IDirect3DTexture9*		pTexture_;				// �e�N�X�`��
	IDirect3DTexture9*		pTexture3D_;			// 3D�`��e�N�X�`��
	IDirect3DTexture9*		pTexture2D_;			// 2D�`��e�N�X�`��
	IDirect3DTexture9*		pTextureMask_;			// �}�X�N�e�N�X�`��
	Polygon2D*				pPolygon_;				// �|���S��
	const D3DXCOLOR*		pColorFade_;			// �t�F�[�h�F
	const float*			pProportionFade_;		// �t�F�[�h����

private:
	void InitializeSelf( void );
	DrawerPostEffect( const DrawerPostEffect& );
	DrawerPostEffect operator=( const DrawerPostEffect& );

};

#endif	// MY_DRAWER_POST_EFFECT_H
