//==============================================================================
//
// File   : Window.cpp
// Brief  : �E�B���h�E�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Window.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
Window* Window::pThis_;		// ���g�̃A�h���X

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Window::Window( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Window::~Window( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : HINSTANCE instanceHandle			: �C���X�^���X�n���h��
// Arg    : int typeShow						: �\���̎��
// Arg    : int width							: ��
// Arg    : int height							: ����
// Arg    : TCHAR* pCaption						: �L���v�V����
// Arg    : TCHAR* pNameClass					: �N���X��
//==============================================================================
int Window::Initialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass )
{
	// ���g�p�錾
	UNREFERENCED_PARAMETER( instanceHandle );
	UNREFERENCED_PARAMETER( typeShow );
	UNREFERENCED_PARAMETER( width );
	UNREFERENCED_PARAMETER( height );
	UNREFERENCED_PARAMETER( pCaption );
	UNREFERENCED_PARAMETER( pNameClass );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Window::Finalize( void )
{
	// �o�^�̉���
	UnregisterClass( windowClass_.lpszClassName, windowClass_.hInstance );

	// �E�B���h�E�̔j��
	if( windowHandle_ != NULL )
	{
		DestroyWindow( windowHandle_ );
		windowHandle_ = NULL;
	}

	// �i�[�̈�̊J��
	delete[] pThis_;
	pThis_ = nullptr;

	// �N���X�����̏�����
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : HINSTANCE instanceHandle			: �C���X�^���X�n���h��
// Arg    : int typeShow						: �\���̎��
// Arg    : int width							: ��
// Arg    : int height							: ����
// Arg    : TCHAR* pCaption						: �L���v�V����
// Arg    : TCHAR* pNameClass					: �N���X��
//==============================================================================
int Window::Reinitialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( instanceHandle, typeShow, width, height, pCaption, pNameClass );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : Window* pOut						: �R�s�[��A�h���X
//==============================================================================
int Window::Copy( Window* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �f�t�H���g�̃E�B���h�E�v���V�[�W��
// Return : LRESULT CALLBACK					: ���s����
// Arg    : HWND windowHandle					: �E�B���h�E�n���h��
// Arg    : UINT message						: ���b�Z�[�W�̎��ʎq
// Arg    : WPARAM wParam						: �p�����[�^
// Arg    : LPARAM lParam						: �p�����[�^
//==============================================================================
LRESULT CALLBACK Window::WindowProcedureDefault( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam )
{
	// ��������
	Window*	pWindow = reinterpret_cast< Window* >( GetWindowLong( windowHandle, GWL_USERDATA ) );		// �����Ă����E�B���h�E�̃|�C���^
	if( pWindow != nullptr )
	{
		// �ʂ̏���
		LRESULT	ret = pWindow->WindowProcedure( windowHandle, message, wParam, lParam );
		return ret;
	}
	else
	{
		// ���g�̃|�C���^��o�^
		if( message == WM_CREATE || message == WM_INITDIALOG )
		{
			SetWindowLong( windowHandle, GWL_USERDATA, (LONG)pThis_ );
			SendMessage( windowHandle, message, wParam, lParam );
			pThis_ = nullptr;
		}
	}

	// ����̏������
	return DefWindowProc( windowHandle, message, wParam, lParam );
}

//==============================================================================
// Brief  : �E�B���h�E�v���V�[�W��
// Return : LRESULT								: ���s����
// Arg    : HWND windowHandle					: �E�B���h�E�n���h��
// Arg    : UINT message						: ���b�Z�[�W�̎��ʎq
// Arg    : WPARAM wParam						: �p�����[�^
// Arg    : LPARAM lParam						: �p�����[�^
//==============================================================================
LRESULT Window::WindowProcedure( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam )
{
	// ���b�Z�[�W���Ƃ̏���
	switch( message )
	{
	// �E�B���h�E���쐬���ꂽ�Ƃ�
	case WM_CREATE:
		break;

	// �E�B���h�E���j�������Ƃ�
	case WM_DESTROY:
		break;

	// �L�[���͂��������Ƃ�
	case WM_KEYDOWN:
		break;

	// �}�E�X�̍��{�^���������ꂽ�Ƃ�
	case WM_LBUTTONDOWN:
		SetFocus( windowHandle );
		break;

	// ���̑�
	default:
		break;
	}

	// ����̏������
	return DefWindowProc( windowHandle, message, wParam, lParam );
}

//==============================================================================
// Brief  : �E�B���h�E�n���h���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : HWND value							: �ݒ肷��l
//==============================================================================
void Window::SetWindowHandle( HWND value )
{
	// �l�̐ݒ�
	windowHandle_ = value;
}

//==============================================================================
// Brief  : �E�B���h�E�n���h���̎擾
// Return : HWND								: �擾����l
// Arg    : void								: �Ȃ�
//==============================================================================
HWND Window::GetWindowHandle( void ) const
{
	// �l�̕ԋp
	return windowHandle_;
}

//==============================================================================
// Brief  : �e�E�B���h�E�n���h���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const HWND& value					: �ݒ肷��l
//==============================================================================
void Window::SetWindowHandleParent( const HWND& value )
{
	// �l�̐ݒ�
	windowHandleParent_ = value;
}

//==============================================================================
// Brief  : �e�E�B���h�E�n���h���̎擾
// Return : void								: �Ȃ�
// Arg    : HWND* pOut							: �l�̊i�[�A�h���X
//==============================================================================
void Window::GetWindowHandleParent( HWND* pOut ) const
{
	// �l�̕ԋp
	*pOut = windowHandleParent_;
}

//==============================================================================
// Brief  : ���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void Window::SetWidth( int value )
{
	// �l�̐ݒ�
	width_ = value;
}

//==============================================================================
// Brief  : ���̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int Window::GetWidth( void ) const
{
	// �l�̕ԋp
	return width_;
}

//==============================================================================
// Brief  : �����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void Window::SetHeight( int value )
{
	// �l�̐ݒ�
	height_ = value;
}

//==============================================================================
// Brief  : �����̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int Window::GetHeight( void ) const
{
	// �l�̕ԋp
	return height_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Window::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pThis_ = nullptr;
	ZeroMemory( &windowClass_, sizeof( WNDCLASSEX ) );
	windowHandle_ = NULL;
	windowHandleParent_ = NULL;
	width_ = 0;
	height_ = 0;
}
