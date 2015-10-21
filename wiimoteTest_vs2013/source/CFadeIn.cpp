//*****************************************************************************
//	�t�F�[�h�C���������� [ CFadeIn.cpp ]
//	Author : KOTARO NAGASAKI
//	create : 6/27
//	Update : 6/27
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h
//*****************************************************************************
#include "CManager.h"
#include "CFadeIn.h"
#include "CSceneManager.h"

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CFadeIn::CFadeIn( OBJTYPE _objType , int _priority ) : CObj2D( _objType , _priority )
{
	priority = _priority;
	objType = _objType;
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CFadeIn::~CFadeIn(  )
{
}
//=============================================================================
//	�N���G�C�g����
//=============================================================================
CFadeIn* CFadeIn::Create( LPDIRECT3DDEVICE9 _device ,
						  int _priority )
{
	CFadeIn* object = new CFadeIn( CObj::OBJTYPE_FADEIN , _priority );

	object->device = _device;
	object->pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	object->size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	object->rot= VEC3_0;
	object->color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	object->texUV = TEXUV(0.0f, 0.0f, 1.0f, 1.0f);

	object->Init();

	return object;
}
//=============================================================================
//	����������
//=============================================================================
void CFadeIn::Init()
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
		ASSERT("CFadeIn�́@���_�o�b�t�@�̍쐬���s")
	}

	valueChangeFlag = true;
}
//=============================================================================
//	�X�V����
//=============================================================================
void CFadeIn::Update(  )
{
	color.a += 0.05f;
	valueChangeFlag = true;
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CFadeIn::Draw(  )
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


	if (color.a >= 1.0f)
	{
		Release();
		CManager::GetSceneManager()->SetChangeFlag(true);
	}
}

//	EOF
