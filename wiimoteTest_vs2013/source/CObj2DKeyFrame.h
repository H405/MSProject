//*****************************************************************************
// �L�[�t���[���A�j���[�V�����p2D�|���S�� [CObj2DKeyFrame.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _COBJ2DKEYFRAME_H_
#define _COBJ2DKEYFRAME_H_

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
//*****************************************************************************
class CObj2DKeyFrame : public CObj2D
{
public:
	CObj2DKeyFrame(OBJTYPE _objType, int _priority);
	virtual ~CObj2DKeyFrame();
	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//=============================================================================
	//	�쐬�㗝����
	//
	//	�T�C�Y�̎w��̓|���S���̑S�����w�肷��
	//	��ʂ����ς��̃|���S������肽���Ƃ��́@SCREE_WIDTH(SCREEN_HEIGHT)�@���w�肷��
	//
	//	keyMax�̓L�[�t���[���̃R�}��
	//	keyCountMax�́A�L�[�t���[���X�V�������s���J�E���g����ݒ�
	//	��1�ȏ���w��
	//
	//	pos�̓f�t�H���g�ŉ�ʂ̒��S
	//	rot,color�͂��ꂼ��A0.0f��1.0f�ŏ�����
	//	�e�N�X�`��UV�l�̓f�t�H���g�l (L:0.0   T:0.0   R:1.0   B:1.0)
	//=============================================================================
	static CObj2DKeyFrame* Create(LPDIRECT3DDEVICE9 _device,
		int _keyMax,
		int _keyCountMax,
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
	bool getKeyFlag()
	{
		return keyFlag;
	}
	//-------------------------------------------------

	//	�Z�b�^�[
	//-------------------------------------------------
	void setKeyFlag(bool _setFlag)
	{
		keyFlag = _setFlag;
	}
	//-------------------------------------------------

protected:

	float keyRate;	//	�L�[�t���[���̕ύX�l���[�g
	int keyMax;	//	�L�[�t���[�����̍ő�l
	int keyNum;	//	���݂̃R�}��
	int keyCountMax;	//	�L�[�t���[���̕ύX�J�E���g�̍ő�l
	int keyCount;	//	�L�[�t���[���J�E���g��

	bool keyFlag;	//	�L�[�t���O��TRUE�̂Ƃ��́A�J�E���g�������Z�����i�L�[�t���[���A�j���[�V��������j
};

#endif

//-----------------------------------EOF---------------------------------------