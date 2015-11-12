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
#include "CameraStateSpline.h"
#include "../../framework/camera/CameraObject.h"
#include "../../framework/develop/Debug.h"

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
