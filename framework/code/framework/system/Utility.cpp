//==============================================================================
//
// File   : Utility.cpp
// Brief  : ���C���֐�
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Utility.h"

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �֐�
//******************************************************************************
namespace Utility
{
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ControlPointSpline::ControlPointSpline( void )
	{
		// �����o�ϐ��̏�����
		position_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		vector_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	}

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ControlPointSpline::~ControlPointSpline( void )
	{
	}

	//==============================================================================
	// Brief  : �C�[�W���O����
	// Return : float								: ����
	// Arg    : float begin							: �J�n
	// Arg    : float end							: �I��
	// Arg    : float time							: ����
	//==============================================================================
	float Easing( float begin, float end, float time )
	{
		// �������v�Z
		float	proportion;		// ����
		if( time < 0.5f )
		{
			proportion = (2 * time) * (2 * time) * 0.5f;
		}
		else
		{
			proportion = -(2 * time - 2) * (2 * time - 2) * 0.5f + 1.0f;
		}

		// ���ʂ�Ԃ�
		return begin + (end - begin) * proportion;
	}

	//==============================================================================
	// Brief  : �X�v���C������
	// Return : void								: �Ȃ�
	// Arg    : const ControlPointSpline& begin		: �J�n�R���g���[���|�C���g
	// Arg    : const ControlPointSpline& end		: �I���R���g���[���|�C���g
	// Arg    : float time							: ����
	// Arg    : D3DXVECTOR3* pOut					: �o�͐�
	//==============================================================================
	void Spline( const ControlPointSpline& begin, const ControlPointSpline& end, float time, D3DXVECTOR3* pOut )
	{
		// �X�v���C������
		SplineVector3( begin.position_, begin.vector_, end.position_, end.vector_, time, pOut );
	}

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
		float time, D3DXVECTOR3* pOut )
	{
		// �s��̐ݒ�
		D3DXVECTOR4	parameter;			// �}��ϐ�
		D3DXMATRIX	coefficient;		// �W��
		D3DXMATRIX	terminal;			// �[�_
		parameter.x = time * time * time;
		parameter.y = time * time;
		parameter.z = time;
		parameter.w = 1.0f;
		coefficient._11 = 2.0f;
		coefficient._12 = coefficient._23 = -2.0f;
		coefficient._13 = coefficient._14 = coefficient._33 = coefficient._41 = 1.0f;
		coefficient._21 = -3.0f;
		coefficient._22 = 3.0f;
		coefficient._24 = -1.0f;
		coefficient._31 = coefficient._32 = coefficient._34 = coefficient._42 = coefficient._43 = coefficient._44 = 0.0f;
		terminal._11 = positionBegin.x;
		terminal._12 = positionBegin.y;
		terminal._13 = positionBegin.z;
		terminal._14 = 0.0f;
		terminal._21 = positionEnd.x;
		terminal._22 = positionEnd.y;
		terminal._23 = positionEnd.z;
		terminal._24 = 0.0f;
		terminal._31 = vectorBegin.x;
		terminal._32 = vectorBegin.y;
		terminal._33 = vectorBegin.z;
		terminal._34 = 0.0f;
		terminal._41 = vectorEnd.x;
		terminal._42 = vectorEnd.y;
		terminal._43 = vectorEnd.z;
		terminal._44 = 0.0f;

		// ���ʂ̌v�Z
		D3DXVECTOR4	position;		// ����
		D3DXVec4Transform( &position, &parameter, &coefficient );
		D3DXVec4Transform( &position, &position, &terminal );

		// ���ʂ�Ԃ�
		pOut->x = position.x;
		pOut->y = position.y;
		pOut->z = position.z;
	}
};

