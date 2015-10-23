//==============================================================================
//
// File   : DrawerSky.h
// Brief  : ��`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_SKY_H
#define MY_DRAWER_SKY_H

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
class PolygonMeshDomeInside;

//******************************************************************************
// �N���X��`
//******************************************************************************
class DrawerSky : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// �ϊ��s��
		PARAMETER_TEXTURE,					// �e�N�X�`��
		PARAMETER_MAX						// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerSky( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerSky( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : PolygonMeshDomeInside* pPolygon		: �������b�V���h�[���|���S��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMeshDomeInside* pPolygon, IDirect3DTexture9* pTexture );

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
	// Arg    : PolygonMeshDomeInside* pPolygon		: �������b�V���h�[���|���S��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMeshDomeInside* pPolygon, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerSky* pOut						: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerSky* pOut ) const;

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
	PolygonMeshDomeInside*	pPolygon_;				// �|���S��

private:
	void InitializeSelf( void );
	DrawerSky( const DrawerSky& );
	DrawerSky operator=( const DrawerSky& );

};

#endif	// MY_DRAWER_SKY_H
