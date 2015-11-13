//==============================================================================
//
// File   : GraphicModelMaterial.cpp
// Brief  : ���f���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicModelMaterial.h"
#include "../drawer/DrawerModelMaterial.h"

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
GraphicModelMaterial::GraphicModelMaterial( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicModelMaterial::~GraphicModelMaterial( void )
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
//==============================================================================
int GraphicModelMaterial::Initialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�̐���
	DrawerModelMaterial*	pDrawerModelMaterial = nullptr;		// �`��N���X
	pDrawerModelMaterial = new DrawerModelMaterial();
	if( pDrawerModelMaterial == nullptr )
	{
		return 1;
	}
	result = pDrawerModelMaterial->Initialize( pModel, pParameter, pEffectGeneral );
	ppDraw_[ GraphicMain::PASS_3D ] = pDrawerModelMaterial;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicModelMaterial::Finalize( void )
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
// Arg    : Model* pModel						: ���f��
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
//==============================================================================
int GraphicModelMaterial::Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pModel, pParameter, pEffectGeneral );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicModelMaterial* pOut					: �R�s�[��A�h���X
//==============================================================================
int GraphicModelMaterial::Copy( GraphicModelMaterial* pOut ) const
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
void GraphicModelMaterial::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}