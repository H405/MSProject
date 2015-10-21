//==============================================================================
//
// File   : InputPad.cpp
// Brief  : �Q�[���p�b�h���̓N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <tchar.h>
#include "InputPad.h"

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
InputPad::InputPad( void ) : Input()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
InputPad::~InputPad( void )
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
int InputPad::Initialize( IDirectInput8* pDirectInput, HWND windowHandle )
{
	// ��{�N���X�̏���
	HRESULT result;		// ���s����
	result = Input::Initialize( pDirectInput, windowHandle );
	if( result != 0 )
	{
		return result;
	}

	// �f�o�C�X�I�u�W�F�N�g�̗�
	result = pDirectInput_->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumDevicesCallback, this, DIEDFL_ATTACHEDONLY );
	if( FAILED( result ) )
	{
		MessageBox(  nullptr, _T( "�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
		return 1;
	}

	// �W���C�X�e�B�b�N�̐ݒ�
	for( int counterJoystick = 0; counterJoystick < countDevice_; ++counterJoystick )
	{
		// �G���[�`�F�b�N
		if( pDevice_ == nullptr )
		{
			MessageBox( NULL, _T( "�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
			return 1;
		}

		// �f�[�^�t�H�[�}�b�g��ݒ�
		result = pDevice_->SetDataFormat( &c_dfDIJoystick );
		if( FAILED( result ) )
		{
			MessageBox( NULL, _T( "�f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
			return 1;
		}

		// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		result = pDevice_->SetCooperativeLevel( windowHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) );
		if( FAILED( result ) )
		{
			MessageBox( NULL, _T( "�������[�h�̐ݒ�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
			return 1;
		}

		// �\�͏��̎擾
		DIDEVCAPS	deviceCpacity;		// �f�o�C�X�̔\��
		deviceCpacity.dwSize = sizeof( DIDEVCAPS );
		result = pDevice_->GetCapabilities( &deviceCpacity );
		if( FAILED( result ) )
		{
			MessageBox( NULL, _T( "�\�͏��̎擾�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
			return 1;
		}
		result = pDevice_->EnumObjects( EnumDeviceObjectsCallback, reinterpret_cast< void* >( this ), DIDFT_AXIS );
		if( FAILED( result ) )
		{
			MessageBox( NULL, _T( "����̐ݒ�Ɏ��s���܂���" ), _T( "�G���[" ), MB_OK );
			return 1;
		}

		// �W���C�X�e�B�b�N�ւ̃A�N�Z�X�����l��
		result = pDevice_->Poll(); 
		if( FAILED( result ) ) 
		{
			result = pDevice_->Acquire();
			while(result == DIERR_INPUTLOST) 
			{
				result = pDevice_->Acquire();
			}
			return 0; 
		}
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int InputPad::Finalize( void )
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
int InputPad::Reinitialize( IDirectInput8* pDirectInput, HWND windowHandle )
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
// Arg    : InputPad* pOut						: �R�s�[��A�h���X
//==============================================================================
int InputPad::Copy( InputPad* pOut ) const
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
void InputPad::Update( void )
{
	// �G���[�`�F�b�N
	if( pDevice_ == nullptr )
	{
		return;
	}

	// ���͂̎󂯎��
	DIJOYSTATE	stateJoystick;		// �W���C�X�e�B�b�N��Ԏ󂯎��p
	if( FAILED( pDevice_->Poll() ) )
	{
		pDevice_->Acquire();
		return;
	}
	pDevice_->GetDeviceState( sizeof( DIJOYSTATE ), &stateJoystick );

	// ���͏��̃��Z�b�g
	for( int counterKey = 0; counterKey < TYPE_MAX; ++counterKey )
	{
		pTrigger_[ counterKey ] = false;
		pRelease_[ counterKey ] = false;
	}

	// ���X�e�B�b�N�����͏��̍쐬
	if( !(stateJoystick_.lX <= minimumThresholdLeft_) && (stateJoystick.lX <= minimumThresholdLeft_) )
	{
		pTrigger_[ TYPE_KEY_LEFT_LEFT ] = true;
	}
	if( (stateJoystick_.lX <= minimumThresholdLeft_) && !(stateJoystick.lX <= minimumThresholdLeft_) )
	{
		pRelease_[ TYPE_KEY_LEFT_LEFT ] = true;
	}
	if( (stateJoystick.lX <= minimumThresholdLeft_) )
	{
		++pRepeat_[ TYPE_KEY_LEFT_LEFT ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_LEFT_LEFT ] = 0;
	}
	
	// ���X�e�B�b�N�E���͏��̍쐬
	if( !(stateJoystick_.lX >= maximumThresholdLeft_) && (stateJoystick.lX >= maximumThresholdLeft_) )
	{
		pTrigger_[ TYPE_KEY_LEFT_RIGHT ] = true;
	}
	if( (stateJoystick_.lX >= maximumThresholdLeft_) && !(stateJoystick.lX >= maximumThresholdLeft_) )
	{
		pRelease_[ TYPE_KEY_LEFT_RIGHT ] = true;
	}
	if( (stateJoystick.lX >= maximumThresholdLeft_) )
	{
		++pRepeat_[ TYPE_KEY_LEFT_RIGHT ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_LEFT_RIGHT ] = 0;
	}
	
	// ���X�e�B�b�N����͏��̍쐬
	if( !(stateJoystick_.lY <= minimumThresholdLeft_) && (stateJoystick.lY <= minimumThresholdLeft_) )
	{
		pTrigger_[ TYPE_KEY_LEFT_UP ] = true;
	}
	if( (stateJoystick_.lY <= minimumThresholdLeft_) && !(stateJoystick.lY <= minimumThresholdLeft_) )
	{
		pRelease_[ TYPE_KEY_LEFT_UP ] = true;
	}
	if( (stateJoystick.lY <= minimumThresholdLeft_) )
	{
		++pRepeat_[ TYPE_KEY_LEFT_UP ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_LEFT_UP ] = 0;
	}
	
	// ���X�e�B�b�N�����͏��̍쐬
	if( !(stateJoystick_.lY >= maximumThresholdLeft_) && (stateJoystick.lY >= maximumThresholdLeft_) )
	{
		pTrigger_[ TYPE_KEY_LEFT_DOWN ] = true;
	}
	if( (stateJoystick_.lY >= maximumThresholdLeft_) && !(stateJoystick.lY >= maximumThresholdLeft_) )
	{
		pRelease_[ TYPE_KEY_LEFT_DOWN ] = true;
	}
	if( (stateJoystick.lY >= maximumThresholdLeft_) )
	{
		++pRepeat_[ TYPE_KEY_LEFT_DOWN ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_LEFT_DOWN ] = 0;
	}
	
	// �E�X�e�B�b�N�����͏��̍쐬
	if( !(stateJoystick_.lZ <= minimumThresholdRight_) && (stateJoystick.lZ <= minimumThresholdRight_) )
	{
		pTrigger_[ TYPE_KEY_RIGHT_LEFT ] = true;
	}
	if( (stateJoystick_.lZ <= minimumThresholdRight_) && !(stateJoystick.lZ <= minimumThresholdRight_) )
	{
		pRelease_[ TYPE_KEY_RIGHT_LEFT ] = true;
	}
	if( (stateJoystick.lZ <= minimumThresholdRight_) )
	{
		++pRepeat_[ TYPE_KEY_RIGHT_LEFT ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_RIGHT_LEFT ] = 0;
	}
	
	// �E�X�e�B�b�N�E���͏��̍쐬
	if( !(stateJoystick_.lZ >= maximumThresholdRight_) && (stateJoystick.lZ >= maximumThresholdRight_) )
	{
		pTrigger_[ TYPE_KEY_RIGHT_RIGHT ] = true;
	}
	if( (stateJoystick_.lZ >= maximumThresholdRight_) && !(stateJoystick.lZ >= maximumThresholdRight_) )
	{
		pRelease_[ TYPE_KEY_RIGHT_RIGHT ] = true;
	}
	if( (stateJoystick.lZ >= maximumThresholdRight_) )
	{
		++pRepeat_[ TYPE_KEY_RIGHT_RIGHT ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_RIGHT_RIGHT ] = 0;
	}
	
	// �E�X�e�B�b�N����͏��̍쐬
	if( !(stateJoystick_.lRz <= minimumThresholdRight_) && (stateJoystick.lRz <= minimumThresholdRight_) )
	{
		pTrigger_[ TYPE_KEY_RIGHT_UP ] = true;
	}
	if( (stateJoystick_.lRz <= minimumThresholdRight_) && !(stateJoystick.lRz <= minimumThresholdRight_) )
	{
		pRelease_[ TYPE_KEY_RIGHT_UP ] = true;
	}
	if( (stateJoystick.lRz <= minimumThresholdRight_) )
	{
		++pRepeat_[ TYPE_KEY_RIGHT_UP ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_RIGHT_UP ] = 0;
	}
	
	// �E�X�e�B�b�N�����͏��̍쐬
	if( !(stateJoystick_.lRz >= maximumThresholdRight_) && (stateJoystick.lRz >= maximumThresholdRight_) )
	{
		pTrigger_[ TYPE_KEY_RIGHT_DOWN ] = true;
	}
	if( (stateJoystick_.lRz >= maximumThresholdRight_) && !(stateJoystick.lRz >= maximumThresholdRight_) )
	{
		pRelease_[ TYPE_KEY_RIGHT_DOWN ] = true;
	}
	if( (stateJoystick.lRz >= maximumThresholdRight_) )
	{
		++pRepeat_[ TYPE_KEY_RIGHT_DOWN ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_RIGHT_DOWN ] = 0;
	}
	
	// �{�^�����͏��̍쐬
	for( int counterJoystick = 0; counterJoystick < TYPE_MAX - TYPE_BUTTON_00; ++counterJoystick )
	{
		// �g���K���̍X�V
		if( !(stateJoystick_.rgbButtons[ counterJoystick] & 0x80) && (stateJoystick.rgbButtons[ counterJoystick] & 0x80) )
		{
			pTrigger_[ counterJoystick + TYPE_BUTTON_00 ] = true;
		}

		// �����[�X���̍X�V
		if( (stateJoystick_.rgbButtons[ counterJoystick] & 0x80) && !(stateJoystick.rgbButtons[ counterJoystick] & 0x80) )
		{
			pRelease_[ counterJoystick + TYPE_BUTTON_00 ] = true;
		}

		// ���s�[�g���̍X�V
		if( (stateJoystick.rgbButtons[ counterJoystick] & 0x80) )
		{
			++pRepeat_[ counterJoystick + TYPE_BUTTON_00 ];
		}
		else
		{
			pRepeat_[ counterJoystick + TYPE_BUTTON_00 ] = 0;
		}
	}

	// �W���C�X�e�B�b�N��Ԃ̍X�V
	stateJoystick_ = stateJoystick;
}

//==============================================================================
// Brief  : �v���X����
// Return : bool								: �v���X����
// Arg    : int typeKey							: ���肷��L�[�̎��
//==============================================================================
bool InputPad::IsPress( int typeKey ) const
{
	// �v���X����
	if( typeKey < TYPE_BUTTON_00 )
	{	// �����L�[�̎�
		switch( typeKey )
		{
		case TYPE_KEY_LEFT_UP:
			if(stateJoystick_.lY <= minimumThresholdLeft_)
			{
				return true;
			}
			break;
		case TYPE_KEY_LEFT_DOWN:
			if(stateJoystick_.lY >= maximumThresholdLeft_)
			{
				return true;
			}
			break;
		case TYPE_KEY_LEFT_LEFT:
			if(stateJoystick_.lX <= minimumThresholdLeft_)
			{
				return true;
			}
			break;
		case TYPE_KEY_LEFT_RIGHT:
			if(stateJoystick_.lX >= maximumThresholdLeft_)
			{
				return true;
			}
			break;
		case TYPE_KEY_RIGHT_UP:
			if(stateJoystick_.lRz <= minimumThresholdRight_)
			{
				return true;
			}
			break;
		case TYPE_KEY_RIGHT_DOWN:
			if(stateJoystick_.lRz >= maximumThresholdRight_)
			{
				return true;
			}
			break;
		case TYPE_KEY_RIGHT_LEFT:
			if(stateJoystick_.lZ <= minimumThresholdRight_)
			{
				return true;
			}
			break;
		case TYPE_KEY_RIGHT_RIGHT:
			if(stateJoystick_.lZ >= maximumThresholdRight_)
			{
				return true;
			}
			break;
		default:
			break;
		}
	}
	else
	{	// �{�^���̎�
		if( stateJoystick_.rgbButtons[ typeKey - TYPE_BUTTON_00 ] & 0x80 )
		{
			return true;
		}
	}

	// �l�̕ԋp
	return false;
}

//==============================================================================
// Brief  : �g���K�[����
// Return : bool								: �g���K�[����
// Arg    : int typeKey							: ���肷��L�[�̎��
//==============================================================================
bool InputPad::IsTrigger( int typeKey ) const
{
	// �l�̕ԋp
	return pTrigger_[ typeKey ];
}

//==============================================================================
// Brief  : �����[�X����
// Return : bool								: �����[�X����
// Arg    : int typeKey							: ���肷��L�[�̎��
//==============================================================================
bool InputPad::IsRelease( int typeKey ) const
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
bool InputPad::IsRepeat( int typeKey, int timeBegin, int timeInterval ) const
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
int InputPad::GetTimePress( int typeKey ) const
{
	// �l�̕ԋp
	return pRepeat_[ typeKey ];
}

//==============================================================================
// Brief  : ���X�e�B�b�N��X���X���̎擾
// Return : float								: �X������
// Arg    : void								: �Ȃ�
//==============================================================================
float InputPad::GetAxisLeftX( void ) const
{
	// �l�̕ԋp
	return static_cast< float >( stateJoystick_.lX ) / maximumTiltStick_;
}

//==============================================================================
// Brief  : ���X�e�B�b�N��Y���X���̎擾
// Return : float								: �X������
// Arg    : void								: �Ȃ�
//==============================================================================
float InputPad::GetAxisLeftY( void ) const
{
	// �l�̕ԋp
	return static_cast< float >( stateJoystick_.lY ) / maximumTiltStick_;
}

//==============================================================================
// Brief  : �E�X�e�B�b�N��X���X���̎擾
// Return : float								: �X������
// Arg    : void								: �Ȃ�
//==============================================================================
float InputPad::GetAxisRightX( void ) const
{
	// �l�̕ԋp
	return static_cast< float >( stateJoystick_.lZ ) / maximumTiltStick_;
}

//==============================================================================
// Brief  : �E�X�e�B�b�N��Y���X���̎擾
// Return : float								: �X������
// Arg    : void								: �Ȃ�
//==============================================================================
float InputPad::GetAxisRightY( void ) const
{
	// �l�̕ԋp
	return static_cast< float >( stateJoystick_.lRz ) / maximumTiltStick_;
}

//==============================================================================
// Brief  : �Q�[���p�b�h���̎擾
// Return : int									: �Q�[���p�b�h��
// Arg    : void								: �Ȃ�
//==============================================================================
int InputPad::GetCount( void ) const
{
	// �l�̕ԋp
	return countDevice_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void InputPad::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	countDevice_ = 0;
	maximumDevice_ = 0;
	maximumTiltStick_ = 1000;
	minimumTiltStick_ = -1000;
	maximumThresholdLeft_ = 30;
	maximumThresholdRight_ = -30;
	minimumThresholdLeft_ = 30;
	minimumThresholdRight_ = -30;
	for( int counterKey = 0; counterKey < TYPE_MAX; ++counterKey )
	{
		pState_[ counterKey ] = false;
		pTrigger_[ counterKey ] = false;
		pRelease_[ counterKey ] = false;
		pRepeat_[ counterKey ] = 0;
	}
}

//==============================================================================
// Brief  : �f�o�C�X�̗�
// Return : BOOL CALLBACK						: ���s����
// Arg    : const DIDEVICEINSTANCE* pDeviceInstance	: �f�o�C�X�̃C���X�^���X
// Arg    : VOID* pContext						: �l�̎󂯎��p
//==============================================================================
BOOL CALLBACK InputPad::EnumDevicesCallback( const DIDEVICEINSTANCE* pDeviceInstance, VOID* pContext )
{
	// �f�o�C�X�̍쐬
	HRESULT		result;					// ���s����
	InputPad*	pThis = nullptr;		// �N���X�̃|�C���^
	pThis = reinterpret_cast< InputPad* >( pContext );
	result = pThis->pDirectInput_->CreateDevice(pDeviceInstance->guidInstance, &pThis->pDevice_, nullptr);
	if( FAILED( result ) )
	{
		return DIENUM_CONTINUE;
	}

	// �K�v�Ȑ�����������
	++pThis->countDevice_;
	if(pThis->countDevice_ < pThis->maximumDevice_)
	{
		return DIENUM_CONTINUE;
	}
	
	// �񋓂̏I��
	return DIENUM_STOP;
}

//==============================================================================
// Brief  : �f�o�C�X�I�u�W�F�N�g�̗�
// Return : BOOL CALLBACK						: ���s����
// Arg    : const DIDEVICEOBJECTINSTANCE* pDeviceObjectInstance	: �f�o�C�X�I�u�W�F�N�g�̃C���X�^���X
// Arg    : VOID* pContext						: �l�̎󂯎��p
//==============================================================================
BOOL CALLBACK InputPad::EnumDeviceObjectsCallback( const DIDEVICEOBJECTINSTANCE* pDeviceObjectInstance, VOID* pContext )
{
	// �f�o�C�X�̐ݒ���쐬
	DIPROPRANGE propertyPad;			// �f�o�C�X�̐ݒ�
	HRESULT		result;					// ���s����
	InputPad*	pThis = nullptr;		// �N���X�̃|�C���^
	propertyPad.diph.dwSize = sizeof( DIPROPRANGE );
	propertyPad.diph.dwHeaderSize = sizeof( DIPROPHEADER );
	propertyPad.diph.dwHow = DIPH_BYID;
	propertyPad.diph.dwObj = pDeviceObjectInstance->dwType;
	propertyPad.lMin = (pThis)->minimumTiltStick_;
	propertyPad.lMax = (pThis)->maximumTiltStick_;
	
	// �쐬�r��
	result = pThis->pDevice_->SetProperty(DIPROP_RANGE, &propertyPad.diph);
	if( FAILED( result ) )
	{
		return DIENUM_STOP;
	}
	
	// ���s
	return DIENUM_CONTINUE;
}
