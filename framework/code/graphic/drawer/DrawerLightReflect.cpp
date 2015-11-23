//==============================================================================
//
// File   : DrawerLightReflect.cpp
// Brief  : ���˃��C�g�`��N���X
// Author : Taiga Shirakawa
// Date   : 2015/11/22 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "DrawerLightReflect.h"
#include "../graphic/GraphicMain.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/develop/DebugMeasure.h"
#include "../../framework/graphic/Material.h"
#include "../../framework/light/LightDirection.h"
#include "../../framework/light/LightPoint.h"
#include "../../framework/render/RenderMatrix.h"
#include "../../framework/resource/Effect.h"
#include "../../framework/polygon/Polygon2D.h"
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
DrawerLightReflect::DrawerLightReflect( void ) : Drawer()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
DrawerLightReflect::~DrawerLightReflect( void )
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
// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
//==============================================================================
int DrawerLightReflect::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth )
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
	pTextureDiffuse_ = pTextureDiffuse;
	pTextureSpecular_ = pTextureSpecular;
	pTextureNormal_ = pTextureNormal;
	pTextureDepth_ = pTextureDepth;
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
int DrawerLightReflect::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTextureDiffuse	: �f�B�t���[�Y���e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureSpecular	: �X�y�L�������e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureNormal	: �@�����e�N�X�`��
// Arg    : IDirect3DTexture9* pTextureDepth	: �[�x���e�N�X�`��
//==============================================================================
int DrawerLightReflect::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pParameter, pEffect, pPolygon, pTextureDiffuse, pTextureSpecular, pTextureNormal, pTextureDepth );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : DrawerLightReflect* pOut				: �R�s�[��A�h���X
//==============================================================================
int DrawerLightReflect::Copy( DrawerLightReflect* pOut ) const
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
void DrawerLightReflect::Draw( const D3DXMATRIX& matrixWorld )
{
	// ���˕ϊ��s��̍쐬
	D3DXMATRIX		matrixReflect;					// ���ˍs��
	D3DXVECTOR3		positionReflect;				// ���˖ʍ��W
	D3DXVECTOR3		normalReflect;					// ���˖ʖ@��
	D3DXPLANE		planeReflect;					// ���˖�
	positionReflect.x = positionReflect.z = normalReflect.x = normalReflect.z = 0.0f;
	positionReflect.y = pEffectParameter_->GetHeightReflect();
	normalReflect.y = 1.0f;
	D3DXPlaneFromPointNormal( &planeReflect, &positionReflect, &normalReflect );
	D3DXMatrixReflect( &matrixReflect, &planeReflect );

	// ���_�V�F�[�_�p�p�����[�^
	D3DXMATRIX	matrixWorldSet;			// �ݒ肷�郏�[���h�}�g���N�X
	float		pSizeScreen[ 2 ];		// ��ʂ̃T�C�Y
	matrixWorldSet = matrixWorld;
	matrixWorldSet._41 -= 0.5f;
	matrixWorldSet._42 -= 0.5f;
	pSizeScreen[ 0 ] = pEffectParameter_->GetWidthScreen();
	pSizeScreen[ 1 ] = pEffectParameter_->GetHeightScreen();
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldSet );
	pEffect_->SetFloatArray( PARAMETER_SIZE_SCREEN, pSizeScreen, 2 );

	// 3D���e�N�X�`��
	pEffect_->SetTexture( PARAMETER_TEXTURE_DIFFUSE, pTextureDiffuse_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_SPECULAR, pTextureSpecular_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_NORMAL, pTextureNormal_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH, pTextureDepth_ );

	// �v���W�F�N�V�����ϊ��t�s��
	const Camera*	pCamera = nullptr;				// �J����
	RenderMatrix*	pRenderMatrix = nullptr;		// �`��ϊ��s��
	D3DXMATRIX		matrixProjectionInverse;		// �v���W�F�N�V�����ϊ��t�s��
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixProjection( &matrixProjectionInverse );
	D3DXMatrixInverse( &matrixProjectionInverse, nullptr, &matrixProjectionInverse );
	pEffect_->SetMatrix( PARAMETER_MATRIX_PROJECTION_INVERSE, matrixProjectionInverse );

	// �r���[�ϊ��t�s��
	D3DXMATRIX	matrixViewInverse;		// �r���[�ϊ��t�s��
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixView( &matrixViewInverse );
	D3DXMatrixInverse( &matrixViewInverse, nullptr, &matrixViewInverse );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW_INVERSE, matrixViewInverse );

	// ���_���W
	D3DXVECTOR3	positionEye;		// ���_���W
	pCamera->GetPositionCamera( &positionEye );
	D3DXVec3TransformCoord( &positionEye, &positionEye, &matrixReflect );
	pEffect_->SetFloatArray( PARAMETER_POSITION_EYE, &positionEye.x, 3 );

	// �J�����̃N���b�v�l
	float	pClipCamera[ 2 ];		// �J�����̃N���b�v�l
	pClipCamera[ 0 ] = pCamera->GetClipNear();
	pClipCamera[ 1 ] = pCamera->GetClipFar();
	pEffect_->SetFloatArray( PARAMETER_CLIP_CAMERA, pClipCamera, 2 );

	// �����F
	D3DXCOLOR	colorAmbient;		// �����F
	pEffectParameter_->GetColorAmbient( &colorAmbient );
	pEffect_->SetFloatArray( PARAMETER_COLOR_AMBIENT, &colorAmbient.r, 3 );

	// �f�B���N�V���i�����C�g�̃x�N�g��
	const LightDirection*	pLightDirection = nullptr;		// �f�B���N�V���i�����C�g
	D3DXVECTOR3				vectorLight;					// �f�B���N�V���i�����C�g�x�N�g��
	pLightDirection = pEffectParameter_->GetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL );
	if( pLightDirection != nullptr )
	{
		pLightDirection->GetVector( &vectorLight );
		D3DXVec3TransformNormal( &vectorLight, &vectorLight, &matrixReflect );
		pEffect_->SetFloatArray( PARAMETER_VECTOR_LIGHT_DIRECTION, &vectorLight.x, 3 );
	}

	// �f�B���N�V���i�����C�g�̐F
	D3DXCOLOR	colorLightDirection;		// �f�B���N�V���i�����C�g�̐F
	if( pLightDirection != nullptr )
	{
		pLightDirection->GetDiffuse( &colorLightDirection );
		pEffect_->SetFloatArray( PARAMETER_COLOR_LIGHT_DIRECTION, &colorLightDirection.r, 3 );
	}

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
		D3DXVec3TransformCoord( &positionPoint, &positionPoint, &matrixReflect );
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
	pEffect_->SetFloatArray( PARAMETER_ATTENUATION_LIGHT_POINT, pAttemuationPoint, 3 * countPoint );

	// �`��
	pEffect_->Begin( 0 );
	pPolygon_->Draw();
	pEffect_->End();
}

//==============================================================================
// Brief  : �f�B�t���[�Y���e�N�X�`���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DTexture9* pValue			: �ݒ肷��l
//==============================================================================
void DrawerLightReflect::SetTextureDiffuse( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTextureDiffuse_ = pValue;
}

//==============================================================================
// Brief  : �f�B�t���[�Y���e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerLightReflect::GetTextureDiffuse( void ) const
{
	// �l�̕ԋp
	return pTextureDiffuse_;
}

//==============================================================================
// Brief  : �X�y�L�������e�N�X�`���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DTexture9* pValue			: �ݒ肷��l
//==============================================================================
void DrawerLightReflect::SetTextureSpecular( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTextureSpecular_ = pValue;
}

//==============================================================================
// Brief  : �X�y�L�������e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerLightReflect::GetTextureSpecular( void ) const
{
	// �l�̕ԋp
	return pTextureSpecular_;
}

//==============================================================================
// Brief  : �@�����e�N�X�`���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DTexture9* pValue			: �ݒ肷��l
//==============================================================================
void DrawerLightReflect::SetTextureNormal( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTextureNormal_ = pValue;
}

//==============================================================================
// Brief  : �@�����e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerLightReflect::GetTextureNormal( void ) const
{
	// �l�̕ԋp
	return pTextureNormal_;
}

//==============================================================================
// Brief  : �[�x���e�N�X�`���̐ݒ�
// Return : void								: �Ȃ�
// Arg    : IDirect3DTexture9* pValue			: �ݒ肷��l
//==============================================================================
void DrawerLightReflect::SetTextureDepth( IDirect3DTexture9* pValue )
{
	// �l�̐ݒ�
	pTextureDepth_ = pValue;
}

//==============================================================================
// Brief  : �[�x���e�N�X�`���̎擾
// Return : IDirect3DTexture9*					: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
IDirect3DTexture9* DrawerLightReflect::GetTextureDepth( void ) const
{
	// �l�̕ԋp
	return pTextureDepth_;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void DrawerLightReflect::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTextureDiffuse_ = nullptr;
	pTextureSpecular_ = nullptr;
	pTextureNormal_ = nullptr;
	pTextureDepth_ = nullptr;
	pPolygon_ = nullptr;
}
