//==============================================================================
//
// File   : ObjectMerge.h
// Brief  : ����3D�`��I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_MERGE_H
#define MY_OBJECT_MERGE_H

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
class GraphicMerge;

//******************************************************************************
// �N���X��`
//******************************************************************************
class ObjectMerge : public Object
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ObjectMerge( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ObjectMerge( void );

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
	// Arg    : ObjectMerge* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ObjectMerge* pOut ) const;

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
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureLight	: ���C�g����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureNotLight	: ���C�g�Ȃ��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureAdd		: ���Z�����e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureRiver	: ��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureDepthRiver	: ��̐[�x�e�N�X�`��
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureRiver, IDirect3DTexture9* pTextureDepthRiver );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetGraphic( GraphicMerge* pValue );
	GraphicMerge* GetGraphic( void ) const;

protected:
	GraphicMerge*	pGraphic_;		// �`��N���X

private:
	void InitializeSelf( void );
	ObjectMerge( const ObjectMerge& );
	ObjectMerge operator=( const ObjectMerge& );

};

#endif	// MY_OBJECT_MERGE_H
