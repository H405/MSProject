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

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class ManagerPoint;
class FireworksState;

//******************************************************************************
// �\���̒�`
//******************************************************************************
typedef struct
{
	//	�ʒu���
	D3DXVECTOR3 pos;

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

	//	���R���ł܂ł̃J�E���^
	int deleteCount;

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
	void burn();

	//==============================================================================
	// Brief  : �X�e�[�g�̐ݒ�
	// Return : void								: �Ȃ�
	// Arg    : FireworksState** ppState				: �X�e�[�g�e�[�u��
	//==============================================================================
	static void SetState( FireworksState** ppState );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	D3DXVECTOR3 getSpeed(){return param.speed;}

	D3DXVECTOR3 getPosition(){return param.pos;}
	void addPosition(float _x, float _y, float _z){param.pos.x += _x;param.pos.y += _y;param.pos.z += _z;}
	void addPositionX(float _x){param.pos.x += _x;}
	void addPositionY(float _y){param.pos.y += _y;}
	void addPositionZ(float _z){param.pos.z += _z;}

	float getRotation(){return param.rot;}
	void addRotationSpeed(float _value){param.rot += _value;}

	float getRotationSpeed(){return param.rotSpeed;}

	bool IsEnable(){return param.enable;}
	void setEnable(bool _flag){param.enable = _flag;}

	ManagerPoint* getManagerPoint(){return param.managerPoint;};

	int getDeleteCount(){return param.deleteCount;}
	void deleteCountPP(){param.deleteCount++;}

	FIREWORKS_PARAM* getParam(){return &param;}

protected:

	// �X�e�[�g
	static FireworksState**	ppState_;
	int indexState;

	//	�ԉΗp�p�����[�^
	FIREWORKS_PARAM param;

private:
	void InitializeSelf( void );
	Fireworks( const Fireworks& );
	Fireworks operator=( const Fireworks& );
};

#endif	// MY_FIREWORKS_H
