//==============================================================================
//
// File   : RenderPassParameter.cpp
// Brief  : �`��p�X�p�����[�^
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "RenderPassParameter.h"

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
RenderPassParameter::RenderPassParameter( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
RenderPassParameter::~RenderPassParameter( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void RenderPassParameter::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	width_ = -1;
	height_ = -1;
	for( int counterRenderRarget = 0; counterRenderRarget < MAXIMUM_RENDER_TARGET; ++counterRenderRarget )
	{
		pFormat_[ counterRenderRarget ] = D3DFMT_A8R8G8B8;
	}
	flagClear_ = (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
	clearTarget_ = D3DCOLOR_RGBA( 0, 0, 0, 0 );
	clearZBuffer_ = 1.0f;
	clearStencil_ = 0;
	pSurfaceDepth_ = nullptr;
}