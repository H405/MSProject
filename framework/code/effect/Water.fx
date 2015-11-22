//==============================================================================
// 
// File   : Water.fx
// Brief  : ���G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixTransform_;					// �ϊ��s��
float4x4	matrixWorld_;						// ���[���h�ϊ��s��
float4x4	matrixWorldView_;					// ���[���h�r���[�ϊ��s��
float4x4	matrixTransformTexture_;			// �e�N�X�`�����W�ϊ��s��

float4x4	matrixWorldInverseTranspose_;		// ���[���h�t�]�u�s��
texture		textureNormal_;						// �@���e�N�X�`��
float3		colorDiffuse_;						// �f�B�t���[�Y�F
float3		colorSpecular_;						// �X�y�L�����F
float		reflection_;						// ���˗�
float		power_;								// ���˂̋���
float		refractive_;						// ���ܗ�

texture		textureReflect_;					// ���˃e�N�X�`��
texture		texture3D_;							// 3D�`��e�N�X�`��
texture		textureDepth_;						// �[�x�e�N�X�`��

float3		positionEye_;						// �J�����̍��W
float2		clipCamera_;						// �J�����̃N���b�v�l

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTextureNormal = sampler_state
{
	Texture = < textureNormal_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = WRAP;
	AddressV = WRAP;
};

sampler samplerTextureReflect = sampler_state
{
	Texture = < textureReflect_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

sampler samplerTexture3D = sampler_state
{
	Texture = < texture3D_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

sampler samplerTextureDepth = sampler_state
{
	Texture = < textureDepth_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

//******************************************************************************
// �\���̒�`
//******************************************************************************
// ���_�V�F�[�_�o��
struct VertexOutput
{
	float4	position_			: POSITION;			// ���W
	float2	textureCoord_		: TEXCOORD0;		// �e�N�X�`�����W
	float3	positionWorld_		: TEXCOORD1;		// �ϊ�����W
	float3	vectorNormalWorld_	: TEXCOORD2;		// �ϊ���@��
	float3	tangentWorld_		: TEXCOORD3;		// �ϊ���ڐ�
	float	depth_				: TEXCOORD4;		// �[�x
	float4	positionTexture_	: TEXCOORD5;		// �e�N�X�`�����W
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
// Arg    : float3 tangentLocal				: ����
// Arg    : float2 positionTexture			: �e�N�X�`�����W
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 vectorNormalLocal : NORMAL, float3 tangentLocal : TANGENT, float2 textureCoord : TEXCOORD0 )
{
	// ���_�̕ϊ�
	VertexOutput	output;		// ���_�V�F�[�_�o��
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixTransform_ );
	output.positionWorld_ = mul( float4( positionLocal, 1.0f ), matrixWorld_ );
	output.positionTexture_ = mul( float4( positionLocal, 1.0f ), matrixTransformTexture_ );

	// �@���̕ϊ�
	output.vectorNormalWorld_ = normalize( mul( float4( vectorNormalLocal, 0.0f ), matrixWorld_ ) ).xyz;

	// ���ڂ̕ϊ�
	output.tangentWorld_ = normalize( mul( float4( tangentLocal, 0.0f ), matrixWorldInverseTranspose_ ).xyz );

	// �[�x�̌v�Z
	output.depth_ = mul( float4( positionLocal, 1.0f ), matrixWorldView_ ).z;

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
	// �����x�N�g�������߂�
	float3	vectorVertexToEye = normalize( positionEye_ - vertex.positionWorld_ );

	// �������擾
	float	height = tex2D( samplerTextureNormal, vertex.textureCoord_ ).a * 2.0f - 1.0f;

	// �@�������߂�
	float3	tangent = normalize( vertex.tangentWorld_ - dot( vertex.tangentWorld_, vertex.vectorNormalWorld_ ) * vertex.vectorNormalWorld_ );
	float3	binormal = cross( vertex.vectorNormalWorld_, tangent );
	float3	vectorVertexToEyeTexture = normalize( mul( vectorVertexToEye, float3x3( tangent, binormal, vertex.vectorNormalWorld_ ) ) );
	float3	normalTexture = normalize( tex2D( samplerTextureNormal, vertex.textureCoord_ + 0.02f * height * vectorVertexToEye.xy ).rgb * 2.0f - 1.0f );
	float3	normal = normalize( mul( normalTexture, float3x3( tangent, binormal, vertex.vectorNormalWorld_ ) ) );
//	normal = vertex.vectorNormalWorld_;

	// �f�B�t���[�Y�F�����߂�
	float	proportionDepth = (tex2Dproj( samplerTextureDepth, vertex.positionTexture_ ) - vertex.depth_) / clipCamera_.y;
	float	offsetTextureReflect = float4( (normal - vectorVertexToEye).xy * refractive_ * 1000.0f * proportionDepth, 0.0f, 0.0f );
	float	offsetTextureUnder = float4( (normal - vectorVertexToEye).xy * refractive_ * 50.0f, 0.0f, 0.0f );
	float	proportionEnvironment = dot( normal, vectorVertexToEye );
	float3	colorReflerct = tex2Dproj( samplerTextureReflect, vertex.positionTexture_ + offsetTextureReflect );
	float3	colorUnder = tex2Dproj( samplerTexture3D, vertex.positionTexture_ + offsetTextureUnder );
	float3	colorWater = colorDiffuse_ * lerp( colorReflerct, colorUnder, proportionEnvironment );
	float3	colorDiffuse = lerp( tex2Dproj( samplerTexture3D, vertex.positionTexture_ ).rgb, colorWater, min( 200.0f * proportionDepth, 1.0f ) );

	// �l�̐ݒ�
	PixelOutput	output;		// �s�N�Z���V�F�[�_�o��
	output.diffuse_ = float4( colorDiffuse, reflection_ );
	output.specular_ = float4( colorSpecular_, power_ * 0.015625f );
	output.normal_ = float4( normal * 0.5f + 0.5f, refractive_ );
	output.depth_.gba = 0.0f;
	output.depth_.r = vertex.depth_;

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
