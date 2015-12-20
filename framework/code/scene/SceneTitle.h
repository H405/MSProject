//==============================================================================
//
// File   : SceneTitle.h
// Brief  : �^�C�g���V�[���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_SCENE_TITLE_H
#define MY_SCENE_TITLE_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../system/SceneMain.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************
#define FIREWORKS_MAX (16)
#define TARGET_MAX (16)

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class CameraObject;
class LightDirection;
class ManagerPoint;
class ManagerFireworks;
class Object2D;
class Object3D;
class Material;
class ObjectModel;
class ObjectModelMaterial;
class PolygonMesh;
class ObjectSky;
class ObjectSkinMesh;
class ObjectMesh;
class ObjectRiver;
class ObjectWaterwheel;
class Player;
class Sound;

//******************************************************************************
// �N���X��`
//******************************************************************************
class SceneTitle : public SceneMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	SceneTitle( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~SceneTitle( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : SceneArgumentMain* pArgument		: �V�[������
	//==============================================================================
	int Initialize( SceneArgumentMain* pArgument );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : SceneArgumentMain* pArgument		: �V�[������
	//==============================================================================
	int Reinitialize( SceneArgumentMain* pArgument );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : SceneTitle* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( SceneTitle* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

protected:

private:
	void InitializeSelf( void );
	SceneTitle( const SceneTitle& );
	SceneTitle operator=( const SceneTitle& );
	
	CameraObject*	pCamera_;					// �J����
	CameraObject*	pCameraShadowNear_;			// �e�p�J������
	CameraObject*	pCameraShadowFar_;			// �e�p�J������
	CameraObject**	ppCameraShadowPoint_;		// �e�p�J�����_
	LightDirection*	pLight_;					// ���C�g


	//	�^�C�g��UI�֌W
	//----------------------------------------------------------
	//	�^�C�g�����S
	Object2D* titleLogo;

	//	�uA�{�^���������Ăˁv����
	Object2D* pushAKey;

	//	�u�����J�n�v����
	Object2D* startGame;

	//	�u���K�J�n�v����
	Object2D* startTutorial;

	//	wii�����R���ő��삷��w
	Object2D* finger;

	//	�uwii�����R���Đڑ��v���v�I�u�W�F�N�g
	Object2D* reConnectWiimote;

	//	�uwii�{�[�h�Đڑ��v���v�I�u�W�F�N�g
	Object2D* reConnectWiiboard;

	//	�I�����̂����A�I�΂�Ă���I�u�W�F�N�g�̃|�C���^
	Object2D* chooseObject;
	Object2D* chooseObjectPrev;

	//	pushAKey�_�ŗp
	int pushAKeyFlashingCount;

	//	chooseObject�_�ŗp
	int pushChooseObjectFlashingCount;

	//	�I�����̑I����@�p�̃t���O
	//	true = wii�����R���iIR�j
	//	false = �����L�[	�Ƃ���
	bool chooseFlag;
	//----------------------------------------------------------


	//	�Q�[���p�X�e�[�W�E�RD�I�u�W�F�N�g�֌W
	//----------------------------------------------------------

	ObjectSky*				sky;			// ��
	ObjectRiver*			river;			// ��
	ObjectModel*			field;			// �n�`

	ObjectModelMaterial*	bridge;			// ��
	ObjectWaterwheel*		waterwheel;		// ����
	ObjectModelMaterial*	houses;			// ��
	ObjectModelMaterial*	gate;			// ����

//	ObjectSkinMesh*			markers;		// �ꏊ�̖ڈ�

	//	�v���C���[
	Player* player;

	// �|�C���g�X�v���C�g�Ǘ��N���X
	ManagerPoint* managerPoint;

	//	�ԉΊǗ��N���X
	ManagerFireworks* managerFireworks;

//	ObjectSkinMesh*		pObjectSkinMesh_[3];		// �X�L�����b�V��

	//	�ł��グ�Ɋւ���t���O�ƃJ�E���^
	bool launchFlag;
	int launchCount;

	//	�^�[�Q�b�g�Ɖԉ΂̓����蔻��p�e�[�u��
	int fireworksTable[FIREWORKS_MAX];
	int fireworksTableIndex;

	static const int	COUNT_HOUSE = 11;		// �Ƃ̐�
	//----------------------------------------------------------

	//	���֘A
	//----------------------------------------------------------
	Sound* bgmSound;
	Sound* desideSound;
	Sound* selectSound;
	Sound* cancelSound;
	//----------------------------------------------------------

	//==============================================================================
	// Brief  : �X�V����1(�uA�{�^���������Ăˁv�̓_��)
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void firstUpdate( void );

	//==============================================================================
	// Brief  : �X�V����2(�Q�[���J�n�E�`���[�g���A���J�n�̑I������)
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void secondUpdate( void );

	//==============================================================================
	// Brief  : �X�V����(����L�[�����ꂽ��̑J�ڏ���)
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void fadeUpdate( void );
	void fadeUpdateDemo( void );

	//==============================================================================
	// Brief  : �Đڑ��v�����p�̍X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void reConnectWiimoteUpdate(void);

	//==============================================================================
	// Brief  : �Đڑ��v�����p�̍X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void reConnectWiiboardUpdate(void);

	//==============================================================================
	// Brief  : wii�����R���̃��X�g�`�F�b�N����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	bool wiiLostCheck(void);

	//	�X�V�֐��i�[�p�|�C���^
	void (SceneTitle::*fpUpdate)(void);
	void (SceneTitle::*fpUpdatePrev)(void);
};

#endif	// MY_SCENE_TITLE_H
