//==============================================================================
//
// File   : Model.h
// Brief  : ���f���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_MODEL_H
#define MY_MODEL_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "d3dx9.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Material;
class Vertex;

//******************************************************************************
// �N���X��`
//******************************************************************************
class Model
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	Model( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual ~Model( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : unsigned int elementVertex			: ���_�̗v�f
	// Arg    : unsigned int countMaterial			: �}�e���A����
	// Arg    : unsigned int countTexture			: �e�N�X�`����
	//==============================================================================
	virtual int Initialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	virtual int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : unsigned int elementVertex			: ���_�̗v�f
	// Arg    : unsigned int countMaterial			: �}�e���A����
	// Arg    : unsigned int countTexture			: �e�N�X�`����
	//==============================================================================
	virtual int Reinitialize( IDirect3DDevice9* pDevice, unsigned int elementVertex, unsigned int countMaterial, unsigned int countTexture );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : Model* pOut							: �R�s�[��A�h���X
	//==============================================================================
	virtual int Copy( Model* pOut ) const;

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : int indexMaterial					: �`��}�e���A���ԍ�
	//==============================================================================
	virtual void Draw( int indexMaterial );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetCountMaterial( unsigned int value );
	unsigned int GetCountMaterial( void ) const;
	void SetMaterial( int index, const Material& value );
	virtual void GetMaterial( int index, Material* pOut ) const;
	void SetCountTexture( unsigned int value );
	unsigned int GetCountTexture( void ) const;
	void SetTexture( int index, IDirect3DTexture9* pValue );
	virtual IDirect3DTexture9* GetTexture( int index ) const;
	virtual unsigned long GetCountBone( void ) const;

protected:
	IDirect3DDevice9*	pDevice_;			// Direct3D�f�o�C�X
	Vertex*				pVertex_;			// ���_���
	unsigned int		countMaterial_;		// �}�e���A����
	Material*			pMaterial_;			// �}�e���A��
	unsigned int		countTexture_;		// �e�N�X�`����
	IDirect3DTexture9**	ppTexture_;			// �e�N�X�`��

private:
	virtual void InitializeSelf( void );
	Model( const Model& );
	Model operator=( const Model& );
};

#endif	// MY_MODEL_H
