//==============================================================================
//
// File   : GraphicSkinMesh.cpp
// Brief  : �X�L�����b�V���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicSkinMesh.h"
#include "../drawer/DrawerSkinMesh.h"
#include "../drawer/DrawerSkinMeshParaboloid.h"
#include "../drawer/DrawerSkinMeshReflect.h"
#include "../drawer/DrawerSkinMeshShadow.h"

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
GraphicSkinMesh::GraphicSkinMesh( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicSkinMesh::~GraphicSkinMesh( void )
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
// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
// Arg    : Effect* pEffectShadow				: �e�`��G�t�F�N�g
// Arg    : Effect* pEffectParaboloid			: �����ϊ��`��G�t�F�N�g
// Arg    : Model* pModel						: ���f��
// Arg    : int countBone						: �{�[����
// Arg    : D3DXMATRIX* pMatrixBone				: �{�[���ϊ��s��Q�ƃA�h���X
//==============================================================================
int GraphicSkinMesh::Initialize( int priority, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow, Effect* pEffectParaboloid,
	Model* pModel, int countBone, D3DXMATRIX* pMatrixBone )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �ʏ�`��N���X�̐���
	DrawerSkinMesh*	pDrawerSkinMesh = nullptr;		// �`��N���X
	pDrawerSkinMesh = new DrawerSkinMesh();
	if( pDrawerSkinMesh == nullptr )
	{
		return 1;
	}
	result = pDrawerSkinMesh->Initialize( pParameter, pEffectGeneral, pModel, countBone, pMatrixBone );
	ppDraw_[ GraphicMain::PASS_3D ] = pDrawerSkinMesh;

	// ���˕`��N���X�̐���
	DrawerSkinMeshReflect*	pDrawerSkinMeshReflect = nullptr;		// �`��N���X
	pDrawerSkinMeshReflect = new DrawerSkinMeshReflect();
	if( pDrawerSkinMeshReflect == nullptr )
	{
		return 1;
	}
	result = pDrawerSkinMeshReflect->Initialize( pParameter, pEffectReflect, pModel, countBone, pMatrixBone );
	ppDraw_[ GraphicMain::PASS_REFLECT ] = pDrawerSkinMeshReflect;

	// �e(��)�`��N���X�̐���
	DrawerSkinMeshShadow*	pDrawerSkinMeshShadowNear = nullptr;		// �`��N���X
	pDrawerSkinMeshShadowNear = new DrawerSkinMeshShadow();
	if( pDrawerSkinMeshShadowNear == nullptr )
	{
		return 1;
	}
	result = pDrawerSkinMeshShadowNear->Initialize( pModel, pParameter, pEffectShadow, GraphicMain::CAMERA_SHADOW_NEAR, countBone, pMatrixBone );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_NEAR ] = pDrawerSkinMeshShadowNear;

	// �e(��)�`��N���X�̐���
	DrawerSkinMeshShadow*	pDrawerSkinMeshShadowFar = nullptr;		// �`��N���X
	pDrawerSkinMeshShadowFar = new DrawerSkinMeshShadow();
	if( pDrawerSkinMeshShadowFar == nullptr )
	{
		return 1;
	}
	result = pDrawerSkinMeshShadowFar->Initialize( pModel, pParameter, pEffectShadow, GraphicMain::CAMERA_SHADOW_FAR, countBone, pMatrixBone );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_FAR ] = pDrawerSkinMeshShadowFar;

	// �e(�_)�`��N���X�̐���
	DrawerSkinMeshParaboloid*	pDrawerSkinMeshParaboloid = nullptr;		// �`��N���X
	pDrawerSkinMeshParaboloid = new DrawerSkinMeshParaboloid();
	if( pDrawerSkinMeshParaboloid == nullptr )
	{
		return 1;
	}
	result = pDrawerSkinMeshParaboloid->Initialize( pModel, pParameter, pEffectParaboloid, GraphicMain::CAMERA_SHADOW_POINT, countBone, pMatrixBone );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_POINT ] = pDrawerSkinMeshParaboloid;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicSkinMesh::Finalize( void )
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
// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
// Arg    : Effect* pEffectShadow				: �e�`��G�t�F�N�g
// Arg    : Effect* pEffectParaboloid			: �����ϊ��`��G�t�F�N�g
// Arg    : Model* pModel						: ���f��
// Arg    : int countBone						: �{�[����
// Arg    : D3DXMATRIX* pMatrixBone				: �{�[���ϊ��s��Q�ƃA�h���X
//==============================================================================
int GraphicSkinMesh::Reinitialize( int priority, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow, Effect* pEffectParaboloid,
	Model* pModel, int countBone, D3DXMATRIX* pMatrixBone )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffectGeneral, pEffectReflect, pEffectShadow, pEffectParaboloid, pModel, countBone, pMatrixBone );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicSkinMesh* pOut				: �R�s�[��A�h���X
//==============================================================================
int GraphicSkinMesh::Copy( GraphicSkinMesh* pOut ) const
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
// Brief  : �`��N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : GraphicSkinMesh* pValue				: �ݒ肷��l
//==============================================================================
void GraphicSkinMesh::SetGraphic( GraphicSkinMesh* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : GraphicSkinMesh*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicSkinMesh* GraphicSkinMesh::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void GraphicSkinMesh::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pGraphic_ = nullptr;
}
