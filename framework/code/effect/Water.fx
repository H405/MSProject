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
float4x4	matrixTransformTexture_;			// テクスチャ座標変換行列

float4x4	matrixWorldInverseTranspose_;		// ワールド逆転置行列
texture		textureNormal_;						// 法線テクスチャ
float3		colorDiffuse_;						// ディフューズ色
float3		colorSpecular_;						// スペキュラ色
float		reflection_;						// 反射率
float		power_;								// 反射の強さ
float		refractive_;						// 屈折率

texture		textureReflect_;					// 反射テクスチャ
texture		texture3D_;							// 3D描画テクスチャ
texture		textureDepth_;						// 深度テクスチャ

float3		positionEye_;						// カメラの座標
float2		clipCamera_;						// カメラのクリップ値

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

sampler samplerTextureReflect = sampler_state
{
	Texture = < textureReflect_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

sampler samplerTexture3D = sampler_state
{
	Texture = < texture3D_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

sampler samplerTextureDepth = sampler_state
{
	Texture = < textureDepth_ >;
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
	float4	positionTexture_	: TEXCOORD5;		// テクスチャ座標
};

// ピクセルシェーダ出力
struct PixelOutput
{
	float4	diffuse_			: COLOR0;			// ディフューズ色
	float4	specular_			: COLOR1;			// スペキュラ色
	float4	normal_				: COLOR2;			// 法線
	float4	depth_				: COLOR3;			// 深度
};

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
	output.positionTexture_ = mul( float4( positionLocal, 1.0f ), matrixTransformTexture_ );

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
	float	height = tex2D( samplerTextureNormal, vertex.textureCoord_ ).a * 2.0f - 1.0f;

	// 法線を求める
	float3	tangent = normalize( vertex.tangentWorld_ - dot( vertex.tangentWorld_, vertex.vectorNormalWorld_ ) * vertex.vectorNormalWorld_ );
	float3	binormal = cross( vertex.vectorNormalWorld_, tangent );
	float3	vectorVertexToEyeTexture = normalize( mul( vectorVertexToEye, float3x3( tangent, binormal, vertex.vectorNormalWorld_ ) ) );
	float3	normalTexture = normalize( tex2D( samplerTextureNormal, vertex.textureCoord_ + 0.02f * height * vectorVertexToEye.xy ).rgb * 2.0f - 1.0f );
	float3	normal = normalize( mul( normalTexture, float3x3( tangent, binormal, vertex.vectorNormalWorld_ ) ) );
//	normal = vertex.vectorNormalWorld_;

	// ディフューズ色を求める
	float	proportionDepth = (tex2Dproj( samplerTextureDepth, vertex.positionTexture_ ) - vertex.depth_) / clipCamera_.y;
	float	offsetTextureReflect = float4( (normal - vectorVertexToEye).xy * refractive_ * 1000.0f * proportionDepth, 0.0f, 0.0f );
	float	offsetTextureUnder = float4( (normal - vectorVertexToEye).xy * refractive_ * 50.0f, 0.0f, 0.0f );
	float	proportionEnvironment = dot( normal, vectorVertexToEye );
	float3	colorReflerct = tex2Dproj( samplerTextureReflect, vertex.positionTexture_ + offsetTextureReflect );
	float3	colorUnder = tex2Dproj( samplerTexture3D, vertex.positionTexture_ + offsetTextureUnder );
	float3	colorWater = colorDiffuse_ * lerp( colorReflerct, colorUnder, proportionEnvironment );
	float3	colorDiffuse = lerp( tex2Dproj( samplerTexture3D, vertex.positionTexture_ ).rgb, colorWater, min( 200.0f * proportionDepth, 1.0f ) );

	// 値の設定
	PixelOutput	output;		// ピクセルシェーダ出力
	output.diffuse_ = float4( colorDiffuse, reflection_ );
	output.specular_ = float4( colorSpecular_, power_ * 0.015625f );
	output.normal_ = float4( normal * 0.5f + 0.5f, refractive_ );
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
