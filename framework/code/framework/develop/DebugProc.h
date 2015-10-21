//==============================================================================
//
// File   : DebugProc.h
// Brief  : �f�o�b�O�\��
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_DEBUG_PROC_H
#define MY_DEBUG_PROC_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "d3dx9.h"
#include <windows.h>
#include <tchar.h>

//******************************************************************************
// ���C�u����
//******************************************************************************
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "d3d9.lib" )

//******************************************************************************
// �}�N����`
//******************************************************************************
#ifdef _DEBUG
#define PrintDebug( pFormat, ... )	DebugProc::Print( pFormat, __VA_ARGS__ )
#else
#define PrintDebug( pFormat, ... )	static_cast< void >( 0 )
#endif

//******************************************************************************
// �N���X�O���錾
//******************************************************************************

//******************************************************************************
// �N���X��`
//******************************************************************************
class DebugProc
{
public:
	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	//==============================================================================
	static int Initialize( IDirect3DDevice9* pDevice );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	static int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	//==============================================================================
	static int Reinitialize( IDirect3DDevice9* pDevice );

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	static void Update( void );

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	static void Draw( void );

	//==============================================================================
	// Brief  : �o�b�t�@�̃N���A
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	static void ClearBuffer( void );

	//==============================================================================
	// Brief  : �f�o�b�O������̕\��
	// Return : void								: �Ȃ�
	// Arg    : const TCHAR *pFormat				: �����t�H�[�}�b�g
	//==============================================================================
	static void Print( const TCHAR *pFormat, ... );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	static void SetIsVisible( bool value );
	static bool GetIsVisible( void );
	static bool IsVisible( void );
	static void SetRectDisplay( const RECT& value );
	static void GetRectDisplay( RECT* pOut );
	static void SetColorCharacter( const D3DXCOLOR& value );
	static void SetColorCharacter( float r, float g, float b, float a );
	static void SetColorCharacter( float r, float g, float b );
	static void SetColorCharacterR( float r );
	static void SetColorCharacterG( float g );
	static void SetColorCharacterB( float b );
	static void SetColorCharacterA( float a );
	static void SetColorCharacterAlpha( float alpha );
	static void GetColorCharacter( D3DXCOLOR* pOut );
	static float GetColorCharacterR( void );
	static float GetColorCharacterG( void );
	static float GetColorCharacterB( void );
	static float GetColorCharacterA( void );

protected:

private:
	static void InitializeSelf( void );

	DebugProc( void );
	~DebugProc( void );
	DebugProc( const DebugProc& );
	DebugProc operator=( const DebugProc& );

	static const unsigned int	MAXIMUM_SIZE_BUFFER = 32768;		// �o�b�t�@�̍ő�T�C�Y

	static ID3DXFont*	pFont_;					// �t�H���g
	static TCHAR*		pBuffer_;				// ������i�[�p�o�b�t�@
	static bool			isVisible_;				// �\�����邩
	static RECT			rectDisplay_;			// �\������̈�
	static D3DXCOLOR	colorCharacter_;		// �����̐F
};

#endif	// MY_DEBUG_PROC_H
