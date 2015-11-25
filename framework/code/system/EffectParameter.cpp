//==============================================================================
//
// File   : EffectParameter.cpp
// Brief  : �G�t�F�N�g�t�@�C���p�̃p�����[�^�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "EffectParameter.h"
#include "../framework/camera/Camera.h"
#include "../framework/light/LightDirection.h"
#include "../framework/light/LightPoint.h"

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
EffectParameter::EffectParameter( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
EffectParameter::~EffectParameter( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int maximumLightDirection			: �f�B���N�V���i�����C�g�ő吔
// Arg    : int maximumLightPoint				: �|�C���g���C�g�ő吔
// Arg    : int maximumCamera					: �J�����ő吔
//==============================================================================
int EffectParameter::Initialize( int maximumLightDirection, int maximumLightPoint, int maximumCamera )
{
	// �����o�ϐ��̐ݒ�
	maximumLightDirection_ = maximumLightDirection;
	maximumLightPoint_ = maximumLightPoint;
	maximumCamera_ = maximumCamera;

	// �i�[�̈�̊m��
	if( maximumLightDirection > 0 )
	{
		ppLightDirection_ = new const LightDirection*[ maximumLightDirection ];
		if( ppLightDirection_ == nullptr )
		{
			return 1;
		}
		for( int counterLight = 0; counterLight < maximumLightDirection; ++counterLight )
		{
			ppLightDirection_[ counterLight ] = nullptr;
		}
	}
	if( maximumLightPoint > 0 )
	{
		ppLightPoint_ = new const LightPoint*[ maximumLightPoint ];
		if( ppLightPoint_ == nullptr )
		{
			return 1;
		}
		for( int counterLight = 0; counterLight < maximumLightPoint; ++counterLight )
		{
			ppLightPoint_[ counterLight ] = nullptr;
		}
	}
	if( maximumCamera > 0 )
	{
		ppCamera_ = new const Camera*[ maximumCamera ];
		if( ppCamera_ == nullptr )
		{
			return 1;
		}
		for( int counterLight = 0; counterLight < maximumCamera; ++counterLight )
		{
			ppCamera_[ counterLight ] = nullptr;
		}
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int EffectParameter::Finalize( void )
{
	// �i�[�̈�̊J��
	delete[] ppLightDirection_;
	ppLightDirection_ = nullptr;

	delete[] ppLightPoint_;
	ppLightPoint_ = nullptr;

	delete[] ppCamera_;
	ppCamera_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int maximumLightDirection			: �f�B���N�V���i�����C�g�ő吔
// Arg    : int maximumLightPoint				: �|�C���g���C�g�ő吔
// Arg    : int maximumCamera					: �J�����ő吔
//==============================================================================
int EffectParameter::Reinitialize( int maximumLightDirection, int maximumLightPoint, int maximumCamera )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( maximumLightDirection, maximumLightPoint, maximumCamera );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : EffectParameter* pOut				: �R�s�[��A�h���X
//==============================================================================
int EffectParameter::Copy( EffectParameter* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �f�B���N�V���i�����C�g���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void EffectParameter::SetCountLightDirection( int value )
{
	// �l�̐ݒ�
	countLightDirection_ = value;
}

//==============================================================================
// Brief  : �f�B���N�V���i�����C�g���̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int EffectParameter::GetCountLightDirection( void ) const
{
	// �l�̕ԋp
	return countLightDirection_;
}

//==============================================================================
// Brief  : �f�B���N�V���i�����C�g�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const LightDirection* pValue		: �ݒ肷��l
//==============================================================================
void EffectParameter::SetLightDirection( int index, const LightDirection* pValue )
{
	// �l�̐ݒ�
	ppLightDirection_[ index ] = pValue;
}

//==============================================================================
// Brief  : �f�B���N�V���i�����C�g�̎擾
// Return : const LightDirection*				: �擾����l
// Arg    : int index							: �ݒ肷��ԍ�
//==============================================================================
const LightDirection* EffectParameter::GetLightDirection( int index ) const
{
	// �l�̕ԋp
	return ppLightDirection_[ index ];
}

//==============================================================================
// Brief  : �|�C���g���C�g���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void EffectParameter::SetCountLightPoint( int value )
{
	// �l�̐ݒ�
	countLightPoint_ = value;
}

//==============================================================================
// Brief  : �|�C���g���C�g���̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int EffectParameter::GetCountLightPoint( void ) const
{
	// �l�̕ԋp
	return countLightPoint_;
}

//==============================================================================
// Brief  : �|�C���g���C�g�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const LightPoint& value				: �ݒ肷��l
//==============================================================================
void EffectParameter::SetLightPoint( int index, const LightPoint* pValue )
{
	// �l�̐ݒ�
	ppLightPoint_[ index ] = pValue;
}

//==============================================================================
// Brief  : �|�C���g���C�g�̎擾
// Return : const LightPoint*					: �擾����l
// Arg    : int index							: �ݒ肷��ԍ�
//==============================================================================
const LightPoint* EffectParameter::GetLightPoint( int index ) const
{
	// �l�̕ԋp
	return ppLightPoint_[ index ];
}

//==============================================================================
// Brief  : �J�������̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void EffectParameter::SetCountCamera( int value )
{
	// �l�̐ݒ�
	countCamera_ = value;
}

//==============================================================================
// Brief  : �J�������̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int EffectParameter::GetCountCamera( void ) const
{
	// �l�̕ԋp
	return countCamera_;
}

//==============================================================================
// Brief  : �J�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : const Camera& value					: �ݒ肷��l
//==============================================================================
void EffectParameter::SetCamera( int index, const Camera* pValue )
{
	// �l�̐ݒ�
	ppCamera_[ index ] = pValue;
}

//==============================================================================
// Brief  : �J�����̎擾
// Return : const Camera*						: �擾����l
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : Camera* pOut						: �l�̊i�[�A�h���X
//==============================================================================
const Camera* EffectParameter::GetCamera( int index ) const
{
	// �l�̕ԋp
	return ppCamera_[ index ];
}

//==============================================================================
// Brief  : �����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: �ݒ肷��l
//==============================================================================
void EffectParameter::SetColorAmbient( const D3DXCOLOR& value )
{
	// �l�̐ݒ�
	colorAmbient_ = value;
}

//==============================================================================
// Brief  : ������RGBA�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void EffectParameter::SetColorAmbient( float r, float g, float b, float a )
{
	// �l�̐ݒ�
	colorAmbient_.r = r;
	colorAmbient_.g = g;
	colorAmbient_.b = b;
	colorAmbient_.a = a;
}

//==============================================================================
// Brief  : ������RGB�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
//==============================================================================
void EffectParameter::SetColorAmbient( float r, float g, float b )
{
	// �l�̐ݒ�
	colorAmbient_.r = r;
	colorAmbient_.g = g;
	colorAmbient_.b = b;
}

//==============================================================================
// Brief  : ������R�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
//==============================================================================
void EffectParameter::SetColorAmbientR( float r )
{
	// �l�̐ݒ�
	colorAmbient_.r = r;
}

//==============================================================================
// Brief  : ������G�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void EffectParameter::SetColorAmbientG( float g )
{
	// �l�̐ݒ�
	colorAmbient_.g = g;
}

//==============================================================================
// Brief  : ������B�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void EffectParameter::SetColorAmbientB( float b )
{
	// �l�̐ݒ�
	colorAmbient_.b = b;
}

//==============================================================================
// Brief  : ������A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void EffectParameter::SetColorAmbientA( float a )
{
	// �l�̐ݒ�
	colorAmbient_.a = a;
}

//==============================================================================
// Brief  : �����̃A���t�@�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void EffectParameter::SetColorAmbientAlpha( float alpha )
{
	// �l�̐ݒ�
	colorAmbient_.a = alpha;
}

//==============================================================================
// Brief  : �����̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXCOLOR* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void EffectParameter::GetColorAmbient( D3DXCOLOR* pOut ) const
{
	// �l�̕ԋp
	*pOut = colorAmbient_;
}

//==============================================================================
// Brief  : ������R�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float EffectParameter::GetColorAmbientR( void ) const
{
	// �l�̕ԋp
	return colorAmbient_.r;
}

//==============================================================================
// Brief  : ������G�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float EffectParameter::GetColorAmbientG( void ) const
{
	// �l�̕ԋp
	return colorAmbient_.g;
}

//==============================================================================
// Brief  : ������B�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float EffectParameter::GetColorAmbientB( void ) const
{
	// �l�̕ԋp
	return colorAmbient_.b;
}

//==============================================================================
// Brief  : ������A�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float EffectParameter::GetColorAmbientA( void ) const
{
	// �l�̕ԋp
	return colorAmbient_.a;
}

//==============================================================================
// Brief  : �X�N���[�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void EffectParameter::SetWidthScreen( float value )
{
	// �l�̐ݒ�
	widthScreen_ = value;
}

//==============================================================================
// Brief  : �X�N���[�����̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float EffectParameter::GetWidthScreen( void ) const
{
	// �l�̕ԋp
	return widthScreen_;
}

//==============================================================================
// Brief  : �X�N���[�������̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void EffectParameter::SetHeightScreen( float value )
{
	// �l�̐ݒ�
	heightScreen_ = value;
}

//==============================================================================
// Brief  : �X�N���[�������̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float EffectParameter::GetHeightScreen( void ) const
{
	// �l�̕ԋp
	return heightScreen_;
}

//==============================================================================
// Brief  : �œ_�����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void EffectParameter::SetForcus( float value )
{
	// �l�̐ݒ�
	forcus_ = value;
}

//==============================================================================
// Brief  : �œ_�����̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float EffectParameter::GetForcus( void ) const
{
	// �l�̕ԋp
	return forcus_;
}

//==============================================================================
// Brief  : ���˖ʂ̍����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void EffectParameter::SetHeightReflect( float value )
{
	// �l�̐ݒ�
	heightReflect_ = value;
}

//==============================================================================
// Brief  : ���˖ʂ̍����̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float EffectParameter::GetHeightReflect( void ) const
{
	// �l�̕ԋp
	return heightReflect_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void EffectParameter::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	maximumLightDirection_ = 0;
	countLightDirection_ = 0;
	ppLightDirection_ = nullptr;
	maximumLightPoint_ = 0;
	countLightPoint_ = 0;
	ppLightPoint_ = nullptr;
	maximumCamera_ = 0;
	countCamera_ = 0;
	ppCamera_ = nullptr;
	colorAmbient_ = D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f );
	widthScreen_ = 0.0f;
	heightScreen_ = 0.0f;
	forcus_ = 0.0f;
	heightReflect_ = 0.0f;
}
