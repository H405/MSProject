//==============================================================================
// 
// File   �F LightEffect.fx
// Brief  �F ���C�g�G�t�F�N�g
// Author �F Taiga Shirakawa
// Date   : 2015/11/01 sun : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixWorld_;						// ���[���h�}�g���N�X
float2		sizeScreen_;						// ��ʃT�C�Y

texture		textureDiffuse_;					// �f�B�t���[�Y�e�N�X�`��
texture		textureSpecular_;					// �X�y�L�����e�N�X�`��
texture		textureNormal_;						// �@���e�N�X�`��
texture		textureDepth_;						// �[�x�e�N�X�`��

float3		positionEye_;						// �J�����̍��W
float2		clipCamera_;						// �J�����̃N���b�v�l
float3		colorAmbient_;						// ���F
float3		vectorLightDirection_;				// �f�B���N�V���i�����C�g�̃x�N�g��
float3		colorLightDirection_;				// �f�B���N�V���i�����C�g�̐F
float3		positionLightPoint_[ 32 ];			// �|�C���g���C�g���C�g�̍��W
float3		colorLightPoint_[ 32 ];				// �|�C���g���C�g���C�g�̐F
float3		attenuationLightPoint_[ 32 ];		// �|�C���g���C�g�̌�����
int			countLightPoint_;					// �|�C���g���C�g�̐�

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTextureDiffuse = sampler_state
{
	Texture = < textureDiffuse_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureSpecular = sampler_state
{
	Texture = < textureSpecular_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureNormal = sampler_state
{
	Texture = < textureNormal_ >;
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
	output.position_.xy /= 0.5f * sizeScreen_;

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
	return tex2D( samplerTextureDiffuse, vertex.textureCoord_ );
}

//==============================================================================
// Brief  �F �ʏ�ϊ�
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