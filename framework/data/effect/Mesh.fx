//==============================================================================
// 
// File   : Mesh.fx
// Brief  : ���b�V���G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixTransform_;		// �ϊ��s��
float4x4	matrixWorld_;			// ���[���h�ϊ��s��
float4x4	matrixWorldView_;		// ���[���h�r���[�ϊ��s��
float2		clipCamera_;			// �J�����̃N���b�v�l
texture		texture_;				// �e�N�X�`��
float3		colorSpecular_;			// �X�y�L�����F
float		reflection_;			// ���˗�
float		power_;					// ���˂̋���
float		refractive_;			// ���ܗ�

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTexture = sampler_state
{
	Texture = < texture_ >;
	MinFilter = Anisotropic;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = Wrap;
	AddressV = Wrap;
	MaxAnisotropy = 8;
};

//******************************************************************************
// �\���̒�`
//******************************************************************************
// ���_�V�F�[�_�o��
struct VertexOutput
{
	float4	position_			: POSITION;			// ���W
	float2	textureCoord_		: TEXCOORD0;		// �e�N�X�`�����W
	float3	vectorNormalWorld_	: TEXCOORD1;		// �ϊ���@��
	float	depth_				: TEXCOORD2;		// �[�x
};

// �s�N�Z���V�F�[�_�o��
struct PixelOutput
{
	float4	diffuse_			: COLOR0;			// �f�B�t���[�Y�F
	float4	specular_			: COLOR1;			// �X�y�L�����F
	float4	normal_				: COLOR2;			// �@��
	float4	depth_				: COLOR3;			// �[�x
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

	// �@���̕ϊ�
	output.vectorNormalWorld_ = normalize( mul( float4( vectorNormalLocal, 0.0f ), matrixWorld_ ) ).xyz;

	// �[�x�̌v�Z
	output.depth_ = mul( float4( positionLocal, 1.0f ), matrixWorldView_ ).z / clipCamera_.y;

	// �o�͒l�̊i�[
	output.textureCoord_ = textureCoord;

	// ���_�V�F�[�_�o�͂�Ԃ�
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
	output.diffuse_ = float4( tex2D( samplerTexture, vertex.textureCoord_ ).rgb, reflection_ );
	output.specular_ = float4( colorSpecular_, power_ * 0.015625f );
	output.normal_ = float4( (vertex.vectorNormalWorld_ * 0.5f + 0.5f), refractive_ );
	output.depth_ = float4( vertex.depth_, 1.0f, 1.0f, 1.0f );

	// ���_�V�F�[�_�o�͂�Ԃ�
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
