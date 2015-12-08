//==============================================================================
// 
// File   : BlurBase.fx
// Brief  : 影用ブラーエフェクト
// Author : Taiga Shirakawa
// Date   : 2015/12/08 tsu : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float2	offsetTexel_;		// テクセルオフセット
texture	texture_;			// テクスチャ

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
	float4	position_		: POSITION;			// 座標
	float2	textureCoord_	: TEXCOORD0;		// テクスチャ座標
};

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

	// テクスチャ座標を格納
	output.textureCoord_ = textureCoord + 0.5f * offsetTexel_;

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
	// 値の出力
	float3	color = 0.25f * tex2D( samplerTexture, vertex.textureCoord_ ).rgb;
	color += 0.125f * tex2D( samplerTexture, vertex.textureCoord_ + float2( offsetTexel_.x, 0.0f ) );
	color += 0.125f * tex2D( samplerTexture, vertex.textureCoord_ + float2( -offsetTexel_.x, 0.0f ) );
	color += 0.125f * tex2D( samplerTexture, vertex.textureCoord_ + float2( 0.0f, offsetTexel_.y ) );
	color += 0.125f * tex2D( samplerTexture, vertex.textureCoord_ + float2( 0.0f, -offsetTexel_.y ) );
	color += 0.0625f * tex2D( samplerTexture, vertex.textureCoord_ + float2( offsetTexel_.x, offsetTexel_.y ) );
	color += 0.0625f * tex2D( samplerTexture, vertex.textureCoord_ + float2( offsetTexel_.x, -offsetTexel_.y ) );
	color += 0.0625f * tex2D( samplerTexture, vertex.textureCoord_ + float2( -offsetTexel_.x, offsetTexel_.y ) );
	color += 0.0625f * tex2D( samplerTexture, vertex.textureCoord_ + float2( -offsetTexel_.x, -offsetTexel_.y ) );
	return float4( color, 1.0f );
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
