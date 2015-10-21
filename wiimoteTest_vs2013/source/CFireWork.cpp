//*****************************************************************************
//	2D�|���S�� [CFireWork.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "CFireWork.h"


//	���������̃t�@�C����
//	������Author�ȊO�̕ύX�͋֎~�I�I
//	�������ύX���K�v�Ȍ�������ꍇ��Author�ɘA�����邱��

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CFireWork::CFireWork(OBJTYPE _objType, int _priority) : CObj2D(_objType, _priority)
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
//	�f�X�g���N�^
//=============================================================================
CFireWork::~CFireWork()
{
	SAFE_RELEASE(vtxBuff);
}

//=============================================================================
//	�쐬����
//
//	�w��̈��������āA�l�̃Z�b�g�Ə��������s��
//	�Ԃ�l�Ƃ��āA�I�u�W�F�N�g�̃|�C���^��Ԃ�
//=============================================================================
CFireWork* CFireWork::Create(
	LPDIRECT3DDEVICE9 _device,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _vec,
	int _type)
{
	CFireWork* object = new CFireWork(CObj::OBJTYPE_FIREWORK, 3);

	object->device = _device;
	object->size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	object->pos = _pos;
	object->vec = _vec;

	object->Init();

	object->setTexture(CTextures::TEXTURE_TEST);

	return object;
}

//=============================================================================
//	����������
//=============================================================================
void CFireWork::Init()
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
		ASSERT("CFireWork�@���_�o�b�t�@�̍쐬���s")
	}

	valueChangeFlag = true;
}

//=============================================================================
//	�|���S���̏���������
//=============================================================================
void CFireWork::setVtxBuff()
{
	VERTEX_2D* temporaryPointer;

	//	�|���S���̃T�C�Y��ύX����O�ɁA�Ίp���̒����Ɛ����p�x���Čv�Z����
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
//	�X�V����
//=============================================================================
void CFireWork::Update()
{
	if (pos.y < 0.0f)
		Release();

	pos += vec;
	setVtxBuff();
}

//=============================================================================
//	����
//=============================================================================
void CFireWork::Fire()
{
	Release();
}

//=============================================================================
//	�`�揈��
//=============================================================================
void CFireWork::Draw()
{
	if (drawflag == true)
	{

		//	���Z����
		device->SetRenderState(D3DRS_BLENDOP,
			D3DBLENDOP_ADD);
		device->SetRenderState(D3DRS_SRCBLEND,
			D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND,
			D3DBLEND_ONE);


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

		// �ʏ퍇��
		device->SetRenderState(D3DRS_BLENDOP,
			D3DBLENDOP_ADD);
		device->SetRenderState(D3DRS_SRCBLEND,
			D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND,
			D3DBLEND_INVSRCALPHA);
	}
}

//-----------------------------------EOF---------------------------------------