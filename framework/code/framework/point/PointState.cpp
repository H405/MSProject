//==============================================================================
//
// File   : PointState.cpp
// Brief  : �|�C���g�X�v���C�g�̃X�e�[�g
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "PointState.h"
#include "Point.h"

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
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Point* pPoint						: �Ώ�
//==============================================================================
void PointState::Update( Point* pPoint )
{
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Point* pPoint						: �Ώ�
//==============================================================================
void PointStateNone::Update( Point* pPoint )
{
	// ����
	if( pPoint->GetTime() >= pPoint->GetTimeExist() )
	{
		pPoint->SetIsEnable( false );
	}
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Point* pPoint						: �Ώ�
//==============================================================================
void PointStateAdd::Update( Point* pPoint )
{
	// �ω��ʂ����Z
	D3DXVECTOR3	position;		// ���W
	D3DXCOLOR	color;			// �F
	pPoint->GetDifferencePosition( &position );
	pPoint->AddPosition( position );
	pPoint->GetDifferenceColor( &color );
	pPoint->AddColor( color );
	pPoint->AddSize( pPoint->GetDifferenceSize() );

	// ����
	if( pPoint->GetTime() >= pPoint->GetTimeExist() )
	{
		pPoint->SetIsEnable( false );
	}
}
//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : Point* pPoint						: �Ώ�
//==============================================================================
void PointStateMultiply::Update( Point* pPoint )
{
	// �ω��ʂ���Z
	D3DXVECTOR3	position;		// ���W
	D3DXCOLOR	color;			// �F
	pPoint->GetDifferencePosition( &position );
	pPoint->MultiplyPosition( position );
	pPoint->GetDifferenceColor( &color );
	pPoint->MultiplyColor( color );
	pPoint->MultiplySize( pPoint->GetDifferenceSize() );

	// ����
	if( pPoint->GetTime() >= pPoint->GetTimeExist() )
	{
		pPoint->SetIsEnable( false );
	}
}
