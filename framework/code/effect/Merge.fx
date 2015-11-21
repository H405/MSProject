//==============================================================================
// 
// File   : Merge.fx
// Brief  : 総合3D描画エフェクト
// Author : Taiga Shirakawa
// Date   : 2015/11/03 sun : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixWorld_;			// ワールド変換行列
float2		sizeScreenHalf_;		// 画面サイズの半分
float		forcus_;				// 焦点距離

texture		textureLight_;			// ライトありテクスチャ
texture		textureNotLight_;		// ライトなしテクスチャ
texture		textureMask_;			// マスクテクスチャ
texture		textureAdd_;			// 加算合成テクスチャ
texture		textureDepth_;			// 深度テクスチャ
texture		textureRiver_;			// 川テクスチャ
texture		textureDepthRiver_;		// 川深度テクスチャ

//******************************************************************************
// サンプリング
//******************************************************************************
sampler samplerTextureLight = sampler_state
{
	Texture = < textureLight_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureNotLight = sampler_state
{
	Texture = < textureNotLight_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureMask = sampler_state
{
	Texture = < textureMask_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureAdd = sampler_state
{
	Texture = < textureAdd_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepth = sampler_state
{
	Texture = < textureDepth_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureRiver = sampler_state
{
	Texture = < textureRiver_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthRiver = sampler_state
{
	Texture = < textureDepthRiver_ >;
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

// ピクセルシェーダ出力
struct PixelOutput
{
	float4	color_			: COLOR0;			// 座標
	float4	depth_			: COLOR1;			// 深度
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

	// 値を格納
	output.textureCoord_ = textureCoord;

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
	// ピクセル色を返す
	PixelOutput	output;
	float	maskLight = tex2D( samplerTextureMask , vertex.textureCoord_ );
	float3	colorLight = tex2D( samplerTextureLight , vertex.textureCoord_ ).rgb;
	float3	colorNotLight = tex2D( samplerTextureNotLight , vertex.textureCoord_ ).rgb;
	float3	colorAdd = tex2D( samplerTextureAdd , vertex.textureCoord_ ).rgb;
	float4	colorRiver = tex2D( samplerTextureRiver , vertex.textureCoord_ );

	// 深度の取得
	float	depthRiver = tex2D( samplerTextureDepthRiver, vertex.textureCoord_ ).r;
	output.depth_.gba = 0.0f;
	output.depth_.r = (1.0f - maskLight) * tex2D( samplerTextureDepth , vertex.textureCoord_ ).r + maskLight * forcus_;

	// 色を求める
	float	proportionRiver = colorRiver.a;// * max( (output.depth_.r - depthRiver), 0.0f ) / output.depth_.r;
	float3	colorLightAndRiver = (1.0f - proportionRiver) * colorLight + proportionRiver * colorRiver;
	output.color_ = float4( (1.0f - maskLight) * colorLightAndRiver + maskLight * colorNotLight + colorAdd, 1.0f );

	// 値を返す
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
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
