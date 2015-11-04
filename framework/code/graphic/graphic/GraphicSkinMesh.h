//==============================================================================
//
// File   : GraphicSkinMesh.h
// Brief  : �X�L�����b�V���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_SKIN_MESH_H
#define MY_GRAPHIC_SKIN_MESH_H

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
class Model;

//******************************************************************************
// �N���X��`
//******************************************************************************
class GraphicSkinMesh : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicSkinMesh( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicSkinMesh( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : Model* pModel						: ���f��
	// Arg    : int countBone						: �{�[����
	// Arg    : D3DXMATRIX* pMatrixBone				: �{�[���ϊ��s��Q�ƃA�h���X
	// Arg    : int* pIndexFrame					: �t���[���ԍ��Q�ƃA�h���X
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame );

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
	// Arg    : Model* pModel						: ���f��
	// Arg    : int countBone						: �{�[����
	// Arg    : D3DXMATRIX* pMatrixBone				: �{�[���ϊ��s��Q�ƃA�h���X
	// Arg    : int* pIndexFrame					: �t���[���ԍ��Q�ƃA�h���X
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicSkinMesh* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicSkinMesh* pOut ) const;

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetGraphic( GraphicSkinMesh* pValue );
	GraphicSkinMesh* GetGraphic( void ) const;

protected:
	GraphicSkinMesh*	pGraphic_;		// �`��N���X

private:
	void InitializeSelf( void );
	GraphicSkinMesh( const GraphicSkinMesh& );
	GraphicSkinMesh operator=( const GraphicSkinMesh& );

};

#endif	// MY_GRAPHIC_SKIN_MESH_H
