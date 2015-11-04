//==============================================================================
//
// File   : ManagerMotion.cpp
// Brief  : ���[�V�����Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerMotion.h"
#include "Motion.h"
#include "../system/File.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �e���v���[�g�錾
//******************************************************************************
template class ManagerMotion< class Motion >;

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerMotion< TypeItem >::ManagerMotion( void ) : ManagerResource()
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
ManagerMotion< TypeItem >::~ManagerMotion( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : TCHAR* pDirectory					: ��f�B���N�g��
// Arg    : int maximumItem						: �ő�v�f��
//==============================================================================
template< class TypeItem >
int ManagerMotion< TypeItem >::Initialize( TCHAR* pDirectory, int maximumItem )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerResource::Initialize( pDirectory, maximumItem );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerMotion< TypeItem >::Finalize( void )
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
//==============================================================================
template< class TypeItem >
int ManagerMotion< TypeItem >::Reinitialize( TCHAR* pDirectory, int maximumItem )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDirectory, maximumItem );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerMotion* pOut					: �R�s�[��A�h���X
//==============================================================================
template< class TypeItem >
int ManagerMotion< TypeItem >::Copy( ManagerMotion* pOut ) const
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
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
void ManagerMotion< TypeItem >::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}

//==============================================================================
// Brief  : ���\�[�X�̓ǂݍ���
// Return : int									: ���s����
// Arg    : TCHAR* pPath						: �t�@�C���p�X
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
int ManagerMotion< TypeItem >::LoadResource( TCHAR* pPath, int index )
{
	// �t�@�C���̓ǂݍ���
	File	file;		// �t�@�C��
	int		result;		// ���s����
	result = file.Initialize( pPath );
	if( result != 0 )
	{
		return result;
	}

	// �t�@�C���̎�ނ��m�F
	if( !file.IsType( _T( "MOT3" ) ) )
	{
		TCHAR	pStringError[ 256 ];		// �G���[���b�Z�[�W
		sprintf_s( pStringError, 256, _T( "�t�@�C��\"%s\"��������܂���B" ), pPath );
		MessageBox( nullptr, &pStringError[ 0 ], _T( "�G���[" ), MB_OK );
		return 1;
	}

	// ���[�V�������̓ǂݍ���
	unsigned long	countBone;			// �{�[����
	unsigned long	countMotion;		// ���[�V������
	unsigned long	countKeyFrame;		// �L�[�t���[����
	file.Read( &countBone );
	file.Read( &countMotion );
	file.Read( &countKeyFrame );

	// ���[�V�����̐���
	Motion*	pMotion = nullptr;				// ���f��
	pMotion= new Motion();
	if( pMotion == nullptr )
	{
		return 1;
	}
	result = pMotion->Initialize( countKeyFrame, countBone );
	if( result != 0 )
	{
		return result;
	}
	pBufferItem_[ index ].pItem_ = pMotion;

	// �L�[�t���[�����̓ǂݍ���
	D3DXMATRIX	matrixSet;			// �ݒ肷��ϊ��s��
	float		matrix[ 12 ];		// �ϊ��s��ǂݍ��ݗp
	float		countFrame;			// �t���[�����ǂݍ��ݗp
	for( unsigned long counterKeyFrame = 0; counterKeyFrame < countKeyFrame; ++counterKeyFrame )
	{
		file.Read( &countFrame );
		for( unsigned long counterBone = 0; counterBone < countBone; ++counterBone )
		{
			file.Read( &matrix[ 0 ], 12 );
			matrixSet._11 = matrix[ 0 ];
			matrixSet._12 = matrix[ 1 ];
			matrixSet._13 = matrix[ 2 ];
			matrixSet._14 = 0.0f;
			matrixSet._21 = matrix[ 3 ];
			matrixSet._22 = matrix[ 4 ];
			matrixSet._23 = matrix[ 5 ];
			matrixSet._24 = 0.0f;
			matrixSet._31 = matrix[ 6 ];
			matrixSet._32 = matrix[ 7 ];
			matrixSet._33 = matrix[ 8 ];
			matrixSet._34 = 0.0f;
			matrixSet._41 = matrix[ 9 ];
			matrixSet._42 = matrix[ 10 ];
			matrixSet._43 = matrix[ 11 ];
			matrixSet._44 = 1.0f;
			pMotion->SetMatrixBone( counterKeyFrame, counterBone, matrixSet );
		}
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���\�[�X�̊J��
// Return : void								: �Ȃ�
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
void ManagerMotion< TypeItem >::ReleaseResource( int index )
{
	// ���[�V�����̊J��
	delete pBufferItem_[ index ].pItem_;
	pBufferItem_[ index ].pItem_ = nullptr;
}
