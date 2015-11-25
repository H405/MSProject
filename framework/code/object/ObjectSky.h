//==============================================================================
//
// File   : ObjectSky.h
// Brief  : ��I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_SKY_H
#define MY_OBJECT_SKY_H

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
class GraphicSky;
class Material;
class PolygonMeshDomeInside;
class Texture;

//******************************************************************************
// �N���X��`
//******************************************************************************
class ObjectSky : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ObjectSky( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ObjectSky( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : int countCellX						: X�����Z����
	// Arg    : int countCellY						: Z�����Z����
	// Arg    : float radius						: ���a
	// Arg    : float lengthTextureX				: X�����e�N�X�`������
	// Arg    : float lengthTextureY				: Z�����e�N�X�`������
	//==============================================================================
	int Initialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellY, float radius, float lengthTextureX, float lengthTextureY );

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
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : int countCellX						: X�����Z����
	// Arg    : int countCellY						: Z�����Z����
	// Arg    : float radius						: ���a
	// Arg    : float lengthTextureX				: X�����e�N�X�`������
	// Arg    : float lengthTextureY				: Z�����e�N�X�`������
	//==============================================================================
	int Reinitialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellY, float radius, float lengthTextureX, float lengthTextureY );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : ObjectSky* pOut						: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ObjectSky* pOut ) const;

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
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
	// Arg    : Texture* pTexture					: �e�N�X�`��
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Effect* pEffectReflect, Texture* pTexture );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetGraphic( GraphicSky* pValue );
	GraphicSky* GetGraphic( void ) const;

protected:

private:
	void InitializeSelf( void );
	ObjectSky( const ObjectSky& );
	ObjectSky operator=( const ObjectSky& );

	GraphicSky*				pGraphic_;			// �`��N���X
	PolygonMeshDomeInside*	pPolygonMesh_;		// �������b�V���h�[���|���S��
};

#endif	// MY_OBJECT_SKY_H
