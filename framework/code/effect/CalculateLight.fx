//==============================================================================
// 
// File   : CalculateLight.fx
// Brief  : ライト計算
// Author : Taiga Shirakawa
// Date   : 2015/10/26 mon : Taiga Shirakawa : create
// 
//==============================================================================

//==============================================================================
// Brief  : ディフューズの計算
// Return : float3							: 色
// Arg    : float3 colorLight				: ライトの色
// Arg    : float3 vectorLight				: ライトのベクトル
// Arg    : float3 vectorNormal				: 法線ベクトル
//==============================================================================
float3 CalculateDiffuse( float3 colorLight, float3 vectorLight, float3 vectorNormal )
{
	// 明度の計算
	float	lightness = dot( vectorNormal, -vectorLight ) * 0.5f + 0.5f;

	// ディフューズ色を返す
	return colorLight * lightness;
}

//==============================================================================
// Brief  : スペキュラの計算
// Return : float3							: 色
// Arg    : float3 colorLight				: ライトの色
// Arg    : float3 vectorLight				: ライトのベクトル
// Arg    : float3 vectorNormal				: 法線ベクトル
// Arg    : float3 vectorVertexToEye		: 頂点から視点へのベクトル
// Arg    : float reflection;				: 反射率
// Arg    : float power;					: 反射の強さ
//==============================================================================
float3 CalculateSpecular( float3 colorLight, float3 vectorLight, float3 vectorNormal, float3 vectorVertexToEye, float reflection, float power )
{
	// ハーフベクトルを求める
	float3	vectorHalf = normalize( vectorVertexToEye - vectorLight );

	// スペキュラ色を返す
	return colorLight * pow( max( dot( vectorNormal, vectorHalf ), 0.0f ), power ) * reflection;
}

//==============================================================================
// Brief  : リムの計算
// Return : float3							: 色
// Arg    : float3 colorLight				: ライトの色
// Arg    : float3 vectorLight				: ライトのベクトル
// Arg    : float3 vectorNormal				: 法線ベクトル
// Arg    : float3 vectorVertexToEye		: 頂点から視点へのベクトル
//==============================================================================
float3 CalculateRim( float3 colorLight, float3 vectorLight, float3 vectorNormal, float3 vectorVertexToEye )
{
	// リム色を返す
	float	rim = (1.0f - max( dot( vectorNormal, vectorVertexToEye ), 0.0f )) * max( dot( vectorLight, vectorVertexToEye ), 0.0f );
	rim = min( 5.0f * pow( rim, 5.0f ), 1.0f );
	return colorLight * rim;
}
