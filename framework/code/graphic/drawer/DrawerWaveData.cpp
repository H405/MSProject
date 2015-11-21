//==============================================================================
//
// File   : DrawerWaveData.cpp
// Brief  : �g���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerWaveData.h"
#include "../../framework/polygon/Polygon2D.h"
#include "../../framework/resource/Effect.h"
#include "../../system/EffectParameter.h"

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
DrawerWaveData::DrawerWaveData( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerWaveData::~DrawerWaveData( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : Polygon2D* pPolygon					: 2D�|���S��
// Arg    : IDirect3DTexture9* pTextureHeight0	: �����e�N�X�`��0
// Arg    : IDirect3DTexture9* pTextureHeight1	: �����e�N�X�`��1
//==============================================================================
int DrawerWaveData::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Drawer::Initialize();
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pEffectParameter_ = pParameter;
	pEffect_ = pEffect;
	pTextureHeight0_ = pTextureHeight0;
	pTextureHeight1_ = pTextureHeight1;
	pPolygon_ = pPolygon;

	// �n���h���̓ǂݍ���
	result = pEffect_->LoadHandle( 1, PARAMETER_MAX );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int DrawerWaveData::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Drawer::Finalize();
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
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : Polygon2D* pPolygon					: 2D�|���S��
// Arg    : IDirect3DTexture9* pTextureHeight0	: �����e�N�X�`��0
// Arg    : IDirect3DTexture9* pTextureHeight1	: �����e�N�X�`��1
//==============================================================================
int DrawerWaveData::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pParameter, pEffect, pPolygon, pTextureHeight0, pTextureHeight1 );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerWaveData* pOut				: �R�s�[��A�h���X
//==============================================================================
int DrawerWaveData::Copy( DrawerWaveData* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Drawer::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`�揈��
// Return : void								: �Ȃ�
// Arg    : const D3DXMATRIX& matrixWorld		: ���[���h�}�g���N�X
//==============================================================================
void DrawerWaveData::Draw( const D3DXMATRIX& matrixWorld )
{
	// ���_�V�F�[�_�p�p�����[�^
	D3DXMATRIX	matrixWorldSet;			// �ݒ肷�郏�[���h�}�g���N�X
	matrixWorldSet = matrixWorld;
	matrixWorldSet._41 -= 0.5f;
	matrixWorldSet._42 += 0.5f;
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldSet );

	// �e�N�X�`��
	isTexture0_ = !isTexture0_;
	pEffect_->SetTexture( PARAMETER_TEXTURE_HEIGHT, (isTexture0_ ? pTextureHeight0_ : pTextureHeight1_) );

	// �ǉ��g
	float	pWaveAdd[ 3 ];		// �ǉ�����g
	pWaveAdd[ 0 ] = static_cast< float >( rand() ) / RAND_MAX;
	pWaveAdd[ 1 ] = static_cast< float >( rand() ) / RAND_MAX;
	pWaveAdd[ 2 ] = 0.2f * (static_cast< float >( rand() ) / RAND_MAX - 0.5f);
	pEffect_->SetFloatArray( PARAMETER_WAVE_ADD, pWaveAdd, 3 );

	// �`��
	pEffect_->Begin( 0 );
	pPolygon_->Draw();
	pEffect_->End();
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerWaveData::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTextureHeight0_ = nullptr;
	pTextureHeight1_ = nullptr;
	pPolygon_ = nullptr;
	isTexture0_ = true;
}
