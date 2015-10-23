//==============================================================================
// 
// File   �F Point.fx
// Brief  �F �|�C���g�X�v���C�g�G�t�F�N�g
// Author �F Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixView_;			// �r���[�ϊ��s��
float4x4	matrixProjection_;		// �v���W�F�N�V�����ϊ��s��
texture		texture_;				// �e�N�X�`��

//******************************************************************************
// �T���v�����O
//******************************************************************************
sampler samplerTexture = sampler_state
{
	Texture = < texture_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = Wrap;
	AddressV = Wrap;
};

//******************************************************************************
// �\���̒�`
//******************************************************************************
// ���_�V�F�[�_�o��
struct VertexOutput
{
	float4	position_		: POSITION;			// ���W
	float	size_			: PSIZE;			// �T�C�Y
	float4	colorDiffuse_	: COLOR0;			// �f�B�t���[�Y�F
};

//==============================================================================
// Brief  �F ���_�ϊ�
// Return �F VertexOutput					�F ���_�o��
// Arg    �F float4 positionWorld			�F ���[���h���W
// Arg    �F float size						�F �|�C���g�X�v���C�g�̃T�C�Y
// Arg    �F float4 colorDiffuse			�F �f�B�t���[�Y�F
//==============================================================================
VertexOutput TransformVertex( float3 positionWorld : POSITION, float size : PSIZE, float4 colorDiffuse : COLOR0 )
{
	// ���_�̕ϊ�
	VertexOutput	output;			// �o��
	float			lengthView;		// �r���[���W�n�̒���
	output.position_ = mul( float4( positionWorld, 1.0f ), matrixView_ );
	lengthView = length( output.position_.xyz );
	output.position_ = mul( output.position_, matrixProjection_ );

	// �T�C�Y�̌v�Z
	output.size_ = 10.0f * size * (matrixProjection_._22 / matrixProjection_._11) * sqrt( 1.0f / lengthView );

	// �l���i�[
	output.colorDiffuse_ = colorDiffuse;

	// ���_�o�͂�Ԃ�
	return output;
}

//==============================================================================
// Brief  �F �s�N�Z���`��
// Return �F float4 : COLOR0				�F �F
// Arg    �F VertexOutput					�F ���_�V�F�[�_�o��
// Arg    �F float4 colorDiffuse			�F �f�B�t���[�Y�F
//==============================================================================
float4 DrawPixel( float2 textureCoord : TEXCOORD0, float4 colorDiffuse : COLOR0 ) : COLOR0
{
	// �s�N�Z���F��Ԃ�
	return tex2D( samplerTexture, textureCoord ) * colorDiffuse;
}

//==============================================================================
// Brief  �F �ʏ�ϊ�
//==============================================================================
technique ShadeNormal
{
	// �ʏ�ϊ�
	pass PassNormal
	{
		// �����_�[�X�e�[�g�̐ݒ�
		PointSpriteEnable = True;
		ZWriteEnable = False;
		AlphaBlendEnable = True;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = One;

		// �V�F�[�_�̐ݒ�
		VertexShader = compile vs_2_0 TransformVertex();
		PixelShader = compile ps_2_0 DrawPixel();
	}
}