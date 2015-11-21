//==============================================================================
//
// File   : CameraObject.cpp
// Brief  : �J�����I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "CameraObject.h"
#include "CameraState.h"
#include "CameraStateDebug.h"
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
CameraObject::CameraObject( void ) : Camera()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
CameraObject::~CameraObject( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int CameraObject::Initialize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Camera::Initialize();
	if( result != 0 )
	{
		return result;
	}

#ifdef _DEVELOP
	// �f�o�b�O�X�e�[�g�̐���
	pStateDebug_ = new CameraStateDebug();
	if( pStateDebug_ == nullptr )
	{
		return 1;
	}
	result = pStateDebug_->Initialize();
	if( result != 0 )
	{
		return result;
	}
#endif

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int CameraObject::Finalize( void )
{
#ifdef _DEVELOP
	// �f�o�b�O�X�e�[�g�̊J��
	delete pStateDebug_;
	pStateDebug_ = nullptr;
#endif

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Camera::Finalize();
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
int CameraObject::Reinitialize( void )
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
// Arg    : CameraObject* pOut					: �R�s�[��A�h���X
//==============================================================================
int CameraObject::Copy( CameraObject* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Camera::Copy( pOut );
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
void CameraObject::Update( void )
{
	// �X�e�[�g�̎��s
	if( pState_ != nullptr )
	{
		pState_->Update( this );
	}

	// ��{�N���X�̏���
	Camera::Update();
}

//==============================================================================
// Brief  : �f�o�b�O�ݒ�
// Return : void								: �Ȃ�
// Arg    : bool value							: �ݒ肷��l
//==============================================================================
void CameraObject::SetDebug( bool value )
{
#ifdef _DEVELOP
	// ���݂̏�ԂƓ����Ȃ�I��
	if( value == isDebugMode_ )
	{
		return;
	}

	// �f�o�b�O�X�e�[�g�̐؂�ւ�
	if( value )
	{
		pStateOriginal_ = pState_;
		pState_ = pStateDebug_;
	}
	else
	{
		pState_ = pStateOriginal_;
	}

	// ���݂̏�Ԃ�ۑ�
	isDebugMode_ = value;
#endif
}

//==============================================================================
// Brief  : �f�o�b�O�ؑ�
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void CameraObject::ToggleDebug( void )
{
#ifdef _DEVELOP
	// �f�o�b�O�X�e�[�g�̐؂�ւ�
	if( !isDebugMode_ )
	{
		pStateOriginal_ = pState_;
		pState_ = pStateDebug_;
	}
	else
	{
		pState_ = pStateOriginal_;
	}

	// ���݂̏�Ԃ�ۑ�
	isDebugMode_ = !isDebugMode_;
#endif
}

//==============================================================================
// Brief  : �J�����x�N�g���̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void CameraObject::GetVector( D3DXVECTOR3* pOut )
{
	// �l�̕ԋp
	*pOut = positionLookAt_ - positionCamera_;
}

//==============================================================================
// Brief  : �ړ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& vectorMove		: �ړ��x�N�g��
//==============================================================================
void CameraObject::Move( const D3DXVECTOR3& vectorMove )
{
	// ��]���Z�o
	D3DXVECTOR3	vectorCameraToLookAt;		// ���_���璍���_�̃x�N�g��
	D3DXVECTOR3	vectorUp;					// ������x�N�g��
	D3DXVECTOR3	vectorAxisUp;				// �������]��
	D3DXVECTOR3	vectorAxisFront;			// �O������]��
	vectorCameraToLookAt = positionLookAt_ - positionCamera_;
	D3DXVec3Normalize( &vectorCameraToLookAt, &vectorCameraToLookAt );
	vectorUp.x = 0.0f;
	vectorUp.y = 1.0f;
	vectorUp.z = 0.0f;
	D3DXVec3Cross( &vectorAxisUp, &vectorUp, &vectorCameraToLookAt );
	D3DXVec3Normalize( &vectorAxisUp, &vectorAxisUp );
	D3DXVec3Cross( &vectorAxisFront, &vectorCameraToLookAt, &vectorAxisUp );
	D3DXVec3Normalize( &vectorAxisFront, &vectorAxisFront );

	// ���������]�Z�o
	float	rotationCameraUp;		// ���_�̏������]
	rotationCameraUp = -acosf( D3DXVec3Dot( &vectorUp, &vectorAxisFront ) );
	if( vectorCameraToLookAt.y < 0.0f )
	{
		rotationCameraUp *= -1;
	}

	// ������ϊ��N�H�[�^�j�I���̍쐬
	D3DXQUATERNION	quaternionTranformformUp;		// ������̃x�N�g����ϊ�����N�H�[�^�j�I��
	quaternionTranformformUp.x = 0.0f;
	quaternionTranformformUp.y = 0.0f;
	quaternionTranformformUp.z = 0.0f;
	quaternionTranformformUp.w = 1.0f;
	D3DXQuaternionRotationAxis( &quaternionTranformformUp, &vectorAxisUp, rotationCameraUp );

	// �O�����x�N�g���̎Z�o
	D3DXQUATERNION	quaternionConjugate;		// �����N�H�[�^�j�I��
	D3DXQUATERNION	quaternionFront;			// �O�����̃x�N�g���̃N�H�[�^�j�I��
	quaternionConjugate = quaternionTranformformUp;
	quaternionConjugate.x *= -1;
	quaternionConjugate.y *= -1;
	quaternionConjugate.z *= -1;
	quaternionFront.x = 0.0f;
	quaternionFront.y = 0.0f;
	quaternionFront.z = 1.0f;
	quaternionFront.w = 0.0f;
	quaternionFront = quaternionConjugate * quaternionFront * quaternionTranformformUp;

	// �O��������]�Z�o
	D3DXVECTOR3	vectorFront;				// �O�����x�N�g��
	float		rotationCameraFront;		// ���_�̑O������]
	vectorFront.x = quaternionFront.x;
	vectorFront.y = quaternionFront.y;
	vectorFront.z = quaternionFront.z;
	rotationCameraFront = acosf( D3DXVec3Dot( &vectorFront, &vectorCameraToLookAt ) );
	if( vectorFront.z * vectorCameraToLookAt.x - vectorFront.x * vectorCameraToLookAt.z < 0.0f )
	{
		rotationCameraFront *= -1;
	}

	// �O�����ϊ��N�H�[�^�j�I���̍쐬
	D3DXQUATERNION	quaternionTranformformFront;		// �O�����̃x�N�g����ϊ�����N�H�[�^�j�I��
	quaternionTranformformFront.x = 0.0f;
	quaternionTranformformFront.y = 0.0f;
	quaternionTranformformFront.z = 0.0f;
	quaternionTranformformFront.w = 1.0f;
	D3DXQuaternionRotationAxis( &quaternionTranformformFront, &vectorAxisFront, rotationCameraFront );

	// �ړ��ϊ��N�H�[�^�j�I���̍쐬
	D3DXQUATERNION	quaternionTranformformMove;		// �ړ������̃x�N�g����ϊ�����N�H�[�^�j�I��
	quaternionTranformformMove = quaternionTranformformUp * quaternionTranformformFront;
	quaternionConjugate = quaternionTranformformMove;
	quaternionConjugate.x *= -1;
	quaternionConjugate.y *= -1;
	quaternionConjugate.z *= -1;

	// �ړ��x�N�g���̐ݒ�
	D3DXQUATERNION	quaternionMove;				// �ړ������̃x�N�g���̃N�H�[�^�j�I��
	D3DXVECTOR3		vectorMoveTransform;		// �ԊҌ�̈ړ��x�N�g��
	quaternionMove.x = vectorMove.x;
	quaternionMove.y = vectorMove.y;
	quaternionMove.z = vectorMove.z;
	quaternionMove.w = 0.0f;
	quaternionMove = quaternionConjugate * quaternionMove * quaternionTranformformMove;
	vectorMoveTransform.x = quaternionMove.x;
	vectorMoveTransform.y = quaternionMove.y;
	vectorMoveTransform.z = quaternionMove.z;

	// �ړ�
	SetPosition( positionCamera_ + vectorMoveTransform );
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
void CameraObject::Set( float viewField, int widthScreen, int heightScreen, float clipNear, float clipFar,
	const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp )
{
	// �l�̐ݒ�
	Camera::Set( viewField, widthScreen, heightScreen, clipNear, clipFar, positionCamera, positionLookAt, vectorUp );
}

//==============================================================================
// Brief  : �r���[��Ԃ�Z�l���擾
// Return : float								: Z�l
// Arg    : const D3DXVECTOR3& position			: ���W
//==============================================================================
float CameraObject::GetViewZ( const D3DXVECTOR3& position )
{
	// �r���[���W�ɕϊ�
	D3DXVECTOR3	positionView;		// �r���[��Ԃł̍��W
	D3DXMATRIX	matrixView;			// �r���[�ϊ��s��
	pRenderMatrix_->GetMatrixView( &matrixView );
	D3DXVec3TransformCoord( &positionView, &position, &matrixView );

	// �l��Ԃ�
	return positionView.z / clipFar_;
}

//==============================================================================
// Brief  : �v���W�F�N�V������Ԃ�Z�l���擾
// Return : float								: Z�l
// Arg    : const D3DXVECTOR3& position			: ���W
//==============================================================================
float CameraObject::GetProjectionZ( const D3DXVECTOR3& position )
{
	// �r���[���W�ɕϊ�
	D3DXVECTOR4	positionWorld;				// ���[���h��Ԃł̍��W
	D3DXVECTOR4	positionProjection;			// �v���W�F�N�V������Ԃł̍��W
	D3DXMATRIX	matrixViewProjection;		// �r���[�v���W�F�N�V�����ϊ��s��
	pRenderMatrix_->GetMatrixViewProjection( &matrixViewProjection );
	positionWorld.x = position.x;
	positionWorld.y = position.y;
	positionWorld.z = position.z;
	positionWorld.w = 1.0f;
	D3DXVec4Transform( &positionProjection, &positionWorld, &matrixViewProjection );

	// �l��Ԃ�
	return positionProjection.z / positionProjection.w;
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void CameraObject::SetPosition( const D3DXVECTOR3& value )
{
	// ���W�̐ݒ�
	SetPosition( value.x, value.y, value.z );
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: �ݒ肷��l
// Arg    : float y								: �ݒ肷��l
// Arg    : float z								: �ݒ肷��l
//==============================================================================
void CameraObject::SetPosition( float x, float y, float z )
{
	// ���_�̐ݒ�
	D3DXVECTOR3	vectorCameraToLookAt = positionLookAt_ - positionCamera_;		// ���_���璍���_�̃x�N�g��
	positionCamera_.x = x;
	positionCamera_.y = y;
	positionCamera_.z = z;

	// �����_�̐ݒ�
	positionLookAt_ = positionCamera_ + vectorCameraToLookAt;
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: �ݒ肷��l
//==============================================================================
void CameraObject::SetPositionX( float x )
{
	// ���W�̐ݒ�
	SetPosition( x, positionCamera_.y, positionCamera_.z );
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: �ݒ肷��l
//==============================================================================
void CameraObject::SetPositionY( float y )
{
	// ���W�̐ݒ�
	SetPosition( positionCamera_.x, y, positionCamera_.z );
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: �ݒ肷��l
//==============================================================================
void CameraObject::SetPositionZ( float z )
{
	// ���W�̐ݒ�
	SetPosition( positionCamera_.x, positionCamera_.y, z );
}

//==============================================================================
// Brief  : ���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: ���Z����l
//==============================================================================
void CameraObject::AddPosition( const D3DXVECTOR3& value )
{
	// ���W�̉��Z
	SetPosition( positionCamera_.x + value.x, positionCamera_.y + value.y, positionCamera_.z + value.z );
}

//==============================================================================
// Brief  : ���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: ���Z����l
// Arg    : float y								: ���Z����l
// Arg    : float z								: ���Z����l
//==============================================================================
void CameraObject::AddPosition( float x, float y, float z )
{
	// ���W�̉��Z
	SetPosition( positionCamera_.x + x, positionCamera_.y + y, positionCamera_.z + z );
}

//==============================================================================
// Brief  : ���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: ���Z����l
//==============================================================================
void CameraObject::AddPositionX( float x )
{
	// ���W�̉��Z
	SetPosition( positionCamera_.x + x, positionCamera_.y, positionCamera_.z );
}

//==============================================================================
// Brief  : ���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: ���Z����l
//==============================================================================
void CameraObject::AddPositionY( float y )
{
	// ���W�̉��Z
	SetPosition( positionCamera_.x, positionCamera_.y + y, positionCamera_.z );
}

//==============================================================================
// Brief  : ���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : float z								: ���Z����l
//==============================================================================
void CameraObject::AddPositionZ( float z )
{
	// ���W�̉��Z
	SetPosition( positionCamera_.x, positionCamera_.y, positionCamera_.z + z );
}

//==============================================================================
// Brief  : ���_���SX����]�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: �ݒ肷��l
//==============================================================================
void CameraObject::SetRotationCameraX( float x )
{
	// ���_���璍���_�܂ł̋����Z�o
	D3DXVECTOR3	vectorCameraToLookAt;		// ���_���璍���_�̃x�N�g��
	float		distanceCameraToLookAt;		// ���_���璍���_�̋���
	vectorCameraToLookAt = positionLookAt_ - positionCamera_;
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// �����_�̈ړ�
	positionLookAt_.y = positionCamera_.y + sinf( x ) * distanceCameraToLookAt;
	positionLookAt_.z = positionCamera_.z + cosf( x ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : ���_���SY����]�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: �ݒ肷��l
//==============================================================================
void CameraObject::SetRotationCameraY( float y )
{
	// ���_���璍���_�܂ł̋����Z�o
	D3DXVECTOR3	vectorCameraToLookAt;		// ���_���璍���_�̃x�N�g��
	float		distanceCameraToLookAt;		// ���_���璍���_�̋���
	vectorCameraToLookAt = positionLookAt_ - positionCamera_;
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// �����_�̈ړ�
	positionLookAt_.x = positionCamera_.x + sinf( y ) * distanceCameraToLookAt;
	positionLookAt_.z = positionCamera_.z + cosf( y ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : ���_���SX����]�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: ���Z����l
//==============================================================================
void CameraObject::AddRotationCameraX( float x )
{
	// ��]���̐ݒ�
	D3DXVECTOR3	vectorCameraToLookAt;		// ���_���璍���_�̃x�N�g��
	D3DXVECTOR3	vectorAxis;					// ��]��
	vectorCameraToLookAt = positionLookAt_ - positionCamera_;
	vectorAxis.x = 0.0f;
	vectorAxis.y = 1.0f;
	vectorAxis.z = 0.0f;
	D3DXVec3Cross( &vectorAxis, &vectorCameraToLookAt, &vectorAxis );
	D3DXVec3Normalize( &vectorAxis, &vectorAxis );

	// �ϊ��N�H�[�^�j�I���̍쐬
	D3DXQUATERNION	quaternionTranform;		// �����_���W��ϊ�����N�H�[�^�j�I��
	quaternionTranform.w = 1.0f;
	quaternionTranform.x = 0.0f;
	quaternionTranform.y = 0.0f;
	quaternionTranform.z = 0.0f;
	D3DXQuaternionRotationAxis( &quaternionTranform, &vectorAxis, x );
	quaternionTranform.x *= -1;
	quaternionTranform.y *= -1;
	quaternionTranform.z *= -1;

	// ���W�N�H�[�^�j�I���̍쐬
	D3DXQUATERNION	quaternionLookAt;		// �����_���W�̃N�H�[�^�j�I��
	quaternionLookAt.w = 0.0f;
	quaternionLookAt.x = vectorCameraToLookAt.x;
	quaternionLookAt.y = vectorCameraToLookAt.y;
	quaternionLookAt.z = vectorCameraToLookAt.z;

	// ���W�̕ϊ�
	quaternionLookAt = quaternionTranform * quaternionLookAt;
	quaternionTranform.x *= -1;
	quaternionTranform.y *= -1;
	quaternionTranform.z *= -1;
	quaternionLookAt = quaternionLookAt * quaternionTranform;

	// �����_�̐ݒ�
	positionLookAt_.x = positionCamera_.x + quaternionLookAt.x;
	positionLookAt_.y = positionCamera_.y + quaternionLookAt.y;
	positionLookAt_.z = positionCamera_.z + quaternionLookAt.z;
}

//==============================================================================
// Brief  : ���_���SY����]�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: ���Z����l
//==============================================================================
void CameraObject::AddRotationCameraY( float y )
{
	// ��]���̐ݒ�
	D3DXVECTOR3	vectorAxis;		// ��]��
	vectorAxis.x = 0.0f;
	vectorAxis.y = 1.0f;
	vectorAxis.z = 0.0f;
	
	// �ϊ��N�H�[�^�j�I���̍쐬
	D3DXQUATERNION	quaternionTranform;		// �����_���W��ϊ�����N�H�[�^�j�I��
	quaternionTranform.w = 1.0f;
	quaternionTranform.x = 0.0f;
	quaternionTranform.y = 0.0f;
	quaternionTranform.z = 0.0f;
	D3DXQuaternionRotationAxis( &quaternionTranform, &vectorAxis, y );
	quaternionTranform.x *= -1;
	quaternionTranform.y *= -1;
	quaternionTranform.z *= -1;
	
	// ���W�N�H�[�^�j�I���̍쐬
	D3DXVECTOR3		vectorCameraToLookAt;	// ���_���璍���_�̃x�N�g��
	D3DXQUATERNION	quaternionLookAt;		// �����_���W�̃N�H�[�^�j�I��
	vectorCameraToLookAt = positionLookAt_ - positionCamera_;
	quaternionLookAt.w = 0.0f;
	quaternionLookAt.x = vectorCameraToLookAt.x;
	quaternionLookAt.y = vectorCameraToLookAt.y;
	quaternionLookAt.z = vectorCameraToLookAt.z;
	
	// ���W�̕ϊ�
	quaternionLookAt = quaternionTranform * quaternionLookAt;
	quaternionTranform.x *= -1;
	quaternionTranform.y *= -1;
	quaternionTranform.z *= -1;
	quaternionLookAt = quaternionLookAt * quaternionTranform;
	
	// �����_�̐ݒ�
	positionLookAt_.x = positionCamera_.x + quaternionLookAt.x;
	positionLookAt_.y = positionCamera_.y + quaternionLookAt.y;
	positionLookAt_.z = positionCamera_.z + quaternionLookAt.z;
}

//==============================================================================
// Brief  : �����_���SX����]�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: �ݒ肷��l
//==============================================================================
void CameraObject::SetRotationLookAtX( float x )
{
	// ���_���璍���_�܂ł̋����Z�o
	D3DXVECTOR3	vectorCameraToLookAt;		// ���_���璍���_�̃x�N�g��
	float		distanceCameraToLookAt;		// ���_���璍���_�̋���
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// ���_�̈ړ�
	positionCamera_.y = positionLookAt_.y + sinf( x + D3DX_PI ) * distanceCameraToLookAt;
	positionCamera_.z = positionLookAt_.z + cosf( x + D3DX_PI ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : �����_���SY����]�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: �ݒ肷��l
//==============================================================================
void CameraObject::SetRotationLookAtY( float y )
{
	// ���_���璍���_�܂ł̋����Z�o
	D3DXVECTOR3	vectorCameraToLookAt;		// ���_���璍���_�̃x�N�g��
	float		distanceCameraToLookAt;		// ���_���璍���_�̋���
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// ���_�̈ړ�
	positionCamera_.x = positionLookAt_.x + sinf( y + D3DX_PI ) * distanceCameraToLookAt;
	positionCamera_.z = positionLookAt_.z + cosf( y + D3DX_PI ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : �����_���SX����]�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: ���Z����l
//==============================================================================
void CameraObject::AddRotationLookAtX( float x )
{
	// ���݂̊p�x�Z�o
	float		rotationCurrentX;			// ���݂̊p�x
	D3DXVECTOR3	vectorCameraToLookAt;		// ���_���璍���_�̃x�N�g��
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	rotationCurrentX = atan2f( vectorCameraToLookAt.y, vectorCameraToLookAt.z );


	// ���_���璍���_�܂ł̋����Z�o
	float	distanceCameraToLookAt;		// ���_���璍���_�̋���
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// ���_�̈ړ�
	positionCamera_.y = positionLookAt_.y + sinf( rotationCurrentX + x ) * distanceCameraToLookAt;
	positionCamera_.z = positionLookAt_.z + cosf( rotationCurrentX + x ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : �����_���SY����]�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: ���Z����l
//==============================================================================
void CameraObject::AddRotationLookAtY( float y )
{
	// ���݂̊p�x�Z�o
	float		rotationCurrentY;			// ���݂̊p�x
	D3DXVECTOR3	vectorCameraToLookAt;		// ���_���璍���_�̃x�N�g��
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	rotationCurrentY = atan2f( vectorCameraToLookAt.x, vectorCameraToLookAt.z );

	// ���_���璍���_�܂ł̋����Z�o
	float		distanceCameraToLookAt;		// ���_���璍���_�̋���
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// ���_�̈ړ�
	positionCamera_.x = positionLookAt_.x + sinf( rotationCurrentY + y ) * distanceCameraToLookAt;
	positionCamera_.z = positionLookAt_.z + cosf( rotationCurrentY + y ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : X����]�̎擾
// Return : float								: �擾����l
// Arg    : void								: �Ȃ�
//==============================================================================
float CameraObject::GetRotationX( void )
{
	// ���݂̊p�x�Z�o
	D3DXVECTOR3	vectorCameraToLookAt;		// ���_���璍���_�̃x�N�g��
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	return atan2f( vectorCameraToLookAt.y, vectorCameraToLookAt.z );
}

//==============================================================================
// Brief  : Y����]�̎擾
// Return : float								: �擾����l
// Arg    : void								: �Ȃ�
//==============================================================================
float CameraObject::GetRotationY( void )
{
	// ���݂̊p�x�Z�o
	D3DXVECTOR3	vectorCameraToLookAt;		// ���_���璍���_�̃x�N�g��
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	return atan2f( vectorCameraToLookAt.x, vectorCameraToLookAt.z );
}

//==============================================================================
// Brief  : �X�e�[�g�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : CameraState* pValue					: �ݒ肷��l
//==============================================================================
void CameraObject::SetState( CameraState* pValue )
{
	// �l�̐ݒ�
#ifdef _DEVELOP
	if( isDebugMode_ )
	{
		pStateOriginal_ = pValue;
	}
	else
	{
		pState_ = pValue;
	}
#else
	pState_ = pValue;
#endif
}

//==============================================================================
// Brief  : �X�e�[�g�̎擾
// Return : CameraState*						: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
CameraState* CameraObject::GetState( void ) const
{
	// �l�̕ԋp
	return pState_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void CameraObject::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pState_ = nullptr;
#ifdef _DEVELOP
	pStateOriginal_ = nullptr;
	pStateDebug_ = nullptr;
	isDebugMode_ = false;
#endif
}
