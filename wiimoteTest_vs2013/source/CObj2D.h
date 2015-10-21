//*****************************************************************************
// 2Dポリゴン [CObj2D.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _COBJ2D_H_
#define _COBJ2D_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"
#include "CObj.h"
#include "textures.h"

//	※※※このファイルは
//	※※※Author以外の変更は禁止！！
//	※※※変更が必要な個所がある場合はAuthorに連絡すること

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class CObj2D : public CObj
{
public:
	CObj2D(OBJTYPE _objType, int _priority);
	virtual ~CObj2D();
	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//=============================================================================
	//	作成代理処理
	//
	//	サイズの指定はポリゴンの全長を指定する
	//	画面いっぱいのポリゴンを作りたいときは　SCREE_WIDTH(SCREEN_HEIGHT)　を指定する
	//
	//	posはデフォルトで画面の中心
	//	rot,colorはそれぞれ、0.0fと1.0fで初期化
	//	テクスチャUV値はデフォルト値 (L:0.0   T:0.0   R:1.0   B:1.0)
	//=============================================================================
	static CObj2D* Create(LPDIRECT3DDEVICE9 _device,
		D3DXVECTOR3 _size,
		int _priority,
		D3DXVECTOR3 _pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3 _rot = VEC3_0,
		D3DXCOLOR _color = COL4_1,
		TEXUV _texUV = UV_DEF);

	virtual void setVtxBuff();

	//	セッター
	//-------------------------------------------------
	virtual void setTexture(char* _textureName);
	virtual void setTexture(CTextures::TEXTURE_TYPE _texType);
	virtual void setPos(D3DXVECTOR3 _pos)
	{
		pos = _pos;
		valueChangeFlag = true;
	}
	virtual void addPos(D3DXVECTOR3 _pos)
	{
		pos += _pos;
		valueChangeFlag = true;
	}
	virtual void subPos(D3DXVECTOR3 _pos)
	{
		pos -= _pos;
		valueChangeFlag = true;
	}
	virtual void setRot(D3DXVECTOR3 _rot)
	{
		rot = _rot;
		valueChangeFlag = true;
	}
	virtual void addRot(D3DXVECTOR3 _rot)
	{
		rot += _rot;
		valueChangeFlag = true;
	}
	virtual void subRot(D3DXVECTOR3 _rot)
	{
		rot -= _rot;
		valueChangeFlag = true;
	}
	virtual void setSize(D3DXVECTOR3 _size)
	{
		size = _size;
		valueChangeFlag = true;
	}
	virtual void addSize(D3DXVECTOR3 _size)
	{
		size += _size;
		valueChangeFlag = true;
	}
	virtual void subSize(D3DXVECTOR3 _size)
	{
		size -= _size;
		valueChangeFlag = true;
	}
	virtual void setColor(D3DXCOLOR _color)
	{
		color = _color;
		valueChangeFlag = true;
	}
	virtual void addColor(D3DXCOLOR _color)
	{
		color += _color;
		valueChangeFlag = true;
	}
	virtual void subColor(D3DXCOLOR _color)
	{
		color -= _color;
		valueChangeFlag = true;
	}
	void setDrawFlag(bool _setFlag)
	{
		drawflag = _setFlag;
	}
	//-------------------------------------------------

	//	ゲッター
	//-------------------------------------------------
	virtual D3DXVECTOR3 getPos()
	{
		return pos;
	}
	virtual D3DXVECTOR3 getRot()
	{
		return rot;
	}
	virtual D3DXVECTOR3 getSize()
	{
		return size;
	}
	virtual D3DXCOLOR getColor()
	{
		return color;
	}
	bool getDrawFlag()
	{
		return drawflag;
	}
	//-------------------------------------------------

protected:

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	CTextures texture;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 size;
	D3DXCOLOR color;
	TEXUV texUV;

	float diagonalAngle;
	float diagonalLength;
	bool drawflag;
	bool valueChangeFlag;
};

#endif

//-----------------------------------EOF---------------------------------------