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
	static float mySinf(double _degree)
	{
		double cutDegreeN;	//	�����_�ȉ���؂�̂Ă��l���i�[
		double cutDegreeF;	//	�����_�ȉ��̒l���i�[
		int cutDegree;	//	�v�Z�p�����l

		//	�����_�ȉ��ƁA���̐��������擾
		cutDegreeF = modf(_degree, &cutDegreeN);

		//	360�x�ȉ��Ɋۂߍ���
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

		//_degree�� 90.1 �̏ꍇ�E�E�E
		//sinTable[90]�̒l�ɁA(sinTable[91] - sinTable[90]) �~ 0.1�̒l�𑫂�
		return (float)(sinTable[cutDegree] + 
			(sinTable[cutDegree + 1] - sinTable[cutDegree]) * cutDegreeF);
	}

	//=============================================================================
	//	cos�l�̃Q�b�^�[
	//
	//	�����̓f�B�O���[�p���w��
	//=============================================================================
	static float myCosf(double _degree)
	{
		double cutDegreeN;	//	�����_�ȉ���؂�̂Ă��l���i�[
		double cutDegreeF;	//	�����_�ȉ��̒l���i�[
		int cutDegree;	//	�v�Z�p�����l

		//	�����_�ȉ��ƁA���̐��������擾
		cutDegreeF = modf(_degree, &cutDegreeN);

		//	360�x�ȉ��Ɋۂߍ���
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

		//_degree�� 90.1 �̏ꍇ�E�E�E
		//cosTable[90]�̒l�ɁA(cosTable[91] - cosTable[90]) �~ 0.1�̒l�𑫂�
		return (float)(cosTable[cutDegree] +
			(cosTable[cutDegree + 1] - cosTable[cutDegree]) * cutDegreeF);
	}

private:

	static float sinTable[TABELE_MAX];
	static float cosTable[TABELE_MAX];
};

#endif

//-----------------------------------EOF---------------------------------------