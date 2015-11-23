//==============================================================================
//
// File   : GraphicPoint.h
// Brief  : �|�C���g�X�v���C�g�`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_POINT_H
#define MY_GRAPHIC_POINT_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "GraphicMain.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Effect;
class EffectParameter;
class PolygonPoint;

//******************************************************************************
// �N���X��`
//******************************************************************************
class GraphicPoint : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicPoint( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicPoint( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
	// Arg    : PolygonPoint* pPolygon				: �|�C���g�X�v���C�g�|���S��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter,
		Effect* pEffectGeneral, Effect* pEffectReflect, PolygonPoint* pPolygon, IDirect3DTexture9* pTexture );

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
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
	// Arg    : PolygonPoint* pPolygon				: �|�C���g�X�v���C�g�|���S��
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter,
		Effect* pEffectGeneral, Effect* pEffectReflect, PolygonPoint* pPolygon, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicPoint* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicPoint* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicPoint( const GraphicPoint& );
	GraphicPoint operator=( const GraphicPoint& );

};

#endif	// MY_GRAPHIC_POINT_H
