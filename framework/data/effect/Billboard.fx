//==============================================================================
// 
// File   �F Billboard.fx
// Brief  �F �r���{�[�h�G�t�F�N�g
// Author �F Taiga Shirakawa
// Date   : 2015/10/23 fri : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixTransform_;		// �ϊ��s��
texture		texture_;				// �e�N�X�`��
float4		color_;					// �F
float2		positionTexture_;		// �e�N�X�`�����W
float2		scaleTexture_;			// �e�N�X�`���g�k

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTexture = sampler_state
{
	Texture = < texture_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = Wrap;
	AddressV = Wrap;
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
// Brief  �F ���_�ϊ�
// Return �F VertexOutput					�F ���_�o��
// Arg    �F float4 positionLocal			�F ���[�J�����W
// Arg    �F float2 positionTexture			�F �e�N�X�`�����W
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float2 textureCoord : TEXCOORD0 )
{
	// ���_�̕ϊ�
	VertexOutput	output;		// �o��
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixTransform_ );

	// �e�N�X�`�����W�̕ϊ�
	output.textureCoord_ = textureCoord / scaleTexture_ + positionTexture_;

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
	// �s�N�Z���F��Ԃ�
	return tex2D( samplerTexture, vertex.textureCoord_ ) * color_;
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