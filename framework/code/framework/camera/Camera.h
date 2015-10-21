//==============================================================================
//
// File   : Camera.h
// Brief  : �J�����N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_CAMERA_H
#define MY_CAMERA_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "d3dx9.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class RenderMatrix;

//******************************************************************************
// �N���X��`
//******************************************************************************
class Camera
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	Camera( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual ~Camera( void );

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
	virtual int Initialize( float viewField, int widthScreen, int heightScreen,
		float clipNear, float clipFar, const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual int Finalize( void );

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
	virtual int Reinitialize( float viewField, int widthScreen, int heightScreen,
		float clipNear, float clipFar, const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : Camera* pOut						: �R�s�[��A�h���X
	//==============================================================================
	virtual int Copy( Camera* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetViewField( float value );
	float GetViewField( void ) const;
	void SetWidthScreen( float value );
	float GetWidthScreen( void ) const;
	void SetHeightScreen( float value );
	float GetHeightScreen( void ) const;
	void SetClipNear( float value );
	float GetClipNear( void ) const;
	void SetClipFar( float value );
	float GetClipFar( void ) const;
	void SetPositionCamera( const D3DXVECTOR3& value );
	void SetPositionCamera( float x, float y, float z );
	void SetPositionCameraX( float x );
	void SetPositionCameraY( float y );
	void SetPositionCameraZ( float z );
	void GetPositionCamera( D3DXVECTOR3* pOut ) const;
	float GetPositionCameraX( void ) const;
	float GetPositionCameraY( void ) const;
	float GetPositionCameraZ( void ) const;
	void AddPositionCamera( const D3DXVECTOR3& value );
	void AddPositionCamera( float x, float y, float z );
	void AddPositionCameraX( float x );
	void AddPositionCameraY( float y );
	void AddPositionCameraZ( float z );
	void SetPositionLookAt( const D3DXVECTOR3& value );
	void SetPositionLookAt( float x, float y, float z );
	void SetPositionLookAtX( float x );
	void SetPositionLookAtY( float y );
	void SetPositionLookAtZ( float z );
	void GetPositionLookAt( D3DXVECTOR3* pOut ) const;
	float GetPositionLookAtX( void ) const;
	float GetPositionLookAtY( void ) const;
	float GetPositionLookAtZ( void ) const;
	void AddPositionLookAt( const D3DXVECTOR3& value );
	void AddPositionLookAt( float x, float y, float z );
	void AddPositionLookAtX( float x );
	void AddPositionLookAtY( float y );
	void AddPositionLookAtZ( float z );
	void SetVectorUp( const D3DXVECTOR3& value );
	void SetVectorUp( float x, float y, float z );
	void SetVectorUpX( float x );
	void SetVectorUpY( float y );
	void SetVectorUpZ( float z );
	void GetVectorUp( D3DXVECTOR3* pOut ) const;
	float GetVectorUpX( void ) const;
	float GetVectorUpY( void ) const;
	float GetVectorUpZ( void ) const;
	void SetRenderMatrix( RenderMatrix* pValue );
	RenderMatrix* GetRenderMatrix( void ) const;

protected:
	float			viewField_;				// ����p
	float			widthScreen_;			// �X�N���[����
	float			heightScreen_;			// �X�N���[����
	float			clipNear_;				// �߂��̃N���b�v��
	float			clipFar_;				// �����̃N���b�v��
	D3DXVECTOR3		positionCamera_;		// ���_���W
	D3DXVECTOR3		positionLookAt_;		// �����_���W
	D3DXVECTOR3		vectorUp_;				// ������x�N�g��
	RenderMatrix*	pRenderMatrix_;			// �`��p�ϊ��s��

private:
	virtual void InitializeSelf( void );
	Camera( const Camera& );
	Camera operator=( const Camera& );

};

#endif	// MY_CAMERA_H
