//==============================================================================
//
// File   : SceneArgumentMain.h
// Brief  : �V�[���̋��ʈ���
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_SCENE_ARGUMENT_MAIN_H
#define MY_SCENE_ARGUMENT_MAIN_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "d3dx9.h"
#include "../framework/scene/SceneArgument.h"

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
class InputKeyboard;
class InputMouse;
class InputPad;
class Model;
class ObjectScreen;
class Texture;
template < class Effect > class ManagerEffect;
template < class Model > class ManagerModel;
template < class Texture > class ManagerTexture;

//******************************************************************************
// �N���X��`
//******************************************************************************
class SceneArgumentMain : public SceneArgument
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	SceneArgumentMain( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~SceneArgumentMain( void );

	IDirect3DDevice9*			pDevice_;				// Direct3D�f�o�C�X
	Fade*						pFade_;					// �t�F�[�h�Ǘ��N���X
	EffectParameter*			pEffectParameter_;		// �G�t�F�N�g�p�����[�^
	ObjectScreen*				pObjectScreen_;			// ��ʃI�u�W�F�N�g
	InputKeyboard*				pKeyboard_;				// �L�[�{�[�h���̓N���X
	InputMouse*					pMouse_;				// �}�E�X���̓N���X
	InputPad*					pPad_;					// �Q�[���p�b�h���̓N���X
	ManagerTexture< Texture >*	pTexture_;				// �e�N�X�`���Ǘ��N���X
	ManagerModel< Model >*		pModel_;				// ���f���Ǘ��N���X
	ManagerEffect< Effect >*	pEffect_;				// �G�t�F�N�g�Ǘ��N���X

protected:

private:
	void InitializeSelf( void );

};

#endif	// MY_SCENE_ARGUMENT_MAIN_H
