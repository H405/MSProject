//*****************************************************************************
//	�L�[�t���[���A�j���[�V�����p2D�|���S�� [CObj2DKeyFrame.cpp]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "CObj2DKeyFrame.h"


//	���������̃t�@�C����
//	������Author�ȊO�̕ύX�͋֎~�I�I
//	�������ύX���K�v�Ȍ�������ꍇ��Author�ɘA�����邱��

//=============================================================================
//	�R���X�g���N�^
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
//	�f�X�g���N�^
//=============================================================================
CObj2DKeyFrame::~CObj2DKeyFrame()
{
	SAFE_RELEASE(vtxBuff);
}

//=============================================================================
//	�쐬����
//
//	�w��̈��������āA�l�̃Z�b�g�Ə��������s��
//	�Ԃ�l�Ƃ��āA�I�u�W�F�N�g�̃|�C���^��Ԃ�
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
//	����������
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
		ASSERT("CObj2DKeyFrame�@���_�o�b�t�@�̍쐬���s")
	}

	valueChangeFlag = true;
}

//=============================================================================
//	�|���S���̏���������
//=============================================================================
void CObj2DKeyFrame::setVtxBuff()
{
	VERTEX_2D* temporaryPointer;

	//	�|���S���̃T�C�Y��ύX����O�ɁA�Ίp���̒����Ɛ����p�x���Čv�Z����
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
//	�e�N�X�`��UV�l�܂�ߏ���
//=============================================================================
void CObj2DKeyFrame::checkTexUV()
{
	texUV.left = keyRate * keyNum;
	texUV.right = keyRate * keyNum + keyRate;
}

//=============================================================================
//	�X�V����
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

			//	�e�N�X�`��UV�l�̂܂�ߏ���
			checkTexUV();

			valueChangeFlag = true;

			keyCount = 0;
		}
	}
}

//=============================================================================
//	�`�揈��
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