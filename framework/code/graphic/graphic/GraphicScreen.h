//==============================================================================
//
// File   : GraphicScreen.h
// Brief  : ��ʃ|���S���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_SCREEN_H
#define MY_GRAPHIC_SCREEN_H

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
class GraphicScreen : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicScreen( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicScreen( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : const float* pProportionFade		: �t�F�[�h����
	// Arg    : IDirect3DTexture9* pTextureGeneral	: �ʏ�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, const float* pProportionFade,
		IDirect3DTexture9* pTextureGeneral, IDirect3DTexture9* pTexture = nullptr );

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
	// Arg    : IDirect3DTexture9* pTextureGeneral	: �ʏ�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, const float* pProportionFade,
		IDirect3DTexture9* pTextureGeneral, IDirect3DTexture9* pTexture = nullptr );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicScreen* pOut						: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicScreen* pOut ) const;

protected:
	IDirect3DTexture9*	pTexture_;			// �e�N�X�`��
	D3DXCOLOR			colorFade_;			// �t�F�[�h�F

private:
	void InitializeSelf( void );
	GraphicScreen( const GraphicScreen& );
	GraphicScreen operator=( const GraphicScreen& );
};

#endif	// MY_GRAPHIC_SCREEN_H
