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
float3		positionLightPoint_[ 9 ];			// �|�C���g���C�g���C�g�̍��W
float3		colorLightPoint_[ 9 ];				// �|�C���g���C�g���C�g�̐F
float3		attenuationLightPoint_[ 9 ];		// �|�C���g���C�g�̌�����

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
	float	height = tex2D( samplerTextureNormal, vertex.textureCoord_ ).a;

	// �@�������߂�
	float3	tangent = normalize( vertex.tangentWorld_ - dot( vertex.tangentWorld_, vertex.vectorNormalWorld_ ) * vertex.vectorNormalWorld_ );
	float3	binormal = cross( vertex.vectorNormalWorld_, tangent );
	float3	vectorVertexToEyeTexture = normalize( mul( vectorVertexToEye, float3x3( tangent, binormal, vertex.vectorNormalWorld_ ) ) );
	float3	normalTexture = normalize( tex2D( samplerTextureNormal, vertex.textureCoord_ + 0.02f * height * vectorVertexToEye.xy ).rgb * 2.0f - 1.0f );
	float3	normal = normalize( mul( normalTexture, float3x3( tangent, binormal, vertex.vectorNormalWorld_ ) ) );
//	normal = vertex.vectorNormalWorld_;

	// �f�B�t���[�Y�F�����߂�
	float	proportionEnvironment = 1.0f - max( dot( normal, vectorVertexToEye ), 0.0f );
	float3	colorDiffuse = colorDiffuse_;

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


	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 0 ] );
	attenuation = attenuationLightPoint_[ 0 ].x
		+ attenuationLightPoint_[ 0 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 0 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 0 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 0 ], vectorLightToVertex, normal );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 0 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 0 ], vectorLightToVertex, normal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 1 ] );
	attenuation = attenuationLightPoint_[ 1 ].x
		+ attenuationLightPoint_[ 1 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 1 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 1 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 1 ], vectorLightToVertex, normal );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 1 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 1 ], vectorLightToVertex, normal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 2 ] );
	attenuation = attenuationLightPoint_[ 2 ].x
		+ attenuationLightPoint_[ 2 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 2 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 2 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 2 ], vectorLightToVertex, normal );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 2 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 2 ], vectorLightToVertex, normal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 3 ] );
	attenuation = attenuationLightPoint_[ 3 ].x
		+ attenuationLightPoint_[ 3 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 3 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 3 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 3 ], vectorLightToVertex, normal );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 3 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 3 ], vectorLightToVertex, normal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 4 ] );
	attenuation = attenuationLightPoint_[ 4 ].x
		+ attenuationLightPoint_[ 4 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 4 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 4 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 4 ], vectorLightToVertex, normal );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 4 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 4 ], vectorLightToVertex, normal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 5 ] );
	attenuation = attenuationLightPoint_[ 5 ].x
		+ attenuationLightPoint_[ 5 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 5 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 5 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 5 ], vectorLightToVertex, normal );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 5 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 5 ], vectorLightToVertex, normal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 6 ] );
	attenuation = attenuationLightPoint_[ 6 ].x
		+ attenuationLightPoint_[ 6 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 6 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 6 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 6 ], vectorLightToVertex, normal );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 6 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 6 ], vectorLightToVertex, normal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 7 ] );
	attenuation = attenuationLightPoint_[ 7 ].x
		+ attenuationLightPoint_[ 7 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 7 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 7 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 7 ], vectorLightToVertex, normal );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 7 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 7 ], vectorLightToVertex, normal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// �|�C���g���C�g�̌��������v�Z
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 8 ] );
	attenuation = attenuationLightPoint_[ 8 ].x
		+ attenuationLightPoint_[ 8 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 8 ].z * distanceLightToVertex * distanceLightToVertex;

	// ���C�g���璸�_�ւ̃x�N�g�������߂�
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 8 ] );

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 8 ], vectorLightToVertex, normal );

	// �|�C���g���C�g�̃X�y�L�����F���v�Z
	specularPoint = CalculateSpecular( colorLightPoint_[ 8 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// �|�C���g���C�g�̃����F���v�Z
	rimPoint = CalculateRim( colorLightPoint_[ 8 ], vectorLightToVertex, normal, vectorVertexToEye );

	// �|�C���g���C�g�̐F���v�Z
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// �l�̐ݒ�
	PixelOutput	output;		// �s�N�Z���V�F�[�_�o��
	output.color_ = float4( color, 0.8f * proportionEnvironment + 0.2f );
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
