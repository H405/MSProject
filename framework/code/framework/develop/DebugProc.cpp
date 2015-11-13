//==============================================================================
//
// File   : DebugProc.cpp
// Brief  : �f�o�b�O�\��
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <stdio.h>
#include <stdarg.h>
#include "DebugProc.h"
#include "Debug.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
ID3DXFont*	DebugProc::pFont_;				// �t�H���g
TCHAR*		DebugProc::pBuffer_;			// ������i�[�p�o�b�t�@
bool		DebugProc::isVisible_;			// �\�����邩
RECT		DebugProc::rectDisplay_;		// �\������̈�
D3DXCOLOR	DebugProc::colorCharacter_;		// �����̐F

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
//==============================================================================
int DebugProc::Initialize( IDirect3DDevice9* pDevice )
{
	// �N���X���̏���������
	InitializeSelf();

	// �����o�ϐ��̐ݒ�
	pBuffer_ = new TCHAR[ MAXIMUM_SIZE_BUFFER ];
	ZeroMemory( pBuffer_, sizeof( TCHAR ) * MAXIMUM_SIZE_BUFFER );
	rectDisplay_.left = 0;
	rectDisplay_.right = 1000;
	rectDisplay_.top = 0;
	rectDisplay_.bottom = 1000;

	// ���\���p�t�H���g��ݒ�
	if( FAILED( D3DXCreateFont( pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T( "Terminal" ), &pFont_ ) ) )
	{
		return E_FAIL;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int DebugProc::Finalize( void )
{
	// �i�[�̈�̊J��
	if( pFont_ != nullptr )
	{
		pFont_->Release();
		pFont_ = nullptr;
	}

	delete[] pBuffer_;
	pBuffer_ = nullptr;

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
int DebugProc::Reinitialize( IDirect3DDevice9* pDevice )
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
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DebugProc::Update( void )
{
}

//==============================================================================
// Brief  : �`�揈��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DebugProc::Draw( void )
{
	// �f�o�b�O����\��
	if( !isVisible_ )
	{
		return;
	}

	// �e�L�X�g�`��
	pFont_->DrawText( NULL, pBuffer_, -1, &rectDisplay_, DT_LEFT, colorCharacter_ );
}

//==============================================================================
// Brief  : �o�b�t�@�̃N���A
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DebugProc::ClearBuffer( void )
{
	// �o�b�t�@�N���A
	ZeroMemory( pBuffer_, sizeof( TCHAR ) * MAXIMUM_SIZE_BUFFER );
}

//==============================================================================
// Brief  : �f�o�b�O������̕\��
// Return : void								: �Ȃ�
// Arg    : const TCHAR *pFormat				: �����t�H�[�}�b�g
//==============================================================================
void DebugProc::Print( const TCHAR *pFormat, ... )
{
	// �G���[�`�F�b�N
#ifndef _DEVELOP
	MessageBox( NULL, _T( "PrintDebug�֐��Ăяo���G���[" ), _T( "�G���[" ), MB_OK );
	abort();
#endif
	Assert( pFont_ != nullptr, _T( "�t�H���g�I�u�W�F�N�g���쐬����Ă��܂���B" ) );

	// �f�o�b�O����\��
	if( !isVisible_ )
	{
		return;
	}

	// �\��������쐬
	TCHAR	pStringAdd[ 256 ] = {};		// �ǉ����镶����
	va_list	args;						// ����
	va_start( args, pFormat );
	_vsntprintf_s( pStringAdd, 256, _TRUNCATE, pFormat, args );
	va_end( args );

	// �\��������L�^
	_tcscat_s( pBuffer_, MAXIMUM_SIZE_BUFFER, pStringAdd );
}

//==============================================================================
// Brief  : �\�����邩�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : bool value							: �ݒ肷��l
//==============================================================================
void DebugProc::SetIsVisible( bool value )
{
	// �l�̐ݒ�
	isVisible_ = value;
}

//==============================================================================
// Brief  : �\�����邩�̎擾
// Return : bool								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
bool DebugProc::GetIsVisible( void )
{
	// �l�̕ԋp
	return isVisible_;
}

//==============================================================================
// Brief  : �\�����邩�̔���
// Return : bool								: ���茋��
// Arg    : void								: �Ȃ�
//==============================================================================
bool DebugProc::IsVisible( void )
{
	// �l�̕ԋp
	return isVisible_;
}

//==============================================================================
// Brief  : �\������̈�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const RECT& value					: �ݒ肷��l
//==============================================================================
void DebugProc::SetRectDisplay( const RECT& value )
{
	// �l�̐ݒ�
	rectDisplay_ = value;
}

//==============================================================================
// Brief  : �\������̈�̎擾
// Return : void								: �Ȃ�
// Arg    : RECT* pOut							: �l�̊i�[�A�h���X
//==============================================================================
void DebugProc::GetRectDisplay( RECT* pOut )
{
	// �l�̕ԋp
	*pOut = rectDisplay_;
}

//==============================================================================
// Brief  : �����̐F�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: �ݒ肷��l
//==============================================================================
void DebugProc::SetColorCharacter( const D3DXCOLOR& value )
{
	// �l�̐ݒ�
	colorCharacter_ = value;
}

//==============================================================================
// Brief  : �����̐F��RGBA�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void DebugProc::SetColorCharacter( float r, float g, float b, float a )
{
	// �l�̐ݒ�
	colorCharacter_.r = r;
	colorCharacter_.g = g;
	colorCharacter_.b = b;
	colorCharacter_.a = a;
}

//==============================================================================
// Brief  : �����̐F��RGB�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
//==============================================================================
void DebugProc::SetColorCharacter( float r, float g, float b )
{
	// �l�̐ݒ�
	colorCharacter_.r = r;
	colorCharacter_.g = g;
	colorCharacter_.b = b;
}

//==============================================================================
// Brief  : �����̐F��R�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
//==============================================================================
void DebugProc::SetColorCharacterR( float r )
{
	// �l�̐ݒ�
	colorCharacter_.r = r;
}

//==============================================================================
// Brief  : �����̐F��G�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void DebugProc::SetColorCharacterG( float g )
{
	// �l�̐ݒ�
	colorCharacter_.g = g;
}

//==============================================================================
// Brief  : �����̐F��B�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void DebugProc::SetColorCharacterB( float b )
{
	// �l�̐ݒ�
	colorCharacter_.b = b;
}

//==============================================================================
// Brief  : �����̐F��A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void DebugProc::SetColorCharacterA( float a )
{
	// �l�̐ݒ�
	colorCharacter_.a = a;
}

//==============================================================================
// Brief  : �����̐F�̃A���t�@�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void DebugProc::SetColorCharacterAlpha( float alpha )
{
	// �l�̐ݒ�
	colorCharacter_.a = alpha;
}

//==============================================================================
// Brief  : �����̐F�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXCOLOR* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void DebugProc::GetColorCharacter( D3DXCOLOR* pOut )
{
	// �l�̕ԋp
	*pOut = colorCharacter_;
}

//==============================================================================
// Brief  : �����̐F��R�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float DebugProc::GetColorCharacterR( void )
{
	// �l�̕ԋp
	return colorCharacter_.r;
}

//==============================================================================
// Brief  : �����̐F��G�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float DebugProc::GetColorCharacterG( void )
{
	// �l�̕ԋp
	return colorCharacter_.g;
}

//==============================================================================
// Brief  : �����̐F��B�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float DebugProc::GetColorCharacterB( void )
{
	// �l�̕ԋp
	return colorCharacter_.b;
}

//==============================================================================
// Brief  : �����̐F��A�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float DebugProc::GetColorCharacterA( void )
{
	// �l�̕ԋp
	return colorCharacter_.a;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DebugProc::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pFont_ = nullptr;
	pBuffer_ = nullptr;
	isVisible_ = true;
	colorCharacter_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
}
