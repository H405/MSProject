//==============================================================================
// 
// File   �F Polygon2D.fx
// Brief  �F 2D�|���S���G�t�F�N�g
// Author �F Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixWorld_;			// ���[���h�}�g���N�X
texture		texture_;				// �e�N�X�`��
texture		textureGeneral_;		// �ʏ�`��e�N�X�`��
float4		colorFade_;				// �t�F�[�h�̐F
float		widthScreenHalf_;		// ��ʕ��̔���
float		heightScreenHalf_;		// ��ʍ����̔���
float		proportionFade_;		// �t�F�[�h����

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

sampler samplerTextureGeneral = sampler_state
{
	Texture = < textureGeneral_ >;
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
// Brief  �F ���_�ϊ�
// Return �F VertexOutput					�F ���_�o��
// Arg    �F float4 positionLocal			�F ���[�J�����W
// Arg    �F float3 vectorNormal			�F �@���x�N�g��
// Arg    �F float2 positionTexture			�F �e�N�X�`�����W
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float2 textureCoord : TEXCOORD0, float4 diffuse : COLOR0 )
{
	// ���_�̕ϊ�
	VertexOutput	output;		// �o��
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;
	output.position_ = mul( output.position_, matrixWorld_ );
	output.position_.x /= widthScreenHalf_;
	output.position_.y /= heightScreenHalf_;

	// �l���i�[
	output.textureCoord_ = textureCoord;
	output.diffuse_ = diffuse;

	// ���_�o�͂�Ԃ�
	return output;
}

//==============================================================================
// Brief  �F �s�N�Z���`��
// Return �F float4 : COLOR0				�F �F
// Arg    �F VertexOutput					�F ���_�V�F�[�_�o��
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// �ʏ�`��F�̌���
	float4	colorGeneral = tex2D( samplerTextureGeneral, vertex.textureCoord_ );
	float4	colorFade = tex2D( samplerTexture, vertex.textureCoord_ ) * colorFade_;
	return (1.0f - proportionFade_) * colorGeneral + proportionFade_ * colorFade_;
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