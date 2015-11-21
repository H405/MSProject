//==============================================================================
// 
// File   : WaveData.fx
// Brief  : �g��񏉊����G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/11/17 mon : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixWorld_;		// ���[���h�}�g���N�X
texture		texture_;			// �e�N�X�`��

const float	offset_ = 1.0f / 256.0f;		// �e�N�X�`���̔����̃T�C�Y

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
	float4	height_			: COLOR0;			// ����
	float4	normal_			: COLOR1;			// �@��
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
	output.position_.xy *= 2.0f;

	// �l�̐ݒ�
	output.textureCoord_ = textureCoord;
	output.textureCoord_ += float2( 0.5f * offset_, 0.5f * offset_ );

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
	float4		color = tex2D( samplerTexture, vertex.textureCoord_ );
	output.height_ = float4( color.rg - color.ba, 1.0f, 1.0f );
	output.normal_ = float4( 0.5f, 0.5f, 1.0f, 0.0f );
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
		// �V�F�[�_�̐ݒ�
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
