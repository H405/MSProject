//==============================================================================
//
// File   : ObjectPostEffect.h
// Brief  : ��ʃ|���S���I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_POST_EFFECT_H
#define MY_OBJECT_POST_EFFECT_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../framework/object/Object.h"

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
class Fade;
class GraphicPostEffect;
class Texture;

//******************************************************************************
// �N���X��`
//******************************************************************************
class ObjectPostEffect : public Object
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ObjectPostEffect( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ObjectPostEffect( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	// Arg    : Fade* pFade							: �t�F�[�h
	//==============================================================================
	int Initialize( int priority, Fade* pFade );

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
	// Arg    : Fade* pFade							: �t�F�[�h
	//==============================================================================
	int Reinitialize( int priority, Fade* pFade );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : ObjectPostEffect* pOut				: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ObjectPostEffect* pOut ) const;

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
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTexture2D		: 2D�`��e�N�X�`��
	// Arg    : IDirect3DTexture9* pTextureMask		: �}�X�N�e�N�X�`��
	// Arg    : Texture* pTexture					: �e�N�X�`��
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, Texture* pTexture = nullptr );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetGraphic( GraphicPostEffect* pValue );
	GraphicPostEffect* GetGraphic( void ) const;

protected:
	GraphicPostEffect*	pGraphic_;		// �`��N���X

private:
	void InitializeSelf( void );
	ObjectPostEffect( const ObjectPostEffect& );
	ObjectPostEffect operator=( const ObjectPostEffect& );

	Fade*	pFade_;					// �t�F�[�h
	float	proportionFade_;		// �t�F�[�h����
};

#endif	// MY_OBJECT_POST_EFFECT_H