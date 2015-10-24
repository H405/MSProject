//==============================================================================
//
// File   : Object.h
// Brief  : �I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_H
#define MY_OBJECT_H

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
class Graphic;
template < class Object > class ManagerUpdate;

//******************************************************************************
// �N���X��`
//******************************************************************************
class Object
{
public:
	// ��]�̎��
	enum
	{
		ROTATION_VECTOR = 0,		// D3DXVECTOR3�^
		ROTATION_QUATERNION,		// D3DXQUATERNION�^
		ROTATION_MATRIX,			// D3DXMATRIX�^
		ROTATION_MAX				// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	Object( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual ~Object( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	//==============================================================================
	virtual int Initialize( int priority );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	//==============================================================================
	virtual int Reinitialize( int priority );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : Object* pOut						: �R�s�[��A�h���X
	//==============================================================================
	virtual int Copy( Object* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual void Update( void );

	//==============================================================================
	// Brief  : �`��N���X�̐���
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	//==============================================================================
	int CreateGraphic( int priority );

	//==============================================================================
	// Brief  : �X�V�Ǘ��N���X�̐ݒ�
	// Return : void								: �Ȃ�
	// Arg    : ManagerUpdate* pValue				: �ݒ肷��l
	//==============================================================================
	static void SetManagerUpdate( ManagerUpdate< Object >* pValue );

	//==============================================================================
	// Brief  : �`��N���X�̗L���ݒ�
	// Return : void								: �Ȃ�
	// Arg    : bool value							: �ݒ肷��l
	//==============================================================================
	void SetEnableGraphic( bool value );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetParent( Object* pValue );
	Object* GetParent( void ) const;
	void SetGraphic( Graphic* pValue );
	Graphic* GetGraphic( void ) const;
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
	void SetTypeRotation( int value );
	int GetTypeRotation( void ) const;
	void SetRotation( const D3DXVECTOR3& value );
	void SetRotation( float x, float y, float z );
	void SetRotationX( float x );
	void SetRotationY( float y );
	void SetRotationZ( float z );
	void GetRotation( D3DXVECTOR3* pOut ) const;
	float GetRotationX( void ) const;
	float GetRotationY( void ) const;
	float GetRotationZ( void ) const;
	void AddRotation( const D3DXVECTOR3& value );
	void AddRotation( float x, float y, float z );
	void AddRotationX( float x );
	void AddRotationY( float y );
	void AddRotationZ( float z );
	void SetQuaternionRotation( const D3DXQUATERNION& value );
	void GetQuaternionRotation( D3DXQUATERNION* pOut ) const;
	void SetMatrixRotation( const D3DXMATRIX& value );
	void GetMatrixRotation( D3DXMATRIX* pOut ) const;
	void SetScale( const D3DXVECTOR3& value );
	void SetScale( float x, float y, float z );
	void SetScaleX( float x );
	void SetScaleY( float y );
	void SetScaleZ( float z );
	void GetScale( D3DXVECTOR3* pOut ) const;
	float GetScaleX( void ) const;
	float GetScaleY( void ) const;
	float GetScaleZ( void ) const;
	void AddScale( const D3DXVECTOR3& value );
	void AddScale( float x, float y, float z );
	void AddScaleX( float x );
	void AddScaleY( float y );
	void AddScaleZ( float z );
	void SetMatrixWorld( const D3DXMATRIX& value );
	void GetMatrixWorld( D3DXMATRIX* pOut ) const;
	void SetIsEnable( bool value );
	bool GetIsEnable( void ) const;
	bool IsEnable( void ) const;

protected:
	int				idUpdate_;					// �X�V�o�^�ԍ�
	Object*			pParent_;					// �e�I�u�W�F�N�g
	Graphic*		pGraphic_;					// �`��N���X
	D3DXVECTOR3		position_;					// ���W
	int				typeRotation_;				// ��]�̎��
	D3DXVECTOR3		rotation_;					// ��]
	D3DXQUATERNION	quaternionRotation_;		// ��]�N�H�[�^�j�I��
	D3DXMATRIX		matrixRotation_;			// ��]�s��
	D3DXVECTOR3		scale_;						// �g�k
	D3DXMATRIX		matrixWorld_;				// ���[���h�}�g���N�X
	bool			needsUpdate_;				// �X�V�t���O
	bool			isEnable_;					// �L���t���O

private:
	virtual void InitializeSelf( void );
	Object( const Object& );
	Object operator=( const Object& );

	static ManagerUpdate< Object >*	pManagerUpdate_;			// �X�V�Ǘ��N���X
};

#endif	// MY_OBJECT_H
