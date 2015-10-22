//==============================================================================
// 
// File   ： Mesh.fx
// Brief  ： メッシュエフェクト
// Author ： Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixTransform_;		// 変換行列
float4x4	matrixWorld_;			// ワールド変換行列
float3		vectorLight_;			// ライトベクトル
float3		positionEye_;			// カメラの座標
texture		texture_;				// テクスチャ
float4		colorAmbient_;			// 環境色
float4		colorLight_;			// ライトの色
float4		colorDiffuse_;			// ディフューズ色
float4		colorSpecular_;			// スペキュラ色
float		reflection_;			// 反射率
float		power_;					// 反射の強さ
float		refractive_;			// 屈折率

//******************************************************************************
// サンプリング
//******************************************************************************
sampler samplerTexture = sampler_state
{
	Texture = < texture_ >;
	MinFilter = Anisotropic;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = Wrap;
	AddressV = Wrap;
	MaxAnisotropy = 8;
};

//******************************************************************************
// 構造体定義
//******************************************************************************
// 頂点シェーダ出力
struct VertexOutput
{
	float4	position_			: POSITION;			// 座標
	float4	colorDiffuse_		: COLOR0;			// ディフューズ色
	float2	textureCoord_		: TEXCOORD0;		// テクスチャ座標
	float3	positionWorld_		: TEXCOORD1;		// ワールド座標
	float3	vectorNormalWorld_	: TEXCOORD2;		// ワールド法線
};

//==============================================================================
// Brief  ： 頂点変換
// Return ： VertexOutput					： 頂点出力
// Arg    ： float4 positionLocal			： ローカル座標
// Arg    ： float3 vectorNormalLocal		： 法線ベクトル
// Arg    ： float2 positionTexture			： テクスチャ座標
// Arg    ： float4 colorDiffuse			： ディフューズ色
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 vectorNormalLocal : NORMAL, float2 textureCoord : TEXCOORD0, float4 colorDiffuse : COLOR0 )
{
	// 頂点の変換
	VertexOutput	output;		// 出力
	output.position_ = mul( float4( positionLocal, 1.0f ), matrixTransform_ );

	// ワールド頂点の変換
	output.positionWorld_ = mul( float4( positionLocal.xyz, 1.0f ), matrixWorld_ ).xyz;

	// ワールド法線の変換
	output.vectorNormalWorld_ = normalize( mul( float4( vectorNormalLocal, 0.0f ), matrixWorld_ ) ).xyz;

	// 出力値の格納
	output.colorDiffuse_ = colorDiffuse;
	output.textureCoord_ = textureCoord;

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
	// 明度の計算
	float	lightness = dot( vertex.vectorNormalWorld_, -vectorLight_ ) * 0.5f + 0.5f;

	// ディフューズ色の計算
	float3	diffuse = colorDiffuse_.rgb * tex2D( samplerTexture, vertex.textureCoord_ ) * lightness * colorLight_.rgb * vertex.colorDiffuse_.rgb + colorAmbient_.rgb;

	// フレネル反射率を算出
	float3	vectorVertexToEye = normalize( positionEye_ - vertex.positionWorld_.xyz );
	float	fresnel = refractive_ + (1.0f - refractive_) * exp( -6.0f * max( dot( vertex.vectorNormalWorld_, vectorVertexToEye ), 0.0f ) );

	// スペキュラ色の算出
	float3	vectorHalf = normalize( vectorVertexToEye - vectorLight_ );
	float3	specular = colorSpecular_.rgb * (pow( max( dot( vertex.vectorNormalWorld_, vectorHalf ), 0.0f ), power_ ) * reflection_ + colorAmbient_.rgb * fresnel);

	// ピクセル色を返す
	return float4( diffuse + specular, colorDiffuse_.a );
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