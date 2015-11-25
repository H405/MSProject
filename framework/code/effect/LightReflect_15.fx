//==============================================================================
// 
// File   : LightReflect.fx
// Brief  : 反射ライトエフェクト
// Author : Taiga Shirakawa
// Date   : 2015/11/22 sun : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float2		offsetTexel_;						// テクセルオフセット

texture		textureDiffuse_;					// ディフューズテクスチャ
texture		textureSpecular_;					// スペキュラテクスチャ
texture		textureNormal_;						// 法線テクスチャ
texture		textureDepth_;						// 深度テクスチャ

float4x4	matrixProjectionInverse_;			// プロジェクション変換逆行列
float4x4	matrixViewInverse_;					// ビュー変換逆行列
float3		positionEye_;						// カメラの座標
float2		clipCamera_;						// カメラのクリップ値
float3		colorAmbient_;						// 環境色
float3		vectorLightDirection_;				// ディレクショナルライトのベクトル
float3		colorLightDirection_;				// ディレクショナルライトの色
float3		positionLightPoint_[ 15 ];			// ポイントライトライトの座標
float3		colorLightPoint_[ 15 ];				// ポイントライトライトの色
float3		attenuationLightPoint_[ 15 ];		// ポイントライトの減衰率

//******************************************************************************
// サンプリング
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
// 構造体定義
//******************************************************************************
// 頂点シェーダ出力
struct VertexOutput
{
	float4	position_		: POSITION;			// 座標
	float2	textureCoord_	: TEXCOORD0;		// テクスチャ座標
};

//******************************************************************************
// インクルード
//******************************************************************************
#include "CalculateLight.fx"

//==============================================================================
// Brief  : 頂点変換
// Return : VertexOutput					: 頂点出力
// Arg    : float4 positionLocal			: ローカル座標
// Arg    : float2 positionTexture			: テクスチャ座標
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float2 textureCoord : TEXCOORD0 )
{
	// 頂点の変換
	VertexOutput	output;		// 出力
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;

	// 値を格納
	output.textureCoord_ = textureCoord + offsetTexel_;

	// 頂点出力を返す
	return output;
}

//==============================================================================
// Brief  : ピクセル描画
// Return : float4							: 色
// Arg    : VertexOutput					: 頂点シェーダ出力
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// テクスチャから情報を取得
	float4	dataDiffuse = tex2D( samplerTextureDiffuse , vertex.textureCoord_ );
	float4	dataSpecular = tex2D( samplerTextureSpecular , vertex.textureCoord_ );
	float4	dataNormal = tex2D( samplerTextureNormal , vertex.textureCoord_ );
	float	dataDepth = tex2D( samplerTextureDepth , vertex.textureCoord_ ).r;

	// 情報の設定
	float3	colorDiffuse = dataDiffuse.rgb;
	float3	colorSpecular = dataSpecular.rgb;
	float3	vectorNormal = dataNormal.xyz * 2.0f - 1.0f;
	float	depth = dataDepth;
	float	power = dataSpecular.a * 64.0f;

	// ワールド座標を求める
	float2	positionTexture = vertex.textureCoord_ * 2.0f - 1.0f;
	float3	positionProjection = mul( float4( positionTexture.x, -positionTexture.y, 1.0f, 1.0f ), matrixProjectionInverse_ ).xyz;
	float3	positionView = float3( positionProjection.xy, 1.0f ) * depth;
	float3	positionWorld = mul( float4( positionView, 1.0f ), matrixViewInverse_ );

	// 視線ベクトルを求める
	float3	vectorVertexToEye = normalize( positionEye_ - positionWorld );

	// 環境光のスペキュラ色を計算
	float	fresnel = dataNormal.a + (1.0f - dataNormal.a) * exp( -6.0f * max( dot( vectorNormal, vectorVertexToEye ), 0.0f ) );
	float3	specularAmbient = colorAmbient_.rgb * fresnel;

	// ディレクショナルライトのディフューズ色を計算
	float3	diffuseDirection = CalculateDiffuse( colorLightDirection_, vectorLightDirection_, vectorNormal );

	// ディレクショナルライトのスペキュラ色を計算
	float3	specularDirection = CalculateSpecular( colorLightDirection_, vectorLightDirection_, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ディレクショナルライトのリム色を計算
	float3	rimDirection = CalculateRim( colorLightDirection_, vectorLightDirection_, vectorNormal, vectorVertexToEye );

	// 環境光とディレクショナルライトの色を計算
	float3	color = colorDiffuse * (diffuseDirection + colorAmbient_) + colorSpecular * (specularDirection + specularAmbient) + rimDirection;

	// ポイントライトの色を計算
	float	distanceLightToVertex;
	float	attenuation;
	float3	vectorLightToVertex;
	float3	diffusePoint;
	float3	specularPoint;
	float3	rimPoint;


	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 0 ] );
	attenuation = attenuationLightPoint_[ 0 ].x
		+ attenuationLightPoint_[ 0 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 0 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 0 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 0 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 0 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 0 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 1 ] );
	attenuation = attenuationLightPoint_[ 1 ].x
		+ attenuationLightPoint_[ 1 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 1 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 1 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 1 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 1 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 1 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 2 ] );
	attenuation = attenuationLightPoint_[ 2 ].x
		+ attenuationLightPoint_[ 2 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 2 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 2 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 2 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 2 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 2 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 3 ] );
	attenuation = attenuationLightPoint_[ 3 ].x
		+ attenuationLightPoint_[ 3 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 3 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 3 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 3 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 3 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 3 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 4 ] );
	attenuation = attenuationLightPoint_[ 4 ].x
		+ attenuationLightPoint_[ 4 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 4 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 4 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 4 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 4 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 4 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 5 ] );
	attenuation = attenuationLightPoint_[ 5 ].x
		+ attenuationLightPoint_[ 5 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 5 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 5 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 5 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 5 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 5 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 6 ] );
	attenuation = attenuationLightPoint_[ 6 ].x
		+ attenuationLightPoint_[ 6 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 6 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 6 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 6 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 6 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 6 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 7 ] );
	attenuation = attenuationLightPoint_[ 7 ].x
		+ attenuationLightPoint_[ 7 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 7 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 7 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 7 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 7 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 7 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 8 ] );
	attenuation = attenuationLightPoint_[ 8 ].x
		+ attenuationLightPoint_[ 8 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 8 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 8 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 8 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 8 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 8 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 9 ] );
	attenuation = attenuationLightPoint_[ 9 ].x
		+ attenuationLightPoint_[ 9 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 9 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 9 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 9 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 9 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 9 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 10 ] );
	attenuation = attenuationLightPoint_[ 10 ].x
		+ attenuationLightPoint_[ 10 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 10 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 10 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 10 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 10 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 10 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 11 ] );
	attenuation = attenuationLightPoint_[ 11 ].x
		+ attenuationLightPoint_[ 11 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 11 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 11 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 11 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 11 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 11 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 12 ] );
	attenuation = attenuationLightPoint_[ 12 ].x
		+ attenuationLightPoint_[ 12 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 12 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 12 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 12 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 12 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 12 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 13 ] );
	attenuation = attenuationLightPoint_[ 13 ].x
		+ attenuationLightPoint_[ 13 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 13 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 13 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 13 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 13 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 13 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ 14 ] );
	attenuation = attenuationLightPoint_[ 14 ].x
		+ attenuationLightPoint_[ 14 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 14 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ 14 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 14 ], vectorLightToVertex, vectorNormal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 14 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 14 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ピクセル色を返す
	return float4( color, dataDepth );
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
