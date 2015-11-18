//==============================================================================
//
// File   : RenderPass.h
// Brief  : �p�X�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_RENDER_PASS_H
#define MY_RENDER_PASS_H

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
class RenderTarget;
class RenderPassParameter;

//******************************************************************************
// �N���X��`
//******************************************************************************
class RenderPass
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	RenderPass( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~RenderPass( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : int countRenderTarget				: �����_�[�^�[�Q�b�g�̐�
	// Arg    : const RenderPassParameter* pParameter	: �`��Ώۃp�����[�^
	//==============================================================================
	int Initialize( IDirect3DDevice9* pDevice, int countRenderTarget, const RenderPassParameter* pParameter = nullptr );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : int countRenderTarget				: �����_�[�^�[�Q�b�g�̐�
	// Arg    : const RenderPassParameter* pParameter	: �`��Ώۃp�����[�^
	//==============================================================================
	int Reinitialize( IDirect3DDevice9* pDevice, int countRenderTarget, const RenderPassParameter* pParameter = nullptr );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : RenderPass* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( RenderPass* pOut ) const;

	//==============================================================================
	// Brief  : �`��Ώۂɐݒ�
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Set();

	//==============================================================================
	// Brief  : �e�N�X�`���̎擾
	// Return : IDirect3DTexture9*					: �ԋp����l
	// Arg    : int index							: �����_�[�^�[�Q�b�g�̔ԍ�
	// Arg    : int indexMultiple					: ���ԕ`��ԍ�
	//==============================================================================
	IDirect3DTexture9* GetTexture( int index, int indexMultiple = 0 ) const;

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	int GetCountRenderTarget( void ) const;
	IDirect3DSurface9* GetSurfaceDepth( void ) const;
	unsigned int GetWidth( void ) const;
	unsigned int GetHeight( void ) const;
	void SetFlagClear( const DWORD& value );
	DWORD GetFlagClear( void ) const;
	void SetClearTarget( const D3DCOLOR& value );
	D3DCOLOR GetClearTarget( void ) const;
	void SetClearZBuffer( float value );
	float GetClearZBuffer( void ) const;
	void SetClearStencil( const DWORD& value );
	DWORD GetClearStencil( void ) const;

protected:

private:
	void InitializeSelf( void );
	RenderPass( const RenderPass& );
	RenderPass operator=( const RenderPass& );

	IDirect3DDevice9*	pDevice_;				// Direct3D�f�o�C�X
	int					countRenderTarget_;		// �����_�[�^�[�Q�b�g��
	RenderTarget**		ppRenderTarget_;		// �����_�[�^�[�Q�b�g
	IDirect3DSurface9*	pSurfaceDepth_;			// �[�x�o�b�t�@
	unsigned int		width_;					// ��
	unsigned int		height_;				// ����
	DWORD				flagClear_;				// �N���A�t���O
	D3DCOLOR			clearTarget_;			// �����_�[�^�[�Q�b�g�̃N���A�l
	float				clearZBuffer_;			// Z�o�b�t�@�̃N���A�l
	DWORD				clearStencil_;			// �X�e���V���o�b�t�@�̃N���A�l
	bool				needsReleaseDepth_;		// �[�x�o�b�t�@���J������K�v�����邩
};

#endif	// MY_RENDER_PASS_H
