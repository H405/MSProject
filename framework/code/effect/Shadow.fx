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

float3		positionLookAtLight_;			// ���s�����̒����_

float4x4	matrixTransformLightNear_;		// ���s����(��)�̕ϊ��s��
float4x4	matrixViewLightNear_;			// ���s����(��)�̃r���[�ϊ��s��
texture		textureDepthLightNear_;			// ���s����(��)�̐[�x�e�N�X�`��
float		clipFarLightNear_;				// ���s����(��)�̃t�@�[�N���b�v��

float4x4	matrixTransformLightFar_;		// ���s����(��)�̕ϊ��s��
float4x4	matrixViewLightFar_;			// ���s����(��)�̃r���[�ϊ��s��
texture		textureDepthLightFar_;			// ���s����(��)�̐[�x�e�N�X�`��
float		clipFarLightFar_;				// ���s����(��)�̃t�@�[�N���b�v��

float4x4	matrixViewLightPoint0_;			// �_����0�̃r���[�ϊ��s��
texture		textureDepthLightPoint0_;		// �_����0�̐[�x�e�N�X�`��
float		clipFarLightPoint0_;			// �_����0�̃t�@�[�N���b�v��
float3		attenuationLightPoint0_;		// �_����0�̌�����

float4x4	matrixViewLightPoint1_;			// �_����1�̃r���[�ϊ��s��
texture		textureDepthLightPoint1_;		// �_����1�̐[�x�e�N�X�`��
float		clipFarLightPoint1_;			// �_����1�̃t�@�[�N���b�v��
float3		attenuationLightPoint1_;		// �_����1�̌�����

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

sampler samplerTextureDepthLightNear = sampler_state
{
	Texture = < textureDepthLightNear_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthLightFar = sampler_state
{
	Texture = < textureDepthLightFar_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthLightPoint0 = sampler_state
{
	Texture = < textureDepthLightPoint0_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthLightPoint1 = sampler_state
{
	Texture = < textureDepthLightPoint1_ >;
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
// Brief  : ���s����(��)�̉e���v�Z
// Return : float							: �e�̔Z��
// Arg    : float3 positionWorld			: ���[���h���W
//==============================================================================
float CalculateShadowNear( float3 positionWorld )
{
	// �e�N�X�`���̍��W�����߂�
	float4	positionLightNear = mul( float4( positionWorld, 1.0f ), matrixTransformLightNear_ );
	float2	positionTextureLightNear = positionLightNear.xy / positionLightNear.w;
	positionTextureLightNear = float2( 1.0f + positionTextureLightNear.x, 1.0f - positionTextureLightNear.y );
	positionTextureLightNear *= 0.5f;

	// �[�x���擾
	float	depthLightNear = clipFarLightNear_ - tex2D( samplerTextureDepthLightNear, positionTextureLightNear ).r;
	float	depth = mul( float4( positionWorld, 1.0f ), matrixViewLightNear_ ).z;

	// �F��Ԃ�
	float	shadow;
	if( depth - depthLightNear > 17.0f )
	{
		shadow = 0.5f;
	}
	else
	{
		shadow = 1.0f;
	}
	return shadow;
}

//==============================================================================
// Brief  : ���s����(��)�̉e���v�Z
// Return : float							: �e�̔Z��
// Arg    : float3 positionWorld			: ���[���h���W
//==============================================================================
float CalculateShadowFar( float3 positionWorld )
{
	// �e�N�X�`���̍��W�����߂�
	float4	positionLightFar = mul( float4( positionWorld, 1.0f ), matrixTransformLightFar_ );
	float2	positionTextureLightFar = positionLightFar.xy / positionLightFar.w;
	positionTextureLightFar = float2( 1.0f + positionTextureLightFar.x, 1.0f - positionTextureLightFar.y );
	positionTextureLightFar *= 0.5f;

	// �[�x���擾
	float	depthLightFar = clipFarLightFar_ - tex2D( samplerTextureDepthLightFar, positionTextureLightFar ).r;
	float	depth = mul( float4( positionWorld, 1.0f ), matrixViewLightFar_ ).z;

	// �F��Ԃ�
	float	shadow;
	if( depth - depthLightFar > 50.0f )
	{
		shadow = 0.5f;
	}
	else
	{
		shadow = 1.0f;
	}
	return shadow;
}

//==============================================================================
// Brief  : �_����0�̉e���v�Z
// Return : float							: �e�̔Z��
// Arg    : float3 positionWorld			: ���[���h���W
//==============================================================================
float CalculateShadowPoint0( float3 positionWorld )
{
	// �K�v�ȏ������߂�
	float4	positionView = mul( float4( positionWorld, 1.0f ), matrixViewLightPoint0_ );
	float	distanceProjection = positionView.x * positionView.x + positionView.y * positionView.y;
	float	distanceToVertex = length( positionView );

	// �e�N�X�`���̍��W�����߂�
	float2	positionTextureLightPoint0 = positionView * (distanceToVertex - positionView.z) / distanceProjection;
	positionTextureLightPoint0 = float2( 1.0f + positionTextureLightPoint0.x, 1.0f - positionTextureLightPoint0.y );
	positionTextureLightPoint0 *= 0.5f;

	// �[�x���擾
	float	depthLightPoint0 = clipFarLightPoint0_ - tex2D( samplerTextureDepthLightPoint0, positionTextureLightPoint0 ).r;

	// �F��Ԃ�
	float	shadow;
	if( distanceToVertex - depthLightPoint0 > 25.0f )
	{
		// �����������߂�
		float	attenuation = attenuationLightPoint0_.x
			+ attenuationLightPoint0_.y * distanceToVertex
			+ attenuationLightPoint0_.z * distanceToVertex * distanceToVertex;

		// �e�̔Z��������
		shadow = 1.0f - 0.7f / (1.0f + attenuation);
	}
	else
	{
		shadow = 1.0f;
	}
	return shadow;
}

//==============================================================================
// Brief  : �_����1�̉e���v�Z
// Return : float							: �e�̔Z��
// Arg    : float3 positionWorld			: ���[���h���W
//==============================================================================
float CalculateShadowPoint1( float3 positionWorld )
{
	// �K�v�ȏ������߂�
	float4	positionView = mul( float4( positionWorld, 1.0f ), matrixViewLightPoint1_ );
	float	distanceProjection = positionView.x * positionView.x + positionView.y * positionView.y;
	float	distanceToVertex = length( positionView );

	// �e�N�X�`���̍��W�����߂�
	float2	positionTextureLightPoint1 = positionView * (distanceToVertex - positionView.z) / distanceProjection;
	positionTextureLightPoint1 = float2( 1.0f + positionTextureLightPoint1.x, 1.0f - positionTextureLightPoint1.y );
	positionTextureLightPoint1 *= 0.5f;

	// �[�x���擾
	float	depthLightPoint1 = clipFarLightPoint1_ - tex2D( samplerTextureDepthLightPoint1, positionTextureLightPoint1 ).r;

	// �F��Ԃ�
	float	shadow;
	if( distanceToVertex - depthLightPoint1 > 25.0f )
	{
		// �����������߂�
		float	attenuation = attenuationLightPoint1_.x
			+ attenuationLightPoint1_.y * distanceToVertex
			+ attenuationLightPoint1_.z * distanceToVertex * distanceToVertex;

		// �e�̔Z��������
		shadow = 1.0f - 0.7f / (1.0f + attenuation);
	}
	else
	{
		shadow = 1.0f;
	}
	return shadow;
}

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

	// ���s�����̉e������
	float	shadow;
	if( distance( positionWorld, positionLookAtLight_ ) < 4000.0f )
	{
		shadow = CalculateShadowNear( positionWorld );
	}
	else
	{
		shadow = CalculateShadowFar( positionWorld );
	}

	// �_�����̉e������
	shadow *= CalculateShadowPoint0( positionWorld );
	shadow *= CalculateShadowPoint1( positionWorld );

	// �F��Ԃ�
	float4	color;
	color.gba = 0.0f;
	color.r = shadow;
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
