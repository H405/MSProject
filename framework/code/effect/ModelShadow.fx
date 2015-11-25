//==============================================================================
// 
// File   : ModelShadow.fx
// Brief  : ���f���e�G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/11/24 tsu : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixTransform_;		// �ϊ��s��
float4x4	matrixWorldView_;		// ���[���h�r���[�ϊ��s��

//******************************************************************************
// �T���v�����O
//******************************************************************************

//******************************************************************************
// �\���̒�`
//******************************************************************************
// ���_�V�F�[�_�o��
struct VertexOutput
{
	float4	position_	: POSITION;			// ���W
	float	depth_		: TEXCOORD2;		// �[�x
};

//==============================================================================
// Brief  : ���_�ϊ�
// Return : VertexOutput					: ���_�V�F�[�_�o��
// Arg    : float4 positionLocal			: ���[�J�����W
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 vectorNormal : NORMAL )
{
	// ���_�̕ϊ�
	VertexOutput	output;		// ���_�V�F�[�_�o��
	output.position_ = mul( float4( positionLocal + 2.5f * vectorNormal, 1.0f ), matrixTransform_ );

	// �[�x�̌v�Z
	output.depth_ = mul( float4( positionLocal, 1.0f ), matrixWorldView_ ).z;

	// ���_�V�F�[�_�o�͂�Ԃ�
	return output;
}

//==============================================================================
// Brief  : �s�N�Z���`��
// Return : float4							: �[�x
// Arg    : VertexOutput					: ���_�V�F�[�_�o��
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// �s�N�Z���V�F�[�_�o�͂�Ԃ�
	float4	depth;
	depth.gba = 0.0f;
	depth.r = 1000.0f - vertex.depth_;
	return depth;
}

//==============================================================================
// Brief  : �ʏ�ϊ�
//==============================================================================
technique ShadeNormal
{
	// �ʏ�ϊ�
	pass PassNormal
	{
		// �����_�[�X�e�[�g�̐ݒ�
		CullMode = CW;

		// �V�F�[�_�̐ݒ�
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
