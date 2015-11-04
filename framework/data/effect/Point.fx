//==============================================================================
// 
// File   : Point.fx
// Brief  : �|�C���g�X�v���C�g�G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixView_;			// �r���[�ϊ��s��
float4x4	matrixProjection_;		// �v���W�F�N�V�����ϊ��s��
texture		texture_;				// �e�N�X�`��

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
	float4	position_	: POSITION;		// ���W
	float	size_		: PSIZE;		// �T�C�Y
	float4	color_		: COLOR0;		// �F
};

// �s�N�Z���V�F�[�_�o��
struct PixelOutput
{
	float4	color_		: COLOR0;		// �F
	float4	mask_		: COLOR1;		// �}�X�N
	float4	add_		: COLOR2;		// ���Z����
};

//==============================================================================
// Brief  : ���_�ϊ�
// Return : VertexOutput					: ���_�o��
// Arg    : float4 positionWorld			: ���[���h���W
// Arg    : float size						: �|�C���g�X�v���C�g�̃T�C�Y
// Arg    : float4 color					: �F
//==============================================================================
VertexOutput TransformVertex( float3 positionWorld : POSITION, float size : PSIZE, float4 color : COLOR0 )
{
	// ���_�̕ϊ�
	VertexOutput	output;			// �o��
	float			lengthView;		// �r���[���W�n�̒���
	output.position_ = mul( float4( positionWorld, 1.0f ), matrixView_ );
	lengthView = length( output.position_.xyz );
	output.position_ = mul( output.position_, matrixProjection_ );

	// �T�C�Y�̌v�Z
	output.size_ = 10.0f * size * (matrixProjection_._22 / matrixProjection_._11) * sqrt( 1.0f / lengthView );

	// �l���i�[
	output.color_ = color;

	// ���_�o�͂�Ԃ�
	return output;
}

//==============================================================================
// Brief  : �s�N�Z���`��
// Return : PixelOutput						: �s�N�Z���V�F�[�_�o��
// Arg    : float2 textureCoord				: �e�N�X�`�����W
// Arg    : float4 color					: �F
//==============================================================================
PixelOutput DrawPixel( float2 textureCoord : TEXCOORD0, float4 color : COLOR0 )
{
	// �l�̐ݒ�
	PixelOutput	output;		// �s�N�Z���V�F�[�_�o��
	output.color_ = 0.0f;
	output.mask_ = 0.0f;
	output.add_ = tex2D( samplerTexture, textureCoord ) * color;

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
		// �����_�[�X�e�[�g�̐ݒ�
		PointSpriteEnable = True;
		ZWriteEnable = False;
		AlphaBlendEnable = True;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = One;

		// �V�F�[�_�̐ݒ�
		VertexShader = compile vs_2_0 TransformVertex();
		PixelShader = compile ps_2_0 DrawPixel();
	}
}