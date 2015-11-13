//==============================================================================
// 
// File   : PostEffect.fx
// Brief  : ポストエフェクト
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixWorld_;			// ワールドマトリクス
float2		sizeScreenHalf_;		// 画面サイズの半分
float4		colorFade_;				// フェードの色
float		proportionFade_;		// フェード割合
float		forcus_;				// 焦点距離
texture		texture_;				// テクスチャ
texture		texture3D_;				// 3D描画テクスチャ
texture		textureLuminance_;		// 輝度テクスチャ
texture		textureBlur_;			// ブラーテクスチャ
texture		textureDepth_;			// 深度テクスチャ
texture		texture2D_;				// 2D描画テクスチャ
texture		textureMask_;			// マスクテクスチャ

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

sampler samplerTexture3D = sampler_state
{
	Texture = < texture3D_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureLuminance = sampler_state
{
	Texture = < textureLuminance_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureBlur = sampler_state
{
	Texture = < textureBlur_ >;
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

sampler samplerTexture2D = sampler_state
{
	Texture = < texture2D_ >;
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
// Brief  : 頂点変換
// Return : VertexOutput					: 頂点出力
// Arg    : float4 positionLocal			: ローカル座標
// Arg    : float3 vectorNormal				: 法線ベクトル
// Arg    : float2 positionTexture			: テクスチャ座標
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float2 textureCoord : TEXCOORD0, float4 diffuse : COLOR0 )
{
	// 頂点の変換
	VertexOutput	output;		// 出力
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;
	output.position_ = mul( output.position_, matrixWorld_ );
	output.position_.xy /= sizeScreenHalf_;

	// 値を格納
	output.textureCoord_ = textureCoord;
	output.diffuse_ = diffuse;

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
	// フォーカスの算出
	float	proportion = forcus_ - tex2D( samplerTextureDepth, vertex.textureCoord_ ).r;
	if( proportion < 0.0f )
	{
		proportion += (1.0f - forcus_) * 0.2f;
		proportion = max( -proportion, 0.0f );
		proportion /= (1.0f - forcus_) * 0.9f + 0.00001f;
	}
	else
	{
		proportion -= forcus_ * 0.2f;
		proportion = max( proportion, 0.0f );
		proportion /= forcus_ * 0.9f + 0.00001f;
	}
//	proportion *= proportion;
//	proportion = min( 4.0f * proportion, 1.0f );
//	return float4( proportion, proportion, proportion, 1.0f );

	// 通常描画色の決定
	float3	color3D = (1.0f - proportion) * tex2D( samplerTexture3D, vertex.textureCoord_ ).rgb + proportion * tex2D( samplerTextureBlur, vertex.textureCoord_ ).rgb;
	float3	color3DLuminance = color3D + tex2D( samplerTextureLuminance, vertex.textureCoord_ ).rgb;
	float	mask = tex2D( samplerTextureMask, vertex.textureCoord_ ).r;
	float3	colorGeneral = (1.0f - mask) * color3DLuminance + mask * tex2D( samplerTexture2D, vertex.textureCoord_ ).rgb;
	float3	colorFade = tex2D( samplerTexture, vertex.textureCoord_ ).rgb * colorFade_;
	return float4( (1.0f - proportionFade_) * colorGeneral + proportionFade_ * colorFade_, 1.0f );
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
