//*****************************************************************************
//	sin,cos計算用 [radianTable.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _CRADIAN_TABLE_H_
#define _CRADIAN_TABLE_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "fileReader.h"
#include "main.h"

//*****************************************************************************
//	定数定義
//*****************************************************************************
#define TABELE_MAX (361)

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CRadianTable
{
public:

	CRadianTable(){};
	~CRadianTable(){};
	static void Init();

	//=============================================================================
	//	sin値のゲッター
	//
	//	引数はディグリー角を指定
	//=============================================================================
	static float mySinf(float _degree)
	{
		float sinValue;
		float downValue;
		float upValue;
		int cutDegree;

		if (_degree >= 0.0f)
		{
			for (;;)
			{
				if (_degree >= 360)
					_degree -= 360;
				else
					break;
			}
		}

		if (_degree < 0.0f)
		{
			for (;;)
			{
				if (_degree <= -360)
					_degree += 360;
				else
					break;
			}
			//	-値を＋値として扱う
			_degree += 360;
		}

		//_degreeが 90.1 の場合・・・
		//sinTable[90]の値に、(sinTable[91] - sinTable[90]) × 0.1の値を足す
		cutDegree = (int)floor(_degree);
		downValue = sinTable[cutDegree];
		upValue = sinTable[cutDegree + 1];

		sinValue = downValue + ((upValue - downValue) * (_degree - cutDegree));

		return sinValue;
	}

	//=============================================================================
	//	cos値のゲッター
	//
	//	引数はディグリー角を指定
	//=============================================================================
	static float myCosf(float _degree)
	{
		float cosValue;
		float downValue;
		float upValue;
		int cutDegree;

		if (_degree >= 0.0f)
		{
			for (;;)
			{
				if (_degree >= 360)
					_degree -= 360;
				else
					break;
			}
		}

		if (_degree < 0.0f)
		{
			for (;;)
			{
				if (_degree <= -360)
					_degree += 360;
				else
					break;
			}
			//	-値を＋値として扱う
			_degree += 360;
		}

		//_degreeが 90.1 の場合・・・
		//cosTable[90]の値に、(cosTable[91] - cosTable[90]) × 0.1の値を足す
		cutDegree = (int)floor(_degree);
		downValue = cosTable[cutDegree];
		upValue = cosTable[cutDegree + 1];

		cosValue = downValue + ((upValue - downValue) * (_degree - cutDegree));

		return cosValue;
	}

private:

	static float sinTable[TABELE_MAX];
	static float cosTable[TABELE_MAX];
};

#endif

//-----------------------------------EOF---------------------------------------