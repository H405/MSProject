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
// Arg    : int countMultiple					: ���ԕ`�搔
//==============================================================================
int RenderTarget::Initialize( IDirect3DDevice9* pDevice, int width, int height, D3DFORMAT format, int countMultiple )
{
	// �����o�ϐ��̐ݒ�
	pDevice_ = pDevice;
	countMultiple_ = countMultiple;

	// �i�[�̈�̊m��
	if( countMultiple <= 0 )
	{
		return 0;
	}
	ppTexture_ = new IDirect3DTexture9*[ countMultiple ];
	if( ppTexture_ == nullptr )
	{
		return 1;
	}
	ppSurfaceTexture_ = new IDirect3DSurface9*[ countMultiple ];
	if( ppSurfaceTexture_ == nullptr )
	{
		return 1;
	}

	// �e�N�X�`���T�[�t�F�C�X�̐���
	int		result;		// ���s����
	for( int counterMultiple = 0; counterMultiple < countMultiple; ++counterMultiple )
	{
		result = D3DXCreateTexture( pDevice_, width, height, 1, D3DUSAGE_RENDERTARGET, format, D3DPOOL_DEFAULT, &ppTexture_[ counterMultiple ] );
		if( result != 0 )
		{
			return 0;
		}
		ppTexture_[ counterMultiple ]->GetSurfaceLevel( 0, &ppSurfaceTexture_[ counterMultiple ] );
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
	// ���\�[�X�̊J��
	for( int counterMultiple = 0; counterMultiple < countMultiple_; ++counterMultiple )
	{
		// �e�N�X�`���T�[�t�F�C�X�̊J��
		if( ppSurfaceTexture_[ counterMultiple ] != nullptr )
		{
			ppSurfaceTexture_[ counterMultiple ]->Release();
			ppSurfaceTexture_[ counterMultiple ] = nullptr;
		}

		// �e�N�X�`���̊J��
		if( ppTexture_[ counterMultiple ] != nullptr )
		{
			ppTexture_[ counterMultiple ]->Release();
			ppTexture_[ counterMultiple ] = nullptr;
		}
	}
	delete[] ppSurfaceTexture_;
	delete[] ppTexture_;

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
// Arg    : int countMultiple					: ���ԕ`�搔
//==============================================================================
int RenderTarget::Reinitialize( IDirect3DDevice9* pDevice, int width, int height, D3DFORMAT format, int countMultiple )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDevice, width, height, format, countMultiple );
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
	pDevice_->SetRenderTarget( index, ppSurfaceTexture_[ indexMultiple_ ] );

	// �ԍ���i�߂�
	++indexMultiple_;
	if( indexMultiple_ >= countMultiple_ )
	{
		indexMultiple_ = 0;
	}
}

//==============================================================================
// Brief  : �e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : int index							: ���Ԕԍ�
//==============================================================================
IDirect3DTexture9* RenderTarget::GetTexture( int index ) const
{
	// �l�̕ԋp
	return ppTexture_[ index ];
}

//==============================================================================
// Brief  : �e�N�X�`���T�[�t�F�C�X�̎擾
// Return : IDirect3DSurface9*					: �ԋp����l
// Arg    : int index							: ���Ԕԍ�
//==============================================================================
IDirect3DSurface9* RenderTarget::GetSurfaceTexture( int index ) const
{
	// �l�̕ԋp
	return ppSurfaceTexture_[ index ];
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
	countMultiple_ = 0;
	indexMultiple_ = 0;
	ppTexture_ = nullptr;
	ppSurfaceTexture_ = nullptr;
	isEnable_ = true;
}
