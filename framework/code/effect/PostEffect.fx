//==============================================================================
// 
// File   : PostEffect.fx
// Brief  : �|�X�g�G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float2		offsetTexel_;			// �e�N�Z���I�t�Z�b�g
float4		colorFade_;				// �t�F�[�h�̐F
float		proportionFade_;		// �t�F�[�h����
float		forcus_;				// �œ_����
texture		texture_;				// �e�N�X�`��
texture		texture3D_;				// 3D�`��e�N�X�`��
texture		textureLuminance_;		// �P�x�e�N�X�`��
texture		textureBlur_;			// �u���[�e�N�X�`��
texture		textureDepth_;			// �[�x�e�N�X�`��
texture		texture2D_;				// 2D�`��e�N�X�`��
texture		textureMask_;			// �}�X�N�e�N�X�`��

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTexture = sampler_state
{
	Texture = < texture_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = Clamp;
	AddressV = Clamp;
};

sampler samplerTexture3D = sampler_state
{
	Texture = < texture3D_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureLuminance = sampler_state
{
	Texture = < textureLuminance_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureBlur = sampler_state
{
	Texture = < textureBlur_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepth = sampler_state
{
	Texture = < textureDepth_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTexture2D = sampler_state
{
	Texture = < texture2D_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureMask = sampler_state
{
	Texture = < textureMask_ >;
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
	float4	diffuse_		: COLOR0;			// �f�B�t���[�Y�F
	float2	textureCoord_	: TEXCOORD0;		// �e�N�X�`�����W
};

//==============================================================================
// Brief  : ���_�ϊ�
// Return : VertexOutput					: ���_�o��
// Arg    : float4 positionLocal			: ���[�J�����W
// Arg    : float3 vectorNormal				: �@���x�N�g��
// Arg    : float2 positionTexture			: �e�N�X�`�����W
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float2 textureCoord : TEXCOORD0, float4 diffuse : COLOR0 )
{
	// ���_�̕ϊ�
	VertexOutput	output;		// �o��
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;

	// �l���i�[
	output.textureCoord_ = textureCoord + offsetTexel_;
	output.diffuse_ = diffuse;

	// ���_�o�͂�Ԃ�
	return output;
}

//==============================================================================
// Brief  : �s�N�Z���`��
// Return : float4 : COLOR0					: �F
// Arg    : VertexOutput					: ���_�V�F�[�_�o��
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// �t�H�[�J�X�̎Z�o
	float	proportion = tex2D( samplerTextureDepth, vertex.textureCoord_ ).r - forcus_;
	if( proportion < 0.0f )
	{
		proportion /= -0.8f * forcus_;
	}
	else
	{
		proportion /= max( 0.6f - 1.6f * forcus_, 0.004f );
	}
	proportion = min( proportion, 1.0f );
	proportion *= proportion;
//	proportion *= proportion;
//	proportion = min( 4.0f * proportion, 1.0f );
//	return float4( proportion, proportion, proportion, 1.0f );

	// �ʏ�`��F�̌���
	float3	color3D = (1.0f - proportion) * tex2D( samplerTexture3D, vertex.textureCoord_ ).rgb + proportion * tex2D( samplerTextureBlur, vertex.textureCoord_ ).rgb;
	float3	color3DLuminance = color3D + tex2D( samplerTextureLuminance, vertex.textureCoord_ ).rgb;
	float	mask = tex2D( samplerTextureMask, vertex.textureCoord_ ).r;
	float3	colorGeneral = (1.0f - mask) * color3DLuminance + mask * tex2D( samplerTexture2D, vertex.textureCoord_ ).rgb;
	float3	colorFade = tex2D( samplerTexture, vertex.textureCoord_ ).rgb * colorFade_;
	return float4( (1.0f - proportionFade_) * colorGeneral + proportionFade_ * colorFade_, 1.0f );
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
