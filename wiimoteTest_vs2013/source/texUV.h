//*****************************************************************************
//	�e�N�X�`��UV�l [texUV.h]
//	Author : KOTARO NAGASAKI
//	create : 4/15
//	Update : 4/15
//*****************************************************************************
#ifndef _TEXUV_H_
#define _TEXUV_H_

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class TEXUV
{
public:

	TEXUV();
	TEXUV(float _left , float _top , float _right , float _bottom);
	~TEXUV();

	TEXUV operator=(const TEXUV& _texUV);

	TEXUV operator+(const TEXUV& _texUV);
	TEXUV operator+=(const TEXUV& _texUV);
	TEXUV operator++();
	TEXUV operator++(int);

	TEXUV operator-(const TEXUV& _texUV);
	TEXUV operator-=(const TEXUV& _texUV);
	TEXUV operator--();
	TEXUV operator--(int);

	TEXUV operator*(const float _num);
	TEXUV operator*=(const float _num);

	TEXUV operator/(const float _num);
	TEXUV operator/=(const float _num);

	float left;
	float top;
	float right;
	float bottom;
};

#define UV_DEF TEXUV(0.0f , 0.0f ,1.0f , 1.0f)

#endif

//-----------------------------------EOF---------------------------------------