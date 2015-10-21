//==============================================================================
//
// File   : InputKeyboard.cpp
// Brief  : �L�[�{�[�h���̓N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <tchar.h>
#include "InputKeyboard.h"

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
InputKeyboard::InputKeyboard( void ) : Input()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
InputKeyboard::~InputKeyboard( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : IDirectInput8* pDirectInput			: DirectInput�I�u�W�F�N�g
// Arg    : HWND windowHandle					: �E�B���h�E�n���h��
//==============================================================================
int InputKeyboard::Initialize( IDirectInput8* pDirectInput, HWND windowHandle )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Input::Initialize( pDirectInput, windowHandle );
	if( result != 0 )
	{
		return result;
	}

	// �f�o�C�X�I�u�W�F�N�g���쐬
	if( FAILED( pDirectInput_->CreateDevice( GUID_SysKeyboard, &pDevice_, NULL ) ) )
	{
		MessageBox( NULL, _T( "�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if( FAILED( pDevice_->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		MessageBox( NULL, _T( "�f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if( FAILED( pDevice_->SetCooperativeLevel( windowHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) ) ) )
	{
		MessageBox( NULL, _T( "�������[�h�̐ݒ�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	pDevice_->Acquire();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int InputKeyboard::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Input::Finalize();
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
// Arg    : IDirectInput8* pDirectInput			: DirectInput�I�u�W�F�N�g
// Arg    : HWND windowHandle					: �E�B���h�E�n���h��
//==============================================================================
int InputKeyboard::Reinitialize( IDirectInput8* pDirectInput, HWND windowHandle )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDirectInput, windowHandle );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : InputKeyboard* pOut					: �R�s�[��A�h���X
//==============================================================================
int InputKeyboard::Copy( InputKeyboard* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Input::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void InputKeyboard::Update( void )
{
	// �L�[�{�[�h�̏�Ԃ��X�V
	BYTE	pState[ MAXIMUM_STATE ];		// �L�[�{�[�h��Ԏ󂯎��p
	if( SUCCEEDED( pDevice_->GetDeviceState( sizeof( pState ), &pState[ 0 ] ) ) )
	{
		memset( &pTrigger_[ 0 ], 0x00, sizeof( pTrigger_ ) );
		memset( &pRelease_[ 0 ], 0x00, sizeof( pRelease_ ) );
		for( int nCntMouse = 0; nCntMouse < MAXIMUM_STATE; ++nCntMouse )
		{
			// �g���K���̍X�V
			if( !(pState_[ nCntMouse ] & 0x80) && (pState[ nCntMouse ] & 0x80) )
			{
				pTrigger_[ nCntMouse ] = true;
			}

			// �����[�X���̍X�V
			if( (pState_[ nCntMouse ] & 0x80) && !(pState[ nCntMouse ] & 0x80) )
			{
				pRelease_[ nCntMouse ] = true;
			}

			// ���s�[�g���̍X�V
			if( (pState[ nCntMouse ] & 0x80) )
			{
				++pRepeat_[ nCntMouse ];
			}
			else
			{
				pRepeat_[ nCntMouse ] = 0;
			}

			// �L�[�{�[�h��Ԃ̍X�V
			pState_[ nCntMouse ] = pState[ nCntMouse ];
		}
	}
	else
	{
		pDevice_->Acquire();
	}
}

//==============================================================================
// Brief  : �v���X����
// Return : bool								: �v���X����
// Arg    : int typeKey							: ���肷��L�[�̎��
//==============================================================================
bool InputKeyboard::IsPress( int typeKey ) const
{
	// �l�̕ԋp
	return (pState_[ typeKey ] & 0x80) != 0;
}

//==============================================================================
// Brief  : �g���K�[����
// Return : bool								: �g���K�[����
// Arg    : int typeKey							: ���肷��L�[�̎��
//==============================================================================
bool InputKeyboard::IsTrigger( int typeKey ) const
{
	// �l�̕ԋp
	return pTrigger_[ typeKey ];
}

//==============================================================================
// Brief  : �����[�X����
// Return : bool								: �����[�X����
// Arg    : int typeKey							: ���肷��L�[�̎��
//==============================================================================
bool InputKeyboard::IsRelease( int typeKey ) const
{
	// �l�̕ԋp
	return pRelease_[ typeKey ];
}

//==============================================================================
// Brief  : ���s�[�g����
// Return : bool								: ���s�[�g����
// Arg    : int typeKey							: ���肷��L�[�̎��
// Arg    : int timeBegin						: ON�ɂȂ�܂ł̎���
// Arg    : int timeInterval					: ON�ɂȂ�Ԋu
//==============================================================================
bool InputKeyboard::IsRepeat( int typeKey, int timeBegin, int timeInterval ) const
{
	// �g���K����
	if( pRepeat_[ typeKey ] == 1 )
	{
		return true;
	}

	// ���s�[�g����
	if( pRepeat_[ typeKey ] >= timeBegin )
	{
		if( (pRepeat_[ typeKey ] - timeBegin) % timeInterval == 0 )
		{
			return true;
		}
	}

	// �l�̕ԋp
	return false;
}

//==============================================================================
// Brief  : �v���X���Ԃ̎擾
// Return : int									: �v���X����
// Arg    : int typeKey							: ���肷��L�[�̎��
//==============================================================================
int InputKeyboard::GetTimePress( int typeKey ) const
{
	// �l�̕ԋp
	return pRepeat_[ typeKey ];
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void InputKeyboard::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	for( int counterKey = 0; counterKey < MAXIMUM_STATE; ++counterKey )
	{
		pState_[ counterKey ] = false;
		pTrigger_[ counterKey ] = false;
		pRelease_[ counterKey ] = false;
		pRepeat_[ counterKey ] = 0;
	}
}
