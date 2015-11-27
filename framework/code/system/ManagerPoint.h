//==============================================================================
//
// File   : ManagerPoint.h
// Brief  : �|�C���g�X�v���C�g�̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_MANAGER_POINT_H
#define MY_MANAGER_POINT_H

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
class Effect;
class EffectParameter;
class GraphicPoint;
class Point;
class PointState;
class PolygonPoint;
class Texture;
class VertexBuffer;

//******************************************************************************
// �N���X��`
//******************************************************************************
class ManagerPoint
{
public:
	// �X�e�[�g
	enum
	{
		STATE_NONE = 0,		// �Ȃ�
		STATE_ADD,			// ���Z
		STATE_MULTIPLY,		// ��Z
		STATE_MAX			// �ő�l
	};

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ManagerPoint( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ManagerPoint( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int maximumItem						: �ő�v�f��
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Initialize( int maximumItem, IDirect3DDevice9* pDevice, const EffectParameter* pParameter,
		Effect* pEffectGeneral, Effect* pEffectReflect, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : int maximumItem						: �ő�v�f��
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Reinitialize( int maximumItem, IDirect3DDevice9* pDevice, const EffectParameter* pParameter,
		Effect* pEffectGeneral, Effect* pEffectReflect, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : ManagerPoint* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ManagerPoint* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : �|�C���g�̒ǉ�
	// Return : void								: �Ȃ�
	// Arg    : int indexState						: �X�e�[�g�ԍ�
	// Arg    : const D3DXVECTOR3& position			: ���W
	// Arg    : const D3DXCOLOR& color				: �F
	// Arg    : float size							: �傫��
	//==============================================================================
	void Add( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size );

	//==============================================================================
	// Brief  : �|�C���g�̒ǉ�
	// Return : void								: �Ȃ�
	// Arg    : int indexState						: �X�e�[�g�ԍ�
	// Arg    : const D3DXVECTOR3& position			: ���W
	// Arg    : const D3DXCOLOR& color				: �F
	// Arg    : float size							: �傫��
	//==============================================================================
	Point* AddR( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size );

	//==============================================================================
	// Brief  : �|�C���g�̒ǉ�
	// Return : void								: �Ȃ�
	// Arg    : int timeExist						: �c������
	// Arg    : const D3DXVECTOR3& position			: ���W
	// Arg    : const D3DXCOLOR& color				: �F
	// Arg    : float size							: �傫��
	// Arg    : const D3DXVECTOR3& differencePosition	: ���W�̕ω���
	// Arg    : const D3DXCOLOR& differenceColor	: �F�̕ω���
	// Arg    : float differenceSize				: �傫���̕ω���
	// Arg    : int indexState						: �X�e�[�g�ԍ�
	//==============================================================================
	void Add( int timeExist, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size,
		const D3DXVECTOR3& differencePosition, const D3DXCOLOR& differenceColor, float differenceSize,
		int indexState = STATE_ADD );

protected:

private:
	ManagerPoint( const ManagerPoint& );
	ManagerPoint operator=( const ManagerPoint& );

	void InitializeSelf( void );
	int GetIndex( void );

	PointState*		ppState_[ STATE_MAX ];		// �X�e�[�g�e�[�u��
	int				maximumItem_;				// �ő�v�f��
	int				indexCurrent_;				// ���݂̗v�f�ԍ�
	Point*			pPoint_;					// �|�C���g���
	PolygonPoint*	pPolygon_;					// �|���S��
	GraphicPoint*	pGraphic_;					// �`��N���X
	VertexBuffer*	pVertexBuffer_;				// ���_�o�b�t�@
};

#endif	// MY_MANAGER_POINT_H
