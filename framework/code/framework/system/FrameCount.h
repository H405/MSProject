//==============================================================================
//
// File   : FrameCount.h
// Brief  : �t���[���J�E���g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_FRAME_COUNT_H
#define MY_FRAME_COUNT_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <windows.h>

//******************************************************************************
// ���C�u����
//******************************************************************************
#pragma comment( lib, "winmm.lib" )

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Manager;

//******************************************************************************
// �N���X��`
//******************************************************************************
class FrameCount
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	FrameCount( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~FrameCount( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : HINSTANCE instanceHandle			: �C���X�^���X�n���h��
	// Arg    : int typeShow						: �\���̎��
	// Arg    : Manager* pManager					: �}�l�[�W��
	// Arg    : int intervalUpdateFps				: FPS�X�V�Ԋu
	// Arg    : int destinationFps					: �ڕWFPS
	//==============================================================================
	int Initialize( HINSTANCE instanceHandle, int typeShow, Manager* pManager, int intervalUpdateFps, int destinationFps );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : HINSTANCE instanceHandle			: �C���X�^���X�n���h��
	// Arg    : int cmdShow							: �\���̎��
	// Arg    : Manager* pManager					: �}�l�[�W��
	//==============================================================================
	int Reinitialize( HINSTANCE instanceHandle, int cmdShow, Manager* pManager );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : FrameCount* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( FrameCount* pOut ) const;

	//==============================================================================
	// Brief  : ���s
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Execute( void );

	//==============================================================================
	// Brief  : �I��
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void End( void );

	//==============================================================================
	// Brief  : �ċN��
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Restart( void );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetIntervalUpdateFps( int value );
	int GetIntervalUpdateFps( void ) const;
	void SetDestinationFps( int value );
	int GetDestinationFps( void ) const;

protected:

private:
	// �J�E���g�̎��
	enum
	{
		TYPE_FRAME_COUNT_DRAW = 0,		// �`��D��
		TYPE_FRAME_COUNT_UPDATE,		// �X�V�D��
		TYPE_FRAME_COUNT_MAX			// �ő�l
	};

	void InitializeSelf( void );
	FrameCount( const FrameCount& );
	FrameCount operator=( const FrameCount& );
	static void CountFrameDraw( FrameCount* pThis );
	static void CountFrameUpdate( FrameCount* pThis );

	HINSTANCE		instanceHandle_;		// �C���X�^���X�n���h��
	int				typeShow_;				// �\���̎��
	bool			isLoopingMain_;			// ���C�����[�v�t���O
	bool			isLoopingReset_;		// ���Z�b�g���[�v�t���O
	int				intervalUpdateFps_;		// FPS�̍X�V�Ԋu
	int				destinationFps_;		// �ڕWFPS
	unsigned long	timeLastExecute_;		// �ŏI���s����
	unsigned long	countFrameTotal_;		// ���t���[����
	unsigned long	timeBeginGame_;			// �Q�[���J�n����
	unsigned long	timeLastUpdate_;		// �ŏI�X�V����
	unsigned long	countFrameUpdate_;		// �X�V�t���[����
	unsigned long	countFrameDraw_;		// �`��t���[����
	int				typeCountFrame_;		// �t���[���J�E���g�̎��
	Manager*		pManager_;				// �}�l�[�W���N���X�i�[�p
#ifdef _DEVELOP
	unsigned long	fpsUpdate_;				// �X�VFPS
	unsigned long	fpsDraw_;				// �`��FPS
#endif

	void (*ppFunctionCountFrame_[ TYPE_FRAME_COUNT_MAX ])( FrameCount* );		// �t���[���J�E���g�֐��e�[�u��
};

#endif	// MY_FRAME_COUNT_H
