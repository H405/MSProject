//==============================================================================
//
// File   : DrawerSkinMeshReflect.h
// Brief  : �X�L�����b�V���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_SKIN_MESH_REFLECT_H
#define MY_DRAWER_SKIN_MESH_REFLECT_H

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
class Motion;

//******************************************************************************
// �N���X��`
//******************************************************************************
class DrawerSkinMeshReflect : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// �ϊ��s��
		PARAMETER_MATRIX_WORLD,				// ���[���h�ϊ��s��
		PARAMETER_MATRIX_WORLD_VIEW,		// ���[���h�r���[�ϊ��s��
		PARAMETER_MATRIX_BONE,				// �{�[���ϊ��s��
		PARAMETER_HEIGHT,					// ���˖ʂ̍���
		PARAMETER_TEXTURE,					// �e�N�X�`��
		PARAMETER_COLOR_SPECULAR,			// �X�y�L�����F
		PARAMETER_REFLECTION,				// ���˗�
		PARAMETER_POWER,					// ���˂̋���
		PARAMETER_REFLACTIVE,				// ���ܗ�
		PARAMETER_MAX						// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerSkinMeshReflect( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerSkinMeshReflect( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : Model* pModel						: ���f��
	// Arg    : int countBone						: �{�[����
	// Arg    : D3DXMATRIX* pMatrixBone				: �{�[���ϊ��s��Q�ƃA�h���X
	// Arg    : int* pIndexFrame					: �t���[���ԍ��Q�ƃA�h���X
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame );

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
	// Arg    : Model* pModel						: ���f��
	// Arg    : int countBone						: �{�[����
	// Arg    : D3DXMATRIX* pMatrixBone				: �{�[���ϊ��s��Q�ƃA�h���X
	// Arg    : int* pIndexFrame					: �t���[���ԍ��Q�ƃA�h���X
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerSkinMeshReflect* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerSkinMeshReflect* pOut ) const;

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
	const EffectParameter*	pEffectParameter_;		// �G�t�F�N�g�p�����[�^
	Effect*					pEffect_;				// �G�t�F�N�g
	Model*					pModel_;				// ���f��
	int						countBone_;				// �{�[����
	D3DXMATRIX*				pMatrixBone_;			// �{�[���ϊ��s��Q�ƃA�h���X
	int*					pIndexFrame_;			// �t���[���ԍ��Q�ƃA�h���X

private:
	void InitializeSelf( void );
	DrawerSkinMeshReflect( const DrawerSkinMeshReflect& );
	DrawerSkinMeshReflect operator=( const DrawerSkinMeshReflect& );

};

#endif	// MY_DRAWER_SKIN_MESH_REFLECT_H
