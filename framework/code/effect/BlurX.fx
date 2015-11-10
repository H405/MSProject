//==============================================================================
// 
// File   : BlurBase.fx
// Brief  : ブラー基エフェクト
// Author : Taiga Shirakawa
// Date   : 2015/11/10 tsu : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixWorld_;		// ワールドマトリクス
float2		sizeScreenHalf_;	// 画面サイズの半分
texture		texture_;			// テクスチャ
float2		offset_;			// オフセット

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
	float2	textureCoord0_	: TEXCOORD0;		// テクスチャ座標
	float2	textureCoord1_	: TEXCOORD1;		// テクスチャ座標
	float2	textureCoord2_	: TEXCOORD2;		// テクスチャ座標
	float2	textureCoord3_	: TEXCOORD3;		// テクスチャ座標
	float2	textureCoord4_	: TEXCOORD4;		// テクスチャ座標
	float2	textureCoord5_	: TEXCOORD5;		// テクスチャ座標
	float2	textureCoord6_	: TEXCOORD6;		// テクスチャ座標
	float2	textureCoord7_	: TEXCOORD7;		// テクスチャ座標
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
	output.position_ = mul( output.position_, matrixWorld_ );
	output.position_.xy /= sizeScreenHalf_;

	// テクスチャ座標を格納
	output.textureCoord0_ = textureCoord + float2( -2.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord1_ = textureCoord + float2( -4.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord2_ = textureCoord + float2( -6.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord3_ = textureCoord + float2( -8.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord4_ = textureCoord + float2( -10.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord5_ = textureCoord + float2( -12.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord6_ = textureCoord + float2( -14.0f / sizeScreenHalf_.x, 0.0f );
	output.textureCoord7_ = textureCoord + float2( -16.0f / sizeScreenHalf_.x, 0.0f );

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
	float4		color = float4( 0.13948364567f * (tex2D( samplerTexture, vertex.textureCoord0_ ).rgb + tex2D( samplerTexture, vertex.textureCoord7_ + offset_).rgb), 1.0f );
	color.rgb += 0.12309388525f * (tex2D( samplerTexture, vertex.textureCoord1_ ).rgb + tex2D( samplerTexture, vertex.textureCoord6_ + offset_).rgb);
	color.rgb += 0.09586561422f * (tex2D( samplerTexture, vertex.textureCoord2_ ).rgb + tex2D( samplerTexture, vertex.textureCoord5_ + offset_).rgb);
	color.rgb += 0.06588740886f * (tex2D( samplerTexture, vertex.textureCoord3_ ).rgb + tex2D( samplerTexture, vertex.textureCoord4_ + offset_).rgb);
	color.rgb += 0.03996273355f * (tex2D( samplerTexture, vertex.textureCoord4_ ).rgb + tex2D( samplerTexture, vertex.textureCoord3_ + offset_).rgb);
	color.rgb += 0.02139050984f * (tex2D( samplerTexture, vertex.textureCoord5_ ).rgb + tex2D( samplerTexture, vertex.textureCoord2_ + offset_).rgb);
	color.rgb += 0.01010416138f * (tex2D( samplerTexture, vertex.textureCoord6_ ).rgb + tex2D( samplerTexture, vertex.textureCoord1_ + offset_).rgb);
	color.rgb += 0.00421204112f * (tex2D( samplerTexture, vertex.textureCoord7_ ).rgb + tex2D( samplerTexture, vertex.textureCoord0_ + offset_).rgb);
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
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
