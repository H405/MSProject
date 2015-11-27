//==============================================================================
//
// File   : PointMain.cpp
// Brief  : �|�C���g�X�v���C�g�̈�_
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "PointMain.h"
#include "../../framework/develop/Debug.h"

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
PointMain::PointMain( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
PointMain::~PointMain( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int PointMain::Initialize( void )
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int PointMain::Finalize( void )
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
int PointMain::Reinitialize( void )
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
// Arg    : PointMain* pOut							: �R�s�[��A�h���X
//==============================================================================
int PointMain::Copy( PointMain* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PointMain::Update( void )
{
	// �X�e�[�g�̍X�V
	Assert( pFunctionState != nullptr, _T( "�|�C���g�X�e�[�g���ݒ肳��Ă��܂���B" ) );
	if( pFunctionState != nullptr )
	{
		(this->*pFunctionState)();
	}

	// ���Ԃ̌o��
	++time_;
}

//==============================================================================
// Brief  : �ݒ�
// Return : void								: �Ȃ�
// Arg    : int indexState						: �X�e�[�g�ԍ�
// Arg    : const D3DXVECTOR3& position			: ���W
// Arg    : const D3DXCOLOR& color				: �F
// Arg    : float size							: �傫��
//==============================================================================
void PointMain::Set( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size )
{
	// �����o�ϐ��̐ݒ�
	position_ = position;
	size_ = size;
	color_ = color;

	// �X�e�[�g�̐ݒ�
	SetState( indexState );
	time_ = 0;

	// �g�p�t���OON
	isEnable_ = true;
}

//==============================================================================
// Brief  : �ݒ�
// Return : void								: �Ȃ�
// Arg    : int timeExist						: �c������
// Arg    : const D3DXVECTOR3& position			: ���W
// Arg    : const D3DXCOLOR& color				: �F
// Arg    : float size							: �傫��
// Arg    : const D3DXVECTOR3& differencePosition	: ���W�̕ω���
// Arg    : const D3DXCOLOR& differenceColor	: �F�̕ω���
// Arg    : float differenceSize				: �傫���̕ω���
// Arg    : int indexState						: �X�e�[�g�ԍ�
//==============================================================================
void PointMain::Set( int timeExist, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size,
	const D3DXVECTOR3& differencePosition, const D3DXCOLOR& differenceColor, float differenceSize, int indexState )
{
	// �����o�ϐ��̐ݒ�
	timeExist_ = timeExist;
	position_ = position;
	size_ = size;
	color_ = color;
	differencePosition_ = differencePosition;
	differenceColor_ = differenceColor;
	differenceSize_ = differenceSize;

	// �X�e�[�g�̐ݒ�
	SetState( indexState );
	time_ = 0;

	// �g�p�t���OON
	isEnable_ = true;
}

//==============================================================================
// Brief  : �o�ߎ��Ԃ̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int PointMain::GetTime( void ) const
{
	// �l�̕ԋp
	return time_;
}

//==============================================================================
// Brief  : �c�����Ԃ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void PointMain::SetTimeExist( int value )
{
	// �l�̐ݒ�
	timeExist_ = value;
}

//==============================================================================
// Brief  : �c�����Ԃ̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int PointMain::GetTimeExist( void ) const
{
	// �l�̕ԋp
	return timeExist_;
}

//==============================================================================
// Brief  : ���W�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void PointMain::SetPosition( const D3DXVECTOR3& value )
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
void PointMain::SetPosition( float x, float y, float z )
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
void PointMain::SetPositionX( float x )
{
	// �l�̐ݒ�
	position_.x = x;
}

//==============================================================================
// Brief  : ���W��Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void PointMain::SetPositionY( float y )
{
	// �l�̐ݒ�
	position_.y = y;
}

//==============================================================================
// Brief  : ���W��Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void PointMain::SetPositionZ( float z )
{
	// �l�̐ݒ�
	position_.z = z;
}

//==============================================================================
// Brief  : ���W�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void PointMain::GetPosition( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = position_;
}

//==============================================================================
// Brief  : ���W��X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetPositionX( void ) const
{
	// �l�̕ԋp
	return position_.x;
}

//==============================================================================
// Brief  : ���W��Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetPositionY( void ) const
{
	// �l�̕ԋp
	return position_.y;
}

//==============================================================================
// Brief  : ���W��Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetPositionZ( void ) const
{
	// �l�̕ԋp
	return position_.z;
}

//==============================================================================
// Brief  : ���W�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: ���Z����l
//==============================================================================
void PointMain::AddPosition( const D3DXVECTOR3& value )
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
void PointMain::AddPosition( float x, float y, float z )
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
void PointMain::AddPositionX( float x )
{
	// �l�̉��Z
	position_.x += x;
}

//==============================================================================
// Brief  : ���W��Y�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void PointMain::AddPositionY( float y )
{
	// �l�̉��Z
	position_.y += y;
}

//==============================================================================
// Brief  : ���W��Z�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void PointMain::AddPositionZ( float z )
{
	// �l�̉��Z
	position_.z += z;
}

//==============================================================================
// Brief  : ���W�̏�Z
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: ��Z����l
//==============================================================================
void PointMain::MultiplyPosition( const D3DXVECTOR3& value )
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
void PointMain::MultiplyPosition( float x, float y, float z )
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
void PointMain::MultiplyPositionX( float x )
{
	// �l�̏�Z
	position_.x *= x;
}

//==============================================================================
// Brief  : ���W��Y�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void PointMain::MultiplyPositionY( float y )
{
	// �l�̏�Z
	position_.y *= y;
}

//==============================================================================
// Brief  : ���W��Z�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void PointMain::MultiplyPositionZ( float z )
{
	// �l�̏�Z
	position_.z *= z;
}

//==============================================================================
// Brief  : �T�C�Y�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void PointMain::SetSize( float value )
{
	// �l�̐ݒ�
	size_ = value;
}

//==============================================================================
// Brief  : �T�C�Y�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetSize( void ) const
{
	// �l�̐ݒ�
	return size_;
}

//==============================================================================
// Brief  : �T�C�Y�̉��Z
// Return : void								: �Ȃ�
// Arg    : float value							: ���Z����l
//==============================================================================
void PointMain::AddSize( float value )
{
	// �l�̉��Z
	size_ += value;
}

//==============================================================================
// Brief  : �T�C�Y�̏�Z
// Return : void								: �Ȃ�
// Arg    : float value							: ��Z����l
//==============================================================================
void PointMain::MultiplySize( float value )
{
	// �l�̏�Z
	size_ *= value;
}

//==============================================================================
// Brief  : �F�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: �ݒ肷��l
//==============================================================================
void PointMain::SetColor( const D3DXCOLOR& value )
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
void PointMain::SetColor( float r, float g, float b, float a )
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
void PointMain::SetColor( float r, float g, float b )
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
void PointMain::SetColorR( float r )
{
	// �l�̐ݒ�
	color_.r = r;
}

//==============================================================================
// Brief  : �F��G�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void PointMain::SetColorG( float g )
{
	// �l�̐ݒ�
	color_.g = g;
}

//==============================================================================
// Brief  : �F��B�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void PointMain::SetColorB( float b )
{
	// �l�̐ݒ�
	color_.b = b;
}

//==============================================================================
// Brief  : �F��A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void PointMain::SetColorA( float a )
{
	// �l�̐ݒ�
	color_.a = a;
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void PointMain::SetColorAlpha( float alpha )
{
	// �l�̐ݒ�
	color_.a = alpha;
}

//==============================================================================
// Brief  : �F�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXCOLOR* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void PointMain::GetColor( D3DXCOLOR* pOut ) const
{
	// �l�̕ԋp
	*pOut = color_;
}

//==============================================================================
// Brief  : �F��R�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetColorR( void ) const
{
	// �l�̕ԋp
	return color_.r;
}

//==============================================================================
// Brief  : �F��G�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetColorG( void ) const
{
	// �l�̕ԋp
	return color_.g;
}

//==============================================================================
// Brief  : �F��B�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetColorB( void ) const
{
	// �l�̕ԋp
	return color_.b;
}

//==============================================================================
// Brief  : �F��A�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetColorA( void ) const
{
	// �l�̕ԋp
	return color_.a;
}

//==============================================================================
// Brief  : �F�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: ���Z����l
//==============================================================================
void PointMain::AddColor( const D3DXCOLOR& value )
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
void PointMain::AddColor( float r, float g, float b, float a )
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
void PointMain::AddColor( float r, float g, float b )
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
void PointMain::AddColorR( float r )
{
	// �l�̉��Z
	color_.r += r;
}

//==============================================================================
// Brief  : �F��G�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void PointMain::AddColorG( float g )
{
	// �l�̉��Z
	color_.g += g;
}

//==============================================================================
// Brief  : �F��B�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void PointMain::AddColorB( float b )
{
	// �l�̉��Z
	color_.b += b;
}

//==============================================================================
// Brief  : �F��A�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void PointMain::AddColorA( float a )
{
	// �l�̉��Z
	color_.a += a;
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void PointMain::AddColorAlpha( float alpha )
{
	// �l�̉��Z
	color_.a += alpha;
}

//==============================================================================
// Brief  : �F�̏�Z
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: ��Z����l
//==============================================================================
void PointMain::MultiplyColor( const D3DXCOLOR& value )
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
void PointMain::MultiplyColor( float r, float g, float b, float a )
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
void PointMain::MultiplyColor( float r, float g, float b )
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
void PointMain::MultiplyColorR( float r )
{
	// �l�̏�Z
	color_.r *= r;
}

//==============================================================================
// Brief  : �F��G�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void PointMain::MultiplyColorG( float g )
{
	// �l�̏�Z
	color_.g *= g;
}

//==============================================================================
// Brief  : �F��B�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void PointMain::MultiplyColorB( float b )
{
	// �l�̏�Z
	color_.b *= b;
}

//==============================================================================
// Brief  : �F��A�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void PointMain::MultiplyColorA( float a )
{
	// �l�̏�Z
	color_.a *= a;
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̏�Z
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void PointMain::MultiplyColorAlpha( float alpha )
{
	// �l�̏�Z
	color_.a *= alpha;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXVECTOR3& value			: �ݒ肷��l
//==============================================================================
void PointMain::SetDifferencePosition( const D3DXVECTOR3& value )
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
void PointMain::SetDifferencePosition( float x, float y, float z )
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
void PointMain::SetDifferencePositionX( float x )
{
	// �l�̐ݒ�
	differencePosition_.x = x;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ�Y�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void PointMain::SetDifferencePositionY( float y )
{
	// �l�̐ݒ�
	differencePosition_.y = y;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ�Z�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void PointMain::SetDifferencePositionZ( float z )
{
	// �l�̐ݒ�
	differencePosition_.z = z;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* pOut					: �l�̊i�[�A�h���X
//==============================================================================
void PointMain::GetDifferencePosition( D3DXVECTOR3* pOut ) const
{
	// �l�̕ԋp
	*pOut = differencePosition_;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ�X�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetDifferencePositionX( void ) const
{
	// �l�̕ԋp
	return differencePosition_.x;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ�Y�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetDifferencePositionY( void ) const
{
	// �l�̕ԋp
	return differencePosition_.y;
}

//==============================================================================
// Brief  : ���W�̕ω��ʂ�Z�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetDifferencePositionZ( void ) const
{
	// �l�̕ԋp
	return differencePosition_.z;
}

//==============================================================================
// Brief  : �T�C�Y�̕ω��ʂ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void PointMain::SetDifferenceSize( float value )
{
	// �l�̐ݒ�
	differenceSize_ = value;
}

//==============================================================================
// Brief  : �T�C�Y�̕ω��ʂ̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetDifferenceSize( void ) const
{
	// �l�̐ݒ�
	return differenceSize_;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: �ݒ肷��l
//==============================================================================
void PointMain::SetDifferenceColor( const D3DXCOLOR& value )
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
void PointMain::SetDifferenceColor( float r, float g, float b, float a )
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
void PointMain::SetDifferenceColor( float r, float g, float b )
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
void PointMain::SetDifferenceColorR( float r )
{
	// �l�̐ݒ�
	differenceColor_.r = r;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�G�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void PointMain::SetDifferenceColorG( float g )
{
	// �l�̐ݒ�
	differenceColor_.g = g;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�B�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void PointMain::SetDifferenceColorB( float b )
{
	// �l�̐ݒ�
	differenceColor_.b = b;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void PointMain::SetDifferenceColorA( float a )
{
	// �l�̐ݒ�
	differenceColor_.a = a;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ̃A���t�@�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void PointMain::SetDifferenceColorAlpha( float alpha )
{
	// �l�̐ݒ�
	differenceColor_.a = alpha;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXCOLOR* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void PointMain::GetDifferenceColor( D3DXCOLOR* pOut ) const
{
	// �l�̕ԋp
	*pOut = differenceColor_;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�R�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetDifferenceColorR( void ) const
{
	// �l�̕ԋp
	return differenceColor_.r;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�G�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetDifferenceColorG( void ) const
{
	// �l�̕ԋp
	return differenceColor_.g;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�B�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetDifferenceColorB( void ) const
{
	// �l�̕ԋp
	return differenceColor_.b;
}

//==============================================================================
// Brief  : �F�̕ω��ʂ�A�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float PointMain::GetDifferenceColorA( void ) const
{
	// �l�̕ԋp
	return differenceColor_.a;
}

//==============================================================================
// Brief  : �L���t���O�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : bool value							: �ݒ肷��l
//==============================================================================
void PointMain::SetIsEnable( bool value )
{
	// �l�̐ݒ�
	isEnable_ = value;
}

//==============================================================================
// Brief  : �L���t���O�̎擾
// Return : bool								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
bool PointMain::GetIsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �L���t���O�̔���
// Return : bool								: ���茋��
// Arg    : void								: �Ȃ�
//==============================================================================
bool PointMain::IsEnable( void ) const
{
	// �l�̕ԋp
	return isEnable_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PointMain::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pFunctionState = &PointMain::UpdateNone;
	time_ = 0;
	timeExist_ = 0;
	position_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	size_ = 0.0f;
	color_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	differencePosition_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	differenceSize_ = 0.0f;
	differenceColor_ = D3DXCOLOR( 0.0f, 0.0f, 0.0f, 0.0f );
	isEnable_ = false;
}

//==============================================================================
// Brief  : �X�e�[�g�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �X�e�[�g�ԍ�
//==============================================================================
void PointMain::SetState( int index )
{
	// �X�e�[�g�̐ݒ�
	switch( index )
	{
		case STATE_NONE:		pFunctionState = &PointMain::UpdateNone;		break;
		case STATE_ADD:			pFunctionState = &PointMain::UpdateAdd;			break;
		case STATE_MULTIPLY:	pFunctionState = &PointMain::UpdateMultiply;	break;
		default:				break;
	}
}

//==============================================================================
// Brief  : �����Ȃ�
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PointMain::UpdateNone( void )
{
	// ����
	if( time_ >= timeExist_ )
	{
		isEnable_ = false;
	}
}

//==============================================================================
// Brief  : ���Z
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PointMain::UpdateAdd( void )
{
	// �ω��ʂ����Z
	position_ += differencePosition_;
	color_ += differenceColor_;
	size_ += differenceSize_;

	// ����
	if( time_ >= timeExist_ )
	{
		isEnable_ = false;
	}
}

//==============================================================================
// Brief  : ��Z
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void PointMain::UpdateMultiply( void )
{
	// �ω��ʂ����Z
	position_.x *= differencePosition_.x;
	position_.y *= differencePosition_.y;
	position_.z *= differencePosition_.z;
	color_.r *= differenceColor_.r;
	color_.g *= differenceColor_.g;
	color_.b *= differenceColor_.b;
	color_.a *= differenceColor_.a;
	size_ *= differenceSize_;

	// ����
	if( time_ >= timeExist_ )
	{
		isEnable_ = false;
	}
}
