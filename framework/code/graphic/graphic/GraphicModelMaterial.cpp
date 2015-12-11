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
#include "../drawer/DrawerModelMaterialReflect.h"
#include "../drawer/DrawerModelParaboloid.h"
#include "../drawer/DrawerModelShadow.h"

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
// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
// Arg    : Effect* pEffectShadow				: �e�`��G�t�F�N�g
// Arg    : Effect* pEffectParaboloid			: �����ϊ��`��G�t�F�N�g
//==============================================================================
int GraphicModelMaterial::Initialize( int priority, Model* pModel, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow, Effect* pEffectParaboloid )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �ʏ�`��N���X�̐���
	DrawerModelMaterial*	pDrawerModelMaterial = nullptr;		// �`��N���X
	pDrawerModelMaterial = new DrawerModelMaterial();
	if( pDrawerModelMaterial == nullptr )
	{
		return 1;
	}
	result = pDrawerModelMaterial->Initialize( pModel, pParameter, pEffectGeneral );
	ppDraw_[ GraphicMain::PASS_3D ] = pDrawerModelMaterial;

	// ���˕`��N���X�̐���
	DrawerModelMaterialReflect*	pDrawerModelMaterialReflect = nullptr;		// �`��N���X
	pDrawerModelMaterialReflect = new DrawerModelMaterialReflect();
	if( pDrawerModelMaterialReflect == nullptr )
	{
		return 1;
	}
	result = pDrawerModelMaterialReflect->Initialize( pModel, pParameter, pEffectReflect );
	ppDraw_[ GraphicMain::PASS_REFLECT ] = pDrawerModelMaterialReflect;

	// �e(��)�`��N���X�̐���
	DrawerModelShadow*	pDrawerModelShadowNear = nullptr;		// �`��N���X
	pDrawerModelShadowNear = new DrawerModelShadow();
	if( pDrawerModelShadowNear == nullptr )
	{
		return 1;
	}
	result = pDrawerModelShadowNear->Initialize( pModel, pParameter, pEffectShadow, GraphicMain::CAMERA_SHADOW_NEAR );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_NEAR ] = pDrawerModelShadowNear;

	// �e(��)�`��N���X�̐���
	DrawerModelShadow*	pDrawerModelShadowFar = nullptr;		// �`��N���X
	pDrawerModelShadowFar = new DrawerModelShadow();
	if( pDrawerModelShadowFar == nullptr )
	{
		return 1;
	}
	result = pDrawerModelShadowFar->Initialize( pModel, pParameter, pEffectShadow, GraphicMain::CAMERA_SHADOW_FAR );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_FAR ] = pDrawerModelShadowFar;

	// �e(�_0)�`��N���X�̐���
	DrawerModelParaboloid*	pDrawerModelParaboloid0 = nullptr;		// �`��N���X
	pDrawerModelParaboloid0 = new DrawerModelParaboloid();
	if( pDrawerModelParaboloid0 == nullptr )
	{
		return 1;
	}
	result = pDrawerModelParaboloid0->Initialize( pModel, pParameter, pEffectParaboloid, GraphicMain::CAMERA_SHADOW_POINT_0 );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_POINT_0 ] = pDrawerModelParaboloid0;

	// �e(�_1)�`��N���X�̐���
	DrawerModelParaboloid*	pDrawerModelParaboloid1 = nullptr;		// �`��N���X
	pDrawerModelParaboloid1 = new DrawerModelParaboloid();
	if( pDrawerModelParaboloid1 == nullptr )
	{
		return 1;
	}
	result = pDrawerModelParaboloid1->Initialize( pModel, pParameter, pEffectParaboloid, GraphicMain::CAMERA_SHADOW_POINT_1 );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_POINT_1 ] = pDrawerModelParaboloid1;

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
// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
// Arg    : Effect* pEffectShadow				: �e�`��G�t�F�N�g
// Arg    : Effect* pEffectParaboloid			: �����ϊ��`��G�t�F�N�g
//==============================================================================
int GraphicModelMaterial::Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow, Effect* pEffectParaboloid )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pModel, pParameter, pEffectGeneral, pEffectReflect, pEffectShadow, pEffectParaboloid );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicModelMaterial* pOut			: �R�s�[��A�h���X
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
