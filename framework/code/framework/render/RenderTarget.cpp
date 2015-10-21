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
//==============================================================================
int RenderTarget::Initialize( IDirect3DDevice9* pDevice )
{
	// �����o�ϐ��̐ݒ�
	pDevice_ = pDevice;

	// �e�N�X�`���T�[�t�F�C�X�̐���
	IDirect3DSurface9*	pSurfaceDepthCurrent = nullptr;		// ���݂̃����_�[�^�[�Q�b�g
	D3DSURFACE_DESC		descSurfaceDepth;					// �T�[�t�F�C�X���
	unsigned int		widthSurface;						// �T�[�t�F�C�X�̕�
	unsigned int		heightSurface;						// �T�[�t�F�C�X�̍���
	int					result;								// ���s����
	pDevice_->GetRenderTarget( 0, &pSurfaceDepthCurrent );
	pSurfaceDepthCurrent->GetDesc( &descSurfaceDepth );
	widthSurface = descSurfaceDepth.Width;
	heightSurface = descSurfaceDepth.Height;
	pSurfaceDepthCurrent->Release();
	pSurfaceDepthCurrent = nullptr;
	result = D3DXCreateTexture( pDevice_, widthSurface, heightSurface, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTexture_ );
	if( result != 0 )
	{
		return 0;
	}

	// �[�x�o�b�t�@�̐���
	D3DSURFACE_DESC	descSurfaceTexture;		// �T�[�t�F�C�X���
	unsigned int	widthTexture;			// �T�[�t�F�C�X�̕�
	unsigned int	heightTexture;			// �T�[�t�F�C�X�̍���
	pTexture_->GetSurfaceLevel( 0, &pSurfaceTexture_ );
	pSurfaceTexture_->GetDesc( &descSurfaceTexture );
	widthTexture = descSurfaceTexture.Width;
	heightTexture = descSurfaceTexture.Height;
	result = pDevice_->CreateDepthStencilSurface( widthTexture, heightTexture, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, FALSE, &pSurfaceDepth_, nullptr );
	if( result != 0 )
	{
		return 0;
	}

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
	// �e�N�X�`���̊J��
	if( pTexture_ != nullptr )
	{
		pTexture_->Release();
		pTexture_ = nullptr;
	}

	// �e�N�X�`���T�[�t�F�C�X�̊J��
	if( pSurfaceTexture_ != nullptr )
	{
		pSurfaceTexture_->Release();
		pSurfaceTexture_ = nullptr;
	}

	// �[�x�o�b�t�@�̊J��
	if( pSurfaceDepth_ != nullptr )
	{
		pSurfaceDepth_->Release();
		pSurfaceDepth_ = nullptr;
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
//==============================================================================
int RenderTarget::Reinitialize( IDirect3DDevice9* pDevice )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice );
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
	pDevice_->SetDepthStencilSurface( pSurfaceDepth_ );
}

//==============================================================================
// Brief  : �o�^ID�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DTexture9* pValue			: �ݒ肷��l
//==============================================================================
void RenderTarget::SetTexture( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : �o�^ID�̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* RenderTarget::GetTexture( void ) const
{
	// �l�̕ԋp
	return pTexture_;
}

//==============================================================================
// Brief  : �e�N�X�`���T�[�t�F�C�X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DSurface9* pValue			: �ݒ肷��l
//==============================================================================
void RenderTarget::SetSurfaceTexture( IDirect3DSurface9* pValue )
{
	// �l�̐ݒ�
	pSurfaceTexture_ = pValue;
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
// Brief  : �[�x�o�b�t�@�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DSurface9* pValue			: �ݒ肷��l
//==============================================================================
void RenderTarget::SetSurfaceDepth( IDirect3DSurface9* pValue )
{
	// �l�̐ݒ�
	pSurfaceDepth_ = pValue;
}

//==============================================================================
// Brief  : �[�x�o�b�t�@�̎擾
// Return : IDirect3DSurface9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DSurface9* RenderTarget::GetSurfaceDepth( void ) const
{
	// �l�̕ԋp
	return pSurfaceDepth_;
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
	pSurfaceDepth_ = nullptr;
	isEnable_ = true;
}
