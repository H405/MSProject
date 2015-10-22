//==============================================================================
//
// File   : GraphicSky.cpp
// Brief  : ��`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicSky.h"
#include "../drawer/DrawerSky.h"

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
GraphicSky::GraphicSky( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicSky::~GraphicSky( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : PolygonMeshDomeInside* pPolygon		: �������b�V���h�[���|���S��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int GraphicSky::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, PolygonMeshDomeInside* pPolygon, IDirect3DTexture9* pTexture )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�̐���
	DrawerSky*	pDrawerSly = nullptr;		// �`��N���X
	pDrawerSly = new DrawerSky();
	if( pDrawerSly == nullptr )
	{
		return 1;
	}
	result = pDrawerSly->Initialize( pParameter, pEffectGeneral, pPolygon, pTexture );
	ppDraw_[ GraphicMain::PASS_GENERAL ] = pDrawerSly;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicSky::Finalize( void )
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
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : PolygonMeshDomeInside* pPolygon		: �������b�V���h�[���|���S��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int GraphicSky::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, PolygonMeshDomeInside* pPolygon, IDirect3DTexture9* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffectGeneral, pPolygon, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicSky* pOut					: �R�s�[��A�h���X
//==============================================================================
int GraphicSky::Copy( GraphicSky* pOut ) const
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
void GraphicSky::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
