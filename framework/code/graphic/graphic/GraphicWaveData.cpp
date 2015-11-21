//==============================================================================
//
// File   : GraphicWaveData.cpp
// Brief  : �g���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicWaveData.h"
#include "../drawer/DrawerWaveData.h"
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
GraphicWaveData::GraphicWaveData( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicWaveData::~GraphicWaveData( void )
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
// Arg    : IDirect3DTexture9* pTextureHeight0	: �����e�N�X�`��0
// Arg    : IDirect3DTexture9* pTextureHeight1	: �����e�N�X�`��1
//==============================================================================
int GraphicWaveData::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffect,
	IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�̐���
	DrawerWaveData*	pDrawerWaveData = nullptr;		// �`��N���X
	pDrawerWaveData = new DrawerWaveData();
	if( pDrawerWaveData == nullptr )
	{
		return 1;
	}
	result = pDrawerWaveData->Initialize( pParameter, pEffect, pPolygon2D_, pTextureHeight0, pTextureHeight1 );
	ppDraw_[ GraphicMain::PASS_WAVE_DATA ] = pDrawerWaveData;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicWaveData::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTextureHeight0	: �����e�N�X�`��0
// Arg    : IDirect3DTexture9* pTextureHeight1	: �����e�N�X�`��1
//==============================================================================
int GraphicWaveData::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffect,
	IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffect, pTextureHeight0, pTextureHeight1 );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicWaveData* pOut				: �R�s�[��A�h���X
//==============================================================================
int GraphicWaveData::Copy( GraphicWaveData* pOut ) const
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
void GraphicWaveData::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
