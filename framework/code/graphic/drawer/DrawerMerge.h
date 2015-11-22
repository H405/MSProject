//==============================================================================
//
// File   : DrawerMerge.h
// Brief  : ����3D�`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_MERGE_H
#define MY_DRAWER_MERGE_H

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
class DrawerMerge : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_WORLD = 0,			// ���[���h�ϊ��s��
		PARAMETER_SIZE_SCREEN_HALF,			// ��ʃT�C�Y�̔���

		PARAMETER_FORCUS,					// �œ_����

		PARAMETER_TEXTURE_LIGHT,			// ���C�g����e�N�X�`��
		PARAMETER_TEXTURE_NOT_LIGHT,		// ���C�g�Ȃ��e�N�X�`��
		PARAMETER_TEXTURE_MASK,				// �}�X�N�e�N�X�`��
		PARAMETER_TEXTURE_ADD,				// ���Z�����e�N�X�`��
		PARAMETER_TEXTURE_DEPTH,			// �[�x�e�N�X�`��

		PARAMETER_MAX						// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerMerge( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerMerge( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : Polygon2D* pPolygon					: 2D�|���S��
	// Arg    : IDirect3DTexture9* pTextureLight	: ���C�g����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNotLight	: ���C�g�Ȃ��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureAdd		: ���Z�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask,
		IDirect3DTexture9* pTextureAdd, IDirect3DTexture9* pTextureDepth );

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
	// Arg    : IDirect3DTexture9* pTextureLight	: ���C�g����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNotLight	: ���C�g�Ȃ��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureAdd		: ���Z�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask,
		IDirect3DTexture9* pTextureAdd, IDirect3DTexture9* pTextureDepth );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerMerge* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerMerge* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : const D3DXMATRIX& matrixWorld		: ���[���h�}�g���N�X
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetTextureLight( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureLight( void ) const;
	void SetTextureNotLight( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureNotLight( void ) const;
	void SetTextureMask( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureMask( void ) const;

protected:
	const EffectParameter*	pEffectParameter_;			// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;					// �G�t�F�N�g
	IDirect3DTexture9*		pTextureLight_;				// ���C�g����e�N�X�`��
	IDirect3DTexture9*		pTextureNotLight_;			// ���C�g�Ȃ��e�N�X�`��
	IDirect3DTexture9*		pTextureMask_;				// �}�X�N�e�N�X�`��
	IDirect3DTexture9*		pTextureAdd_;				// ���Z�����e�N�X�`��
	IDirect3DTexture9*		pTextureDepth_;				// �[�x�e�N�X�`��
	Polygon2D*				pPolygon_;					// �|���S��

private:
	void InitializeSelf( void );
	DrawerMerge( const DrawerMerge& );
	DrawerMerge operator=( const DrawerMerge& );
};

#endif	// MY_DRAWER_MERGE_H
