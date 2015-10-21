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
texture		textureGeneral_;		// 通常描画テクスチャ
float4		colorFade_;				// フェードの色
float		widthScreenHalf_;		// 画面幅の半分
float		heightScreenHalf_;		// 画面高さの半分
float		proportionFade_;		// フェード割合

//******************************************************************************
// サンプリング
//******************************************************************************
sampler samplerTexture = sampler_state
{
	Texture = < texture_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = Clamp;
	AddressV = Clamp;
};

sampler samplerTextureGeneral = sampler_state
{
	Texture = < textureGeneral_ >;
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
	output.position_.x /= widthScreenHalf_;
	output.position_.y /= heightScreenHalf_;

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
	// 通常描画色の決定
	float4	colorGeneral = tex2D( samplerTextureGeneral, vertex.textureCoord_ );
	float4	colorFade = tex2D( samplerTexture, vertex.textureCoord_ ) * colorFade_;
	return (1.0f - proportionFade_) * colorGeneral + proportionFade_ * colorFade_;
}

//==============================================================================
// Brief  ： 通常変換
//==============================================================================
technique ShadeNormal
{
	// 通常変換
	pass PassNormal
	{
		VertexShader = compile vs_2_0 TransformVertex();
		PixelShader = compile ps_2_0 DrawPixel();
	}
}