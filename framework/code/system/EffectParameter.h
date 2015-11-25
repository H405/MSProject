//==============================================================================
//
// File   : EffectParameter.h
// Brief  : �G�t�F�N�g�t�@�C���p�̃p�����[�^�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_EFFECT_PARAMETER_H
#define MY_EFFECT_PARAMETER_H

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
class Camera;
class LightDirection;
class LightPoint;

//******************************************************************************
// �N���X��`
//******************************************************************************
class EffectParameter
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	EffectParameter( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~EffectParameter( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int maximumLightDirection			: �f�B���N�V���i�����C�g�ő吔
	// Arg    : int maximumLightPoint				: �|�C���g���C�g�ő吔
	// Arg    : int maximumCamera					: �J�����ő吔
	//==============================================================================
	int Initialize( int maximumLightDirection, int maximumLightPoint, int maximumCamera );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : int maximumLightDirection			: �f�B���N�V���i�����C�g�ő吔
	// Arg    : int maximumLightPoint				: �|�C���g���C�g�ő吔
	// Arg    : int maximumCamera					: �J�����ő吔
	//==============================================================================
	int Reinitialize( int maximumLightDirection, int maximumLightPoint, int maximumCamera );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : EffectParameter* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( EffectParameter* pOut ) const;

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetCountLightDirection( int value );
	int GetCountLightDirection( void ) const;
	void SetLightDirection( int index, const LightDirection* pValue );
	const LightDirection* GetLightDirection( int index ) const;
	void SetCountLightPoint( int value );
	int GetCountLightPoint( void ) const;
	void SetLightPoint( int index, const LightPoint* pValue );
	const LightPoint* GetLightPoint( int index ) const;
	void SetCountCamera( int value );
	int GetCountCamera( void ) const;
	void SetCamera( int index, const Camera* pValue );
	const Camera* GetCamera( int index ) const;
	void SetColorAmbient( const D3DXCOLOR& value );
	void SetColorAmbient( float r, float g, float b, float a );
	void SetColorAmbient( float r, float g, float b );
	void SetColorAmbientR( float r );
	void SetColorAmbientG( float g );
	void SetColorAmbientB( float b );
	void SetColorAmbientA( float a );
	void SetColorAmbientAlpha( float alpha );
	void GetColorAmbient( D3DXCOLOR* pOut ) const;
	float GetColorAmbientR( void ) const;
	float GetColorAmbientG( void ) const;
	float GetColorAmbientB( void ) const;
	float GetColorAmbientA( void ) const;
	void SetWidthScreen( float value );
	float GetWidthScreen( void ) const;
	void SetHeightScreen( float value );
	float GetHeightScreen( void ) const;
	void SetForcus( float value );
	float GetForcus( void ) const;
	void SetHeightReflect( float value );
	float GetHeightReflect( void ) const;

protected:

private:
	void InitializeSelf( void );
	EffectParameter( const EffectParameter& );
	EffectParameter operator=( const EffectParameter& );

	int						maximumLightDirection_;		// �f�B���N�V���i�����C�g�ő吔
	int						countLightDirection_;		// �f�B���N�V���i�����C�g��
	const LightDirection**	ppLightDirection_;			// �f�B���N�V���i�����C�g
	int						maximumLightPoint_;			// �|�C���g���C�g�ő吔
	int						countLightPoint_;			// �|�C���g���C�g��
	const LightPoint**		ppLightPoint_;				// �|�C���g���C�g
	int						maximumCamera_;				// �J�����ő吔
	int						countCamera_;				// �J������
	const Camera**			ppCamera_;					// �J����
	D3DXCOLOR				colorAmbient_;				// ����
	float					widthScreen_;				// ��ʕ�
	float					heightScreen_;				// ��ʍ���
	float					forcus_;					// �œ_����
	float					heightReflect_;				// ���˖ʂ̍���
};

#endif	// MY_EFFECT_PARAMETER_H
