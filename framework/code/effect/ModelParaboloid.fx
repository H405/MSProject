//==============================================================================
// 
// File   : ModelParaboloid.fx
// Brief  : �����ʕϊ����f���G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/12/08 tsu : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixWorldView_;		// ���[���h�r���[�ϊ��s��
float2		clipCamera_;			// �J�����̃N���b�v�l

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
	float	depth_		: TEXCOORD0;		// �[�x
};

//==============================================================================
// Brief  : ���_�ϊ�
// Return : VertexOutput					: ���_�V�F�[�_�o��
// Arg    : float4 positionLocal			: ���[�J�����W
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION )
{
	// ���[���h�r���[�ϊ�
	float4	positionView = mul( float4( positionLocal, 1.0f ), matrixWorldView_ );

	// �K�v�Ȓl���v�Z
	float	distanceProjection = positionView.x * positionView.x + positionView.y * positionView.y;
	float	distanceToVertex = length( positionView );

	// ���_�̕ϊ�
	VertexOutput	output;		// ���_�V�F�[�_�o��
	output.position_.x = distanceToVertex * positionView.x * (distanceToVertex - positionView.z) / distanceProjection;
	output.position_.y = distanceToVertex * positionView.y * (distanceToVertex - positionView.z) / distanceProjection;
	output.position_.z = clipCamera_.y * (distanceToVertex - clipCamera_.x) / (clipCamera_.y - clipCamera_.x);
	output.position_.w = distanceToVertex;

	// �[�x�̊i�[
	output.depth_ = distanceToVertex;

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
	depth.r = clipCamera_.y - vertex.depth_;
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
