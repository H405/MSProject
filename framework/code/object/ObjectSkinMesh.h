//==============================================================================
//
// File   : ObjectSkinMesh.h
// Brief  : �X�L�����b�V���I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_SKIN_MESH_H
#define MY_OBJECT_SKIN_MESH_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../framework/object/ObjectMovement.h"

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
class GraphicSkinMesh;
class Model;
class Motion;

//******************************************************************************
// �N���X��`
//******************************************************************************
class ObjectSkinMesh : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ObjectSkinMesh( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ObjectSkinMesh( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	// Arg    : int countMotion						: ���[�V������
	//==============================================================================
	int Initialize( int priority, int countMotion );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	// Arg    : int countMotion						: ���[�V������
	//==============================================================================
	int Reinitialize( int priority, int countMotion );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : ObjectSkinMesh* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ObjectSkinMesh* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : �`��N���X�̐���
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : Model* pModel						: ���f��
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
	//==============================================================================
	int CreateGraphic( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral, Effect* pEffectReflect );

	//==============================================================================
	// Brief  : ���̃��[�V������ݒ�
	// Return : void								: �Ȃ�
	// Arg    : int indexMotion						: ���̃��[�V�����ԍ�
	// Arg    : int timeBeginBlend					: �u�����h�J�n����
	// Arg    : int timeBlend						: �u�����h����
	//==============================================================================
	void SetNextMotion( int indexMotion, int timeBeginBlend, int timeBlend );

	//==============================================================================
	// Brief  : �u�����h��������
	// Return : bool								: �u�����h�����ǂ���
	// Arg    : void								: �Ȃ�
	//==============================================================================
	bool IsBlending( void );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetGraphic( GraphicSkinMesh* pValue );
	GraphicSkinMesh* GetGraphic( void ) const;
	void SetTableMotion( int index, Motion* pValue );
	Motion* GetTableMotion( int index ) const;
	void SetMatrixBoneCurrent( int index, const D3DXMATRIX& value );
	void GetMatrixBoneCurrent( int index, D3DXMATRIX* pOut ) const;
	int GetIndexMotionCurrent( void ) const;
	int GetIndexMotionNext( void ) const;
	int GetIndexFrame( void ) const;

protected:
	GraphicSkinMesh*	pGraphic_;		// �`��N���X

private:
	void InitializeSelf( void );
	ObjectSkinMesh( const ObjectSkinMesh& );
	ObjectSkinMesh operator=( const ObjectSkinMesh& );

	Model*		pModel_;					// ���f��
	Motion**	ppTableMotion_;				// ���[�V�����e�[�u��
	D3DXMATRIX*	pMatrixBoneCurrent_;		// ���݂̃{�[���ϊ��s��
	int			countMotion_;				// ���[�V������
	int			indexMotionCurrent_;		// ���݂̃��[�V�����ԍ�
	int			indexMotionNext_;			// ���̃��[�V�����ԍ�
	int			indexFrame_;				// �t���[���ԍ�
	int			indexFrameBeginBlend_;		// �u�����h�J�n�t���[���ԍ�
	int			countFrameBlend_;			// �u�����h����t���[����
};

#endif	// MY_OBJECT_SKIN_MESH_H
