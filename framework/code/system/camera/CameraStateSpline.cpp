//==============================================================================
//
// File   : CameraStateSpline.cpp
// Brief  : �f�o�b�O�X�e�[�g
// Author : Taiga Shirakawa
// Date   : 2015/11/07 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <stdio.h>
#include "CameraStateSpline.h"
#include "../../framework/camera/CameraObject.h"
#include "../../framework/develop/Debug.h"
#include "../../framework/develop/DebugProc.h"

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
CameraStateSpline::CameraStateSpline( void ) : CameraState()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
CameraStateSpline::~CameraStateSpline( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int countSection					: �Z�N�V������
// Arg    : int countControlPointCamera			: ���_�R���g���[���|�C���g��
// Arg    : int countControlPointLookAt			: ���_�R���g���[���|�C���g��
//==============================================================================
int CameraStateSpline::Initialize( int countSection, int countControlPointCamera, int countControlPointLookAt )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = CameraState::Initialize();
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	countSection_ = countSection;
	countControlPointCamera_ = countControlPointCamera;
	countControlPointLookAt_ = countControlPointLookAt;

	// �i�[�̈�̊m��
	pFrame_ = new int[ countSection ];
	if( pFrame_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countSection; ++counterItem )
	{
		pFrame_[ counterItem ] = 0;
	}

	pTablePointCamera_ = new Utility::ControlPointSpline[ countControlPointCamera ];
	if( pTablePointCamera_ == nullptr )
	{
		return 1;
	}

	pTablePointLookAt_ = new Utility::ControlPointSpline[ countControlPointLookAt ];
	if( pTablePointLookAt_ == nullptr )
	{
		return 1;
	}

	pIndexPointCameraBegin_ = new int[ countSection ];
	if( pIndexPointCameraBegin_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countSection; ++counterItem )
	{
		pIndexPointCameraBegin_[ counterItem ] = 0;
	}

	pIndexPointCameraEnd_ = new int[ countSection ];
	if( pIndexPointCameraEnd_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countSection; ++counterItem )
	{
		pIndexPointCameraEnd_[ counterItem ] = 0;
	}

	pIndexPointLookAtBegin_ = new int[ countSection ];
	if( pIndexPointLookAtBegin_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countSection; ++counterItem )
	{
		pIndexPointLookAtBegin_[ counterItem ] = 0;
	}

	pIndexPointLookAtEnd_ = new int[ countSection ];
	if( pIndexPointLookAtEnd_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countSection; ++counterItem )
	{
		pIndexPointLookAtEnd_[ counterItem ] = 0;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : const TCHAR* pNameFile				: �t�@�C����
//==============================================================================
int CameraStateSpline::Initialize( const TCHAR* pNameFile )
{
	// �t�@�C�����J��
	FILE*	pFile = nullptr;		// �t�@�C��
	_tfopen_s( &pFile, pNameFile, _T( "rt" ) );
	if( pFile == nullptr )
	{
		TCHAR	pStringError[ 256 ];		// �G���[������
		_stprintf_s( pStringError, 256, _T( "�t�@�C��\"%s\"��������܂���B" ), pNameFile );
		PrintMsgBox( pStringError );
		return 1;
	}

	// �T�C�Y�����߂�
	unsigned int	sizeFile;		// �t�@�C���̃T�C�Y
	fseek( pFile, 0, SEEK_END );
	sizeFile = ftell( pFile );
	fseek( pFile, 0, SEEK_SET );

	// �o�b�t�@�̊m��
	char*	pBufferFile = nullptr;		// �i�[�p
	pBufferFile = new char[ sizeFile ];
	if( pBufferFile == nullptr )
	{
		return -1;
	}
	memset( pBufferFile, 0x00, sizeof( char ) * sizeFile );

	// �t�@�C���̓��e���R�s�[
	fread( pBufferFile, sizeof( char ), sizeFile, pFile );

	// �t�@�C�������
	fclose( pFile );
	pFile = nullptr;

	// ���s�̕␳
	int		countBreak;		// ���s��
	countBreak = 0;
	for( unsigned int counterCharacter = 0; counterCharacter < sizeFile; ++counterCharacter )
	{
		if( pBufferFile[ counterCharacter ] == '\n' )
		{
			++countBreak;
		}
	}
	sizeFile -= countBreak;

	// �f�[�^�̊J�n�ʒu���L�^
	unsigned int	indexBeginLookAt;			// �����_���J�n�ʒu
	unsigned int	indexBeginSection;			// �Z�N�V�������J�n�ʒu
	int				lengthCompareLookAt;		// ��r������
	int				lengthCompareSection;		// ��r������
	lengthCompareLookAt = _tcslen( _T( "[�����_]" ) );
	lengthCompareSection = _tcslen( _T( "[�Z�N�V����]" ) );
	for( unsigned int counterCharacter = 0; counterCharacter < sizeFile - lengthCompareSection; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "[�����_]" ), lengthCompareLookAt ) )
		{
			indexBeginLookAt = counterCharacter;
		}
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "[�Z�N�V����]" ), lengthCompareSection ) )
		{
			indexBeginSection = counterCharacter;
		}
	}

	// �e�v�f�̌������߂�
	int		countPointCamera;		// ���_�̃R���g���[���|�C���g��
	int		countPointLookAt;		// �����_�̃R���g���[���|�C���g��
	int		countSection;			// �Z�N�V������
	int		lengthCompare;			// ��r������
	countPointCamera = 0;
	lengthCompare = _tcslen( _T( "CP" ) );
	for( unsigned int counterCharacter = 0; counterCharacter < indexBeginLookAt - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "CP" ), lengthCompare ) )
		{
			++countPointCamera;
		}
	}
	countPointLookAt = 0;
	for( unsigned int counterCharacter = indexBeginLookAt; counterCharacter < indexBeginSection - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "CP" ), lengthCompare ) )
		{
			++countPointLookAt;
		}
	}
	countSection = 0;
	for( unsigned int counterCharacter = indexBeginSection; counterCharacter < sizeFile - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "SE" ), lengthCompare ) )
		{
			++countSection;
		}
	}

	// ����������
	int		result;		// ���s����
	result = Initialize( countSection, countPointCamera, countPointLookAt );
	if( result != 0 )
	{
		return result;
	}

	// �R���g���[���|�C���g��ID�i�[�̈���m��
	int*	pIdPointCamera = nullptr;		// ���_�R���g���[���|�C���gID
	int*	pIdPointLookAt = nullptr;		// �����_�R���g���[���|�C���gID
	pIdPointCamera = new int[ countPointCamera ];
	if( pIdPointCamera == nullptr )
	{
		return 1;
	}
	pIdPointLookAt = new int[ countPointLookAt ];
	if( pIdPointLookAt == nullptr )
	{
		return 1;
	}

	// ���_���̐ݒ�
	int			indexIdPointCamera;			// ���_�R���g���[���|�C���gID�ԍ�
	TCHAR		pStringNumber[ 64 ];		// ����������
	D3DXVECTOR3	positionPoint;				// �R���g���[���|�C���g�̍��W
	D3DXVECTOR3	vectorPoint;				// �R���g���[���|�C���g�̃x�N�g��
	indexIdPointCamera = 0;
	for( unsigned int counterCharacter = 0; counterCharacter < indexBeginLookAt - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "CP" ), lengthCompare ) )
		{
			// ID�̎擾
			counterCharacter += 2;
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			pIdPointCamera[ indexIdPointCamera ] = _tstoi( pStringNumber );

			// �R���g���[���|�C���g���̎擾
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			positionPoint.x = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			positionPoint.y = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			positionPoint.z = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			vectorPoint.x = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			vectorPoint.y = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			vectorPoint.z = static_cast< float >( _tstof( pStringNumber ) );

			// �R���g���[���|�C���g�̐ݒ�
			SetControlPointCamera( indexIdPointCamera, positionPoint, vectorPoint );

			// ID�ԍ���i�߂�
			++indexIdPointCamera;
		}
	}

	// �����_���̐ݒ�
	int		indexIdPointLookAt;		// ���_�R���g���[���|�C���gID�ԍ�
	indexIdPointLookAt = 0;
	for( unsigned int counterCharacter = indexBeginLookAt; counterCharacter < indexBeginSection - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "CP" ), lengthCompare ) )
		{
			// ID�̎擾
			counterCharacter += 2;
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			pIdPointLookAt[ indexIdPointLookAt ] = _tstoi( pStringNumber );

			// �R���g���[���|�C���g���̎擾
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			positionPoint.x = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			positionPoint.y = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			positionPoint.z = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			vectorPoint.x = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			vectorPoint.y = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			vectorPoint.z = static_cast< float >( _tstof( pStringNumber ) );

			// �R���g���[���|�C���g�̐ݒ�
			SetControlPointLookAt( indexIdPointLookAt, positionPoint, vectorPoint );

			// ID�ԍ���i�߂�
			++indexIdPointLookAt;
		}
	}

	// �Z�N�V�������̐ݒ�
	int		indexSection;			// �Z�N�V�����ԍ�
	int		countFrame;				// �t���[����
	int		idCameraBegin;			// ���_�J�n�R���g���[���|�C���gID
	int		idCameraEnd;			// ���_�I���R���g���[���|�C���gID
	int		idLookAtBegin;			// �����_�J�n�R���g���[���|�C���gID
	int		idLookAtEnd;			// �����_�I���R���g���[���|�C���gID
	int		indexCameraBegin;		// ���_�J�n�R���g���[���|�C���g�ԍ�
	int		indexCameraEnd;			// ���_�I���R���g���[���|�C���g�ԍ�
	int		indexLookAtBegin;		// �����_�J�n�R���g���[���|�C���g�ԍ�
	int		indexLookAtEnd;			// �����_�I���R���g���[���|�C���g�ԍ�
	indexSection = 0;
	for( unsigned int counterCharacter = indexBeginSection; counterCharacter < sizeFile - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "SE" ), lengthCompare ) )
		{
			// �t���[�����̎擾
			counterCharacter += 2;
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, sizeFile - lengthCompare, 64, pStringNumber );
			countFrame = _tstoi( pStringNumber );

			// �R���g���[���|�C���gID�̎擾
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, sizeFile - lengthCompare, 64, pStringNumber );
			idCameraBegin = _tstoi( pStringNumber );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, sizeFile - lengthCompare, 64, pStringNumber );
			idCameraEnd = _tstoi( pStringNumber );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, sizeFile - lengthCompare, 64, pStringNumber );
			idLookAtBegin = _tstoi( pStringNumber );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, sizeFile - lengthCompare, 64, pStringNumber );
			idLookAtEnd = _tstoi( pStringNumber );

			// ID��ԍ��ɕϊ�
			indexCameraBegin = GetIndexFromId( pIdPointCamera, countPointCamera, idCameraBegin );
			indexCameraEnd = GetIndexFromId( pIdPointCamera, countPointCamera, idCameraEnd );
			indexLookAtBegin = GetIndexFromId( pIdPointLookAt, countPointLookAt, idLookAtBegin );
			indexLookAtEnd = GetIndexFromId( pIdPointLookAt, countPointLookAt, idLookAtEnd );

			// �Z�N�V�����̐ݒ�
			SetSection( indexSection, countFrame, indexCameraBegin, indexCameraEnd, indexLookAtBegin, indexLookAtEnd );

			// �Z�N�V�����ԍ���i�߂�
			++indexSection;
		}
	}

	// �R���g���[���|�C���g��ID�i�[�̈���J��
	delete[] pIdPointCamera;
	pIdPointCamera = nullptr;
	delete[] pIdPointLookAt;
	pIdPointLookAt = nullptr;

	// �o�b�t�@�̊J��
	delete[] pBufferFile;
	pBufferFile = nullptr;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int CameraStateSpline::Finalize( void )
{
	// �m�ۂ����̈�̊J��
	delete[] pFrame_;
	pFrame_ = nullptr;
	delete[] pTablePointCamera_;
	pTablePointCamera_ = nullptr;
	delete[] pTablePointLookAt_;
	pTablePointLookAt_ = nullptr;
	delete[] pIndexPointCameraBegin_;
	pIndexPointCameraBegin_ = nullptr;
	delete[] pIndexPointCameraEnd_;
	pIndexPointCameraEnd_ = nullptr;
	delete[] pIndexPointLookAtBegin_;
	pIndexPointLookAtBegin_ = nullptr;
	delete[] pIndexPointLookAtEnd_;
	pIndexPointLookAtEnd_ = nullptr;

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = CameraState::Finalize();
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
// Arg    : int countSection					: �Z�N�V������
// Arg    : int countControlPointCamera			: ���_�R���g���[���|�C���g��
// Arg    : int countControlPointLookAt			: ���_�R���g���[���|�C���g��
//==============================================================================
int CameraStateSpline::Reinitialize( int countSection, int countControlPointCamera, int countControlPointLookAt )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( countSection, countControlPointCamera, countControlPointLookAt );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : CameraStateSpline* pOut				: �R�s�[��A�h���X
//==============================================================================
int CameraStateSpline::Copy( CameraStateSpline* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = CameraState::Copy( pOut );
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
// Arg    : CameraObject* pCamera				: �J�����N���X
//==============================================================================
void CameraStateSpline::Update( CameraObject* pCamera )
{
	// �L���ȂƂ��̂ݏ�������
	if( !isEnable_ )
	{
		return;
	}

	// ���_���W��ݒ�
	int			indexPointCameraBegin;		// �J�n���_�ԍ�
	int			indexPointCameraEnd;		// �I�����_�ԍ�
	D3DXVECTOR3	positionCamera;				// ���_�̍��W
	indexPointCameraBegin = pIndexPointCameraBegin_[ indexSection_ ];
	indexPointCameraEnd = pIndexPointCameraEnd_[ indexSection_ ];
	if( indexPointCameraBegin == -1 )
	{
		Assert( indexSection_ != 0, _T( "�X�v���C���J�����X�e�[�g�̐ݒ肪�s���ł��B" ) );
		indexPointCameraBegin = pIndexPointCameraEnd_[ indexSection_ - 1 ];
	}
	Utility::Spline( pTablePointCamera_[ indexPointCameraBegin ], pTablePointCamera_[ indexPointCameraEnd ],
		static_cast< float >( countFrame_ ) / pFrame_[ indexSection_ ], &positionCamera );
	pCamera->SetPositionCamera( positionCamera );

	// �����_���W��ݒ�
	int			indexPointLookAtBegin;		// �J�n���_�ԍ�
	int			indexPointLookAtEnd;		// �I�����_�ԍ�
	D3DXVECTOR3	positionLookAt;				// �����_�̍��W
	indexPointLookAtBegin = pIndexPointLookAtBegin_[ indexSection_ ];
	indexPointLookAtEnd = pIndexPointLookAtEnd_[ indexSection_ ];
	if( indexPointLookAtBegin == -1 )
	{
		Assert( indexSection_ != 0, _T( "�X�v���C���J�����X�e�[�g�̐ݒ肪�s���ł��B" ) );
		indexPointLookAtBegin = pIndexPointLookAtEnd_[ indexSection_ - 1 ];
	}
	Utility::Spline( pTablePointLookAt_[ indexPointLookAtBegin ], pTablePointLookAt_[ indexPointLookAtEnd ],
		static_cast< float >( countFrame_ ) / pFrame_[ indexSection_ ], &positionLookAt );
	pCamera->SetPositionLookAt( positionLookAt );

	// �o�߃t���[�����̉��Z
	++countFrame_;

	// �t���[���ԍ���i�߂�
	if( countFrame_ >= pFrame_[ indexSection_ ] )
	{
		countFrame_ = 0;
		++indexSection_;
		if( indexSection_ >= countSection_ )
		{
			indexSection_ = 0;
		}
	}
}

//==============================================================================
// Brief  : �Z�N�V�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : int frame							: ��������
// Arg    : int indexCameraBegin				: �J�n���_�R���g���[���|�C���g�ԍ�
// Arg    : int indexCameraEnd					: �I�����_�R���g���[���|�C���g�ԍ�
// Arg    : int indexLookAtBegin				: �J�n�����_�R���g���[���|�C���g�ԍ�
// Arg    : int indexLookAtEnd					: �I�������_�R���g���[���|�C���g�ԍ�
//==============================================================================
void CameraStateSpline::SetSection( int index, int frame, int indexCameraBegin, int indexCameraEnd, int indexLookAtBegin, int indexLookAtEnd )
{
	// �G���[�`�F�b�N
	Assert( index < countSection_, _T( "�����̒l���s���ł��B" ) );

	// �����o�ϐ��̐ݒ�
	pFrame_[ index ] = frame;
	pIndexPointCameraBegin_[ index ] = indexCameraBegin;
	pIndexPointCameraEnd_[ index ] = indexCameraEnd;
	pIndexPointLookAtBegin_[ index ] = indexLookAtBegin;
	pIndexPointLookAtEnd_[ index ] = indexLookAtEnd;
}

//==============================================================================
// Brief  : ���_�R���g���[���|�C���g�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR3& position			: ���W
// Arg    : const D3DXVECTOR3& vector			: �x�N�g��
//==============================================================================
void CameraStateSpline::SetControlPointCamera( int index, const D3DXVECTOR3& position, const D3DXVECTOR3& vector )
{
	// �G���[�`�F�b�N
	Assert( index < countControlPointCamera_, _T( "�����̒l���s���ł��B" ) );

	// �����o�ϐ��̐ݒ�
	pTablePointCamera_[ index ].position_ = position;
	pTablePointCamera_[ index ].vector_ = vector;
}

//==============================================================================
// Brief  : ���_�R���g���[���|�C���g�̎擾
// Return : void								: �Ȃ�
// Arg    : int index							: �擾����ԍ�
// Arg    : D3DXVECTOR3* pOutPosition			: ���W
// Arg    : D3DXVECTOR3* pOutVector				: �x�N�g��
//==============================================================================
void CameraStateSpline::GetControlPointCamera( int index, D3DXVECTOR3* pOutPosition, D3DXVECTOR3* pOutVector ) const
{
	// �l��Ԃ�
	*pOutPosition = pTablePointCamera_[ index ].position_;
	*pOutVector = pTablePointCamera_[ index ].vector_;
}

//==============================================================================
// Brief  : �����_�R���g���[���|�C���g�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const D3DXVECTOR3& position			: ���W
// Arg    : const D3DXVECTOR3& vector			: �x�N�g��
//==============================================================================
void CameraStateSpline::SetControlPointLookAt( int index, const D3DXVECTOR3& position, const D3DXVECTOR3& vector )
{
	// �G���[�`�F�b�N
	Assert( index < countControlPointLookAt_, _T( "�����̒l���s���ł��B" ) );

	// �����o�ϐ��̐ݒ�
	pTablePointLookAt_[ index ].position_ = position;
	pTablePointLookAt_[ index ].vector_ = vector;
}

//==============================================================================
// Brief  : �����_�R���g���[���|�C���g�̎擾
// Return : void								: �Ȃ�
// Arg    : int index							: �擾����ԍ�
// Arg    : D3DXVECTOR3* pOutPosition			: ���W
// Arg    : D3DXVECTOR3* pOutVector				: �x�N�g��
//==============================================================================
void CameraStateSpline::GetControlPointLookAt( int index, D3DXVECTOR3* pOutPosition, D3DXVECTOR3* pOutVector ) const
{
	// �l��Ԃ�
	*pOutPosition = pTablePointLookAt_[ index ].position_;
	*pOutVector = pTablePointLookAt_[ index ].vector_;
}

//==============================================================================
// Brief  : �t���[�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int indexSection					: �Z�N�V�����ԍ�
// Arg    : int countFrame						: �t���[����
//==============================================================================
void CameraStateSpline::SetCountFrame( int indexSection, int countFrame )
{
	// �t���[������ݒ肷��
	pFrame_[ indexSection ] = countFrame;
}

//==============================================================================
// Brief  : ���t���[�����̎擾
// Return : int									: ���t���[����
// Arg    : void								: �J�����N���X
//==============================================================================
int CameraStateSpline::GetCountFrame( void )
{
	// ���t���[���������߂�
	int		countFrame;		// ���t���[����
	countFrame = 0;
	for( int counterSection = 0; counterSection < countSection_; ++counterSection )
	{
		countFrame += pFrame_[ counterSection ];
	}

	// ���t���[������Ԃ�
	return countFrame;
}

//==============================================================================
// Brief  : ���t���[�����̎擾
// Return : int									: ���t���[����
// Arg    : int indexSection					: �Z�N�V�����ԍ�
//==============================================================================
int CameraStateSpline::GetCountFrame( int indexSection )
{
	// �t���[������Ԃ�
	return pFrame_[ indexSection ];
}

//==============================================================================
// Brief  : �J�n���_�ԍ��̎擾
// Return : int									: �J�n���_�ԍ�
// Arg    : int indexSection					: �Z�N�V�����ԍ�
//==============================================================================
int CameraStateSpline::GetIndexCameraBegin( int indexSection )
{
	// �J�n���_�ԍ���Ԃ�
	return pIndexPointCameraBegin_[ indexSection ];
}

//==============================================================================
// Brief  : �I�����_�ԍ��̎擾
// Return : int									: �I�����_�ԍ�
// Arg    : int indexSection					: �Z�N�V�����ԍ�
//==============================================================================
int CameraStateSpline::GetIndexCameraEnd( int indexSection )
{
	// �I�����_�ԍ���Ԃ�
	return pIndexPointCameraEnd_[ indexSection ];
}

//==============================================================================
// Brief  : �J�n�����_�ԍ��̎擾
// Return : int									: �J�n�����_�ԍ�
// Arg    : int indexSection					: �Z�N�V�����ԍ�
//==============================================================================
int CameraStateSpline::GetIndexLookAtBegin( int indexSection )
{
	// �J�n�����_�ԍ���Ԃ�
	return pIndexPointLookAtBegin_[ indexSection ];
}

//==============================================================================
// Brief  : �I�������_�ԍ��̎擾
// Return : int									: �I�������_�ԍ�
// Arg    : int indexSection					: �Z�N�V�����ԍ�
//==============================================================================
int CameraStateSpline::GetIndexLookAtEnd( int indexSection )
{
	// �I�������_�ԍ���Ԃ�
	return pIndexPointLookAtEnd_[ indexSection ];
}

//==============================================================================
// Brief  : ���_���W�̎擾
// Return : void								: �Ȃ�
// Arg    : int indexSection					: �Z�N�V�����ԍ�
// Arg    : int indexFrame						: �t���[���ԍ�
// Arg    : D3DXVECTOR3* pOut					: �o�͐�
//==============================================================================
void CameraStateSpline::GetPositionCamera( int indexSection, int indexFrame, D3DXVECTOR3* pOut )
{
	// ���_���W��ݒ�
	int		indexPointCameraBegin;		// �J�n���_�ԍ�
	int		indexPointCameraEnd;		// �I�����_�ԍ�
	indexPointCameraBegin = pIndexPointCameraBegin_[ indexSection ];
	indexPointCameraEnd = pIndexPointCameraEnd_[ indexSection ];
	if( indexPointCameraBegin == -1 )
	{
		Assert( indexSection != 0, _T( "�X�v���C���J�����X�e�[�g�̐ݒ肪�s���ł��B" ) );
		indexPointCameraBegin = pIndexPointCameraEnd_[ indexSection - 1 ];
	}
	Utility::Spline( pTablePointCamera_[ indexPointCameraBegin ], pTablePointCamera_[ indexPointCameraEnd ],
		static_cast< float >( indexFrame ) / pFrame_[ indexSection ], pOut );
}

//==============================================================================
// Brief  : �����_���W�̎擾
// Return : void								: �Ȃ�
// Arg    : int indexSection					: �Z�N�V�����ԍ�
// Arg    : int indexFrame						: �t���[���ԍ�
// Arg    : D3DXVECTOR3* pOut					: �o�͐�
//==============================================================================
void CameraStateSpline::GetPositionLookAt( int indexSection, int indexFrame, D3DXVECTOR3* pOut )
{
	// ���_���W��ݒ�
	int		indexPointLookAtBegin;		// �J�n���_�ԍ�
	int		indexPointLookAtEnd;		// �I�����_�ԍ�
	indexPointLookAtBegin = pIndexPointLookAtBegin_[ indexSection ];
	indexPointLookAtEnd = pIndexPointLookAtEnd_[ indexSection ];
	if( indexPointLookAtBegin == -1 )
	{
		Assert( indexSection != 0, _T( "�X�v���C���J�����X�e�[�g�̐ݒ肪�s���ł��B" ) );
		indexPointLookAtBegin = pIndexPointLookAtEnd_[ indexSection - 1 ];
	}
	Utility::Spline( pTablePointLookAt_[ indexPointLookAtBegin ], pTablePointLookAt_[ indexPointLookAtEnd ],
		static_cast< float >( indexFrame ) / pFrame_[ indexSection ], pOut );
}

//==============================================================================
// Brief  : �Z�N�V�������̎擾
// Return : int									: �Z�N�V������
// Arg    : void								: �Ȃ�
//==============================================================================
int CameraStateSpline::GetCountSection( void ) const
{
	// �l�̕ԋp
	return countSection_;
}

//==============================================================================
// Brief  : �L���t���O�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : bool value							: �ݒ肷��l
//==============================================================================
void CameraStateSpline::SetIsEnable( bool value )
{
	// �l�̐ݒ�
	isEnable_ = value;
}

//==============================================================================
// Brief  : �L���t���O�̎擾
// Return : bool								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
bool CameraStateSpline::GetIsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �L���t���O�̔���
// Return : bool								: ���茋��
// Arg    : void								: �Ȃ�
//==============================================================================
bool CameraStateSpline::IsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void CameraStateSpline::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	countSection_ = 0;
	countControlPointCamera_ = 0;
	countControlPointLookAt_ = 0;
	indexSection_ = 0;
	countFrame_ = 0;
	pFrame_ = nullptr;
	pTablePointCamera_ = nullptr;
	pTablePointLookAt_ = nullptr;
	pIndexPointCameraBegin_ = nullptr;
	pIndexPointCameraEnd_ = nullptr;
	pIndexPointLookAtBegin_ = nullptr;
	pIndexPointLookAtEnd_ = nullptr;
	isEnable_ = true;
}

//==============================================================================
// Brief  : ����������̎擾
// Return : unsigned int						: �擾��̔ԍ�
// Arg    : const TCHAR* pBuffer				: �o�b�t�@
// Arg    : unsigned int indexBegin				: �J�n�ԍ�
// Arg    : unsigned int indexEnd				: �I���ԍ�
// Arg    : int sizeOut							: �o�͐�T�C�Y
// Arg    : TCHAR* pOut							: �o�͐�
//==============================================================================
unsigned int CameraStateSpline::GetStringNumber( const TCHAR* pBuffer, unsigned int indexBegin, unsigned int indexEnd, int sizeOut, TCHAR* pOut )
{
	// �J�n�ԍ��̌���
	unsigned int	indexCurrent;			// ���݂̔ԍ�
	unsigned int	indexBeginNumber;		// ������J�n�ԍ�
	for( indexCurrent = indexBegin; indexCurrent < indexEnd; ++indexCurrent )
	{
		if( pBuffer[ indexCurrent ] != _T( ' ' ) && pBuffer[ indexCurrent ] != _T( '\t' ) && pBuffer[ indexCurrent ] != _T( ':' )
			&& pBuffer[ indexCurrent ] != _T( '(' ) && pBuffer[ indexCurrent ] != _T( ')' ) && pBuffer[ indexCurrent ] != _T( ',' ) )
		{
			indexBeginNumber = indexCurrent;
			break;
		}
	}

	// �I���ԍ��̌���
	unsigned int	indexEndNumber;		// ������I���ԍ�
	for( ; indexCurrent < indexEnd; ++indexCurrent )
	{
		if( pBuffer[ indexCurrent ] == _T( ' ' ) || pBuffer[ indexCurrent ] == _T( '\t' ) || pBuffer[ indexCurrent ] == _T( ')' ) || pBuffer[ indexCurrent ] == _T( '\n' ) )
		{
			indexEndNumber = indexCurrent;
			break;
		}
	}

	// ������̎��o��
	_tcsncpy_s( pOut, sizeOut, &pBuffer[ indexBeginNumber ], indexEndNumber - indexBeginNumber );
	pOut[ indexEndNumber - indexBeginNumber ] = _T( '\0' );

	// ���݂̔ԍ���Ԃ�
	return indexCurrent;
}

//==============================================================================
// Brief  : ID����R���g���[���ԍ����擾
// Return : int									: �i�[�ꏊ
// Arg    : const int* pBuffer					: ID�i�[�̈�
// Arg    : int countItem						: �i�[�̈�v�f��
// Arg    : int id								: �Ώ�ID
//==============================================================================
int CameraStateSpline::GetIndexFromId( const int* pBuffer, int countItem, int id )
{
	// ��v����ID������
	for( int counterItem = 0; counterItem < countItem; ++counterItem )
	{
		if( pBuffer[ counterItem ] == id )
		{
			return counterItem;
		}
	}

	// ������Ȃ�����
	return -1;
}
