//==============================================================================
//
// File   : LightPoint.cpp
// Brief  : �|�C���g���C�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "LightPoint.h"

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
LightPoint::LightPoint( void ) : Light()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
LightPoint::~LightPoint( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : const D3DXCOLOR& diffuse			: �f�B�t���[�Y�J���[
// Arg    : const D3DXCOLOR& specular			: �X�y�L�����J���[
// Arg    : const D3DXVECTOR3& position			: ���W
// Arg    : const D3DXVECTOR3& attemuation		: ������
//==============================================================================
int LightPoint::Initialize( const D3DXCOLOR& diffuse, const D3DXCOLOR& specular, const D3DXVECTOR3& position, const D3DXVECTOR3& attemuation )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Light::Initialize( diffuse, specular );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	position_ = position;
	attemuation_ = attemuation;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int LightPoint::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Light::Finalize();
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
// Arg    : const D3DXCOLOR& diffuse			: �f�B�t���[�Y�J���[
// Arg    : const D3DXCOLOR& specular			: �X�y�L�����J���[
// Arg    : const D3DXVECTOR3& position			: ���W
// Arg    : const D3DXVECTOR3& attemuation		: ������
//==============================================================================
int LightPoint::Reinitialize( const D3DXCOLOR& diffuse, const D3DXCOLOR& specular, const D3DXVECTOR3& position, const D3DXVECTOR3& attemuation )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( diffuse, specular, position, attemuation );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : LightPoint* pOut					: �R�s�[��A�h���X
//==============================================================================
int LightPoint::Copy( LightPoint* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Light::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void LightPoint::SetPosition( const D3DXVECTOR3& value )
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
void LightPoint::SetPosition( float x, float y, float z )
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
void LightPoint::SetPositionX( float x )
{
	// �l�̐ݒ�
	position_.x = x;
}

//==============================================================================
// Brief  : ���W��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void LightPoint::SetPositionY( float y )
{
	// �l�̐ݒ�
	position_.y = y;
}

//==============================================================================
// Brief  : ���W��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void LightPoint::SetPositionZ( float z )
{
	// �l�̐ݒ�
	position_.z = z;
}

//==============================================================================
// Brief  : ���W�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void LightPoint::GetPosition( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = position_;
}

//==============================================================================
// Brief  : ���W��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float LightPoint::GetPositionX( void ) const
{
	// �l�̕ԋp
	return position_.x;
}

//==============================================================================
// Brief  : ���W��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float LightPoint::GetPositionY( void ) const
{
	// �l�̕ԋp
	return position_.y;
}

//==============================================================================
// Brief  : ���W��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float LightPoint::GetPositionZ( void ) const
{
	// �l�̕ԋp
	return position_.z;
}

//==============================================================================
// Brief  : �������̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void LightPoint::SetAttemuation( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	attemuation_ = value;
}

//==============================================================================
// Brief  : �������̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void LightPoint::SetAttemuation( float x, float y, float z )
{
	// �l�̐ݒ�
	attemuation_.x = x;
	attemuation_.y = y;
	attemuation_.z = z;
}

//==============================================================================
// Brief  : ��������X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void LightPoint::SetAttemuationX( float x )
{
	// �l�̐ݒ�
	attemuation_.x = x;
}

//==============================================================================
// Brief  : ��������Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void LightPoint::SetAttemuationY( float y )
{
	// �l�̐ݒ�
	attemuation_.y = y;
}

//==============================================================================
// Brief  : ��������Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void LightPoint::SetAttemuationZ( float z )
{
	// �l�̐ݒ�
	attemuation_.z = z;
}

//==============================================================================
// Brief  : �������̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void LightPoint::GetAttemuation( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = attemuation_;
}

//==============================================================================
// Brief  : ��������X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float LightPoint::GetAttemuationX( void ) const
{
	// �l�̕ԋp
	return attemuation_.x;
}

//==============================================================================
// Brief  : ��������Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float LightPoint::GetAttemuationY( void ) const
{
	// �l�̕ԋp
	return attemuation_.y;
}

//==============================================================================
// Brief  : ��������Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float LightPoint::GetAttemuationZ( void ) const
{
	// �l�̕ԋp
	return attemuation_.z;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void LightPoint::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	position_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	attemuation_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}
