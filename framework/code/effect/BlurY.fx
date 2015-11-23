//==============================================================================
// 
// File   : BlurBase.fx
// Brief  : �u���[��G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/11/10 tsu : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float2		offset_;			// �I�t�Z�b�g
texture		texture_;			// �e�N�X�`��
float2		offsetBlur_;		// �u���[�̃I�t�Z�b�g

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
	float4	position_		: POSITION;			// ���W
	float2	textureCoord0_	: TEXCOORD0;		// �e�N�X�`�����W
	float2	textureCoord1_	: TEXCOORD1;		// �e�N�X�`�����W
	float2	textureCoord2_	: TEXCOORD2;		// �e�N�X�`�����W
	float2	textureCoord3_	: TEXCOORD3;		// �e�N�X�`�����W
	float2	textureCoord4_	: TEXCOORD4;		// �e�N�X�`�����W
	float2	textureCoord5_	: TEXCOORD5;		// �e�N�X�`�����W
	float2	textureCoord6_	: TEXCOORD6;		// �e�N�X�`�����W
	float2	textureCoord7_	: TEXCOORD7;		// �e�N�X�`�����W
};

// �s�N�Z���V�F�[�_�o��
struct PixelOutput
{
	float4	color_			: COLOR0;			// �F
	float4	luminance_		: COLOR1;			// �P�x
};

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

	// �e�N�X�`�����W���i�[
	output.textureCoord0_ = textureCoord + offset_ + float2( 0.0f, -4.0f * offset_.y );
	output.textureCoord1_ = textureCoord + offset_ + float2( 0.0f, -8.0f * offset_.y );
	output.textureCoord2_ = textureCoord + offset_ + float2( 0.0f, -12.0f* offset_.y );
	output.textureCoord3_ = textureCoord + offset_ + float2( 0.0f, -16.0f* offset_.y );
	output.textureCoord4_ = textureCoord + offset_ + float2( 0.0f, -20.0f * offset_.y );
	output.textureCoord5_ = textureCoord + offset_ + float2( 0.0f, -24.0f * offset_.y );
	output.textureCoord6_ = textureCoord + offset_ + float2( 0.0f, -28.0f * offset_.y );
	output.textureCoord7_ = textureCoord + offset_ + float2( 0.0f, -32.0f * offset_.y );

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
	// �l�̏o��
	PixelOutput	output;		// �o�͒l
	float4		color = float4( 0.13948364567f * (tex2D( samplerTexture, vertex.textureCoord0_ ).rgb + tex2D( samplerTexture, vertex.textureCoord7_ + offsetBlur_).rgb), 1.0f );
	color.rgb += 0.12309388525f * (tex2D( samplerTexture, vertex.textureCoord1_ ).rgb + tex2D( samplerTexture, vertex.textureCoord6_ + offsetBlur_).rgb);
	color.rgb += 0.09586561422f * (tex2D( samplerTexture, vertex.textureCoord2_ ).rgb + tex2D( samplerTexture, vertex.textureCoord5_ + offsetBlur_).rgb);
	color.rgb += 0.06588740886f * (tex2D( samplerTexture, vertex.textureCoord3_ ).rgb + tex2D( samplerTexture, vertex.textureCoord4_ + offsetBlur_).rgb);
	color.rgb += 0.03996273355f * (tex2D( samplerTexture, vertex.textureCoord4_ ).rgb + tex2D( samplerTexture, vertex.textureCoord3_ + offsetBlur_).rgb);
	color.rgb += 0.02139050984f * (tex2D( samplerTexture, vertex.textureCoord5_ ).rgb + tex2D( samplerTexture, vertex.textureCoord2_ + offsetBlur_).rgb);
	color.rgb += 0.01010416138f * (tex2D( samplerTexture, vertex.textureCoord6_ ).rgb + tex2D( samplerTexture, vertex.textureCoord1_ + offsetBlur_).rgb);
	color.rgb += 0.00421204112f * (tex2D( samplerTexture, vertex.textureCoord7_ ).rgb + tex2D( samplerTexture, vertex.textureCoord0_ + offsetBlur_).rgb);
	output.color_ = color;
	output.luminance_ = color * pow( (0.298912f * color.r + 0.586611f * color.g + 0.114478f * color.b), 2.0f );
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
