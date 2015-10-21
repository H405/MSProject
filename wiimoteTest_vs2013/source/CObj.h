//*****************************************************************************
//	シーン処理 [CObj.h]
//	Author : KOTARO NAGASAKI
//	create : 4/16
//	Update : 4/16
//*****************************************************************************
#ifndef _COBJ_H_
#define _COBJ_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	定数定義
//*****************************************************************************
#define NORMAL_COBJ_PRIORITY (8)	//	通常の（オブジェクト用の）CObj系オブジェクト登録用プライオリティ数

#define PAUSE_COBJ_PRIOTITY (1)	//	ポーズ事用のCObj系オブジェクト登録用プライオリティ数

#define FADE_COBJ_PRIOTITY (1)	//	フェード時用のCObj系オブジェクト登録用プライオリティ数

#define RENDER_TARTGET_COBJ_PRIOTITY (3)	//	レンダーターゲット用のCObj系オブジェクト登録用プライオリティ数

#define COBJ_PRIORITY_MAX (NORMAL_COBJ_PRIORITY + PAUSE_COBJ_PRIOTITY + FADE_COBJ_PRIOTITY + RENDER_TARTGET_COBJ_PRIOTITY)	//	プライオリティの総数

#define PRIORIRY_PAUSE (NORMAL_COBJ_PRIORITY)	//	ポーズ事用のCObj系オブジェクト登録用プライオリティの開始番号
#define PRIORIRY_FADE (PRIORIRY_PAUSE + PAUSE_COBJ_PRIOTITY)	//	フェード時用のCObj系オブジェクト登録用プライオリティの開始番号
#define PRIORITY_RENDER_TARGET (PRIORIRY_FADE + FADE_COBJ_PRIOTITY)	//	レンダーターゲット1用のCObj系オブジェクト登録用プライオリティの開始番号
#define PRIORITY_RENDER_TARGET2 (PRIORITY_RENDER_TARGET + 1)	//	レンダーターゲット2用のCObj系オブジェクト登録用プライオリティの開始番号
#define PRIORITY_RENDER_TARGET3 (PRIORITY_RENDER_TARGET2 + 1)	//	レンダーターゲット3用のCObj系オブジェクト登録用プライオリティの開始番号

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CObj
{
public:

	//*****************************************************************************
	//	列挙体定義
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
	//	関数定義
	//*****************************************************************************
		//	共通な仮想関数と静的関数
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

		//	全てで使うわけではないが
		//	ダウンキャストせずにオーバーライドで呼び出せるように仮想関数としてここで定義
		//	必要ないところで不正なデータを返さないよう、オール０を返す
		//	もしくは、引数に引数の値をそのまま代入(する必要ないけど、値入れないと警告出るから)
		//-------------------------------------------------------------------------------
		virtual void Fire(){};
		//-------------------------------------------------------------------------------

		static CObj* getInstans(OBJTYPE _objType);

protected:

	//*****************************************************************************
	//	変数定義
	//*****************************************************************************
	LPDIRECT3DDEVICE9 device;	//	デバイス
	static CObj* top[COBJ_PRIORITY_MAX];	//	各プライオリティごとの先頭オブジェクトへのポインタ
	static CObj* cur[COBJ_PRIORITY_MAX];	//	各プライオリティごとの末尾（現在の）オブジェクトへのポインタ
	CObj* next;	//	各々のオブジェクトが持っている、リストの次のオブジェクトへのポインタ
	CObj* prev;	//	各々のオブジェクトが持っている、リストの前のオブジェクトへのポインタ
	int priority;	//	プライオリティ
	bool deleteFlag;	//	描画後、削除するかしないかのフラグ
	OBJTYPE objType;	//	オブジェクトの識別インデックス（クラス毎に共通）
	SPECIALTYPE specialType;	//	objTypeから更に詳しく分類する場合の識別番号

};

#endif

//-----------------------------------EOF---------------------------------------