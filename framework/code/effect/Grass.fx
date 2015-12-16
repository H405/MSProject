//==============================================================================
// 
// File   : Grass.fx
// Brief  : 草エフェクト
// Author : Taiga Shirakawa
// Date   : 2015/12/10 fri : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixTransform_;		// 変換行列
float4x4	matrixWorldView_;		// ワールドビュー変換行列
texture		texture_;				// テクスチャ
float2		vectorWind_;			// 風向き

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
	float	depth_			: TEXCOORD1;		// 深度
};

// ピクセルシェーダ出力
struct PixelOutput
{
	float4	diffuse_		: COLOR0;			// ディフューズ色
	float4	specular_		: COLOR1;			// スペキュラ色
	float4	normal_			: COLOR2;			// 法線
	float4	depth_			: COLOR3;			// 深度
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
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixTransform_ );
	output.position_.xy += positionLocal.y * vectorWind_;

	// テクスチャ座標の変換
	output.textureCoord_ = textureCoord;

	// 深度の計算
	output.depth_ = mul( float4( positionLocal, 1.0f ), matrixWorldView_ ).z;

	// 頂点出力を返す
	return output;
}

//==============================================================================
// Brief  : ピクセル描画
// Return : PixelOutput						: ピクセルシェーダ出力
// Arg    : VertexOutput					: 頂点シェーダ出力
//==============================================================================
PixelOutput DrawPixel( VertexOutput vertex )
{
	// 描画するか判定
	float4	color = tex2D( samplerTexture, vertex.textureCoord_ );
	clip( color.a - 0.5f );

	// 値の設定
	PixelOutput	output;		// ピクセルシェーダ出力
	output.diffuse_ = float4( color.rgb, 0.1f );
	output.specular_ = float4( 0.02f, 0.05f, 0.04f, 0.078125f );
	output.normal_ = float4( 0.0f, 1.0f, 0.0f, 0.5f );
	output.depth_ = 0.0f;
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
