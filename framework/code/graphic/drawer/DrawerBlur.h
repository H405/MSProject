//==============================================================================
//
// File   : DrawerBlur.h
// Brief  : �u���[�`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/10 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_BLUR_H
#define MY_DRAWER_BLUR_H

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
class DrawerBlur : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_WORLD = 0,		// ���[���h�ϊ��s��
		PARAMETER_SIZE_SCREEN_HALF,		// ��ʃT�C�Y�̔���
		PARAMETER_TEXTURE,				// �u���[���|����e�N�X�`��
		PARAMETER_OFFSET,				// �I�t�Z�b�g
		PARAMETER_MAX					// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerBlur( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerBlur( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : Polygon2D* pPolygon					: 2D�|���S��
	// Arg    : IDirect3DTexture9* pTexture			: �u���[���|����e�N�X�`��
	// Arg    : const D3DXVECTOR2& offset			: �I�t�Z�b�g
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTexture, const D3DXVECTOR2& offset );

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
	// Arg    : const D3DXVECTOR2& offset			: �I�t�Z�b�g
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTexture, const D3DXVECTOR2& offset );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerBlur* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerBlur* pOut ) const;

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
	DrawerBlur( const DrawerBlur& );
	DrawerBlur operator=( const DrawerBlur& );

};

#endif	// MY_DRAWER_BLUR_H
