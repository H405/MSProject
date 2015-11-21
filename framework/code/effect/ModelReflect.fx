//==============================================================================
// 
// File   : ModelReflect.fx
// Brief  : ���˃��f���G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/11/21 sat : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixTransform_;		// �ϊ��s��
float4x4	matrixWorld_;			// ���[���h�ϊ��s��
texture		texture_;				// �e�N�X�`��
float		height_;				// ���˖ʂ̍���

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTexture = sampler_state
{
	Texture = < texture_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = WRAP;
	AddressV = WRAP;
};

//******************************************************************************
// �\���̒�`
//******************************************************************************
// ���_�V�F�[�_�o��
struct VertexOutput
{
	float4	position_			: POSITION;			// ���W
	float2	textureCoord_		: TEXCOORD0;		// �e�N�X�`�����W
	float	heightWorld_		: TEXCOORD1;		// ���[���h���W�̍���
};

//==============================================================================
// Brief  : ���_�ϊ�
// Return : VertexOutput					: ���_�V�F�[�_�o��
// Arg    : float4 positionLocal			: ���[�J�����W
// Arg    : float3 vectorNormalLocal		: �@���x�N�g��
// Arg    : float2 positionTexture			: �e�N�X�`�����W
// Arg    : float4 colorDiffuse				: �f�B�t���[�Y�F
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 vectorNormalLocal : NORMAL, float2 textureCoord : TEXCOORD0 )
{
	// ���_�̕ϊ�
	VertexOutput	output;		// ���_�V�F�[�_�o��
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixTransform_ );
	output.heightWorld_ = mul( float4( positionLocal, 1.0f ), matrixWorld_ ).y;

	// �o�͒l�̊i�[
	output.textureCoord_ = textureCoord;

	// ���_�V�F�[�_�o�͂�Ԃ�
	return output;
}

//==============================================================================
// Brief  : �s�N�Z���`��
// Return : float4							: �F
// Arg    : VertexOutput					: ���_�V�F�[�_�o��
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// ���˖ʂ�艺�͕`�悵�Ȃ�
	clip( height_ - vertex.heightWorld_ );

	// �F��Ԃ�
	return tex2D( samplerTexture, vertex.textureCoord_ );
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
		CullMode = CW;

		// �V�F�[�_�̐ݒ�
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
