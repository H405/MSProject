//==============================================================================
//
// File   : GraphicMain.cpp
// Brief  : �`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicMain.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
Polygon2D*			GraphicMain::pPolygon2D_ = nullptr;				// 2D�|���S���N���X
Polygon3D*			GraphicMain::pPolygon3D_ = nullptr;				// 3D�|���S���N���X
PolygonBillboard*	GraphicMain::pPolygonBillboard_ = nullptr;		// �r���{�[�h�|���S���N���X
PolygonSignboard*	GraphicMain::pPolygonSignboard_ = nullptr;		// ������r���{�[�h�|���S���N���X

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicMain::GraphicMain( void ) : Graphic()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
GraphicMain::~GraphicMain( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
//==============================================================================
int GraphicMain::Initialize( int priority )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Graphic::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �`��N���X�i�[�̈�̊m��
	countDraw_ = GraphicMain::PASS_MAX;
	ppDraw_ = new Drawer*[ GraphicMain::PASS_MAX ];
	if( ppDraw_ == nullptr )
	{
		return 1;
	}
	for( int counterDrawer = 0; counterDrawer < GraphicMain::PASS_MAX; ++counterDrawer )
	{
		ppDraw_[ counterDrawer ] = nullptr;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int GraphicMain::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Graphic::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
//==============================================================================
int GraphicMain::Reinitialize( int priority )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : GraphicMain* pOut					: �R�s�[��A�h���X
//==============================================================================
int GraphicMain::Copy( GraphicMain* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Graphic::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : 2D�|���S���N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : Polygon2D* pValue					: �ݒ肷��l
//==============================================================================
void GraphicMain::SetPolygon2D( Polygon2D* pValue )
{
	// �l�̐ݒ�
	pPolygon2D_ = pValue;
}

//==============================================================================
// Brief  : 3D�|���S���N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : Polygon3D* pValue					: �ݒ肷��l
//==============================================================================
void GraphicMain::SetPolygon3D( Polygon3D* pValue )
{
	// �l�̐ݒ�
	pPolygon3D_ = pValue;
}

//==============================================================================
// Brief  : �r���{�[�h�|���S���N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : PolygonBillboard* pValue			: �ݒ肷��l
//==============================================================================
void GraphicMain::SetPolygonBillboard( PolygonBillboard* pValue )
{
	// �l�̐ݒ�
	pPolygonBillboard_ = pValue;
}

//==============================================================================
// Brief  : ������r���{�[�h�|���S���N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : PolygonSignboard* pValue			: �ݒ肷��l
//==============================================================================
void GraphicMain::SetPolygonSignboard( PolygonSignboard* pValue )
{
	// �l�̐ݒ�
	pPolygonSignboard_ = pValue;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void GraphicMain::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
}
