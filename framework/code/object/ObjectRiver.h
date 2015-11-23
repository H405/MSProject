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
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureNormal	: �@���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureReflect	: ���˃e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: ���˃��C�e�B���O�Ȃ��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureReflectAdd		: ���ˉ��Z�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
	//==============================================================================
	int CreateGraphic( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTextureNormal,
		IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth );

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
