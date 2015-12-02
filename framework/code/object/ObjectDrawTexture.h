//==============================================================================
//
// File   : ObjectDrawTexture.h
// Brief  : �f�o�b�O�e�N�X�`���`��I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/27 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_DRAW_TEXTURE_H
#define MY_OBJECT_DRAW_TEXTURE_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../framework/object/object.h"

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
class GraphicDrawTexture;
class InputKeyboard;

//******************************************************************************
// �N���X��`
//******************************************************************************
class ObjectDrawTexture : public Object
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ObjectDrawTexture( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ObjectDrawTexture( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	// Arg    : InputKeyboard* pKeyboard			: �L�[�{�[�h����
	//==============================================================================
	int Initialize( int priority, InputKeyboard* pKeyboard );

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
	// Arg    : InputKeyboard* pKeyboard			: �L�[�{�[�h����
	//==============================================================================
	int Reinitialize( int priority, InputKeyboard* pKeyboard );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : ObjectDrawTexture* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ObjectDrawTexture* pOut ) const;

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
	// Arg    : int countTexture					: �e�N�X�`����
	// Arg    : IDirect3DTexture9** ppTexture		: �e�N�X�`��
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, int countTexture, IDirect3DTexture9** ppTexture );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetGraphic( GraphicDrawTexture* pValue );
	GraphicDrawTexture* GetGraphic( void ) const;

protected:
	GraphicDrawTexture*	pGraphic_;		// �`��N���X

private:
	void InitializeSelf( void );
	ObjectDrawTexture( const ObjectDrawTexture& );
	ObjectDrawTexture operator=( const ObjectDrawTexture& );

	const EffectParameter*	pParameter_;			// �G�t�F�N�g�̃p�����[�^
	int						countTexture_;			// �e�N�X�`����
	int						indexTexture_;			// �e�N�X�`���ԍ�
	IDirect3DTexture9**		ppTableTexture_;		// �e�N�X�`���e�[�u��
	IDirect3DTexture9*		pTextureCurrent_;		// ���݂̃e�N�X�`��
	float					pMultiply_[ 3 ];		// �F�̔{��
	InputKeyboard*			pKeyboard_;				// �L�[�{�[�h����
	bool					isEnableDraw_;			// �\���t���O
};

#endif	// MY_OBJECT_DRAW_TEXTURE_H
