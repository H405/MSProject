//*****************************************************************************
//	 [textures.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CTextures
{
public:
	//*****************************************************************************
	//	列挙体定義
	//*****************************************************************************
	typedef enum
	{
		TEXTYPE_NONE = 0,
		TEXTURE_TEST,
		TEXTYPE_MAX
	}TEXTURE_TYPE;

	//*****************************************************************************
	//	関数定義
	//*****************************************************************************
	CTextures(){};
	~CTextures(){};
	void LoadTexture(LPDIRECT3DDEVICE9 _device, int _num);
	static void Init(LPDIRECT3DDEVICE9 _device);
	static void Uninit();
	static CTextures* GetTexture(TEXTURE_TYPE _textureNum);

	//*****************************************************************************
	//	変数定義
	//*****************************************************************************
	LPDIRECT3DTEXTURE9 texData;	//	テクスチャデータ

private:

	//*****************************************************************************
	//	変数定義
	//*****************************************************************************
	static CTextures textureInfo[TEXTYPE_MAX];	//	テクスチャ情報
};

#endif
//-----------------------------------EOF---------------------------------------