//==============================================================================
//
// File   : GraphicRiver.h
// Brief  : ��`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_RIVER_H
#define MY_GRAPHIC_RIVER_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicMain.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class DrawerRiver;
class Effect;
class EffectParameter;
class Model;

//******************************************************************************
// �N���X��`
//******************************************************************************
class GraphicRiver : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicRiver( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicRiver( void );

	//==============================================================================
	// Brief  : ����������
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
	int Initialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTextureNormal,
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
	int Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTextureNormal,
		IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicRiver* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicRiver* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicRiver( const GraphicRiver& );
	GraphicRiver operator=( const GraphicRiver& );

	const EffectParameter*	pParameter_;		// �G�t�F�N�g�p�����[�^
	DrawerRiver*			pDrawerRiver_;		// ��`��N���X
};

#endif	// MY_GRAPHIC_RIVER_H
