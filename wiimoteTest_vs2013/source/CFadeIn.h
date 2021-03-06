//*****************************************************************************
//	フェードイン処理処理 [ CFadeIn.h ]
//	Author : KOTARO NAGASAKI
//	create : 6/27
//*****************************************************************************
#ifndef _FADEIN_H_
#define _FADEIN_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"
#include "CObj2D.h"

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CFadeIn:public CObj2D
{
public:

	//*****************************************************************************
	//	関数定義
	//*****************************************************************************
	CFadeIn( OBJTYPE _objType , int _priority);
	~CFadeIn(  );
	void Init();
	void Update(  );
	void Draw(  );
	static CFadeIn* Create(LPDIRECT3DDEVICE9 _device,
							int _priority);

private:

};

#endif

//	EOF
