//==============================================================================
// 
// File   : Shadow.fx
// Brief  : �e�G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/11/24 tsu : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float2		offsetTexel_;					// �e�N�Z���I�t�Z�b�g

float4x4	matrixProjectionInverse_;		// �v���W�F�N�V�����ϊ��t�s��
float4x4	matrixViewInverse_;				// �r���[�ϊ��t�s��
texture		textureDepth_;					// �[�x�e�N�X�`��

float4x4	matrixTransformLight_;			// ���C�g�̕ϊ��s��
float4x4	matrixViewLight_;				// ���C�g�̃r���[�ϊ��s��
texture		textureDepthLight_;				// ���C�g�̐[�x�e�N�X�`��

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTextureDepth = sampler_state
{
	Texture = < textureDepth_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthLight = sampler_state
{
	Texture = < textureDepthLight_ >;
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
// Return : VertexOutput					: ���_�V�F�[�_�o��
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
// Return : float4							: �[�x
// Arg    : VertexOutput					: ���_�V�F�[�_�o��
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// ���[���h���W�����߂�
	float	dataDepth = tex2D( samplerTextureDepth, vertex.textureCoord_ ).r;
	float2	positionTexture = vertex.textureCoord_ * 2.0f - 1.0f;
	float3	positionProjection = mul( float4( positionTexture.x, -positionTexture.y, 1.0f, 1.0f ), matrixProjectionInverse_ ).xyz;
	float3	positionView = float3( positionProjection.xy, 1.0f ) * dataDepth;
	float3	positionWorld = mul( float4( positionView, 1.0f ), matrixViewInverse_ );

	// �e�N�X�`���̍��W�����߂�
	float4	positionLight = mul( float4( positionWorld, 1.0f ), matrixTransformLight_ );
	float2	positionTextureLight = positionLight.xy / positionLight.w;
	positionTextureLight = float2( 1.0f + positionTextureLight.x, 1.0f - positionTextureLight.y );
	positionTextureLight *= 0.5f;

	// �[�x���擾
	float	depthLight = 1000.0f - tex2D( samplerTextureDepthLight, positionTextureLight ).r;
	float	depth = mul( float4( positionWorld, 1.0f ), matrixViewLight_ ).z;

	// �F��Ԃ�
	float4	color;
	color.gba = 0.0f;
	if( depth - depthLight > 2.0f )
	{
		color.r = 0.5f;
	}
	else
	{
		color.r = 1.0f;
	}
//	color.r = depthLight;
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
		// �V�F�[�_�̐ݒ�
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
