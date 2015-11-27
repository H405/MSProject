//==============================================================================
//
// File   : PointMain.h
// Brief  : �|�C���g�X�v���C�g�̈�_
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_POINT_MAIN_H
#define MY_POINT_MAIN_H

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
class PointMainState;

//******************************************************************************
// �N���X��`
//******************************************************************************
class PointMain
{
friend class PointMainState;

public:
	// �X�e�[�g
	enum
	{
		STATE_NONE = 0,		// �Ȃ�
		STATE_ADD,			// ���Z
		STATE_MULTIPLY,		// ��Z
		STATE_MAX			// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	PointMain( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~PointMain( void );

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
	// Arg    : PointMain* pOut						: �R�s�[��A�h���X
	//==============================================================================
	int Copy( PointMain* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : �ݒ�
	// Return : void								: �Ȃ�
	// Arg    : int indexState						: �X�e�[�g�ԍ�
	// Arg    : const D3DXVECTOR3& position			: ���W
	// Arg    : const D3DXCOLOR& color				: �F
	// Arg    : float size							: �傫��
	//==============================================================================
	void Set( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size );

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
	void Set( int timeExist, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size,
		const D3DXVECTOR3& differencePosition, const D3DXCOLOR& differenceColor, float differenceSize, int indexState );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	int GetTime( void ) const;
	void SetTimeExist( int value );
	int GetTimeExist( void ) const;
	void SetPosition( const D3DXVECTOR3& value );
	void SetPosition( float x, float y, float z );
	void SetPositionX( float x );
	void SetPositionY( float y );
	void SetPositionZ( float z );
	void GetPosition( D3DXVECTOR3* pOut ) const;
	float GetPositionX( void ) const;
	float GetPositionY( void ) const;
	float GetPositionZ( void ) const;
	void AddPosition( const D3DXVECTOR3& value );
	void AddPosition( float x, float y, float z );
	void AddPositionX( float x );
	void AddPositionY( float y );
	void AddPositionZ( float z );
	void MultiplyPosition( const D3DXVECTOR3& value );
	void MultiplyPosition( float x, float y, float z );
	void MultiplyPositionX( float x );
	void MultiplyPositionY( float y );
	void MultiplyPositionZ( float z );
	void SetSize( float value );
	float GetSize( void ) const;
	void AddSize( float value );
	void MultiplySize( float value );
	void SetColor( const D3DXCOLOR& value );
	void SetColor( float r, float g, float b, float a );
	void SetColor( float r, float g, float b );
	void SetColorR( float r );
	void SetColorG( float g );
	void SetColorB( float b );
	void SetColorA( float a );
	void SetColorAlpha( float alpha );
	void GetColor( D3DXCOLOR* pOut ) const;
	float GetColorR( void ) const;
	float GetColorG( void ) const;
	float GetColorB( void ) const;
	float GetColorA( void ) const;
	void AddColor( const D3DXCOLOR& value );
	void AddColor( float r, float g, float b, float a );
	void AddColor( float r, float g, float b );
	void AddColorR( float r );
	void AddColorG( float g );
	void AddColorB( float b );
	void AddColorA( float a );
	void AddColorAlpha( float alpha );
	void MultiplyColor( const D3DXCOLOR& value );
	void MultiplyColor( float r, float g, float b, float a );
	void MultiplyColor( float r, float g, float b );
	void MultiplyColorR( float r );
	void MultiplyColorG( float g );
	void MultiplyColorB( float b );
	void MultiplyColorA( float a );
	void MultiplyColorAlpha( float alpha );
	void SetDifferencePosition( const D3DXVECTOR3& value );
	void SetDifferencePosition( float x, float y, float z );
	void SetDifferencePositionX( float x );
	void SetDifferencePositionY( float y );
	void SetDifferencePositionZ( float z );
	void GetDifferencePosition( D3DXVECTOR3* pOut ) const;
	float GetDifferencePositionX( void ) const;
	float GetDifferencePositionY( void ) const;
	float GetDifferencePositionZ( void ) const;
	void SetDifferenceSize( float value );
	float GetDifferenceSize( void ) const;
	void SetDifferenceColor( const D3DXCOLOR& value );
	void SetDifferenceColor( float r, float g, float b, float a );
	void SetDifferenceColor( float r, float g, float b );
	void SetDifferenceColorR( float r );
	void SetDifferenceColorG( float g );
	void SetDifferenceColorB( float b );
	void SetDifferenceColorA( float a );
	void SetDifferenceColorAlpha( float alpha );
	void GetDifferenceColor( D3DXCOLOR* pOut ) const;
	float GetDifferenceColorR( void ) const;
	float GetDifferenceColorG( void ) const;
	float GetDifferenceColorB( void ) const;
	float GetDifferenceColorA( void ) const;
	void SetIsEnable( bool value );
	bool GetIsEnable( void ) const;
	bool IsEnable( void ) const;

protected:

private:
	PointMain( const PointMain& );
	PointMain operator=( const PointMain& );

	void InitializeSelf( void );
	void SetState( int index );

	void UpdateNone( void );
	void UpdateAdd( void );
	void UpdateMultiply( void );

	void (PointMain::*pFunctionState)( void );		// �X�e�[�g

	int			time_;						// �o�ߎ���
	int			timeExist_;					// �c������
	D3DXVECTOR3	position_;					// ���W
	float		size_;						// �傫��
	D3DXCOLOR	color_;						// �F
	D3DXVECTOR3	differencePosition_;		// ���W�̕ω���
	float		differenceSize_;			// �傫���̕ω���
	D3DXCOLOR	differenceColor_;			// �F�̕ω���
	bool		isEnable_;					// �L���t���O
};

#endif	// MY_POINT_MAIN_H
