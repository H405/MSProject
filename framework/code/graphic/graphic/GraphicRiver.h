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
	// Arg    : Effect** ppEffectGeneral			: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureNormal	: �@���e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: ���ʊ��}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: �w�ʊ��}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: ���ʉ��Z���}�b�v�e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: �w�ʉ��Z���}�b�v�e�N�X�`��
	//==============================================================================
	int Initialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect** ppEffectGeneral,
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
	int Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect** ppEffectGeneral,
		IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
		IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicRiver* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicRiver* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : int index							: �`��ԍ�
	//==============================================================================
	void Draw( int index );

protected:

private:
	void InitializeSelf( void );
	GraphicRiver( const GraphicRiver& );
	GraphicRiver operator=( const GraphicRiver& );

	const EffectParameter*	pParameter_;		// �G�t�F�N�g�p�����[�^
	DrawerRiver*			pDrawerRiver_;		// ��`��N���X
};

#endif	// MY_GRAPHIC_RIVER_H
