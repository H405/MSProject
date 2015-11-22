//==============================================================================
//
// File   : ObjectLightReflect.h
// Brief  : ���˃��C�g�`��I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/22 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_LIGHT_REFLECT_H
#define MY_OBJECT_LIGHT_REFLECT_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../framework/object/object.h"

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
class GraphicLightReflect;

//******************************************************************************
// �N���X��`
//******************************************************************************
class ObjectLightReflect : public Object
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ObjectLightReflect( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ObjectLightReflect( void );

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
	// Arg    : ObjectLightReflect* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ObjectLightReflect* pOut ) const;

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
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect** ppEffectGeneral			: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
		IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetGraphic( GraphicLightReflect* pValue );
	GraphicLightReflect* GetGraphic( void ) const;

protected:
	GraphicLightReflect*	pGraphic_;		// �`��N���X

private:
	void InitializeSelf( void );
	ObjectLightReflect( const ObjectLightReflect& );
	ObjectLightReflect operator=( const ObjectLightReflect& );

};

#endif	// MY_OBJECT_LIGHT_REFLECT_H
