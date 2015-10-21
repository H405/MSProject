//==============================================================================
//
// File   : WindowMain.cpp
// Brief  : ���C���E�B���h�E�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "WindowMain.h"

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
WindowMain::WindowMain( void ) : Window()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
WindowMain::~WindowMain( void )
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
int WindowMain::Initialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Window::Initialize( instanceHandle, typeShow, width, height, pCaption, pNameClass );
	if( result != 0 )
	{
		return result;
	}

	// �ϐ��̐ݒ�
	pThis_ = this;
	width_ = width;
	height_ = height;

	// �E�B���h�E�N���X�̐ݒ�
	windowClass_.cbSize = sizeof( WNDCLASSEX );
	windowClass_.style = CS_CLASSDC;
	windowClass_.lpfnWndProc = WindowProcedureDefault;
	windowClass_.cbClsExtra = 0;
	windowClass_.cbWndExtra = 0;
	windowClass_.hInstance = instanceHandle;
	windowClass_.hIcon = NULL;
	windowClass_.hCursor = LoadCursor( NULL, IDC_ARROW );
	windowClass_.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	windowClass_.lpszMenuName = NULL;
	windowClass_.lpszClassName = pNameClass;
	windowClass_.hIconSm = NULL;

	// �E�B���h�E�̓o�^
	RegisterClassEx( &windowClass_ );

	// �E�B���h�E�̍쐬
	windowHandle_ = CreateWindowEx(	0,
									pNameClass,
									pCaption,
									WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
									CW_USEDEFAULT,
									CW_USEDEFAULT,
									width,
									height,
									windowHandleParent_,
									NULL,
									instanceHandle,
									NULL );
	if( windowHandle_ == NULL )
	{
		return 1;
	}

	// �E�B���h�E�̕\��
	ShowWindow( windowHandle_, typeShow );
	UpdateWindow( windowHandle_ );

	// �E�B���h�E�̑傫���𒲐�
	int		widthSet;		// �N���C�A���g�̈撲���p��
	int		heightSet;		// �N���C�A���g�̈撲���p����
	RECT	rectWindow;		// �E�B���h�E�̈�̑傫��
	RECT	rectClient;		// �N���C�A���g�̈�̑傫��
	GetClientRect( windowHandle_, &rectClient );
	GetWindowRect( windowHandle_, &rectWindow );
	GetClientRect( windowHandle_, &rectClient );
	widthSet = width + (rectWindow.right - rectWindow.left) - (rectClient.right - rectClient.left);
	heightSet = height + (rectWindow.bottom - rectWindow.top) - (rectClient.bottom - rectClient.top);
	SetWindowPos( windowHandle_, NULL, 0, 0, widthSet, heightSet, SWP_NOMOVE | SWP_NOZORDER );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int WindowMain::Finalize( void )
{
	// �i�[�̈�̊J��

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Window::Finalize();
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
// Arg    : HINSTANCE instanceHandle			: �C���X�^���X�n���h��
// Arg    : int typeShow						: �\���̎��
// Arg    : int width							: ��
// Arg    : int height							: ����
// Arg    : TCHAR* pCaption						: �L���v�V����
// Arg    : TCHAR* pNameClass					: �N���X��
//==============================================================================
int WindowMain::Reinitialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass )
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
// Arg    : WindowMain* pOut					: �R�s�[��A�h���X
//==============================================================================
int WindowMain::Copy( WindowMain* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �E�B���h�E�v���V�[�W��
// Return : LRESULT								: ���s����
// Arg    : HWND windowHandle					: �E�B���h�E�n���h��
// Arg    : UINT message						: ���b�Z�[�W�̎��ʎq
// Arg    : WPARAM wParam						: �p�����[�^
// Arg    : LPARAM lParam						: �p�����[�^
//==============================================================================
LRESULT WindowMain::WindowProcedure( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam )
{
	// ���b�Z�[�W���Ƃ̏���
	switch( message )
	{
	// �E�B���h�E���쐬���ꂽ�Ƃ�
	case WM_CREATE:
		break;

	// �E�B���h�E���j�������Ƃ�
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	// �E�B���h�E��������Ƃ�
	case WM_CLOSE:
		DestroyWindow( windowHandle_ );
		windowHandle_ = NULL;
		break;

	// �L�[���͂��������Ƃ�
	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_ESCAPE:
			DestroyWindow( windowHandle_ );
			windowHandle_ = NULL;
			break;
		}
		break;

	// ���̑�
	default:
		break;
	}

	// ����̏������
	return DefWindowProc( windowHandle, message, wParam, lParam );
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void WindowMain::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
