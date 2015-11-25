//==============================================================================
// 
// File   : SkinMeshReflect.fx
// Brief  : 反射スキンメッシュエフェクト
// Author : Taiga Shirakawa
// Date   : 2015/11/23 mon : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixTransform_;		// 変換行列
float4x4	matrixWorld_;			// ワールド変換行列
float4x4	matrixWorldView_;		// ワールドビュー変換行列
float4x3	matrixBone_[ 70 ];		// ボーン変換行列
float		height_;				// 反射面の高さ
texture		texture_;				// テクスチャ
float3		colorSpecular_;			// スペキュラ色
float		reflection_;			// 反射率
float		power_;					// 反射の強さ
float		refractive_;			// 屈折率

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
	float4	position_			: POSITION;			// 座標
	float2	textureCoord_		: TEXCOORD0;		// テクスチャ座標
	float3	vectorNormalWorld_	: TEXCOORD1;		// 変換後法線
	float	depth_				: TEXCOORD2;		// 深度
	float	heightWorld_		: TEXCOORD3;		// ワールド座標の高さ
};

// ピクセルシェーダ出力
struct PixelOutput
{
	float4	diffuse_			: COLOR0;			// ディフューズ色
	float4	specular_			: COLOR1;			// スペキュラ色
	float4	normal_				: COLOR2;			// 法線
	float4	depth_				: COLOR3;			// 深度
};

//==============================================================================
// Brief  : 頂点変換
// Return : VertexOutput					: 頂点シェーダ出力
// Arg    : float4 positionLocal			: ローカル座標
// Arg    : float3 weight					: ブレンド割合
// Arg    : float4 indices					: 頂点番号
// Arg    : float3 vectorNormalLocal		: 法線ベクトル
// Arg    : float2 positionTexture			: テクスチャ座標
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 weight : BLENDWEIGHT, float4 indices : BLENDINDICES, float3 vectorNormalLocal : NORMAL, float2 textureCoord : TEXCOORD0 )
{
	// 頂点のボーン行列変換
	VertexOutput	output;				// 頂点シェーダ出力
	float4x3		matrixBone;			// ボーン変換行列
	float4x4		matrixBone4x4;		// 4x4ボーン変換行列
	matrixBone = matrixBone_[ indices[ 0 ] ] * weight.x;
	matrixBone += matrixBone_[ indices[ 1 ] ] * weight.y;
	matrixBone += matrixBone_[ indices[ 2 ] ] * weight.z;
	matrixBone += matrixBone_[ indices[ 3 ] ] * (1.0f - weight.x - weight.y - weight.z);
	matrixBone4x4 = float4x4( matrixBone[ 0 ], 0.0f, matrixBone[ 1 ], 0.0f, matrixBone[ 2 ], 0.0f, matrixBone[ 3 ], 1.0f );
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixBone4x4 );
	output.heightWorld_ = mul( float4( output.position_.xyz, 1.0f ), matrixWorld_ ).y;

	// 深度の計算
	output.depth_ = mul( output.position_, matrixWorldView_ ).z;

	// 頂点の変換
	output.position_ = mul( output.position_, matrixTransform_ );

	// 法線の変換
	output.vectorNormalWorld_ = normalize( mul( float4( vectorNormalLocal, 0.0f ), matrixBone4x4 ) ).xyz;
	output.vectorNormalWorld_ = normalize( mul( float4( output.vectorNormalWorld_, 0.0f ), matrixWorld_ ) ).xyz;

	// 出力値の格納
	output.textureCoord_ = textureCoord;

	// 頂点シェーダ出力を返す
	return output;
}

//==============================================================================
// Brief  : ピクセル描画
// Return : PixelOutput						: ピクセルシェーダ出力
// Arg    : VertexOutput					: 頂点シェーダ出力
//==============================================================================
PixelOutput DrawPixel( VertexOutput vertex )
{
	// 反射面より下は描画しない
	clip( height_ - vertex.heightWorld_ );

	// 値の設定
	PixelOutput	output;		// ピクセルシェーダ出力
	output.diffuse_ = float4( tex2D( samplerTexture, vertex.textureCoord_ ).rgb, reflection_ );
	output.specular_ = float4( colorSpecular_, power_ * 0.015625f );
	output.normal_ = float4( (vertex.vectorNormalWorld_ * 0.5f + 0.5f), refractive_ );
	output.depth_.gba = 0.0f;
	output.depth_ = vertex.depth_;

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
		CullMode = CW;

		// シェーダの設定
		VertexShader = compile vs_3_0 TransformVertex();
		PixelShader = compile ps_3_0 DrawPixel();
	}
}
