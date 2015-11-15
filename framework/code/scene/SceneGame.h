//==============================================================================
//
// File   : SceneGame.h
// Brief  : �Q�[���V�[���N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_SCENE_GAME_H
#define MY_SCENE_GAME_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../system/SceneMain.h"
#include "d3dx9.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************
#define FIREWORKS_MAX (16)
#define TARGET_MAX (16)

//******************************************************************************
// �񋓑�
//******************************************************************************
typedef enum
{
	CAMERA_STATE_FRONT = 0,
	CAMERA_STATE_LEFT,
	CAMERA_STATE_BACK,
	CAMERA_STATE_RIGHT,
	CAMERA_STATE_MAX
}CAMERA_STATE;

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class CameraObject;
class CameraStateSpline;
class LightDirection;
class ManagerPoint;
class ManagerFireworks;
class ManagerTarget;
class Object2D;
class ObjectScore;
class Object3D;
class Material;
class ObjectModel;
class ObjectModelMaterial;
class PolygonMesh;
class ObjectMesh;
class ObjectSky;
class ObjectBillboard;
class ObjectSkinMesh;
class ObjectWaterwheel;

class GraphicPoint;
class PolygonPoint;

//******************************************************************************
// �N���X��`
//******************************************************************************
class SceneGame : public SceneMain
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	SceneGame( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~SceneGame( void );

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
	// Arg    : SceneGame* pOut						: �R�s�[��A�h���X
	//==============================================================================
	int Copy( SceneGame* pOut ) const;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

protected:

private:
	void InitializeSelf( void );
	SceneGame( const SceneGame& );
	SceneGame operator=( const SceneGame& );

	CameraObject*		pCamera_;		// �J����
	LightDirection*		pLight_;		// ���C�g
	ObjectSky*			pObjectSky_;	// �X�J�C�h�[��

	//	���ԃI�u�W�F�N�g
	ObjectWaterwheel* waterWheel[3];

	//	��
	ObjectModelMaterial* house[3];

	//	��
	ObjectModelMaterial* bridge;

	//	�t�B�[���h
	ObjectModel* field;

	//	�v���C���[
	ObjectModelMaterial* player;
	ObjectModelMaterial* playerArm;

	//	�u�X�R�A�v����
	Object2D* stringScore;

	//	�X�R�A�I�u�W�F�N�g
	ObjectScore* score;

	//	�|�[�Y���p�w�i
	Object2D* pauseFrame;

	//	�|�[�Y���p�����u�ĊJ�v
	Object2D* stringReturn;

	//	�|�[�Y���p�����u���~�v
	Object2D* stringStop;

	//	�|�[�Y���p�����u���߂���v
	Object2D* stringRetry;

	//	�P�X�e�[�W�N���A�㕶���u���̃X�e�[�W�ցv
	Object2D* stringNext;

	//	�uwii�����R���Đڑ��v���v�I�u�W�F�N�g
	Object2D* reConnectWiimote;

	//	�uwii�{�[�h�Đڑ��v���v�I�u�W�F�N�g
	Object2D* reConnectWiiboard;

	//	wii�����R���ő��삷��w
	Object2D* finger;

	//	�I�����̂����A�I�΂�Ă���I�u�W�F�N�g�̃|�C���^
	Object2D* chooseObject;
	Object2D* chooseObjectPrev;

	// �|�C���g�X�v���C�g�Ǘ��N���X
	ManagerPoint* managerPoint;

	//	�ԉΊǗ��N���X
	ManagerFireworks* managerFireworks;

	//	�^�[�Q�b�g�Ǘ��N���X
	ManagerTarget* managerTarget;

	ObjectSkinMesh*		pObjectSkinMesh_[3];		// �X�L�����b�V��




	//	�ł��グ�Ɋւ���t���O�ƃJ�E���^
	bool launchFlag;
	int launchCount;

	//	�^�[�Q�b�g�Ɖԉ΂̓����蔻��p�e�[�u��
	int fireworksTable[FIREWORKS_MAX];
	int targetTable[TARGET_MAX];
	int fireworksTableIndex;
	int targetTableIndex;

	//	chooseObject�_�ŗp
	int pushChooseObjectFlashingCount;

	//	�I�����̑I����@�p�̃t���O
	//	true = wii�����R���iIR�j
	//	false = �����L�[	�Ƃ���
	bool chooseFlag;

	//	�J�����̕���
	CAMERA_STATE cameraState;

	//==============================================================================
	// Brief  : �ʏ펞�p�̍X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void normalUpdate(void);

	//==============================================================================
	// Brief  : �|�[�Y���p�̍X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void pauseUpdate(void);

	//==============================================================================
	// Brief  : �|�[�Y���p�̍X�V����(�|�[�Y���̃t�F�[�h�p)
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void pauseFadeUpdate(void);

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

	//==============================================================================
	// Brief  : �ԉ΂ƃ^�[�Q�b�g�̓����蔻�菈��
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void collision_fireworks_target();

	//==============================================================================
	// Brief  : �X�e�[�W�֘A�̓ǂݍ��ݏ���
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void InitializeStage(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : ���̑��RD�I�u�W�F�N�g�̓ǂݍ��ݏ���
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Initialize3DObject(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : UI�֘A�̓ǂݍ��ݏ���
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void InitializeUI(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : �_�Ɖ~�̓����蔻�菈��
	// Return : bool								: �����������������ĂȂ���
	// Arg    : D3DXVECTOR3							: �_�̈ʒu
	// Arg    : D3DXVECTOR3							: �~�̈ʒu
	// Arg    : D3DXVECTOR3							: �������Ă�Ɣ��肷��ő勗��
	// Arg    : float								: �~�̒��S����_�ւ̋���
	//==============================================================================
	bool hitCheckPointCircle(D3DXVECTOR3 _pointPos, D3DXVECTOR3 _circlePos, float _hitCheckOffset, float* _hitPosLength);

	//==============================================================================
	// ������ǉ�
	//==============================================================================
	CameraStateSpline*	pStateCameraPrevious_;		// �Q�[���J�n�O�J��������
	CameraStateSpline*	pStateCameraResult_;		// ���U���g�O�J��������
	int					timerSceneGame_;			// �Q�[���V�[���o�ߎ���

	int Initialize2( void );
	int Finalize2( void );
	void InitializeSelf2( void );

	// �Q�[���J�n�O�X�V
	void UpdatePreviousGame( void );

	// �Q�[���J�n�O�J�E���g�_�E���X�V
	void UpdateCountDownGame( void );

	// ���U���g�ҋ@�X�V
	void UpdateWaitResult( void );

	// ���U���g�O�X�V
	void UpdatePreviousResult( void );

	// ���U���g�X�V
	void UpdateResult( void );

	//==============================================================================
	// ������ǉ�
	//==============================================================================

	//	�X�V�֐��i�[�p�|�C���^
	void (SceneGame::*fpUpdate)(void);

	int targetAppearCount;


	//	�ꎞ�ϐ�
	D3DXVECTOR3 buffWiiAccel;
	D3DXVECTOR3 buffWiiRot;
};

#endif	// MY_SCENE_GAME_H
