//==============================================================================
// 
// File   : Shadow.fx
// Brief  : 影エフェクト
// Author : Taiga Shirakawa
// Date   : 2015/11/24 tsu : Taiga Shirakawa : create
// 
//==============================================================================

//******************************************************************************
// 変数宣言
//******************************************************************************
float2		offsetTexel_;					// テクセルオフセット

float4x4	matrixProjectionInverse_;		// プロジェクション変換逆行列
float4x4	matrixViewInverse_;				// ビュー変換逆行列
texture		textureDepth_;					// 深度テクスチャ

float3		positionLookAtLight_;			// 平行光源の注視点

float4x4	matrixTransformLightNear_;		// 平行光源(近)の変換行列
float4x4	matrixViewLightNear_;			// 平行光源(近)のビュー変換行列
texture		textureDepthLightNear_;			// 平行光源(近)の深度テクスチャ
float		clipFarLightNear_;				// 平行光源(近)のファークリップ面

float4x4	matrixTransformLightFar_;		// 平行光源(遠)の変換行列
float4x4	matrixViewLightFar_;			// 平行光源(遠)のビュー変換行列
texture		textureDepthLightFar_;			// 平行光源(遠)の深度テクスチャ
float		clipFarLightFar_;				// 平行光源(遠)のファークリップ面

float4x4	matrixViewLightPoint0_;			// 点光源0のビュー変換行列
texture		textureDepthLightPoint0_;		// 点光源0の深度テクスチャ
float		clipFarLightPoint0_;			// 点光源0のファークリップ面
float3		attenuationLightPoint0_;		// 点光源0の減衰率

float4x4	matrixViewLightPoint1_;			// 点光源1のビュー変換行列
texture		textureDepthLightPoint1_;		// 点光源1の深度テクスチャ
float		clipFarLightPoint1_;			// 点光源1のファークリップ面
float3		attenuationLightPoint1_;		// 点光源1の減衰率

//******************************************************************************
// サンプリング
//******************************************************************************
sampler samplerTextureDepth = sampler_state
{
	Texture = < textureDepth_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthLightNear = sampler_state
{
	Texture = < textureDepthLightNear_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthLightFar = sampler_state
{
	Texture = < textureDepthLightFar_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthLightPoint0 = sampler_state
{
	Texture = < textureDepthLightPoint0_ >;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = None;
	AddressU  = Clamp;
	AddressV  = Clamp;
};

sampler samplerTextureDepthLightPoint1 = sampler_state
{
	Texture = < textureDepthLightPoint1_ >;
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

//==============================================================================
// Brief  : 平行光源(近)の影を計算
// Return : float							: 影の濃さ
// Arg    : float3 positionWorld			: ワールド座標
//==============================================================================
float CalculateShadowNear( float3 positionWorld )
{
	// テクスチャの座標を求める
	float4	positionLightNear = mul( float4( positionWorld, 1.0f ), matrixTransformLightNear_ );
	float2	positionTextureLightNear = positionLightNear.xy / positionLightNear.w;
	positionTextureLightNear = float2( 1.0f + positionTextureLightNear.x, 1.0f - positionTextureLightNear.y );
	positionTextureLightNear *= 0.5f;

	// 深度を取得
	float	depthLightNear = clipFarLightNear_ - tex2D( samplerTextureDepthLightNear, positionTextureLightNear ).r;
	float	depth = mul( float4( positionWorld, 1.0f ), matrixViewLightNear_ ).z;

	// 色を返す
	float	shadow;
	if( depth - depthLightNear > 17.0f )
	{
		shadow = 0.5f;
	}
	else
	{
		shadow = 1.0f;
	}
	return shadow;
}

//==============================================================================
// Brief  : 平行光源(遠)の影を計算
// Return : float							: 影の濃さ
// Arg    : float3 positionWorld			: ワールド座標
//==============================================================================
float CalculateShadowFar( float3 positionWorld )
{
	// テクスチャの座標を求める
	float4	positionLightFar = mul( float4( positionWorld, 1.0f ), matrixTransformLightFar_ );
	float2	positionTextureLightFar = positionLightFar.xy / positionLightFar.w;
	positionTextureLightFar = float2( 1.0f + positionTextureLightFar.x, 1.0f - positionTextureLightFar.y );
	positionTextureLightFar *= 0.5f;

	// 深度を取得
	float	depthLightFar = clipFarLightFar_ - tex2D( samplerTextureDepthLightFar, positionTextureLightFar ).r;
	float	depth = mul( float4( positionWorld, 1.0f ), matrixViewLightFar_ ).z;

	// 色を返す
	float	shadow;
	if( depth - depthLightFar > 50.0f )
	{
		shadow = 0.5f;
	}
	else
	{
		shadow = 1.0f;
	}
	return shadow;
}

//==============================================================================
// Brief  : 点光源0の影を計算
// Return : float							: 影の濃さ
// Arg    : float3 positionWorld			: ワールド座標
//==============================================================================
float CalculateShadowPoint0( float3 positionWorld )
{
	// 必要な情報を求める
	float4	positionView = mul( float4( positionWorld, 1.0f ), matrixViewLightPoint0_ );
	float	distanceProjection = positionView.x * positionView.x + positionView.y * positionView.y;
	float	distanceToVertex = length( positionView );

	// テクスチャの座標を求める
	float2	positionTextureLightPoint0 = positionView * (distanceToVertex - positionView.z) / distanceProjection;
	positionTextureLightPoint0 = float2( 1.0f + positionTextureLightPoint0.x, 1.0f - positionTextureLightPoint0.y );
	positionTextureLightPoint0 *= 0.5f;

	// 深度を取得
	float	depthLightPoint0 = clipFarLightPoint0_ - tex2D( samplerTextureDepthLightPoint0, positionTextureLightPoint0 ).r;

	// 色を返す
	float	shadow;
	if( distanceToVertex - depthLightPoint0 > 25.0f )
	{
		// 減衰率を求める
		float	attenuation = attenuationLightPoint0_.x
			+ attenuationLightPoint0_.y * distanceToVertex
			+ attenuationLightPoint0_.z * distanceToVertex * distanceToVertex;

		// 影の濃さを決定
		shadow = 1.0f - 0.7f / (1.0f + attenuation);
	}
	else
	{
		shadow = 1.0f;
	}
	return shadow;
}

//==============================================================================
// Brief  : 点光源1の影を計算
// Return : float							: 影の濃さ
// Arg    : float3 positionWorld			: ワールド座標
//==============================================================================
float CalculateShadowPoint1( float3 positionWorld )
{
	// 必要な情報を求める
	float4	positionView = mul( float4( positionWorld, 1.0f ), matrixViewLightPoint1_ );
	float	distanceProjection = positionView.x * positionView.x + positionView.y * positionView.y;
	float	distanceToVertex = length( positionView );

	// テクスチャの座標を求める
	float2	positionTextureLightPoint1 = positionView * (distanceToVertex - positionView.z) / distanceProjection;
	positionTextureLightPoint1 = float2( 1.0f + positionTextureLightPoint1.x, 1.0f - positionTextureLightPoint1.y );
	positionTextureLightPoint1 *= 0.5f;

	// 深度を取得
	float	depthLightPoint1 = clipFarLightPoint1_ - tex2D( samplerTextureDepthLightPoint1, positionTextureLightPoint1 ).r;

	// 色を返す
	float	shadow;
	if( distanceToVertex - depthLightPoint1 > 25.0f )
	{
		// 減衰率を求める
		float	attenuation = attenuationLightPoint1_.x
			+ attenuationLightPoint1_.y * distanceToVertex
			+ attenuationLightPoint1_.z * distanceToVertex * distanceToVertex;

		// 影の濃さを決定
		shadow = 1.0f - 0.7f / (1.0f + attenuation);
	}
	else
	{
		shadow = 1.0f;
	}
	return shadow;
}

//==============================================================================
// Brief  : 頂点変換
// Return : VertexOutput					: 頂点シェーダ出力
// Arg    : float4 positionLocal			: ローカル座標
// Arg    : float2 positionTexture			: テクスチャ座標
//==============================================================================
VertexOutput TransformVertex( float3 positionLocal : POSITION, float2 textureCoord : TEXCOORD0 )
{
	// 頂点の変換
	VertexOutput	output;		// 出力
	output.position_.xyz = positionLocal;
	output.position_.w = 1.0f;

	// 値を格納
	output.textureCoord_ = textureCoord + offsetTexel_;

	// 頂点出力を返す
	return output;
}

//==============================================================================
// Brief  : ピクセル描画
// Return : float4							: 深度
// Arg    : VertexOutput					: 頂点シェーダ出力
//==============================================================================
float4 DrawPixel( VertexOutput vertex ) : COLOR0
{
	// ワールド座標を求める
	float	dataDepth = tex2D( samplerTextureDepth, vertex.textureCoord_ ).r;
	float2	positionTexture = vertex.textureCoord_ * 2.0f - 1.0f;
	float3	positionProjection = mul( float4( positionTexture.x, -positionTexture.y, 1.0f, 1.0f ), matrixProjectionInverse_ ).xyz;
	float3	positionView = float3( positionProjection.xy, 1.0f ) * dataDepth;
	float3	positionWorld = mul( float4( positionView, 1.0f ), matrixViewInverse_ );

	// 平行光源の影を決定
	float	shadow;
	if( distance( positionWorld, positionLookAtLight_ ) < 4000.0f )
	{
		shadow = CalculateShadowNear( positionWorld );
	}
	else
	{
		shadow = CalculateShadowFar( positionWorld );
	}

	// 点光源の影を決定
	shadow *= CalculateShadowPoint0( positionWorld );
	shadow *= CalculateShadowPoint1( positionWorld );

	// 色を返す
	float4	color;
	color.gba = 0.0f;
	color.r = shadow;
	return color;
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
