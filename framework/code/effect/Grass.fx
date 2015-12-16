//==============================================================================
// 
// File   : Grass.fx
// Brief  : ���G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/12/10 fri : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixTransform_;		// �ϊ��s��
float4x4	matrixWorldView_;		// ���[���h�r���[�ϊ��s��
texture		texture_;				// �e�N�X�`��
float2		vectorWind_;			// ������

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
	float	depth_			: TEXCOORD1;		// �[�x
};

// �s�N�Z���V�F�[�_�o��
struct PixelOutput
{
	float4	diffuse_		: COLOR0;			// �f�B�t���[�Y�F
	float4	specular_		: COLOR1;			// �X�y�L�����F
	float4	normal_			: COLOR2;			// �@��
	float4	depth_			: COLOR3;			// �[�x
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
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixTransform_ );
	output.position_.xy += positionLocal.y * vectorWind_;

	// �e�N�X�`�����W�̕ϊ�
	output.textureCoord_ = textureCoord;

	// �[�x�̌v�Z
	output.depth_ = mul( float4( positionLocal, 1.0f ), matrixWorldView_ ).z;

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
	// �`�悷�邩����
	float4	color = tex2D( samplerTexture, vertex.textureCoord_ );
	clip( color.a - 0.5f );

	// �l�̐ݒ�
	PixelOutput	output;		// �s�N�Z���V�F�[�_�o��
	output.diffuse_ = float4( color.rgb, 0.1f );
	output.specular_ = float4( 0.02f, 0.05f, 0.04f, 0.078125f );
	output.normal_ = float4( 0.0f, 1.0f, 0.0f, 0.5f );
	output.depth_ = 0.0f;
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
