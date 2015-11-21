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
// Arg    : Effect** ppEffectGeneral			: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTextureNormal	: �@���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: ���ʊ��}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: �w�ʊ��}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: ���ʉ��Z���}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: �w�ʉ��Z���}�b�v�e�N�X�`��
//==============================================================================
int GraphicRiver::Initialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect** ppEffectGeneral,
	IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
	IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack )
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
	pDrawerRiver_ = new DrawerRiver[ GraphicMain::LIGHT_POINT_MAX + 1 ];
	if( pDrawerRiver_ == nullptr )
	{
		return 1;
	}
	for( int counterDrawer = 0; counterDrawer <= GraphicMain::LIGHT_POINT_MAX; ++counterDrawer )
	{
		result = pDrawerRiver_[ counterDrawer ].Initialize( pModel, pParameter, ppEffectGeneral[ counterDrawer ], pTextureNormal,
			pTextureEnvironmentFront, pTextureEnvironmentBack, pTextureEnvironmentAddFront, pTextureEnvironmentAddBack );
		if( result != 0 )
		{
			return result;
		}
	}
	ppDraw_[ GraphicMain::PASS_WATER ] = &pDrawerRiver_[ 0 ];

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
// Arg    : Effect** ppEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTextureNormal	: �@���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: ���ʊ��}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: �w�ʊ��}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: ���ʉ��Z���}�b�v�e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: �w�ʉ��Z���}�b�v�e�N�X�`��
//==============================================================================
int GraphicRiver::Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect** ppEffectGeneral,
	IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
	IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pModel, pParameter, ppEffectGeneral, pTextureNormal,
		pTextureEnvironmentFront, pTextureEnvironmentBack, pTextureEnvironmentAddFront, pTextureEnvironmentAddBack );
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
// Brief  : �`�揈��
// Return : void								: �Ȃ�
// Arg    : int index							: �`��ԍ�
//==============================================================================
void GraphicRiver::Draw( int index )
{
	// ���C�g�̐��ɉ����ĕ`��N���X��ύX
	ppDraw_[ GraphicMain::PASS_WATER ] = &pDrawerRiver_[ pParameter_->GetCountLightPoint() ];

	// ��{�N���X�̏���
	Graphic::Draw( index );
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
