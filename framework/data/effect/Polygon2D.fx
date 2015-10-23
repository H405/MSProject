//==============================================================================
// 
// File   �F Polygon2D.fx
// Brief  �F 2D�|���S���G�t�F�N�g
// Author �F Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixWorld_;			// ���[���h�}�g���N�X
texture		texture_;				// �e�N�X�`��
float		widthScreenHalf_;		// ��ʕ��̔���
float		heightScreenHalf_;		// ��ʍ����̔���
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

// �s�N�Z���V�F�[�_�o��
struct PixelOutput
{
	float4	color0_			: COLOR0;			// �F
	float4	color1_			: COLOR1;			// �}�X�N
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
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;
	output.position_ = mul( output.position_, matrixWorld_ );
	output.position_.x /= widthScreenHalf_;
	output.position_.y /= heightScreenHalf_;

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
PixelOutput DrawPixel( VertexOutput vertex )
{
	// �s�N�Z���F��Ԃ�
	PixelOutput	output;		// �o��
	output.color0_ = tex2D( samplerTexture, vertex.textureCoord_ ) * color_;
	output.color1_ = float4( 1.0f, 0.0f, 0.0f, output.color0_.a );
	return output;
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
		ZEnable = False;
		ZWriteEnable = False;
		AlphaBlendEnable = True;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		// �V�F�[�_�̐ݒ�
		VertexShader = compile vs_2_0 TransformVertex();
		PixelShader = compile ps_2_0 DrawPixel();
	}
}