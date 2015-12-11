//==============================================================================
//
// File   : DrawerGrass.cpp
// Brief  : ���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/12/11 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerGrass.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/polygon/PolygonSignboard.h"
#include "../../framework/render/RenderMatrix.h"
#include "../../framework/resource/Effect.h"
#include "../../graphic/graphic/GraphicMain.h"
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
DrawerGrass::DrawerGrass( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerGrass::~DrawerGrass( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : PolygonSignboard* pPolygon			: �r���{�[�h�|���S��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
// Arg    : float hardness						: �d��
//==============================================================================
int DrawerGrass::Initialize( const EffectParameter* pParameter, Effect* pEffect, PolygonSignboard* pPolygon,
	IDirect3DTexture9* pTexture, float hardness )
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
	pTexture_ = pTexture;
	pPolygon_ = pPolygon;
	hardness_ = hardness;

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
int DrawerGrass::Finalize( void )
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
// Arg    : PolygonSignboard* pPolygon			: �r���{�[�h�|���S��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
// Arg    : float hardness						: �d��
//==============================================================================
int DrawerGrass::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, PolygonSignboard* pPolygon,
	IDirect3DTexture9* pTexture, float hardness )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pParameter, pEffect, pPolygon, pTexture, hardness );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerGrass* pOut				: �R�s�[��A�h���X
//==============================================================================
int DrawerGrass::Copy( DrawerGrass* pOut ) const
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
void DrawerGrass::Draw( const D3DXMATRIX& matrixWorld )
{
	// �K�v�ȏ����擾
	D3DXMATRIX		matrixTransform;				// �ϊ��s��
	D3DXMATRIX		matrixViewProjection;			// �r���[�v���W�F�N�V�����s��
	const Camera*	pCamera = nullptr;				// �J����
	RenderMatrix*	pRenderMatrix = nullptr;		// �����_�[�}�g���N�X
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );

	// �]�u�r���[�s������߂�
	D3DXMATRIX	matrixView;				// �r���[�s��
	D3DXMATRIX	matrixViewInverse;		// �]�u�r���[�s��
	pRenderMatrix->GetMatrixView( &matrixView );
	matrixViewInverse._11 = matrixView._11;
	matrixViewInverse._22 = matrixView._22;
	matrixViewInverse._33 = matrixView._33;
	matrixViewInverse._44 = matrixView._44;
	matrixViewInverse._12 = matrixView._21;
	matrixViewInverse._13 = matrixView._31;
	matrixViewInverse._21 = matrixView._12;
	matrixViewInverse._23 = matrixView._32;
	matrixViewInverse._31 = matrixView._13;
	matrixViewInverse._32 = matrixView._23;
	matrixViewInverse._14 = matrixViewInverse._24 = matrixViewInverse._34 = matrixViewInverse._41 = matrixViewInverse._42 = matrixViewInverse._43 = 0.0f;

	// �ϊ��s��
	D3DXVECTOR3	translate;		// ���s�ړ�
	matrixTransform = matrixWorld;
	translate.x = matrixWorld._41;
	translate.y = matrixWorld._42;
	translate.z = matrixWorld._43;
	matrixTransform._41 = matrixTransform._42 = matrixTransform._43 = 0.0f;
	D3DXMatrixMultiply( &matrixTransform, &matrixTransform, &matrixViewInverse );
	matrixTransform._41 = translate.x;
	matrixTransform._42 = translate.y;
	matrixTransform._43 = translate.z;
	D3DXMatrixMultiply( &matrixTransform, &matrixTransform, &matrixViewProjection );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM, matrixTransform );

	// �e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture_ );

	// ������
	D3DXVECTOR3	vectorWind;					// ������
	D3DXVECTOR3	vectorTransformCoord;		// ���_�̕ω��x�N�g��
	pEffectParameter_->GetVectorWind( &vectorWind );
	velocityTransform_ += vectorWind;
	velocityTransform_ -= vectorTransform_ * hardness_;
	vectorTransform_ += velocityTransform_;
	D3DXVec3TransformNormal( &vectorTransformCoord, &vectorTransform_, &matrixViewProjection );
	pEffect_->SetFloatArray( PARAMETER_VECTOR_WIND, &vectorTransformCoord.x, 2 );

	// �`��
	pEffect_->Begin( 0 );
	pPolygon_->Draw();
	pEffect_->End();
}

//==============================================================================
// Brief  : �e�N�X�`���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DTexture9* pValue			: �ݒ肷��l
//==============================================================================
void DrawerGrass::SetTexture( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : �e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerGrass::GetTexture( void ) const
{
	// �l�̕ԋp
	return pTexture_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerGrass::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTexture_ = nullptr;
	pPolygon_ = nullptr;
	vectorTransform_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	velocityTransform_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}
