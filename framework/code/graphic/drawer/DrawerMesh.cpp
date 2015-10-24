//==============================================================================
//
// File   : DrawerMesh.cpp
// Brief  : ���b�V���|���S���`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerMesh.h"
#include "../graphic/GraphicMain.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/graphic/Material.h"
#include "../../framework/light/LightDirection.h"
#include "../../framework/light/LightPoint.h"
#include "../../framework/polygon/PolygonMesh.h"
#include "../../framework/render/RenderMatrix.h"
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
DrawerMesh::DrawerMesh( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerMesh::~DrawerMesh( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffect						: �`��G�t�F�N�g
// Arg    : PolygonMesh* pPolygon				: ���b�V���|���S��
// Arg    : Material* pMaterial					: �}�e���A��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int DrawerMesh::Initialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture )
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
	pMaterial_ = pMaterial;

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
int DrawerMesh::Finalize( void )
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
// Arg    : PolygonMesh* pPolygon				: ���b�V���|���S��
// Arg    : Material* pMaterial					: �}�e���A��
// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
//==============================================================================
int DrawerMesh::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pParameter, pEffect, pPolygon, pMaterial, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerMesh* pOut					: �R�s�[��A�h���X
//==============================================================================
int DrawerMesh::Copy( DrawerMesh* pOut ) const
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
void DrawerMesh::Draw( const D3DXMATRIX& matrixWorld )
{
	// �ϊ��s��
	D3DXMATRIX		matrixTransform;				// �ϊ��s��
	D3DXMATRIX		matrixViewProjection;			// �r���[�v���W�F�N�V�����s��
	const Camera*	pCamera = nullptr;				// �J����
	RenderMatrix*	pRenderMatrix = nullptr;		// �����_�[�}�g���N�X
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );
	D3DXMatrixMultiply( &matrixTransform, &matrixWorld, &matrixViewProjection );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM, matrixTransform );

	// ���[���h�}�g���N�X
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorld );

	// ���_���W
	D3DXVECTOR3	positionEye;		// ���_���W
	pCamera->GetPositionCamera( &positionEye );
	pEffect_->SetFloatArray( PARAMETER_POSITION_EYE, &positionEye.x, 3 );

	// �����F
	D3DXCOLOR	colorAmbient;		// �����F
	pEffectParameter_->GetColorAmbient( &colorAmbient );
	pEffect_->SetFloatArray( PARAMETER_COLOR_AMBIENT, &colorAmbient.r, 3 );

	// �f�B���N�V���i�����C�g�̃x�N�g��
	const LightDirection*	pLightDirection = nullptr;		// �f�B���N�V���i�����C�g
	D3DXVECTOR3				vectorLight;					// �f�B���N�V���i�����C�g�x�N�g��
	pLightDirection = pEffectParameter_->GetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL );
	pLightDirection->GetVector( &vectorLight );
	pEffect_->SetFloatArray( PARAMETER_VECTOR_LIGHT_DIRECTION, &vectorLight.x, 3 );

	// �f�B���N�V���i�����C�g�̐F
	D3DXCOLOR	colorLightDirection;		// �f�B���N�V���i�����C�g�̐F
	pLightDirection->GetDiffuse( &colorLightDirection );
	pEffect_->SetFloatArray( PARAMETER_COLOR_LIGHT_DIRECTION, &colorLightDirection.r, 3 );

	// �|�C���g���C�g�̐ݒ�
	int					countPoint;				// �|�C���g���C�g�̐�
	const LightPoint*	pLightPoint;			// �|�C���g���C�g
	D3DXVECTOR3			positionPoint;			// �|�C���g���C�g�̍��W
	D3DXCOLOR			colorPoint;				// �|�C���g���C�g�̐F
	D3DXVECTOR3			attemuationPoint;		// �|�C���g���C�g�̌�����
	float				pPositionPoint[ 3 * GraphicMain::LIGHT_POINT_MAX ];			// �|�C���g���C�g�̍��W
	float				pColorPoint[ 3 * GraphicMain::LIGHT_POINT_MAX ];			// �|�C���g���C�g�̐F
	float				pAttemuationPoint[ 3 * GraphicMain::LIGHT_POINT_MAX ];		// �|�C���g���C�g�̌�����
	countPoint = pEffectParameter_->GetCountLightPoint();
	for( int counterLight = 0; counterLight < countPoint; ++counterLight )
	{
		// �|�C���g���C�g�̍��W
		pLightPoint = pEffectParameter_->GetLightPoint( counterLight );
		pLightPoint->GetPosition( &positionPoint );
		pPositionPoint[ 3 * counterLight + 0 ] = positionPoint.x;
		pPositionPoint[ 3 * counterLight + 1 ] = positionPoint.y;
		pPositionPoint[ 3 * counterLight + 2 ] = positionPoint.z;

		// �|�C���g���C�g�̐F
		pLightPoint->GetDiffuse( &colorPoint );
		pColorPoint[ 3 * counterLight + 0 ] = colorPoint.r;
		pColorPoint[ 3 * counterLight + 1 ] = colorPoint.g;
		pColorPoint[ 3 * counterLight + 2 ] = colorPoint.b;

		// �|�C���g���C�g�̌�����
		pLightPoint->GetAttemuation( &attemuationPoint );
		pAttemuationPoint[ 3 * counterLight + 0 ] = attemuationPoint.x;
		pAttemuationPoint[ 3 * counterLight + 1 ] = attemuationPoint.y;
		pAttemuationPoint[ 3 * counterLight + 2 ] = attemuationPoint.z;
	}

	// �|�C���g���C�g�̍��W
	pEffect_->SetFloatArray( PARAMETER_POSITION_LIGHT_POINT, pPositionPoint, 3 * countPoint );

	// �|�C���g���C�g�̐F
	pEffect_->SetFloatArray( PARAMETER_COLOR_LIGHT_POINT, pColorPoint, 3 * countPoint );

	// �|�C���g���C�g�̌�����
	pEffect_->SetFloatArray( PARAMETER_ATTEMUATION_LIGHT_POINT, pAttemuationPoint, 3 * countPoint );

	// �|�C���g���C�g�̐�
	pEffect_->SetInteger( PARAMETER_COUNT_LIGHT_POINT, countPoint );

	// �e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture_ );

	// �X�y�L�����F
	pEffect_->SetColor( PARAMETER_COLOR_SPECULAR, pMaterial_->specular_ );

	// ���˗�
	pEffect_->SetFloat( PARAMETER_REFLECTION, pMaterial_->reflection_ );

	// ���˂̋���
	pEffect_->SetFloat( PARAMETER_POWER, pMaterial_->power_ );

	// ���ܗ�
	pEffect_->SetFloat( PARAMETER_REFLACTIVE, pMaterial_->refractive_ );

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
void DrawerMesh::SetTexture( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : �e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerMesh::GetTexture( void ) const
{
	// �l�̕ԋp
	return pTexture_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerMesh::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTexture_ = nullptr;
	pPolygon_ = nullptr;
	pMaterial_ = nullptr;
}
