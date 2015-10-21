//==============================================================================
//
// File   : ObjectMesh.h
// Brief  : ���b�V���|���S���I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_MESH_H
#define MY_OBJECT_MESH_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../framework/object/ObjectMovement.h"
#include "../framework/graphic/Material.h"

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
class GraphicMesh;
class PolygonMesh;
class Texture;

//******************************************************************************
// �N���X��`
//******************************************************************************
class ObjectMesh : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ObjectMesh( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ObjectMesh( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : int countCellX						: X�����Z����
	// Arg    : int countCellZ						: Z�����Z����
	// Arg    : float lengthCellX					: X�����Z������
	// Arg    : float lengthCellZ					: Z�����Z������
	// Arg    : float lengthTextureX				: X�����e�N�X�`������
	// Arg    : float lengthTextureZ				: Z�����e�N�X�`������
	//==============================================================================
	int Initialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
		float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ );

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
	// Arg    : int countCellZ						: Z�����Z����
	// Arg    : float lengthCellX					: X�����Z������
	// Arg    : float lengthCellZ					: Z�����Z������
	// Arg    : float lengthTextureX				: X�����e�N�X�`������
	// Arg    : float lengthTextureZ				: Z�����e�N�X�`������
	//==============================================================================
	int Reinitialize( int priority, IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
		float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : ObjectMesh* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ObjectMesh* pOut ) const;

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
	// Arg    : Texture* pTexture					: �e�N�X�`��
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetGraphic( GraphicMesh* pValue );
	GraphicMesh* GetGraphic( void ) const;

protected:
	GraphicMesh*	pGraphic_;		// �`��N���X
	PolygonMesh*	pPolygon_;		// ���b�V���|���S��
	Material		material_;		// �}�e���A��

private:
	void InitializeSelf( void );
	ObjectMesh( const ObjectMesh& );
	ObjectMesh operator=( const ObjectMesh& );
};

#endif	// MY_OBJECT_MESH_H
