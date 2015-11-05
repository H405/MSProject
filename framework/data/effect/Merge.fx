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
float2		sizeScreen_;			// ��ʃT�C�Y

texture		textureLight_;			// ���C�g����e�N�X�`��
texture		textureNotLight_;		// ���C�g�Ȃ��e�N�X�`��
texture		textureMask_;			// �}�X�N�e�N�X�`��
texture		textureAdd_;			// ���Z�����e�N�X�`��

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
	output.position_.xy /= 0.5f * sizeScreen_;

	// �l���i�[
	output.textureCoord_ = textureCoord;

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
	// �s�N�Z���F��Ԃ�
	float	proportion = tex2D( samplerTextureMask , vertex.textureCoord_ );
	float3	colorLight = tex2D( samplerTextureLight , vertex.textureCoord_ ).rgb;
	float3	colorNotLight = tex2D( samplerTextureNotLight , vertex.textureCoord_ ).rgb;
	float3	colorAdd = tex2D( samplerTextureAdd , vertex.textureCoord_ ).rgb;
	return float4( (1.0f - proportion) * colorLight + proportion * colorNotLight + colorAdd, 1.0f );
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
