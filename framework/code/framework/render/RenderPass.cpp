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
#include "RenderPassParameter.h"
#include "RenderTarget.h"
#include "../develop/Debug.h"

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
// Arg    : const RenderPassParameter* pParameter	: �`��Ώۃp�����[�^
//==============================================================================
int RenderPass::Initialize( IDirect3DDevice9* pDevice, int countRenderTarget, const RenderPassParameter* pParameter )
{
	// �T�C�Y�̌���
	if( pParameter == nullptr || pParameter->width_ < 0 || pParameter->height_ < 0 )
	{
		IDirect3DSurface9*	pSurfaceDepthCurrent = nullptr;		// ���݂̃����_�[�^�[�Q�b�g
		D3DSURFACE_DESC		descSurfaceDepth;					// �T�[�t�F�C�X���
		pDevice->GetRenderTarget( 0, &pSurfaceDepthCurrent );
		pSurfaceDepthCurrent->GetDesc( &descSurfaceDepth );
		width_ = descSurfaceDepth.Width;
		height_ = descSurfaceDepth.Height;
		pSurfaceDepthCurrent->Release();
		pSurfaceDepthCurrent = nullptr;
	}

	// �����o�ϐ��̐ݒ�
	int		result;		// ���s����
	pDevice_ = pDevice;
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
		result = ppRenderTarget_[ counterItem ]->Initialize( pDevice, width_, height_, (pParameter == nullptr ? D3DFMT_A8R8G8B8 : pParameter->pFormat_[ counterItem ]) );
		if( result != 0 )
		{
			return result;
		}
	}
	if( pParameter != nullptr )
	{
		width_ = static_cast< unsigned int >( pParameter->width_ );
		height_ = static_cast< unsigned int >( pParameter->height_ );
		flagClear_ = pParameter->flagClear_;
		clearTarget_ = pParameter->clearTarget_;
		clearZBuffer_ = pParameter->clearZBuffer_;
		clearStencil_ = pParameter->clearStencil_;
	}

	// �[�x�o�b�t�@�̐���
	IDirect3DSurface9*	pSurface = nullptr;		// �T�[�t�F�C�X
	D3DSURFACE_DESC		descSurfaceTexture;		// �T�[�t�F�C�X���
	unsigned int		widthTexture;			// �T�[�t�F�C�X�̕�
	unsigned int		heightTexture;			// �T�[�t�F�C�X�̍���
	ppRenderTarget_[ 0 ]->GetTexture()->GetSurfaceLevel( 0, &pSurface );
	pSurface->GetDesc( &descSurfaceTexture );
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
int RenderPass::Finalize( void )
{
	// �[�x�o�b�t�@�̊J��
	if( pSurfaceDepth_ != nullptr )
	{
		pSurfaceDepth_->Release();
		pSurfaceDepth_ = nullptr;
	}

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
// Arg    : const RenderPassParameter* pParameter	: �`��Ώۃp�����[�^
//==============================================================================
int RenderPass::Reinitialize( IDirect3DDevice9* pDevice, int countRenderTarget, const RenderPassParameter* pParameter )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice, countRenderTarget, pParameter );
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
// Brief  : �`��Ώۂɐݒ�
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void RenderPass::Set( void )
{
	// �f�o�C�X�Ƀ����_�[�^�[�Q�b�g��ݒ�
	for( int counterRenderTarget = 0; counterRenderTarget < countRenderTarget_; ++counterRenderTarget )
	{
		ppRenderTarget_[ counterRenderTarget ]->Set( counterRenderTarget );
	}
	pDevice_->SetDepthStencilSurface( pSurfaceDepth_ );
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
// Brief  : �e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : int index							: �����_�[�^�[�Q�b�g�̔ԍ�
//==============================================================================
IDirect3DTexture9* RenderPass::GetTexture( int index ) const
{
	// �G���[�`�F�b�N
	Assert( index >= 0 && index < countRenderTarget_, _T( "�����_�[�^�[�Q�b�g�̔ԍ����s���ł��B" ) );
	Assert( ppRenderTarget_[ index ] != nullptr, _T( "�����_�[�^�[�Q�b�g�̔ԍ����s���ł��B" ) );

	// �l�̕ԋp
	return ppRenderTarget_[ index ]->GetTexture();
}

//==============================================================================
// Brief  : �[�x�o�b�t�@�̎擾
// Return : IDirect3DSurface9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DSurface9* RenderPass::GetSurfaceDepth( void ) const
{
	// �l�̕ԋp
	return pSurfaceDepth_;
}

//==============================================================================
// Brief  : ���̎擾
// Return : unsigned int						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned int RenderPass::GetWidth( void ) const
{
	// �l�̕ԋp
	return width_;
}

//==============================================================================
// Brief  : �����̎擾
// Return : unsigned int						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned int RenderPass::GetHeight( void ) const
{
	// �l�̕ԋp
	return height_;
}

//==============================================================================
// Brief  : �N���A�t���O�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const DWORD& value					: �ݒ肷��l
//==============================================================================
void RenderPass::SetFlagClear( const DWORD& value )
{
	// �l�̐ݒ�
	flagClear_ = value;
}

//==============================================================================
// Brief  : �N���A�t���O�̎擾
// Return : DWORD								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
DWORD RenderPass::GetFlagClear( void ) const
{
	// �l�̕ԋp
	return flagClear_;
}

//==============================================================================
// Brief  : �����_�[�^�[�Q�b�g�̃N���A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DCOLOR& value				: �ݒ肷��l
//==============================================================================
void RenderPass::SetClearTarget( const D3DCOLOR& value )
{
	// �l�̐ݒ�
	clearTarget_ = value;
}

//==============================================================================
// Brief  : �����_�[�^�[�Q�b�g�̃N���A�l�̎擾
// Return : DWORD								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
D3DCOLOR RenderPass::GetClearTarget( void ) const
{
	// �l�̕ԋp
	return clearTarget_;
}

//==============================================================================
// Brief  : Z�o�b�t�@�̃N���A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void RenderPass::SetClearZBuffer( float value )
{
	// �l�̐ݒ�
	clearZBuffer_ = value;
}

//==============================================================================
// Brief  : Z�o�b�t�@�̃N���A�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float RenderPass::GetClearZBuffer( void ) const
{
	// �l�̕ԋp
	return clearZBuffer_;
}

//==============================================================================
// Brief  : �X�e���V���o�b�t�@�̃N���A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const DWORD& value					: �ݒ肷��l
//==============================================================================
void RenderPass::SetClearStencil( const DWORD& value )
{
	// �l�̐ݒ�
	clearStencil_ = value;
}

//==============================================================================
// Brief  : �X�e���V���o�b�t�@�̃N���A�l�̎擾
// Return : DWORD								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
DWORD RenderPass::GetClearStencil( void ) const
{
	// �l�̕ԋp
	return clearStencil_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void RenderPass::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pDevice_ = nullptr;
	countRenderTarget_ = 0;
	ppRenderTarget_ = nullptr;
	pSurfaceDepth_ = nullptr;
	width_ = 0;
	height_ = 0;
	flagClear_ = (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
	clearTarget_ = D3DCOLOR_RGBA( 0, 0, 0, 0 );
	clearZBuffer_ = 1.0f;
	clearStencil_ = 0;
}
