//==============================================================================
//
// File   : ManagerSound.cpp
// Brief  : �T�E���h�Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/25 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerSound.h"
#include "Sound.h"
#include "../develop/Debug.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �e���v���[�g�錾
//******************************************************************************
template class ManagerSound< class Sound >;

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerSound< TypeItem >::ManagerSound( void ) : ManagerResource()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerSound< TypeItem >::~ManagerSound( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : TCHAR* pDirectory					: ��f�B���N�g��
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : IXAudio2* pXAudio					: XAudio2�C���^�[�t�F�[�X
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::Initialize( TCHAR* pDirectory, int maximumItem, IXAudio2* pXAudio )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerResource::Initialize( pDirectory, maximumItem );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pXAudio_ = pXAudio;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerResource::Finalize();
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
// Arg    : TCHAR* pDirectory					: ��f�B���N�g��
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : IXAudio2* pXAudio					: XAudio2�C���^�[�t�F�[�X
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::Reinitialize( TCHAR* pDirectory, int maximumItem, IXAudio2* pXAudio )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDirectory, maximumItem, pXAudio );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerSound* pOut					: �R�s�[��A�h���X
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::Copy( ManagerSound* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerResource::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���\�[�X�̓ǂݍ���
// Return : int									: ���\�[�XID
// Arg    : TCHAR* pNameFile					: �t�@�C����
// Arg    : int maximumStack					: �ő哯���Đ���
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::Load( TCHAR* pNameFile, int maximumStack )
{
	// �G���[�`�F�b�N
	Assert( pNameFile != nullptr, _T( "�t�@�C���p�X���s���ł��B" ) );

	// �t�@�C���p�X�̍쐬
	TCHAR	pPath[ _MAX_PATH ] = {};		// �t�@�C���p�X
	_tcscpy_s( pPath, _MAX_PATH, pDirectory_ );
	_tcscat_s( pPath, _MAX_PATH, pNameFile );

	// ���ɍ���Ă��Ȃ�������
	int		index;		// �v�f�ԍ�
	index = GetId( pPath );
	if( index != -1 )
	{
		return index;
	}

	// �i�[�ꏊ�̌���
	for( index = 0; index < maximumItem_; ++index )
	{
		if( !pBufferItem_[ index ].isEnable_ )
		{
			break;
		}
	}
	if( index >= maximumItem_ )
	{
		PrintDebugWnd( _T( "���\�[�X�̊i�[�̈�ɋ󂫂�����܂���B" ) );
		return -1;
	}

	// ���\�[�X�̓ǂݍ���
	int		result;		// ���s����
	result = LoadResource( pPath, index, maximumStack );
	if( result != 0 )
	{
		return -1;
	}

	// �v�f�ɒl��ݒ�
	pBufferItem_[ index ].id_ = index;
	_tcscpy_s( pBufferItem_[ index ].pPath_, _MAX_PATH, pPath );
	pBufferItem_[ index ].isEnable_ = true;

	// ���\�[�XID��Ԃ�
	return index;
}

//==============================================================================
// Brief  : ���\�[�X�̎擾
// Return : TypeItem*							: ���\�[�X
// Arg    : TCHAR* pNameFile					: �t�@�C����
// Arg    : int maximumStack					: �ő哯���Đ���
//==============================================================================
template< class TypeItem >
TypeItem* ManagerSound< TypeItem >::Get( TCHAR* pNameFile, int maximumStack )
{
	// �G���[�`�F�b�N
	Assert( pNameFile != nullptr, _T( "�t�@�C���p�X���s���ł��B" ) );

	// �t�@�C���p�X�̍쐬
	TCHAR	pPath[ _MAX_PATH ] = {};		// �t�@�C���p�X
	_tcscpy_s( pPath, _MAX_PATH, pDirectory_ );
	_tcscat_s( pPath, _MAX_PATH, pNameFile );

	// ���ɍ���Ă��Ȃ�������
	int		index;		// �v�f�ԍ�
	index = GetId( pPath );
	if( index != -1 )
	{
		return pBufferItem_[ index ].pItem_;
	}

	// ����Ă��Ȃ��Ƃ��ǂݍ���
	index = Load( pNameFile, maximumStack );
	if( index == -1 )
	{
		return nullptr;
	}

	// ���\�[�X�̕ԋp
	return pBufferItem_[ index ].pItem_;
}

//==============================================================================
// Brief  : XAudio2�C���^�[�t�F�[�X�̎擾
// Return : IXAudio2*							: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
IXAudio2* ManagerSound< TypeItem >::GetXAudio( void ) const
{
	// �l�̕ԋp
	return pXAudio_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
void ManagerSound< TypeItem >::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pXAudio_ = nullptr;
}

//==============================================================================
// Brief  : ���\�[�X�̓ǂݍ���
// Return : int									: ���s����
// Arg    : TCHAR* pPath						: �t�@�C���p�X
// Arg    : int index							: �i�[�v�f�ԍ�
// Arg    : int maximumStack					: �ő哯���Đ���
//==============================================================================
template< class TypeItem >
int ManagerSound< TypeItem >::LoadResource( TCHAR* pPath, int index, int maximumStack )
{
	// �T�E���h�f�[�^�t�@�C���̐���
	HANDLE	handleFile;		// �t�@�C���n���h��
	handleFile = CreateFile( pPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	if( handleFile == INVALID_HANDLE_VALUE )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"���J���܂���B" ), pPath );
		PrintMsgBox( pStringError );
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	// �t�@�C���|�C���^��擪�Ɉړ�
	if( SetFilePointer( handleFile, 0, NULL, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"�𑀍�ł��܂���B" ), pPath );
		PrintMsgBox( pStringError );
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	// ��ނ̊m�F
	HRESULT	result;				// ���s����
	DWORD	sizeChunk;			// �`�����N�̃T�C�Y
	DWORD	positionChunk;		// �`�����N�̈ʒu
	DWORD	typeFile;			// �t�@�C���̎��
	result = CheckChunk( handleFile, _T( 'FFIR' ), &sizeChunk, &positionChunk );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"�̎�ނ̊m�F�Ɏ��s���܂����B" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// ��ނ̓ǂݍ���
	result = ReadChunk( handleFile, &typeFile, positionChunk, sizeof( DWORD ) );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"�̎�ނ̓ǂݍ��݂Ɏ��s���܂����B" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// ��ނ̊m�F
	if( typeFile != _T( 'EVAW' ) )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"�̎�ނ��s���ł��B" ), pPath );
		PrintMsgBox( pStringError );
		return 1;
	}

	// �t�H�[�}�b�g�̊m�F
	WAVEFORMATEXTENSIBLE	formatWave;		// �����t�@�C���t�H�[�}�b�g
	ZeroMemory( &formatWave, sizeof( WAVEFORMATEXTENSIBLE ) );
	result = CheckChunk( handleFile, _T( ' tmf' ), &sizeChunk, &positionChunk );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"�̃t�H�[�}�b�g�̊m�F�Ɏ��s���܂����B" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// �t�H�[�}�b�g�̓ǂݍ���
	result = ReadChunk( handleFile, &formatWave, positionChunk, sizeChunk );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"�̃t�H�[�}�b�g�̓ǂݍ��݂Ɏ��s���܂����B" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// �I�[�f�B�I�f�[�^�̊m�F
	DWORD	sizeData;					// �f�[�^�̃T�C�Y
	BYTE*	pBufferData = nullptr;		// �f�[�^�i�[�o�b�t�@
	result = CheckChunk( handleFile, _T( 'atad' ), &sizeData, &positionChunk );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"�̊m�F�Ɏ��s���܂����B" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// �I�[�f�B�I�f�[�^�̊i�[�̈���m��
	pBufferData = new BYTE[ sizeData ];
	if( pBufferData == nullptr )
	{
		return 1;
	}

	// �I�[�f�B�I�f�[�^�̓ǂݍ���
	result = ReadChunk( handleFile, pBufferData, positionChunk, sizeData );
	if( result != S_OK )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B" ), pPath );
		PrintMsgBox( pStringError );
		return result;
	}

	// �\�[�X�{�C�X�̐���
	IXAudio2SourceVoice**	ppSourceVoice = nullptr;		// �\�[�X�{�C�X
	ppSourceVoice = new IXAudio2SourceVoice*[ maximumStack ];
	if( ppSourceVoice == nullptr )
	{
		return 1;
	}
	for( int counterSourceVoice = 0; counterSourceVoice < maximumStack; ++counterSourceVoice )
	{
		// �\�[�X�{�C�X�̐���
		result = pXAudio_->CreateSourceVoice( &ppSourceVoice[ counterSourceVoice ], &(formatWave.Format) );
		if( result != S_OK )
		{
			PrintMsgBox( _T( "�\�[�X�{�C�X�̐����Ɏ��s���܂����B" ) );
			return result;
		}

		// �I�[�f�B�I�o�b�t�@�̓o�^
		XAUDIO2_BUFFER	bufferAudio;		// �����t�@�C���p�o�b�t�@
		ZeroMemory( &bufferAudio, sizeof( XAUDIO2_BUFFER ) );
		bufferAudio.AudioBytes = sizeData;
		bufferAudio.pAudioData = pBufferData;
		bufferAudio.Flags = XAUDIO2_END_OF_STREAM;
		bufferAudio.LoopCount = 0;
		ppSourceVoice[ counterSourceVoice ]->SubmitSourceBuffer( &bufferAudio );
	}

	// �T�E���h�̐���
	pBufferItem_[ index ].pItem_ = new Sound();
	if( pBufferItem_[ index ].pItem_ == nullptr )
	{
		return 1;
	}
	result = pBufferItem_[ index ].pItem_->Initialize( maximumStack, ppSourceVoice, pBufferData, sizeData );
	if( result != 0 )
	{
		return result;
	}

	// �\�[�X�{�C�X�i�[�̈�̊J��
	delete[] ppSourceVoice;
	ppSourceVoice = nullptr;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���\�[�X�̊J��
// Return : void								: �Ȃ�
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
void ManagerSound< TypeItem >::ReleaseResource( int index )
{
	// �T�E���h�̊J��
	delete pBufferItem_[ index ].pItem_;
	pBufferItem_[ index ].pItem_ = nullptr;
}

//==============================================================================
// Brief  : �`�����N�̊m�F
// Return : void								: �Ȃ�
// Arg    : HANDLE handle						: �t�@�C���n���h��
// Arg    : DWORD format						: �t�H�[�}�b�g
// Arg    : DWORD* pSize						: �`�����N�T�C�Y�̊i�[�p
// Arg    : DWORD* pPosition					: �`�����N�ʒu�̊i�[�p
//==============================================================================
template< class TypeItem >
HRESULT ManagerSound< TypeItem >::CheckChunk( HANDLE handle, DWORD format, DWORD* pSize, DWORD* pPosition )
{
	// �t�@�C���|�C���^��擪�Ɉړ�
	if( SetFilePointer( handle, 0, NULL, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
	{
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	// �`�����N�̓ǂݍ���
	HRESULT result;			// ���s����
	DWORD	sizeRiff;		// RIFF�t�H�[�}�b�g�̃T�C�Y
	DWORD	offset;			// �I�t�Z�b�g
	result = S_OK;
	sizeRiff = 0;
	offset = 0;
	while( result == S_OK )
	{
		// ��ނ̓ǂݍ���
		DWORD	typeChunk;		// �`�����N�̎��
		DWORD	byteRead;		// �ǂݍ��񂾃o�C�g��
		if( ReadFile( handle, &typeChunk, sizeof( DWORD ), &byteRead, NULL ) == 0 )
		{
			result = HRESULT_FROM_WIN32( GetLastError() );
		}

		// �f�[�^�T�C�Y�̓ǂݍ���
		DWORD	sizeData;		// �f�[�^�̃T�C�Y
		if( ReadFile( handle, &sizeData, sizeof( DWORD ), &byteRead, NULL ) == 0 )
		{
			result = HRESULT_FROM_WIN32( GetLastError() );
		}

		// �t�@�C���̎�ނ̓ǂݍ���
		DWORD	typeFile;		// �t�@�C���̎��
		switch( typeChunk )
		{
		case 'FFIR':
			//	�t�@�C���^�C�v�̓ǂݍ���
			sizeRiff = sizeData;
			sizeData = 4;
			if( ReadFile( handle, &typeFile, sizeof( DWORD ), &byteRead, NULL ) == 0 )
			{
				result = HRESULT_FROM_WIN32( GetLastError() );
			}
			break;

		default:
			//	�t�@�C���|�C���^���`�����N�f�[�^���ړ�
			if( SetFilePointer( handle, sizeData, NULL, FILE_CURRENT ) == INVALID_SET_FILE_POINTER )
			{
				return HRESULT_FROM_WIN32( GetLastError() );
			}
			break;
		}

		// �T�C�Y�ƃI�t�Z�b�g��Ԃ�
		offset += sizeof( DWORD ) * 2;
		if( typeChunk == format )
		{
			*pSize = sizeData;
			*pPosition = offset;
			return S_OK;
		}

		// 
		offset += sizeData;
		if( sizeRiff <= 0 )
		{
			return S_FALSE;
		}
	}

	// ����I��
	return S_OK;
}

//==============================================================================
// Brief  : �`�����N�̓ǂݍ���
// Return : void								: �Ȃ�
// Arg    : HANDLE handle						: �t�@�C���n���h��
// Arg    : void* pBuffer						: �i�[�o�b�t�@
// Arg    : DWORD offset						: �f�[�^�̃I�t�Z�b�g
// Arg    : DWORD size							: �f�[�^�̃T�C�Y
//==============================================================================
template< class TypeItem >
HRESULT ManagerSound< TypeItem >::ReadChunk( HANDLE handle, void* pBuffer, DWORD offset, DWORD size )
{
	// �t�@�C���|�C���^���w��ʒu�܂ňړ�
	DWORD	byteRead;		// �ǂݍ��񂾃o�C�g��
	if( SetFilePointer( handle, offset, NULL, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
	{
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	// �f�[�^�̓ǂݍ���
	if( ReadFile( handle, pBuffer, size, &byteRead, NULL ) == 0 )
	{
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	// ����I��
	return S_OK;
}
