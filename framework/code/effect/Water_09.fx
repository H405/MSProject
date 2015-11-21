//==============================================================================
// 
// File   : Water.fx
// Brief  : 水エフェクト
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixTransform_;					// 変換行列
float4x4	matrixWorld_;						// ワールド変換行列
float4x4	matrixWorldView_;					// ワールドビュー変換行列

float4x4	matrixWorldInverseTranspose_;		// ワールド逆転置行列
texture		textureNormal_;						// 法線テクスチャ
float3		colorDiffuse_;						// ディフューズ色
float3		colorSpecular_;						// スペキュラ色
float		reflection_;						// 反射率
float		power_;								// 反射の強さ
float		refractive_;						// 屈折率

texture		textureEnvironmentFront_;			// 正面環境テクスチャ
texture		textureEnvironmentBack_;			// 背面環境テクスチャ
texture		textureEnvironmentAddFront_;		// 正面加算環境テクスチャ
texture		textureEnvironmentAddBack_;			// 背面加算環境テクスチャ

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
sampler samplerTextureNormal = sampler_state
{
	Texture = < textureNormal_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = WRAP;
	AddressV = WRAP;
};

sampler samplerTextureEnvironmentFront = sampler_state
{
	Texture = < textureEnvironmentFront_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

sampler samplerTextureEnvironmentBack = sampler_state
{
	Texture = < textureEnvironmentBack_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

sampler samplerTextureEnvironmentAddFront = sampler_state
{
	Texture = < textureEnvironmentAddFront_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

sampler samplerTextureEnvironmentAddBack = sampler_state
{
	Texture = < textureEnvironmentAddBack_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

//******************************************************************************
// 構造体定義
//******************************************************************************
// 頂点シェーダ出力
struct VertexOutput
{
	float4	position_			: POSITION;			// 座標
	float2	textureCoord_		: TEXCOORD0;		// テクスチャ座標
	float3	positionWorld_		: TEXCOORD1;		// 変換後座標
	float3	vectorNormalWorld_	: TEXCOORD2;		// 変換後法線
	float3	tangentWorld_		: TEXCOORD3;		// 変換後接線
	float	depth_				: TEXCOORD4;		// 深度
};

// ピクセルシェーダ出力
struct PixelOutput
{
	float4	color_				: COLOR0;			// 色
	float4	depth_				: COLOR1;			// 深度
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
// Brief  : 頂点変換
// Return : VertexOutput					: 頂点シェーダ出力
// Arg    : float4 positionLocal			: ローカル座標
// Arg    : float3 vectorNormalLocal		: 法線ベクトル
// Arg    : float3 tangentLocal				: 正接
// Arg    : float2 positionTexture			: テクスチャ座標
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 vectorNormalLocal : NORMAL, float3 tangentLocal : TANGENT, float2 textureCoord : TEXCOORD0 )
{
	// 頂点の変換
	VertexOutput	output;		// 頂点シェーダ出力
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixTransform_ );
	output.positionWorld_ = mul( float4( positionLocal, 1.0f ), matrixWorld_ );

	// 法線の変換
	output.vectorNormalWorld_ = normalize( mul( float4( vectorNormalLocal, 0.0f ), matrixWorld_ ) ).xyz;

	// 正接の変換
	output.tangentWorld_ = normalize( mul( float4( tangentLocal, 0.0f ), matrixWorldInverseTranspose_ ).xyz );

	// 深度の計算
	output.depth_ = mul( float4( positionLocal, 1.0f ), matrixWorldView_ ).z;

	// 出力値の格納
	output.textureCoord_ = textureCoord;

	// 頂点シェーダ出力を返す
	return output;
}

//==============================================================================
// Brief  : ピクセル描画
// Return : PixelOutput						: ピクセルシェーダ出力
// Arg    : VertexOutput					: 頂点シェーダ出力
//==============================================================================
PixelOutput DrawPixel( VertexOutput vertex )
{
	// 視線ベクトルを求める
	float3	vectorVertexToEye = normalize( positionEye_ - vertex.positionWorld_ );

	// 高さを取得
	float	height = tex2D( samplerTextureNormal, vertex.textureCoord_ ).a;

	// 法線を求める
	float3	tangent = normalize( vertex.tangentWorld_ - dot( vertex.tangentWorld_, vertex.vectorNormalWorld_ ) * vertex.vectorNormalWorld_ );
	float3	binormal = cross( vertex.vectorNormalWorld_, tangent );
	float3	vectorVertexToEyeTexture = normalize( mul( vectorVertexToEye, float3x3( tangent, binormal, vertex.vectorNormalWorld_ ) ) );
	float3	normalTexture = normalize( tex2D( samplerTextureNormal, vertex.textureCoord_ + 0.02f * height * vectorVertexToEye.xy ).rgb * 2.0f - 1.0f );
	float3	normal = normalize( mul( normalTexture, float3x3( tangent, binormal, vertex.vectorNormalWorld_ ) ) );
//	normal = vertex.vectorNormalWorld_;

	// ディフューズ色を求める
	float	proportionEnvironment = 1.0f - max( dot( normal, vectorVertexToEye ), 0.0f );
	float3	colorDiffuse = colorDiffuse_;

	// 環境光のスペキュラ色を計算
	float	fresnel = refractive_ + (1.0f - refractive_) * exp( -6.0f * max( dot( normal, vectorVertexToEye ), 0.0f ) );
	float3	specularAmbient = colorAmbient_.rgb * fresnel;

	// ディレクショナルライトのディフューズ色を計算
	float3	diffuseDirection = CalculateDiffuse( colorLightDirection_, vectorLightDirection_, normal );

	// ディレクショナルライトのスペキュラ色を計算
	float3	specularDirection = CalculateSpecular( colorLightDirection_, vectorLightDirection_, normal, vectorVertexToEye, reflection_, power_ );

	// ディレクショナルライトのリム色を計算
	float3	rimDirection = CalculateRim( colorLightDirection_, vectorLightDirection_, normal, vectorVertexToEye );

	// 環境光とディレクショナルライトの色を計算
	float3	color = colorDiffuse * (diffuseDirection + colorAmbient_) + colorSpecular_ * (specularDirection + specularAmbient) + rimDirection;

	// ポイントライトの色を計算
	float	distanceLightToVertex;
	float	attenuation;
	float3	vectorLightToVertex;
	float3	diffusePoint;
	float3	specularPoint;
	float3	rimPoint;


	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 0 ] );
	attenuation = attenuationLightPoint_[ 0 ].x
		+ attenuationLightPoint_[ 0 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 0 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 0 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 0 ], vectorLightToVertex, normal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 0 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 0 ], vectorLightToVertex, normal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 1 ] );
	attenuation = attenuationLightPoint_[ 1 ].x
		+ attenuationLightPoint_[ 1 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 1 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 1 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 1 ], vectorLightToVertex, normal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 1 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 1 ], vectorLightToVertex, normal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 2 ] );
	attenuation = attenuationLightPoint_[ 2 ].x
		+ attenuationLightPoint_[ 2 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 2 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 2 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 2 ], vectorLightToVertex, normal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 2 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 2 ], vectorLightToVertex, normal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 3 ] );
	attenuation = attenuationLightPoint_[ 3 ].x
		+ attenuationLightPoint_[ 3 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 3 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 3 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 3 ], vectorLightToVertex, normal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 3 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 3 ], vectorLightToVertex, normal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 4 ] );
	attenuation = attenuationLightPoint_[ 4 ].x
		+ attenuationLightPoint_[ 4 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 4 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 4 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 4 ], vectorLightToVertex, normal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 4 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 4 ], vectorLightToVertex, normal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 5 ] );
	attenuation = attenuationLightPoint_[ 5 ].x
		+ attenuationLightPoint_[ 5 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 5 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 5 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 5 ], vectorLightToVertex, normal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 5 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 5 ], vectorLightToVertex, normal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 6 ] );
	attenuation = attenuationLightPoint_[ 6 ].x
		+ attenuationLightPoint_[ 6 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 6 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 6 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 6 ], vectorLightToVertex, normal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 6 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 6 ], vectorLightToVertex, normal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 7 ] );
	attenuation = attenuationLightPoint_[ 7 ].x
		+ attenuationLightPoint_[ 7 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 7 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 7 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 7 ], vectorLightToVertex, normal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 7 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 7 ], vectorLightToVertex, normal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// ポイントライトの減衰率を計算
	distanceLightToVertex = distance( vertex.positionWorld_, positionLightPoint_[ 8 ] );
	attenuation = attenuationLightPoint_[ 8 ].x
		+ attenuationLightPoint_[ 8 ].y * distanceLightToVertex
		+ attenuationLightPoint_[ 8 ].z * distanceLightToVertex * distanceLightToVertex;

	// ライトから頂点へのベクトルを求める
	vectorLightToVertex = normalize( vertex.positionWorld_ - positionLightPoint_[ 8 ] );

	// ディレクショナルライトのディフューズ色を計算
	diffusePoint = CalculateDiffuse( colorLightPoint_[ 8 ], vectorLightToVertex, normal );

	// ポイントライトのスペキュラ色を計算
	specularPoint = CalculateSpecular( colorLightPoint_[ 8 ], vectorLightToVertex, normal, vectorVertexToEye, reflection_, power_ );

	// ポイントライトのリム色を計算
	rimPoint = CalculateRim( colorLightPoint_[ 8 ], vectorLightToVertex, normal, vectorVertexToEye );

	// ポイントライトの色を計算
	color += (colorDiffuse * diffusePoint + colorSpecular_ * specularPoint + rimPoint) / attenuation;

	// 値の設定
	PixelOutput	output;		// ピクセルシェーダ出力
	output.color_ = float4( color, 0.8f * proportionEnvironment + 0.2f );
	output.depth_.gba = 0.0f;
	output.depth_.r = vertex.depth_;

	// ピクセルシェーダ出力を返す
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
		// シェーダの設定
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
