//==============================================================================
//
// File   : Object.cpp
// Brief  : �I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Object.h"
#include "../develop/Debug.h"
#include "../develop/DebugProc.h"
#include "../graphic/Graphic.h"
#include "../system/ManagerUpdate.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
ManagerUpdate< Object >* Object::pManagerUpdate_ = nullptr;		// �X�V�Ǘ��N���X

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Object::Object( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Object::~Object( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
//==============================================================================
int Object::Initialize( int priority )
{
	// �G���[�`�F�b�N
	Assert( pManagerUpdate_ != nullptr, _T( "�X�V�Ǘ��N���X���o�^����Ă��܂���B" ) );

	// �Ǘ��N���X�Ɏ��g��o�^
	idUpdate_ = pManagerUpdate_->Register( this, priority );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Object::Finalize( void )
{
	// �i�[�̈�̊J��
	delete pGraphic_;
	pGraphic_ = nullptr;

	// �G���[�`�F�b�N
	Assert( pManagerUpdate_ != nullptr, _T( "�X�V�Ǘ��N���X���o�^����Ă��܂���B" ) );

	// �Ǘ��N���X�Ɏ��g�̓o�^������v��
	pManagerUpdate_->Unregister( idUpdate_ );

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
int Object::Reinitialize( int priority )
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
// Arg    : Object* pOut						: �R�s�[��A�h���X
//==============================================================================
int Object::Copy( Object* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Object::Update( void )
{
	// ���[���h�}�g���N�X�̍X�V
	if( needsUpdate_ || pParent_ != nullptr )
	{
		// ��]�s��̍쐬
		D3DXMATRIX	matrixRotation;		// ��]�s��
		D3DXMatrixIdentity( &matrixRotation );
		if( typeRotation_ == ROTATION_VECTOR )
		{
			D3DXMATRIX	matrixRotationVector;
			D3DXMatrixRotationYawPitchRoll( &matrixRotationVector, rotation_.y, rotation_.x, rotation_.z );
			matrixRotation *= matrixRotationVector;
		}
		if( typeRotation_ == ROTATION_MATRIX )
		{
			matrixRotation *= matrixRotation_;
		}

		// ���[�J���ϊ��s��̍X�V
		D3DXMatrixIdentity( &matrixWorld_ );
		matrixWorld_._11 = scale_.x;
		matrixWorld_._22 = scale_.y;
		matrixWorld_._33 = scale_.z;
		matrixWorld_ *= matrixRotation;
		matrixWorld_._41 = position_.x;
		matrixWorld_._42 = position_.y;
		matrixWorld_._43 = position_.z;

		// �e�̍s��ƍ���
		if( pParent_ != nullptr )
		{
			D3DXMATRIX	matrixRotationParent;		// �e�̉�]�s��
			pParent_->GetMatrixRotation( &matrixRotationParent );
			matrixWorld_ *= matrixRotationParent;
		}

		// �`����̍X�V
		if( pGraphic_ != nullptr )
		{
			pGraphic_->SetMatrixWorld( matrixWorld_ );
		}
	}
}

//==============================================================================
// Brief  : �`��N���X�̐���
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
//==============================================================================
int Object::CreateGraphic( int priority )
{
	// �O���t�B�b�N�̐���
	int		result;		// ���s����
	pGraphic_ = new Graphic();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V�Ǘ��N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : ManagerUpdate* pValue				: �ݒ肷��l
//==============================================================================
void Object::SetManagerUpdate( ManagerUpdate< Object >* pValue )
{
	// �l�̐ݒ�
	pManagerUpdate_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̗L���ݒ�
// Return : void								: �Ȃ�
// Arg    : bool value							: �ݒ肷��l
//==============================================================================
void Object::SetEnableGraphic( bool value )
{
	pGraphic_->SetIsEnable(value);
}

//==============================================================================
// Brief  : �e�I�u�W�F�N�g�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : Object* pValue						: �ݒ肷��l
//==============================================================================
void Object::SetParent( Object* pValue )
{
	// �l�̐ݒ�
	pParent_ = pValue;
}

//==============================================================================
// Brief  : �e�I�u�W�F�N�g�̎擾
// Return : Object*								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
Object* Object::GetParent( void ) const
{
	// �l�̕ԋp
	return pParent_;
}

//==============================================================================
// Brief  : �`��N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : Graphic* pValue						: �ݒ肷��l
//==============================================================================
void Object::SetGraphic( Graphic* pValue )
{
	// �l�̐ݒ�
	pGraphic_ = pValue;
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : Graphic*							: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
Graphic* Object::GetGraphic( void ) const
{
	// �l�̕ԋp
	return pGraphic_;
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void Object::SetPosition( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	position_ = value;
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Object::SetPosition( float x, float y, float z )
{
	// �l�̐ݒ�
	position_.x = x;
	position_.y = y;
	position_.z = z;
}

//==============================================================================
// Brief  : ���W��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Object::SetPositionX( float x )
{
	// �l�̐ݒ�
	position_.x = x;
}

//==============================================================================
// Brief  : ���W��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Object::SetPositionY( float y )
{
	// �l�̐ݒ�
	position_.y = y;
}

//==============================================================================
// Brief  : ���W��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Object::SetPositionZ( float z )
{
	// �l�̐ݒ�
	position_.z = z;
}

//==============================================================================
// Brief  : ���W�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Object::GetPosition( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = position_;
}

//==============================================================================
// Brief  : ���W��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object::GetPositionX( void ) const
{
	// �l�̕ԋp
	return position_.x;
}

//==============================================================================
// Brief  : ���W��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object::GetPositionY( void ) const
{
	// �l�̕ԋp
	return position_.y;
}

//==============================================================================
// Brief  : ���W��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object::GetPositionZ( void ) const
{
	// �l�̕ԋp
	return position_.z;
}

//==============================================================================
// Brief  : ���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: ���Z����l
//==============================================================================
void Object::AddPosition( const D3DXVECTOR3& value )
{
	// �l�̉��Z
	position_ += value;
}

//==============================================================================
// Brief  : ���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Object::AddPosition( float x, float y, float z )
{
	// �l�̉��Z
	position_.x += x;
	position_.y += y;
	position_.z += z;
}

//==============================================================================
// Brief  : ���W��X�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Object::AddPositionX( float x )
{
	// �l�̉��Z
	position_.x += x;
}

//==============================================================================
// Brief  : ���W��Y�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Object::AddPositionY( float y )
{
	// �l�̉��Z
	position_.y += y;
}

//==============================================================================
// Brief  : ���W��Z�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Object::AddPositionZ( float z )
{
	// �l�̉��Z
	position_.z += z;
}

//==============================================================================
// Brief  : ��]�̎�ނ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void Object::SetTypeRotation( int value )
{
	// �l�̐ݒ�
	typeRotation_ = value;
}

//==============================================================================
// Brief  : ��]�̎�ނ̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int Object::GetTypeRotation( void ) const
{
	// �l�̕ԋp
	return typeRotation_;
}

//==============================================================================
// Brief  : ��]�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void Object::SetRotation( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	rotation_ = value;
}

//==============================================================================
// Brief  : ��]�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Object::SetRotation( float x, float y, float z )
{
	// �l�̐ݒ�
	rotation_.x = x;
	rotation_.y = y;
	rotation_.z = z;
}

//==============================================================================
// Brief  : ��]��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Object::SetRotationX( float x )
{
	// �l�̐ݒ�
	rotation_.x = x;
}

//==============================================================================
// Brief  : ��]��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Object::SetRotationY( float y )
{
	// �l�̐ݒ�
	rotation_.y = y;
}

//==============================================================================
// Brief  : ��]��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Object::SetRotationZ( float z )
{
	// �l�̐ݒ�
	rotation_.z = z;
}

//==============================================================================
// Brief  : ��]�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Object::GetRotation( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = rotation_;
}

//==============================================================================
// Brief  : ��]��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object::GetRotationX( void ) const
{
	// �l�̕ԋp
	return rotation_.x;
}

//==============================================================================
// Brief  : ��]��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object::GetRotationY( void ) const
{
	// �l�̕ԋp
	return rotation_.y;
}

//==============================================================================
// Brief  : ��]��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object::GetRotationZ( void ) const
{
	// �l�̕ԋp
	return rotation_.z;
}

//==============================================================================
// Brief  : ��]�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: ���Z����l
//==============================================================================
void Object::AddRotation( const D3DXVECTOR3& value )
{
	// �l�̉��Z
	rotation_ += value;
}

//==============================================================================
// Brief  : ��]�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Object::AddRotation( float x, float y, float z )
{
	// �l�̉��Z
	rotation_.x += x;
	rotation_.y += y;
	rotation_.z += z;
}

//==============================================================================
// Brief  : ��]��X�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Object::AddRotationX( float x )
{
	// �l�̉��Z
	rotation_.x += x;
}

//==============================================================================
// Brief  : ��]��Y�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Object::AddRotationY( float y )
{
	// �l�̉��Z
	rotation_.y += y;
}

//==============================================================================
// Brief  : ��]��Z�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Object::AddRotationZ( float z )
{
	// �l�̉��Z
	rotation_.z += z;
}

//==============================================================================
// Brief  : ��]�N�H�[�^�j�I���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXQUATERNION& value			: �ݒ肷��l
//==============================================================================
void Object::SetQuaternionRotation( const D3DXQUATERNION& value )
{
	// �l�̐ݒ�
	quaternionRotation_ = value;
}

//==============================================================================
// Brief  : ��]�N�H�[�^�j�I���̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXQUATERNION* pOut				: �l�̊i�[�A�h���X
//==============================================================================
void Object::GetQuaternionRotation( D3DXQUATERNION* pOut ) const
{
	// �l�̕ԋp
	*pOut = quaternionRotation_;
}

//==============================================================================
// Brief  : ��]�s��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXMATRIX& value				: �ݒ肷��l
//==============================================================================
void Object::SetMatrixRotation( const D3DXMATRIX& value )
{
	// �l�̐ݒ�
	matrixRotation_ = value;
}

//==============================================================================
// Brief  : ��]�s��̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXMATRIX* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Object::GetMatrixRotation( D3DXMATRIX* pOut ) const
{
	// �l�̕ԋp
	*pOut = matrixRotation_;
}

//==============================================================================
// Brief  : �g�k�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void Object::SetScale( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	scale_ = value;
}

//==============================================================================
// Brief  : �g�k�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Object::SetScale( float x, float y, float z )
{
	// �l�̐ݒ�
	scale_.x = x;
	scale_.y = y;
	scale_.z = z;
}

//==============================================================================
// Brief  : �g�k��X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Object::SetScaleX( float x )
{
	// �l�̐ݒ�
	scale_.x = x;
}

//==============================================================================
// Brief  : �g�k��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Object::SetScaleY( float y )
{
	// �l�̐ݒ�
	scale_.y = y;
}

//==============================================================================
// Brief  : �g�k��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Object::SetScaleZ( float z )
{
	// �l�̐ݒ�
	scale_.z = z;
}

//==============================================================================
// Brief  : �g�k�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Object::GetScale( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = scale_;
}

//==============================================================================
// Brief  : �g�k��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object::GetScaleX( void ) const
{
	// �l�̕ԋp
	return scale_.x;
}

//==============================================================================
// Brief  : �g�k��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object::GetScaleY( void ) const
{
	// �l�̕ԋp
	return scale_.y;
}

//==============================================================================
// Brief  : �g�k��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Object::GetScaleZ( void ) const
{
	// �l�̕ԋp
	return scale_.z;
}

//==============================================================================
// Brief  : �g�k�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: ���Z����l
//==============================================================================
void Object::AddScale( const D3DXVECTOR3& value )
{
	// �l�̉��Z
	scale_ += value;
}

//==============================================================================
// Brief  : �g�k�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Object::AddScale( float x, float y, float z )
{
	// �l�̉��Z
	scale_.x += x;
	scale_.y += y;
	scale_.z += z;
}

//==============================================================================
// Brief  : �g�k��X�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Object::AddScaleX( float x )
{
	// �l�̉��Z
	scale_.x += x;
}

//==============================================================================
// Brief  : �g�k��Y�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Object::AddScaleY( float y )
{
	// �l�̉��Z
	scale_.y += y;
}

//==============================================================================
// Brief  : �g�k��Z�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Object::AddScaleZ( float z )
{
	// �l�̉��Z
	scale_.z += z;
}

//==============================================================================
// Brief  : ���[���h�}�g���N�X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXMATRIX& value				: �ݒ肷��l
//==============================================================================
void Object::SetMatrixWorld( const D3DXMATRIX& value )
{
	// �l�̐ݒ�
	matrixWorld_ = value;
}

//==============================================================================
// Brief  : ���[���h�}�g���N�X�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXMATRIX* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Object::GetMatrixWorld( D3DXMATRIX* pOut ) const
{
	// �l�̕ԋp
	*pOut = matrixWorld_;
}

//==============================================================================
// Brief  : �L���t���O�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : bool value							: �ݒ肷��l
//==============================================================================
void Object::SetIsEnable( bool value )
{
	// �l�̐ݒ�
	isEnable_ = value;
}

//==============================================================================
// Brief  : �L���t���O�̎擾
// Return : bool								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
bool Object::GetIsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �L���t���O�̔���
// Return : bool								: ���茋��
// Arg    : void								: �Ȃ�
//==============================================================================
bool Object::IsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Object::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	idUpdate_ = -1;
	pParent_ = nullptr;
	pGraphic_ = nullptr;
	position_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	typeRotation_ = ROTATION_VECTOR;
	rotation_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	quaternionRotation_ = D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 1.0f );
	matrixRotation_ = D3DXMATRIX( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f );
	scale_ = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
	matrixWorld_ = D3DXMATRIX( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f );
	needsUpdate_ = true;
	isEnable_ = true;
}
