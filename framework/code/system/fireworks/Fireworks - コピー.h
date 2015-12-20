//==============================================================================
//
// File   : Fireworks.h
// Brief  : �ԉ΃I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_FIREWORKS_H
#define MY_FIREWORKS_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "d3dx9.h"
#include "../target/Target.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************
#define FIRE_MAX (150)	//	�P�̉ԉ΂��琶�������ΉԂ̐�(6�̔{���ɂ��邱��)
#define SMALL_FIREWORKS_MAX (5)
#define DELETECOUNT_MAX (100)
typedef int TIME;


//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class ManagerPoint;
class FireworksState;
class Fire;
class ManagerLight;
class LightPoint;
class LightDirection;
class Sound;
class SceneArgumentMain;
class Target;

//******************************************************************************
// �\���̒�`
//******************************************************************************
typedef struct
{
	D3DXVECTOR3 startPos;
	D3DXVECTOR3 buffPos1;
	D3DXVECTOR3 buffPos2;
	D3DXVECTOR3 endPos;
	int count;


	//	�ʒu���
	D3DXVECTOR3 pos;
	D3DXVECTOR3 setPos;
	D3DXVECTOR3 posOld[SMALL_FIREWORKS_MAX];

	//	�s��ϊ��p��]�x�N�g��
	D3DXVECTOR3 matRot;

	//	�ړ��̉�]����
	float rot;

	//	Z���̉�]���x�i�P�A�b�v�f�[�g�łǂ̂��炢��]���邩�j
	float rotSpeed;

	//	�ړ����x
	D3DXVECTOR3 speed;

	//	�|�C���g�X�v���C�g�N���X�Ǘ��I�u�W�F�N�g
	ManagerPoint* managerPoint;

	//	�g�p�\�t���O
	bool enable;

	//	�j��t���O
	bool burnFlag;

	//	���R���ł܂ł̃J�E���^
	TIME disappear;

	//	�����p�J�E���^
	TIME appear;

	//	�ʒu�����Z�b�g���鎞��
	TIME setPosOld;

	Fire* fire;
	Fire* smallFire;

	//	�e����ΉԂ̑���
	int fireMax;

	//	���􂵂��ԉ΂̑���
	int smallFireMax;
	int setSmallFireIndex;

	D3DXMATRIX matrix;

	//	�J�����̋t�s��
	D3DXMATRIX invViewMatrix;

	//	����
	LightPoint* lightPoint;

	//	��
	Sound* launchSound;
	Sound* burnSound;

	//	�F���
	COLOR_STATE colorState;
	D3DXCOLOR color;

}FIREWORKS_PARAM;

//******************************************************************************
// �N���X��`
//******************************************************************************
class Fireworks
{
friend class FireworksState;

public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	Fireworks( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~Fireworks( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	//==============================================================================
	int Set(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _speed,
		float _rot,
		float _rotSpeed);

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	//==============================================================================
	int Set(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		COLOR_STATE _colorState = COLOR_STATE_W);
	int Set(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		Target* _target);
	int SetSP(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		COLOR_STATE _colorState = COLOR_STATE_W);
	int SetW(
		int _indexState,
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _diffRot,
		Target* _target);

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : �ԉ΂̔�������
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int burn(
		float _hitCheckOffset,
		float _hitPosLength);

	//==============================================================================
	// Brief  : �ԉ΂̔�������(�\���E�OVer)
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void burn2();

	//==============================================================================
	// Brief  : �X�e�[�g�̐ݒ�
	// Return : void								: �Ȃ�
	// Arg    : FireworksState** ppState				: �X�e�[�g�e�[�u��
	//==============================================================================
	static void SetState( FireworksState** ppState );

	//==============================================================================
	// Brief  : �ԉ΂̉���������
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void setSound(Sound* _burnSound, Sound* _launchSound);

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	D3DXVECTOR3 getSpeed(){return param.speed;}

	D3DXVECTOR3 getPosition(){return param.pos;}
	D3DXVECTOR3 getSetPosition(){return param.setPos;}
	void addPosition(float _x, float _y, float _z){param.pos.x += _x;param.pos.y += _y;param.pos.z += _z;}
	void addPositionX(float _x){param.pos.x += _x;}
	void addPositionY(float _y){param.pos.y += _y;}
	void addPositionZ(float _z){param.pos.z += _z;}

	float getRotation(){return param.rot;}
	void addRotationSpeed(float _value){param.rot += _value;}

	float getRotationSpeed(){return param.rotSpeed;}

	bool IsEnable(){return param.enable;}
	void setEnable(bool _flag){param.enable = _flag;}
	bool IsBurnFlag(){return param.burnFlag;}

	ManagerPoint* getManagerPoint(){return param.managerPoint;};

	int getDeleteCount(){return param.disappear;}
	void disappearPP(){param.disappear++;}

	FIREWORKS_PARAM* getParam(){return &param;}
	void setInvViewMatrix(D3DXMATRIX _invViewMatrix){param.invViewMatrix = _invViewMatrix;};

	void setManagerLight(ManagerLight* _managerLight);

	COLOR_STATE getColorState(){return param.colorState;}

protected:

	// �X�e�[�g
	static FireworksState**	ppState_;
	int indexState;

	//	�ԉΗp�p�����[�^
	FIREWORKS_PARAM param;

	ManagerLight* managerLight;

	int burnSoundIndex;
	int launchSoundIndex;

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void NormalUpdate( void );

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void BurnUpdate( void );

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Burn2Update( void );

	//	�X�V�֐��i�[�p�|�C���^
	void (Fireworks::*fpUpdate)(void);

private:
	void InitializeSelf( void );
	Fireworks( const Fireworks& );
	Fireworks operator=( const Fireworks& );
};

#endif	// MY_FIREWORKS_H
