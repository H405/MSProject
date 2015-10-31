//==============================================================================
// 
// File   : Mesh.fx
// Brief  : メッシュエフェクト
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixTransform_;					// 変換行列
float4x4	matrixWorld_;						// ワールド変換行列
float3		positionEye_;						// カメラの座標
float3		colorAmbient_;						// 環境色
float3		vectorLightDirection_;				// ディレクショナルライトのベクトル
float3		colorLightDirection_;				// ディレクショナルライトの色
float3		positionLightPoint_[ 32 ];			// ポイントライトライトの座標
float3		colorLightPoint_[ 32 ];				// ポイントライトライトの色
float3		attenuationLightPoint_[ 32 ];		// ポイントライトの減衰率
int			countLightPoint_;					// ポイントライトの数
texture		texture_;							// テクスチャ
float3		colorSpecular_;						// スペキュラ色
float		reflection_;						// 反射率
float		power_;								// 反射の強さ
float		refractive_;						// 屈折率

//******************************************************************************
// サンプリング
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
// 構造体定義
//******************************************************************************
// 頂点シェーダ出力
struct VertexOutput
{
	float4	position_			: POSITION;			// 座標
	float2	textureCoord_		: TEXCOORD0;		// テクスチャ座標
	float3	positionWorld_		: TEXCOORD1;		// ワールド座標
	float3	vectorNormalWorld_	: TEXCOORD2;		// ワールド法線
};

// ライト計算
#include "CalculateLight.fx"

//==============================================================================
// Brief  : 頂点変換
// Return : VertexOutput					: 頂点出力
// Arg    : float4 positionLocal			: ローカル座標
// Arg    : float3 vectorNormalLocal		: 法線ベクトル
// Arg    : float2 positionTexture			: テクスチャ座標
// Arg    : float4 colorDiffuse				: ディフューズ色
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 vectorNormalLocal : NORMAL, float2 textureCoord : TEXCOORD0 )
{
	// 頂点の変換
	VertexOutput	output;		// 出力
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixTransform_ );

	// ワールド頂点の変換
	output.positionWorld_ = mul( float4( positionLocal.xyz, 1.0f ), matrixWorld_ ).xyz;

	// ワールド法線の変換
	output.vectorNormalWorld_ = normalize( mul( float4( vectorNormalLocal, 0.0f ), matrixWorld_ ) ).xyz;

	// 出力値の格納
	output.textureCoord_ = textureCoord;

	// 頂点出力を返す
	return output;
}

//==============================================================================
// Brief  : ピクセル描画
// Return : float4 : COLOR0					: 色
// Arg    : VertexOutput					: 頂点シェーダ出力
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// 頂点から視点へのベクトルを求める
	float3	vectorVertexToEye = normalize( positionEye_ - vertex.positionWorld_.xyz );

	// モデルのディフューズ色を求める
	float4	colorDiffuse = tex2D( samplerTexture, vertex.textureCoord_ );

	// 環境光のスペキュラ色を計算
	float	fresnel = refractive_ + (1.0f - refractive_) * exp( -6.0f * max( dot( vertex.vectorNormalWorld_, vectorVertexToEye ), 0.0f ) );
	float3	specularAmbient = colorAmbient_.rgb * fresnel;

	// ディレクショナルライトのディフューズ色を計算
	float3	diffuseDirection = CalculateDiffuse( colorLightDirection_, vectorLightDirection_, vertex.vectorNormalWorld_ );

	// ディレクショナルライトのスペキュラ色を計算
	float3	specularDirection = CalculateSpecular( colorLightDirection_, vectorLightDirection_, vertex.vectorNormalWorld_, vectorVertexToEye, reflection_, power_ );

	// ディレクショナルライトのリム色を計算
	float3	rimDirection = CalculateRim( colorLightDirection_, vectorLightDirection_, vertex.vectorNormalWorld_, vectorVertexToEye );

	// ディレクショナルライトの色を計算
	float3	color = colorDiffuse.rgb * (diffuseDirection + colorAmbient_) + colorSpecular_ * (specularDirection + specularAmbient ) + rimDirection;

	// ポイントライトの色を計算
	for( int counterLight = 0; counterLight < countLightPoint_; ++counterLight )
	{
		// ライトから頂点へのベクトルを求める
		float3	vectorLightToVertex = normalize( vertex.positionWorld_.xyz - positionLightPoint_[ counterLight ] );

		// ディレクショナルライトのディフューズ色を計算
		float3	diffusePoint = CalculateDiffuse( colorLightPoint_[ counterLight ], vectorLightToVertex, vertex.vectorNormalWorld_ );

		// ポイントライトのスペキュラ色を計算
		float3	specularPoint = CalculateSpecular( colorLightPoint_[ counterLight ], vectorLightToVertex, vertex.vectorNormalWorld_, vectorVertexToEye, reflection_, power_ );

		// ポイントライトのリム色を計算
		float3	rimPoint = CalculateRim( colorLightPoint_[ counterLight ], vectorLightToVertex, vertex.vectorNormalWorld_, vectorVertexToEye );

		// ポイントライトの減衰率を計算
		float	distanceLightToVertex = distance( vertex.positionWorld_.xyz, positionLightPoint_[ counterLight ] );
		float	attenuation = attenuationLightPoint_[ counterLight ].x
			+ attenuationLightPoint_[ counterLight ].y * distanceLightToVertex
			+ attenuationLightPoint_[ counterLight ].z * distanceLightToVertex * distanceLightToVertex;

		// ポイントライトの色を計算
		color += (colorDiffuse.rgb * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;
	}

	// ピクセル色を返す
	return float4( color, colorDiffuse.a );
}

//==============================================================================
// Brief  : 通常変換
//==============================================================================
technique ShadeNormal
{
	// 通常変換
	pass PassNormal
	{
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
