//==============================================================================
//
// File   : GraphicWaveDataInitialize.cpp
// Brief  : �g���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicWaveDataInitialize.h"
#include "../drawer/DrawerWaveDataInitialize.h"
#include "../../framework/resource/Effect.h"
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
GraphicWaveDataInitialize::GraphicWaveDataInitialize( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicWaveDataInitialize::~GraphicWaveDataInitialize( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �G�t�F�N�g
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int GraphicWaveDataInitialize::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTexture )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�̐���
	DrawerWaveDataInitialize*	pDrawerWaveDataInitialize = nullptr;		// �`��N���X
	pDrawerWaveDataInitialize = new DrawerWaveDataInitialize();
	if( pDrawerWaveDataInitialize == nullptr )
	{
		return 1;
	}
	result = pDrawerWaveDataInitialize->Initialize( pParameter, pEffect, pPolygon2D_, pTexture );
	ppDraw_[ GraphicMain::PASS_WAVE_DATA ] = pDrawerWaveDataInitialize;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicWaveDataInitialize::Finalize( void )
{
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
// Arg    : Effect* pEffect						: �G�t�F�N�g
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int GraphicWaveDataInitialize::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffect, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicWaveDataInitialize* pOut		: �R�s�[��A�h���X
//==============================================================================
int GraphicWaveDataInitialize::Copy( GraphicWaveDataInitialize* pOut ) const
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
void GraphicWaveDataInitialize::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
