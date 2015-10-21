//*****************************************************************************
//	フェードアウト処理処理 [ CFadeOut.cpp ]
//	Author : KOTARO NAGASAKI
//	create : 6/27
//	Update : 6/27
//*****************************************************************************

//*****************************************************************************
//	インクルード
//*****************************************************************************
#include "CManager.h"
#include "CFadeOut.h"
#include "CSceneManager.h"

//=============================================================================
//	コンストラクタ
//=============================================================================
CFadeOut::CFadeOut(OBJTYPE _objType, int _priority) : CObj2D(_objType, _priority)
{
	priority = _priority;
	objType = _objType;
}
//=============================================================================
//	デストラクタ
//=============================================================================
CFadeOut::~CFadeOut()
{
}
//=============================================================================
//	クリエイト処理
//=============================================================================
CFadeOut* CFadeOut::Create(LPDIRECT3DDEVICE9 _device,
	int _priority)
{
	CFadeOut* object = new CFadeOut(CObj::OBJTYPE_FADEOUT, _priority);

	object->device = _device;
	object->pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	object->size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	object->rot = VEC3_0;
	object->color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	object->texUV = TEXUV(0.0f, 0.0f, 1.0f, 1.0f);

	object->Init();

	return object;
}
//=============================================================================
//	初期化処理
//=============================================================================
void CFadeOut::Init()
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
		ASSERT("CFadeOutの　頂点バッファの作成失敗")
	}

	valueChangeFlag = true;
}
//=============================================================================
//	更新処理
//=============================================================================
void CFadeOut::Update()
{
	color.a -= 0.05f;
	valueChangeFlag = true;

	if (color.a <= 0.0f)
	{
		Release();
		CManager::GetSceneManager()->SetChangeFlag(true);
	}
}
//=============================================================================
//	描画処理
//=============================================================================
void CFadeOut::Draw()
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

//	EOF
