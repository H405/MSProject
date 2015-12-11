//==============================================================================
//
// File   : ObjectSkinMesh.cpp
// Brief  : �X�L�����b�V���I�u�W�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectSkinMesh.h"
#include "../graphic/graphic/GraphicSkinMesh.h"
#include "../framework/resource/Model.h"
#include "../framework/resource/Motion.h"

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
ObjectSkinMesh::ObjectSkinMesh( void ) : ObjectMovement()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectSkinMesh::~ObjectSkinMesh( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
// Arg    : int countMotion						: ���[�V������
//==============================================================================
int ObjectSkinMesh::Initialize( int priority, int countMotion )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	countMotion_ = countMotion;
	ppTableMotion_ = new Motion*[ countMotion ];
	for( int counterItem = 0; counterItem < countMotion; ++counterItem )
	{
		ppTableMotion_[ counterItem ] = nullptr;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectSkinMesh::Finalize( void )
{
	// �i�[�̈�̊J��
	delete[] ppTableMotion_;
	ppTableMotion_ = nullptr;

	delete[] pMatrixBoneCurrent_;
	pMatrixBoneCurrent_ = nullptr;

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
// Arg    : int countMotion						: ���[�V������
//==============================================================================
int ObjectSkinMesh::Reinitialize( int priority, int countMotion )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority, countMotion );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ObjectSkinMesh* pOut				: �R�s�[��A�h���X
//==============================================================================
int ObjectSkinMesh::Copy( ObjectSkinMesh* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectSkinMesh::Update( void )
{
	// �{�[���ϊ��s��̍X�V
	unsigned long	countBone;				// �{�[����
	D3DXMATRIX		matrixBoneMotion;		// ���[�V�����̃{�[���ϊ��s��
	countBone = pModel_->GetCountBone();
	for( unsigned int counterBone = 0; counterBone < countBone; ++counterBone )
	{
		pModel_->GetMatrixBone( counterBone, &pMatrixBoneCurrent_[ counterBone ] );
	}
	if( indexMotionNext_ >= 0 )
	{
		// �������������߂�
		float	proportion;		// ��������
		if( indexFrame_ <= indexFrameBeginBlend_ || indexMotionNext_ < 0 )
		{
			proportion = 0.0f;
		}
		else
		{
			proportion = static_cast< float >( indexFrame_ - indexFrameBeginBlend_ ) / countFrameBlend_;
		}

		// �{�[���ϊ��s����v�Z
		for( unsigned int counterBone = 0; counterBone < countBone; ++counterBone )
		{
			ppTableMotion_[ indexMotionCurrent_ ]->GetMatrixBone( indexFrame_, counterBone, &matrixBoneMotion );
			if( proportion > 0.0f && indexMotionNext_ >= 0 )
			{
				D3DXMATRIX	matrixBoneNext;		// ���̃��[�V�����̃{�[���ϊ��s��
				ppTableMotion_[ indexMotionNext_ ]->GetMatrixBone( indexFrame_, counterBone, &matrixBoneNext );
				matrixBoneMotion *= 1.0f - proportion;
				matrixBoneMotion += proportion * matrixBoneNext;
			}
		}
	}
	else
	{
		for( unsigned int counterBone = 0; counterBone < countBone; ++counterBone )
		{
			ppTableMotion_[ indexMotionCurrent_ ]->GetMatrixBone( indexFrame_, counterBone, &matrixBoneMotion );
			D3DXMatrixMultiply( &pMatrixBoneCurrent_[ counterBone ], &pMatrixBoneCurrent_[ counterBone ], &matrixBoneMotion );
		}
	}

	// �t���[����i�߂�
	if( countMotion_ > 0 )
	{
		++indexFrame_;
		if( static_cast< unsigned int >( indexFrame_ ) >= ppTableMotion_[ indexMotionCurrent_ ]->GetCountFrame() )
		{
			indexFrame_ = 0;
			if( indexMotionNext_ >= 0 )
			{
				indexMotionCurrent_ = indexMotionNext_;
			}
		}
	}

	// ��{�N���X�̏���
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : �`��N���X�̐���
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : Model* pModel						: ���f��
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : Effect* pEffectReflect				: ���˕`��G�t�F�N�g
// Arg    : Effect* pEffectShadow				: �e�`��G�t�F�N�g
// Arg    : Effect* pEffectParaboloid			: �����ϊ��`��G�t�F�N�g
//==============================================================================
int ObjectSkinMesh::CreateGraphic( int priority, Model* pModel, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow, Effect* pEffectParaboloid )
{
	// �����o�ϐ��̐ݒ�
	pModel_ = pModel;

	// �{�[���ϊ��s��̊i�[�̈���m��
	int		countBone;		// �{�[����
	countBone = pModel->GetCountBone();
	pMatrixBoneCurrent_ = new D3DXMATRIX[ countBone ];
	for( int counterItem = 0; counterItem < countBone; ++counterItem )
	{
		D3DXMatrixIdentity( &pMatrixBoneCurrent_[ counterItem ] );
	}

	// �O���t�B�b�N�̐���
	int		result;		// ���s����
	pGraphic_ = new GraphicSkinMesh();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, pEffectReflect, pEffectShadow, pEffectParaboloid,
		pModel, countBone, pMatrixBoneCurrent_ );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// �l�̕ԋp
	return 0;
}

//==============================================================================
// Brief  : ���̃��[�V������ݒ�
// Return : void								: �Ȃ�
// Arg    : int indexMotion						: ���̃��[�V�����ԍ�
// Arg    : int timeBeginBlend					: �u�����h�J�n����
// Arg    : int timeBlend						: �u�����h����
//==============================================================================
void ObjectSkinMesh::SetNextMotion( int indexMotion, int timeBeginBlend, int timeBlend )
{
	// �����o�ϐ��̐ݒ�
	indexMotionNext_ = indexMotion;
	indexFrameBeginBlend_ = timeBeginBlend;
	countFrameBlend_ = timeBlend;

	// �u�����h�J�n���Ԃ̏C��
	int		timeMotionCurrent;		// ���݂̃��[�V�����̎���
	timeMotionCurrent = ppTableMotion_[ indexMotionCurrent_ ]->GetCountFrame();
	if( timeBeginBlend == -1 )
	{
		indexFrameBeginBlend_ = timeMotionCurrent - timeBlend;
	}
	if( timeBeginBlend < 0 )
	{
		timeBeginBlend = 0;
	}

	// �u�����h���Ԃ̏C��
	if( timeBeginBlend + timeBlend > timeMotionCurrent )
	{
		timeBlend = timeMotionCurrent - timeBeginBlend;
	}
}

//==============================================================================
// Brief  : �u�����h��������
// Return : bool								: �u�����h�����ǂ���
// Arg    : void								: �Ȃ�
//==============================================================================
bool ObjectSkinMesh::IsBlending( void )
{
	// �l�̕ԋp
	return (indexFrame_ >= indexFrameBeginBlend_ ? true : false);
}

//==============================================================================
// Brief  : ���[�V�����e�[�u���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int index							: �ݒ肷��ԍ�
// Arg    : Motion* pValue						: �ݒ肷��l
//==============================================================================
void ObjectSkinMesh::SetTableMotion( int index, Motion* pValue )
{
	// �l�̐ݒ�
	ppTableMotion_[ index ] = pValue;
}

//==============================================================================
// Brief  : ���[�V�����e�[�u���̎擾
// Return : Motion*								: �ԋp����l
// Arg    : int index							: �ݒ肷��ԍ�
//==============================================================================
Motion* ObjectSkinMesh::GetTableMotion( int index ) const
{
	// �l�̕ԋp
	return ppTableMotion_[ index ];
}

//==============================================================================
// Brief  : ���݂̃��[�V�����ԍ��̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectSkinMesh::GetIndexMotionCurrent( void ) const
{
	// �l�̕ԋp
	return indexMotionCurrent_;
}

//==============================================================================
// Brief  : ���̃��[�V�����ԍ��̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectSkinMesh::GetIndexMotionNext( void ) const
{
	// �l�̕ԋp
	return indexMotionNext_;
}

//==============================================================================
// Brief  : �t���[���ԍ��̎擾
// Return : int									: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectSkinMesh::GetIndexFrame( void ) const
{
	// �l�̕ԋp
	return indexFrame_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectSkinMesh::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pGraphic_ = nullptr;
	pModel_ = nullptr;
	ppTableMotion_ = nullptr;
	pMatrixBoneCurrent_ = nullptr;
	countMotion_ = 0;
	indexMotionCurrent_ = 0;
	indexMotionNext_ = -1;
	indexFrame_ = 0;
	indexFrameBeginBlend_ = 0;
	countFrameBlend_ = 0;
}
