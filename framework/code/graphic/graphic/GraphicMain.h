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

//******************************************************************************
// �N���X��`
//******************************************************************************
class GraphicMain : public Graphic
{
public:
	// �p�X
	enum
	{
		PASS_3D = 0,			// 3D�`��
		PASS_3D_NOT_LIGHT,		// ���C�e�B���O�Ȃ�3D�`��
		PASS_LIGHT_EFFECT,		// ���C�e�B���O
		PASS_3D_MERGE,			// ����3D�`��
		PASS_BLUR_X,			// X�����u���[
		PASS_BLUR_Y,			// Y�����u���[
		PASS_2D,				// 2D�`��
		PASS_POST_EFFECT,		// �|�X�g�G�t�F�N�g
		PASS_MAX				// �ő吔
	};

	// 3D�`��
	enum
	{
		RENDER_PASS_3D_DIFFUSE = 0,				// �f�B�t���[�Y�F
		RENDER_PASS_3D_SPECULAR,				// �X�y�L�����F
		RENDER_PASS_3D_NORMAL,					// �@��
		RENDER_PASS_3D_DEPTH,					// �[�x
		RENDER_PASS_3D_MAX						// �ő�l
	};

	// ���C�e�B���O�Ȃ�3D�`��
	enum
	{
		RENDER_PASS_3D_NOT_LIGHT_COLOR = 0,		// �F
		RENDER_PASS_3D_NOT_LIGHT_MASK,			// �}�X�N
		RENDER_PASS_3D_NOT_LIGHT_ADD,			// ���Z����
		RENDER_PASS_3D_NOT_LIGHT_MAX			// �ő�l
	};

	// ���C�e�B���O
	enum
	{
		RENDER_PASS_LIGHT_EFFECT_COLOR = 0,		// �F
		RENDER_PASS_LIGHT_EFFECT_MAX			// �ő�l
	};

	// ����3D�`��
	enum
	{
		RENDER_PASS_3D_MERGE_COLOR = 0,			// �F
		RENDER_PASS_3D_MERGE_MAX				// �ő�l
	};

	// X�����u���[
	enum
	{
		RENDER_PASS_BLUR_X_COLOR = 0,			// �F
		RENDER_PASS_BLUR_X_MAX					// �ő�l
	};

	// Y�����u���[
	enum
	{
		RENDER_PASS_BLUR_Y_COLOR = 0,			// �F
		RENDER_PASS_BLUR_Y_LUMINANCE,			// �P�x
		RENDER_PASS_BLUR_Y_MAX					// �ő�l
	};

	// 2D�`��
	enum
	{
		RENDER_PASS_2D_COLOR = 0,				// �F
		RENDER_PASS_2D_MASK,					// �}�X�N
		RENDER_PASS_2D_MAX						// �ő�l
	};

	// ��ʕ`��
	enum
	{
		RENDER_PASS_POST_EFFECT_COLOR = 0,		// �F
		RENDER_PASS_POST_EFFECT_MAX				// �ő�l
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
		LIGHT_POINT_MAX = 10		// �ő�l
	};

	// �J����
	enum
	{
		CAMERA_GENERAL = 0,		// �ʏ�J����
		CAMERA_MAX				// �ő�l
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

protected:
	static Polygon2D*	pPolygon2D_;		// 2D�|���S��
	static Polygon3D*	pPolygon3D_;		// 3D�|���S��

private:
	void InitializeSelf( void );
	GraphicMain( const GraphicMain& );
	GraphicMain operator=( const GraphicMain& );
};

#endif	// MY_GRAPHIC_MAIN_H
