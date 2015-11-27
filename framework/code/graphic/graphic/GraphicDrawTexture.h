//==============================================================================
//
// File   : GraphicDrawTexture.h
// Brief  : �f�o�b�O�e�N�X�`���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/27 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_DRAW_TEXTURE_H
#define MY_GRAPHIC_DRAW_TEXTURE_H

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
class EffectParameter;
class Effect;

//******************************************************************************
// �N���X��`
//******************************************************************************
class GraphicDrawTexture : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicDrawTexture( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicDrawTexture( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9** pTexture		: �e�N�X�`��
	// Arg    : float* pMultiply					: �F�̔{��
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9** ppTexture, float* pMultiply );

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
	// Arg    : IDirect3DTexture9** pTexture		: �e�N�X�`��
	// Arg    : float* pMultiply					: �F�̔{��
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9** ppTexture, float* pMultiply );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicDrawTexture* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicDrawTexture* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicDrawTexture( const GraphicDrawTexture& );
	GraphicDrawTexture operator=( const GraphicDrawTexture& );

};

#endif	// MY_GRAPHIC_DRAW_TEXTURE_H
