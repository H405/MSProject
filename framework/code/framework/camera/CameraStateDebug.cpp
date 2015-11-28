//==============================================================================
//
// File   : CameraStateDebug.cpp
// Brief  : �f�o�b�O�X�e�[�g
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "CameraStateDebug.h"
#include "CameraObject.h"
#include "../develop/Debug.h"
#include "../develop/DebugProc.h"
#include "../input/InputMouse.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
InputMouse*	CameraStateDebug::pMouse_ = nullptr;		// �}�E�X���̓N���X

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
CameraStateDebug::CameraStateDebug( void ) : CameraState()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
CameraStateDebug::~CameraStateDebug( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int CameraStateDebug::Initialize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = CameraState::Initialize();
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
int CameraStateDebug::Finalize( void )
{
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
// Arg    : void								: �Ȃ�
//==============================================================================
int CameraStateDebug::Reinitialize( void )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize();
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : CameraStateDebug* pOut				: �R�s�[��A�h���X
//==============================================================================
int CameraStateDebug::Copy( CameraStateDebug* pOut ) const
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
void CameraStateDebug::Update( CameraObject* pCamera )
{
	// �h���b�O����
	if( isDraggingLeft_ )
	{
		if( pMouse_->IsRelease( InputMouse::TYPE_LEFT ) )
		{
			isDraggingLeft_ = false;
		}
	}
	else
	{
		if( pMouse_->IsTrigger( InputMouse::TYPE_LEFT ) )
		{
			isDraggingLeft_ = true;
		}
	}
	if( isDraggingRight_ )
	{
		if( pMouse_->IsRelease( InputMouse::TYPE_RIGHT ) )
		{
			isDraggingRight_ = false;
		}
	}
	else
	{
		if( pMouse_->IsTrigger( InputMouse::TYPE_RIGHT ) )
		{
			isDraggingRight_ = true;
		}
	}

#if 0
	// ���x�{��
	if( pMouse_->IsPress( DIK_LSHIFT ) )
	{
		velocity = 5.0f;
	}
#endif

	// �J�����̈ړ�
	LONG		positionMouseX;			// �}�E�XX���W
	LONG		positionMouseY;			// �}�E�XY���W
	int			wheel = 0;				// �z�C�[���ړ���
	D3DXVECTOR3	vectorMove;				// �ړ�����
	float		velocity = 1.0f;		// ���x�{��
	positionMouseX = pMouse_->GetPositionWindowX();
	positionMouseY = pMouse_->GetPositionWindowY();
	if( isDraggingLeft_ )
	{
		vectorMove = D3DXVECTOR3( 1.0f * velocity * ( positionPreviousX_ - positionMouseX ), 1.0f * velocity * ( positionMouseY - positionPreviousY_ ), 0.0f );
		pCamera->Move( vectorMove );
	}
	wheel = pMouse_->GetMoveWheel();
	if( wheel != 0 )
	{
		vectorMove = D3DXVECTOR3( 0.0f, 0.0f, 0.2f * velocity * wheel );
		pCamera->Move( vectorMove );
	}


	// �J�����̊p�x
	if( isDraggingRight_ )
	{
		pCamera->AddRotationCameraX( -0.0075f * (positionPreviousY_ - positionMouseY) );
		pCamera->AddRotationCameraY( 0.0075f * (positionPreviousX_ - positionMouseX) );
	}
#if 0
	// �J�����̃��Z�b�g
	if( pMouse_->IsPress( DIK_O ) )
	{
		pCamera->SetPositionCamera( 0.0f, 30.0f, -100.0f );
		pCamera->SetPositionLookAt( 0.0f, 0.0f, 0.0f );
	}
#endif
	// �}�E�X���W�X�V
	positionPreviousX_ = positionMouseX;
	positionPreviousY_ = positionMouseY;

	// �}�j���A��
	D3DXVECTOR3	vectorCamera;		// �����x�N�g��
	pCamera->GetVector( &vectorCamera );
	D3DXVec3Normalize( &vectorCamera, &vectorCamera );
	PrintDebug( "*--------------------------------------*\n" );
	PrintDebug( "| �f�o�b�O�p�J����                     |\n" );
	PrintDebug( "*--------------------------------------*\n" );
	PrintDebug( "���_�̍��W       �F ( %11.6f, %11.6f, %11.6f )\n", pCamera->GetPositionCameraX(), pCamera->GetPositionCameraY(), pCamera->GetPositionCameraZ() );
	PrintDebug( "�����_�̍��W     �F ( %11.6f, %11.6f, %11.6f )\n", pCamera->GetPositionLookAtX(), pCamera->GetPositionLookAtY(), pCamera->GetPositionLookAtZ() );
	PrintDebug( "�����x�N�g��     �F ( %11.6f, %11.6f, %11.6f )\n", vectorCamera.x, vectorCamera.y, vectorCamera.z );
	PrintDebug( "���h���b�O       �F ��/��/��/�E �ړ�\n" );
	PrintDebug( "�z�C�[��         �F �O/��       �ړ�\n" );
	PrintDebug( "�E�h���b�O       �F ��/��/��/�E ��]\n" );
#if 0
	PrintDebug( "��Shift�L�[      �F �ړ����x�㏸\n" );
	PrintDebug( "O�L�[            �F ���_�֖߂� \n" );
#endif
	PrintDebug( "\n" );
}

#ifdef _DEVELOP
//==============================================================================
// Brief  : �}�E�X���̓N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : InputMouse* pMouse					: �}�E�X���̓N���X
//==============================================================================
void CameraStateDebug::SetInputMouse( InputMouse* pMouse )
{
	// �l�̐ݒ�
	pMouse_ = pMouse;
}
#endif

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void CameraStateDebug::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	positionPreviousX_ = 0;
	positionPreviousY_ = 0;
	isDraggingLeft_ = false;
	isDraggingRight_ = false;
}
