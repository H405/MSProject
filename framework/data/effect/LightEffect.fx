//==============================================================================
// 
// File   ： LightEffect.fx
// Brief  ： ライトエフェクト
// Author ： Taiga Shirakawa
// Date   : 2015/11/01 sun : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixWorld_;						// ワールド変換行列
float2		sizeScreen_;						// 画面サイズ

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
float3		positionLightPoint_[ 32 ];			// ポイントライトライトの座標
float3		colorLightPoint_[ 32 ];				// ポイントライトライトの色
float3		attenuationLightPoint_[ 32 ];		// ポイントライトの減衰率
int			countLightPoint_;					// ポイントライトの数

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
	float4	diffuse_		: COLOR0;			// ディフューズ色
	float2	textureCoord_	: TEXCOORD0;		// テクスチャ座標
};

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

//==============================================================================
// Brief  ： 頂点変換
// Return ： VertexOutput					： 頂点出力
// Arg    ： float4 positionLocal			： ローカル座標
// Arg    ： float3 vectorNormal			： 法線ベクトル
// Arg    ： float2 positionTexture			： テクスチャ座標
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float2 textureCoord : TEXCOORD0, float4 diffuse : COLOR0 )
{
	// 頂点の変換
	VertexOutput	output;		// 出力
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;
	output.position_ = mul( output.position_, matrixWorld_ );
	output.position_.xy /= 0.5f * sizeScreen_;

	// 値を格納
	output.textureCoord_ = textureCoord;
	output.diffuse_ = diffuse;

	// 頂点出力を返す
	return output;
}

//==============================================================================
// Brief  ： ピクセル描画
// Return ： float4 : COLOR0				： 色
// Arg    ： VertexOutput					： 頂点シェーダ出力
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// 情報を取得
	float4	dataDiffuse = tex2D( samplerTextureDiffuse , vertex.textureCoord_ );
	float4	dataSpecular = tex2D( samplerTextureSpecular , vertex.textureCoord_ );
	float4	dataNormal = tex2D( samplerTextureNormal , vertex.textureCoord_ );
	float	dataDepth = tex2D( samplerTextureDepth , vertex.textureCoord_ ).r;

	float3	colorDiffuse = dataDiffuse.rgb;
	float3	colorSpecular = dataSpecular.rgb;
	float3	vectorNormal = normalize( dataNormal.xyz * 2.0f - 1.0f );
	float	depth = dataDepth * clipCamera_.y;

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
	float3	specularDirection = CalculateSpecular( colorLightDirection_, vectorLightDirection_, vectorNormal, vectorVertexToEye, dataDiffuse.a, dataSpecular.a * 64.0f );

	// ディレクショナルライトのリム色を計算
	float3	rimDirection = CalculateRim( colorLightDirection_, vectorLightDirection_, vectorNormal, vectorVertexToEye );

	// 環境光とディレクショナルライトの色を計算
	float3	color = colorDiffuse * (diffuseDirection + colorAmbient_) + colorSpecular * (specularDirection + specularAmbient) + rimDirection;
	
	// ポイントライトの色を計算
	for( int counterLight = 0; counterLight < countLightPoint_; ++counterLight )
	{
		// ポイントライトの減衰率を計算
		float	distanceLightToVertex = distance( positionWorld, positionLightPoint_[ counterLight ] );
		float	attenuation = attenuationLightPoint_[ counterLight ].x
			+ attenuationLightPoint_[ counterLight ].y * distanceLightToVertex
			+ attenuationLightPoint_[ counterLight ].z * distanceLightToVertex * distanceLightToVertex;

		// ライトから頂点へのベクトルを求める
		float3	vectorLightToVertex = normalize( positionWorld - positionLightPoint_[ counterLight ] );

		// ディレクショナルライトのディフューズ色を計算
		float3	diffusePoint = CalculateDiffuse( colorLightPoint_[ counterLight ], vectorLightToVertex, vectorNormal );

		// ポイントライトのスペキュラ色を計算
		float3	specularPoint = CalculateSpecular( colorLightPoint_[ counterLight ], vectorLightToVertex, vectorNormal, vectorVertexToEye, dataDiffuse.a, dataSpecular.a * 64.0f );

		// ポイントライトのリム色を計算
		float3	rimPoint = CalculateRim( colorLightPoint_[ counterLight ], vectorLightToVertex, vectorNormal, vectorVertexToEye );

		// ポイントライトの色を計算
		color += (colorDiffuse * diffusePoint + colorSpecular * specularPoint + rimPoint) / attenuation;
	}

	// ピクセル色を返す
	return float4( color, 1.0f );
}

//==============================================================================
// Brief  ： 通常変換
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