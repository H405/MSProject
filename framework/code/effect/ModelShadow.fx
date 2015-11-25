//==============================================================================
// 
// File   : ModelShadow.fx
// Brief  : モデル影エフェクト
// Author : Taiga Shirakawa
// Date   : 2015/11/24 tsu : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixTransform_;		// 変換行列
float4x4	matrixWorldView_;		// ワールドビュー変換行列

//******************************************************************************
// サンプリング
//******************************************************************************

//******************************************************************************
// 構造体定義
//******************************************************************************
// 頂点シェーダ出力
struct VertexOutput
{
	float4	position_	: POSITION;			// 座標
	float	depth_		: TEXCOORD2;		// 深度
};

//==============================================================================
// Brief  : 頂点変換
// Return : VertexOutput					: 頂点シェーダ出力
// Arg    : float4 positionLocal			: ローカル座標
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float3 vectorNormal : NORMAL )
{
	// 頂点の変換
	VertexOutput	output;		// 頂点シェーダ出力
	output.position_ = mul( float4( positionLocal + 2.5f * vectorNormal, 1.0f ), matrixTransform_ );

	// 深度の計算
	output.depth_ = mul( float4( positionLocal, 1.0f ), matrixWorldView_ ).z;

	// 頂点シェーダ出力を返す
	return output;
}

//==============================================================================
// Brief  : ピクセル描画
// Return : float4							: 深度
// Arg    : VertexOutput					: 頂点シェーダ出力
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// ピクセルシェーダ出力を返す
	float4	depth;
	depth.gba = 0.0f;
	depth.r = 1000.0f - vertex.depth_;
	return depth;
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
