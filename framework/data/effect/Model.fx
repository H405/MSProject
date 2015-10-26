//==============================================================================
// 
// File   �F Model.fx
// Brief  �F ���f���G�t�F�N�g
// Author �F Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixTransform_;					// �ϊ��s��
float4x4	matrixWorld_;						// ���[���h�ϊ��s��
float3		positionEye_;						// �J�����̍��W
float3		colorAmbient_;						// ���F
float3		vectorLightDirection_;				// �f�B���N�V���i�����C�g�̃x�N�g��
float3		colorLightDirection_;				// �f�B���N�V���i�����C�g�̐F
float3		positionLightPoint_[ 32 ];			// �|�C���g���C�g���C�g�̍��W
float3		colorLightPoint_[ 32 ];				// �|�C���g���C�g���C�g�̐F
float3		attenuationLightPoint_[ 32 ];		// �|�C���g���C�g�̌�����
int			countLightPoint_;					// �|�C���g���C�g�̐�
texture		texture_;							// �e�N�X�`��
float3		colorSpecular_;						// �X�y�L�����F
float		reflection_;						// ���˗�
float		power_;								// ���˂̋���
float		refractive_;						// ���ܗ�

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTexture = sampler_state
{
	Texture = < texture_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = Clamp;
	AddressV = Clamp;
};

//******************************************************************************
// �\���̒�`
//******************************************************************************
// ���_�V�F�[�_�o��
struct VertexOutput
{
	float4	position_			: POSITION;			// ���W
	float2	textureCoord_		: TEXCOORD0;		// �e�N�X�`�����W
	float3	positionWorld_		: TEXCOORD1;		// ���[���h���W
	float3	vectorNormalWorld_	: TEXCOORD2;		// ���[���h�@��
};

//==============================================================================
// Brief  �F �f�B�t���[�Y�̌v�Z
// Return �F float3							�F �F
// Arg    �F float3 colorLight				�F ���C�g�̐F
// Arg    �F float3 vectorLight				�F ���C�g�̃x�N�g��
// Arg    �F float3 vectorNormal			�F �@���x�N�g��
//==============================================================================
float3 CalculateDiffuse( float3 colorLight, float3 vectorLight, float3 vectorNormal )
{
	// ���x�̌v�Z
	float	lightness = dot( vectorNormal, -vectorLight ) * 0.5f + 0.5f;

	// �f�B�t���[�Y�F��Ԃ�
	return colorLight * lightness;
}

//==============================================================================
// Brief  �F �X�y�L�����̌v�Z
// Return �F float3							�F �F
// Arg    �F float3 colorLight				�F ���C�g�̐F
// Arg    �F float3 vectorLight				�F ���C�g�̃x�N�g��
// Arg    �F float3 vectorNormal			�F �@���x�N�g��
// Arg    �F float3 vectorVertexToEye		�F ���_���王�_�ւ̃x�N�g��
//==============================================================================
float3 CalculateSpecular( float3 colorLight, float3 vectorLight, float3 vectorNormal, float3 vectorVertexToEye )
{
	// �n�[�t�x�N�g�������߂�
	float3	vectorHalf = normalize( vectorVertexToEye - vectorLight );

	// �X�y�L�����F��Ԃ�
	return colorLight * pow( max( dot( vectorNormal, vectorHalf ), 0.0f ), power_ ) * reflection_;
}

//==============================================================================
// Brief  �F �����̌v�Z
// Return �F float3							�F �F
// Arg    �F float3 colorLight				�F ���C�g�̐F
// Arg    �F float3 vectorLight				�F ���C�g�̃x�N�g��
// Arg    �F float3 vectorNormal			�F �@���x�N�g��
// Arg    �F float3 vectorVertexToEye		�F ���_���王�_�ւ̃x�N�g��
//==============================================================================
float3 CalculateRim( float3 colorLight, float3 vectorLight, float3 vectorNormal, float3 vectorVertexToEye )
{
	// �����F��Ԃ�
	float	rim = (1.0f - max( dot( vectorNormal, vectorVertexToEye ), 0.0f )) * max( dot( vectorLight, vectorVertexToEye ), 0.0f );
	rim = min( 5.0f * pow( rim, 5.0f ), 1.0f );
	return colorLight * rim;
}

//==============================================================================
// Brief  �F ���_�ϊ�
// Return �F VertexOutput					�F ���_�o��
// Arg    �F float4 positionLocal			�F ���[�J�����W
// Arg    �F float3 vectorNormalLocal		�F �@���x�N�g��
// Arg    �F float2 positionTexture			�F �e�N�X�`�����W
// Arg    �F float4 colorDiffuse			�F �f�B�t���[�Y�F
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 vectorNormalLocal : NORMAL, float2 textureCoord : TEXCOORD0 )
{
	// ���_�̕ϊ�
	VertexOutput	output;		// �o��
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixTransform_ );

	// ���[���h���_�̕ϊ�
	output.positionWorld_ = mul( float4( positionLocal.xyz, 1.0f ), matrixWorld_ ).xyz;

	// ���[���h�@���̕ϊ�
	output.vectorNormalWorld_ = normalize( mul( float4( vectorNormalLocal, 0.0f ), matrixWorld_ ) ).xyz;

	// �o�͒l�̊i�[
	output.textureCoord_ = textureCoord;

	// ���_�o�͂�Ԃ�
	return output;
}

//==============================================================================
// Brief  �F �s�N�Z���`��
// Return �F float4 : COLOR0				�F �F
// Arg    �F VertexOutput					�F ���_�V�F�[�_�o��
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// ���_���王�_�ւ̃x�N�g�������߂�
	float3	vectorVertexToEye = normalize( positionEye_ - vertex.positionWorld_.xyz );

	// ���f���̃f�B�t���[�Y�F�����߂�
	float4	colorDiffuse = tex2D( samplerTexture, vertex.textureCoord_ );

	// �����̃X�y�L�����F���v�Z
	float	fresnel = refractive_ + (1.0f - refractive_) * exp( -6.0f * max( dot( vertex.vectorNormalWorld_, vectorVertexToEye ), 0.0f ) );
	float3	specularAmbient = colorAmbient_.rgb * fresnel;

	// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
	float3	diffuseDirection = CalculateDiffuse( colorLightDirection_, vectorLightDirection_, vertex.vectorNormalWorld_ );

	// �f�B���N�V���i�����C�g�̃X�y�L�����F���v�Z
	float3	specularDirection = CalculateSpecular( colorLightDirection_, vectorLightDirection_, vertex.vectorNormalWorld_, vectorVertexToEye );

	// �f�B���N�V���i�����C�g�̃����F���v�Z
	float3	rimDirection = CalculateRim( colorLightDirection_, vectorLightDirection_, vertex.vectorNormalWorld_, vectorVertexToEye );

	// �����ƃf�B���N�V���i�����C�g�̐F���v�Z
	float3	color = colorDiffuse.rgb * (diffuseDirection + colorAmbient_) + colorSpecular_ * (specularDirection + specularAmbient ) + rimDirection;

	// �|�C���g���C�g�̐F���v�Z
	for( int counterLight = 0; counterLight < countLightPoint_; ++counterLight )
	{
		// ���C�g���璸�_�ւ̃x�N�g�������߂�
		float3	vectorLightToVertex = normalize( vertex.positionWorld_.xyz - positionLightPoint_[ counterLight ] );

		// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�F���v�Z
		float3	diffusePoint = CalculateDiffuse( colorLightPoint_[ counterLight ], vectorLightToVertex, vertex.vectorNormalWorld_ );

		// �|�C���g���C�g�̃X�y�L�����F���v�Z
		float3	specularPoint = CalculateSpecular( colorLightPoint_[ counterLight ], vectorLightToVertex, vertex.vectorNormalWorld_, vectorVertexToEye );

		// �|�C���g���C�g�̃����F���v�Z
		float3	rimPoint = CalculateRim( colorLightPoint_[ counterLight ], vectorLightToVertex, vertex.vectorNormalWorld_, vectorVertexToEye );

		// �|�C���g���C�g�̌��������v�Z
		float	distanceLightToVertex = distance( vertex.positionWorld_.xyz, positionLightPoint_[ counterLight ] );
		float	attenuation = attenuationLightPoint_[ counterLight ].x
			+ attenuationLightPoint_[ counterLight ].y * distanceLightToVertex
			+ attenuationLightPoint_[ counterLight ].z * distanceLightToVertex * distanceLightToVertex;

		// �|�C���g���C�g�̐F���v�Z
		color += (colorDiffuse.rgb * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;
	}

	// �s�N�Z���F��Ԃ�
	return float4( color, colorDiffuse.a );
}

//==============================================================================
// Brief  �F �ʏ�ϊ�
//==============================================================================
technique ShadeNormal
{
	// �ʏ�ϊ�
	pass PassNormal
	{
		// �����_�[�X�e�[�g�̐ݒ�
		AlphaBlendEnable = True;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		// �V�F�[�_�̐ݒ�
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
