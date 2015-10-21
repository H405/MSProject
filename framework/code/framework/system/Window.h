//==============================================================================
//
// File   : Window.h
// Brief  : �E�B���h�E�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_WINDOW_H
#define MY_WINDOW_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <windows.h>
#include <stdio.h>

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************

//******************************************************************************
// �N���X��`
//******************************************************************************
class Window
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	Window( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual ~Window( void );

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
	virtual int Initialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual int Finalize( void );

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
	virtual int Reinitialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : Window* pOut						: �R�s�[��A�h���X
	//==============================================================================
	virtual int Copy( Window* pOut ) const;

	//==============================================================================
	// Brief  : �f�t�H���g�̃E�B���h�E�v���V�[�W��
	// Return : LRESULT CALLBACK					: ���s����
	// Arg    : HWND windowHandle					: �E�B���h�E�n���h��
	// Arg    : UINT message						: ���b�Z�[�W�̎��ʎq
	// Arg    : WPARAM wParam						: �p�����[�^
	// Arg    : LPARAM lParam						: �p�����[�^
	//==============================================================================
	static LRESULT CALLBACK WindowProcedureDefault( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam );

	//==============================================================================
	// Brief  : �E�B���h�E�v���V�[�W��
	// Return : LRESULT								: ���s����
	// Arg    : HWND windowHandle					: �E�B���h�E�n���h��
	// Arg    : UINT message						: ���b�Z�[�W�̎��ʎq
	// Arg    : WPARAM wParam						: �p�����[�^
	// Arg    : LPARAM lParam						: �p�����[�^
	//==============================================================================
	virtual LRESULT WindowProcedure( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetWindowHandle( HWND value );
	HWND GetWindowHandle( void ) const;
	void SetWindowHandleParent( const HWND& value );
	void GetWindowHandleParent( HWND* pOut ) const;
	void SetWidth( int value );
	int GetWidth( void ) const;
	void SetHeight( int value );
	int GetHeight( void ) const;

protected:
	static Window*	pThis_;						// ���g�̃A�h���X
	WNDCLASSEX		windowClass_;				// �E�B���h�E�N���X
	HWND			windowHandle_;				// �E�B���h�E�n���h��
	HWND			windowHandleParent_;		// �e�E�B���h�E�n���h��
	int				width_;						// ��
	int				height_;					// ����

private:
	virtual void InitializeSelf( void );
	Window( const Window& );
	Window operator=( const Window& );
};

#endif	// MY_WINDOW_H
