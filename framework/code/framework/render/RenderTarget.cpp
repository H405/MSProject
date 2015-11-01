//==============================================================================
//
// File   : RenderTarget.cpp
// Brief  : �`��Ώ�
// Author : Taiga Shirakawa
// Date   : 2015/10/10 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
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
RenderTarget::RenderTarget( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
RenderTarget::~RenderTarget( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : int width							: ��
// Arg    : int height							: ����
// Arg    : D3DFORMAT format					: �e�N�X�`���t�H�[�}�b�g
//==============================================================================
int RenderTarget::Initialize( IDirect3DDevice9* pDevice, int width, int height, D3DFORMAT format )
{
	// �����o�ϐ��̐ݒ�
	pDevice_ = pDevice;

	// �e�N�X�`���T�[�t�F�C�X�̐���
	int			result;		// ���s����
	result = D3DXCreateTexture( pDevice_, width, height, 1, D3DUSAGE_RENDERTARGET, format, D3DPOOL_DEFAULT, &pTexture_ );
	if( result != 0 )
	{
		return 0;
	}
	pTexture_->GetSurfaceLevel( 0, &pSurfaceTexture_ );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int RenderTarget::Finalize( void )
{
	// �e�N�X�`���T�[�t�F�C�X�̊J��
	if( pSurfaceTexture_ != nullptr )
	{
		pSurfaceTexture_->Release();
		pSurfaceTexture_ = nullptr;
	}

	// �e�N�X�`���̊J��
	if( pTexture_ != nullptr )
	{
		pTexture_->Release();
		pTexture_ = nullptr;
	}

	// �N���X�����̏�����
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : int width							: ��
// Arg    : int height							: ����
// Arg    : D3DFORMAT format					: �e�N�X�`���t�H�[�}�b�g
//==============================================================================
int RenderTarget::Reinitialize( IDirect3DDevice9* pDevice, int width, int height, D3DFORMAT format )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice, width, height, format );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : RenderTarget* pOut					: �R�s�[��A�h���X
//==============================================================================
int RenderTarget::Copy( RenderTarget* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`��Ώۂɐݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
//==============================================================================
void RenderTarget::Set( int index )
{
	// �f�o�C�X�Ƀ����_�[�^�[�Q�b�g��ݒ�
	pDevice_->SetRenderTarget( index, pSurfaceTexture_ );
}

//==============================================================================
// Brief  : �e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* RenderTarget::GetTexture( void ) const
{
	// �l�̕ԋp
	return pTexture_;
}

//==============================================================================
// Brief  : �e�N�X�`���T�[�t�F�C�X�̎擾
// Return : IDirect3DSurface9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DSurface9* RenderTarget::GetSurfaceTexture( void ) const
{
	// �l�̕ԋp
	return pSurfaceTexture_;
}

//==============================================================================
// Brief  : �L���t���O�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : bool value							: �ݒ肷��l
//==============================================================================
void RenderTarget::SetIsEnable( bool value )
{
	// �l�̐ݒ�
	isEnable_ = value;
}

//==============================================================================
// Brief  : �L���t���O�̎擾
// Return : bool								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
bool RenderTarget::GetIsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �L���t���O�̔���
// Return : bool								: ���茋��
// Arg    : void								: �Ȃ�
//==============================================================================
bool RenderTarget::IsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void RenderTarget::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pDevice_ = nullptr;
	pTexture_ = nullptr;
	pSurfaceTexture_ = nullptr;
	isEnable_ = true;
}
