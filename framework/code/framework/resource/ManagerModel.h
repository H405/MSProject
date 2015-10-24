//==============================================================================
//
// File   : ManagerModel.h
// Brief  : ���f���Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_MANAGER_MODEL_H
#define MY_MANAGER_MODEL_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "d3dx9.h"
#include "ManagerResource.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Model;
class Texture;
template < class Texture > class ManagerTexture;

//******************************************************************************
// �N���X��`
//******************************************************************************
template< class TypeItem >
class ManagerModel : public ManagerResource< TypeItem >
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ManagerModel( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ManagerModel( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : TCHAR* pDirectory					: ��f�B���N�g��
	// Arg    : TCHAR* pDirectoryTexture			: �e�N�X�`����f�B���N�g��
	// Arg    : int maximumItem						: �ő�v�f��
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : ManagerTexture< Texture >* pTexture	: �e�N�X�`���Ǘ��N���X
	//==============================================================================
	int Initialize( TCHAR* pDirectory, TCHAR* pDirectoryTexture, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : TCHAR* pDirectory					: ��f�B���N�g��
	// Arg    : TCHAR* pDirectoryTexture			: �e�N�X�`����f�B���N�g��
	// Arg    : int maximumItem						: �ő�v�f��
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : ManagerTexture< Texture >* pTexture	: �e�N�X�`���Ǘ��N���X
	//==============================================================================
	int Reinitialize( TCHAR* pDirectory, TCHAR* pDirectoryTexture, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : ManagerModel* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ManagerModel* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	ManagerModel( const ManagerModel& );
	ManagerModel operator=( const ManagerModel& );

	int LoadResource( TCHAR* pPath, int index );
	void ReleaseResource( int index );

	IDirect3DDevice9*			pDevice_;				// Direct3D�f�o�C�X
	ManagerTexture< Texture >*	pTexture_;				// �e�N�X�`���Ǘ��N���X
	TCHAR*						pDirectoryTexture_;		// �e�N�X�`����f�B���N�g��
};

#endif	// MY_MANAGER_MODEL_H
