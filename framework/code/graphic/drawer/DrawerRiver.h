//==============================================================================
//
// File   : DrawerRiver.h
// Brief  : ��`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_RIVER_H
#define MY_DRAWER_RIVER_H

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
class Model;

//******************************************************************************
// �N���X��`
//******************************************************************************
class DrawerRiver : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,					// �ϊ��s��
		PARAMETER_MATRIX_WORLD,							// ���[���h�ϊ��s��
		PARAMETER_MATRIX_WORLD_VIEW,					// ���[���h�r���[�ϊ��s��
		PARAMETER_MATRIX_TRANSFORM_TEXTURE,				// �e�N�X�`�����W�ϊ��s��

		PARAMETER_MATRIX_WORLD_INVERSE_TRANSPOSE,		// ���[���h�t�]�u�s��
		PARAMETER_TEXTURE_NORMAL,						// �@���e�N�X�`��
		PARAMETER_COLOR_DIFFUSE,						// �f�B�t���[�Y�F
		PARAMETER_COLOR_SPECULAR,						// �X�y�L�����F
		PARAMETER_REFLECTION,							// ���˗�
		PARAMETER_POWER,								// ���˂̋���
		PARAMETER_REFLACTIVE,							// ���ܗ�

		PARAMETER_TEXTURE_REFLECT,						// ���˃e�N�X�`��
		PARAMETER_TEXTURE_REFLECT_NOT_LIGHT,			// ���˃��C�e�B���O�Ȃ��e�N�X�`��
		PARAMETER_TEXTURE_REFLECT_ADD,					// ���ˉ��Z�����e�N�X�`��
		PARAMETER_TEXTURE_3D,							// 3D�`��e�N�X�`��
		PARAMETER_TEXTURE_DEPTH,						// �[�x�e�N�X�`��

		PARAMETER_POSITION_EYE,							// ���_���W
		PARAMETER_CLIP_CAMERA,							// �J�����̃N���b�v�l

		PARAMETER_MAX									// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerRiver( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerRiver( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : Model* pModel						: ���f��
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureNormal	: �@���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureReflect	: ���˃e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: ���˃��C�e�B���O�Ȃ��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureReflectAdd		: ���ˉ��Z�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
	//==============================================================================
	int Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTextureNormal,
		IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : Model* pModel						: ���f��
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureNormal	: �@���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureReflect	: ���˃e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: ���˃��C�e�B���O�Ȃ��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureReflectAdd		: ���ˉ��Z�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
	//==============================================================================
	int Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTextureNormal,
		IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerRiver* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerRiver* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : const D3DXMATRIX& matrixWorld		: ���[���h�}�g���N�X
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetModel( Model* pValue );
	Model* GetModel( void ) const;

protected:
	const EffectParameter*	pEffectParameter_;				// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;						// �G�t�F�N�g
	Model*					pModel_;						// ���f��
	IDirect3DTexture9*		pTextureNormal_;				// �@���e�N�X�`��
	IDirect3DTexture9*		pTextureReflect_;				// ���˃e�N�X�`��
	IDirect3DTexture9*		pTextureReflectNotLight_;		// ���˃��C�e�B���O�Ȃ��e�N�X�`��
	IDirect3DTexture9*		pTextureReflectAdd_;			// ���ˉ��Z�����e�N�X�`��
	IDirect3DTexture9*		pTexture3D_;					// 3D�`��e�N�X�`��
	IDirect3DTexture9*		pTextureDepth_;					// �[�x�e�N�X�`��

private:
	void InitializeSelf( void );
	DrawerRiver( const DrawerRiver& );
	DrawerRiver operator=( const DrawerRiver& );
};

#endif	// MY_DRAWER_RIVER_H
