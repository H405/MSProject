//==============================================================================
//
// File   : DrawerModelMaterialReflect.h
// Brief  : ���˃��f���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/21 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DRAWER_MODEL_MATERIAL_REFLECT_H
#define MY_DRAWER_MODEL_MATERIAL_REFLECT_H

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
class DrawerModelMaterialReflect : public Drawer
{
public:
	// �p�����[�^
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// �ϊ��s��
		PARAMETER_MATRIX_WORLD,				// ���[���h�ϊ��s��
		PARAMETER_MATRIX_WORLD_VIEW,		// ���[���h�r���[�ϊ��s��
		PARAMETER_HEIGHT,					// ���˖ʂ̍���
		PARAMETER_COLOR_DIFFUSE,			// �f�B�t���[�Y�F
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
	DrawerModelMaterialReflect( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~DrawerModelMaterialReflect( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : Model* pModel						: ���f��
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �`��G�t�F�N�g
	//==============================================================================
	int Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect );

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
	//==============================================================================
	int Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : DrawerModelMaterialReflect* pOut	: �R�s�[��A�h���X
	//==============================================================================
	int Copy( DrawerModelMaterialReflect* pOut ) const;

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

private:
	void InitializeSelf( void );
	DrawerModelMaterialReflect( const DrawerModelMaterialReflect& );
	DrawerModelMaterialReflect operator=( const DrawerModelMaterialReflect& );
};

#endif	// MY_DRAWER_MODEL_MATERIAL_REFLECT_H
