//==============================================================================
//
// File   : Utility.h
// Brief  : ���C���֐�
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_UTILITY_H
#define MY_UTILITY_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "d3dx9.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************
namespace Utility
{
	// �X�v���C���Ȑ��̃R���g���[���|�C���g
	class ControlPointSpline
	{
	public:
		ControlPointSpline( void );			// �R���X�g���N�^
		~ControlPointSpline( void );		// �f�X�g���N�^

		D3DXVECTOR3	position_;		// ���W
		D3DXVECTOR3	vector_;			// �x�N�g��
	};

	//==============================================================================
	// Brief  : �C�[�W���O����
	// Return : float								: ����
	// Arg    : float begin							: �J�n
	// Arg    : float end							: �I��
	// Arg    : float time							: ����
	//==============================================================================
	float Easing( float begin, float end, float time );

	//==============================================================================
	// Brief  : �X�v���C������
	// Return : void								: �Ȃ�
	// Arg    : const ControlPointSpline& begin		: �J�n�R���g���[���|�C���g
	// Arg    : const ControlPointSpline& end		: �I���R���g���[���|�C���g
	// Arg    : float time							: ����
	// Arg    : D3DXVECTOR3* pOut					: �o�͐�
	//==============================================================================
	void Spline( const ControlPointSpline& begin, const ControlPointSpline& end, float time, D3DXVECTOR3* pOut );

	//==============================================================================
	// Brief  : �X�v���C������
	// Return : void								: �Ȃ�
	// Arg    : const D3DXVECTOR3& positionBegin	: �J�n���W
	// Arg    : const D3DXVECTOR3& vectorBegin		: �J�n�x�N�g��
	// Arg    : const D3DXVECTOR3& positionEnd		: �I�����W
	// Arg    : const D3DXVECTOR3& vectonEnd		: �I���x�N�g��
	// Arg    : float time							: ����
	// Arg    : D3DXVECTOR3* pOut					: �o�͐�
	//==============================================================================
	void SplineVector3( const D3DXVECTOR3& positionBegin, const D3DXVECTOR3& vectorBegin, const D3DXVECTOR3& positionEnd, const D3DXVECTOR3& vectorEnd,
		float time, D3DXVECTOR3* pOut );
};

#endif // MY_UTILITY_H
