//*****************************************************************************
//	���[�v�A�j���[�V�����p2D�|���S�� [CObj2DLoop.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "CObj2DLoop.h"


//	���������̃t�@�C����
//	������Author�ȊO�̕ύX�͋֎~�I�I
//	�������ύX���K�v�Ȍ�������ꍇ��Author�ɘA�����邱��

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CObj2DLoop::CObj2DLoop(OBJTYPE _objType, int _priority) : CObj2D(_objType, _priority)
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

	loopRateX = 0.0f;
	loopRateY = 0.0f;
	loopCountMax = 0;
	loopCount = 0;

	loopFlag = true;
	valueChangeFlag = false;
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CObj2DLoop::~CObj2DLoop()
{
	SAFE_RELEASE(vtxBuff);
}

//=============================================================================
//	�쐬����
//
//	�w��̈��������āA�l�̃Z�b�g�Ə��������s��
//	�Ԃ�l�Ƃ��āA�I�u�W�F�N�g�̃|�C���^��Ԃ�
//=============================================================================
CObj2DLoop* CObj2DLoop::Create(LPDIRECT3DDEVICE9 _device,
	float _loopRateX,
	float _loopRateY,
	int _loopCountMax,
	D3DXVECTOR3 _size,
	int _priority,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _rot,
	D3DXCOLOR _color,
	TEXUV _texUV)
{
	CObj2DLoop* object = new CObj2DLoop(CObj::OBJTYPE_2D, _priority);

	object->device = _device;
	object->size = _size;
	object->pos = _pos;
	object->rot = _rot;
	object->color = _color;
	object->texUV = _texUV;

	object->loopRateX = _loopRateX;
	object->loopRateY = _loopRateY;
	object->loopCountMax = _loopCountMax;

	object->Init();

	return object;
}

//=============================================================================
//	����������
//=============================================================================
void CObj2DLoop::Init()
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
		ASSERT("CObj2DLoop�@���_�o�b�t�@�̍쐬���s")
	}

	valueChangeFlag = true;
}

//=============================================================================
//	�|���S���̏���������
//=============================================================================
void CObj2DLoop::setVtxBuff()
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
//	�e�N�X�`��UV�l�܂�ߏ���
//=============================================================================
void CObj2DLoop::checkTexUV()
{
	if (texUV.left >= 1.0f)
	{
		texUV.left -= 1.0f;
		texUV.right -= 1.0f;
	}

	if (texUV.top >= 1.0f)
	{
		texUV.top -= 1.0f;
		texUV.bottom -= 1.0f;
	}

	if (texUV.left <= -1.0f)
	{
		texUV.left += 1.0f;
		texUV.right += 1.0f;
	}

	if (texUV.top <= -1.0f)
	{
		texUV.top += 1.0f;
		texUV.bottom += 1.0f;
	}
}

//=============================================================================
//	�X�V����
//=============================================================================
void CObj2DLoop::Update()
{
	if (loopFlag == true)
	{
		loopCount++;

		if (loopCount == loopCountMax)
		{
			texUV.left += loopRateX;
			texUV.right += loopRateX;

			texUV.top += loopRateY;
			texUV.bottom += loopRateY;

			//	�e�N�X�`��UV�l�̂܂�ߏ���
			checkTexUV();

			valueChangeFlag = true;

			loopCount = 0;
		}
	}
}

//=============================================================================
//	�`�揈��
//=============================================================================
void CObj2DLoop::Draw()
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