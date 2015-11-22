//==============================================================================
//
// File   : GraphicLightEffect.h
// Brief  : ���C�g�`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_LIGHT_EFFECT_H
#define MY_GRAPHIC_LIGHT_EFFECT_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicMain.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class DrawerLightEffect;
class Effect;
class EffectParameter;

//******************************************************************************
// �N���X��`
//******************************************************************************
class GraphicLightEffect : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicLightEffect( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicLightEffect( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect** ppEffectGeneral			: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDiffuseRiver		: �f�B�t���[�Y���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureSpecularRiver	: �X�y�L�������e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNormalRiver		: �@�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepthRiver		: �[�x���e�N�X�`��
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
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
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect** ppEffectGeneral			: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDiffuseRiver		: �f�B�t���[�Y���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureSpecularRiver	: �X�y�L�������e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNormalRiver		: �@�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepthRiver		: �[�x���e�N�X�`��
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
		IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth,
		IDirect3DTexture9* pTextureDiffuseRiver, IDirect3DTexture9* pTextureSpecularRiver, IDirect3DTexture9* pTextureNormalRiver, IDirect3DTexture9* pTextureDepthRiver );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicLightEffect* pOut			: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicLightEffect* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : int index							: �`��ԍ�
	//==============================================================================
	void Draw( int index );

protected:

private:
	void InitializeSelf( void );
	GraphicLightEffect( const GraphicLightEffect& );
	GraphicLightEffect operator=( const GraphicLightEffect& );

	const EffectParameter*	pParameter_;		// �G�t�F�N�g�p�����[�^
	DrawerLightEffect*		pDrawerLight_;		// ���C�g�`��N���X
};

#endif	// MY_GRAPHIC_LIGHT_EFFECT_H
