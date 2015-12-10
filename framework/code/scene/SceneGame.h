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

typedef enum
{
	ADD_1 = 0,
	ADD_5,
	ADD_10,
	ADD_20,
}ADD_SCORE_STATE;

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class CameraObject;
class CameraStateSpline;
class Gage;
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
class ObjectRiver;
class ObjectSkinMesh;
class ObjectWaterwheel;
class Player;

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

	static const int	COUNT_HOUSE = 11;		// �Ƃ̐�
	static const int	COUNT_GRASS = 500;		// ���̐�

	CameraObject*	pCamera_;					// �J����
	CameraObject*	pCameraShadowNear_;			// �e�p�J������
	CameraObject*	pCameraShadowFar_;			// �e�p�J������
	CameraObject**	ppCameraShadowPoint_;		// �e�p�J�����_
	LightDirection*	pLight_;					// ���C�g


	//	�Q�[��UI�֌W
	//----------------------------------------------------------
	//	�u�X�R�A�v����
	Object2D* stringScore;

	//	�X�R�A�I�u�W�F�N�g
	ObjectScore* score;

	//	�Q�[�W�I�u�W�F�N�g
	Gage* gage;

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

	//	�u���̎p���ɂȂ���AB�L�[�𓯎������v�I�u�W�F�N�g
	Object2D* calibrationWiimote;

	//	wii�����R���ő��삷��w
	Object2D* finger;

	//	�I�����̂����A�I�΂�Ă���I�u�W�F�N�g�̃|�C���^
	Object2D* chooseObject;
	Object2D* chooseObjectPrev;

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

	ObjectBillboard*		grasses;		// ��

	ObjectSkinMesh*			markers;		// �ꏊ�̖ڈ�

	//	�v���C���[
	Player* player;

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
	//----------------------------------------------------------

	//	�J�����̕���
	CAMERA_STATE cameraState;

	//==============================================================================
	// Brief  : calibration���p�̍X�V����
	//==============================================================================
	void calibrationUpdate(void);

	//==============================================================================
	// Brief  : �ʏ펞�p�̍X�V����
	//==============================================================================
	void normalUpdate(void);

	//==============================================================================
	// Brief  : �|�[�Y���p�̍X�V����
	//==============================================================================
	void pauseUpdate(void);

	//==============================================================================
	// Brief  : �|�[�Y���p�̍X�V����(�|�[�Y���̃t�F�[�h�p)
	//==============================================================================
	void pauseFadeUpdate(void);

	//==============================================================================
	// Brief  : �Đڑ��v�����p�̍X�V����
	//==============================================================================
	void reConnectWiimoteUpdate(void);

	//==============================================================================
	// Brief  : �Đڑ��v�����p�̍X�V����
	//==============================================================================
	void reConnectWiiboardUpdate(void);

	//==============================================================================
	// Brief  : wii�����R���̃��X�g�`�F�b�N����
	//==============================================================================
	bool wiiLostCheck(void);

	//==============================================================================
	// Brief  : �ԉ΂ƃ^�[�Q�b�g�̓����蔻�菈��
	//==============================================================================
	void collision_fireworks_target();

	//==============================================================================
	// Brief  : �ԉ΂Ɖԉ΂̓����蔻�菈��
	//==============================================================================
	void collision_fireworks_fireworks();

	//==============================================================================
	// Brief  : �X�e�[�W�֘A�̓ǂݍ��ݏ���
	//==============================================================================
	void InitializeStage(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : ���̑��RD�I�u�W�F�N�g�̓ǂݍ��ݏ���
	//==============================================================================
	void Initialize3DObject(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : UI�֘A�̓ǂݍ��ݏ���
	//==============================================================================
	void InitializeUI(SceneArgumentMain* pArgument);

	//==============================================================================
	// Brief  : �v���C���[�̈ړ�����
	//==============================================================================
	void MovePlayer();

	//==============================================================================
	// Brief  : �ԉΑł��グ����
	//==============================================================================
	void LaunchFireworks();

	//==============================================================================
	// Brief  : �V���N���Q�[�W�̉��Z��������
	//==============================================================================
	void AddGage(ADD_SCORE_STATE _state);

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
	// �Q�[���Z�N�V����
	enum
	{
		SECTION_WATERWHEEL = 0,		// ����
		SECTION_HOUSE,				// ����
		SECTION_BRIDGE,				// ��
		SECTION_MAXIMUM				// �ő�l
	};

	// �J�E���g�_�E���摜
	enum
	{
		IMAGE_COUNT_3 = 0,			// �J�E���g3
		IMAGE_COUNT_2,				// �J�E���g2
		IMAGE_COUNT_1,				// �J�E���g1
		IMAGE_COUNT_START,			// �����J�n
		IMAGE_COUNT_MAXIMUM			// �ő�l
	};

	// ���U���g�摜
	enum
	{
		IMAGE_RESULT_BACK = 0,			// �w�i
		IMAGE_RESULT_LOGO,				// ���S
		IMAGE_RESULT_SYNCRONIZE,		// �V���N��
		IMAGE_RESULT_JUDGE_0,			// ����0
		IMAGE_RESULT_JUDGE_1,			// ����1
		IMAGE_RESULT_JUDGE_2,			// ����2
		IMAGE_RESULT_TO_RANKING,		// �����L���O��
		IMAGE_RESULT_TO_TITLE,			// �^�C�g����
		IMAGE_RESULT_MAXIMUM			// �ő�l
	};

	// �����L���O�摜
	enum
	{
		IMAGE_RANKING_LOGO = 0,			// ���S
		IMAGE_RANKING_RANK_1,			// �����N1
		IMAGE_RANKING_RANK_2,			// �����N2
		IMAGE_RANKING_RANK_3,			// �����N3
		IMAGE_RANKING_RANK_4,			// �����N4
		IMAGE_RANKING_RANK_5,			// �����N5
		IMAGE_RANKING_MAXIMUM			// �ő�l
	};

	// ���U���g���o����
	enum
	{
		TIME_RESULT_BEGIN				= 0,																		// �J�n
		TIME_RESULT_BEGIN_BACK			= 0,																		// �w�i�J�n����
		COUNT_RESULT_BEGIN_BACK			= 10,																		// �w�i�J�n�t���[����
		TIME_RESULT_BEGIN_LOGO			= TIME_RESULT_BEGIN_BACK + COUNT_RESULT_BEGIN_BACK,							// ���S�J�n����
		COUNT_RESULT_BEGIN_LOGO			= 20,																		// ���S�J�n�t���[����
		TIME_RESULT_BEGIN_SYNCRONIZE	= TIME_RESULT_BEGIN_LOGO + COUNT_RESULT_BEGIN_LOGO,							// �V���N�����J�n����
		COUNT_RESULT_BEGIN_SYNCRONIZE	= 20,																		// �V���N�����J�n�t���[����
		TIME_RESULT_BEGIN_JUDGE_0		= TIME_RESULT_BEGIN_SYNCRONIZE + COUNT_RESULT_BEGIN_SYNCRONIZE + 10,		// ����0�J�n����
		COUNT_RESULT_BEGIN_JUDGE_0		= 15,																		// ����0�J�n�t���[����
		TIME_RESULT_BEGIN_JUDGE_1		= TIME_RESULT_BEGIN_JUDGE_0 + 5,											// ����1�J�n����
		COUNT_RESULT_BEGIN_JUDGE_1		= 15,																		// ����1�J�n�t���[����
		TIME_RESULT_BEGIN_JUDGE_2		= TIME_RESULT_BEGIN_JUDGE_0 + 10,											// ����2�J�n����
		COUNT_RESULT_BEGIN_JUDGE_2		= 15,																		// ����2�J�n�t���[����
		TIME_RESULT_BEGIN_GAUGE			= TIME_RESULT_BEGIN_JUDGE_2 + COUNT_RESULT_BEGIN_JUDGE_2,					// �V���N���Q�[�W�J�n����
		COUNT_RESULT_BEGIN_GAUGE		= 120,																		// �V���N���Q�[�W�J�n�t���[����
		TIME_RESULT_BEGIN_TO_RANKING	= TIME_RESULT_BEGIN_GAUGE + COUNT_RESULT_BEGIN_GAUGE + 30,					// �����L���O�֊J�n�J�n����
		COUNT_RESULT_BEGIN_TO_RANKING	= 20,																		// �����L���O�֊J�n�J�n�t���[����
		TIME_RESULT_BEGIN_TO_TITLE		= TIME_RESULT_BEGIN_GAUGE + COUNT_RESULT_BEGIN_GAUGE + 30,					// �^�C�g���֊J�n�J�n����
		COUNT_RESULT_BEGIN_TO_TITLE		= 20,																		// �^�C�g���֊J�n�J�n�t���[����
		TIME_RESULT_END					= TIME_RESULT_BEGIN_TO_TITLE + COUNT_RESULT_BEGIN_TO_TITLE					// �I��
	};

	// �����L���O���o����
	enum
	{
		TIME_RANKING_BEGIN				= 0,																		// �J�n
		TIME_RANKING_BEGIN_LOGO			= 0,																		// ���S�J�n����
		COUNT_RANKING_BEGIN_LOGO		= 20,																		// ���S�J�n�t���[����
		TIME_RANKING_BEGIN_RANK_5		= TIME_RANKING_BEGIN_LOGO + COUNT_RANKING_BEGIN_LOGO + 10,					// �����N5�J�n����
		COUNT_RANKING_BEGIN_RANK_5		= 20,																		// �����N5�J�n�t���[����
		TIME_RANKING_BEGIN_RANK_4		= TIME_RANKING_BEGIN_LOGO + COUNT_RANKING_BEGIN_LOGO + 20,					// �����N4�J�n����
		COUNT_RANKING_BEGIN_RANK_4		= 20,																		// �����N4�J�n�t���[����
		TIME_RANKING_BEGIN_RANK_3		= TIME_RANKING_BEGIN_LOGO + COUNT_RANKING_BEGIN_LOGO + 30,					// �����N3�J�n����
		COUNT_RANKING_BEGIN_RANK_3		= 20,																		// �����N3�J�n�t���[����
		TIME_RANKING_BEGIN_RANK_2		= TIME_RANKING_BEGIN_LOGO + COUNT_RANKING_BEGIN_LOGO + 40,					// �����N2�J�n����
		COUNT_RANKING_BEGIN_RANK_2		= 20,																		// �����N2�J�n�t���[����
		TIME_RANKING_BEGIN_RANK_1		= TIME_RANKING_BEGIN_RANK_2 + COUNT_RANKING_BEGIN_RANK_2 + 20,				// �����N1�J�n����
		COUNT_RANKING_BEGIN_RANK_1		= 30,																		// �����N1�J�n�t���[����
		TIME_RANKING_END				= TIME_RANKING_BEGIN_RANK_1 + COUNT_RANKING_BEGIN_RANK_1					// �I��
	};

	static const int	MAXIMUM_RANK = 5;		// �����L���O�ő吔

	CameraStateSpline*	pStateCameraPrevious_;				// �Q�[���J�n�O�J��������
	CameraStateSpline*	pStateCameraBetween_;				// �Q�[���Z�N�V�����ԃJ��������
	CameraStateSpline*	pStateCameraResult_;				// ���U���g�O�J��������
	int					timerSceneGame_;					// �Q�[���V�[���o�ߎ���

	Object2D*			pObjectCount_;						// �J�E���g�_�E���摜�I�u�W�F�N�g

	Object2D*			pObjectResult_;						// ���U���g�摜�I�u�W�F�N�g

	int					pRankingScore_[ MAXIMUM_RANK ];		// �����L���O�̃X�R�A
	int					indexRank_;							// �����N�̔ԍ�
	Object2D*			pObjectRanking_;					// �����L���O�摜�I�u�W�F�N�g
	ObjectScore*		pObjectScoreRanking_;				// �����L���O�X�R�A�I�u�W�F�N�g

	int					indexSection_;						// �Q�[���Z�N�V�����ԍ�

	ObjectModel*		pObjectTestForShadow_;				// �e�m�F�p

	int Initialize2( void );
	int Finalize2( void );
	void InitializeSelf2( void );

	// �Q�[���J�n�O�X�V
	void UpdatePreviousGame( void );

	// �Q�[���J�n�O�J�E���g�_�E���X�V
	void UpdateCountDownGame( void );

	// �Q�[���Z�N�V�����ԍX�V
	void UpdateBetweenSection( void );

	// ���U���g�ҋ@�X�V
	void UpdateWaitResult( void );

	// ���U���g�O�X�V
	void UpdatePreviousResult( void );

	// ���U���g�X�V
	void UpdateResult( void );

	// �����L���O�X�V
	void UpdateRanking( void );

	// �e�X�g�X�V
	void UpdateTest( void );

	// �J�����̃e�X�g�X�V
	void UpdateTestCamera( void );

	// ���U���g�I�u�W�F�N�g���\���ɂ���
	void DisableObjectResult( void );

	// �����L���O�I�u�W�F�N�g���\���ɂ���
	void DisableObjectRanking( void );

	//==============================================================================
	// ������ǉ�
	//==============================================================================

	//	�X�V�֐��i�[�p�|�C���^
	void (SceneGame::*fpUpdate)(void);

	//	�ꎞ�ϐ�
	int targetAppearCount;
	D3DXVECTOR3 buffWiiAccel;
	D3DXVECTOR3 buffWiiRot;
};

#endif	// MY_SCENE_GAME_H
