//==============================================================================
// 
// File   : Point.fx
// Brief  : ポイントスプライトエフェクト
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixView_;			// ビュー変換行列
float4x4	matrixProjection_;		// プロジェクション変換行列
texture		texture_;				// テクスチャ

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
	float4	position_	: POSITION;		// 座標
	float	size_		: PSIZE;		// サイズ
	float4	color_		: COLOR0;		// 色
};

// ピクセルシェーダ出力
struct PixelOutput
{
	float4	color_		: COLOR0;		// 色
	float4	mask_		: COLOR1;		// マスク
	float4	add_		: COLOR2;		// 加算合成
};

//==============================================================================
// Brief  : 頂点変換
// Return : VertexOutput					: 頂点出力
// Arg    : float4 positionWorld			: ワールド座標
// Arg    : float size						: ポイントスプライトのサイズ
// Arg    : float4 color					: 色
//==============================================================================
VertexOutput TransformVertex( float3 positionWorld : POSITION, float size : PSIZE, float4 color : COLOR0 )
{
	// 頂点の変換
	VertexOutput	output;			// 出力
	float			lengthView;		// ビュー座標系の長さ
	output.position_ = mul( float4( positionWorld, 1.0f ), matrixView_ );
	lengthView = length( output.position_.xyz );
	output.position_ = mul( output.position_, matrixProjection_ );

	// サイズの計算
	output.size_ = 10.0f * size * (matrixProjection_._22 / matrixProjection_._11) * sqrt( 1.0f / lengthView );

	// 値を格納
	output.color_ = color;

	// 頂点出力を返す
	return output;
}

//==============================================================================
// Brief  : ピクセル描画
// Return : PixelOutput						: ピクセルシェーダ出力
// Arg    : float2 textureCoord				: テクスチャ座標
// Arg    : float4 color					: 色
//==============================================================================
PixelOutput DrawPixel( float2 textureCoord : TEXCOORD0, float4 color : COLOR0 )
{
	// 値の設定
	PixelOutput	output;		// ピクセルシェーダ出力
	output.color_ = 0.0f;
	output.mask_ = 0.0f;
	output.add_ = tex2D( samplerTexture, textureCoord ) * color;

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
		// レンダーステートの設定
		PointSpriteEnable = True;
		ZWriteEnable = False;
		AlphaBlendEnable = True;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = One;

		// シェーダの設定
		VertexShader = compile vs_2_0 TransformVertex();
		PixelShader = compile ps_2_0 DrawPixel();
	}
}