//==============================================================================
//
// File   : GraphicRiver.cpp
// Brief  : ��`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicRiver.h"
#include "../drawer/DrawerRiver.h"
#include "../../system/EffectParameter.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicRiver::GraphicRiver( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicRiver::~GraphicRiver( void )
{
	// �I������
	Finalize();
}

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
int GraphicRiver::Initialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTextureNormal,
	IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pParameter_ = pParameter;

	// �`��N���X�̐���
	pDrawerRiver_ = new DrawerRiver();
	if( pDrawerRiver_ == nullptr )
	{
		return 1;
	}
	result = pDrawerRiver_->Initialize( pModel, pParameter, pEffectGeneral, pTextureNormal, pTextureReflect, pTextureReflectNotLight, pTextureReflectAdd,
		pTexture3D, pTextureDepth );
	if( result != 0 )
	{
		return result;
	}
	ppDraw_[ GraphicMain::PASS_WATER ] = pDrawerRiver_;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicRiver::Finalize( void )
{
	// �i�[�̈�̊J��
	delete[] pDrawerRiver_;
	pDrawerRiver_ = nullptr;
	ppDraw_[ GraphicMain::PASS_WATER ] = nullptr;

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

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
int GraphicRiver::Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTextureNormal,
	IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pModel, pParameter, pEffectGeneral, pTextureNormal, pTextureReflect, pTextureReflectNotLight, pTextureReflectAdd,
		pTexture3D, pTextureDepth );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicRiver* pOut					: �R�s�[��A�h���X
//==============================================================================
int GraphicRiver::Copy( GraphicRiver* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void GraphicRiver::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pParameter_ = nullptr;
	pDrawerRiver_ = nullptr;
}
