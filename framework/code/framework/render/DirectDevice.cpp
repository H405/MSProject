//==============================================================================
//
// File   : DirectDevice.cpp
// Brief  : Direct3D�f�o�C�X�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/16 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <tchar.h>
#include "DirectDevice.h"
#include "../develop/Debug.h"

//******************************************************************************
// ���C�u����
//******************************************************************************
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

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
DirectDevice::DirectDevice( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DirectDevice::~DirectDevice( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : HWND windowHandle					: �E�B���h�E�n���h��
// Arg    : int width							: �E�B���h�E��
// Arg    : int height							: �E�B���h�E����
// Arg    : bool isWindowMode					: �E�B���h�E���[�h�t���O
//==============================================================================
int DirectDevice::Initialize( HWND windowHandle, int width, int height, bool isWindowMode )
{
	// Direct3D�̏�����
	IDirect3D9*				pDirect3D;					// Direct3D�I�u�W�F�N�g
	D3DPRESENT_PARAMETERS	presentParameter;			// �v���[���g�p�����[�^
	D3DDISPLAYMODE			displayMode;				// �f�B�X�v���C���[�h
	int						countDisplayMode = 0;		// �f�B�X�v���C���[�h�̐�

	// Direct3D�I�u�W�F�N�g�̐���
	pDirect3D = Direct3DCreate9( D3D_SDK_VERSION );
	if( pDirect3D == nullptr )
	{
		PrintMsgBox( _T( "Direct3D�I�u�W�F�N�g�̐����Ɏ��s���܂����B" ) );
		return 1;
	}

	// �t���X�N���[���̊m�F
	if( !isWindowMode )
	{	// �E�B���h�E���[�h�̎w�肪����Ă��Ȃ��Ƃ�
		if( MessageBox( NULL, _T( "�t���X�N���[���ŋN�����܂����H\n" ), _T( "�t���X�N���[���̊m�F" ), MB_YESNO ) == IDYES )
		{
			isWindowMode_ = false;
		}
		else
		{
			isWindowMode_ = true;
		}
	}
	else
	{
		isWindowMode_ = true;
	}

	// �f�B�X�v���C���[�h�̗�
	if( !isWindowMode_ )
	{	// �E�B���h�E���[�h�̎w�肪����Ă��Ȃ��Ƃ�
		countDisplayMode = pDirect3D->GetAdapterModeCount( D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8 );
		for( int nCntDisp = 0; nCntDisp < countDisplayMode; ++nCntDisp )
		{
			// �f�B�X�v���C���[�h�̎擾
			if( FAILED( pDirect3D->EnumAdapterModes( D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, nCntDisp, &displayMode ) ) )
			{
				PrintMsgBox( _T( "�f�B�X�v���C���[�h�̎擾�Ɏ��s���܂����B" ), _T( "�G���[" ) );
				return 1;
			}

			// �f�B�X�v���C���[�h�̌���
			if( static_cast< int >( displayMode.Width ) == width && static_cast< int >( displayMode.Height ) == height )
			{
				break;
			}
		}
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	BOOL	flagWindowed;		// �E�B���h�E���[�h
	flagWindowed = (isWindowMode_ ? TRUE : FALSE);
	ZeroMemory( &presentParameter, sizeof( presentParameter ) );		// ���[�N���[���N���A
	presentParameter.BackBufferCount		= 1;						// �o�b�N�o�b�t�@�̐�
	presentParameter.BackBufferWidth		= width;					// �Q�[����ʃT�C�Y(��)
	presentParameter.BackBufferHeight		= height;					// �Q�[����ʃT�C�Y(����)
	presentParameter.BackBufferFormat		= D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	presentParameter.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	presentParameter.Windowed				= flagWindowed;				// �E�B���h�E���[�h
	presentParameter.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	presentParameter.AutoDepthStencilFormat	= D3DFMT_D24S8;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��( �Ή����Ă��邩�m�F���������悢 ) D3DFMT_D24S8 ���ǂ�
	presentParameter.hDeviceWindow			= windowHandle;

	if( isWindowMode_ )
	{	// �E�B���h�E���[�h
		presentParameter.BackBufferFormat			= D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		presentParameter.FullScreen_RefreshRateInHz	= 0;								// ���t���b�V�����[�g
		presentParameter.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��( �e�B�A�����O���N���� )
	}
	else
	{	// �t���X�N���[�����[�h
		presentParameter.BackBufferFormat			= D3DFMT_R5G6B5;					// �o�b�N�o�b�t�@
		presentParameter.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		presentParameter.PresentationInterval		= D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if( FAILED( pDirect3D->CreateDevice(	D3DADAPTER_DEFAULT,						// �f�B�X�v���C�A�_�v�^
											D3DDEVTYPE_HAL,							// �f�B�X�v���C�^�C�v
											windowHandle,							// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
											D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
											&presentParameter,						// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
											&pDevice_ ) ) )							// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
		presentParameter.AutoDepthStencilFormat	= D3DFMT_D16;
		if( FAILED( pDirect3D->CreateDevice(	D3DADAPTER_DEFAULT,						// �f�B�X�v���C�A�_�v�^
												D3DDEVTYPE_HAL,							// �f�B�X�v���C�^�C�v
												windowHandle,							// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
												D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
												&presentParameter,						// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
												&pDevice_ ) ) )							// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
		{
			MessageBox( NULL, _T( "��掿���[�h�ŋN�����܂��B" ), _T( "�m�F" ), MB_OK );
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
			if( FAILED( pDirect3D->CreateDevice(	D3DADAPTER_DEFAULT, 
													D3DDEVTYPE_HAL, 
													windowHandle, 
													D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
													&presentParameter,
													&pDevice_ ) ) )
			{
				// ��L�̐ݒ肪���s������
				// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
				if( FAILED( pDirect3D->CreateDevice(	D3DADAPTER_DEFAULT, 
														D3DDEVTYPE_REF,
														windowHandle, 
														D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
														&presentParameter,
														&pDevice_ ) ) )
				{
					// ���������s
					PrintMsgBox( _T( "�f�o�C�X�I�u�W�F�N�g�̏������Ɏ��s���܂����B" ) );
					return 1;
				}
			}
		}
	}

	// �t���X�N���[�����̃_�C�A���O�ݒ�
	if( !isWindowMode_ )
	{
		pDevice_->SetDialogBoxMode( TRUE );
	}

	// Direct3D�I�u�W�F�N�g�̊J��
	if( pDirect3D != nullptr )
	{
		pDirect3D->Release();
		pDirect3D = nullptr;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int DirectDevice::Finalize( void )
{
	// Direct3D�f�o�C�X�I�u�W�F�N�g�̊J��
	if( pDevice_ != nullptr )
	{
		pDevice_->Release();
		pDevice_ = nullptr;
	}

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : HWND windowHandle					: �E�B���h�E�n���h��
// Arg    : int width							: �E�B���h�E��
// Arg    : int height							: �E�B���h�E����
// Arg    : bool isWindowMode					: �E�B���h�E���[�h�t���O
//==============================================================================
int DirectDevice::Reinitialize( HWND windowHandle, int width, int height, bool isWindowMode )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( windowHandle, width, height, isWindowMode );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DirectDevice* pOut					: �R�s�[��A�h���X
//==============================================================================
int DirectDevice::Copy( DirectDevice* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : Direct3D�f�o�C�X�̎擾
// Return : IDirect3DDevice9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DDevice9* DirectDevice::GetDevice( void ) const
{
	// �l�̕ԋp
	return pDevice_;
}

//==============================================================================
// Brief  : �E�B���h�E���[�h�t���O�̎擾
// Return : bool								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
bool DirectDevice::GetIsWindowMode( void ) const
{
	// �l�̕ԋp
	return isWindowMode_;
}

//==============================================================================
// Brief  : �E�B���h�E���[�h�t���O�̔���
// Return : bool								: ���茋��
// Arg    : void								: �Ȃ�
//==============================================================================
bool DirectDevice::IsWindowMode( void ) const
{
	// �l�̕ԋp
	return isWindowMode_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DirectDevice::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pDevice_ = nullptr;
}
