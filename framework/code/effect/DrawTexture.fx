//==============================================================================
// 
// File   : DrawTexture.fx
// Brief  : �f�o�b�O�p�e�N�X�`���\���G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/11/27 fri : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float2	offsetTexel_;		// �e�N�Z���I�t�Z�b�g
texture	texture_;			// �e�N�X�`��
float3	multiply_;			// �F�̔{��

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTexture = sampler_state
{
	Texture = < texture_ >;
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
// Return : float4							: �F
// Arg    : VertexOutput					: ���_�V�F�[�_�o��
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// �s�N�Z���F��Ԃ�
	float4	color = tex2D( samplerTexture , vertex.textureCoord_ );
	color.rgb *= multiply_;
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
