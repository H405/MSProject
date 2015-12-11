//==============================================================================
//
// File   : DrawerGrass.h
// Brief  : ���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/12/11 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_GRASS_H
#define MY_DRAWER_GRASS_H

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
class PolygonSignboard;

//******************************************************************************
// �N���X��`
//******************************************************************************
class DrawerGrass : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// �ϊ��s��
		PARAMETER_TEXTURE,					// �e�N�X�`��
		PARAMETER_VECTOR_WIND,				// ������
		PARAMETER_MAX						// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerGrass( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerGrass( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : PolygonSignboard* pPolygon			: �r���{�[�h�|���S��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	// Arg    : float hardness						: �d��
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, PolygonSignboard* pPolygon,
		IDirect3DTexture9* pTexture, float hardness );

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
	// Arg    : PolygonSignboard* pPolygon			: �r���{�[�h�|���S��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	// Arg    : float hardness						: �d��
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, PolygonSignboard* pPolygon,
		IDirect3DTexture9* pTexture, float hardness );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerGrass* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerGrass* pOut ) const;

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
	const EffectParameter*	pEffectParameter_;			// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;					// �G�t�F�N�g
	IDirect3DTexture9*		pTexture_;					// �e�N�X�`��
	PolygonSignboard*		pPolygon_;					// �|���S��
	float					hardness_;					// �d��
	D3DXVECTOR3				vectorTransform_;			// �ό`�̃x�N�g��
	D3DXVECTOR3				velocityTransform_;			// �ό`�̑��x

private:
	void InitializeSelf( void );
	DrawerGrass( const DrawerGrass& );
	DrawerGrass operator=( const DrawerGrass& );

};

#endif	// MY_DRAWER_GRASS_H
