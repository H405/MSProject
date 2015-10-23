//==============================================================================
// 
// File   �F Mesh.fx
// Brief  �F ���b�V���G�t�F�N�g
// Author �F Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixTransform_;		// �ϊ��s��
float4x4	matrixWorld_;			// ���[���h�ϊ��s��
float3		vectorLight_;			// ���C�g�x�N�g��
float3		positionEye_;			// �J�����̍��W
texture		texture_;				// �e�N�X�`��
float4		colorAmbient_;			// ���F
float4		colorLight_;			// ���C�g�̐F
float4		colorDiffuse_;			// �f�B�t���[�Y�F
float4		colorSpecular_;			// �X�y�L�����F
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
	float4	colorDiffuse_		: COLOR0;			// �f�B�t���[�Y�F
	float2	textureCoord_		: TEXCOORD0;		// �e�N�X�`�����W
	float3	positionWorld_		: TEXCOORD1;		// ���[���h���W
	float3	vectorNormalWorld_	: TEXCOORD2;		// ���[���h�@��
};

//==============================================================================
// Brief  �F ���_�ϊ�
// Return �F VertexOutput					�F ���_�o��
// Arg    �F float4 positionLocal			�F ���[�J�����W
// Arg    �F float3 vectorNormalLocal		�F �@���x�N�g��
// Arg    �F float2 positionTexture			�F �e�N�X�`�����W
// Arg    �F float4 colorDiffuse			�F �f�B�t���[�Y�F
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 vectorNormalLocal : NORMAL, float2 textureCoord : TEXCOORD0, float4 colorDiffuse : COLOR0 )
{
	// ���_�̕ϊ�
	VertexOutput	output;		// �o��
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixTransform_ );

	// ���[���h���_�̕ϊ�
	output.positionWorld_ = mul( float4( positionLocal.xyz, 1.0f ), matrixWorld_ ).xyz;

	// ���[���h�@���̕ϊ�
	output.vectorNormalWorld_ = normalize( mul( float4( vectorNormalLocal, 0.0f ), matrixWorld_ ) ).xyz;

	// �o�͒l�̊i�[
	output.colorDiffuse_ = colorDiffuse;
	output.textureCoord_ = textureCoord;

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
	// ���x�̌v�Z
	float	lightness = dot( vertex.vectorNormalWorld_, -vectorLight_ ) * 0.5f + 0.5f;

	// �f�B�t���[�Y�F�̌v�Z
	float3	diffuse = colorDiffuse_.rgb * tex2D( samplerTexture, vertex.textureCoord_ ) * lightness * colorLight_.rgb * vertex.colorDiffuse_.rgb + colorAmbient_.rgb;

	// �t���l�����˗����Z�o
	float3	vectorVertexToEye = normalize( positionEye_ - vertex.positionWorld_.xyz );
	float	fresnel = refractive_ + (1.0f - refractive_) * exp( -6.0f * max( dot( vertex.vectorNormalWorld_, vectorVertexToEye ), 0.0f ) );

	// �X�y�L�����F�̎Z�o
	float3	vectorHalf = normalize( vectorVertexToEye - vectorLight_ );
	float3	specular = colorSpecular_.rgb * (pow( max( dot( vertex.vectorNormalWorld_, vectorHalf ), 0.0f ), power_ ) * reflection_ + colorAmbient_.rgb * fresnel);

	// �s�N�Z���F��Ԃ�
	return float4( diffuse + specular, colorDiffuse_.a );
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