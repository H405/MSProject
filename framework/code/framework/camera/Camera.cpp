//==============================================================================
//
// File   : Camera.cpp
// Brief  : �J�����N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Camera.h"
#include "../render/RenderMatrix.h"

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
Camera::Camera( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Camera::~Camera( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Camera::Initialize( void )
{
	// �`��p�ϊ��s��̐���
	int		result;		// ���s����
	pRenderMatrix_ = new RenderMatrix();
	if( pRenderMatrix_ == nullptr )
	{
		return 1;
	}
	result = pRenderMatrix_->Initialize();
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
int Camera::Finalize( void )
{
	// �`��p�ϊ��s��̔j��
	delete pRenderMatrix_;
	pRenderMatrix_ = nullptr;

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
int Camera::Reinitialize( void )
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
// Arg    : Camera* pOut						: �R�s�[��A�h���X
//==============================================================================
int Camera::Copy( Camera* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Camera::Update( void )
{
	// �r���[�}�g���N�X�̍X�V
	if( pRenderMatrix_ != nullptr )
	{
		D3DXMATRIX	matrixView;		// �r���[�}�g���N�X
		D3DXMatrixLookAtLH( &matrixView, &positionCamera_, &positionLookAt_, &vectorUp_ );
		pRenderMatrix_->SetMatrixView( matrixView );
	}
}

//==============================================================================
// Brief  : �l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float viewField						: ����p
// Arg    : int widthScreen						: �X�N���[����
// Arg    : int heightScreen					: �X�N���[������
// Arg    : float clipNear						: �߂��̃N���b�v��
// Arg    : float clipFar						: �����̃N���b�v��
// Arg    : const D3DXVECTOR3& positionCamera	: ���_
// Arg    : const D3DXVECTOR3& positionLookAt	: �����_
// Arg    : const D3DXVECTOR3& vectorUp			: ������x�N�g��
//==============================================================================
void Camera::Set( float viewField, int widthScreen, int heightScreen, float clipNear, float clipFar,
	const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp, bool isPerspective )
{
	// �����o�ϐ��̐ݒ�
	viewField_ = viewField;
	widthScreen_ = static_cast< float >( widthScreen );
	heightScreen_ = static_cast< float >( heightScreen );
	clipNear_ = clipNear;
	clipFar_ = clipFar;
	positionCamera_ = positionCamera;
	positionLookAt_ = positionLookAt;
	vectorUp_ = vectorUp;

	// �v���W�F�N�V�����}�g���N�X�̐���
	D3DXMATRIX	matrixProjection;		// �v���W�F�N�V�����}�g���N�X
	if( isPerspective )
	{
		D3DXMatrixPerspectiveFovLH( &matrixProjection, viewField, widthScreen_ / heightScreen_, clipNear_, clipFar_ );
	}
	else
	{
		D3DXMatrixOrthoLH( &matrixProjection, widthScreen_, heightScreen_, clipNear_, clipFar_ );
	}
	pRenderMatrix_->SetMatrixProjection( matrixProjection );
}

//==============================================================================
// Brief  : ����p�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void Camera::SetViewField( float value )
{
	// �l�̐ݒ�
	viewField_ = value;
}

//==============================================================================
// Brief  : ����p�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetViewField( void ) const
{
	// �l�̕ԋp
	return viewField_;
}

//==============================================================================
// Brief  : �X�N���[�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void Camera::SetWidthScreen( float value )
{
	// �l�̐ݒ�
	widthScreen_ = value;
}

//==============================================================================
// Brief  : �X�N���[�����̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetWidthScreen( void ) const
{
	// �l�̕ԋp
	return widthScreen_;
}

//==============================================================================
// Brief  : �X�N���[�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void Camera::SetHeightScreen( float value )
{
	// �l�̐ݒ�
	heightScreen_ = value;
}

//==============================================================================
// Brief  : �X�N���[�����̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetHeightScreen( void ) const
{
	// �l�̕ԋp
	return heightScreen_;
}

//==============================================================================
// Brief  : �߂��̃N���b�v�ʂ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void Camera::SetClipNear( float value )
{
	// �l�̐ݒ�
	clipNear_ = value;
}

//==============================================================================
// Brief  : �߂��̃N���b�v�ʂ̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetClipNear( void ) const
{
	// �l�̕ԋp
	return clipNear_;
}

//==============================================================================
// Brief  : �����̃N���b�v�ʂ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void Camera::SetClipFar( float value )
{
	// �l�̐ݒ�
	clipFar_ = value;
}

//==============================================================================
// Brief  : �����̃N���b�v�ʂ̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetClipFar( void ) const
{
	// �l�̕ԋp
	return clipFar_;
}

//==============================================================================
// Brief  : ���_���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void Camera::SetPositionCamera( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	positionCamera_ = value;
}

//==============================================================================
// Brief  : ���_���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Camera::SetPositionCamera( float x, float y, float z )
{
	// �l�̐ݒ�
	positionCamera_.x = x;
	positionCamera_.y = y;
	positionCamera_.z = z;
}

//==============================================================================
// Brief  : ���_���W��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Camera::SetPositionCameraX( float x )
{
	// �l�̐ݒ�
	positionCamera_.x = x;
}

//==============================================================================
// Brief  : ���_���W��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Camera::SetPositionCameraY( float y )
{
	// �l�̐ݒ�
	positionCamera_.y = y;
}

//==============================================================================
// Brief  : ���_���W��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Camera::SetPositionCameraZ( float z )
{
	// �l�̐ݒ�
	positionCamera_.z = z;
}

//==============================================================================
// Brief  : ���_���W�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Camera::GetPositionCamera( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = positionCamera_;
}

//==============================================================================
// Brief  : ���_���W��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetPositionCameraX( void ) const
{
	// �l�̕ԋp
	return positionCamera_.x;
}

//==============================================================================
// Brief  : ���_���W��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetPositionCameraY( void ) const
{
	// �l�̕ԋp
	return positionCamera_.y;
}

//==============================================================================
// Brief  : ���_���W��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetPositionCameraZ( void ) const
{
	// �l�̕ԋp
	return positionCamera_.z;
}
//==============================================================================
// Brief  : ���_���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: ���Z����l
//==============================================================================
void Camera::AddPositionCamera( const D3DXVECTOR3& value )
{
	// �l�̉��Z
	positionCamera_ += value;
}

//==============================================================================
// Brief  : ���_���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Camera::AddPositionCamera( float x, float y, float z )
{
	// �l�̉��Z
	positionCamera_.x += x;
	positionCamera_.y += y;
	positionCamera_.z += z;
}

//==============================================================================
// Brief  : ���_���W��X�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Camera::AddPositionCameraX( float x )
{
	// �l�̉��Z
	positionCamera_.x += x;
}

//==============================================================================
// Brief  : ���_���W��Y�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Camera::AddPositionCameraY( float y )
{
	// �l�̉��Z
	positionCamera_.y += y;
}

//==============================================================================
// Brief  : ���_���W��Z�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Camera::AddPositionCameraZ( float z )
{
	// �l�̉��Z
	positionCamera_.z += z;
}

//==============================================================================
// Brief  : �����_���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void Camera::SetPositionLookAt( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	positionLookAt_ = value;
}

//==============================================================================
// Brief  : �����_���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Camera::SetPositionLookAt( float x, float y, float z )
{
	// �l�̐ݒ�
	positionLookAt_.x = x;
	positionLookAt_.y = y;
	positionLookAt_.z = z;
}

//==============================================================================
// Brief  : �����_���W��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Camera::SetPositionLookAtX( float x )
{
	// �l�̐ݒ�
	positionLookAt_.x = x;
}

//==============================================================================
// Brief  : �����_���W��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Camera::SetPositionLookAtY( float y )
{
	// �l�̐ݒ�
	positionLookAt_.y = y;
}

//==============================================================================
// Brief  : �����_���W��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Camera::SetPositionLookAtZ( float z )
{
	// �l�̐ݒ�
	positionLookAt_.z = z;
}

//==============================================================================
// Brief  : �����_���W�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Camera::GetPositionLookAt( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = positionLookAt_;
}

//==============================================================================
// Brief  : �����_���W��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetPositionLookAtX( void ) const
{
	// �l�̕ԋp
	return positionLookAt_.x;
}

//==============================================================================
// Brief  : �����_���W��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetPositionLookAtY( void ) const
{
	// �l�̕ԋp
	return positionLookAt_.y;
}

//==============================================================================
// Brief  : �����_���W��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetPositionLookAtZ( void ) const
{
	// �l�̕ԋp
	return positionLookAt_.z;
}

//==============================================================================
// Brief  : �����_���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: ���Z����l
//==============================================================================
void Camera::AddPositionLookAt( const D3DXVECTOR3& value )
{
	// �l�̉��Z
	positionLookAt_ += value;
}

//==============================================================================
// Brief  : �����_���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Camera::AddPositionLookAt( float x, float y, float z )
{
	// �l�̉��Z
	positionLookAt_.x += x;
	positionLookAt_.y += y;
	positionLookAt_.z += z;
}

//==============================================================================
// Brief  : �����_���W��X�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Camera::AddPositionLookAtX( float x )
{
	// �l�̉��Z
	positionLookAt_.x += x;
}

//==============================================================================
// Brief  : �����_���W��Y�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Camera::AddPositionLookAtY( float y )
{
	// �l�̉��Z
	positionLookAt_.y += y;
}

//==============================================================================
// Brief  : �����_���W��Z�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Camera::AddPositionLookAtZ( float z )
{
	// �l�̉��Z
	positionLookAt_.z += z;
}

//==============================================================================
// Brief  : ������x�N�g���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void Camera::SetVectorUp( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	vectorUp_ = value;
}

//==============================================================================
// Brief  : ������x�N�g���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Camera::SetVectorUp( float x, float y, float z )
{
	// �l�̐ݒ�
	vectorUp_.x = x;
	vectorUp_.y = y;
	vectorUp_.z = z;
}

//==============================================================================
// Brief  : ������x�N�g����X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Camera::SetVectorUpX( float x )
{
	// �l�̐ݒ�
	vectorUp_.x = x;
}

//==============================================================================
// Brief  : ������x�N�g����Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Camera::SetVectorUpY( float y )
{
	// �l�̐ݒ�
	vectorUp_.y = y;
}

//==============================================================================
// Brief  : ������x�N�g����Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Camera::SetVectorUpZ( float z )
{
	// �l�̐ݒ�
	vectorUp_.z = z;
}

//==============================================================================
// Brief  : ������x�N�g���̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Camera::GetVectorUp( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = vectorUp_;
}

//==============================================================================
// Brief  : ������x�N�g����X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetVectorUpX( void ) const
{
	// �l�̕ԋp
	return vectorUp_.x;
}

//==============================================================================
// Brief  : ������x�N�g����Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetVectorUpY( void ) const
{
	// �l�̕ԋp
	return vectorUp_.y;
}

//==============================================================================
// Brief  : ������x�N�g����Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Camera::GetVectorUpZ( void ) const
{
	// �l�̕ԋp
	return vectorUp_.z;
}

//==============================================================================
// Brief  : �`��p�ϊ��s��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : RenderMatrix* pValue				: �ݒ肷��l
//==============================================================================
void Camera::SetRenderMatrix( RenderMatrix* pValue )
{
	// �l�̐ݒ�
	pRenderMatrix_ = pValue;
}

//==============================================================================
// Brief  : �`��p�ϊ��s��̎擾
// Return : RenderMatrix*						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
RenderMatrix* Camera::GetRenderMatrix( void ) const
{
	// �l�̕ԋp
	return pRenderMatrix_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Camera::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	viewField_ = 0.0f;
	widthScreen_ = 0.0f;
	heightScreen_ = 0.0f;
	clipNear_ = 0.0f;
	clipFar_ = 0.0f;
	positionCamera_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	positionLookAt_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	vectorUp_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	pRenderMatrix_ = nullptr;
}
