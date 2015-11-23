//==============================================================================
// 
// File   : WaveData.fx
// Brief  : �g���G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/11/17 mon : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixWorld_;		// ���[���h�ϊ��s��
texture		textureHeight_;		// �������e�N�X�`��
float3		waveAdd_;			// �g�̒ǉ����

const float	sizeTextureHalf_ = 128.0f;		// �e�N�X�`���̔����̃T�C�Y
const float	offset_ = 1.0f / 256.0f;		// �I�t�Z�b�g
const float	powerSpring_ = 0.5f;			// �΂˂̋���

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTextureHeight = sampler_state
{
	Texture = < textureHeight_ >;
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
};

// �s�N�Z���V�F�[�_�o��
struct PixelOutput
{
	float4	height_				: COLOR0;			// ����
	float4	normal_				: COLOR1;			// �@��
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
	VertexOutput	output;		// �o��
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;

	// �l���i�[
	output.textureCoord_ = textureCoord;
	output.textureCoord_ += float2( 0.5f * offset_, 0.5f * offset_ );

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
	// ���������擾
	float2	heightCurrent = tex2D( samplerTextureHeight, vertex.textureCoord_ ).rg;
	float4	heightAround = float4(
		tex2D( samplerTextureHeight, vertex.textureCoord_ + float2( offset_, 0.0f ) ).r,
		tex2D( samplerTextureHeight, vertex.textureCoord_ + float2( 0.0f, offset_ ) ).r,
		tex2D( samplerTextureHeight, vertex.textureCoord_ - float2( offset_, 0.0f ) ).r,
		tex2D( samplerTextureHeight, vertex.textureCoord_ - float2( 0.0f, offset_ ) ).r
	);

	// ���x���v�Z
	float	velocity = heightAround.r + heightAround.g + heightAround.b + heightAround.a;
	velocity = (0.25f * velocity - heightCurrent.r) * powerSpring_ + heightCurrent.g;
	if( distance( vertex.textureCoord_, waveAdd_.xy ) < 10.0f * offset_ )
	{
		velocity += waveAdd_.z;
	}

	// �������X�V
	PixelOutput	output;		// �s�N�Z���V�F�[�_�o��
	float		height = heightCurrent.r + velocity;
//	height += -0.001f * height;
	output.height_ = float4( height, velocity, 1.0f, 1.0f );

	// �@�����v�Z
	float2	vectorHeight = float2( heightAround.b - heightAround.r, heightAround.a - heightAround.g ) * 0.5f + 0.5f;
	output.normal_ = float4( vectorHeight, 1.0f, 0.5f * heightCurrent.r + 0.5f );

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
