//==============================================================================
//
// File   : DrawerSkinMeshShadow.h
// Brief  : ���f���e�`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/24 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_SKIN_MESH_SHADOW_H
#define MY_DRAWER_SKIN_MESH_SHADOW_H

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
class DrawerSkinMeshShadow : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// �ϊ��s��
		PARAMETER_MATRIX_WORLD_VIEW,		// ���[���h�r���[�ϊ��s��
		PARAMETER_MATRIX_BONE,				// �{�[���ϊ��s��
		PARAMETER_CLIP_FAR,					// �t�@�[�N���b�v��
		PARAMETER_MAX						// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	DrawerSkinMeshShadow( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerSkinMeshShadow( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : Model* pModel						: ���f��
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	// Arg    : int indexCamera						: �J�����ԍ�
	// Arg    : int countBone						: �{�[����
	// Arg    : D3DXMATRIX* pMatrixBone				: �{�[���ϊ��s��Q�ƃA�h���X
	//==============================================================================
	int Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, int indexCamera,
		int countBone, D3DXMATRIX* pMatrixBone );

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
	// Arg    : int indexCamera						: �J�����ԍ�
	// Arg    : int countBone						: �{�[����
	// Arg    : D3DXMATRIX* pMatrixBone				: �{�[���ϊ��s��Q�ƃA�h���X
	//==============================================================================
	int Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, int indexCamera,
		int countBone, D3DXMATRIX* pMatrixBone );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerSkinMeshShadow* pOut			: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerSkinMeshShadow* pOut ) const;

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
	int						indexCamera_;			// �J�����ԍ�
	int						countBone_;				// �{�[����
	D3DXMATRIX*				pMatrixBone_;			// �{�[���ϊ��s��Q�ƃA�h���X

private:
	void InitializeSelf( void );
	DrawerSkinMeshShadow( const DrawerSkinMeshShadow& );
	DrawerSkinMeshShadow operator=( const DrawerSkinMeshShadow& );
};

#endif	// MY_DRAWER_SKIN_MESH_SHADOW_H
