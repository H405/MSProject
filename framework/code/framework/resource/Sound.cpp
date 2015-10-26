//==============================================================================
//
// File   : Sound.cpp
// Brief  : �T�E���h�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/25 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Sound.h"

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
Sound::Sound( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Sound::~Sound( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : IXAudio2SourceVoice* pSourceVoice	: �\�[�X�{�C�X
// Arg    : BYTE* pData							: �f�[�^
// Arg    : DWORD size							: �f�[�^�T�C�Y
//==============================================================================
int Sound::Initialize( IXAudio2SourceVoice* pSourceVoice, BYTE* pData, DWORD size )
{
	// �����o�ϐ��̐ݒ�
	pSourceVoice_ = pSourceVoice;
	pData_ = pData;
	size_ = size;
	audioBuffer_.pAudioData = pData;
	audioBuffer_.AudioBytes = size;
	audioBuffer_.Flags = XAUDIO2_END_OF_STREAM;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Sound::Finalize( void )
{
	// �\�[�X�{�C�X�̊J��
	if( pSourceVoice_ != nullptr )
	{
		// �Đ��̒�~
		pSourceVoice_->Stop( 0 );

		// �\�[�X�{�C�X�̊J��
		pSourceVoice_->DestroyVoice();
		pSourceVoice_ = nullptr;
	}

	//	�I�[�f�B�I�f�[�^�̊J��
	delete[] pData_;
	pData_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : IXAudio2SourceVoice* pSourceVoice	: �\�[�X�{�C�X
// Arg    : BYTE* pData							: �f�[�^
// Arg    : DWORD size							: �f�[�^�T�C�Y
//==============================================================================
int Sound::Reinitialize( IXAudio2SourceVoice* pSourceVoice, BYTE* pData, DWORD size )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pSourceVoice, pData, size );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : Sound* pOut							: �R�s�[��A�h���X
//==============================================================================
int Sound::Copy( Sound* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �Đ�
// Return : void								: �Ȃ�
// Arg    : int countLoop						: ���[�v��
//==============================================================================
void Sound::Play( int countLoop )
{
	// ���[�v�񐔂̐ݒ�
	audioBuffer_.LoopCount = (countLoop < 0 ? XAUDIO2_LOOP_INFINITE : countLoop);

	// ��Ԏ擾
	XAUDIO2_VOICE_STATE	state;		// ���
	pSourceVoice_->GetState( &state );

	// �I�[�f�B�I�o�b�t�@������Ƃ��ɒ�~������
	if( state.BuffersQueued != 0 )
	{
		pSourceVoice_->Stop( 0 );
		pSourceVoice_->FlushSourceBuffers();
	}

	// �Đ�
	pSourceVoice_->SubmitSourceBuffer( &audioBuffer_ );
	pSourceVoice_->Start( 0 );
}

//==============================================================================
// Brief  : �ꎞ��~
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Sound::Pause( void )
{
	// ��Ԏ擾
	XAUDIO2_VOICE_STATE	state;		// ���
	pSourceVoice_->GetState( &state );

	// �I�[�f�B�I�o�b�t�@������Ƃ��Ɉꎞ��~������
	if( state.BuffersQueued != 0 )
	{
		pSourceVoice_->Stop( 0 );
	}
}

//==============================================================================
// Brief  : �ꎞ��~����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Sound::Unpause( void )
{
	// ��Ԏ擾
	XAUDIO2_VOICE_STATE	state;		// ���
	pSourceVoice_->GetState( &state );

	// �I�[�f�B�I�o�b�t�@������Ƃ��Ɉꎞ��~������������
	if( state.BuffersQueued != 0 )
	{
		pSourceVoice_->Start( 0 );
	}
}

//==============================================================================
// Brief  : ��~
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Sound::Stop( void )
{
	// ��Ԏ擾
	XAUDIO2_VOICE_STATE	state;		// ���
	pSourceVoice_->GetState( &state );

	// �I�[�f�B�I�o�b�t�@������Ƃ��ɒ�~������
	if( state.BuffersQueued != 0 )
	{
		pSourceVoice_->Stop( 0 );
		pSourceVoice_->FlushSourceBuffers();
	}
}

//==============================================================================
// Brief  : ���ʂ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void Sound::SetVolume( float value )
{
	// �l�̐ݒ�
	pSourceVoice_->SetVolume( value );
}

//==============================================================================
// Brief  : ���ʂ̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Sound::GetVolume( void ) const
{
	// �l�̕ԋp
	float volume;		// ����
	pSourceVoice_->GetVolume( &volume );
	return volume;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Sound::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pSourceVoice_ = nullptr;
	pData_ = nullptr;
	size_ = 0;
	ZeroMemory( &audioBuffer_, sizeof( XAUDIO2_BUFFER ) );
}
