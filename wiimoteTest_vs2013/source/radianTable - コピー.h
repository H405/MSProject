//*****************************************************************************
//	sin,cos�v�Z�p [radianTable.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _CRADIAN_TABLE_H_
#define _CRADIAN_TABLE_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "fileReader.h"
#include "main.h"

//*****************************************************************************
//	�萔��`
//*****************************************************************************
#define TABELE_MAX (361)

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class CRadianTable
{
public:

	CRadianTable(){};
	~CRadianTable(){};
	static void Init();

	//=============================================================================
	//	sin�l�̃Q�b�^�[
	//
	//	�����̓f�B�O���[�p���w��
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
			//	-�l���{�l�Ƃ��Ĉ���
			_degree += 360;
		}

		//_degree�� 90.1 �̏ꍇ�E�E�E
		//sinTable[90]�̒l�ɁA(sinTable[91] - sinTable[90]) �~ 0.1�̒l�𑫂�
		cutDegree = (int)floor(_degree);
		downValue = sinTable[cutDegree];
		upValue = sinTable[cutDegree + 1];

		sinValue = downValue + ((upValue - downValue) * (_degree - cutDegree));

		return sinValue;
	}

	//=============================================================================
	//	cos�l�̃Q�b�^�[
	//
	//	�����̓f�B�O���[�p���w��
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
			//	-�l���{�l�Ƃ��Ĉ���
			_degree += 360;
		}

		//_degree�� 90.1 �̏ꍇ�E�E�E
		//cosTable[90]�̒l�ɁA(cosTable[91] - cosTable[90]) �~ 0.1�̒l�𑫂�
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