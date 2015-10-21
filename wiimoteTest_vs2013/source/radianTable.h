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
	static float mySinf(double _degree)
	{
		double cutDegreeN;	//	小数点以下を切り捨てた値を格納
		double cutDegreeF;	//	小数点以下の値を格納
		int cutDegree;	//	計算用正数値

		//	小数点以下と、その整数部を取得
		cutDegreeF = modf(_degree, &cutDegreeN);

		//	360度以下に丸め込む
		if (_degree >= 0.0f)
		{
			cutDegree = (int)cutDegreeN % 360;
		}
		//	
		else
		{
			cutDegree = (int)cutDegreeN % 360;
			cutDegree += 360;
		}

		//_degreeが 90.1 の場合・・・
		//sinTable[90]の値に、(sinTable[91] - sinTable[90]) × 0.1の値を足す
		return (float)(sinTable[cutDegree] + 
			(sinTable[cutDegree + 1] - sinTable[cutDegree]) * cutDegreeF);
	}

	//=============================================================================
	//	cos値のゲッター
	//
	//	引数はディグリー角を指定
	//=============================================================================
	static float myCosf(double _degree)
	{
		double cutDegreeN;	//	小数点以下を切り捨てた値を格納
		double cutDegreeF;	//	小数点以下の値を格納
		int cutDegree;	//	計算用正数値

		//	小数点以下と、その整数部を取得
		cutDegreeF = modf(_degree, &cutDegreeN);

		//	360度以下に丸め込む
		if (_degree >= 0.0f)
		{
			cutDegree = (int)cutDegreeN % 360;
		}
		//	
		else
		{
			cutDegree = (int)cutDegreeN % 360;
			cutDegree += 360;
		}

		//_degreeが 90.1 の場合・・・
		//cosTable[90]の値に、(cosTable[91] - cosTable[90]) × 0.1の値を足す
		return (float)(cosTable[cutDegree] +
			(cosTable[cutDegree + 1] - cosTable[cutDegree]) * cutDegreeF);
	}

private:

	static float sinTable[TABELE_MAX];
	static float cosTable[TABELE_MAX];
};

#endif

//-----------------------------------EOF---------------------------------------