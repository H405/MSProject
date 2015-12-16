//==============================================================================
//
// File   : ManagerTarget.h
// Brief  : �^�[�Q�b�g�Ǘ��I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_MANAGER_TARGET_H
#define MY_MANAGER_TARGET_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "target/Target.h"
#include <stdio.h>

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************
#define TARGET_MAX (16)

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Target;
class Effect;
class EffectParameter;
class Texture;


//******************************************************************************
// �N���X��`
//******************************************************************************
class ManagerTarget
{
public:
	enum
	{
		STATE_NORMAL = 0,
		STATE_MAX
	}STATE;

	typedef struct
	{
		char name[256];
		int appearTime;
		D3DXVECTOR3 appearPos;
		COLOR_STATE colorState;
	}TARGET_APPEAR_DATA;

	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ManagerTarget( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ManagerTarget( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Initialize(
		IDirect3DDevice9* pDevice,
		const EffectParameter* pParameter,
		Effect* pEffectGeneral,
		Texture* pTextureCross,
		Texture* pTextureArrow,
		Texture* pTextureCircle
	);

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
	void Update(int* _table , int* _fireworksTableIndex);

	//==============================================================================
	// Brief  : �^�[�Q�b�g���ˏ���
	// Return : int									: �z��ԍ�
	// Arg2   : D3DXVECTOR3							: �����ʒu
	//==============================================================================
	int Add(D3DXVECTOR3 _pos, COLOR_STATE _colorState = COLOR_STATE_W);

	//==============================================================================
	// Brief  : �C���f�b�N�X�擾����
	// Return : int									: �g�p�\�ȃI�u�W�F�N�g�̔ԍ��i�S���g�p���̏ꍇ�͕��̒l���Ԃ�j
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int GetIndex();

	//==============================================================================
	// Brief  : �e�[�u���̃\�[�g����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Sort(int* _table, int _deleteIndex);

	//==============================================================================
	// Brief  : �^�[�Q�b�g�����X�N���v�g�ǂݍ��ݏ���
	//==============================================================================
	void ReadTargetScriptFromFile(const char* _fileName);

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	Target* getTarget(int _index){return &target[_index];}
	void setInvViewMatrix(D3DXMATRIX _invViewMatrix){invViewMatrix = _invViewMatrix;};

protected:

	//	�^�[�Q�b�g�̔z��
	Target* target;

	//	�J�����̋t�s��
	D3DXMATRIX invViewMatrix;

	//	�^�[�Q�b�g�̎��R���ŔF���p�t���O
	bool enableOld[TARGET_MAX];

	TARGET_APPEAR_DATA* targetAppearData;
	int targetAppearDataMax;

	int targetAppearCount;
	int targetAppearIndex;

	//==============================================================================
	// Brief  : �^�[�Q�b�g�����X�N���v�g�ǂݍ��ݏ���
	//==============================================================================
	void SkipComment(FILE* _fp);
	void Read_TIM_POS_COL(FILE* _fp, int _readDataIndex);
	void ReadAppearTargetMax(FILE* _fp);
	void SortAppearTargetData();
	void autoAppear(int* _table , int* _targetTableIndex);

private:
	void InitializeSelf( void );
	ManagerTarget( const ManagerTarget& );
	ManagerTarget operator=( const ManagerTarget& );
};

#endif	// MY_MANAGER_TARGET_H
