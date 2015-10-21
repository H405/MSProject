//==============================================================================
//
// File   : Effect.cpp
// Brief  : �G�t�F�N�g�N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/16 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "Effect.h"
#include "../develop/Debug.h"

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
Effect::Effect( void )
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
Effect::~Effect( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : ID3DXEffect* pEffect				: �G�t�F�N�g
//==============================================================================
int Effect::Initialize( ID3DXEffect* pEffect )
{
	// �����o�ϐ��̐ݒ�
	pEffect_ = pEffect;

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int Effect::Finalize( void )
{
	// �i�[�̈�̊J��
	delete[] pHandleTechnique_;
	pHandleTechnique_ = nullptr;

	delete[] pHandleParameter_;
	pHandleParameter_ = nullptr;

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : ID3DXEffect* pEffect				: �G�t�F�N�g
//==============================================================================
int Effect::Reinitialize( ID3DXEffect* pEffect )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pEffect );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : Effect* pOut						: �R�s�[��A�h���X
//==============================================================================
int Effect::Copy( Effect* pOut ) const
{
	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �n���h���̓ǂݍ���
// Return : int									: ���s����
// Arg    : int countTechnique					: �e�N�j�b�N��
// Arg    : int countParameter					: �p�����[�^��
//==============================================================================
int Effect::LoadHandle( int countTechnique, int countParameter )
{
	// ���łɓǂݍ��܂�Ă���ꍇ�͏I��
	if( pHandleTechnique_ != nullptr )
	{
		return 0;
	}

	// �G���[�`�F�b�N
	Assert( countTechnique > 0, _T( "�e�N�j�b�N�����s���ł��B" ) );

	// �����o�ϐ��̐ݒ�
	countTechnique_ = countTechnique;
	countParameter_ = countParameter;
	pHandleTechnique_ = new D3DXHANDLE[ countTechnique ];
	for( int counterItem = 0; counterItem < countTechnique; ++counterItem )
	{
		pHandleTechnique_[ counterItem ] = NULL;
	}
	if( countParameter > 0 )
	{
		pHandleParameter_ = new D3DXHANDLE[ countParameter ];
		for( int counterItem = 0; counterItem < countParameter; ++counterItem )
		{
			pHandleParameter_[ counterItem ] = NULL;
		}
	}

	// �n���h���̓ǂݍ���
	for( int counterTechnique = 0; counterTechnique < countTechnique; ++counterTechnique )
	{
		pHandleTechnique_[ counterTechnique ] = pEffect_->GetTechnique( counterTechnique );
	}
	for( int counterParameter = 0; counterParameter < countParameter; ++counterParameter )
	{
		pHandleParameter_[ counterParameter ] = pEffect_->GetParameter( NULL, counterParameter );
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �J�n
// Return : void								: �Ȃ�
// Arg    : int indexTechnique					: �e�N�j�b�N�ԍ�
//==============================================================================
void Effect::Begin( int indexTechnique )
{
	// �G�t�F�N�g�`��̊J�n
	unsigned int	countPass;		// �K�v�ȃp�X��
	pEffect_->SetTechnique( pHandleTechnique_[ indexTechnique ] );
	pEffect_->Begin( &countPass, 0 );
	pEffect_->BeginPass( 0 );
}

//==============================================================================
// Brief  : �I��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Effect::End( void )
{
	// �G�t�F�N�g�`��̏I��
	pEffect_->EndPass();
	pEffect_->End();
}

//==============================================================================
// Brief  : �e�N�X�`���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int indexParameter					: �p�����[�^�ԍ�
// Arg    : IDirect3DBaseTexture9* pTexture		: �ݒ肷��e�N�X�`��
//==============================================================================
void Effect::SetTexture( int indexParameter, IDirect3DBaseTexture9* pTexture )
{
	// �G���[�`�F�b�N
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "�p�����[�^�ԍ����s���ł��B" ) );

	// �e�N�X�`���̐ݒ�
	pEffect_->SetTexture( pHandleParameter_[ indexParameter ], pTexture );
}

//==============================================================================
// Brief  : �s��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int indexParameter					: �p�����[�^�ԍ�
// Arg    : const D3DXMATRIX& matrix			: �ݒ肷��s��
//==============================================================================
void Effect::SetMatrix( int indexParameter, const D3DXMATRIX& matrix )
{
	// �G���[�`�F�b�N
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "�p�����[�^�ԍ����s���ł��B" ) );

	// �s��̐ݒ�
	pEffect_->SetMatrix( pHandleParameter_[ indexParameter ], &matrix );
}

//==============================================================================
// Brief  : �F�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int indexParameter					: �p�����[�^�ԍ�
// Arg    : const D3DXCOLOR& color				: �ݒ肷��F
//==============================================================================
void Effect::SetColor( int indexParameter, const D3DXCOLOR& color )
{
	// �G���[�`�F�b�N
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "�p�����[�^�ԍ����s���ł��B" ) );

	// �F�̐ݒ�
	pEffect_->SetFloatArray( pHandleParameter_[ indexParameter ], &color.r, 4 );
}

//==============================================================================
// Brief  : �����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int indexParameter					: �p�����[�^�ԍ�
// Arg    : float value							: �ݒ肷��l
//==============================================================================
void Effect::SetFloat( int indexParameter, float value )
{
	// �G���[�`�F�b�N
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "�p�����[�^�ԍ����s���ł��B" ) );

	// �����̐ݒ�
	pEffect_->SetFloat( pHandleParameter_[ indexParameter ], value );
}

//==============================================================================
// Brief  : �����z��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int indexParameter					: �p�����[�^�ԍ�
// Arg    : const float* pValue					: �ݒ肷��l
// Arg    : int count							: �ݒ肷��v�f��
//==============================================================================
void Effect::SetFloatArray( int indexParameter, const float* pValue, int count )
{
	// �G���[�`�F�b�N
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "�p�����[�^�ԍ����s���ł��B" ) );

	// �����z��̐ݒ�
	pEffect_->SetFloatArray( pHandleParameter_[ indexParameter ], pValue, count );
}

//==============================================================================
// Brief  : �����̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int indexParameter					: �p�����[�^�ԍ�
// Arg    : int value							: �ݒ肷��l
//==============================================================================
void Effect::SetInteger( int indexParameter, int value )
{
	// �G���[�`�F�b�N
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "�p�����[�^�ԍ����s���ł��B" ) );

	// �����̐ݒ�
	pEffect_->SetInt( pHandleParameter_[ indexParameter ], value );
}

//==============================================================================
// Brief  : �����z��̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int indexParameter					: �p�����[�^�ԍ�
// Arg    : const int* pValue					: �ݒ肷��l
// Arg    : int count							: �ݒ肷��v�f��
//==============================================================================
void Effect::SetIntegerArray( int indexParameter, const int* pValue, int count )
{
	// �G���[�`�F�b�N
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "�p�����[�^�ԍ����s���ł��B" ) );

	// �����z��̐ݒ�
	pEffect_->SetIntArray( pHandleParameter_[ indexParameter ], pValue, count );
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void Effect::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffect_ = nullptr;
	countTechnique_ = 0;
	countParameter_ = 0;
	pHandleTechnique_ = nullptr;
	pHandleParameter_ = nullptr;
}
