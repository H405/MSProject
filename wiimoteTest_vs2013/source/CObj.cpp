//*****************************************************************************
//	シーン処理 [CObj.cpp]
//	Author : KOTARO NAGASAKI
//	create : 4/16
//	Update : 4/16
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "CObj.h"

//*****************************************************************************
//	静的変数定義
//*****************************************************************************
CObj* CObj::top[COBJ_PRIORITY_MAX] = {nullptr};
CObj* CObj::cur[COBJ_PRIORITY_MAX] = {nullptr};

//=============================================================================
//	コンストラクタ
//=============================================================================
CObj::CObj(OBJTYPE _objType, int _priority)
{
	priority = _priority;
	objType = _objType;

	//	初めの一度だけ-----------------------------------------------------------
	//	先頭のオブジェクトが存在しない場合
	if(top[priority] == NULL)
	{
		top[priority] = this;
	}

	//	最後尾のオブジェクトが存在しない場合
	if(cur[priority] == NULL)
	{
		cur[priority] = this;
	}
	else
	{
		//	最後尾のオブジェクトの次のオブジェクトを、このオブジェクトにする
		cur[priority]->next = this;
	}
	//-------------------------------------------------------------------------------

	//	現在のオブジェクトが先頭の場合、このオブジェクトの前のオブジェクトをNULLに
	if(top[priority] == this)
	{
		this->prev = NULL;
	}
	//	現在のオブジェクトが先頭で無い場合、このオブジェクトの前のオブジェクトポインタをを最後尾のオブジェクトポインタに
	else
	{
		this->prev = cur[priority];
	}

	//	最後尾のオブジェクトをこのオブジェクトにする
	cur[priority] = this;

	//	このオブジェクトの次のオブジェクトをこのNULLにする
	this->next = NULL;

	//デリートフラグ
	deleteFlag = false;
}
//=============================================================================
//	デストラクタ
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
//	リリース
//=============================================================================
void CObj::Release()
{
	deleteFlag = true;
}
//=============================================================================
//	デリートフラグのチェック
//=============================================================================
void CObj::CheckDeleteFlag()
{
	for(int count = 0;count < COBJ_PRIORITY_MAX;count++)
	{
		CObj* obj = top[count];

		//	更新前デリート処理
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
//	全体更新
//=============================================================================
void CObj::UpdateAll()
{
	for(int count = 0;count < COBJ_PRIORITY_MAX;count++)
	{
		CObj* obj = top[count];

		//	更新前デリート処理
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

		//	更新処理
		//-------------------------------------------------------------------------------
		obj = top[count];

		while(obj != NULL)
		{
			obj->Update();

			obj = obj->next;
		}
		//-------------------------------------------------------------------------------

		//	更新後デリート処理
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
//	全体更新(指定のプライオリティのみ)
//=============================================================================
void CObj::UpdateAll(int _priority)
{
	CObj* obj = top[_priority];

	//	更新前デリート処理
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

	//	更新処理
	//-------------------------------------------------------------------------------
	obj = top[_priority];

	while(obj != NULL)
	{
		obj->Update();

		obj = obj->next;
	}
	//-------------------------------------------------------------------------------

	//	更新後デリート処理
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
//	全体描画(レンダーターゲットを除く)
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
//	全体描画(指定のプライオリティのみ)
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
//	全体解放
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
//	全体解放(指定プライオリティのみ)
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