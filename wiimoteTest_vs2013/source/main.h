//*****************************************************************************
//	���C������ [main.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
//	�C���N���[�h�t�@�C��
//*****************************************************************************
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#define _AFX_SECURE_NO_WARNINGS
#define _ATL_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>
#include <Windowsx.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//	�x���΍��p
#include "dinput.h"
#include <stdio.h>
#include <mmsystem.h>
#include <process.h>
#include <assert.h>
#include <dshow.h>
#include "radianTable.h"
#include "texUV.h"
#include "CObj.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif

#ifdef _DEBUG

#include "CDebug.h"

#endif

//*****************************************************************************
//	���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib , "d3d9.lib")
#pragma comment (lib , "d3dx9.lib")
#pragma comment (lib , "dxguid.lib")
#pragma comment (lib , "dinput8.lib")
#pragma comment (lib , "winmm.lib")
#pragma comment (lib, "Strmiids.lib")

//*****************************************************************************
//	�}�N����`
//*****************************************************************************
//	�Q�c�|���S�����_�t�H�[�}�b�g(���_���W[2D] / ���ˌ� / �e�N�X�`�����W)
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//	�R�c�|���S�����_�t�H�[�}�b�g(���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W)
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//	int�l180��float�l1.57...�ւ̕ϊ�
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)

//	float�l1.57��int�l180...�ւ̕ϊ�
#define RAD_TO_DEG(_rad)	((_rad * 180.0f) / D3DX_PI)

#define SQUARE(_num)	(_num * _num)
#define CUBE(_num)	(_num * _num * _num)


//	�����_���Ł@(-_num <= �v�Z�l <= num)�@��Ԃ��}�N��
//	�n���l�́@1�ȏ���w�肷�邱��
#define RANDAM(_num)	((rand() % _num) - (rand() % _num))

#define VEC3_0	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
#define VEC4_0	(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))
#define COL4_0	(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))
#define COL4_1	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))


#define SCREEN_WIDTH	(1024.0f)
#define SCREEN_HEIGHT	(768.0f)

#define SAFE_RELEASE(p)	{if (p != nullptr) {(p)->Release();(p) = nullptr;}}
#define SAFE_RELEASE_ARRAY(p)\\
				{\\
		if (p != nullptr)\\
						{\\
			for (int arrayCount = 0; arrayCount < sizeof(p) / 4; arrayCount++)\\
									{\\
				(p[arrayCount])->Release();\\
				(p[arrayCount]) = nullptr;\\
									}\\
						}\\
				}

#define SAFE_DELETE(p)	{if (p != nullptr) {delete (p);(p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)\\
				{\\
		if (p != nullptr)\\
						{\\
			for (int arrayCount = 0; arrayCount < sizeof(p) / 4; arrayCount++)\\
									{\\
				delete (p[arrayCount]);\\
				(p[arrayCount]) = nullptr;\\
									}\\
						}\\
				}

//	���b�Z�[�W�{�b�N�X�̊ȈՍ쐬
//	�\������e�L�X�g���Z�b�g����
#define MESSAGE(message) MessageBox(NULL, message, "Message", MB_ICONWARNING);

//	�A�T�[�g���b�Z�[�W
#define ASSERT(message) MessageBoxA(NULL, message, "Message", MB_ICONWARNING); assert(false);

//*****************************************************************************
//	�\���̒�`
//*****************************************************************************
//	��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 vtx;	//	���_���W
	float rhw;			//	�e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;	//	���ˌ�
	D3DXVECTOR2 tex;	//	�e�N�X�`�����W
}VERTEX_2D;
//-----------------------------------------------------------------------------

//	��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 vtx;	//	���_���W
	D3DXVECTOR3 nor;	//	�@���x�N�g��
	D3DCOLOR diffuse;	//	���ˌ�
	D3DXVECTOR2 tex;	//	�e�N�X�`�����W
}VERTEX_3D;
//-----------------------------------------------------------------------------

#endif

//-----------------------------------EOF---------------------------------------