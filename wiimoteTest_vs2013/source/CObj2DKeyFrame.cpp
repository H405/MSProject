//*****************************************************************************
//	キーフレームアニメーション用2Dポリゴン [CObj2DKeyFrame.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "CObj2DKeyFrame.h"


//	※※※このファイルは
//	※※※Author以外の変更は禁止！！
//	※※※変更が必要な個所がある場合はAuthorに連絡すること

//=============================================================================
//	コンストラクタ
//=============================================================================
CObj2DKeyFrame::CObj2DKeyFrame(OBJTYPE _objType, int _priority) : CObj2D(_objType, _priority)
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

	keyRate = 0.0f;
	keyMax = 0;
	keyNum = 0;
	keyCountMax = 0;
	keyCount = 0;
	keyFlag = true;
}
//=============================================================================
//	デストラクタ
//=============================================================================
CObj2DKeyFrame::~CObj2DKeyFrame()
{
	SAFE_RELEASE(vtxBuff);
}

//=============================================================================
//	作成処理
//
//	指定の引数を入れて、値のセットと初期化を行う
//	返り値として、オブジェクトのポインタを返す
//=============================================================================
CObj2DKeyFrame* CObj2DKeyFrame::Create(LPDIRECT3DDEVICE9 _device,
	int _keyMax,
	int _keyCountMax,
	D3DXVECTOR3 _size,
	int _priority,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _rot,
	D3DXCOLOR _color,
	TEXUV _texUV)
{
	CObj2DKeyFrame* object = new CObj2DKeyFrame(CObj::OBJTYPE_2D, _priority);

	object->device = _device;
	object->size = _size;
	object->pos = _pos;
	object->rot = _rot;
	object->color = _color;
	object->texUV = _texUV;

	object->keyMax = _keyMax;
	object->keyRate = 1.0f / _keyMax;
	object->keyCountMax = _keyCountMax;

	object->checkTexUV();

	object->Init();

	return object;
}

//=============================================================================
//	初期化処理
//=============================================================================
void CObj2DKeyFrame::Init()
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
		ASSERT("CObj2DKeyFrame　頂点バッファの作成失敗")
	}

	valueChangeFlag = true;
}

//=============================================================================
//	ポリゴンの初期化処理
//=============================================================================
void CObj2DKeyFrame::setVtxBuff()
{
	VERTEX_2D* temporaryPointer;

	//	ポリゴンのサイズを変更する前に、対角線の長さと成す角度を再計算する
	diagonalAngle = RAD_TO_DEG(atan2f(size.y, size.x));
	diagonalLength = sqrtf(SQUARE(size.x * 0.5f) + SQUARE(size.y * 0.5f));

	vtxBuff->Lock(0,
		0,
		reinterpret_cast<void **>(&temporaryPointer),
		0);

	/*temporaryPointer[0].vtx = 
		D3DXVECTOR3(pos.x - (CRadianTable::myCosf(-diagonalAngle + rot.z)) * diagonalLength,
			pos.y - (CRadianTable::mySinf(-diagonalAngle + rot.z)) * diagonalLength,
			0.0f);
	temporaryPointer[0].rhw = 1.0f;
	temporaryPointer[0].diffuse = color;
	temporaryPointer[0].tex = D3DXVECTOR2(texUV.left, texUV.bottom);



	temporaryPointer[1].vtx =
		D3DXVECTOR3(pos.x - (CRadianTable::myCosf(diagonalAngle + rot.z)) * diagonalLength,
		pos.y - (CRadianTable::mySinf(diagonalAngle + rot.z)) * diagonalLength,
		0.0f);
	temporaryPointer[1].rhw = 1.0f;
	temporaryPointer[1].diffuse = color;
	temporaryPointer[1].tex = D3DXVECTOR2(texUV.left, texUV.top);



	temporaryPointer[2].vtx =
		D3DXVECTOR3(pos.x + (CRadianTable::myCosf(diagonalAngle + rot.z)) * diagonalLength,
		pos.y + (CRadianTable::mySinf(diagonalAngle + rot.z)) * diagonalLength,
		0.0f);
	temporaryPointer[2].rhw = 1.0f;
	temporaryPointer[2].diffuse = color;
	temporaryPointer[2].tex = D3DXVECTOR2(texUV.right, texUV.bottom);




	temporaryPointer[3].vtx =
		D3DXVECTOR3(pos.x + (CRadianTable::myCosf(-diagonalAngle + rot.z)) * diagonalLength,
		pos.y + (CRadianTable::mySinf(-diagonalAngle + rot.z)) * diagonalLength,
		0.0f);
	temporaryPointer[3].rhw = 1.0f;
	temporaryPointer[3].diffuse = color;
	temporaryPointer[3].tex = D3DXVECTOR2(texUV.right, texUV.top);*/
	





	temporaryPointer[0].vtx =
		D3DXVECTOR3(pos.x - (CRadianTable::myCosf(-diagonalAngle + rot.z)) * diagonalLength,
		pos.y - (CRadianTable::mySinf(-diagonalAngle + rot.z)) * diagonalLength,
		0.0f);
	temporaryPointer[0].rhw = 1.0f;
	temporaryPointer[0].diffuse = color;
	temporaryPointer[0].tex = D3DXVECTOR2(texUV.left, texUV.bottom);



	temporaryPointer[1].vtx =
		D3DXVECTOR3(pos.x - (CRadianTable::myCosf(diagonalAngle + rot.z)) * diagonalLength,
		pos.y - (CRadianTable::mySinf(diagonalAngle + rot.z)) * diagonalLength,
		0.0f);
	temporaryPointer[1].rhw = 1.0f;
	temporaryPointer[1].diffuse = color;
	temporaryPointer[1].tex = D3DXVECTOR2(texUV.left, texUV.top);



	temporaryPointer[2].vtx =
		D3DXVECTOR3(pos.x + (CRadianTable::myCosf(diagonalAngle + rot.z)) * diagonalLength,
		pos.y + (CRadianTable::mySinf(diagonalAngle + rot.z)) * diagonalLength,
		0.0f);
	temporaryPointer[2].rhw = 1.0f;
	temporaryPointer[2].diffuse = color;
	temporaryPointer[2].tex = D3DXVECTOR2(texUV.right, texUV.bottom);




	temporaryPointer[3].vtx =
		D3DXVECTOR3(pos.x + (CRadianTable::myCosf(-diagonalAngle + rot.z)) * diagonalLength,
		pos.y + (CRadianTable::mySinf(-diagonalAngle + rot.z)) * diagonalLength,
		0.0f);
	temporaryPointer[3].rhw = 1.0f;
	temporaryPointer[3].diffuse = color;
	temporaryPointer[3].tex = D3DXVECTOR2(texUV.right, texUV.top);





	vtxBuff->Unlock();
}

//=============================================================================
//	テクスチャUV値まるめ処理
//=============================================================================
void CObj2DKeyFrame::checkTexUV()
{
	texUV.left = keyRate * keyNum;
	texUV.right = keyRate * keyNum + keyRate;
}

//=============================================================================
//	更新処理
//=============================================================================
void CObj2DKeyFrame::Update()
{
	if (keyFlag == true)
	{
		keyCount++;

		if (keyCount == keyCountMax)
		{
			keyNum++;

			if (keyNum == keyMax)
			{
				keyNum = 0;
			}

			//	テクスチャUV値のまるめ処理
			checkTexUV();

			valueChangeFlag = true;

			keyCount = 0;
		}
	}
}

//=============================================================================
//	描画処理
//=============================================================================
void CObj2DKeyFrame::Draw()
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