//==============================================================================
//
// File   : CameraObject.h
// Brief  : �J�����I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_CAMERA_OBJECT_H
#define MY_CAMERA_OBJECT_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Camera.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class CameraStateDebug;
class CameraState;

//******************************************************************************
// �N���X��`
//******************************************************************************
class CameraObject : public Camera
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	CameraObject( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~CameraObject( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : float viewField						: ����p
	// Arg    : int widthScreen						: �X�N���[����
	// Arg    : int heightScreen					: �X�N���[������
	// Arg    : float clipNear						: �߂��̃N���b�v��
	// Arg    : float clipFar						: �����̃N���b�v��
	// Arg    : const D3DXVECTOR3& positionCamera	: ���_
	// Arg    : const D3DXVECTOR3& positionLookAt	: �����_
	// Arg    : const D3DXVECTOR3& vectorUp			: ������x�N�g��
	//==============================================================================
	int Initialize( float viewField, int widthScreen, int heightScreen, float clipNear, float clipFar, const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : float viewField						: ����p
	// Arg    : int widthScreen						: �X�N���[����
	// Arg    : int heightScreen					: �X�N���[������
	// Arg    : float clipNear						: �߂��̃N���b�v��
	// Arg    : float clipFar						: �����̃N���b�v��
	// Arg    : const D3DXVECTOR3& positionCamera	: ���_
	// Arg    : const D3DXVECTOR3& positionLookAt	: �����_
	// Arg    : const D3DXVECTOR3& vectorUp			: ������x�N�g��
	//==============================================================================
	int Reinitialize( float viewField, int widthScreen, int heightScreen, float clipNear, float clipFar, const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : CameraObject* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( CameraObject* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : �f�o�b�O�ݒ�
	// Return : void								: �Ȃ�
	// Arg    : bool value							: �ݒ肷��l
	//==============================================================================
	void SetDebug( bool value );

	//==============================================================================
	// Brief  : �J�����x�N�g���̎擾
	// Return : void								: �Ȃ�
	// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
	//==============================================================================
	void GetVector( D3DXVECTOR3* pOut );

	//==============================================================================
	// Brief  : �ړ�
	// Return : void								: �Ȃ�
	// Arg    : const D3DXVECTOR3& vectorMove		: �ړ��x�N�g��
	//==============================================================================
	void Move( const D3DXVECTOR3& vectorMove );

	//==============================================================================
	// Brief  : �r���[��Ԃ�Z�l���擾
	// Return : float								: Z�l
	// Arg    : const D3DXVECTOR3& position			: ���W
	//==============================================================================
	float GetViewZ( const D3DXVECTOR3& position );

	//==============================================================================
	// Brief  : �v���W�F�N�V������Ԃ�Z�l���擾
	// Return : float								: Z�l
	// Arg    : const D3DXVECTOR3& position			: ���W
	//==============================================================================
	float GetProjectionZ( const D3DXVECTOR3& position );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetPosition( const D3DXVECTOR3& value );
	void SetPosition( float x, float y, float z );
	void SetPositionX( float x );
	void SetPositionY( float y );
	void SetPositionZ( float z );
	void AddPosition( const D3DXVECTOR3& value );
	void AddPosition( float x, float y, float z );
	void AddPositionX( float x );
	void AddPositionY( float y );
	void AddPositionZ( float z );
	void SetRotationCameraX( float x );
	void SetRotationCameraY( float y );
	void AddRotationCameraX( float x );
	void AddRotationCameraY( float y );
	void SetRotationLookAtX( float x );
	void SetRotationLookAtY( float y );
	void AddRotationLookAtX( float x );
	void AddRotationLookAtY( float y );
	float GetRotationX( void );
	float GetRotationY( void );
	void SetState( CameraState* pValue );
	CameraState* GetState( void ) const;

protected:
	CameraState*		pState_;				// �X�e�[�g

#ifdef _DEVELOP
	CameraState*		pStateOriginal_;		// ���̃X�e�[�g
	CameraStateDebug*	pStateDebug_;			// �f�o�b�O�X�e�[�g
	bool				isDebugMode_;			// �f�o�b�O���[�h�t���O
#endif

private:
	void InitializeSelf( void );
	CameraObject( const CameraObject& );
	CameraObject operator=( const CameraObject& );

};

#endif	// MY_CAMERA_OBJECT_H
