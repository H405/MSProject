//==============================================================================
//
// File   : RenderPass.cpp
// Brief  : �p�X�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "RenderPass.h"
#include "RenderTarget.h"

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
RenderPass::RenderPass( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
RenderPass::~RenderPass( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : int countRenderTarget				: �����_�[�^�[�Q�b�g�̐�
//==============================================================================
int RenderPass::Initialize( IDirect3DDevice9* pDevice, int countRenderTarget )
{
	// �����o�ϐ��̐ݒ�
	int		result;		// ���s����
	countRenderTarget_ = countRenderTarget;
	ppRenderTarget_ = new RenderTarget*[ countRenderTarget ];
	if( ppRenderTarget_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countRenderTarget; ++counterItem )
	{
		ppRenderTarget_[ counterItem ] = new RenderTarget();
		if( ppRenderTarget_[ counterItem ] == nullptr )
		{
			return 1;
		}
		result = ppRenderTarget_[ counterItem ]->Initialize( pDevice );
		if( result != 0 )
		{
			return result;
		}
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int RenderPass::Finalize( void )
{
	// �����_�[�^�[�Q�b�g�̊J��
	if( ppRenderTarget_ != nullptr )
	{
		for( int counterItem = 0; counterItem < countRenderTarget_; ++counterItem )
		{
			delete ppRenderTarget_[ counterItem ];
			ppRenderTarget_[ counterItem ] = nullptr;
		}
	}
	delete[] ppRenderTarget_;
	ppRenderTarget_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : int countRenderTarget				: �����_�[�^�[�Q�b�g�̐�
//==============================================================================
int RenderPass::Reinitialize( IDirect3DDevice9* pDevice, int countRenderTarget )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice, countRenderTarget );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : RenderPass* pOut					: �R�s�[��A�h���X
//==============================================================================
int RenderPass::Copy( RenderPass* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �����_�[�^�[�Q�b�g���̎擾
// Return : int									: �ԋp�l
// Arg    : void								: �Ȃ�
//==============================================================================
int RenderPass::GetCountRenderTarget( void ) const
{
	// �l�̕ԋp
	return countRenderTarget_;
}

//==============================================================================
// Brief  : �����_�[�^�[�Q�b�g�̎擾
// Return : RenderTarget*						: �擾����l
// Arg    : int index							: �ݒ肷��ԍ�
//==============================================================================
RenderTarget* RenderPass::GetRenderTarget( int index ) const
{
	// �l�̕ԋp
	return ppRenderTarget_[ index ];
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void RenderPass::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	countRenderTarget_ = 0;
	ppRenderTarget_ = nullptr;
}
