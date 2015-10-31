//==============================================================================
//
// File   : ManagerMain.h
// Brief  : ���C���v���O�����Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_MANAGER_MAIN_H
#define MY_MANAGER_MAIN_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../framework/system/Manager.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class DirectDevice;
class DirectInput;
class Effect;
class EffectParameter;
class Fade;
class Graphic;
class CWiiController;
class InputKeyboard;
class InputMouse;
class InputPad;
class VirtualController;
class ManagerSceneMain;
class Model;
class Motion;
class Object;
class ObjectScreen;
class Polygon2D;
class Polygon3D;
class RenderPass;
class SceneArgumentMain;
class Sound;
class Texture;
class XAudio;
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
class ManagerMain : public Manager
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ManagerMain( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ManagerMain( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : HINSTANCE instanceHandle			: �C���X�^���X�n���h��
	// Arg    : int typeShow						: �\���̎��
	//==============================================================================
	int Initialize( HINSTANCE instanceHandle, int typeShow );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : HINSTANCE instanceHandle			: �C���X�^���X�n���h��
	// Arg    : int typeShow						: �\���̎��
	//==============================================================================
	int Reinitialize( HINSTANCE instanceHandle, int typeShow );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : ManagerMain* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( ManagerMain* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : �`�揈��
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Draw( void );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================

protected:

private:
	void InitializeSelf( void );
	ManagerMain( const ManagerMain& );
	ManagerMain operator=( const ManagerMain& );

	ManagerSceneMain*			pScene_;				// �V�[���Ǘ��N���X
	SceneArgumentMain*			pArgument_;				// �V�[������
	DirectDevice*				pDevice_;				// Direct3D�f�o�C�X
	XAudio*						pXAudio_;				// XAudio2�C���^�[�t�F�[�X
	Fade*						pFade_;					// �t�F�[�h
	EffectParameter*			pEffectParameter_;		// �G�t�F�N�g�p�����[�^
	ObjectScreen*				pObjectScreen_;			// ��ʃI�u�W�F�N�g
	ManagerDraw< Graphic >*		pDraw_;					// �`��Ǘ��N���X
	ManagerUpdate< Object >*	pUpdate_;				// �X�V�Ǘ��N���X
	RenderPass*					pRenderPass_;			// �p�X���
	DirectInput*				pDirectInput_;			// DirectInput�I�u�W�F�N�g
	CWiiController*				pWiiController_;		// wii�����R�����̓N���X
	InputKeyboard*				pKeyboard_;				// �L�[�{�[�h���̓N���X
	InputMouse*					pMouse_;				// �}�E�X���̓N���X
	InputPad*					pPad_;					// �Q�[���p�b�h���̓N���X
	VirtualController*			pVirtualController_;	// ���z�R���g���[���Ǘ��N���X
	ManagerTexture< Texture >*	pTexture_;				// �e�N�X�`���Ǘ��N���X
	ManagerModel< Model >*		pModel_;				// ���f���Ǘ��N���X
	ManagerMotion< Motion >*		pMotion_;			// ���[�V�����Ǘ��N���X
	ManagerEffect< Effect >*	pEffect_;				// �G�t�F�N�g�Ǘ��N���X
	ManagerSound< Sound >*		pSound_;				// �T�E���h�Ǘ��N���X
	Polygon2D*					pPolygon2D_;			// 2D�|���S��
	Polygon3D*					pPolygon3D_;			// 3D�|���S��
};

#endif	// MY_MANAGER_MAIN_H
