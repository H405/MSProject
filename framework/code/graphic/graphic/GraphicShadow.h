//==============================================================================
//
// File   : GraphicShadow.h
// Brief  : ���C�g�`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_SHADOW_H
#define MY_GRAPHIC_SHADOW_H

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
class DrawerShadow;
class Effect;
class EffectParameter;

//******************************************************************************
// �N���X��`
//******************************************************************************
class GraphicShadow : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicShadow( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicShadow( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureLight	: ���C�g�̐[�x���e�N�X�`��
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLight );

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
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureLight	: ���C�g�̐[�x���e�N�X�`��
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLight );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicShadow* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicShadow* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicShadow( const GraphicShadow& );
	GraphicShadow operator=( const GraphicShadow& );

	const EffectParameter*	pParameter_;		// �G�t�F�N�g�p�����[�^
	DrawerShadow*		pDrawerLight_;		// ���C�g�`��N���X
};

#endif	// MY_GRAPHIC_SHADOW_H
