//==============================================================================
//
// File   : GraphicMerge.h
// Brief  : ����3D�`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_MERGE_H
#define MY_GRAPHIC_MERGE_H

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
class GraphicMerge : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicMerge( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicMerge( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureLight	: ���C�g����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNotLight	: ���C�g�Ȃ��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureAdd		: ���Z�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureRiver	: ��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepthRiver	: ��̐[�x�e�N�X�`��
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureRiver, IDirect3DTexture9* pTextureDepthRiver );

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
	// Arg    : IDirect3DTexture9* pTextureLight	: ���C�g����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNotLight	: ���C�g�Ȃ��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureAdd		: ���Z�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureRiver	: ��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepthRiver	: ��̐[�x�e�N�X�`��
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureRiver, IDirect3DTexture9* pTextureDepthRiver );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicMerge* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicMerge* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicMerge( const GraphicMerge& );
	GraphicMerge operator=( const GraphicMerge& );

};

#endif	// MY_GRAPHIC_MERGE_H
