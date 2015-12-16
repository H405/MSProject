//==============================================================================
// 
// File   : SkinMeshShadow.fx
// Brief  : �X�L�����b�V���e�G�t�F�N�g
// Author : Taiga Shirakawa
// Date   : 2015/12/09 wed : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// �ϐ��錾
//******************************************************************************
float4x4	matrixTransform_;		// �ϊ��s��
float4x4	matrixWorldView_;		// ���[���h�r���[�ϊ��s��
float4x3	matrixBone_[ 70 ];		// �{�[���ϊ��s��
float		clipFar_;				// �t�@�[�N���b�v��

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
// Arg    : float3 weight					: �u�����h����
// Arg    : float4 indices					: ���_�ԍ�
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 weight : BLENDWEIGHT, float4 indices : BLENDINDICES )
{
	// �{�[���s��ϊ�
	VertexOutput	output;				// ���_�V�F�[�_�o��
	float4x3		matrixBone;			// �{�[���ϊ��s��
	float4x4		matrixBone4x4;		// 4x4�{�[���ϊ��s��
	matrixBone = matrixBone_[ indices[ 0 ] ] * weight.x;
	matrixBone += matrixBone_[ indices[ 1 ] ] * weight.y;
	matrixBone += matrixBone_[ indices[ 2 ] ] * weight.z;
	matrixBone += matrixBone_[ indices[ 3 ] ] * (1.0f - weight.x - weight.y - weight.z);
	matrixBone4x4 = float4x4( matrixBone[ 0 ], 0.0f, matrixBone[ 1 ], 0.0f, matrixBone[ 2 ], 0.0f, matrixBone[ 3 ], 1.0f );
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixBone4x4 );

	// �[�x�̌v�Z
	output.depth_ = mul( output.position_, matrixWorldView_ ).z;

	// ���_�̕ϊ�
	output.position_ = mul( output.position_, matrixTransform_ );

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
	depth.r = clipFar_ - vertex.depth_;
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