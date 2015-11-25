//==============================================================================
// 
// File   : Shadow.fx
// Brief  : 影エフェクト
// Author : Taiga Shirakawa
// Date   : 2015/11/24 tsu : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float2		offsetTexel_;					// テクセルオフセット

float4x4	matrixProjectionInverse_;		// プロジェクション変換逆行列
float4x4	matrixViewInverse_;				// ビュー変換逆行列
texture		textureDepth_;					// 深度テクスチャ

float4x4	matrixTransformLight_;			// ライトの変換行列
float4x4	matrixViewLight_;				// ライトのビュー変換行列
texture		textureDepthLight_;				// ライトの深度テクスチャ

//******************************************************************************
// サンプリング
//******************************************************************************
sampler samplerTextureDepth = sampler_state
{
	Texture = < textureDepth_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthLight = sampler_state
{
	Texture = < textureDepthLight_ >;
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

//==============================================================================
// Brief  : 頂点変換
// Return : VertexOutput					: 頂点シェーダ出力
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
// Return : float4							: 深度
// Arg    : VertexOutput					: 頂点シェーダ出力
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// ワールド座標を求める
	float	dataDepth = tex2D( samplerTextureDepth, vertex.textureCoord_ ).r;
	float2	positionTexture = vertex.textureCoord_ * 2.0f - 1.0f;
	float3	positionProjection = mul( float4( positionTexture.x, -positionTexture.y, 1.0f, 1.0f ), matrixProjectionInverse_ ).xyz;
	float3	positionView = float3( positionProjection.xy, 1.0f ) * dataDepth;
	float3	positionWorld = mul( float4( positionView, 1.0f ), matrixViewInverse_ );

	// テクスチャの座標を求める
	float4	positionLight = mul( float4( positionWorld, 1.0f ), matrixTransformLight_ );
	float2	positionTextureLight = positionLight.xy / positionLight.w;
	positionTextureLight = float2( 1.0f + positionTextureLight.x, 1.0f - positionTextureLight.y );
	positionTextureLight *= 0.5f;

	// 深度を取得
	float	depthLight = 1000.0f - tex2D( samplerTextureDepthLight, positionTextureLight ).r;
	float	depth = mul( float4( positionWorld, 1.0f ), matrixViewLight_ ).z;

	// 色を返す
	float4	color;
	color.gba = 0.0f;
	if( depth - depthLight > 2.0f )
	{
		color.r = 0.5f;
	}
	else
	{
		color.r = 1.0f;
	}
//	color.r = depthLight;
	return color;
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
