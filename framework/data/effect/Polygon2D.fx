//==============================================================================
// 
// File   ： Polygon2D.fx
// Brief  ： 2Dポリゴンエフェクト
// Author ： Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixWorld_;			// ワールドマトリクス
texture		texture_;				// テクスチャ
float		widthScreenHalf_;		// 画面幅の半分
float		heightScreenHalf_;		// 画面高さの半分
float4		color_;					// 色
float2		positionTexture_;		// テクスチャ座標
float2		scaleTexture_;			// テクスチャ拡縮

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
	float4	color0_			: COLOR0;			// 色
	float4	color1_			: COLOR1;			// マスク
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
	output.position_ = mul( output.position_, matrixWorld_ );
	output.position_.x /= widthScreenHalf_;
	output.position_.y /= heightScreenHalf_;

	// テクスチャ座標の変換
	output.textureCoord_ = textureCoord / scaleTexture_ + positionTexture_;

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
	output.color0_ = tex2D( samplerTexture, vertex.textureCoord_ ) * color_;
	output.color1_ = float4( 1.0f, 0.0f, 0.0f, output.color0_.a );
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
		// レンダーステートの設定
		ZEnable = False;
		ZWriteEnable = False;
		AlphaBlendEnable = True;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		// シェーダの設定
		VertexShader = compile vs_2_0 TransformVertex();
		PixelShader = compile ps_2_0 DrawPixel();
	}
}