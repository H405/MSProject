//==============================================================================
//
// File   : DrawerBillboard.h
// Brief  : �r���{�[�h�|���S���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/23 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_BILLBOARD_H
#define MY_DRAWER_BILLBOARD_H

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
class Polygon3D;

//******************************************************************************
// �N���X��`
//******************************************************************************
class DrawerBillboard : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// �ϊ��s��
		PARAMETER_TEXTURE,					// �e�N�X�`��
		PARAMETER_COLOR,					// �F
		PARAMETER_POSITION_TEXTURE,			// �e�N�X�`�����W
		PARAMETER_SCALE_TEXTURE,			// �e�N�X�`���g�k
		PARAMETER_MAX						// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerBillboard( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerBillboard( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : Polygon3D* pPolygon					: �r���{�[�h�|���S��
	// Arg    : D3DXCOLOR* pColor					: �F
	// Arg    : D3DXVECTOR2* pPositionTexture		: �e�N�X�`�����W
	// Arg    : D3DXVECTOR2* pScaleTexture			: �e�N�X�`���g�k
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon3D* pPolygon,
		D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture );

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
	// Arg    : Polygon3D* pPolygon					: �r���{�[�h�|���S��
	// Arg    : D3DXCOLOR* pColor					: �F
	// Arg    : D3DXVECTOR2* pPositionTexture		: �e�N�X�`�����W
	// Arg    : D3DXVECTOR2* pScaleTexture			: �e�N�X�`���g�k
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon3D* pPolygon,
		D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerBillboard* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerBillboard* pOut ) const;

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
	IDirect3DTexture9*		pTexture_;				// �e�N�X�`��
	Polygon3D*				pPolygon_;				// �|���S��
	D3DXCOLOR*				pColor_;				// �F
	D3DXVECTOR2*			pPositionTexture_;		// �e�N�X�`�����W
	D3DXVECTOR2*			pScaleTexture_;			// �e�N�X�`���g�k

private:
	void InitializeSelf( void );
	DrawerBillboard( const DrawerBillboard& );
	DrawerBillboard operator=( const DrawerBillboard& );

};

#endif	// MY_DRAWER_BILLBOARD_H
