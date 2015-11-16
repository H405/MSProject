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
class CWiiController;
class Effect;
class EffectParameter;
class Fade;
class Graphic;
class InputKeyboard;
class InputMouse;
class InputPad;
class ManagerLight;
class Model;
class Motion;
class Object;
class Sound;
class Texture;
class VirtualController;
class Window;

template < class Graphic > class ManagerDraw;
template < class Effect > class ManagerEffect;
template < class Model > class ManagerModel;
template < class Motion > class ManagerMotion;
template < class Sound > class ManagerSound;
template < class Texture > class ManagerTexture;
template < class Object > class ManagerUpdate;

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

	Window*						pWindow_;				// �E�B���h�E
	IDirect3DDevice9*			pDevice_;				// Direct3D�f�o�C�X
	Fade*						pFade_;					// �t�F�[�h�Ǘ��N���X
	ManagerLight*				pLight_;				// ���C�g�Ǘ��N���X
	EffectParameter*			pEffectParameter_;		// �G�t�F�N�g�p�����[�^
	CWiiController*				pWiiController_;		// wii�����R�����̓N���X
	InputKeyboard*				pKeyboard_;				// �L�[�{�[�h���̓N���X
	InputMouse*					pMouse_;				// �}�E�X���̓N���X
	InputPad*					pPad_;					// �Q�[���p�b�h���̓N���X
	VirtualController*			pVirtualController_;	// ���z�R���g���[���Ǘ��N���X
	ManagerTexture< Texture >*	pTexture_;				// �e�N�X�`���Ǘ��N���X
	ManagerModel< Model >*		pModel_;				// ���f���Ǘ��N���X
	ManagerMotion< Motion >*	pMotion_;				// ���[�V�����Ǘ��N���X
	ManagerEffect< Effect >*	pEffect_;				// �G�t�F�N�g�Ǘ��N���X
	ManagerSound< Sound >*		pSound_;				// �T�E���h�Ǘ��N���X

	ManagerDraw< Graphic >*		pDraw_;					// �`��Ǘ��N���X
	ManagerUpdate< Object >*	pUpdate_;				// �X�V�Ǘ��N���X

protected:

private:
	void InitializeSelf( void );

};

#endif	// MY_SCENE_ARGUMENT_MAIN_H
