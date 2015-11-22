//==============================================================================
// 
// File   : Water.fx
// Brief  : ���G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixTransform_;					// �ϊ��s��
float4x4	matrixWorld_;						// ���[���h�ϊ��s��
float4x4	matrixWorldView_;					// ���[���h�r���[�ϊ��s��
float4x4	matrixTransformTexture_;			// �e�N�X�`�����W�ϊ��s��

float4x4	matrixWorldInverseTranspose_;		// ���[���h�t�]�u�s��
texture		textureNormal_;						// �@���e�N�X�`��
float3		colorDiffuse_;						// �f�B�t���[�Y�F
float3		colorSpecular_;						// �X�y�L�����F
float		reflection_;						// ���˗�
float		power_;								// ���˂̋���
float		refractive_;						// ���ܗ�

texture		textureEnvironmentFront_;			// ���ʊ��e�N�X�`��
texture		textureEnvironmentBack_;			// �w�ʊ��e�N�X�`��
texture		textureEnvironmentAddFront_;		// ���ʉ��Z���e�N�X�`��
texture		textureEnvironmentAddBack_;			// �w�ʉ��Z���e�N�X�`��

float3		positionEye_;						// �J�����̍��W
float2		clipCamera_;						// �J�����̃N���b�v�l
float3		colorAmbient_;						// ���F
float3		vectorLightDirection_;				// �f�B���N�V���i�����C�g�̃x�N�g��
float3		colorLightDirection_;				// �f�B���N�V���i�����C�g�̐F
float3		positionLightPoint_[ 32 ];			// �|�C���g���C�g���C�g�̍��W
float3		colorLightPoint_[ 32 ];				// �|�C���g���C�g���C�g�̐F
float3		attenuationLightPoint_[ 32 ];		// �|�C���g���C�g�̌�����

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTextureNormal = sampler_state
{
	Texture = < textureNormal_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = WRAP;
	AddressV = WRAP;
};

sampler samplerTextureEnvironmentFront = sampler_state
{
	Texture = < textureEnvironmentFront_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

sampler samplerTextureEnvironmentBack = sampler_state
{
	Texture = < textureEnvironmentBack_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

sampler samplerTextureEnvironmentAddFront = sampler_state
{
	Texture = < textureEnvironmentAddFront_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

sampler samplerTextureEnvironmentAddBack = sampler_state
{
	Texture = < textureEnvironmentAddBack_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

//******************************************************************************
// �\���̒�`
//******************************************************************************
// ���_�V�F�[�_�o��
struct VertexOutput
{
	float4	position_			: POSITION;			// ���W
	float2	textureCoord_		: TEXCOORD0;		// �e�N�X�`�����W
	float3	positionWorld_		: TEXCOORD1;		// �ϊ�����W
	float3	vectorNormalWorld_	: TEXCOORD2;		// �ϊ���@��
	float3	tangentWorld_		: TEXCOORD3;		// �ϊ���ڐ�
	float	depth_				: TEXCOORD4;		// �[�x
	float4	positionTexture_	: TEXCOORD5;		// �e�N�X�`�����W
};

// �s�N�Z���V�F�[�_�o��
struct PixelOutput
{
	float4	color_				: COLOR0;			// �F
	float4	depth_				: COLOR1;			// �[�x
};

//==============================================================================
// Brief  : �f�B�t���[�Y�̌v�Z
// Return : float3							: �F
// Arg    : float3 colorLight				: ���C�g�̐F
// Arg    : float3 vectorLight				: ���C�g�̃x�N�g��
// Arg    : float3 vectorNormal				: �@���x�N�g��
//==============================================================================
float3 CalculateDiffuse( float3 colorLight, float3 vectorLight, float3 vectorNormal )
{
	// ���x�̌v�Z
	float	lightness = dot( vectorNormal, -vectorLight ) * 0.5f + 0.5f;

	// �f�B�t���[�Y�F��Ԃ�
	return colorLight * lightness;
}

//==============================================================================
// Brief  : �X�y�L�����̌v�Z
// Return : float3							: �F
// Arg    : float3 colorLight				: ���C�g�̐F
// Arg    : float3 vectorLight				: ���C�g�̃x�N�g��
// Arg    : float3 vectorNormal				: �@���x�N�g��
// Arg    : float3 vectorVertexToEye		: ���_���王�_�ւ̃x�N�g��
// Arg    : float reflection;				: ���˗�
// Arg    : float power;					: ���˂̋���
//==============================================================================
float3 CalculateSpecular( float3 colorLight, float3 vectorLight, float3 vectorNormal, float3 vectorVertexToEye, float reflection, float power )
{
	// �n�[�t�x�N�g�������߂�
	float3	vectorHalf = normalize( vectorVertexToEye - vectorLight );

	// �X�y�L�����F��Ԃ�
	return colorLight * pow( max( dot( vectorNormal, vectorHalf ), 0.0f ), power ) * reflection;
}

//==============================================================================
// Brief  : �����̌v�Z
// Return : float3							: �F
// Arg    : float3 colorLight				: ���C�g�̐F
// Arg    : float3 vectorLight				: ���C�g�̃x�N�g��
// Arg    : float3 vectorNormal				: �@���x�N�g��
// Arg    : float3 vectorVertexToEye		: ���_���王�_�ւ̃x�N�g��
//==============================================================================
float3 CalculateRim( float3 colorLight, float3 vectorLight, float3 vectorNormal, float3 vectorVertexToEye )
{
	// �����F��Ԃ�
	float	rim = (1.0f - max( dot( vectorNormal, vectorVertexToEye ), 0.0f )) * max( dot( vectorLight, vectorVertexToEye ), 0.0f );
	rim = min( 5.0f * pow( rim, 5.0f ), 1.0f );
	return colorLight * rim;
}

//==============================================================================
// Brief  : ���_�ϊ�
// Return : VertexOutput					: ���_�V�F�[�_�o��
// Arg    : float4 positionLocal			: ���[�J�����W
// Arg    : float3 vectorNormalLocal		: �@���x�N�g��
// Arg    : float3 tangentLocal				: ����
// Arg    : float2 positionTexture			: �e�N�X�`�����W
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 vectorNormalLocal : NORMAL, float3 tangentLocal : TANGENT, float2 textureCoord : TEXCOORD0 )
{
	// ���_�̕ϊ�
	VertexOutput	output;		// ���_�V�F�[�_�o��
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixTransform_ );
	output.positionWorld_ = mul( float4( positionLocal, 1.0f ), matrixWorld_ );
	output.positionTexture_ = mul( float4( positionLocal, 1.0f ), matrixTransformTexture_ );

	// �@���̕ϊ�
	output.vectorNormalWorld_ = normalize( mul( float4( vectorNormalLocal, 0.0f ), matrixWorld_ ) ).xyz;

	// ���ڂ̕ϊ�
	output.tangentWorld_ = normalize( mul( float4( tangentLocal, 0.0f ), matrixWorldInverseTranspose_ ).xyz );

	// �[�x�̌v�Z
	output.depth_ = mul( float4( positionLocal, 1.0f ), matrixWorldView_ ).z;

	// �o�͒l�̊i�[
	output.textureCoord_ = textureCoord;

	// ���_�V�F�[�_�o�͂�Ԃ�
	return output;
}

//==============================================================================
// Brief  : �s�N�Z���`��
// Return : PixelOutput						: �s�N�Z���V�F�[�_�o��
// Arg    : VertexOutput					: ���_�V�F�[�_�o��
//==============================================================================
PixelOutput DrawPixel( VertexOutput vertex )
{
	// �����x�N�g�������߂�
	float3	vectorVertexToEye = normalize( positionEye_ - vertex.positionWorld_ );

	// �������擾
	float	height = tex2D( samplerTextureNormal, vertex.textureCoord_ ).a * 2.0f - 1.0f;

	// �@�������߂�
	float3	tangent = normalize( vertex.tangentWorld_ - dot( vertex.tangentWorld_, vertex.vectorNormalWorld_ ) * vertex.vectorNormalWorld_ );
	float3	binormal = cross( vertex.vectorNormalWorld_, tangent );
	float3	vectorVertexToEyeTexture = normalize( mul( vectorVertexToEye, float3x3( tangent, binormal, vertex.vectorNormalWorld_ ) ) );
	float3	normalTexture = normalize( tex2D( samplerTextureNormal, vertex.textureCoord_ + 0.02f * height * vectorVertexToEye.xy ).rgb * 2.0f - 1.0f );
	float3	normal = normalize( mul( normalTexture, float3x3( tangent, binormal, vertex.vectorNormalWorld_ ) ) );
//	normal = vertex.vectorNormalWorld_;

	// �f�B�t���[�Y�F�����߂�
	float	proportionDepth = (tex2Dproj( samplerTextureEnvironmentAddFront, vertex.positionTexture_ ) - vertex.depth_) / 1000.0f;
	float	offsetTextureReflect = float4( (normal - vectorVertexToEye).xy * refractive_ * 5000.0f * proportionDepth, 0.0f, 0.0f );
	float	offsetTextureUnder = float4( (normal - vectorVertexToEye).xy * refractive_ * 50.0f, 0.0f, 0.0f );
	float	proportionEnvironment = dot( normal, vectorVertexToEye );
	float3	colorReflerct = tex2Dproj( samplerTextureEnvironmentFront, vertex.positionTexture_ + offsetTextureReflect );
	float3	colorUnder = tex2Dproj( samplerTextureEnvironmentBack, vertex.positionTexture_ + offsetTextureUnder );
	float3	colorWater = colorDiffuse_ * lerp( colorReflerct, colorUnder, proportionEnvironment );
	float3	colorDiffuse = lerp( tex2Dproj( samplerTextureEnvironmentBack, vertex.positionTexture_ ).rgb, colorWater, min( 200.0f * proportionDepth, 1.0f ) );

	// �����̃X�y�L�����F���v�Z
	float	fresnel = refractive_ + (1.0f - refractive_) * exp( -6.0f * max( dot( normal, vectorVertexToEye ), 0.0f ) );
	float3	specularAmbient = colorAmbient_.rgb * fresnel;

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	float3	diffuseDirection = CalculateDiffuse( colorLightDirection_, vectorLightDirection_, normal );

	// �f�B���N�V���i�����C�g�̃X�y�L�����F���v�Z
	float3	specularDirection = CalculateSpecular( colorLightDirection_, vectorLightDirection_, normal, vectorVertexToEye, reflection_, power_ );

	// �f�B���N�V���i�����C�g�̃����F���v�Z
	float3	rimDirection = CalculateRim( colorLightDirection_, vectorLightDirection_, normal, vectorVertexToEye );

	// �����ƃf�B���N�V���i�����C�g�̐F���v�Z
	float3	color = colorDiffuse * (diffuseDirection + colorAmbient_) + colorSpecular_ * (specularDirection + specularAmbient) + rimDirection;

	// �|�C���g���C�g�̐F���v�Z
	float	distanceLightToVertex;
	float	attenuation;
	float3	vectorLightToVertex;
	float3	diffusePoint;
	float3	specularPoint;
	float3	rimPoint;
	for( int counterLight = 0; counterLight < 10; ++counterLight )
	{
		// �|�C���g���C�g�̌��������v�Z
		distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ counterLight ] );
		attenuation = attenuationLightPoint_[ counterLight ].x
			+ attenuationLightPoint_[ counterLight ].y * distanceLightToVertex
			+ attenuationLightPoint_[ counterLight ].z * distanceLightToVertex * distanceLightToVertex;

		// ���C�g���璸�_�ւ̃x�N�g�������߂�
		vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ counterLight ] );

		// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
		diffusePoint = CalculateDiffuse( colorLightPoint_[ counterLight ], vectorLightToVertex, normal );

		// �|�C���g���C�g�̃X�y�L�����F���v�Z
		specularPoint = CalculateSpecular( colorLightPoint_[ counterLight ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

		// �|�C���g���C�g�̃����F���v�Z
		rimPoint = CalculateRim( colorLightPoint_[ counterLight ], vectorLightToVertex, normal, vectorVertexToEye );

		// �|�C���g���C�g�̐F���v�Z
		color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;
	}

	// �l�̐ݒ�
	PixelOutput	output;		// �s�N�Z���V�F�[�_�o��
	output.color_ = float4( color, 1.0f );
	output.depth_.gba = 0.0f;
	output.depth_.r = vertex.depth_;

	// �s�N�Z���V�F�[�_�o�͂�Ԃ�
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
		// �V�F�[�_�̐ݒ�
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
