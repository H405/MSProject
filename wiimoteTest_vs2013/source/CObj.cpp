//*****************************************************************************
//	�V�[������ [CObj.cpp]
//	Author : KOTARO NAGASAKI
//	create : 4/16
//	Update : 4/16
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "CObj.h"

//*****************************************************************************
//	�ÓI�ϐ���`
//*****************************************************************************
CObj* CObj::top[COBJ_PRIORITY_MAX] = {nullptr};
CObj* CObj::cur[COBJ_PRIORITY_MAX] = {nullptr};

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CObj::CObj(OBJTYPE _objType, int _priority)
{
	priority = _priority;
	objType = _objType;

	//	���߂̈�x����-----------------------------------------------------------
	//	�擪�̃I�u�W�F�N�g�����݂��Ȃ��ꍇ
	if(top[priority] == NULL)
	{
		top[priority] = this;
	}

	//	�Ō���̃I�u�W�F�N�g�����݂��Ȃ��ꍇ
	if(cur[priority] == NULL)
	{
		cur[priority] = this;
	}
	else
	{
		//	�Ō���̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���A���̃I�u�W�F�N�g�ɂ���
		cur[priority]->next = this;
	}
	//-------------------------------------------------------------------------------

	//	���݂̃I�u�W�F�N�g���擪�̏ꍇ�A���̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g��NULL��
	if(top[priority] == this)
	{
		this->prev = NULL;
	}
	//	���݂̃I�u�W�F�N�g���擪�Ŗ����ꍇ�A���̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g�|�C���^�����Ō���̃I�u�W�F�N�g�|�C���^��
	else
	{
		this->prev = cur[priority];
	}

	//	�Ō���̃I�u�W�F�N�g�����̃I�u�W�F�N�g�ɂ���
	cur[priority] = this;

	//	���̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g������NULL�ɂ���
	this->next = NULL;

	//�f���[�g�t���O
	deleteFlag = false;
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CObj::~CObj()
{
	if((this == top[priority]) && (this == cur[priority]))
	{
		top[priority] = NULL;
		cur[priority] = NULL;
	}
	else
	{
		if(this == top[priority])
		{
			top[priority] = this->next;
			top[priority]->prev = NULL;
		}
		else if(this == cur[priority])
		{
			cur[priority] = this->prev;
			cur[priority]->next = NULL;
		}
		else
		{
			this->prev->next = this->next;
			this->next->prev = this->prev;
		}
	}
}
//=============================================================================
//	�����[�X
//=============================================================================
void CObj::Release()
{
	deleteFlag = true;
}
//=============================================================================
//	�f���[�g�t���O�̃`�F�b�N
//=============================================================================
void CObj::CheckDeleteFlag()
{
	for(int count = 0;count < COBJ_PRIORITY_MAX;count++)
	{
		CObj* obj = top[count];

		//	�X�V�O�f���[�g����
		//-------------------------------------------------------------------------------
		{
			while(obj != NULL)
			{
				CObj* objNext = top[count]->next;
				objNext = obj->next;

				if(obj->deleteFlag == true)
				{
					//obj->Uninit();
					delete obj;
				}

				obj = objNext;
			}
		}
	}
}
//=============================================================================
//	�S�̍X�V
//=============================================================================
void CObj::UpdateAll()
{
	for(int count = 0;count < COBJ_PRIORITY_MAX;count++)
	{
		CObj* obj = top[count];

		//	�X�V�O�f���[�g����
		//-------------------------------------------------------------------------------
		{
			while(obj != NULL)
			{
				CObj* objNext = top[count]->next;
				objNext = obj->next;

				if(obj->deleteFlag == true)
				{
					//obj->Uninit();
					delete obj;
				}

				obj = objNext;
			}
		}
		//-------------------------------------------------------------------------------

		//	�X�V����
		//-------------------------------------------------------------------------------
		obj = top[count];

		while(obj != NULL)
		{
			obj->Update();

			obj = obj->next;
		}
		//-------------------------------------------------------------------------------

		//	�X�V��f���[�g����
		//-------------------------------------------------------------------------------
		{
			obj = top[count];

			while(obj != NULL)
			{
				CObj* objNext = top[count]->next;
				objNext = obj->next;

				if(obj->deleteFlag == true)
				{
					//obj->Uninit();
					delete obj;
				}

				obj = objNext;
			}
		}
		//-------------------------------------------------------------------------------
	}
}
//=============================================================================
//	�S�̍X�V(�w��̃v���C�I���e�B�̂�)
//=============================================================================
void CObj::UpdateAll(int _priority)
{
	CObj* obj = top[_priority];

	//	�X�V�O�f���[�g����
	//-------------------------------------------------------------------------------
	{
		while(obj != NULL)
		{
			CObj* objNext = top[_priority]->next;
			objNext = obj->next;

			if(obj->deleteFlag == true)
			{
				//obj->Uninit();
				delete obj;
			}

			obj = objNext;
		}
	}
	//-------------------------------------------------------------------------------

	//	�X�V����
	//-------------------------------------------------------------------------------
	obj = top[_priority];

	while(obj != NULL)
	{
		obj->Update();

		obj = obj->next;
	}
	//-------------------------------------------------------------------------------

	//	�X�V��f���[�g����
	//-------------------------------------------------------------------------------
	{
		obj = top[_priority];

		while(obj != NULL)
		{
			CObj* objNext = top[_priority]->next;
			objNext = obj->next;

			if(obj->deleteFlag == true)
			{
				//obj->Uninit();
				delete obj;
			}

			obj = objNext;
		}
	}
	//-------------------------------------------------------------------------------
}
//=============================================================================
//	�S�̕`��(�����_�[�^�[�Q�b�g������)
//=============================================================================
void CObj::DrawAll()
{
	for(int count = 0;count < NORMAL_COBJ_PRIORITY + PAUSE_COBJ_PRIOTITY + FADE_COBJ_PRIOTITY;count++)
	{
		CObj* obj = top[count];

		while(obj != NULL)
		{
			obj->Draw();

			obj = obj->next;
		}
	}
}
//=============================================================================
//	�S�̕`��(�w��̃v���C�I���e�B�̂�)
//=============================================================================
void CObj::DrawAll(int _priority)
{
	CObj* obj = top[_priority];

	while(obj != NULL)
	{
		obj->Draw();

		obj = obj->next;
	}
}
//=============================================================================
//	�S�̉��
//=============================================================================
void CObj::ReleaseAll()
{
	for(int count = 0;count < COBJ_PRIORITY_MAX;count++)
	{
		CObj* obj = top[count];

		while(obj != NULL)
		{
			CObj* objNext;
			objNext = obj->next;
			//obj->Uninit();
			delete obj;
			obj = objNext;
		}

		top[count] = NULL;
		cur[count] = NULL;
	}
}
//=============================================================================
//	�S�̉��(�w��v���C�I���e�B�̂�)
//=============================================================================
void CObj::ReleaseAll(int _priority)
{
	CObj* obj = top[_priority];

	while(obj != NULL)
	{
		CObj* objNext;
		objNext = obj->next;
		//obj->Uninit();
		delete obj;
		obj = objNext;
	}

	top[_priority] = NULL;
	cur[_priority] = NULL;
}

CObj* CObj::getInstans(OBJTYPE _objType)
{
	CObj* obj = top[3];

	while (obj != NULL)
	{
		if (obj->objType == _objType)
			return obj;

		obj = obj->next;
	}

	return nullptr;
}
//-----------------------------------EOF---------------------------------------