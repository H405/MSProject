//==============================================================================
//
// File   : GraphicModel.cpp
// Brief  : ���f���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicModel.h"
#include "../drawer/DrawerModel.h"
#include "../drawer/DrawerModelParaboloid.h"
#include "../drawer/DrawerModelReflect.h"
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
GraphicModel::GraphicModel( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicModel::~GraphicModel( void )
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
int GraphicModel::Initialize( int priority, Model* pModel, const EffectParameter* pParameter,
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
	DrawerModel*	pDrawerModel = nullptr;		// �`��N���X
	pDrawerModel = new DrawerModel();
	if( pDrawerModel == nullptr )
	{
		return 1;
	}
	result = pDrawerModel->Initialize( pModel, pParameter, pEffectGeneral );
	ppDraw_[ GraphicMain::PASS_3D ] = pDrawerModel;

	// ���˕`��N���X�̐���
	DrawerModelReflect*	pDrawerModelReflect = nullptr;		// �`��N���X
	pDrawerModelReflect = new DrawerModelReflect();
	if( pDrawerModelReflect == nullptr )
	{
		return 1;
	}
	result = pDrawerModelReflect->Initialize( pModel, pParameter, pEffectReflect );
	ppDraw_[ GraphicMain::PASS_REFLECT ] = pDrawerModelReflect;

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

	// �e(�_)�`��N���X�̐���
	DrawerModelParaboloid*	pDrawerModelParaboloid = nullptr;		// �`��N���X
	pDrawerModelParaboloid = new DrawerModelParaboloid();
	if( pDrawerModelParaboloid == nullptr )
	{
		return 1;
	}
	result = pDrawerModelParaboloid->Initialize( pModel, pParameter, pEffectParaboloid, GraphicMain::CAMERA_SHADOW_POINT );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_POINT ] = pDrawerModelParaboloid;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicModel::Finalize( void )
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
int GraphicModel::Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter,
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
// Arg    : GraphicModel* pOut					: �R�s�[��A�h���X
//==============================================================================
int GraphicModel::Copy( GraphicModel* pOut ) const
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
void GraphicModel::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
