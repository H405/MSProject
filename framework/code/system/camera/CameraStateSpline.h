//==============================================================================
//
// File   : CameraStateSpline.h
// Brief  : �X�v���C���ړ��X�e�[�g
// Author : Taiga Shirakawa
// Date   : 2015/11/07 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_CAMERA_STATE_SPLINE_H
#define MY_CAMERA_STATE_SPLINE_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../../framework/camera/CameraState.h"
#include "../../framework/system/Utility.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class InputMouse;

//******************************************************************************
// �N���X��`
//******************************************************************************
class CameraStateSpline : public CameraState
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	CameraStateSpline( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~CameraStateSpline( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int countSection					: �Z�N�V������
	// Arg    : int countControlPointCamera			: ���_�R���g���[���|�C���g��
	// Arg    : int countControlPointLookAt			: ���_�R���g���[���|�C���g��
	//==============================================================================
	int Initialize( int countSection, int countControlPointCamera, int countControlPointLookAt );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : int countSection					: �Z�N�V������
	// Arg    : int countControlPointCamera			: ���_�R���g���[���|�C���g��
	// Arg    : int countControlPointLookAt			: ���_�R���g���[���|�C���g��
	//==============================================================================
	int Reinitialize( int countSection, int countControlPointCamera, int countControlPointLookAt );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : CameraStateSpline* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( CameraStateSpline* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : CameraObject* pCamera				: �J�����N���X
	//==============================================================================
	void Update( CameraObject* pCamera );

	//==============================================================================
	// Brief  : �Z�N�V�����̐ݒ�
	// Return : void								: �Ȃ�
	// Arg    : int index							: �ݒ肷��ԍ�
	// Arg    : int frame							: ��������
	// Arg    : int indexCameraBegin				: �J�n���_�R���g���[���|�C���g�ԍ�
	// Arg    : int indexCameraEnd					: �I�����_�R���g���[���|�C���g�ԍ�
	// Arg    : int indexLookAtBegin				: �J�n�����_�R���g���[���|�C���g�ԍ�
	// Arg    : int indexLookAtEnd					: �I�������_�R���g���[���|�C���g�ԍ�
	//==============================================================================
	void SetSection( int index, int frame, int indexCameraBegin, int indexCameraEnd, int indexLookAtBegin, int indexLookAtEnd );

	//==============================================================================
	// Brief  : ���_�R���g���[���|�C���g�̐ݒ�
	// Return : void								: �Ȃ�
	// Arg    : int index							: �ݒ肷��ԍ�
	// Arg    : const D3DXVECTOR3& position			: ���W
	// Arg    : const D3DXVECTOR3& vector			: �x�N�g��
	//==============================================================================
	void SetControlPointCamera( int index, const D3DXVECTOR3& position, const D3DXVECTOR3& vector );

	//==============================================================================
	// Brief  : �����_�R���g���[���|�C���g�̐ݒ�
	// Return : void								: �Ȃ�
	// Arg    : int index							: �ݒ肷��ԍ�
	// Arg    : const D3DXVECTOR3& position			: ���W
	// Arg    : const D3DXVECTOR3& vector			: �x�N�g��
	//==============================================================================
	void SetControlPointLookAt( int index, const D3DXVECTOR3& position, const D3DXVECTOR3& vector );

protected:

private:
	void InitializeSelf( void );
	CameraStateSpline( const CameraStateSpline& );
	CameraStateSpline operator=( const CameraStateSpline& );

	int								countSection_;					// �Z�N�V������
	int								countControlPointCamera_;		// ���_�R���g���[���|�C���g��
	int								countControlPointLookAt_;		// �����_�R���g���[���|�C���g��
	int								indexSection_;					// �Z�N�V�����ԍ�
	int								countFrame_;					// �o�߃t���[����
	int*							pFrame_;						// �p������
	Utility::ControlPointSpline*	pTablePointCamera_;				// ���_�R���g���[���|�C���g�e�[�u��
	Utility::ControlPointSpline*	pTablePointLookAt_;				// �����_�R���g���[���|�C���g�e�[�u��
	int*							pIndexPointCameraBegin_;		// �J�n���_�R���g���[���|�C���g�ԍ�
	int*							pIndexPointCameraEnd_;			// �I�����_�R���g���[���|�C���g�ԍ�
	int*							pIndexPointLookAtBegin_;		// �J�n�����_�R���g���[���|�C���g�ԍ�
	int*							pIndexPointLookAtEnd_;			// �I�������_�R���g���[���|�C���g�ԍ�
};

#endif	// MY_CAMERA_STATE_SPLINE_H
