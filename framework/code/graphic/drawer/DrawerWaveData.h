//==============================================================================
//
// File   : DrawerWaveData.h
// Brief  : �g���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_WAVE_DATA_H
#define MY_DRAWER_WAVE_DATA_H

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
class DrawerWaveData : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_WORLD = 0,		// ���[���h�ϊ��s��
		PARAMETER_TEXTURE_HEIGHT,		// �����e�N�X�`��
		PARAMETER_WAVE_ADD,				// �g�ǉ����
		PARAMETER_MAX					// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerWaveData( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerWaveData( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : Polygon2D* pPolygon					: 2D�|���S��
	// Arg    : IDirect3DTexture9* pTextureHeight0	: �����e�N�X�`��0
	// Arg    : IDirect3DTexture9* pTextureHeight1	: �����e�N�X�`��1
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 );

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
	// Arg    : IDirect3DTexture9* pTextureHeight0	: �����e�N�X�`��0
	// Arg    : IDirect3DTexture9* pTextureHeight1	: �����e�N�X�`��1
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerWaveData* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerWaveData* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : const D3DXMATRIX& matrixWorld		: ���[���h�}�g���N�X
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

protected:
	const EffectParameter*	pEffectParameter_;		// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;				// �G�t�F�N�g
	IDirect3DTexture9*		pTextureHeight0_;		// �����e�N�X�`��0
	IDirect3DTexture9*		pTextureHeight1_;		// �����e�N�X�`��1
	Polygon2D*				pPolygon_;				// �|���S��
	bool					isTexture0_;			// �e�N�X�`��0�t���O

private:
	void InitializeSelf( void );
	DrawerWaveData( const DrawerWaveData& );
	DrawerWaveData operator=( const DrawerWaveData& );

};

#endif	// MY_DRAWER_WAVE_DATA_H
