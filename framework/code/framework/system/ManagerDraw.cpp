//==============================================================================
//
// File   : ManagerDraw.cpp
// Brief  : �`����s�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/10 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerDraw.h"
#include "../develop/Debug.h"
#include "../develop/DebugProc.h"
#include "../graphic/Graphic.h"
#include "../render/RenderPass.h"
#include "../render/RenderTarget.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �e���v���[�g�錾
//******************************************************************************
template class ManagerDraw< class Graphic >;

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerDraw< TypeItem >::ManagerDraw( void ) : ManagerExector()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerDraw< TypeItem >::~ManagerDraw( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : int countPass						: �`��p�X��
// Arg    : RenderPass* pRenderPass				: �`��p�X
//==============================================================================
template< class TypeItem >
int ManagerDraw< TypeItem >::Initialize( int maximumItem, IDirect3DDevice9* pDevice, int countPass, RenderPass* pRenderPass )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerExector::Initialize( maximumItem );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pDevice_ = pDevice;
	countPass_ = countPass;
	pRenderPass_ = pRenderPass;

	// �ő僌���_�[�^�[�Q�b�g���̎擾
	D3DCAPS9	capacity;		// ���\
	pDevice->GetDeviceCaps( &capacity );
	maximumRenderTarget_ = capacity.NumSimultaneousRTs;

//	NAGASAKI�ύX
#ifdef SCREENSHOT_ON
	screenShot = new CScreenShot(pDevice);
#endif
//	NAGASAKI�ύX

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerDraw< TypeItem >::Finalize( void )
{
//	NAGASAKI�ύX
	delete screenShot;
//	NAGASAKI�ύX

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerExector::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// �N���X�����̏�����
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : int countPass						: �`��p�X��
// Arg    : RenderPass* pRenderPass				: �`��p�X
//==============================================================================
template< class TypeItem >
int ManagerDraw< TypeItem >::Reinitialize( int maximumItem, IDirect3DDevice9* pDevice, int countPass, RenderPass* pRenderPass )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( maximumItem, pDevice, countPass, pRenderPass );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerDraw* pOut					: �R�s�[��A�h���X
//==============================================================================
template< class TypeItem >
int ManagerDraw< TypeItem >::Copy( ManagerDraw* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerExector::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���s
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerDraw< TypeItem >::Execute( void )
{
	// �L���ȂƂ��̂ݏ���
	if( !isEnable_ )
	{
		return 0;
	}

	// Direct3D�ɂ��`��̊J�n
	IDirect3DSurface9*	pSurfaceRenderOrigin;		// ���̕`��T�[�t�F�C�X
	IDirect3DSurface9*	pSurfaceDepthOrigin;		// ���̐[�x�T�[�t�F�C�X
	if( SUCCEEDED( pDevice_->BeginScene() ) )
	{
		// ���̕`��Ώۂ��L�^
		pDevice_->GetRenderTarget( 0, &pSurfaceRenderOrigin );
		pDevice_->GetDepthStencilSurface( &pSurfaceDepthOrigin );

		// �p�X�̕`��
		for( int counterPass = 0; counterPass < countPass_; ++counterPass )
		{
			// �����_�[�^�[�Q�b�g�̐ݒ�
			int			countRenderTarget;		// �����_�[�^�[�Q�b�g��
			DWORD		flagClear;				// �N���A�t���O
			D3DCOLOR	clearTarget;			// �����_�[�^�[�Q�b�g�̃N���A�l
			float		clearZBuffer;			// Z�o�b�t�@�̃N���A�l
			DWORD		clearStencil;			// �X�e���V���o�b�t�@�̃N���A�l
			if( counterPass < countPass_ - 1 )
			{
				countRenderTarget = pRenderPass_[ counterPass ].GetCountRenderTarget();
				pRenderPass_[ counterPass ].Set();
				flagClear = pRenderPass_[ counterPass ].GetFlagClear();
				clearTarget = pRenderPass_[ counterPass ].GetClearTarget();
				clearZBuffer = pRenderPass_[ counterPass ].GetClearZBuffer();
				clearStencil = pRenderPass_[ counterPass ].GetClearStencil();
			}
			else
			{
				countRenderTarget = 1;
				pDevice_->SetRenderTarget( 0, pSurfaceRenderOrigin );
				pDevice_->SetDepthStencilSurface( pSurfaceDepthOrigin );
				flagClear = (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
				clearTarget = D3DCOLOR_RGBA( 0, 0, 0, 0 );
				clearZBuffer = 1.0f;
				clearStencil = 0;
			}
			for( int counterRenderTarget = countRenderTarget; counterRenderTarget < maximumRenderTarget_; ++counterRenderTarget )
			{
				pDevice_->SetRenderTarget( counterRenderTarget, nullptr );
			}

			// �o�b�t�@�̃N���A
			pDevice_->Clear( 0, NULL, flagClear, clearTarget, clearZBuffer, clearStencil );

			// �I�u�W�F�N�g�̕`��
			int		indexItemCurrent;		// ���݂̗v�f�ԍ�
			for( indexItemCurrent = indexTop_; indexItemCurrent >= 0; indexItemCurrent = pBufferItem_[ indexItemCurrent ].indexNext_ )
			{
				if( pBufferItem_[ indexItemCurrent ].needsUnregister_ || !pBufferItem_[ indexItemCurrent ].isEnable_ || !pBufferItem_[ indexItemCurrent ].pItem_->IsEnable() )
				{
					continue;
				}
				pBufferItem_[ indexItemCurrent ].pItem_->Draw( counterPass );
			}
		}

//	NAGASAKI�ύX
#ifdef SCREENSHOT_ON
		//	�X�N���[���V���b�g�쐬
		if (screenShotFlag == true)
		{
			screenShot->Create();
			screenShotFlag = false;
		}
#endif
//	NAGASAKI�ύX

#ifdef _DEVELOP
		// �f�o�b�O�����̕`��
		DebugProc::Draw();
		DebugProc::ClearBuffer();
#endif

		// Direct3D�ɂ��`��̏I��
		pDevice_->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	pDevice_->Present( NULL, NULL, NULL, NULL );

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerExector::Execute();
	if( result != 0 )
	{
		return result;
	}

	// �l�̕ԋp
	return 0;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
void ManagerDraw< TypeItem >::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pDevice_ = nullptr;
	countPass_ = 0;
	pRenderPass_ = nullptr;

//	NAGASAKI�ύX
	screenShotFlag = false;
	screenShot = nullptr;
//	NAGASAKI�ύX
}
