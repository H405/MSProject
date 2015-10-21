//==============================================================================
//
// File   : InputMouse.cpp
// Brief  : �}�E�X���̓N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <tchar.h>
#include "InputMouse.h"

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
InputMouse::InputMouse( void ) : Input()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
InputMouse::~InputMouse( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : IDirectInput8* pDirectInput			: DirectInput�I�u�W�F�N�g
// Arg    : HWND windowHandle					: �E�B���h�E�n���h��
// Arg    : int widthScreen						: �X�N���[����
// Arg    : int heightScreen					: �X�N���[������
//==============================================================================
int InputMouse::Initialize( IDirectInput8* pDirectInput, HWND windowHandle, int widthScreen, int heightScreen )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Input::Initialize( pDirectInput, windowHandle );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	widthScreen_ = widthScreen;
	heightScreen_ = heightScreen;

	// �f�o�C�X�I�u�W�F�N�g���쐬
	if( FAILED( pDirectInput->CreateDevice( GUID_SysMouse, &pDevice_, NULL ) ) )
	{
		MessageBox( NULL, _T( "�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
		return 1;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if( FAILED( pDevice_->SetDataFormat( &c_dfDIMouse2 ) ) )
	{
		MessageBox( NULL, _T( "�f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
		return 1;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if( FAILED( pDevice_->SetCooperativeLevel( windowHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) ) ) )
	{
		MessageBox( NULL, _T( "�������[�h�̐ݒ�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
		return 1;
	}

	// �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
	DIPROPDWORD propertyMouse;
	propertyMouse.diph.dwSize		= sizeof( propertyMouse ); 
	propertyMouse.diph.dwHeaderSize	= sizeof( propertyMouse.diph ); 
	propertyMouse.diph.dwObj		= 0;
	propertyMouse.diph.dwHow		= DIPH_DEVICE;
	propertyMouse.dwData			= DIPROPAXISMODE_REL;
	if( FAILED( pDevice_->SetProperty( DIPROP_AXISMODE, &propertyMouse.diph ) ) )
	{
		MessageBox( NULL, _T( "�����[�h�̐ݒ�Ɏ��s" ), _T( "Direct Input Error" ), MB_OK );
		return 1;
	}

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	pDevice_->Acquire();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int InputMouse::Finalize( void )
{
	// �J�[�\���̕\��
	Show();

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
// Arg    : int widthScreen						: �X�N���[����
// Arg    : int heightScreen					: �X�N���[������
//==============================================================================
int InputMouse::Reinitialize( IDirectInput8* pDirectInput, HWND windowHandle, int widthScreen, int heightScreen )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDirectInput, windowHandle, widthScreen, heightScreen );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : InputMouse* pOut					: �R�s�[��A�h���X
//==============================================================================
int InputMouse::Copy( InputMouse* pOut ) const
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
void InputMouse::Update( void )
{
	// �}�E�X���W�̎擾
	GetCursorPos( &positionWindow_ );
	ScreenToClient( windowHandle_, &positionWindow_ );
	position_ = positionWindow_;
	if( position_.x < 0 )
	{
		position_.x = 0;
	}
	else if( position_.x >= static_cast< LONG >( widthScreen_ ) )
	{
		position_.x = widthScreen_ - 1;
	}
	if( position_.y < 0 )
	{
		position_.y = 0;
	}
	else if( position_.y >= static_cast< LONG >( heightScreen_ ) )
	{
		position_.y = heightScreen_ - 1;
	}

	// �}�E�X���X�V
	DIMOUSESTATE2	stateMouse;						// �}�E�X���擾
	BYTE			aMouseState[ TYPE_MAX ];		// �}�E�X��Ԋi�[���[�N
	if( SUCCEEDED( pDevice_->GetDeviceState( sizeof( DIMOUSESTATE2 ), &stateMouse ) ) )
	{
		aMouseState[ TYPE_LEFT ] = (stateMouse.rgbButtons[ 0 ] & 0x80);
		aMouseState[ TYPE_RIGHT ] = (stateMouse.rgbButtons[ 1 ] & 0x80);
		aMouseState[ TYPE_MIDDLE ] = (stateMouse.rgbButtons[ 2 ] & 0x80);
		vectorMove_.x = stateMouse.lX;
		vectorMove_.y = stateMouse.lY;
		moveWheel_ = stateMouse.lZ;
		memset( &pTrigger_[ 0 ], 0x00, sizeof( pTrigger_ ) );
		memset( &pRelease_[ 0 ], 0x00, sizeof( pRelease_ ) );
		for( int nCntMouse = 0; nCntMouse < TYPE_MAX; ++nCntMouse )
		{
			// �g���K���̍X�V
			if( !(pState_[ nCntMouse ] & 0x80) && (aMouseState[ nCntMouse ] & 0x80) )
			{
				pTrigger_[ nCntMouse ] = true;
			}

			// �����[�X���̍X�V
			if( (pState_[ nCntMouse ] & 0x80) && !(aMouseState[ nCntMouse ] & 0x80) )
			{
				pRelease_[ nCntMouse ] = true;
			}

			// ���s�[�g���̍X�V
			if( (aMouseState[ nCntMouse ] & 0x80) )
			{
				++pRepeat_[ nCntMouse ];
			}
			else
			{
				pRepeat_[ nCntMouse ] = 0;
			}

			// �L�[�{�[�h��Ԃ̍X�V
			pState_[ nCntMouse ] = aMouseState[ nCntMouse ];
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
bool InputMouse::IsPress( int typeKey ) const
{
	// �l�̕ԋp
	return (pState_[ typeKey ] & 0x80) != 0;
}

//==============================================================================
// Brief  : �g���K�[����
// Return : bool								: �g���K�[����
// Arg    : int typeKey							: ���肷��L�[�̎��
//==============================================================================
bool InputMouse::IsTrigger( int typeKey ) const
{
	// �l�̕ԋp
	return pTrigger_[ typeKey ];
}

//==============================================================================
// Brief  : �����[�X����
// Return : bool								: �����[�X����
// Arg    : int typeKey							: ���肷��L�[�̎��
//==============================================================================
bool InputMouse::IsRelease( int typeKey ) const
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
bool InputMouse::IsRepeat( int typeKey, int timeBegin, int timeInterval ) const
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
int InputMouse::GetTimePress( int typeKey ) const
{
	// �l�̕ԋp
	return pRepeat_[ typeKey ];
}

//==============================================================================
// Brief  : �J�[�\���̕\��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void InputMouse::Show( void )
{
	// �J�[�\���̕\��
	while( ShowCursor( TRUE ) < 0 ) {}
}

//==============================================================================
// Brief  : �J�[�\���̔�\��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void InputMouse::Hide( void )
{
	// �J�[�\���̔�\��
	while( ShowCursor( FALSE ) >= 0 ) {}
}

//==============================================================================
// Brief  : X���W�̎擾
// Return : int									: X���W
// Arg    : void								: �Ȃ�
//==============================================================================
int InputMouse::GetPositionX( void ) const
{
	// �l�̕ԋp
	return position_.x;
}

//==============================================================================
// Brief  : Y���W�̎擾
// Return : int									: Y���W
// Arg    : void								: �Ȃ�
//==============================================================================
int InputMouse::GetPositionY( void ) const
{
	// �l�̕ԋp
	return position_.y;
}

//==============================================================================
// Brief  : �E�B���h�EX���W�̎擾
// Return : int									: X���W
// Arg    : void								: �Ȃ�
//==============================================================================
int InputMouse::GetPositionWindowX( void ) const
{
	// �l�̕ԋp
	return positionWindow_.x;
}

//==============================================================================
// Brief  : �E�B���h�EY���W�̎擾
// Return : int									: Y���W
// Arg    : void								: �Ȃ�
//==============================================================================
int InputMouse::GetPositionWindowY( void ) const
{
	// �l�̕ԋp
	return positionWindow_.y;
}

//==============================================================================
// Brief  : X�ړ��l�̎擾
// Return : int									: X�ړ��l
// Arg    : void								: �Ȃ�
//==============================================================================
int InputMouse::GetMoveX( void ) const
{
	// �l�̕ԋp
	return vectorMove_.x;
}

//==============================================================================
// Brief  : Y�ړ��l�̎擾
// Return : int									: Y�ړ��l
// Arg    : void								: �Ȃ�
//==============================================================================
int InputMouse::GetMoveY( void ) const
{
	// �l�̕ԋp
	return vectorMove_.y;
}

//==============================================================================
// Brief  : �z�C�[���ړ��l�̎擾
// Return : int									: �z�C�[���ړ��l
// Arg    : void								: �Ȃ�
//==============================================================================
int InputMouse::GetMoveWheel( void ) const
{
	// �l�̕ԋp
	return moveWheel_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void InputMouse::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	windowHandle_ = NULL;
	widthScreen_ = 0;
	heightScreen_ = 0;
	moveWheel_ = 0;
	for( int counterKey = 0; counterKey < TYPE_MAX; ++counterKey )
	{
		pState_[ counterKey ] = false;
		pTrigger_[ counterKey ] = false;
		pRelease_[ counterKey ] = false;
		pRepeat_[ counterKey ] = 0;
	}
}
