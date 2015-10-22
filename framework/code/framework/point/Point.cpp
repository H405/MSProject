//==============================================================================
//
// File   : Point.cpp
// Brief  : �|�C���g�X�v���C�g�̈�_
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Point.h"
#include "PointState.h"
#include "../develop/Debug.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
PointState**	Point::ppState_ = nullptr;		// �X�e�[�g�e�[�u��

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Point::Point( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Point::~Point( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Point::Initialize( void )
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Point::Finalize( void )
{
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
int Point::Reinitialize( void )
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
// Arg    : Point* pOut							: �R�s�[��A�h���X
//==============================================================================
int Point::Copy( Point* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�e�[�g�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : PointState** ppState				: �X�e�[�g�e�[�u��
//==============================================================================
void Point::SetState( PointState** ppState )
{
	// �X�e�[�g�e�[�u���̐ݒ�
	ppState_ = ppState;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Point::Update( void )
{
	// �X�e�[�g�̐؂�ւ�
	if( indexStateNext_ >= 0 )
	{
		indexStateCurrent_ = indexStateNext_;
		indexStateNext_ = -1;
		time_ = 0;
	}

	// �X�e�[�g�̍X�V
	Assert( ppState_ != nullptr, _T( "�|�C���g�X�e�[�g���ݒ肳��Ă��܂���B" ) );
	if( ppState_[ indexStateCurrent_ ] != nullptr )
	{
		ppState_[ indexStateCurrent_ ]->Update( this );
	}

	// ���Ԃ̌o��
	++time_;
}

//==============================================================================
// Brief  : �ݒ�
// Return : int									: ���s����
// Arg    : int indexState						: �X�e�[�g�ԍ�
// Arg    : const D3DXVECTOR3& position			: ���W
// Arg    : const D3DXCOLOR& color				: �F
// Arg    : float size							: �傫��
//==============================================================================
int Point::Set( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size )
{
	// �����o�ϐ��̐ݒ�
	position_ = position;
	size_ = size;
	color_ = color;

	// �l�̕ԋp
	return 0;
}

//==============================================================================
// Brief  : �ݒ�
// Return : int									: ���s����
// Arg    : int timeExist						: �c������
// Arg    : const D3DXVECTOR3& position			: ���W
// Arg    : const D3DXCOLOR& color				: �F
// Arg    : float size							: �傫��
// Arg    : const D3DXVECTOR3& differencePosition	: ���W�̕ω���
// Arg    : const D3DXCOLOR& differenceColor	: �F�̕ω���
// Arg    : float differenceSize				: �傫���̕ω���
// Arg    : int indexState						: �X�e�[�g�ԍ�
//==============================================================================
int Point::Set( int timeExist, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size, const D3DXVECTOR3& differencePosition, const D3DXCOLOR& differenceColor, float differenceSize, int indexState )
{
	// �����o�ϐ��̐ݒ�
	position_ = position;
	size_ = size;
	color_ = color;

	// �l�̕ԋp
	return 0;
}

//==============================================================================
// Brief  : �X�e�[�g�̐؂�ւ�
// Return : void								: �Ȃ�
// Arg    : int indexState						: �X�e�[�g�ԍ�
//==============================================================================
void Point::ShiftState( int indexState )
{
	// ���̃X�e�[�g�ԍ���ݒ�
	indexStateNext_ = indexState;
}

//==============================================================================
// Brief  : ���݂̃X�e�[�g�ԍ��̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int Point::GetIndexStateCurrent( void ) const
{
	// �l�̕ԋp
	return indexStateCurrent_;
}

//==============================================================================
// Brief  : �o�ߎ��Ԃ̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int Point::GetTime( void ) const
{
	// �l�̕ԋp
	return time_;
}

//==============================================================================
// Brief  : �c�����Ԃ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void Point::SetTimeExist( int value )
{
	// �l�̐ݒ�
	timeExist_ = value;
}

//==============================================================================
// Brief  : �c�����Ԃ̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int Point::GetTimeExist( void ) const
{
	// �l�̕ԋp
	return timeExist_;
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void Point::SetPosition( const D3DXVECTOR3& value )
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
void Point::SetPosition( float x, float y, float z )
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
void Point::SetPositionX( float x )
{
	// �l�̐ݒ�
	position_.x = x;
}

//==============================================================================
// Brief  : ���W��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Point::SetPositionY( float y )
{
	// �l�̐ݒ�
	position_.y = y;
}

//==============================================================================
// Brief  : ���W��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Point::SetPositionZ( float z )
{
	// �l�̐ݒ�
	position_.z = z;
}

//==============================================================================
// Brief  : ���W�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Point::GetPosition( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = position_;
}

//==============================================================================
// Brief  : ���W��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetPositionX( void ) const
{
	// �l�̕ԋp
	return position_.x;
}

//==============================================================================
// Brief  : ���W��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetPositionY( void ) const
{
	// �l�̕ԋp
	return position_.y;
}

//==============================================================================
// Brief  : ���W��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetPositionZ( void ) const
{
	// �l�̕ԋp
	return position_.z;
}

//==============================================================================
// Brief  : ���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: ���Z����l
//==============================================================================
void Point::AddPosition( const D3DXVECTOR3& value )
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
void Point::AddPosition( float x, float y, float z )
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
void Point::AddPositionX( float x )
{
	// �l�̉��Z
	position_.x += x;
}

//==============================================================================
// Brief  : ���W��Y�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Point::AddPositionY( float y )
{
	// �l�̉��Z
	position_.y += y;
}

//==============================================================================
// Brief  : ���W��Z�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Point::AddPositionZ( float z )
{
	// �l�̉��Z
	position_.z += z;
}

//==============================================================================
// Brief  : ���W�̏�Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: ��Z����l
//==============================================================================
void Point::MultiplyPosition( const D3DXVECTOR3& value )
{
	// �l�̏�Z
	position_.x *= value.x;
	position_.y *= value.y;
	position_.z *= value.z;
}

//==============================================================================
// Brief  : ���W�̏�Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Point::MultiplyPosition( float x, float y, float z )
{
	// �l�̏�Z
	position_.x *= x;
	position_.y *= y;
	position_.z *= z;
}

//==============================================================================
// Brief  : ���W��X�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Point::MultiplyPositionX( float x )
{
	// �l�̏�Z
	position_.x *= x;
}

//==============================================================================
// Brief  : ���W��Y�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Point::MultiplyPositionY( float y )
{
	// �l�̏�Z
	position_.y *= y;
}

//==============================================================================
// Brief  : ���W��Z�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Point::MultiplyPositionZ( float z )
{
	// �l�̏�Z
	position_.z *= z;
}

//==============================================================================
// Brief  : �T�C�Y�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void Point::SetSize( float value )
{
	// �l�̐ݒ�
	size_ = value;
}

//==============================================================================
// Brief  : �T�C�Y�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetSize( void ) const
{
	// �l�̐ݒ�
	return size_;
}

//==============================================================================
// Brief  : �F�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: �ݒ肷��l
//==============================================================================
void Point::SetColor( const D3DXCOLOR& value )
{
	// �l�̐ݒ�
	color_ = value;
}

//==============================================================================
// Brief  : �F��RGBA�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void Point::SetColor( float r, float g, float b, float a )
{
	// �l�̐ݒ�
	color_.r = r;
	color_.g = g;
	color_.b = b;
	color_.a = a;
}

//==============================================================================
// Brief  : �F��RGB�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
//==============================================================================
void Point::SetColor( float r, float g, float b )
{
	// �l�̐ݒ�
	color_.r = r;
	color_.g = g;
	color_.b = b;
}

//==============================================================================
// Brief  : �F��R�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
//==============================================================================
void Point::SetColorR( float r )
{
	// �l�̐ݒ�
	color_.r = r;
}

//==============================================================================
// Brief  : �F��G�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void Point::SetColorG( float g )
{
	// �l�̐ݒ�
	color_.g = g;
}

//==============================================================================
// Brief  : �F��B�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void Point::SetColorB( float b )
{
	// �l�̐ݒ�
	color_.b = b;
}

//==============================================================================
// Brief  : �F��A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void Point::SetColorA( float a )
{
	// �l�̐ݒ�
	color_.a = a;
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void Point::SetColorAlpha( float alpha )
{
	// �l�̐ݒ�
	color_.a = alpha;
}

//==============================================================================
// Brief  : �F�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXCOLOR* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void Point::GetColor( D3DXCOLOR* pOut ) const
{
	// �l�̕ԋp
	*pOut = color_;
}

//==============================================================================
// Brief  : �F��R�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetColorR( void ) const
{
	// �l�̕ԋp
	return color_.r;
}

//==============================================================================
// Brief  : �F��G�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetColorG( void ) const
{
	// �l�̕ԋp
	return color_.g;
}

//==============================================================================
// Brief  : �F��B�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetColorB( void ) const
{
	// �l�̕ԋp
	return color_.b;
}

//==============================================================================
// Brief  : �F��A�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetColorA( void ) const
{
	// �l�̕ԋp
	return color_.a;
}

//==============================================================================
// Brief  : �F�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: ���Z����l
//==============================================================================
void Point::AddColor( const D3DXCOLOR& value )
{
	// �l�̉��Z
	color_ += value;
}

//==============================================================================
// Brief  : �F��RGBA�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void Point::AddColor( float r, float g, float b, float a )
{
	// �l�̉��Z
	color_.r += r;
	color_.g += g;
	color_.b += b;
	color_.a += a;
}

//==============================================================================
// Brief  : �F��RGB�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
//==============================================================================
void Point::AddColor( float r, float g, float b )
{
	// �l�̉��Z
	color_.r += r;
	color_.g += g;
	color_.b += b;
}

//==============================================================================
// Brief  : �F��R�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
//==============================================================================
void Point::AddColorR( float r )
{
	// �l�̉��Z
	color_.r += r;
}

//==============================================================================
// Brief  : �F��G�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void Point::AddColorG( float g )
{
	// �l�̉��Z
	color_.g += g;
}

//==============================================================================
// Brief  : �F��B�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void Point::AddColorB( float b )
{
	// �l�̉��Z
	color_.b += b;
}

//==============================================================================
// Brief  : �F��A�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void Point::AddColorA( float a )
{
	// �l�̉��Z
	color_.a += a;
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void Point::AddColorAlpha( float alpha )
{
	// �l�̉��Z
	color_.a += alpha;
}

//==============================================================================
// Brief  : �F�̏�Z
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: ��Z����l
//==============================================================================
void Point::MultiplyColor( const D3DXCOLOR& value )
{
	// �l�̏�Z
	color_.r *= value.r;
	color_.g *= value.g;
	color_.b *= value.b;
	color_.a *= value.a;
}

//==============================================================================
// Brief  : �F��RGBA�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void Point::MultiplyColor( float r, float g, float b, float a )
{
	// �l�̏�Z
	color_.r *= r;
	color_.g *= g;
	color_.b *= b;
	color_.a *= a;
}

//==============================================================================
// Brief  : �F��RGB�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
//==============================================================================
void Point::MultiplyColor( float r, float g, float b )
{
	// �l�̏�Z
	color_.r *= r;
	color_.g *= g;
	color_.b *= b;
}

//==============================================================================
// Brief  : �F��R�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
//==============================================================================
void Point::MultiplyColorR( float r )
{
	// �l�̏�Z
	color_.r *= r;
}

//==============================================================================
// Brief  : �F��G�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void Point::MultiplyColorG( float g )
{
	// �l�̏�Z
	color_.g *= g;
}

//==============================================================================
// Brief  : �F��B�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void Point::MultiplyColorB( float b )
{
	// �l�̏�Z
	color_.b *= b;
}

//==============================================================================
// Brief  : �F��A�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void Point::MultiplyColorA( float a )
{
	// �l�̏�Z
	color_.a *= a;
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void Point::MultiplyColorAlpha( float alpha )
{
	// �l�̏�Z
	color_.a *= alpha;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void Point::SetDifferencePosition( const D3DXVECTOR3& value )
{
	// �l�̐ݒ�
	differencePosition_ = value;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void Point::SetDifferencePosition( float x, float y, float z )
{
	// �l�̐ݒ�
	differencePosition_.x = x;
	differencePosition_.y = y;
	differencePosition_.z = z;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ�X�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void Point::SetDifferencePositionX( float x )
{
	// �l�̐ݒ�
	differencePosition_.x = x;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ�Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void Point::SetDifferencePositionY( float y )
{
	// �l�̐ݒ�
	differencePosition_.y = y;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ�Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void Point::SetDifferencePositionZ( float z )
{
	// �l�̐ݒ�
	differencePosition_.z = z;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void Point::GetDifferencePosition( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = differencePosition_;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ�X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetDifferencePositionX( void ) const
{
	// �l�̕ԋp
	return differencePosition_.x;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ�Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetDifferencePositionY( void ) const
{
	// �l�̕ԋp
	return differencePosition_.y;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ�Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetDifferencePositionZ( void ) const
{
	// �l�̕ԋp
	return differencePosition_.z;
}

//==============================================================================
// Brief  : �T�C�Y�̕ω��ʂ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void Point::SetDifferenceSize( float value )
{
	// �l�̐ݒ�
	differenceSize_ = value;
}

//==============================================================================
// Brief  : �T�C�Y�̕ω��ʂ̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetDifferenceSize( void ) const
{
	// �l�̐ݒ�
	return differenceSize_;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: �ݒ肷��l
//==============================================================================
void Point::SetDifferenceColor( const D3DXCOLOR& value )
{
	// �l�̐ݒ�
	differenceColor_ = value;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�RGBA�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void Point::SetDifferenceColor( float r, float g, float b, float a )
{
	// �l�̐ݒ�
	differenceColor_.r = r;
	differenceColor_.g = g;
	differenceColor_.b = b;
	differenceColor_.a = a;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�RGB�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
//==============================================================================
void Point::SetDifferenceColor( float r, float g, float b )
{
	// �l�̐ݒ�
	differenceColor_.r = r;
	differenceColor_.g = g;
	differenceColor_.b = b;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�R�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
//==============================================================================
void Point::SetDifferenceColorR( float r )
{
	// �l�̐ݒ�
	differenceColor_.r = r;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�G�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void Point::SetDifferenceColorG( float g )
{
	// �l�̐ݒ�
	differenceColor_.g = g;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�B�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void Point::SetDifferenceColorB( float b )
{
	// �l�̐ݒ�
	differenceColor_.b = b;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void Point::SetDifferenceColorA( float a )
{
	// �l�̐ݒ�
	differenceColor_.a = a;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ̃A���t�@�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void Point::SetDifferenceColorAlpha( float alpha )
{
	// �l�̐ݒ�
	differenceColor_.a = alpha;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXCOLOR* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void Point::GetDifferenceColor( D3DXCOLOR* pOut ) const
{
	// �l�̕ԋp
	*pOut = differenceColor_;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�R�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetDifferenceColorR( void ) const
{
	// �l�̕ԋp
	return differenceColor_.r;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�G�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetDifferenceColorG( void ) const
{
	// �l�̕ԋp
	return differenceColor_.g;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�B�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetDifferenceColorB( void ) const
{
	// �l�̕ԋp
	return differenceColor_.b;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�A�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float Point::GetDifferenceColorA( void ) const
{
	// �l�̕ԋp
	return differenceColor_.a;
}

//==============================================================================
// Brief  : �L���t���O�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : bool value							: �ݒ肷��l
//==============================================================================
void Point::SetIsEnable( bool value )
{
	// �l�̐ݒ�
	isEnable_ = value;
}

//==============================================================================
// Brief  : �L���t���O�̎擾
// Return : bool								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
bool Point::GetIsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �L���t���O�̔���
// Return : bool								: ���茋��
// Arg    : void								: �Ȃ�
//==============================================================================
bool Point::IsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Point::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	indexStateCurrent_ = 0;
	indexStateNext_ = -1;
	time_ = 0;
	timeExist_ = 0;
	position_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	size_ = 0.0f;
	color_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	differencePosition_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	differenceSize_ = 0.0f;
	differenceColor_ = D3DXCOLOR( 0.0f, 0.0f, 0.0f, 0.0f );
	isEnable_ = true;
}
