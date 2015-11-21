//==============================================================================
//
// File   : GraphicWaveData.h
// Brief  : �g���`�揈���̊Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GRAPHIC_WAVE_DATA_H
#define MY_GRAPHIC_WAVE_DATA_H

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

//******************************************************************************
// �N���X��`
//******************************************************************************
class GraphicWaveData : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	GraphicWaveData( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~GraphicWaveData( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffect						: �G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureHeight0	: �����e�N�X�`��0
	// Arg    : IDirect3DTexture9* pTextureHeight1	: �����e�N�X�`��1
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffect,
		IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 );

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
	// Arg    : Effect* pEffect						: �G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTextureHeight0	: �����e�N�X�`��0
	// Arg    : IDirect3DTexture9* pTextureHeight1	: �����e�N�X�`��1
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffect,
		IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : GraphicWaveData* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( GraphicWaveData* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicWaveData( const GraphicWaveData& );
	GraphicWaveData operator=( const GraphicWaveData& );

};

#endif	// MY_GRAPHIC_WAVE_DATA_H
