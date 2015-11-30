//==============================================================================
//
// File   : LightPoint.h
// Brief  : �|�C���g���C�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_LIGHT_POINT_H
#define MY_LIGHT_POINT_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Light.h"

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
class LightPoint : public Light
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	LightPoint( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~LightPoint( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Initialize( void );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Reinitialize( void );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : LightPoint* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( LightPoint* pOut ) const;

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void Set( const D3DXCOLOR& diffuse, const D3DXCOLOR& specular, const D3DXVECTOR3& position, const D3DXVECTOR3& attenuation );
	void SetPosition( const D3DXVECTOR3& value );
	void SetPosition( float x, float y, float z );
	void SetPositionX( float x );
	void SetPositionY( float y );
	void SetPositionZ( float z );
	void GetPosition( D3DXVECTOR3* pOut ) const;
	float GetPositionX( void ) const;
	float GetPositionY( void ) const;
	float GetPositionZ( void ) const;
	void SetAttenuation( const D3DXVECTOR3& value );
	void SetAttenuation( float x, float y, float z );
	void SetAttenuationX( float x );
	void SetAttenuationY( float y );
	void SetAttenuationZ( float z );
	void GetAttenuation( D3DXVECTOR3* pOut ) const;
	float GetAttenuationX( void ) const;
	float GetAttenuationY( void ) const;
	float GetAttenuationZ( void ) const;

protected:
	D3DXVECTOR3	position_;			// ���W
	D3DXVECTOR3	attenuation_;		// ������

private:
	void InitializeSelf( void );
	LightPoint( const LightPoint& );
	LightPoint operator=( const LightPoint& );

};

#endif	// MY_LIGHT_POINT_H
