//==============================================================================
//
// File   : ObjectMovement.cpp
// Brief  : �ړ��I�u�W�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/10/20 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectMovement.h"

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
ObjectMovement::ObjectMovement( void ) : Object()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectMovement::~ObjectMovement( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int ObjectMovement::Initialize( int priority )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( priority );
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
int ObjectMovement::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Finalize();
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
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int ObjectMovement::Reinitialize( int priority )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ObjectMovement* pOut				: �R�s�[��A�h���X
//==============================================================================
int ObjectMovement::Copy( ObjectMovement* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Copy( pOut );
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
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectMovement::Update( void )
{
	// ���x�̉��Z
	position_ += velocityPosition_;
	rotation_ += velocityRotation_;
	scale_ += velocityScale_;
	velocityPosition_ += accelPosition_;
	velocityPosition_.x *= friction_;
	velocityPosition_.z *= friction_;

	// �������Ԍo��
	++indexStateCurrent_;

	// ��{�N���X�̏���
	Object::Update();
}

//==============================================================================
// Brief  : �X�e�[�g�X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectMovement::UpdateState( void )
{
	// �X�e�[�g�ԍ��̍X�V
	if( indexStateNext_ != -1 )
	{
		indexStateCurrent_ = indexStateNext_;
		indexStateNext_ = -1;
		timeState_ = 0;
	}
}

//==============================================================================
// Brief  : �X�e�[�g�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �X�e�[�g�ԍ�
//==============================================================================
void ObjectMovement::SetState( int index )
{
	// ���̃X�e�[�g��ݒ�
	indexStateNext_ = index;
}

//==============================================================================
// Brief  : ���W���x�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void ObjectMovement::SetVelocityPosition( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	velocityPosition_ = value;
}

//==============================================================================
// Brief  : ���W���x�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void ObjectMovement::SetVelocityPosition( float x, float y, float z )
{
	// �l�̐ݒ�
	velocityPosition_.x = x;
	velocityPosition_.y = y;
	velocityPosition_.z = z;
}

//==============================================================================
// Brief  : ���W���x��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectMovement::SetVelocityPositionX( float x )
{
	// �l�̐ݒ�
	velocityPosition_.x = x;
}

//==============================================================================
// Brief  : ���W���x��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectMovement::SetVelocityPositionY( float y )
{
	// �l�̐ݒ�
	velocityPosition_.y = y;
}

//==============================================================================
// Brief  : ���W���x��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void ObjectMovement::SetVelocityPositionZ( float z )
{
	// �l�̐ݒ�
	velocityPosition_.z = z;
}

//==============================================================================
// Brief  : ���W���x�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void ObjectMovement::GetVelocityPosition( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = velocityPosition_;
}

//==============================================================================
// Brief  : ���W���x��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetVelocityPositionX( void ) const
{
	// �l�̕ԋp
	return velocityPosition_.x;
}

//==============================================================================
// Brief  : ���W���x��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetVelocityPositionY( void ) const
{
	// �l�̕ԋp
	return velocityPosition_.y;
}

//==============================================================================
// Brief  : ���W���x��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetVelocityPositionZ( void ) const
{
	// �l�̕ԋp
	return velocityPosition_.z;
}

//==============================================================================
// Brief  : ��]���x�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void ObjectMovement::SetVelocityRotation( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	velocityRotation_ = value;
}

//==============================================================================
// Brief  : ��]���x�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void ObjectMovement::SetVelocityRotation( float x, float y, float z )
{
	// �l�̐ݒ�
	velocityRotation_.x = x;
	velocityRotation_.y = y;
	velocityRotation_.z = z;
}

//==============================================================================
// Brief  : ��]���x��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectMovement::SetVelocityRotationX( float x )
{
	// �l�̐ݒ�
	velocityRotation_.x = x;
}

//==============================================================================
// Brief  : ��]���x��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectMovement::SetVelocityRotationY( float y )
{
	// �l�̐ݒ�
	velocityRotation_.y = y;
}

//==============================================================================
// Brief  : ��]���x��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void ObjectMovement::SetVelocityRotationZ( float z )
{
	// �l�̐ݒ�
	velocityRotation_.z = z;
}

//==============================================================================
// Brief  : ��]���x�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void ObjectMovement::GetVelocityRotation( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = velocityRotation_;
}

//==============================================================================
// Brief  : ��]���x��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetVelocityRotationX( void ) const
{
	// �l�̕ԋp
	return velocityRotation_.x;
}

//==============================================================================
// Brief  : ��]���x��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetVelocityRotationY( void ) const
{
	// �l�̕ԋp
	return velocityRotation_.y;
}

//==============================================================================
// Brief  : ��]���x��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetVelocityRotationZ( void ) const
{
	// �l�̕ԋp
	return velocityRotation_.z;
}

//==============================================================================
// Brief  : �g�k���x�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void ObjectMovement::SetVelocityScale( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	velocityScale_ = value;
}

//==============================================================================
// Brief  : �g�k���x�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void ObjectMovement::SetVelocityScale( float x, float y, float z )
{
	// �l�̐ݒ�
	velocityScale_.x = x;
	velocityScale_.y = y;
	velocityScale_.z = z;
}

//==============================================================================
// Brief  : �g�k���x��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectMovement::SetVelocityScaleX( float x )
{
	// �l�̐ݒ�
	velocityScale_.x = x;
}

//==============================================================================
// Brief  : �g�k���x��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectMovement::SetVelocityScaleY( float y )
{
	// �l�̐ݒ�
	velocityScale_.y = y;
}

//==============================================================================
// Brief  : �g�k���x��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void ObjectMovement::SetVelocityScaleZ( float z )
{
	// �l�̐ݒ�
	velocityScale_.z = z;
}

//==============================================================================
// Brief  : �g�k���x�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void ObjectMovement::GetVelocityScale( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = velocityScale_;
}

//==============================================================================
// Brief  : �g�k���x��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetVelocityScaleX( void ) const
{
	// �l�̕ԋp
	return velocityScale_.x;
}

//==============================================================================
// Brief  : �g�k���x��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetVelocityScaleY( void ) const
{
	// �l�̕ԋp
	return velocityScale_.y;
}

//==============================================================================
// Brief  : �g�k���x��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetVelocityScaleZ( void ) const
{
	// �l�̕ԋp
	return velocityScale_.z;
}

//==============================================================================
// Brief  : ���W�����x�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void ObjectMovement::SetAccelPosition( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	accelPosition_ = value;
}

//==============================================================================
// Brief  : ���W�����x�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void ObjectMovement::SetAccelPosition( float x, float y, float z )
{
	// �l�̐ݒ�
	accelPosition_.x = x;
	accelPosition_.y = y;
	accelPosition_.z = z;
}

//==============================================================================
// Brief  : ���W�����x��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectMovement::SetAccelPositionX( float x )
{
	// �l�̐ݒ�
	accelPosition_.x = x;
}

//==============================================================================
// Brief  : ���W�����x��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectMovement::SetAccelPositionY( float y )
{
	// �l�̐ݒ�
	accelPosition_.y = y;
}

//==============================================================================
// Brief  : ���W�����x��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void ObjectMovement::SetAccelPositionZ( float z )
{
	// �l�̐ݒ�
	accelPosition_.z = z;
}

//==============================================================================
// Brief  : ���W�����x�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void ObjectMovement::GetAccelPosition( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = accelPosition_;
}

//==============================================================================
// Brief  : ���W�����x��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetAccelPositionX( void ) const
{
	// �l�̕ԋp
	return accelPosition_.x;
}

//==============================================================================
// Brief  : ���W�����x��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetAccelPositionY( void ) const
{
	// �l�̕ԋp
	return accelPosition_.y;
}

//==============================================================================
// Brief  : ���W�����x��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetAccelPositionZ( void ) const
{
	// �l�̕ԋp
	return accelPosition_.z;
}

//==============================================================================
// Brief  : ���C�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void ObjectMovement::SetFriction( float value )
{
	// �l�̐ݒ�
	friction_ = value;
}

//==============================================================================
// Brief  : ���C�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectMovement::GetFriction( void ) const
{
	// �l�̕ԋp
	return friction_;
}

//==============================================================================
// Brief  : �X�e�[�g�o�ߎ��Ԃ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void ObjectMovement::SetTimeState( int value )
{
	// �l�̐ݒ�
	timeState_ = value;
}

//==============================================================================
// Brief  : �X�e�[�g�o�ߎ��Ԃ̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectMovement::GetTimeState( void ) const
{
	// �l�̕ԋp
	return timeState_;
}

//==============================================================================
// Brief  : ���݂̃X�e�[�g�ԍ��̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectMovement::GetIndexStateCurrent( void ) const
{
	// �l�̕ԋp
	return indexStateCurrent_;
}

//==============================================================================
// Brief  : ���̃X�e�[�g�ԍ��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void ObjectMovement::SetIndexStateNext( int value )
{
	// �l�̐ݒ�
	indexStateNext_ = value;
}

//==============================================================================
// Brief  : ���̃X�e�[�g�ԍ��̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectMovement::GetIndexStateNext( void ) const
{
	// �l�̕ԋp
	return indexStateNext_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectMovement::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	velocityPosition_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );;
	velocityRotation_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );;
	velocityScale_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );;
	accelPosition_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );;
	friction_ = 1.0f;
	timeState_ = 0;
	indexStateCurrent_ = 0;
	indexStateNext_ = -1;
}
