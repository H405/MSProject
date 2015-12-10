//==============================================================================
//
// File   : GraphicMain.h
// Brief  : �`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_MAIN_H
#define MY_GRAPHIC_MAIN_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../../framework/graphic/graphic.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Polygon2D;
class Polygon3D;
class PolygonBillboard;

//******************************************************************************
// �N���X��`
//******************************************************************************
class GraphicMain : public Graphic
{
public:
	// �p�X
	enum
	{
		PASS_WAVE_DATA = 0,				// �g���
		PASS_3D,						// 3D�`��
		PASS_DEPTH_SHADOW_NEAR,			// �e�p�[�x(��)
		PASS_DEPTH_SHADOW_FAR,			// �e�p�[�x(��)
		PASS_DEPTH_SHADOW_POINT_0,		// �e�p�[�x(�_0)
		PASS_DEPTH_SHADOW_POINT_1,		// �e�p�[�x(�_1)
		PASS_SHADOW,					// �e
		PASS_BLUR_SHADOW,				// �e�p�u���[
		PASS_REFLECT,					// ����
		PASS_LIGHT_REFLECT,				// ���˂̃��C�e�B���O
		PASS_REFLECT_NOT_LIGHT,			// ���˃��C�e�B���O�Ȃ�
		PASS_WATER,						// ��
		PASS_3D_NOT_LIGHT,				// ���C�e�B���O�Ȃ�3D�`��
		PASS_LIGHT_EFFECT,				// ���C�e�B���O
		PASS_3D_MERGE,					// ����3D�`��
		PASS_BLUR_X,					// X�����u���[
		PASS_BLUR_Y,					// Y�����u���[
		PASS_2D,						// 2D�`��
		PASS_POST_EFFECT,				// �|�X�g�G�t�F�N�g
		PASS_MAX						// �ő吔
	};

	// �g
	enum
	{
		RENDER_PASS_WAVE_DATA_HEIGHT = 0,				// ����
		RENDER_PASS_WAVE_DATA_NORMAL,					// �@��
		RENDER_PASS_WAVE_DATA_MAX						// �ő�l
	};

	// 3D�`��
	enum
	{
		RENDER_PASS_3D_DIFFUSE = 0,						// �f�B�t���[�Y�F
		RENDER_PASS_3D_SPECULAR,						// �X�y�L�����F
		RENDER_PASS_3D_NORMAL,							// �@��
		RENDER_PASS_3D_DEPTH,							// �[�x
		RENDER_PASS_3D_MAX								// �ő�l
	};

	// �e�p�[�x(��)
	enum
	{
		RENDER_PASS_DEPTH_SHADOW_NEAR_DEPTH = 0,		// �[�x
		RENDER_PASS_DEPTH_SHADOW_NEAR_MAX				// �ő�l
	};

	// �e�p�[�x(��)
	enum
	{
		RENDER_PASS_DEPTH_SHADOW_FAR_DEPTH = 0,			// �[�x
		RENDER_PASS_DEPTH_SHADOW_FAR_MAX				// �ő�l
	};

	// �e�p�[�x(�_0)
	enum
	{
		RENDER_PASS_DEPTH_SHADOW_POINT_0_DEPTH = 0,		// �[�x
		RENDER_PASS_DEPTH_SHADOW_POINT_0_MAX			// �ő�l
	};

	// �e�p�[�x(�_1)
	enum
	{
		RENDER_PASS_DEPTH_SHADOW_POINT_1_DEPTH = 0,		// �[�x
		RENDER_PASS_DEPTH_SHADOW_POINT_1_MAX			// �ő�l
	};

	// �e
	enum
	{
		RENDER_PASS_SHADOW_COLOR = 0,					// �F
		RENDER_PASS_SHADOW_MAX							// �ő�l
	};

	// �e�p�u���[
	enum
	{
		RENDER_PASS_BLUR_SHADOW_COLOR = 0,				// �F
		RENDER_PASS_BLUR_SHADOW_MAX						// �ő�l
	};

	// ����
	enum
	{
		RENDER_PASS_REFLECT_DIFFUSE = 0,				// �f�B�t���[�Y�F
		RENDER_PASS_REFLECT_SPECULAR,					// �X�y�L�����F
		RENDER_PASS_REFLECT_NORMAL,						// �@��
		RENDER_PASS_REFLECT_DEPTH,						// �[�x
		RENDER_PASS_REFLECT_MAX							// �ő�l
	};

	// ���˂̃��C�e�B���O
	enum
	{
		RENDER_PASS_LIGHT_REFLECT_COLOR = 0,			// �F
		RENDER_PASS_LIGHT_REFLECT_MAX					// �ő�l
	};

	// ���˃��C�e�B���O�Ȃ�
	enum
	{
		RENDER_PASS_REFLECT_NOT_LIGHT_COLOR = 0,		// �F
		RENDER_PASS_REFLECT_NOT_LIGHT_ADD,				// ���Z����
		RENDER_PASS_REFLECT_NOT_LIGHT_MAX				// �ő�l
	};

	// ��
	enum
	{
		RENDER_PASS_WATER_DIFFUSE = 0,					// �f�B�t���[�Y�F
		RENDER_PASS_WATER_SPECULAR,						// �X�y�L�����F
		RENDER_PASS_WATER_NORMAL,						// �@��
		RENDER_PASS_WATER_DEPTH,						// �[�x
		RENDER_PASS_WATER_MAX							// �ő�l
	};

	// ���C�e�B���O�Ȃ�3D�`��
	enum
	{
		RENDER_PASS_3D_NOT_LIGHT_COLOR = 0,				// �F
		RENDER_PASS_3D_NOT_LIGHT_MASK,					// �}�X�N
		RENDER_PASS_3D_NOT_LIGHT_ADD,					// ���Z����
		RENDER_PASS_3D_NOT_LIGHT_MAX					// �ő�l
	};

	// ���C�e�B���O
	enum
	{
		RENDER_PASS_LIGHT_EFFECT_COLOR = 0,				// �F
		RENDER_PASS_LIGHT_EFFECT_DEPTH,					// �[�x
		RENDER_PASS_LIGHT_EFFECT_MAX					// �ő�l
	};

	// ����3D�`��
	enum
	{
		RENDER_PASS_3D_MERGE_COLOR = 0,					// �F
		RENDER_PASS_3D_MERGE_DEPTH,						// �[�x
		RENDER_PASS_3D_MERGE_MAX						// �ő�l
	};

	// X�����u���[
	enum
	{
		RENDER_PASS_BLUR_X_COLOR = 0,					// �F
		RENDER_PASS_BLUR_X_MAX							// �ő�l
	};

	// Y�����u���[
	enum
	{
		RENDER_PASS_BLUR_Y_COLOR = 0,					// �F
		RENDER_PASS_BLUR_Y_LUMINANCE,					// �P�x
		RENDER_PASS_BLUR_Y_MAX							// �ő�l
	};

	// 2D�`��
	enum
	{
		RENDER_PASS_2D_COLOR = 0,						// �F
		RENDER_PASS_2D_MASK,							// �}�X�N
		RENDER_PASS_2D_MAX								// �ő�l
	};

	// ��ʕ`��
	enum
	{
		RENDER_PASS_POST_EFFECT_COLOR = 0,				// �F
		RENDER_PASS_POST_EFFECT_MAX						// �ő�l
	};

	// �f�B���N�V���i�����C�g
	enum
	{
		LIGHT_DIRECTIONAL_GENERAL = 0,		// �ʏ탉�C�g
		LIGHT_DIRECTIONAL_MAX				// �ő�l
	};

	// �|�C���g���C�g
	enum
	{
		LIGHT_POINT_MAX = 16				// �ő�l
	};

	// �J����
	enum
	{
		CAMERA_GENERAL = 0,					// �ʏ�J����
		CAMERA_SHADOW_NEAR,					// �e�p�J������
		CAMERA_SHADOW_FAR,					// �e�p�J������
		CAMERA_SHADOW_POINT_0,				// �e�p�J�����_0
		CAMERA_SHADOW_POINT_1,				// �e�p�J�����_1
		CAMERA_MAX							// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicMain( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicMain( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	//==============================================================================
	int Initialize( int priority );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	//==============================================================================
	int Reinitialize( int priority );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicMain* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicMain* pOut ) const;
	
	//==============================================================================
	// Brief  : 2D�|���S���N���X�̐ݒ�
	// Return : void								: �Ȃ�
	// Arg    : Polygon2D* pValue					: �ݒ肷��l
	//==============================================================================
	static void SetPolygon2D( Polygon2D* pValue );

	//==============================================================================
	// Brief  : 3D�|���S���N���X�̐ݒ�
	// Return : void								: �Ȃ�
	// Arg    : Polygon3D* pValue					: �ݒ肷��l
	//==============================================================================
	static void SetPolygon3D( Polygon3D* pValue );
	
	//==============================================================================
	// Brief  : �r���{�[�h�|���S���N���X�̐ݒ�
	// Return : void								: �Ȃ�
	// Arg    : PolygonBillboard* pValue			: �ݒ肷��l
	//==============================================================================
	static void SetPolygonBillboard( PolygonBillboard* pValue );

	static const int	MAXIMUM_LIGHT_POINT_SHADOW = 2;		// �e�𗎂Ƃ��_�����ő吔

protected:
	static Polygon2D*			pPolygon2D_;			// 2D�|���S��
	static Polygon3D*			pPolygon3D_;			// 3D�|���S��
	static PolygonBillboard*	pPolygonBillboard_;		// �r���{�[�h�|���S��

private:
	void InitializeSelf( void );
	GraphicMain( const GraphicMain& );
	GraphicMain operator=( const GraphicMain& );
};

#endif	// MY_GRAPHIC_MAIN_H
