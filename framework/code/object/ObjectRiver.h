//==============================================================================
//
// File   : ObjectRiver.h
// Brief  : ��I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_RIVER_H
#define MY_OBJECT_RIVER_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../framework/object/ObjectMovement.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Model;
class EffectParameter;
class Effect;
class GraphicRiver;

//******************************************************************************
// �N���X��`
//******************************************************************************
class ObjectRiver : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ObjectRiver( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ObjectRiver( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	//==============================================================================
	int Initialize( int priority );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	//==============================================================================
	int Reinitialize( int priority );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : ObjectRiver* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ObjectRiver* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : �`��N���X�̐���
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : Model* pModel						: ���f��
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect** ppEffectGeneral			: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureNormal	: �@���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: ���ʊ��}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: �w�ʊ��}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: ���ʉ��Z���}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: �w�ʉ��Z���}�b�v�e�N�X�`��
	//==============================================================================
	int CreateGraphic( int priority, Model* pModel, const EffectParameter* pParameter, Effect** ppEffectGeneral,
		IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
		IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetGraphic( GraphicRiver* pValue );
	GraphicRiver* GetGraphic( void ) const;

protected:
	GraphicRiver*	pGraphic_;		// �`��N���X

private:
	void InitializeSelf( void );
	ObjectRiver( const ObjectRiver& );
	ObjectRiver operator=( const ObjectRiver& );
};

#endif	// MY_OBJECT_RIVER_H
