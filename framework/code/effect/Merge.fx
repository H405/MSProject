//==============================================================================
// 
// File   : Merge.fx
// Brief  : ����3D�`��G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/11/03 sun : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixWorld_;			// ���[���h�ϊ��s��
float2		sizeScreenHalf_;		// ��ʃT�C�Y�̔���
float		forcus_;				// �œ_����

texture		textureLight_;			// ���C�g����e�N�X�`��
texture		textureNotLight_;		// ���C�g�Ȃ��e�N�X�`��
texture		textureMask_;			// �}�X�N�e�N�X�`��
texture		textureAdd_;			// ���Z�����e�N�X�`��
texture		textureDepth_;			// �[�x�e�N�X�`��
texture		textureRiver_;			// ��e�N�X�`��
texture		textureDepthRiver_;		// ��[�x�e�N�X�`��

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTextureLight = sampler_state
{
	Texture = < textureLight_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureNotLight = sampler_state
{
	Texture = < textureNotLight_ >;
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

sampler samplerTextureAdd = sampler_state
{
	Texture = < textureAdd_ >;
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

sampler samplerTextureRiver = sampler_state
{
	Texture = < textureRiver_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthRiver = sampler_state
{
	Texture = < textureDepthRiver_ >;
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

// �s�N�Z���V�F�[�_�o��
struct PixelOutput
{
	float4	color_			: COLOR0;			// ���W
	float4	depth_			: COLOR1;			// �[�x
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
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;
	output.position_ = mul( output.position_, matrixWorld_ );
	output.position_.xy /= sizeScreenHalf_;

	// �l���i�[
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
	PixelOutput	output;
	float	maskLight = tex2D( samplerTextureMask , vertex.textureCoord_ );
	float3	colorLight = tex2D( samplerTextureLight , vertex.textureCoord_ ).rgb;
	float3	colorNotLight = tex2D( samplerTextureNotLight , vertex.textureCoord_ ).rgb;
	float3	colorAdd = tex2D( samplerTextureAdd , vertex.textureCoord_ ).rgb;
	float4	colorRiver = tex2D( samplerTextureRiver , vertex.textureCoord_ );

	// �[�x�̎擾
	float	depthRiver = tex2D( samplerTextureDepthRiver, vertex.textureCoord_ ).r;
	output.depth_.gba = 0.0f;
	output.depth_.r = (1.0f - maskLight) * tex2D( samplerTextureDepth , vertex.textureCoord_ ).r + maskLight * forcus_;

	// �F�����߂�
	float	proportionRiver = colorRiver.a;// * max( (output.depth_.r - depthRiver), 0.0f ) / output.depth_.r;
	float3	colorLightAndRiver = (1.0f - proportionRiver) * colorLight + proportionRiver * colorRiver;
	output.color_ = float4( (1.0f - maskLight) * colorLightAndRiver + maskLight * colorNotLight + colorAdd, 1.0f );

	// �l��Ԃ�
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
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
