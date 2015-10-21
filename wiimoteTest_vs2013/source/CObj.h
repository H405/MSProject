//*****************************************************************************
//	�V�[������ [CObj.h]
//	Author : KOTARO NAGASAKI
//	create : 4/16
//	Update : 4/16
//*****************************************************************************
#ifndef _COBJ_H_
#define _COBJ_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	�萔��`
//*****************************************************************************
#define NORMAL_COBJ_PRIORITY (8)	//	�ʏ�́i�I�u�W�F�N�g�p�́jCObj�n�I�u�W�F�N�g�o�^�p�v���C�I���e�B��

#define PAUSE_COBJ_PRIOTITY (1)	//	�|�[�Y���p��CObj�n�I�u�W�F�N�g�o�^�p�v���C�I���e�B��

#define FADE_COBJ_PRIOTITY (1)	//	�t�F�[�h���p��CObj�n�I�u�W�F�N�g�o�^�p�v���C�I���e�B��

#define RENDER_TARTGET_COBJ_PRIOTITY (3)	//	�����_�[�^�[�Q�b�g�p��CObj�n�I�u�W�F�N�g�o�^�p�v���C�I���e�B��

#define COBJ_PRIORITY_MAX (NORMAL_COBJ_PRIORITY + PAUSE_COBJ_PRIOTITY + FADE_COBJ_PRIOTITY + RENDER_TARTGET_COBJ_PRIOTITY)	//	�v���C�I���e�B�̑���

#define PRIORIRY_PAUSE (NORMAL_COBJ_PRIORITY)	//	�|�[�Y���p��CObj�n�I�u�W�F�N�g�o�^�p�v���C�I���e�B�̊J�n�ԍ�
#define PRIORIRY_FADE (PRIORIRY_PAUSE + PAUSE_COBJ_PRIOTITY)	//	�t�F�[�h���p��CObj�n�I�u�W�F�N�g�o�^�p�v���C�I���e�B�̊J�n�ԍ�
#define PRIORITY_RENDER_TARGET (PRIORIRY_FADE + FADE_COBJ_PRIOTITY)	//	�����_�[�^�[�Q�b�g1�p��CObj�n�I�u�W�F�N�g�o�^�p�v���C�I���e�B�̊J�n�ԍ�
#define PRIORITY_RENDER_TARGET2 (PRIORITY_RENDER_TARGET + 1)	//	�����_�[�^�[�Q�b�g2�p��CObj�n�I�u�W�F�N�g�o�^�p�v���C�I���e�B�̊J�n�ԍ�
#define PRIORITY_RENDER_TARGET3 (PRIORITY_RENDER_TARGET2 + 1)	//	�����_�[�^�[�Q�b�g3�p��CObj�n�I�u�W�F�N�g�o�^�p�v���C�I���e�B�̊J�n�ԍ�

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class CObj
{
public:

	//*****************************************************************************
	//	�񋓑̒�`
	//*****************************************************************************
	typedef enum
	{
		OBJTYPE_NONE = 0 ,
		OBJTYPE_2D ,
		OBJTYPE_2DKEYFRAME,
		OBJTYPE_2DLOOP,
		OBJTYPE_FADEIN,
		OBJTYPE_FADEOUT,
		OBJTYPE_FIREWORK,
		OBJTYPE_MAX
	}OBJTYPE;

	typedef enum
	{
		SPECIALTYPE_NONE = 0,
		SPECIALTYPE_MAX
	}SPECIALTYPE;

	//*****************************************************************************
	//	�֐���`
	//*****************************************************************************
		//	���ʂȉ��z�֐��ƐÓI�֐�
		//-------------------------------------------------------------------------------
		CObj(OBJTYPE _objType , int _priority = 3);
		virtual ~CObj();
		virtual void Update() = 0;
		virtual void Draw() = 0;
		static void UpdateAll();
		static void UpdateAll(int _priority);
		static void DrawAll();
		static void DrawAll(int _priority);
		static void ReleaseAll();
		static void ReleaseAll(int _priority);
		static void CheckDeleteFlag();
		void Release();
		bool GetDeleteFlag(){return deleteFlag;};
		//-------------------------------------------------------------------------------

		//	�S�ĂŎg���킯�ł͂Ȃ���
		//	�_�E���L���X�g�����ɃI�[�o�[���C�h�ŌĂяo����悤�ɉ��z�֐��Ƃ��Ă����Œ�`
		//	�K�v�Ȃ��Ƃ���ŕs���ȃf�[�^��Ԃ��Ȃ��悤�A�I�[���O��Ԃ�
		//	�������́A�����Ɉ����̒l�����̂܂ܑ��(����K�v�Ȃ����ǁA�l����Ȃ��ƌx���o�邩��)
		//-------------------------------------------------------------------------------
		virtual void Fire(){};
		//-------------------------------------------------------------------------------

		static CObj* getInstans(OBJTYPE _objType);

protected:

	//*****************************************************************************
	//	�ϐ���`
	//*****************************************************************************
	LPDIRECT3DDEVICE9 device;	//	�f�o�C�X
	static CObj* top[COBJ_PRIORITY_MAX];	//	�e�v���C�I���e�B���Ƃ̐擪�I�u�W�F�N�g�ւ̃|�C���^
	static CObj* cur[COBJ_PRIORITY_MAX];	//	�e�v���C�I���e�B���Ƃ̖����i���݂́j�I�u�W�F�N�g�ւ̃|�C���^
	CObj* next;	//	�e�X�̃I�u�W�F�N�g�������Ă���A���X�g�̎��̃I�u�W�F�N�g�ւ̃|�C���^
	CObj* prev;	//	�e�X�̃I�u�W�F�N�g�������Ă���A���X�g�̑O�̃I�u�W�F�N�g�ւ̃|�C���^
	int priority;	//	�v���C�I���e�B
	bool deleteFlag;	//	�`���A�폜���邩���Ȃ����̃t���O
	OBJTYPE objType;	//	�I�u�W�F�N�g�̎��ʃC���f�b�N�X�i�N���X���ɋ��ʁj
	SPECIALTYPE specialType;	//	objType����X�ɏڂ������ނ���ꍇ�̎��ʔԍ�

};

#endif

//-----------------------------------EOF---------------------------------------