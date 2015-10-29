//==============================================================================
//
// File   : File.cpp
// Brief  : �t�@�C���ǂݍ��݃N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/29 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "File.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �e���v���[�g�錾
//******************************************************************************
template void File::Read( char* pOut, int count );
template void File::Read( unsigned char* pOut, int count );
template void File::Read( short* pOut, int count );
template void File::Read( unsigned short* pOut, int count );
template void File::Read( int* pOut, int count );
template void File::Read( unsigned int* pOut, int count );
template void File::Read( long* pOut, int count );
template void File::Read( unsigned long* pOut, int count );
template void File::Read( long long* pOut, int count );
template void File::Read( unsigned long long* pOut, int count );
template void File::Read( float* pOut, int count );
template void File::Read( double* pOut, int count );

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
File::File( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
File::~File( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : const TCHAR* pNameFile				: �t�@�C����
//==============================================================================
int File::Initialize( const TCHAR* pNameFile )
{
	// �t�@�C�����J��
	_tfopen_s( &pFile_, pNameFile, "rb" );
	if( pFile_ == nullptr )
	{
		return 1;
	}

	// �w�b�_�̓ǂݎ��
	char	aBufferHeader[ 32 ] = { 0 };
	fread( &aBufferHeader[ 0 ], sizeof( char ), 32, pFile_ );

	// �w�b�_���̊i�[
	memcpy( &pType_[ 0 ], &aBufferHeader[ 0x00 ], sizeof( char ) * 4 );
	pType_[ 4 ] = '\0';
	memcpy( &size_, &aBufferHeader[ 0x04 ], sizeof( unsigned long ) );
	memcpy( &version_, &aBufferHeader[ 0x08 ], sizeof( unsigned long ) );
	memcpy( &form_, &aBufferHeader[ 0x0C ], sizeof( unsigned long ) );
	memcpy( &code_, &aBufferHeader[ 0x10 ], sizeof( unsigned short ) );
	memcpy( &compress_, &aBufferHeader[ 0x12 ], sizeof( unsigned short ) );

	// �o�b�t�@�i�[�̈�̊m��
	pBuffer_ = new char[ size_ ];
	if( pBuffer_ == nullptr )
	{
		this->~File();
		return 1;
	}

	// �t�@�C���̓ǂݍ���
	if( fread( &pBuffer_[ 0 ], sizeof( char ), size_, pFile_ ) != size_ )
	{
		this->~File();
		return 1;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int File::Finalize( void )
{
	// �t�@�C�������
	if( pFile_ != nullptr )
	{
		fclose( pFile_ );
		pFile_ = nullptr;
	}

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : const TCHAR* pNameFile				: �t�@�C����
//==============================================================================
int File::Reinitialize( const TCHAR* pNameFile )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pNameFile );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : File* pOut							: �R�s�[��A�h���X
//==============================================================================
int File::Copy( File* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ��ނ̔���
// Return : bool								: ��ނ��ǂ���
// Arg    : const TCHAR* pType					: �t�@�C���̎��
//==============================================================================
bool File::IsType( const TCHAR* pType )
{
	// ��r
	if( !_tcscmp( &pType_ [ 0 ], pType ) )
	{
		return true;
	}
	return false;
}

//==============================================================================
// Brief  : �ǂݍ���
// Return : void								: �Ȃ�
// Arg    : Type* pOut							: �l�̊i�[��A�h���X
// Arg    : int count							: �ǂݍ��ݗv�f��
//==============================================================================
template< typename Type >
void File::Read( Type* pOut, int count )
{
	// �o�͐�֏�������
	unsigned long	size = sizeof( Type ) * count;
	memcpy( pOut, &pBuffer_[ cursor_ ], size );

	// �J�[�\���̈ړ�
	cursor_ += size;
}

//==============================================================================
// Brief  : �J�[�\���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : unsigned long value					: �ݒ肷��l
//==============================================================================
void File::SetCursor( unsigned long value )
{
	// �l�̐ݒ�
	cursor_ = value;
}

//==============================================================================
// Brief  : �J�[�\���̎擾
// Return : unsigned long						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned long File::GetCursor( void ) const
{
	// �l�̕ԋp
	return cursor_;
}

//==============================================================================
// Brief  : �J�[�\���̉��Z
// Return : void								: �Ȃ�
// Arg    : unsigned long value					: ���Z�l
//==============================================================================
void File::AddCursor( unsigned long value )
{
	// �l�̉��Z
	cursor_ += value;
}

//==============================================================================
// Brief  : ��ނ̎擾
// Return : void								: �Ȃ�
// Arg    : TCHAR* pOut							: �l�̊i�[�A�h���X
// Arg    : int lengthOut						: �l�̊i�[�A�h���X�̃T�C�Y
//==============================================================================
void File::GetType( TCHAR* pOut, int lengthOut ) const
{
	// �l�̕ԋp
	_tcscpy_s( pOut, lengthOut, pType_ );
}

//==============================================================================
// Brief  : �t�@�C���T�C�Y�̎擾
// Return : unsigned long						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned long File::GetSize( void ) const
{
	// �l�̕ԋp
	return size_;
}

//==============================================================================
// Brief  : �o�[�W�����̎擾
// Return : unsigned long						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned long File::GetVersion( void ) const
{
	// �l�̕ԋp
	return version_;
}

//==============================================================================
// Brief  : �ۑ��`���̎擾
// Return : unsigned long						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned long File::GetForm( void ) const
{
	// �l�̕ԋp
	return form_;
}

//==============================================================================
// Brief  : �Í����`���̎擾
// Return : unsigned short						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned short File::GetCode( void ) const
{
	// �l�̕ԋp
	return code_;
}

//==============================================================================
// Brief  : ���k�`���̎擾
// Return : unsigned short						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
unsigned short File::GetCompress( void ) const
{
	// �l�̕ԋp
	return compress_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void File::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pFile_ = nullptr;
	pBuffer_ = nullptr;
	cursor_ = 0;
	for( int counterCharacter = 0; counterCharacter < COUNT_SIZE_TYPE + 1; ++counterCharacter )
	{
		pType_[ counterCharacter ] = _T( '\0' );
	}
	size_ = 0;
	version_ = 0;
	form_ = 0;
	code_ = 0;
	compress_ = 0;
}
