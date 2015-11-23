//==============================================================================
// 
// File   : WaveData.fx
// Brief  : 波情報エフェクト
// Author : Taiga Shirakawa
// Date   : 2015/11/17 mon : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixWorld_;		// ワールド変換行列
texture		textureHeight_;		// 高さ情報テクスチャ
float3		waveAdd_;			// 波の追加情報

const float	sizeTextureHalf_ = 128.0f;		// テクスチャの半分のサイズ
const float	offset_ = 1.0f / 256.0f;		// オフセット
const float	powerSpring_ = 0.5f;			// ばねの強さ

//******************************************************************************
// サンプリング
//******************************************************************************
sampler samplerTextureHeight = sampler_state
{
	Texture = < textureHeight_ >;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = WRAP;
	AddressV = WRAP;
};

//******************************************************************************
// 構造体定義
//******************************************************************************
// 頂点シェーダ出力
struct VertexOutput
{
	float4	position_			: POSITION;			// 座標
	float2	textureCoord_		: TEXCOORD0;		// テクスチャ座標
};

// ピクセルシェーダ出力
struct PixelOutput
{
	float4	height_				: COLOR0;			// 高さ
	float4	normal_				: COLOR1;			// 法線
};

//==============================================================================
// Brief  : 頂点変換
// Return : VertexOutput					: 頂点シェーダ出力
// Arg    : float4 positionLocal			: ローカル座標
// Arg    : float3 vectorNormalLocal		: 法線ベクトル
// Arg    : float2 positionTexture			: テクスチャ座標
// Arg    : float4 colorDiffuse				: ディフューズ色
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 vectorNormalLocal : NORMAL, float2 textureCoord : TEXCOORD0 )
{
	// 頂点の変換
	VertexOutput	output;		// 出力
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;

	// 値を格納
	output.textureCoord_ = textureCoord;
	output.textureCoord_ += float2( 0.5f * offset_, 0.5f * offset_ );

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
	// 高さ情報を取得
	float2	heightCurrent = tex2D( samplerTextureHeight, vertex.textureCoord_ ).rg;
	float4	heightAround = float4(
		tex2D( samplerTextureHeight, vertex.textureCoord_ + float2( offset_, 0.0f ) ).r,
		tex2D( samplerTextureHeight, vertex.textureCoord_ + float2( 0.0f, offset_ ) ).r,
		tex2D( samplerTextureHeight, vertex.textureCoord_ - float2( offset_, 0.0f ) ).r,
		tex2D( samplerTextureHeight, vertex.textureCoord_ - float2( 0.0f, offset_ ) ).r
	);

	// 速度を計算
	float	velocity = heightAround.r + heightAround.g + heightAround.b + heightAround.a;
	velocity = (0.25f * velocity - heightCurrent.r) * powerSpring_ + heightCurrent.g;
	if( distance( vertex.textureCoord_, waveAdd_.xy ) < 10.0f * offset_ )
	{
		velocity += waveAdd_.z;
	}

	// 高さを更新
	PixelOutput	output;		// ピクセルシェーダ出力
	float		height = heightCurrent.r + velocity;
//	height += -0.001f * height;
	output.height_ = float4( height, velocity, 1.0f, 1.0f );

	// 法線を計算
	float2	vectorHeight = float2( heightAround.b - heightAround.r, heightAround.a - heightAround.g ) * 0.5f + 0.5f;
	output.normal_ = float4( vectorHeight, 1.0f, 0.5f * heightCurrent.r + 0.5f );

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
