//==============================================================================
// 
// File   ： Model.fx
// Brief  ： モデルエフェクト
// Author ： Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
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
float3		attemuationLightPoint_[ 32 ];		// ポイントライトの減衰率
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
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = Clamp;
	AddressV = Clamp;
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

//==============================================================================
// Brief  ： ディレクショナルライトのディフューズ
// Return ： float3							： 色
// Arg    ： float3 vectorNormalWorld		： 法線ベクトル
//==============================================================================
float3 CalculateDiffuseDirection( float3 vectorNormal )
{
	// 明度の計算
	float	lightness = dot( vectorNormal, -vectorLightDirection_ ) * 0.5f + 0.5f;

	// ディフューズ色を返す
	return colorLightDirection_ * lightness + colorLightDirection_ * colorAmbient_.rgb;
}

//==============================================================================
// Brief  ： ディレクショナルライトのスペキュラ
// Return ： float3							： 色
// Arg    ： float3 vectorNormalWorld		： 法線ベクトル
// Arg    ： float3 vectorVertexToEye		： 頂点から視点へのベクトル
//==============================================================================
float3 CalculateSpecularDirection( float3 vectorNormal, float3 vectorVertexToEye )
{
	// ハーフベクトルを求める
	float3	vectorHalf = normalize( vectorVertexToEye - vectorLightDirection_ );

	// スペキュラ色を返す
	return colorLightDirection_ * pow( max( dot( vectorNormal, vectorHalf ), 0.0f ), power_ ) * reflection_;
}

//==============================================================================
// Brief  ： ディレクショナルライトのリム
// Return ： float3							： 色
// Arg    ： float3 vectorNormalWorld		： 法線ベクトル
// Arg    ： float3 vectorVertexToEye		： 頂点から視点へのベクトル
//==============================================================================
float3 CalculateRimDirection( float3 vectorNormal, float3 vectorVertexToEye )
{
	// リム色を返す
	float	rim = (1.0f - max( dot( vectorNormal, vectorVertexToEye ), 0.0f )) * max( dot( vectorLightDirection_, vectorVertexToEye ), 0.0f );
	rim = min( 5.0f * pow( rim, 5.0f ), 1.0f );
	return colorLightDirection_ * rim;
}

//==============================================================================
// Brief  ： 頂点変換
// Return ： VertexOutput					： 頂点出力
// Arg    ： float4 positionLocal			： ローカル座標
// Arg    ： float3 vectorNormalLocal		： 法線ベクトル
// Arg    ： float2 positionTexture			： テクスチャ座標
// Arg    ： float4 colorDiffuse			： ディフューズ色
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
// Brief  ： ピクセル描画
// Return ： float4 : COLOR0				： 色
// Arg    ： VertexOutput					： 頂点シェーダ出力
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
	float3	diffuseDirection = CalculateDiffuseDirection( vertex.vectorNormalWorld_ );

	// ディレクショナルライトのスペキュラ色を計算
	float3	specularDirection = CalculateSpecularDirection( vertex.vectorNormalWorld_, vectorVertexToEye );

	// ディレクショナルライトのリム色を計算
	float3	rimDirection = CalculateRimDirection( vertex.vectorNormalWorld_, vectorVertexToEye );

	// ピクセル色を返す
	float3	color = colorDiffuse.rgb * (diffuseDirection + colorAmbient_) + colorSpecular_ * (specularDirection + specularAmbient ) + rimDirection;
	return float4( color, colorDiffuse.a );

//	// 明度の計算
//	float	lightness = GetLightness( vertex.vectorNormalWorld_ );//dot( vertex.vectorNormalWorld_, -vectorLight_ ) * 0.5f + 0.5f;
//
//	// ディフューズ色の計算
//	float3	diffuse = colorDiffuse_.rgb * tex2D( samplerTexture, vertex.textureCoord_ ) * lightness * colorLight_.rgb + colorAmbient_.rgb;
//
//	// フレネル反射率を算出
//	float3	vectorVertexToEye = normalize( positionEye_ - vertex.positionWorld_.xyz );
//	float	fresnel = refractive_ + (1.0f - refractive_) * exp( -6.0f * max( dot( vertex.vectorNormalWorld_, vectorVertexToEye ), 0.0f ) );
//
//	// スペキュラ色の算出
//	float3	vectorHalf = normalize( vectorVertexToEye - vectorLight_ );
//	float3	specular = colorSpecular_.rgb * (pow( max( dot( vertex.vectorNormalWorld_, vectorHalf ), 0.0f ), power_ ) * reflection_ + colorAmbient_.rgb * fresnel);
////	float3	specular = colorSpecular_.rgb * (pow( max( dot( reflect( vectorLight_, vertex.vectorNormalWorld_ ), vectorVertexToEye ), 0.0f ), power_ ) * reflection_ + colorAmbient_.rgb * fresnel);
//
//	// ピクセル色を返す
//	return float4( diffuse + specular, colorDiffuse_.a );
}

//==============================================================================
// Brief  ： 通常変換
//==============================================================================
technique ShadeNormal
{
	// 通常変換
	pass PassNormal
	{
		// レンダーステートの設定
		AlphaBlendEnable = True;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		// シェーダの設定
		VertexShader = compile vs_2_0 TransformVertex();
		PixelShader = compile ps_2_0 DrawPixel();
	}
}