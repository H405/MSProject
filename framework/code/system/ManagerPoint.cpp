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
#include "ManagerPoint.h"
#include "../graphic/graphic/GraphicPoint.h"
#include "../framework/develop/Debug.h"
#include "../framework/point/Point.h"
#include "../framework/point/PointState.h"
#include "../framework/polygon/PolygonPoint.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/vertex/Vertex.h"
#include "../framework/vertex/VertexBuffer.h"

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
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int ManagerPoint::Initialize( int maximumItem, IDirect3DDevice9* pDevice, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTexture )
{
	// �����o�ϐ��̐ݒ�
	maximumItem_ = maximumItem;
	pPoint_ = new Point[ maximumItem ];
	for( int counterItem = 0; counterItem < maximumItem; ++counterItem )
	{
		pPoint_[ counterItem ].Initialize();
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
	result = pGraphic_->Initialize( INT_MIN, pParameter, pEffectGeneral, pPolygon_, pTexture );
	if( result != 0 )
	{
		return result;
	}

	// ���_�o�b�t�@�̍쐬
	pVertexBuffer_ = new VertexBuffer();
	if( pVertexBuffer_ == nullptr )
	{
		return 1;
	}
	result = pVertexBuffer_->Initialize( maximumItem, pPolygon_->GetVertex() );
	if( result != 0 )
	{
		return result;
	}

	// �X�e�[�g�e�[�u���̍쐬
	ppState_[ STATE_NONE ]		= new PointStateNone();
	ppState_[ STATE_ADD ]		= new PointStateAdd();
	ppState_[ STATE_MULTIPLY ]	= new PointStateMultiply();
	Point::SetState( ppState_ );

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
	// �X�e�[�g�e�[�u���̊J��
	for( int counterState = 0; counterState < STATE_MAX; ++counterState )
	{
		delete ppState_[ counterState ];
		ppState_[ counterState ] = nullptr;
	}

	// ���_�o�b�t�@�̊J��
	delete pVertexBuffer_;
	pVertexBuffer_ = nullptr;

	// �`��N���X�̊J��
	delete pGraphic_;
	pGraphic_ = nullptr;

	// �|���S���̊J��
	delete pPolygon_;
	pPolygon_ = nullptr;

	// �i�[�̈�̊J��
	delete[] pPoint_;
	pPoint_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int ManagerPoint::Reinitialize( int maximumItem, IDirect3DDevice9* pDevice, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( maximumItem, pDevice, pParameter, pEffectGeneral, pTexture );
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
	// ���_�o�b�t�@�̍쐬
	int		countPoint;		// �|�C���g�̐�
	countPoint = 0;
	for( int counterPoint = 0; counterPoint < maximumItem_; ++counterPoint )
	{
		// �g�p����Ă��Ȃ��Ƃ�����
		if( !pPoint_[ counterPoint ].IsEnable() )
		{
			continue;
		}

		// �|�C���g�̍X�V
		pPoint_[ counterPoint ].Update();

		// ���_�o�b�t�@�֓o�^
		D3DXVECTOR3	position;		// ���W
		D3DXCOLOR	color;			// �F
		countPoint, pPoint_[ counterPoint ].GetPosition( &position );
		countPoint, pPoint_[ counterPoint ].GetColor( &color );
		pVertexBuffer_->SetPosition( countPoint, position );
		pVertexBuffer_->SetColorDiffuse( countPoint, color );
		pVertexBuffer_->SetPointSize( countPoint, pPoint_[ counterPoint ].GetSize() );

		// �|�C���g�̐������Z
		++countPoint;
	}

	// �|���S���֏���]��
	pPolygon_->SetVertexBuffer( countPoint, pVertexBuffer_->GetBuffer() );
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
	int		index;		// �󂫔ԍ�
	index = GetIndex();
	if( index < 0 )
	{
		PrintDebugWnd( _T( "�|�C���g�ɋ󂫂�����܂���B\n" ) );
		return;
	}

	// �|�C���g�̐ݒ�
	pPoint_[ index ].Set( indexState, position, color, size );
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
	int		index;		// �󂫔ԍ�
	index = GetIndex();
	if( index < 0 )
	{
		PrintDebugWnd( _T( "�|�C���g�ɋ󂫂�����܂���B\n" ) );
		return;
	}

	// �|�C���g�̐ݒ�
	pPoint_[ index ].Set( timeExist, position, color, size, differencePosition, differenceColor, differenceSize, indexState );
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
	pPoint_ = nullptr;
	pPolygon_ = nullptr;
	pGraphic_ = nullptr;
	pVertexBuffer_ = nullptr;
}

//==============================================================================
// Brief  : �󂫔ԍ��̎擾
// Return : int									: �󂫔ԍ�
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerPoint::GetIndex( void )
{
	// �󂫔ԍ���T��
	for( int counterPoint = 0; counterPoint < maximumItem_; ++counterPoint )
	{
		if( !pPoint_[ counterPoint ].IsEnable() )
		{
			return counterPoint;
		}
	}

	// �󂢂Ă��Ȃ�����
	return -1;
}
