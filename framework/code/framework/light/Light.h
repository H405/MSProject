//==============================================================================
//
// File   : Light.h
// Brief  : ���C�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_LIGHT_H
#define MY_LIGHT_H

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

//******************************************************************************
// �N���X��`
//******************************************************************************
class Light
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	Light( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual ~Light( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual int Initialize( void );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual int Reinitialize( void );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : Light* pOut							: �R�s�[��A�h���X
	//==============================================================================
	virtual int Copy( Light* pOut ) const;

	//==============================================================================
	// Brief  : �g�p
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Use( void );

	//==============================================================================
	// Brief  : �J��
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Release( void );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void Set( const D3DXCOLOR& diffuse, const D3DXCOLOR& specular );
	void SetDiffuse( const D3DXCOLOR& value );
	void SetDiffuse( float r, float g, float b, float a );
	void SetDiffuse( float r, float g, float b );
	void SetDiffuseR( float r );
	void SetDiffuseG( float g );
	void SetDiffuseB( float b );
	void SetDiffuseA( float a );
	void SetDiffuseAlpha( float alpha );
	void GetDiffuse( D3DXCOLOR* pOut ) const;
	float GetDiffuseR( void ) const;
	float GetDiffuseG( void ) const;
	float GetDiffuseB( void ) const;
	float GetDiffuseA( void ) const;
	void SetSpecular( const D3DXCOLOR& value );
	void SetSpecular( float r, float g, float b, float a );
	void SetSpecular( float r, float g, float b );
	void SetSpecularR( float r );
	void SetSpecularG( float g );
	void SetSpecularB( float b );
	void SetSpecularA( float a );
	void SetSpecularAlpha( float alpha );
	void GetSpecular( D3DXCOLOR* pOut ) const;
	float GetSpecularR( void ) const;
	float GetSpecularG( void ) const;
	float GetSpecularB( void ) const;
	float GetSpecularA( void ) const;
	void SetCastsShadow( bool value );
	bool GetCastsShadow( void ) const;
	bool CastsShadow( void ) const;
	void SetIsEnable( bool value );
	bool GetIsEnable( void ) const;
	bool IsEnable( void ) const;
	bool GetIsUsed( void ) const;
	bool IsUsed( void ) const;

protected:
	D3DXCOLOR	diffuse_;			// �f�B�t���[�Y�J���[
	D3DXCOLOR	specular_;			// �X�y�L�����J���[
	bool		castsShadow_;		// �e�𗎂Ƃ���
	bool		isEnable_;			// �L���t���O
	bool		isUsed_;			// �g�p�t���O

private:
	virtual void InitializeSelf( void );
	Light( const Light& );
	Light operator=( const Light& );

};

#endif	// MY_LIGHT_H
