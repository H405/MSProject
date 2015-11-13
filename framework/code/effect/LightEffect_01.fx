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
float4x4	matrixWorld_;						// ���[���h�ϊ��s��
float2		sizeScreen_;						// ��ʃT�C�Y

texture		textureDiffuse_;					// �f�B�t���[�Y�e�N�X�`��
texture		textureSpecular_;					// �X�y�L�����e�N�X�`��
texture		textureNormal_;						// �@���e�N�X�`��
texture		textureDepth_;						// �[�x�e�N�X�`��

float4x4	matrixProjectionInverse_;			// �v���W�F�N�V�����ϊ��t�s��
float4x4	matrixViewInverse_;					// �r���[�ϊ��t�s��
float3		positionEye_;						// �J�����̍��W
float2		clipCamera_;						// �J�����̃N���b�v�l
float3		colorAmbient_;						// ���F
float3		vectorLightDirection_;				// �f�B���N�V���i�����C�g�̃x�N�g��
float3		colorLightDirection_;				// �f�B���N�V���i�����C�g�̐F
float3		positionLightPoint_[ 1 ];			// �|�C���g���C�g���C�g�̍��W
float3		colorLightPoint_[ 1 ];				// �|�C���g���C�g���C�g�̐F
float3		attenuationLightPoint_[ 1 ];		// �|�C���g���C�g�̌�����
int			countLightPoint_;					// �|�C���g���C�g�̐�

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
	output.position_ = mul( output.position_, matrixWorld_ );
	output.position_.xy /= 0.5f * sizeScreen_;

	// �l���i�[
	output.textureCoord_ = textureCoord;

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
	float4	dataDiffuse = tex2D( samplerTextureDiffuse , vertex.textureCoord_ );
	float4	dataSpecular = tex2D( samplerTextureSpecular , vertex.textureCoord_ );
	float4	dataNormal = tex2D( samplerTextureNormal , vertex.textureCoord_ );
	float	dataDepth = tex2D( samplerTextureDepth , vertex.textureCoord_ ).r;

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

	// �����̃X�y�L�����F���v�Z
	float	fresnel = dataNormal.a + (1.0f - dataNormal.a) * exp( -6.0f * max( dot( vectorNormal, vectorVertexToEye ), 0.0f ) );
	float3	specularAmbient = colorAmbient_.rgb * fresnel;

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	float3	diffuseDirection = CalculateDiffuse( colorLightDirection_, vectorLightDirection_, vectorNormal );

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
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 0 ], vectorLightToVertex, vectorNormal );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 0 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 0 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// �s�N�Z���F��Ԃ�
	PixelOutput	output;
	output.color_ = float4( color, 1.0f );
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
