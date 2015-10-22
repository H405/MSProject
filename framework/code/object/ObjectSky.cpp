//==============================================================================
//
// File   : ObjectSky.cpp
// Brief  : ��I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectSky.h"
#include "../framework/polygon/PolygonMeshDomeInside.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/GraphicSky.h"

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
ObjectSky::ObjectSky( void ) : ObjectMovement()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectSky::~ObjectSky( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : int countCellX						: X�����Z����
// Arg    : int countCellY						: Z�����Z����
// Arg    : float radius						: ���a
// Arg    : float lengthTextureX				: X�����e�N�X�`������
// Arg    : float lengthTextureY				: Z�����e�N�X�`������
//==============================================================================
int ObjectSky::Initialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellY, float radius, float lengthTextureX, float lengthTextureY )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �������b�V���h�[���|���S���̐���
	pPolygonMesh_ = new PolygonMeshDomeInside();
	if( pPolygonMesh_ == nullptr )
	{
		return 1;
	}
	result = pPolygonMesh_->Initialize( pDevice, countCellX, countCellY, radius, lengthTextureX, lengthTextureY );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectSky::Finalize( void )
{
	// �������b�V���h�[���|���S���̊J��
	delete pPolygonMesh_;
	pPolygonMesh_ = nullptr;

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Finalize();
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
// Arg    : int priority						: �X�V�D��x
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : int countCellX						: X�����Z����
// Arg    : int countCellY						: Z�����Z����
// Arg    : float radius						: ���a
// Arg    : float lengthTextureX				: X�����e�N�X�`������
// Arg    : float lengthTextureY				: Z�����e�N�X�`������
//==============================================================================
int ObjectSky::Reinitialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellY, float radius, float lengthTextureX, float lengthTextureY )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pDevice, countCellX, countCellY, radius, lengthTextureX, lengthTextureY );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ObjectSky* pOut						: �R�s�[��A�h���X
//==============================================================================
int ObjectSky::Copy( ObjectSky* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectSky::Update( void )
{
	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : �`��N���X�̐���
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : Texture* pTexture					: �e�N�X�`��
//==============================================================================
int ObjectSky::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture )
{
	// �O���t�B�b�N�̐���
	int					result;				// ���s����
	IDirect3DTexture9*	pTextureSet;		// �ݒ肷��e�N�X�`��
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}
	pGraphic_ = new GraphicSky();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, pPolygonMesh_, pTextureSet );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`��N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : GraphicSky* pValue					: �ݒ肷��l
//==============================================================================
void ObjectSky::SetGraphic( GraphicSky* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : GraphicSky*							: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicSky* ObjectSky::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectSky::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pGraphic_ = nullptr;
	pPolygonMesh_ = nullptr;
}
