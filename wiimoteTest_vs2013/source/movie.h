//*****************************************************************************
//	 [ .cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CMovie
{
public:

	CMovie(){};
	~CMovie(){};

	void Init();

private:

	IGraphBuilder* graphBuilder;

};

//-----------------------------------EOF---------------------------------------