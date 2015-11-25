//==============================================================================
// 
// File   : LightEffect.fx
// Brief  : ���C�g�G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/11/01 sun : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float2		offsetTexel_;						// �e�N�Z���I�t�Z�b�g

texture		textureDiffuse_;					// �f�B�t���[�Y�e�N�X�`��
texture		textureSpecular_;					// �X�y�L�����e�N�X�`��
texture		textureNormal_;						// �@���e�N�X�`��
texture		textureDepth_;						// �[�x�e�N�X�`��
texture		textureDiffuseRiver_;				// ��̃f�B�t���[�Y�e�N�X�`��
texture		textureSpecularRiver_;				// ��̃X�y�L�����e�N�X�`��
texture		textureNormalRiver_;				// ��̖@���e�N�X�`��
texture		textureDepthRiver_;					// ��̐[�x�e�N�X�`��
texture		textureShadow_;						// �e�e�N�X�`��

float4x4	matrixProjectionInverse_;			// �v���W�F�N�V�����ϊ��t�s��
float4x4	matrixViewInverse_;					// �r���[�ϊ��t�s��
float3		positionEye_;						// �J�����̍��W
float2		clipCamera_;						// �J�����̃N���b�v�l
float3		colorAmbient_;						// ���F
float3		vectorLightDirection_;				// �f�B���N�V���i�����C�g�̃x�N�g��
float3		colorLightDirection_;				// �f�B���N�V���i�����C�g�̐F
float3		positionLightPoint_[ 9 ];			// �|�C���g���C�g���C�g�̍��W
float3		colorLightPoint_[ 9 ];				// �|�C���g���C�g���C�g�̐F
float3		attenuationLightPoint_[ 9 ];		// �|�C���g���C�g�̌�����

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTextureDiffuse = sampler_state
{
	Texture = < textureDiffuse_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureSpecular = sampler_state
{
	Texture = < textureSpecular_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureNormal = sampler_state
{
	Texture = < textureNormal_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepth = sampler_state
{
	Texture = < textureDepth_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDiffuseRiver = sampler_state
{
	Texture = < textureDiffuseRiver_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureSpecularRiver = sampler_state
{
	Texture = < textureSpecularRiver_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureNormalRiver = sampler_state
{
	Texture = < textureNormalRiver_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthRiver = sampler_state
{
	Texture = < textureDepthRiver_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureShadow = sampler_state
{
	Texture = < textureShadow_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

//******************************************************************************
// �\���̒�`
//******************************************************************************
// ���_�V�F�[�_�o��
struct VertexOutput
{
	float4	position_		: POSITION;			// ���W
	float2	textureCoord_	: TEXCOORD0;		// �e�N�X�`�����W
};

// �s�N�Z���V�F�[�_�o��
struct PixelOutput
{
	float4	color_			: COLOR0;			// �F
	float4	depth_			: COLOR1;			// �[�x
};

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "CalculateLight.fx"

//==============================================================================
// Brief  : ���_�ϊ�
// Return : VertexOutput					: ���_�o��
// Arg    : float4 positionLocal			: ���[�J�����W
// Arg    : float2 positionTexture			: �e�N�X�`�����W
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float2 textureCoord : TEXCOORD0 )
{
	// ���_�̕ϊ�
	VertexOutput	output;		// �o��
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;

	// �l���i�[
	output.textureCoord_ = textureCoord + offsetTexel_;

	// ���_�o�͂�Ԃ�
	return output;
}

//==============================================================================
// Brief  : �s�N�Z���`��
// Return : PixelOutput						: �s�N�Z���V�F�[�_�o��
// Arg    : VertexOutput					: ���_�V�F�[�_�o��
//==============================================================================
PixelOutput DrawPixel( VertexOutput vertex )
{
	// �e�N�X�`����������擾
	float4	dataSpecularRiver = tex2D( samplerTextureSpecularRiver, vertex.textureCoord_ );
	float	proportionRiver = min( 4.0f * dataSpecularRiver.b, 1.0f );
	float4	dataDiffuse = lerp( tex2D( samplerTextureDiffuse, vertex.textureCoord_ ), tex2D( samplerTextureDiffuseRiver, vertex.textureCoord_ ), proportionRiver );
	float4	dataSpecular = lerp( tex2D( samplerTextureSpecular, vertex.textureCoord_ ), dataSpecularRiver, proportionRiver );
	float4	dataNormal = lerp( tex2D( samplerTextureNormal, vertex.textureCoord_ ), tex2D( samplerTextureNormalRiver, vertex.textureCoord_ ), proportionRiver );
	float	dataDepth = lerp( tex2D( samplerTextureDepth, vertex.textureCoord_ ).r, tex2D( samplerTextureDepthRiver, vertex.textureCoord_ ).r, proportionRiver );

	// ���̐ݒ�
	float3	colorDiffuse = dataDiffuse.rgb;
	float3	colorSpecular = dataSpecular.rgb;
	float3	vectorNormal = dataNormal.xyz * 2.0f - 1.0f;
	float	depth = dataDepth;
	float	power = dataSpecular.a * 64.0f;

	// ���[���h���W�����߂�
	float2	positionTexture = vertex.textureCoord_ * 2.0f - 1.0f;
	float3	positionProjection = mul( float4( positionTexture.x, -positionTexture.y, 1.0f, 1.0f ), matrixProjectionInverse_ ).xyz;
	float3	positionView = float3( positionProjection.xy, 1.0f ) * depth;
	float3	positionWorld = mul( float4( positionView, 1.0f ), matrixViewInverse_ );

	// �����x�N�g�������߂�
	float3	vectorVertexToEye = normalize( positionEye_ - positionWorld );

	// �e
	float	shadow = lerp( tex2D( samplerTextureShadow, vertex.textureCoord_ ).r, 1.0f, proportionRiver );

	// �����̃X�y�L�����F���v�Z
	float	fresnel = dataNormal.a + (1.0f - dataNormal.a) * exp( -6.0f * max( dot( vectorNormal, vectorVertexToEye ), 0.0f ) );
	float3	specularAmbient = colorAmbient_.rgb * fresnel;

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	float3	diffuseDirection = colorLightDirection_ * min( dot( vectorNormal, -vectorLightDirection_ ) * 0.5f + 0.5f, shadow );

	// �f�B���N�V���i�����C�g�̃X�y�L�����F���v�Z
	float3	specularDirection = CalculateSpecular( colorLightDirection_, vectorLightDirection_, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// �f�B���N�V���i�����C�g�̃����F���v�Z
	float3	rimDirection = CalculateRim( colorLightDirection_, vectorLightDirection_, vectorNormal, vectorVertexToEye );

	// �����ƃf�B���N�V���i�����C�g�̐F���v�Z
	float3	color = colorDiffuse * (diffuseDirection + colorAmbient_) + colorSpecular * (specularDirection + specularAmbient) + rimDirection;

	// �|�C���g���C�g�̐F���v�Z
	float	distanceLightToVertex;
	float	attenuation;
	float3	vectorLightToVertex;
	float3	diffusePoint;
	float3	specularPoint;
	float3	rimPoint;


	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 0 ] );
	attenuation = attenuationLightPoint_[ 0 ].x
		+ attenuationLightPoint_[ 0 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 0 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 0 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = colorLightPoint_[ 0 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 0 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 0 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 1 ] );
	attenuation = attenuationLightPoint_[ 1 ].x
		+ attenuationLightPoint_[ 1 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 1 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 1 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = colorLightPoint_[ 1 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 1 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 1 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 2 ] );
	attenuation = attenuationLightPoint_[ 2 ].x
		+ attenuationLightPoint_[ 2 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 2 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 2 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = colorLightPoint_[ 2 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 2 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 2 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 3 ] );
	attenuation = attenuationLightPoint_[ 3 ].x
		+ attenuationLightPoint_[ 3 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 3 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 3 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = colorLightPoint_[ 3 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 3 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 3 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 4 ] );
	attenuation = attenuationLightPoint_[ 4 ].x
		+ attenuationLightPoint_[ 4 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 4 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 4 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = colorLightPoint_[ 4 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 4 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 4 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 5 ] );
	attenuation = attenuationLightPoint_[ 5 ].x
		+ attenuationLightPoint_[ 5 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 5 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 5 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = colorLightPoint_[ 5 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 5 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 5 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 6 ] );
	attenuation = attenuationLightPoint_[ 6 ].x
		+ attenuationLightPoint_[ 6 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 6 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 6 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = colorLightPoint_[ 6 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 6 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 6 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 7 ] );
	attenuation = attenuationLightPoint_[ 7 ].x
		+ attenuationLightPoint_[ 7 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 7 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 7 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = colorLightPoint_[ 7 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 7 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 7 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 8 ] );
	attenuation = attenuationLightPoint_[ 8 ].x
		+ attenuationLightPoint_[ 8 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 8 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 8 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = colorLightPoint_[ 8 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 8 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 8 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// �s�N�Z���F��Ԃ�
	PixelOutput	output;
	output.color_ = float4( color, dataDepth );
	output.depth_.gba = 0.0f;
	output.depth_.r = dataDepth / clipCamera_.y;
	return output;
}

//==============================================================================
// Brief  : �ʏ�ϊ�
//==============================================================================
technique ShadeNormal
{
	// �ʏ�ϊ�
	pass PassNormal
	{
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
