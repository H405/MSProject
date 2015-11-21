//==============================================================================
// 
// File   : WaveData.fx
// Brief  : 波情報初期化エフェクト
// Author : Taiga Shirakawa
// Date   : 2015/11/17 mon : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixWorld_;		// ワールドマトリクス
texture		texture_;			// テクスチャ

const float	offset_ = 1.0f / 256.0f;		// テクスチャの半分のサイズ

//******************************************************************************
// サンプリング
//******************************************************************************
sampler samplerTexture = sampler_state
{
	Texture = < texture_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = Wrap;
	AddressV = Wrap;
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
	float4	height_			: COLOR0;			// 高さ
	float4	normal_			: COLOR1;			// 法線
};

//==============================================================================
// Brief  ： 頂点変換
// Return ： VertexOutput					： 頂点出力
// Arg    ： float4 positionLocal			： ローカル座標
// Arg    ： float2 positionTexture			： テクスチャ座標
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float2 textureCoord : TEXCOORD0 )
{
	// 頂点の変換
	VertexOutput	output;		// 出力
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;
	output.position_.xy *= 2.0f;

	// 値の設定
	output.textureCoord_ = textureCoord;
	output.textureCoord_ += float2( 0.5f * offset_, 0.5f * offset_ );

	// 頂点出力を返す
	return output;
}

//==============================================================================
// Brief  ： ピクセル描画
// Return ： float4 : COLOR0				： 色
// Arg    ： VertexOutput					： 頂点シェーダ出力
//==============================================================================
PixelOutput DrawPixel( VertexOutput vertex )
{
	// ピクセル色を返す
	PixelOutput	output;		// 出力
	float4		color = tex2D( samplerTexture, vertex.textureCoord_ );
	output.height_ = float4( color.rg - color.ba, 1.0f, 1.0f );
	output.normal_ = float4( 0.5f, 0.5f, 1.0f, 0.0f );
	return output;
}

//==============================================================================
// Brief  ： 通常変換
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
