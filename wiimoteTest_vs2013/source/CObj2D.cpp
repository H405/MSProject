//*****************************************************************************
//	2Dポリゴン [CObj2D.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "CObj2D.h"


//	※※※このファイルは
//	※※※Author以外の変更は禁止！！
//	※※※変更が必要な個所がある場合はAuthorに連絡すること

//=============================================================================
//	コンストラクタ
//=============================================================================
CObj2D::CObj2D(OBJTYPE _objType, int _priority) : CObj(_objType, _priority)
{
	device = nullptr;
	vtxBuff = nullptr;
	texture.texData = nullptr;
	pos = VEC3_0;
	rot = VEC3_0;
	size = VEC3_0;
	color = COL4_1;
	texUV = TEXUV(0.0f, 0.0f, 1.0f, 1.0f);
	diagonalAngle = 0.0f;
	diagonalLength = 0.0f;

	drawflag = true;
	valueChangeFlag = false;
}
//=============================================================================
//	デストラクタ
//=============================================================================
CObj2D::~CObj2D()
{
	SAFE_RELEASE(vtxBuff);
}

//=============================================================================
//	作成処理
//
//	指定の引数を入れて、値のセットと初期化を行う
//	返り値として、オブジェクトのポインタを返す
//=============================================================================
CObj2D* CObj2D::Create(LPDIRECT3DDEVICE9 _device,
	D3DXVECTOR3 _size,
	int _priority,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _rot,
	D3DXCOLOR _color,
	TEXUV _texUV)
{
	CObj2D* object = new CObj2D(CObj::OBJTYPE_2D, _priority);

	object->device = _device;
	object->size = _size;
	object->pos = _pos;
	object->rot = _rot;
	object->color = _color;
	object->texUV = _texUV;

	object->Init();

	return object;
}

//=============================================================================
//	初期化処理
//=============================================================================
void CObj2D::Init()
{
	HRESULT result =
		device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&vtxBuff,
									NULL);

	if (result == E_FAIL)
	{
		ASSERT("CObj2D　頂点バッファの作成失敗")
	}

	valueChangeFlag = true;
}

//=============================================================================
//	ポリゴンの初期化処理
//=============================================================================
void CObj2D::setVtxBuff()
{
	VERTEX_2D* temporaryPointer;

	//	ポリゴンのサイズを変更する前に、対角線の長さと成す角度を再計算する
	diagonalAngle = RAD_TO_DEG(atan2f(size.y, size.x));
	diagonalLength = sqrtf(SQUARE(size.x * 0.5f) + SQUARE(size.y * 0.5f));

	vtxBuff->Lock(0,
		0,
		reinterpret_cast<void **>(&temporaryPointer),
		0);

	temporaryPointer[0].vtx = 
		D3DXVECTOR3(
			pos.x - (CRadianTable::myCosf(-diagonalAngle + rot.z)) * diagonalLength,
			pos.y - (CRadianTable::mySinf(-diagonalAngle + rot.z)) * diagonalLength,
			0.0f);
	temporaryPointer[0].rhw = 1.0f;
	temporaryPointer[0].diffuse = color;
	temporaryPointer[0].tex = D3DXVECTOR2(texUV.left, texUV.bottom);



	temporaryPointer[1].vtx =
		D3DXVECTOR3(
			pos.x - (CRadianTable::myCosf(diagonalAngle + rot.z)) * diagonalLength,
			pos.y - (CRadianTable::mySinf(diagonalAngle + rot.z)) * diagonalLength,
			0.0f);
	temporaryPointer[1].rhw = 1.0f;
	temporaryPointer[1].diffuse = color;
	temporaryPointer[1].tex = D3DXVECTOR2(texUV.left, texUV.top);



	temporaryPointer[2].vtx =
		D3DXVECTOR3(
			pos.x + (CRadianTable::myCosf(diagonalAngle + rot.z)) * diagonalLength,
			pos.y + (CRadianTable::mySinf(diagonalAngle + rot.z)) * diagonalLength,
			0.0f);
	temporaryPointer[2].rhw = 1.0f;
	temporaryPointer[2].diffuse = color;
	temporaryPointer[2].tex = D3DXVECTOR2(texUV.right, texUV.bottom);




	temporaryPointer[3].vtx =
		D3DXVECTOR3(
			pos.x + (CRadianTable::myCosf(-diagonalAngle + rot.z)) * diagonalLength,
			pos.y + (CRadianTable::mySinf(-diagonalAngle + rot.z)) * diagonalLength,
			0.0f);
	temporaryPointer[3].rhw = 1.0f;
	temporaryPointer[3].diffuse = color;
	temporaryPointer[3].tex = D3DXVECTOR2(texUV.right, texUV.top);



	vtxBuff->Unlock();
}

//=============================================================================
//	テクスチャの初期化処理
//=============================================================================
void CObj2D::setTexture(char* _textureName)
{
	HRESULT result = 
		D3DXCreateTextureFromFile(device,
								_textureName,
								&texture.texData);

	if (result == E_FAIL)
	{
		ASSERT("CObj2D　texture読み込み失敗");
	}
}
//=============================================================================
//	テクスチャの初期化処理
//=============================================================================
void CObj2D::setTexture(CTextures::TEXTURE_TYPE _texType)
{
	texture = *CTextures::GetTexture(_texType);

	if (texture.texData == NULL)
	{
		ASSERT("CObj2D　texture読み込み失敗");
	}
}

//=============================================================================
//	更新処理
//=============================================================================
void CObj2D::Update()
{
}

//=============================================================================
//	描画処理
//=============================================================================
void CObj2D::Draw()
{
	if (drawflag == true)
	{
		if (valueChangeFlag == true)
		{
			setVtxBuff();
			valueChangeFlag = false;
		}

		device->SetStreamSource(0,
			vtxBuff,
			0,
			sizeof(VERTEX_2D));

		device->SetFVF(FVF_VERTEX_2D);

		device->SetTexture(0, texture.texData);

		device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//-----------------------------------EOF---------------------------------------