//==============================================================================
//
// File   : GraphicBlur.cpp
// Brief  : �u���[��`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/10 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicBlur.h"
#include "../drawer/DrawerBlur.h"
#include "../../framework/resource/Effect.h"
#include "../../system/EffectParameter.h"

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
GraphicBlur::GraphicBlur( void ) : GraphicMain()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicBlur::~GraphicBlur( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectX					: X�����u���[�G�t�F�N�g
// Arg    : Effect* pEffectY					: Y�����u���[�G�t�F�N�g
// Arg    : IDirect3DTexture9* pTextureX		: X�����u���[���|����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureY		: Y�����u���[���|����e�N�X�`��
//==============================================================================
int GraphicBlur::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectX, Effect* pEffectY,
	IDirect3DTexture9* pTextureX, IDirect3DTexture9* pTextureY )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// X�����`��N���X�̐���
	DrawerBlur*	pDrawerBlurX = nullptr;		// �`��N���X
	D3DXVECTOR2	offsetX;					// X�����I�t�Z�b�g
	offsetX.x = 32.0f / pParameter->GetWidthScreen();
	offsetX.y = 0.0f;
	pDrawerBlurX = new DrawerBlur();
	if( pDrawerBlurX == nullptr )
	{
		return 1;
	}
	result = pDrawerBlurX->Initialize( pParameter, pEffectX, pPolygon2D_, pTextureX, offsetX );
	ppDraw_[ GraphicMain::PASS_BLUR_X ] = pDrawerBlurX;

	// Y�����`��N���X�̐���
	DrawerBlur*	pDrawerBlurY = nullptr;		// �`��N���X
	D3DXVECTOR2	offsetY;					// Y�����I�t�Z�b�g
	offsetY.x = 0.0f;
	offsetY.y = 32.0f / pParameter->GetHeightScreen();
	pDrawerBlurY = new DrawerBlur();
	if( pDrawerBlurY == nullptr )
	{
		return 1;
	}
	result = pDrawerBlurY->Initialize( pParameter, pEffectY, pPolygon2D_, pTextureY, offsetY );
	ppDraw_[ GraphicMain::PASS_BLUR_Y ] = pDrawerBlurY;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicBlur::Finalize( void )
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
// Arg    : Effect* pEffectX					: X�����u���[�G�t�F�N�g
// Arg    : Effect* pEffectY					: Y�����u���[�G�t�F�N�g
// Arg    : IDirect3DTexture9* pTextureX		: X�����u���[���|����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureY		: Y�����u���[���|����e�N�X�`��
//==============================================================================
int GraphicBlur::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectX, Effect* pEffectY,
	IDirect3DTexture9* pTextureX, IDirect3DTexture9* pTextureY )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, pParameter, pEffectX, pEffectY, pTextureX, pTextureY );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicBlur* pOut					: �R�s�[��A�h���X
//==============================================================================
int GraphicBlur::Copy( GraphicBlur* pOut ) const
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
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void GraphicBlur::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
