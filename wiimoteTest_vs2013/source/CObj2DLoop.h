//*****************************************************************************
// ���[�v�A�j���[�V�����p2D�|���S�� [CObj2DLoop.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _COBJ2DLOOP_H_
#define _COBJ2DLOOP_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "main.h"
#include "CObj2D.h"


//	���������̃t�@�C����
//	������Author�ȊO�̕ύX�͋֎~�I�I
//	�������ύX���K�v�Ȍ�������ꍇ��Author�ɘA�����邱��

//*****************************************************************************
//	�N���X��`
//
//	�]�v�Ȓ��_�v�Z�����Ȃ��悤�ɁA���t���[�����_�v�Z�����Ȃ�
//	�ʒu�A��]�A�F�@�̒l���ύX���ꂽ�ꍇ�́A������setVtxBuff�֐����Ăяo������
//	���[�v�A�j���[�V���������݂̂��s���ꍇ�͎����I�ɌĂ΂��̂Őݒ�̕K�v�Ȃ�
//*****************************************************************************
class CObj2DLoop:public CObj2D
{
public:
	CObj2DLoop(OBJTYPE _objType, int _priority);
	virtual ~CObj2DLoop();
	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//=============================================================================
	//	�쐬�㗝����
	//
	//	�T�C�Y�̎w��̓|���S���̑S�����w�肷��
	//	��ʂ����ς��̃|���S������肽���Ƃ��́@SCREE_WIDTH(SCREEN_HEIGHT)�@���w�肷��
	//
	//	loopRateX,loopRateY�́A��x�̃��[�v�X�V�����ł��炷UV�l��ݒ�
	//	loopCountMax�́A���[�v�X�V�������s���J�E���g����ݒ�
	//	��1�ȏ���w�肷�邱��
	//
	//	pos�̓f�t�H���g�ŉ�ʂ̒��S
	//	rot,color�͂��ꂼ��A0.0f��1.0f�ŏ�����
	//	�e�N�X�`��UV�l�̓f�t�H���g�l (L:0.0   T:0.0   R:1.0   B:1.0)
	//=============================================================================
	static CObj2DLoop* Create(LPDIRECT3DDEVICE9 _device,
		float _loopRateX,
		float _loopRateY,
		int _loopCountMax,
		D3DXVECTOR3 _size,
		int _priority,
		D3DXVECTOR3 _pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3 _rot = VEC3_0,
		D3DXCOLOR _color = COL4_1,
		TEXUV _texUV = UV_DEF);

	virtual void setVtxBuff();
	void checkTexUV();

	//	�Q�b�^�[
	//-------------------------------------------------
	bool getLoopFlag()
	{
		return loopFlag;
	}
	//-------------------------------------------------

	//	�Z�b�^�[
	//-------------------------------------------------
	void setLoopFlag(bool _setFlag)
	{
		loopFlag = _setFlag;
	}
	//-------------------------------------------------

private:
	float loopRateX;	//	���[�v�t���[��X�̕ύX�l���[�g
	float loopRateY;	//	���[�v�t���[��Y�̕ύX�l���[�g
	int loopCountMax;	//	���[�v�t���[���̕ύX�J�E���g�̍ő�l
	int loopCount;		//	���[�v�t���[���J�E���g��

	bool loopFlag;		//	���[�v�t���O��TRUE�̂Ƃ��́A�J�E���g�������Z�����i���[�v����j
};

#endif

//-----------------------------------EOF---------------------------------------