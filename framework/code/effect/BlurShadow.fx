//==============================================================================
// 
// File   : BlurBase.fx
// Brief  : �e�p�u���[�G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/12/08 tsu : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float2	offsetTexel_;		// �e�N�Z���I�t�Z�b�g
texture	texture_;			// �e�N�X�`��

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
	float2	textureCoord_	: TEXCOORD0;		// �e�N�X�`�����W
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
	output.textureCoord_ = textureCoord + 0.5f * offsetTexel_;

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
	float3	color = 0.25f * tex2D( samplerTexture, vertex.textureCoord_ ).rgb;
	color += 0.125f * tex2D( samplerTexture, vertex.textureCoord_ + float2( offsetTexel_.x, 0.0f ) );
	color += 0.125f * tex2D( samplerTexture, vertex.textureCoord_ + float2( -offsetTexel_.x, 0.0f ) );
	color += 0.125f * tex2D( samplerTexture, vertex.textureCoord_ + float2( 0.0f, offsetTexel_.y ) );
	color += 0.125f * tex2D( samplerTexture, vertex.textureCoord_ + float2( 0.0f, -offsetTexel_.y ) );
	color += 0.0625f * tex2D( samplerTexture, vertex.textureCoord_ + float2( offsetTexel_.x, offsetTexel_.y ) );
	color += 0.0625f * tex2D( samplerTexture, vertex.textureCoord_ + float2( offsetTexel_.x, -offsetTexel_.y ) );
	color += 0.0625f * tex2D( samplerTexture, vertex.textureCoord_ + float2( -offsetTexel_.x, offsetTexel_.y ) );
	color += 0.0625f * tex2D( samplerTexture, vertex.textureCoord_ + float2( -offsetTexel_.x, -offsetTexel_.y ) );
	return float4( color, 1.0f );
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
