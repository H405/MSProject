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
// Arg    : int countSourceVoice				: �\�[�X�{�C�X��
// Arg    : IXAudio2SourceVoice** ppSourceVoice	: �\�[�X�{�C�X
// Arg    : BYTE* pData							: �f�[�^
// Arg    : DWORD size							: �f�[�^�T�C�Y
//==============================================================================
int Sound::Initialize( int countSourceVoice, IXAudio2SourceVoice** ppSourceVoice, BYTE* pData, DWORD size )
{
	// �����o�ϐ��̐ݒ�
	countSourceVoice_ = countSourceVoice;
	ppSourceVoice_ = new IXAudio2SourceVoice*[ countSourceVoice ];
	if( ppSourceVoice_ == nullptr )
	{
		return 1;
	}
	for( int counterSourceVoice = 0; counterSourceVoice < countSourceVoice; ++counterSourceVoice )
	{
		ppSourceVoice_[ counterSourceVoice ] = ppSourceVoice[ counterSourceVoice ];
	}
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
	if( ppSourceVoice_ != nullptr )
	{
		for( int counterSourceVoice = 0; counterSourceVoice < countSourceVoice_; ++counterSourceVoice )
		{
			if( ppSourceVoice_[ counterSourceVoice ] != nullptr )
			{
				// �Đ��̒�~
				ppSourceVoice_[ counterSourceVoice ]->Stop( 0 );

				// �\�[�X�{�C�X�̊J��
				ppSourceVoice_[ counterSourceVoice ]->DestroyVoice();
				ppSourceVoice_[ counterSourceVoice ] = nullptr;
			}
		}
	}
	delete[] ppSourceVoice_;
	ppSourceVoice_ = nullptr;

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
// Arg    : int countSourceVoice				: �\�[�X�{�C�X��
// Arg    : IXAudio2SourceVoice** ppSourceVoice	: �\�[�X�{�C�X
// Arg    : BYTE* pData							: �f�[�^
// Arg    : DWORD size							: �f�[�^�T�C�Y
//==============================================================================
int Sound::Reinitialize( int countSourceVoice, IXAudio2SourceVoice** ppSourceVoice, BYTE* pData, DWORD size )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( countSourceVoice, ppSourceVoice, pData, size );
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
// Return : int									: �\�[�X�{�C�X�ԍ�
// Arg    : int countLoop						: ���[�v��
// Arg    : int indexSourceVoice				: �\�[�X�{�C�X�ԍ�
//==============================================================================
int Sound::Play( int countLoop, int indexSourceVoice )
{
	// �\�[�X�{�C�X�ԍ�������
	int		index;		// �\�[�X�{�C�X�ԍ�
	if( indexSourceVoice < 0 )
	{
		++indexSource_;
		if( indexSource_ >= countSourceVoice_ )
		{
			indexSource_ = 0;
		}
		index = indexSource_;
	}
	else
	{
		index = indexSourceVoice;
	}

	// ���[�v�񐔂̐ݒ�
	audioBuffer_.LoopCount = (countLoop < 0 ? XAUDIO2_LOOP_INFINITE : countLoop);

	// ��Ԏ擾
	XAUDIO2_VOICE_STATE	state;		// ���
	ppSourceVoice_[ index ]->GetState( &state );

	// �I�[�f�B�I�o�b�t�@������Ƃ��ɒ�~������
	if( state.BuffersQueued != 0 )
	{
		ppSourceVoice_[ index ]->Stop( 0 );
		ppSourceVoice_[ index ]->FlushSourceBuffers();
	}

	// �Đ�
	ppSourceVoice_[ index ]->SubmitSourceBuffer( &audioBuffer_ );
	ppSourceVoice_[ index ]->Start( 0 );

	// �\�[�X�{�C�X�ԍ���Ԃ�
	return index;
}

//==============================================================================
// Brief  : �ꎞ��~
// Return : int									: �\�[�X�{�C�X�ԍ�
// Arg    : int indexSourceVoice				: �\�[�X�{�C�X�ԍ�
//==============================================================================
int Sound::Pause( int indexSourceVoice )
{
	// �\�[�X�{�C�X�ԍ�������
	int		index;		// �\�[�X�{�C�X�ԍ�
	index = (indexSourceVoice < 0 ? indexSource_ : indexSourceVoice);

	// ��Ԏ擾
	XAUDIO2_VOICE_STATE	state;		// ���
	ppSourceVoice_[ index ]->GetState( &state );

	// �I�[�f�B�I�o�b�t�@������Ƃ��Ɉꎞ��~������
	if( state.BuffersQueued != 0 )
	{
		ppSourceVoice_[ index ]->Stop( 0 );
	}

	// �\�[�X�{�C�X�ԍ���Ԃ�
	return index;
}

//==============================================================================
// Brief  : �ꎞ��~����
// Return : int									: �\�[�X�{�C�X�ԍ�
// Arg    : int indexSourceVoice				: �\�[�X�{�C�X�ԍ�
//==============================================================================
int Sound::Unpause( int indexSourceVoice )
{
	// �\�[�X�{�C�X�ԍ�������
	int		index;		// �\�[�X�{�C�X�ԍ�
	index = (indexSourceVoice < 0 ? indexSource_ : indexSourceVoice);

	// ��Ԏ擾
	XAUDIO2_VOICE_STATE	state;		// ���
	ppSourceVoice_[ index ]->GetState( &state );

	// �I�[�f�B�I�o�b�t�@������Ƃ��Ɉꎞ��~������������
	if( state.BuffersQueued != 0 )
	{
		ppSourceVoice_[ index ]->Start( 0 );
	}

	// �\�[�X�{�C�X�ԍ���Ԃ�
	return index;
}

//==============================================================================
// Brief  : ��~
// Return : int									: �\�[�X�{�C�X�ԍ�
// Arg    : int indexSourceVoice				: �\�[�X�{�C�X�ԍ�
//==============================================================================
int Sound::Stop( int indexSourceVoice )
{
	// �\�[�X�{�C�X�ԍ�������
	int		index;		// �\�[�X�{�C�X�ԍ�
	index = (indexSourceVoice < 0 ? indexSource_ : indexSourceVoice);

	// ��Ԏ擾
	XAUDIO2_VOICE_STATE	state;		// ���
	ppSourceVoice_[ index ]->GetState( &state );

	// �I�[�f�B�I�o�b�t�@������Ƃ��ɒ�~������
	if( state.BuffersQueued != 0 )
	{
		ppSourceVoice_[ index ]->Stop( 0 );
		ppSourceVoice_[ index ]->FlushSourceBuffers();
	}

	// �\�[�X�{�C�X�ԍ���Ԃ�
	return index;
}

//==============================================================================
// Brief  : ���ʂ̐ݒ�
// Return : int									: �\�[�X�{�C�X�ԍ�
// Arg    : int indexSourceVoice				: �\�[�X�{�C�X�ԍ�
//==============================================================================
int Sound::SetVolume( float value, int indexSourceVoice )
{
	// �\�[�X�{�C�X�ԍ�������
	int		index;		// �\�[�X�{�C�X�ԍ�
	index = (indexSourceVoice < 0 ? indexSource_ : indexSourceVoice);

	// �l�̐ݒ�
	ppSourceVoice_[ index ]->SetVolume( value );

	// �\�[�X�{�C�X�ԍ���Ԃ�
	return index;
}

//==============================================================================
// Brief  : ���ʂ̎擾
// Return : float								: �ԋp����l
// Arg    : int indexSourceVoice				: �\�[�X�{�C�X�ԍ�
//==============================================================================
float Sound::GetVolume( int indexSourceVoice ) const
{
	// �\�[�X�{�C�X�ԍ�������
	int		index;		// �\�[�X�{�C�X�ԍ�
	index = (indexSourceVoice < 0 ? indexSource_ : indexSourceVoice);

	// �l�̕ԋp
	float volume;		// ����
	ppSourceVoice_[ index ]->GetVolume( &volume );
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
	countSourceVoice_ = 0;
	indexSource_ = 0;
	ppSourceVoice_ = nullptr;
	pData_ = nullptr;
	size_ = 0;
	ZeroMemory( &audioBuffer_, sizeof( XAUDIO2_BUFFER ) );
}
