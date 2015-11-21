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

		PARAMETER_MATRIX_WORLD_INVERSE_TRANSPOSE,		// ���[���h�t�]�u�s��
		PARAMETER_TEXTURE_NORMAL,						// �@���e�N�X�`��
		PARAMETER_COLOR_DIFFUSE,						// �f�B�t���[�Y�F
		PARAMETER_COLOR_SPECULAR,						// �X�y�L�����F
		PARAMETER_REFLECTION,							// ���˗�
		PARAMETER_POWER,								// ���˂̋���
		PARAMETER_REFLACTIVE,							// ���ܗ�

		PARAMETER_TEXTURE_ENVIRONMENT_FRONT,			// ���ʊ��e�N�X�`��
		PARAMETER_TEXTURE_ENVIRONMENT_BACK,				// �w�ʊ��e�N�X�`��
		PARAMETER_TEXTURE_ENVIRONMENT_ADD_FRONT,		// ���ʉ��Z���e�N�X�`��
		PARAMETER_TEXTURE_ENVIRONMENT_ADD_BACK,			// �w�ʉ��Z���e�N�X�`��

		PARAMETER_POSITION_EYE,							// ���_���W
		PARAMETER_CLIP_CAMERA,							// �J�����̃N���b�v�l
		PARAMETER_COLOR_AMBIENT,						// �����F
		PARAMETER_VECTOR_LIGHT_DIRECTION,				// �f�B���N�V���i�����C�g�̃x�N�g��
		PARAMETER_COLOR_LIGHT_DIRECTION,				// �f�B���N�V���i�����C�g�̐F
		PARAMETER_POSITION_LIGHT_POINT,					// �|�C���g���C�g�̍��W
		PARAMETER_COLOR_LIGHT_POINT,					// �|�C���g���C�g�̐F
		PARAMETER_ATTENUATION_LIGHT_POINT,				// �|�C���g���C�g�̌�����

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
	// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: ���ʊ��}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: �w�ʊ��}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: ���ʉ��Z���}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: �w�ʉ��Z���}�b�v�e�N�X�`��
	//==============================================================================
	int Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect,
		IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
		IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack );

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
	// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: ���ʊ��}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: �w�ʊ��}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: ���ʉ��Z���}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: �w�ʉ��Z���}�b�v�e�N�X�`��
	//==============================================================================
	int Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect,
		IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
		IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack );

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
	const EffectParameter*	pEffectParameter_;					// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;							// �G�t�F�N�g
	Model*					pModel_;							// ���f��
	IDirect3DTexture9*		pTextureNormal_;					// �@���e�N�X�`��
	IDirect3DTexture9*		pTextureEnvironmentFront_;			// ���ʕ������}�b�v
	IDirect3DTexture9*		pTextureEnvironmentBack_;			// �w�ʕ������}�b�v
	IDirect3DTexture9*		pTextureEnvironmentAddFront_;		// ���ʉ��Z�������}�b�v
	IDirect3DTexture9*		pTextureEnvironmentAddBack_;		// �w�ʉ��Z�������}�b�v

private:
	void InitializeSelf( void );
	DrawerRiver( const DrawerRiver& );
	DrawerRiver operator=( const DrawerRiver& );
};

#endif	// MY_DRAWER_RIVER_H
