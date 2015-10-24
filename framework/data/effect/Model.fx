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
float3		attemuationLightPoint_[ 32 ];		// �|�C���g���C�g�̌�����
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
// Brief  �F �f�B���N�V���i�����C�g�̃f�B�t���[�Y
// Return �F float3							�F �F
// Arg    �F float3 vectorNormalWorld		�F �@���x�N�g��
//==============================================================================
float3 CalculateDiffuseDirection( float3 vectorNormal )
{
	// ���x�̌v�Z
	float	lightness = dot( vectorNormal, -vectorLightDirection_ ) * 0.5f + 0.5f;

	// �f�B�t���[�Y�F��Ԃ�
	return colorLightDirection_ * lightness + colorLightDirection_ * colorAmbient_.rgb;
}

//==============================================================================
// Brief  �F �f�B���N�V���i�����C�g�̃X�y�L����
// Return �F float3							�F �F
// Arg    �F float3 vectorNormalWorld		�F �@���x�N�g��
// Arg    �F float3 vectorVertexToEye		�F ���_���王�_�ւ̃x�N�g��
//==============================================================================
float3 CalculateSpecularDirection( float3 vectorNormal, float3 vectorVertexToEye )
{
	// �n�[�t�x�N�g�������߂�
	float3	vectorHalf = normalize( vectorVertexToEye - vectorLightDirection_ );

	// �X�y�L�����F��Ԃ�
	return colorLightDirection_ * pow( max( dot( vectorNormal, vectorHalf ), 0.0f ), power_ ) * reflection_;
}

//==============================================================================
// Brief  �F �f�B���N�V���i�����C�g�̃���
// Return �F float3							�F �F
// Arg    �F float3 vectorNormalWorld		�F �@���x�N�g��
// Arg    �F float3 vectorVertexToEye		�F ���_���王�_�ւ̃x�N�g��
//==============================================================================
float3 CalculateRimDirection( float3 vectorNormal, float3 vectorVertexToEye )
{
	// �����F��Ԃ�
	float	rim = (1.0f - max( dot( vectorNormal, vectorVertexToEye ), 0.0f )) * max( dot( vectorLightDirection_, vectorVertexToEye ), 0.0f );
	rim = min( 5.0f * pow( rim, 5.0f ), 1.0f );
	return colorLightDirection_ * rim;
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
	float3	diffuseDirection = CalculateDiffuseDirection( vertex.vectorNormalWorld_ );

	// �f�B���N�V���i�����C�g�̃X�y�L�����F���v�Z
	float3	specularDirection = CalculateSpecularDirection( vertex.vectorNormalWorld_, vectorVertexToEye );

	// �f�B���N�V���i�����C�g�̃����F���v�Z
	float3	rimDirection = CalculateRimDirection( vertex.vectorNormalWorld_, vectorVertexToEye );

	// �s�N�Z���F��Ԃ�
	float3	color = colorDiffuse.rgb * (diffuseDirection + colorAmbient_) + colorSpecular_ * (specularDirection + specularAmbient ) + rimDirection;
	return float4( color, colorDiffuse.a );

//	// ���x�̌v�Z
//	float	lightness = GetLightness( vertex.vectorNormalWorld_ );//dot( vertex.vectorNormalWorld_, -vectorLight_ ) * 0.5f + 0.5f;
//
//	// �f�B�t���[�Y�F�̌v�Z
//	float3	diffuse = colorDiffuse_.rgb * tex2D( samplerTexture, vertex.textureCoord_ ) * lightness * colorLight_.rgb + colorAmbient_.rgb;
//
//	// �t���l�����˗����Z�o
//	float3	vectorVertexToEye = normalize( positionEye_ - vertex.positionWorld_.xyz );
//	float	fresnel = refractive_ + (1.0f - refractive_) * exp( -6.0f * max( dot( vertex.vectorNormalWorld_, vectorVertexToEye ), 0.0f ) );
//
//	// �X�y�L�����F�̎Z�o
//	float3	vectorHalf = normalize( vectorVertexToEye - vectorLight_ );
//	float3	specular = colorSpecular_.rgb * (pow( max( dot( vertex.vectorNormalWorld_, vectorHalf ), 0.0f ), power_ ) * reflection_ + colorAmbient_.rgb * fresnel);
////	float3	specular = colorSpecular_.rgb * (pow( max( dot( reflect( vectorLight_, vertex.vectorNormalWorld_ ), vectorVertexToEye ), 0.0f ), power_ ) * reflection_ + colorAmbient_.rgb * fresnel);
//
//	// �s�N�Z���F��Ԃ�
//	return float4( diffuse + specular, colorDiffuse_.a );
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
		VertexShader = compile vs_2_0 TransformVertex();
		PixelShader = compile ps_2_0 DrawPixel();
	}
}