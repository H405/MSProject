//==============================================================================
//
// File   : ManagerTarget.cpp
// Brief  : �^�[�Q�b�g�Ǘ��I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerTarget.h"
#include "../framework/develop/Debug.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerTexture.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerTarget::ManagerTarget( void )
{
	// �N���X���̏���������
	InitializeSelf();
}
//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerTarget::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	target = nullptr;
}
//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ManagerTarget::~ManagerTarget( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int ManagerTarget::Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Texture* pTextureCross,
	Texture* pTextureArrow,
	Texture* pTextureCircle
	)
{
	//	�^�[�Q�b�g���w������p��
	target = new Target[TARGET_MAX];
	for(int count = 0;count < TARGET_MAX;count++)
	{
		target[count].Initialize(
			pDevice,
			pParameter,
			pEffectGeneral,
			pTextureCross,
			pTextureArrow,
			pTextureCircle);
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerTarget::Finalize( void )
{
	delete[] target;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}
//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ManagerTarget::Update( void )
{
	for( int counterPoint = 0; counterPoint < TARGET_MAX; ++counterPoint )
	{
		// �g�p����Ă��Ȃ��Ƃ�����
		if( !target[ counterPoint ].IsEnable() )
		{
			continue;
		}

		target[counterPoint].Update();
	}
}
//==============================================================================
// Brief  : �^�[�Q�b�g���ˏ���
// Return : void								: �Ȃ�
// Arg2   : D3DXVECTOR3							: �����ʒu
//==============================================================================
void ManagerTarget::Add(D3DXVECTOR3 _pos)
{
	int index = GetIndex();
	if(index < 0)
	{
		//PrintDebugWnd( _T( "�|�C���g�ɋ󂫂�����܂���B\n" ) );
		return;
	}

	//	�^�[�Q�b�g�̃Z�b�g
	target[index].Set(_pos);
}
//==============================================================================
// Brief  : �C���f�b�N�X�擾����
// Return : int									: �g�p�\�ȃI�u�W�F�N�g�̔ԍ��i�S���g�p���̏ꍇ�͕��̒l���Ԃ�j
// Arg    : void								: �Ȃ�
//==============================================================================
int ManagerTarget::GetIndex()
{
	// �󂫔ԍ���T��
	for( int counterPoint = 0; counterPoint < TARGET_MAX; ++counterPoint )
	{
		if( !target[ counterPoint ].IsEnable() )
		{
			return counterPoint;
		}
	}

	// �󂢂Ă��Ȃ�����
	return -1;
}
