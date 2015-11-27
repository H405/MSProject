//==============================================================================
//
// File   : ManagerPoint.cpp
// Brief  : �|�C���g�X�v���C�g�̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include <process.h>
#include "ManagerPoint.h"
#include "PointMain.h"
#include "../../graphic/graphic/GraphicPoint.h"
#include "../../framework/develop/Debug.h"
#include "../../framework/develop/DebugProc.h"
#include "../../framework/develop/DebugMeasure.h"
#include "../../framework/polygon/PolygonPoint.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerTexture.h"
#include "../../framework/vertex/Vertex.h"
#include "../../framework/vertex/VertexBuffer.h"

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
ManagerPoint::ManagerPoint( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerPoint::~ManagerPoint( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : int countThread						: �X���b�h��
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int ManagerPoint::Initialize( int maximumItem, int countThread, IDirect3DDevice9* pDevice, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, IDirect3DTexture9* pTexture )
{
	// �����o�ϐ��̐ݒ�
	countThread_ = countThread;
	countItemBuffer_ = (maximumItem + countThread - 1) / countThread;
	maximumItem_ = countThread_ * countItemBuffer_;

	// �|�C���g���i�[�o�b�t�@�̊m��
	ppPoint_ = new PointMain*[ countThread ];
	if( ppPoint_ == nullptr )
	{
		return 1;
	}
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		ppPoint_[ counterThread ] = new PointMain[ maximumItem ];
		if( ppPoint_[ counterThread ] == nullptr )
		{
			return 1;
		}
		for( int counterItem = 0; counterItem < maximumItem; ++counterItem )
		{
			ppPoint_[ counterThread ][ counterItem ].Initialize();
		}
	}

	// �|���S���̐���
	int		result;		// ���s����
	pPolygon_ = new PolygonPoint();
	if( pPolygon_ == nullptr )
	{
		return 1;
	}
	result = pPolygon_->Initialize( maximumItem, pDevice );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�̐���
	pGraphic_ = new GraphicPoint();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( INT_MIN, pParameter, pEffectGeneral, pEffectReflect, pPolygon_, pTexture );
	if( result != 0 )
	{
		return result;
	}

	// ���_�o�b�t�@�̍쐬
	pVertexBuffer_ = new VertexBuffer[ countThread ];
	if( pVertexBuffer_ == nullptr )
	{
		return 1;
	}
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		result = pVertexBuffer_[ counterThread ].Initialize( countItemBuffer_, pPolygon_->GetVertex() );
		if( result != 0 )
		{
			return result;
		}
	}

	// �������_�o�b�t�@�̍쐬
	pVertexBufferMerge_ = new VertexBuffer();
	if( pVertexBufferMerge_ == nullptr )
	{
		return 1;
	}
	result = pVertexBufferMerge_->Initialize( maximumItem_, pPolygon_->GetVertex() );
	if( result != 0 )
	{
		return result;
	}

	// �ݒ�|�C���g���i�[�̈�̊m��
	pCountPoint_ = new int[ countThread ];
	if( pCountPoint_ == nullptr )
	{
		return 1;
	}
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		pCountPoint_[ counterThread ] = 0;
	}

	// �N���e�B�J���Z�N�V�����̏�����
	InitializeCriticalSectionEx( &criticalSectionFinish_, 0, 0 );

	// �ǂݍ��݃X���b�h�̐���
	pHandleThread_ = new HANDLE[ countThread ];
	if( pHandleThread_ == nullptr )
	{
		return 1;
	}
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		// �X���b�h�ԍ��̐ݒ�
		EnterCriticalSection( &criticalSectionFinish_ );
		countThreadFinish_ = counterThread;
		LeaveCriticalSection( &criticalSectionFinish_ );

		// �X���b�h�̍쐬
		pHandleThread_[ counterThread ] = reinterpret_cast< HANDLE >( _beginthreadex( nullptr, 0, UpdateBuffer, this, 0, nullptr ) );

		// �X���b�h�쐬�ҋ@
		for( ; ; )
		{
			// �ҋ@
			Sleep( 1 );

			// �쐬���ꂽ���m�F
			int		indexCurrent;		// ���݂̃X���b�h�ԍ�
			EnterCriticalSection( &criticalSectionFinish_ );
			indexCurrent = countThreadFinish_;
			LeaveCriticalSection( &criticalSectionFinish_ );
			if( indexCurrent == -1 )
			{
				break;
			}
		}

		int		indexDebug;		// ���݂̃X���b�h�ԍ�
		EnterCriticalSection( &criticalSectionFinish_ );
		indexDebug = countThreadFinish_;
		LeaveCriticalSection( &criticalSectionFinish_ );
		PrintDebugWnd( _T( "Create %2d\n" ), indexDebug );
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerPoint::Finalize( void )
{
	// �X���b�h�̊J��
	needsDelete_ = true;
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		ResumeThread( pHandleThread_[ counterThread ] );
		WaitForSingleObject( pHandleThread_[ counterThread ], INFINITE );
		CloseHandle( pHandleThread_[ counterThread ] );
		pHandleThread_[ counterThread ] = NULL;
	}
	delete[] pHandleThread_;
	pHandleThread_ = nullptr;

	// �N���e�B�J���Z�N�V�����̊J��
	DeleteCriticalSection( &criticalSectionFinish_ );

	// �ݒ�|�C���g���i�[�̈�̊J��
	delete[] pCountPoint_;
	pCountPoint_ = nullptr;

	// �������_�o�b�t�@�̊J��
	delete pVertexBufferMerge_;
	pVertexBufferMerge_ = nullptr;

	// ���_�o�b�t�@�̊J��
	delete[] pVertexBuffer_;
	pVertexBuffer_ = nullptr;

	// �`��N���X�̊J��
	delete pGraphic_;
	pGraphic_ = nullptr;

	// �|���S���̊J��
	delete pPolygon_;
	pPolygon_ = nullptr;

	// �i�[�̈�̊J��
	if( ppPoint_ != nullptr )
	{
		for( int counterThread = 0; counterThread < countThread_; ++counterThread )
		{
			delete[] ppPoint_[ counterThread ];
			ppPoint_[ counterThread ] = nullptr;
		}
	}
	delete[] ppPoint_;
	ppPoint_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : int countThread						: �X���b�h��
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int ManagerPoint::Reinitialize( int maximumItem, int countThread, IDirect3DDevice9* pDevice, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, IDirect3DTexture9* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( maximumItem, countThread, pDevice, pParameter, pEffectGeneral, pEffectReflect, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerPoint* pOut					: �R�s�[��A�h���X
//==============================================================================
int ManagerPoint::Copy( ManagerPoint* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerPoint::Update( void )
{
	// �I���X���b�h���̃N���A
	EnterCriticalSection( &criticalSectionFinish_ );
	countThreadFinish_ = 0;
	LeaveCriticalSection( &criticalSectionFinish_ );

	// �ݒ�|�C���g���̃N���A
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		pCountPoint_[ counterThread ] = 0;
	}

	// �o�b�t�@�̍X�V
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		ResumeThread( pHandleThread_[ counterThread ] );
	}

	// �X�V�ҋ@
	for( ; ; )
	{
		// �ҋ@
		Sleep( 1 );

		// �X�V���ꂽ���m�F
		int		countThreadUpdated;		// �X�V���ꂽ�X���b�h��
		EnterCriticalSection( &criticalSectionFinish_ );
		countThreadUpdated = countThreadFinish_;
		LeaveCriticalSection( &criticalSectionFinish_ );
		if( countThreadUpdated >= countThread_ )
		{
			break;
		}
	}

	// �o�b�t�@�̓���
	int		countPoint;		// �ݒ�|�C���g��
	countPoint = 0;
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		pVertexBufferMerge_->Merge( countPoint, pVertexBuffer_[ counterThread ], pCountPoint_[ counterThread ] );
		countPoint += pCountPoint_[ counterThread ];
//		PrintDebug( _T( "Thread Point %2d\n" ), pCountPoint_[ counterThread ] );
	}

	// �|���S���֏���]��
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
	}
	pPolygon_->SetVertexBuffer( countPoint, pVertexBufferMerge_->GetBuffer() );
}

//==============================================================================
// Brief  : �|�C���g�̒ǉ�
// Return : void								: �Ȃ�
// Arg    : int indexState						: �X�e�[�g�ԍ�
// Arg    : const D3DXVECTOR3& position			: ���W
// Arg    : const D3DXCOLOR& color				: �F
// Arg    : float size							: �傫��
//==============================================================================
void ManagerPoint::Add( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size )
{
	// �󂫔ԍ��̎擾
	int		indexBuffer;		// �󂫃o�b�t�@�ԍ�
	int		indexItem;			// �󂫗v�f�ԍ�
	GetVacantIndex( &indexBuffer, &indexItem );
	if( indexBuffer < 0 || indexItem < 0 )
	{
		PrintDebugWnd( _T( "�|�C���g�ɋ󂫂�����܂���B\n" ) );
		return;
	}

	// �|�C���g�̐ݒ�
	ppPoint_[ indexBuffer ][ indexItem ].Set( indexState, position, color, size );
}

//==============================================================================
// Brief  : �|�C���g�̒ǉ�
// Return : void								: �Ȃ�
// Arg    : int timeExist						: �c������
// Arg    : const D3DXVECTOR3& position			: ���W
// Arg    : const D3DXCOLOR& color				: �F
// Arg    : float size							: �傫��
// Arg    : const D3DXVECTOR3& differencePosition	: ���W�̕ω���
// Arg    : const D3DXCOLOR& differenceColor	: �F�̕ω���
// Arg    : float differenceSize				: �傫���̕ω���
// Arg    : int indexState						: �X�e�[�g�ԍ�
//==============================================================================
void ManagerPoint::Add( int timeExist, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size,
	const D3DXVECTOR3& differencePosition, const D3DXCOLOR& differenceColor, float differenceSize, int indexState )
{
	// �󂫔ԍ��̎擾
	int		indexBuffer;		// �󂫃o�b�t�@�ԍ�
	int		indexItem;			// �󂫗v�f�ԍ�
	GetVacantIndex( &indexBuffer, &indexItem );
	if( indexBuffer < 0 || indexItem < 0 )
	{
		PrintDebugWnd( _T( "�|�C���g�ɋ󂫂�����܂���B\n" ) );
		return;
	}

	// �|�C���g�̐ݒ�
	ppPoint_[ indexBuffer ][ indexItem ].Set( timeExist, position, color, size, differencePosition, differenceColor, differenceSize, indexState );
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerPoint::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	maximumItem_ = 0;
	countThread_ = 0;
	countItemBuffer_ = 0;
	indexBuffer_ = 0;
	indexItem_ = 0;
	ppPoint_ = nullptr;
	pPolygon_ = nullptr;
	pGraphic_ = nullptr;
	pVertexBuffer_ = nullptr;
	pVertexBufferMerge_ = nullptr;
	pHandleThread_ = nullptr;
	ZeroMemory( &criticalSectionFinish_, sizeof( CRITICAL_SECTION ) );
	countThreadFinish_ = 0;
	pCountPoint_ = nullptr;
	needsDelete_ = false;
}

//==============================================================================
// Brief  : �󂫔ԍ��̎擾
// Return : void								: �Ȃ�
// Arg    : int* pOutIndexThread				: �X���b�h�ԍ��i�[��
// Arg    : int* pOutIndexItem					: �v�f�ԍ��i�[��
//==============================================================================
void ManagerPoint::GetVacantIndex( int* pOutIndexThread, int* pOutIndexItem )
{
	// �󂫔ԍ���T��
	for( int counterItem = 0; counterItem < maximumItem_; ++counterItem )
	{
		++indexBuffer_;
		if( indexBuffer_ >= countThread_ )
		{
			indexBuffer_ = 0;
			++indexItem_;
			if( indexItem_ >= countItemBuffer_ )
			{
				indexItem_ = 0;
			}
		}
		if( !ppPoint_[ indexBuffer_ ][ indexItem_ ].IsEnable() )
		{
			*pOutIndexThread = indexBuffer_;
			*pOutIndexItem = indexItem_;
			return;
		}
	}

	// �󂢂Ă��Ȃ�����
	*pOutIndexThread = -1;
	*pOutIndexItem = -1;
}

//==============================================================================
// Brief  : �o�b�t�@�̍X�V
// Return : unsigned int						: ���s����
// Arg    : LPVOID pParameter					: �p�����[�^
//==============================================================================
unsigned int _stdcall ManagerPoint::UpdateBuffer( LPVOID pParameter )
{
	// �N���X�̃A�h���X���擾
	ManagerPoint*	pManagerPoint = reinterpret_cast< ManagerPoint* >( pParameter );

	// ���g�̔ԍ����L�^
	int		index;		// ���g�̔ԍ�
	EnterCriticalSection( &pManagerPoint->criticalSectionFinish_ );
	index = pManagerPoint->countThreadFinish_;
	pManagerPoint->countThreadFinish_ = -1;
	LeaveCriticalSection( &pManagerPoint->criticalSectionFinish_ );
	SuspendThread( pManagerPoint->pHandleThread_[ index ] );
	PrintDebugWnd( _T( "Save Index %2d\n" ), index );

	// �X�V���[�v
	bool	needsUpdate;		// �X�V�t���O
	needsUpdate = !pManagerPoint->needsDelete_;
	while( needsUpdate )
	{
		// ���_�o�b�t�@�̍쐬
		int		countPoint;		// �|�C���g�̐�
		countPoint = 0;
		for( int counterPoint = 0; counterPoint < pManagerPoint->countItemBuffer_; ++counterPoint )
		{
			// �g�p����Ă��Ȃ��Ƃ�����
			if( !pManagerPoint->ppPoint_[ index ][ counterPoint ].IsEnable() )
			{
				continue;
			}

			// �|�C���g�̍X�V
			pManagerPoint->ppPoint_[ index ][ counterPoint ].Update();

			// ���_�o�b�t�@�֓o�^
			D3DXVECTOR3	position;		// ���W
			D3DXCOLOR	color;			// �F
			pManagerPoint->ppPoint_[ index ][ counterPoint ].GetPosition( &position );
			pManagerPoint->ppPoint_[ index ][ counterPoint ].GetColor( &color );
			pManagerPoint->pVertexBuffer_[ index ].SetValueForPoint( countPoint, position, color, pManagerPoint->ppPoint_[ index ][ counterPoint ].GetSize() );

			// �|�C���g�̐������Z
			++countPoint;
		}

		// �ݒ�|�C���g�����i�[
		pManagerPoint->pCountPoint_[ index ] = countPoint;

		// �I���J�E���g�̉��Z
		EnterCriticalSection( &pManagerPoint->criticalSectionFinish_ );
		++pManagerPoint->countThreadFinish_;
		LeaveCriticalSection( &pManagerPoint->criticalSectionFinish_ );

		// �ꎞ��~
		SuspendThread( pManagerPoint->pHandleThread_[ index ] );

		// �I������
		if( pManagerPoint->needsDelete_ )
		{
			needsUpdate = false;
		}
	}

	// �X���b�h�̏I��
	_endthreadex( 0 );
	return 0;
}
