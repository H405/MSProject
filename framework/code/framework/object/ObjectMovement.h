//==============================================================================
//
// File   : ObjectMovement.h
// Brief  : �ړ��I�u�W�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/10/20 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_MOVEMENT_H
#define MY_OBJECT_MOVEMENT_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "d3dx9.h"
#include "Object.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************

//******************************************************************************
// �N���X��`
//******************************************************************************
class ObjectMovement : public Object
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ObjectMovement( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual ~ObjectMovement( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	//==============================================================================
	virtual int Initialize( int priority );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	//==============================================================================
	virtual int Reinitialize( int priority );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : ObjectMovement* pOut				: �R�s�[��A�h���X
	//==============================================================================
	virtual int Copy( ObjectMovement* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual void Update( void );

	//==============================================================================
	// Brief  : �X�e�[�g�X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void UpdateState( void );

	//==============================================================================
	// Brief  : �X�e�[�g�̐ݒ�
	// Return : void								: �Ȃ�
	// Arg    : int index							: �X�e�[�g�ԍ�
	//==============================================================================
	virtual void SetState( int index );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetVelocityPosition( const D3DXVECTOR3& value );
	void SetVelocityPosition( float x, float y, float z );
	void SetVelocityPositionX( float x );
	void SetVelocityPositionY( float y );
	void SetVelocityPositionZ( float z );
	void GetVelocityPosition( D3DXVECTOR3* pOut ) const;
	float GetVelocityPositionX( void ) const;
	float GetVelocityPositionY( void ) const;
	float GetVelocityPositionZ( void ) const;
	void SetVelocityRotation( const D3DXVECTOR3& value );
	void SetVelocityRotation( float x, float y, float z );
	void SetVelocityRotationX( float x );
	void SetVelocityRotationY( float y );
	void SetVelocityRotationZ( float z );
	void GetVelocityRotation( D3DXVECTOR3* pOut ) const;
	float GetVelocityRotationX( void ) const;
	float GetVelocityRotationY( void ) const;
	float GetVelocityRotationZ( void ) const;
	void SetVelocityScale( const D3DXVECTOR3& value );
	void SetVelocityScale( float x, float y, float z );
	void SetVelocityScaleX( float x );
	void SetVelocityScaleY( float y );
	void SetVelocityScaleZ( float z );
	void GetVelocityScale( D3DXVECTOR3* pOut ) const;
	float GetVelocityScaleX( void ) const;
	float GetVelocityScaleY( void ) const;
	float GetVelocityScaleZ( void ) const;
	void SetAccelPosition( const D3DXVECTOR3& value );
	void SetAccelPosition( float x, float y, float z );
	void SetAccelPositionX( float x );
	void SetAccelPositionY( float y );
	void SetAccelPositionZ( float z );
	void GetAccelPosition( D3DXVECTOR3* pOut ) const;
	float GetAccelPositionX( void ) const;
	float GetAccelPositionY( void ) const;
	float GetAccelPositionZ( void ) const;
	void SetFriction( float value );
	float GetFriction( void ) const;
	void SetTimeState( int value );
	int GetTimeState( void ) const;
	int GetIndexStateCurrent( void ) const;
	void SetIndexStateNext( int value );
	int GetIndexStateNext( void ) const;

protected:

private:
	virtual void InitializeSelf( void );
	ObjectMovement( const ObjectMovement& );
	ObjectMovement operator=( const ObjectMovement& );

	D3DXVECTOR3	velocityPosition_;		// ���W���x
	D3DXVECTOR3	velocityRotation_;		// ��]���x
	D3DXVECTOR3	velocityScale_;			// �g�k���x
	D3DXVECTOR3	accelPosition_;			// ���W�����x
	float		friction_;				// ���C
	int			timeState_;				// �X�e�[�g�o�ߎ���
	int			indexStateCurrent_;		// ���݂̃X�e�[�g�ԍ�
	int			indexStateNext_;		// ���̃X�e�[�g�ԍ�
};

#endif	// MY_OBJECT_MOVEMENT_H
