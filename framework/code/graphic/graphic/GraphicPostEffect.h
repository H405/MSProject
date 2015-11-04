//==============================================================================
//
// File   : GraphicPostEffect.h
// Brief  : ��ʃ|���S���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_POST_EFFECT_H
#define MY_GRAPHIC_POST_EFFECT_H

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
class Effect;
class EffectParameter;

//******************************************************************************
// �N���X��`
//******************************************************************************
class GraphicPostEffect : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicPostEffect( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicPostEffect( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : const float* pProportionFade		: �t�F�[�h����
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture2D		: 2D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, const float* pProportionFade,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture = nullptr );

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
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : const float* pProportionFade		: �t�F�[�h����
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture2D		: 2D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, const float* pProportionFade,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture = nullptr );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicPostEffect* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicPostEffect* pOut ) const;

protected:
	IDirect3DTexture9*	pTexture_;			// �e�N�X�`��
	D3DXCOLOR			colorFade_;			// �t�F�[�h�F

private:
	void InitializeSelf( void );
	GraphicPostEffect( const GraphicPostEffect& );
	GraphicPostEffect operator=( const GraphicPostEffect& );
};

#endif	// MY_GRAPHIC_POST_EFFECT_H
