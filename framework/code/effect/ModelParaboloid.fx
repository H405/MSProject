//==============================================================================
// 
// File   : ModelParaboloid.fx
// Brief  : 放物面変換モデルエフェクト
// Author : Taiga Shirakawa
// Date   : 2015/12/08 tsu : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float4x4	matrixWorldView_;		// ワールドビュー変換行列
float2		clipCamera_;			// カメラのクリップ値

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
	float	depth_		: TEXCOORD0;		// 深度
};

//==============================================================================
// Brief  : 頂点変換
// Return : VertexOutput					: 頂点シェーダ出力
// Arg    : float4 positionLocal			: ローカル座標
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION )
{
	// ワールドビュー変換
	float4	positionView = mul( float4( positionLocal, 1.0f ), matrixWorldView_ );

	// 必要な値を計算
	float	distanceProjection = positionView.x * positionView.x + positionView.y * positionView.y;
	float	distanceToVertex = length( positionView );

	// 頂点の変換
	VertexOutput	output;		// 頂点シェーダ出力
	output.position_.x = distanceToVertex * positionView.x * (distanceToVertex - positionView.z) / distanceProjection;
	output.position_.y = distanceToVertex * positionView.y * (distanceToVertex - positionView.z) / distanceProjection;
	output.position_.z = clipCamera_.y * (distanceToVertex - clipCamera_.x) / (clipCamera_.y - clipCamera_.x);
	output.position_.w = distanceToVertex;

	// 深度の格納
	output.depth_ = distanceToVertex;

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
	depth.r = clipCamera_.y - vertex.depth_;
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
