//==============================================================================
//
// File   : GraphicLightReflect.cpp
// Brief  : ���˃��C�g�`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/22 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicLightReflect.h"
#include "../drawer/DrawerLightReflect.h"
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
GraphicLightReflect::GraphicLightReflect( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicLightReflect::~GraphicLightReflect( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect** ppEffectGeneral			: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
//==============================================================================
int GraphicLightReflect::Initialize( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
	IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth )
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
	pDrawerLight_ = new DrawerLightReflect[ GraphicMain::LIGHT_POINT_MAX + 1 ];
	if( pDrawerLight_ == nullptr )
	{
		return 1;
	}
	for( int counterDrawer = 0; counterDrawer <= GraphicMain::LIGHT_POINT_MAX; ++counterDrawer )
	{
		result = pDrawerLight_[ counterDrawer ].Initialize( pParameter, ppEffectGeneral[ counterDrawer ], pPolygon2D_, pTextureDiffuse, pTextureSpecular, pTextureNormal, pTextureDepth );
		if( result != 0 )
		{
			return result;
		}
	}
	ppDraw_[ GraphicMain::PASS_LIGHT_REFLECT ] = &pDrawerLight_[ 0 ];

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicLightReflect::Finalize( void )
{
	// �i�[�̈�̊J��
	delete[] pDrawerLight_;
	pDrawerLight_ = nullptr;
	ppDraw_[ GraphicMain::PASS_LIGHT_REFLECT ] = nullptr;

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
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect** ppEffectGeneral			: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
//==============================================================================
int GraphicLightReflect::Reinitialize( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
	IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, ppEffectGeneral, pTextureDiffuse, pTextureSpecular, pTextureNormal, pTextureDepth );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicLightReflect* pOut			: �R�s�[��A�h���X
//==============================================================================
int GraphicLightReflect::Copy( GraphicLightReflect* pOut ) const
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
void GraphicLightReflect::Draw( int index )
{
	// ���C�g�̐��ɉ����ĕ`��N���X��ύX
	ppDraw_[ GraphicMain::PASS_LIGHT_REFLECT ] = &pDrawerLight_[ pParameter_->GetCountLightPoint() ];

	// ��{�N���X�̏���
	Graphic::Draw( index );
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void GraphicLightReflect::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pParameter_ = nullptr;
	pDrawerLight_ = nullptr;
}
