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
float4x4	matrixWorld_;		// ���[���h�}�g���N�X
float2		sizeScreenHalf_;	// ��ʃT�C�Y�̔���
texture		texture_;			// �e�N�X�`��
float2		offset_;			// �I�t�Z�b�g

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
	output.position_.xy /= sizeScreenHalf_;

	// �e�N�X�`�����W���i�[
	output.textureCoord0_ = textureCoord + float2( -2.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord1_ = textureCoord + float2( -4.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord2_ = textureCoord + float2( -6.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord3_ = textureCoord + float2( -8.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord4_ = textureCoord + float2( -10.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord5_ = textureCoord + float2( -12.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord6_ = textureCoord + float2( -14.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord7_ = textureCoord + float2( -16.0f / sizeScreenHalf_.x, 0.0f );

	// ���_�o�͂�Ԃ�
	return output;
}

//==============================================================================
// Brief  : �s�N�Z���`��
// Return : float4 : COLOR0					: �F
// Arg    : VertexOutput					: ���_�V�F�[�_�o��
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// �l�̏o��
	float4		color = float4( 0.13948364567f * (tex2D( samplerTexture, vertex.textureCoord0_ ).rgb + tex2D( samplerTexture, vertex.textureCoord7_ + offset_).rgb), 1.0f );
	color.rgb += 0.12309388525f * (tex2D( samplerTexture, vertex.textureCoord1_ ).rgb + tex2D( samplerTexture, vertex.textureCoord6_ + offset_).rgb);
	color.rgb += 0.09586561422f * (tex2D( samplerTexture, vertex.textureCoord2_ ).rgb + tex2D( samplerTexture, vertex.textureCoord5_ + offset_).rgb);
	color.rgb += 0.06588740886f * (tex2D( samplerTexture, vertex.textureCoord3_ ).rgb + tex2D( samplerTexture, vertex.textureCoord4_ + offset_).rgb);
	color.rgb += 0.03996273355f * (tex2D( samplerTexture, vertex.textureCoord4_ ).rgb + tex2D( samplerTexture, vertex.textureCoord3_ + offset_).rgb);
	color.rgb += 0.02139050984f * (tex2D( samplerTexture, vertex.textureCoord5_ ).rgb + tex2D( samplerTexture, vertex.textureCoord2_ + offset_).rgb);
	color.rgb += 0.01010416138f * (tex2D( samplerTexture, vertex.textureCoord6_ ).rgb + tex2D( samplerTexture, vertex.textureCoord1_ + offset_).rgb);
	color.rgb += 0.00421204112f * (tex2D( samplerTexture, vertex.textureCoord7_ ).rgb + tex2D( samplerTexture, vertex.textureCoord0_ + offset_).rgb);
	return color;
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