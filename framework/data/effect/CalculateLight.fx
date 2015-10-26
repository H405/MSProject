//==============================================================================
// 
// File   : CalculateLight.fx
// Brief  : ���C�g�v�Z
// Author : Taiga Shirakawa
// Date   : 2015/10/26 mon : Taiga Shirakawa : create
// 
//==============================================================================

//==============================================================================
// Brief  : �f�B�t���[�Y�̌v�Z
// Return : float3							: �F
// Arg    : float3 colorLight				: ���C�g�̐F
// Arg    : float3 vectorLight				: ���C�g�̃x�N�g��
// Arg    : float3 vectorNormal				: �@���x�N�g��
//==============================================================================
float3 CalculateDiffuse( float3 colorLight, float3 vectorLight, float3 vectorNormal )
{
	// ���x�̌v�Z
	float	lightness = dot( vectorNormal, -vectorLight ) * 0.5f + 0.5f;

	// �f�B�t���[�Y�F��Ԃ�
	return colorLight * lightness;
}

//==============================================================================
// Brief  : �X�y�L�����̌v�Z
// Return : float3							: �F
// Arg    : float3 colorLight				: ���C�g�̐F
// Arg    : float3 vectorLight				: ���C�g�̃x�N�g��
// Arg    : float3 vectorNormal				: �@���x�N�g��
// Arg    : float3 vectorVertexToEye		: ���_���王�_�ւ̃x�N�g��
// Arg    : float reflection;				: ���˗�
// Arg    : float power;					: ���˂̋���
//==============================================================================
float3 CalculateSpecular( float3 colorLight, float3 vectorLight, float3 vectorNormal, float3 vectorVertexToEye, float reflection, float power )
{
	// �n�[�t�x�N�g�������߂�
	float3	vectorHalf = normalize( vectorVertexToEye - vectorLight );

	// �X�y�L�����F��Ԃ�
	return colorLight * pow( max( dot( vectorNormal, vectorHalf ), 0.0f ), power ) * reflection;
}

//==============================================================================
// Brief  : �����̌v�Z
// Return : float3							: �F
// Arg    : float3 colorLight				: ���C�g�̐F
// Arg    : float3 vectorLight				: ���C�g�̃x�N�g��
// Arg    : float3 vectorNormal				: �@���x�N�g��
// Arg    : float3 vectorVertexToEye		: ���_���王�_�ւ̃x�N�g��
//==============================================================================
float3 CalculateRim( float3 colorLight, float3 vectorLight, float3 vectorNormal, float3 vectorVertexToEye )
{
	// �����F��Ԃ�
	float	rim = (1.0f - max( dot( vectorNormal, vectorVertexToEye ), 0.0f )) * max( dot( vectorLight, vectorVertexToEye ), 0.0f );
	rim = min( 5.0f * pow( rim, 5.0f ), 1.0f );
	return colorLight * rim;
}
