//==============================================================================
// 
// File   : LightEffect.fx
// Brief  : ライトエフェクト
// Author : Taiga Shirakawa
// Date   : 2015/11/01 sun : Taiga Shirakawa : create
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
texture		textureDiffuseRiver_;				// 川のディフューズテクスチャ
texture		textureSpecularRiver_;				// 川のスペキュラテクスチャ
texture		textureNormalRiver_;				// 川の法線テクスチャ
texture		textureDepthRiver_;					// 川の深度テクスチャ
texture		textureShadow_;						// 影テクスチャ

float4x4	matrixProjectionInverse_;			// プロジェクション変換逆行列
float4x4	matrixViewInverse_;					// ビュー変換逆行列
float3		positionEye_;						// カメラの座標
float2		clipCamera_;						// カメラのクリップ値
float3		colorAmbient_;						// 環境色
float3		vectorLightDirection_;				// ディレクショナルライトのベクトル
float3		colorLightDirection_;				// ディレクショナルライトの色
float3		positionLightPoint_[ 9 ];			// ポイントライトライトの座標
float3		colorLightPoint_[ 9 ];				// ポイントライトライトの色
float3		attenuationLightPoint_[ 9 ];		// ポイントライトの減衰率

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

sampler samplerTextureDiffuseRiver = sampler_state
{
	Texture = < textureDiffuseRiver_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureSpecularRiver = sampler_state
{
	Texture = < textureSpecularRiver_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureNormalRiver = sampler_state
{
	Texture = < textureNormalRiver_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthRiver = sampler_state
{
	Texture = < textureDepthRiver_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureShadow = sampler_state
{
	Texture = < textureShadow_ >;
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

// ピクセルシェーダ出力
struct PixelOutput
{
	float4	color_			: COLOR0;			// 色
	float4	depth_			: COLOR1;			// 深度
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
// Return : PixelOutput						: ピクセルシェーダ出力
// Arg    : VertexOutput					: 頂点シェーダ出力
//==============================================================================
PixelOutput DrawPixel( VertexOutput vertex )
{
	// テクスチャから情報を取得
	float4	dataSpecularRiver = tex2D( samplerTextureSpecularRiver, vertex.textureCoord_ );
	float	proportionRiver = min( 4.0f * dataSpecularRiver.b, 1.0f );
	float4	dataDiffuse = lerp( tex2D( samplerTextureDiffuse, vertex.textureCoord_ ), tex2D( samplerTextureDiffuseRiver, vertex.textureCoord_ ), proportionRiver );
	float4	dataSpecular = lerp( tex2D( samplerTextureSpecular, vertex.textureCoord_ ), dataSpecularRiver, proportionRiver );
	float4	dataNormal = lerp( tex2D( samplerTextureNormal, vertex.textureCoord_ ), tex2D( samplerTextureNormalRiver, vertex.textureCoord_ ), proportionRiver );
	float	dataDepth = lerp( tex2D( samplerTextureDepth, vertex.textureCoord_ ).r, tex2D( samplerTextureDepthRiver, vertex.textureCoord_ ).r, proportionRiver );

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

	// 影
	float	shadow = lerp( tex2D( samplerTextureShadow, vertex.textureCoord_ ).r, 1.0f, proportionRiver );

	// 環境光のスペキュラ色を計算
	float	fresnel = dataNormal.a + (1.0f - dataNormal.a) * exp( -6.0f * max( dot( vectorNormal, vectorVertexToEye ), 0.0f ) );
	float3	specularAmbient = colorAmbient_.rgb * fresnel;

	// ディレクショナルライトのディフューズ色を計算
	float3	diffuseDirection = colorLightDirection_ * min( dot( vectorNormal, -vectorLightDirection_ ) * 0.5f + 0.5f, shadow );

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
	diffusePoint = colorLightPoint_[ 0 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

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
	diffusePoint = colorLightPoint_[ 1 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

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
	diffusePoint = colorLightPoint_[ 2 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

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
	diffusePoint = colorLightPoint_[ 3 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

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
	diffusePoint = colorLightPoint_[ 4 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

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
	diffusePoint = colorLightPoint_[ 5 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

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
	diffusePoint = colorLightPoint_[ 6 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

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
	diffusePoint = colorLightPoint_[ 7 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

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
	diffusePoint = colorLightPoint_[ 8 ] * min( dot( vectorNormal, -vectorLightToVertex ) * 0.5f + 0.5f, shadow );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 8 ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, power );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 8 ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;

	// ピクセル色を返す
	PixelOutput	output;
	output.color_ = float4( color, dataDepth );
	output.depth_.gba = 0.0f;
	output.depth_.r = dataDepth / clipCamera_.y;
	return output;
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
