//==============================================================================
// 
// File   �F Sky.fx
// Brief  �F ��G�t�F�N�g
// Author �F Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixTransform_;		// �ϊ��s��
texture		texture_;				// �e�N�X�`��

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTexture = sampler_state
{
	Texture = < texture_ >;
	MinFilter = Linear;
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
	float4	diffuse_				: COLOR0;			// �f�B�t���[�Y�F
	float4	specular_				: COLOR1;			// �X�y�L�����F
	float4	normal_					: COLOR2;			// �@��
	float4	depth_					: COLOR3;			// �[�x
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

	// �o�͒l�̊i�[
	output.textureCoord_ = textureCoord;

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
	// �s�N�Z���F��Ԃ�
	PixelOutput	output;		// �s�N�Z���V�F�[�_�o��

	// �l�̐ݒ�
	output.diffuse_ = tex2D( samplerTexture, vertex.textureCoord_ );
	output.specular_ = 1.0f;
	output.normal_ = 0.5f;
	output.depth_ = 1.0f;

	// ���_�V�F�[�_�o�͂�Ԃ�
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
		VertexShader = compile vs_2_0 TransformVertex();
		PixelShader = compile ps_2_0 DrawPixel();
	}
}