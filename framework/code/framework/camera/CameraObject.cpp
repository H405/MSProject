//==============================================================================
//
// File   : CameraObject.cpp
// Brief  : カメラオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "CameraObject.h"
#include "CameraState.h"
#include "CameraStateDebug.h"
#include "../render/RenderMatrix.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
CameraObject::CameraObject( void ) : Camera()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
CameraObject::~CameraObject( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int CameraObject::Initialize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Camera::Initialize();
	if( result != 0 )
	{
		return result;
	}

#ifdef _DEVELOP
	// デバッグステートの生成
	pStateDebug_ = new CameraStateDebug();
	if( pStateDebug_ == nullptr )
	{
		return 1;
	}
	result = pStateDebug_->Initialize();
	if( result != 0 )
	{
		return result;
	}
#endif

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int CameraObject::Finalize( void )
{
#ifdef _DEVELOP
	// デバッグステートの開放
	delete pStateDebug_;
	pStateDebug_ = nullptr;
#endif

	// 基本クラスの処理
	int		result;		// 実行結果
	result = Camera::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int CameraObject::Reinitialize( void )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize();
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : CameraObject* pOut					: コピー先アドレス
//==============================================================================
int CameraObject::Copy( CameraObject* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Camera::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void CameraObject::Update( void )
{
	// ステートの実行
	if( pState_ != nullptr )
	{
		pState_->Update( this );
	}

	// 基本クラスの処理
	Camera::Update();
}

//==============================================================================
// Brief  : デバッグ設定
// Return : void								: なし
// Arg    : bool value							: 設定する値
//==============================================================================
void CameraObject::SetDebug( bool value )
{
#ifdef _DEVELOP
	// 現在の状態と同じなら終了
	if( value == isDebugMode_ )
	{
		return;
	}

	// デバッグステートの切り替え
	if( value )
	{
		pStateOriginal_ = pState_;
		pState_ = pStateDebug_;
	}
	else
	{
		pState_ = pStateOriginal_;
	}

	// 現在の状態を保存
	isDebugMode_ = value;
#endif
}

//==============================================================================
// Brief  : デバッグ切替
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void CameraObject::ToggleDebug( void )
{
#ifdef _DEVELOP
	// デバッグステートの切り替え
	if( !isDebugMode_ )
	{
		pStateOriginal_ = pState_;
		pState_ = pStateDebug_;
	}
	else
	{
		pState_ = pStateOriginal_;
	}

	// 現在の状態を保存
	isDebugMode_ = !isDebugMode_;
#endif
}

//==============================================================================
// Brief  : カメラベクトルの取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void CameraObject::GetVector( D3DXVECTOR3* pOut )
{
	// 値の返却
	*pOut = positionLookAt_ - positionCamera_;
}

//==============================================================================
// Brief  : 移動
// Return : void								: なし
// Arg    : const D3DXVECTOR3& vectorMove		: 移動ベクトル
//==============================================================================
void CameraObject::Move( const D3DXVECTOR3& vectorMove )
{
	// 回転軸算出
	D3DXVECTOR3	vectorCameraToLookAt;		// 視点から注視点のベクトル
	D3DXVECTOR3	vectorUp;					// 上方向ベクトル
	D3DXVECTOR3	vectorAxisUp;				// 上方向回転軸
	D3DXVECTOR3	vectorAxisFront;			// 前方向回転軸
	vectorCameraToLookAt = positionLookAt_ - positionCamera_;
	D3DXVec3Normalize( &vectorCameraToLookAt, &vectorCameraToLookAt );
	vectorUp.x = 0.0f;
	vectorUp.y = 1.0f;
	vectorUp.z = 0.0f;
	D3DXVec3Cross( &vectorAxisUp, &vectorUp, &vectorCameraToLookAt );
	D3DXVec3Normalize( &vectorAxisUp, &vectorAxisUp );
	D3DXVec3Cross( &vectorAxisFront, &vectorCameraToLookAt, &vectorAxisUp );
	D3DXVec3Normalize( &vectorAxisFront, &vectorAxisFront );

	// 上方向軸回転算出
	float	rotationCameraUp;		// 視点の上方向回転
	rotationCameraUp = -acosf( D3DXVec3Dot( &vectorUp, &vectorAxisFront ) );
	if( vectorCameraToLookAt.y < 0.0f )
	{
		rotationCameraUp *= -1;
	}

	// 上方向変換クォータニオンの作成
	D3DXQUATERNION	quaternionTranformformUp;		// 上方向のベクトルを変換するクォータニオン
	quaternionTranformformUp.x = 0.0f;
	quaternionTranformformUp.y = 0.0f;
	quaternionTranformformUp.z = 0.0f;
	quaternionTranformformUp.w = 1.0f;
	D3DXQuaternionRotationAxis( &quaternionTranformformUp, &vectorAxisUp, rotationCameraUp );

	// 前方向ベクトルの算出
	D3DXQUATERNION	quaternionConjugate;		// 共役クォータニオン
	D3DXQUATERNION	quaternionFront;			// 前方向のベクトルのクォータニオン
	quaternionConjugate = quaternionTranformformUp;
	quaternionConjugate.x *= -1;
	quaternionConjugate.y *= -1;
	quaternionConjugate.z *= -1;
	quaternionFront.x = 0.0f;
	quaternionFront.y = 0.0f;
	quaternionFront.z = 1.0f;
	quaternionFront.w = 0.0f;
	quaternionFront = quaternionConjugate * quaternionFront * quaternionTranformformUp;

	// 前方向軸回転算出
	D3DXVECTOR3	vectorFront;				// 前方向ベクトル
	float		rotationCameraFront;		// 視点の前方向回転
	vectorFront.x = quaternionFront.x;
	vectorFront.y = quaternionFront.y;
	vectorFront.z = quaternionFront.z;
	rotationCameraFront = acosf( D3DXVec3Dot( &vectorFront, &vectorCameraToLookAt ) );
	if( vectorFront.z * vectorCameraToLookAt.x - vectorFront.x * vectorCameraToLookAt.z < 0.0f )
	{
		rotationCameraFront *= -1;
	}

	// 前方向変換クォータニオンの作成
	D3DXQUATERNION	quaternionTranformformFront;		// 前方向のベクトルを変換するクォータニオン
	quaternionTranformformFront.x = 0.0f;
	quaternionTranformformFront.y = 0.0f;
	quaternionTranformformFront.z = 0.0f;
	quaternionTranformformFront.w = 1.0f;
	D3DXQuaternionRotationAxis( &quaternionTranformformFront, &vectorAxisFront, rotationCameraFront );

	// 移動変換クォータニオンの作成
	D3DXQUATERNION	quaternionTranformformMove;		// 移動方向のベクトルを変換するクォータニオン
	quaternionTranformformMove = quaternionTranformformUp * quaternionTranformformFront;
	quaternionConjugate = quaternionTranformformMove;
	quaternionConjugate.x *= -1;
	quaternionConjugate.y *= -1;
	quaternionConjugate.z *= -1;

	// 移動ベクトルの設定
	D3DXQUATERNION	quaternionMove;				// 移動方向のベクトルのクォータニオン
	D3DXVECTOR3		vectorMoveTransform;		// 返還後の移動ベクトル
	quaternionMove.x = vectorMove.x;
	quaternionMove.y = vectorMove.y;
	quaternionMove.z = vectorMove.z;
	quaternionMove.w = 0.0f;
	quaternionMove = quaternionConjugate * quaternionMove * quaternionTranformformMove;
	vectorMoveTransform.x = quaternionMove.x;
	vectorMoveTransform.y = quaternionMove.y;
	vectorMoveTransform.z = quaternionMove.z;

	// 移動
	SetPosition( positionCamera_ + vectorMoveTransform );
}

//==============================================================================
// Brief  : 値の設定
// Return : void								: なし
// Arg    : float viewField						: 視野角
// Arg    : int widthScreen						: スクリーン幅
// Arg    : int heightScreen					: スクリーン高さ
// Arg    : float clipNear						: 近くのクリップ面
// Arg    : float clipFar						: 遠くのクリップ面
// Arg    : const D3DXVECTOR3& positionCamera	: 視点
// Arg    : const D3DXVECTOR3& positionLookAt	: 注視点
// Arg    : const D3DXVECTOR3& vectorUp			: 上方向ベクトル
//==============================================================================
void CameraObject::Set( float viewField, int widthScreen, int heightScreen, float clipNear, float clipFar,
	const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp )
{
	// 値の設定
	Camera::Set( viewField, widthScreen, heightScreen, clipNear, clipFar, positionCamera, positionLookAt, vectorUp );
}

//==============================================================================
// Brief  : ビュー空間のZ値を取得
// Return : float								: Z値
// Arg    : const D3DXVECTOR3& position			: 座標
//==============================================================================
float CameraObject::GetViewZ( const D3DXVECTOR3& position )
{
	// ビュー座標に変換
	D3DXVECTOR3	positionView;		// ビュー空間での座標
	D3DXMATRIX	matrixView;			// ビュー変換行列
	pRenderMatrix_->GetMatrixView( &matrixView );
	D3DXVec3TransformCoord( &positionView, &position, &matrixView );

	// 値を返す
	return positionView.z / clipFar_;
}

//==============================================================================
// Brief  : プロジェクション空間のZ値を取得
// Return : float								: Z値
// Arg    : const D3DXVECTOR3& position			: 座標
//==============================================================================
float CameraObject::GetProjectionZ( const D3DXVECTOR3& position )
{
	// ビュー座標に変換
	D3DXVECTOR4	positionWorld;				// ワールド空間での座標
	D3DXVECTOR4	positionProjection;			// プロジェクション空間での座標
	D3DXMATRIX	matrixViewProjection;		// ビュープロジェクション変換行列
	pRenderMatrix_->GetMatrixViewProjection( &matrixViewProjection );
	positionWorld.x = position.x;
	positionWorld.y = position.y;
	positionWorld.z = position.z;
	positionWorld.w = 1.0f;
	D3DXVec4Transform( &positionProjection, &positionWorld, &matrixViewProjection );

	// 値を返す
	return positionProjection.z / positionProjection.w;
}

//==============================================================================
// Brief  : 座標の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void CameraObject::SetPosition( const D3DXVECTOR3& value )
{
	// 座標の設定
	SetPosition( value.x, value.y, value.z );
}

//==============================================================================
// Brief  : 座標の設定
// Return : void								: なし
// Arg    : float x								: 設定する値
// Arg    : float y								: 設定する値
// Arg    : float z								: 設定する値
//==============================================================================
void CameraObject::SetPosition( float x, float y, float z )
{
	// 視点の設定
	D3DXVECTOR3	vectorCameraToLookAt = positionLookAt_ - positionCamera_;		// 視点から注視点のベクトル
	positionCamera_.x = x;
	positionCamera_.y = y;
	positionCamera_.z = z;

	// 注視点の設定
	positionLookAt_ = positionCamera_ + vectorCameraToLookAt;
}

//==============================================================================
// Brief  : 座標の設定
// Return : void								: なし
// Arg    : float x								: 設定する値
//==============================================================================
void CameraObject::SetPositionX( float x )
{
	// 座標の設定
	SetPosition( x, positionCamera_.y, positionCamera_.z );
}

//==============================================================================
// Brief  : 座標の設定
// Return : void								: なし
// Arg    : float y								: 設定する値
//==============================================================================
void CameraObject::SetPositionY( float y )
{
	// 座標の設定
	SetPosition( positionCamera_.x, y, positionCamera_.z );
}

//==============================================================================
// Brief  : 座標の設定
// Return : void								: なし
// Arg    : float z								: 設定する値
//==============================================================================
void CameraObject::SetPositionZ( float z )
{
	// 座標の設定
	SetPosition( positionCamera_.x, positionCamera_.y, z );
}

//==============================================================================
// Brief  : 座標の加算
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 加算する値
//==============================================================================
void CameraObject::AddPosition( const D3DXVECTOR3& value )
{
	// 座標の加算
	SetPosition( positionCamera_.x + value.x, positionCamera_.y + value.y, positionCamera_.z + value.z );
}

//==============================================================================
// Brief  : 座標の加算
// Return : void								: なし
// Arg    : float x								: 加算する値
// Arg    : float y								: 加算する値
// Arg    : float z								: 加算する値
//==============================================================================
void CameraObject::AddPosition( float x, float y, float z )
{
	// 座標の加算
	SetPosition( positionCamera_.x + x, positionCamera_.y + y, positionCamera_.z + z );
}

//==============================================================================
// Brief  : 座標の加算
// Return : void								: なし
// Arg    : float x								: 加算する値
//==============================================================================
void CameraObject::AddPositionX( float x )
{
	// 座標の加算
	SetPosition( positionCamera_.x + x, positionCamera_.y, positionCamera_.z );
}

//==============================================================================
// Brief  : 座標の加算
// Return : void								: なし
// Arg    : float y								: 加算する値
//==============================================================================
void CameraObject::AddPositionY( float y )
{
	// 座標の加算
	SetPosition( positionCamera_.x, positionCamera_.y + y, positionCamera_.z );
}

//==============================================================================
// Brief  : 座標の加算
// Return : void								: なし
// Arg    : float z								: 加算する値
//==============================================================================
void CameraObject::AddPositionZ( float z )
{
	// 座標の加算
	SetPosition( positionCamera_.x, positionCamera_.y, positionCamera_.z + z );
}

//==============================================================================
// Brief  : 視点中心X軸回転の設定
// Return : void								: なし
// Arg    : float x								: 設定する値
//==============================================================================
void CameraObject::SetRotationCameraX( float x )
{
	// 視点から注視点までの距離算出
	D3DXVECTOR3	vectorCameraToLookAt;		// 視点から注視点のベクトル
	float		distanceCameraToLookAt;		// 視点から注視点の距離
	vectorCameraToLookAt = positionLookAt_ - positionCamera_;
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// 注視点の移動
	positionLookAt_.y = positionCamera_.y + sinf( x ) * distanceCameraToLookAt;
	positionLookAt_.z = positionCamera_.z + cosf( x ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : 視点中心Y軸回転の設定
// Return : void								: なし
// Arg    : float y								: 設定する値
//==============================================================================
void CameraObject::SetRotationCameraY( float y )
{
	// 視点から注視点までの距離算出
	D3DXVECTOR3	vectorCameraToLookAt;		// 視点から注視点のベクトル
	float		distanceCameraToLookAt;		// 視点から注視点の距離
	vectorCameraToLookAt = positionLookAt_ - positionCamera_;
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// 注視点の移動
	positionLookAt_.x = positionCamera_.x + sinf( y ) * distanceCameraToLookAt;
	positionLookAt_.z = positionCamera_.z + cosf( y ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : 視点中心X軸回転の加算
// Return : void								: なし
// Arg    : float x								: 加算する値
//==============================================================================
void CameraObject::AddRotationCameraX( float x )
{
	// 回転軸の設定
	D3DXVECTOR3	vectorCameraToLookAt;		// 視点から注視点のベクトル
	D3DXVECTOR3	vectorAxis;					// 回転軸
	vectorCameraToLookAt = positionLookAt_ - positionCamera_;
	vectorAxis.x = 0.0f;
	vectorAxis.y = 1.0f;
	vectorAxis.z = 0.0f;
	D3DXVec3Cross( &vectorAxis, &vectorCameraToLookAt, &vectorAxis );
	D3DXVec3Normalize( &vectorAxis, &vectorAxis );

	// 変換クォータニオンの作成
	D3DXQUATERNION	quaternionTranform;		// 注視点座標を変換するクォータニオン
	quaternionTranform.w = 1.0f;
	quaternionTranform.x = 0.0f;
	quaternionTranform.y = 0.0f;
	quaternionTranform.z = 0.0f;
	D3DXQuaternionRotationAxis( &quaternionTranform, &vectorAxis, x );
	quaternionTranform.x *= -1;
	quaternionTranform.y *= -1;
	quaternionTranform.z *= -1;

	// 座標クォータニオンの作成
	D3DXQUATERNION	quaternionLookAt;		// 注視点座標のクォータニオン
	quaternionLookAt.w = 0.0f;
	quaternionLookAt.x = vectorCameraToLookAt.x;
	quaternionLookAt.y = vectorCameraToLookAt.y;
	quaternionLookAt.z = vectorCameraToLookAt.z;

	// 座標の変換
	quaternionLookAt = quaternionTranform * quaternionLookAt;
	quaternionTranform.x *= -1;
	quaternionTranform.y *= -1;
	quaternionTranform.z *= -1;
	quaternionLookAt = quaternionLookAt * quaternionTranform;

	// 注視点の設定
	positionLookAt_.x = positionCamera_.x + quaternionLookAt.x;
	positionLookAt_.y = positionCamera_.y + quaternionLookAt.y;
	positionLookAt_.z = positionCamera_.z + quaternionLookAt.z;
}

//==============================================================================
// Brief  : 視点中心Y軸回転の加算
// Return : void								: なし
// Arg    : float y								: 加算する値
//==============================================================================
void CameraObject::AddRotationCameraY( float y )
{
	// 回転軸の設定
	D3DXVECTOR3	vectorAxis;		// 回転軸
	vectorAxis.x = 0.0f;
	vectorAxis.y = 1.0f;
	vectorAxis.z = 0.0f;
	
	// 変換クォータニオンの作成
	D3DXQUATERNION	quaternionTranform;		// 注視点座標を変換するクォータニオン
	quaternionTranform.w = 1.0f;
	quaternionTranform.x = 0.0f;
	quaternionTranform.y = 0.0f;
	quaternionTranform.z = 0.0f;
	D3DXQuaternionRotationAxis( &quaternionTranform, &vectorAxis, y );
	quaternionTranform.x *= -1;
	quaternionTranform.y *= -1;
	quaternionTranform.z *= -1;
	
	// 座標クォータニオンの作成
	D3DXVECTOR3		vectorCameraToLookAt;	// 視点から注視点のベクトル
	D3DXQUATERNION	quaternionLookAt;		// 注視点座標のクォータニオン
	vectorCameraToLookAt = positionLookAt_ - positionCamera_;
	quaternionLookAt.w = 0.0f;
	quaternionLookAt.x = vectorCameraToLookAt.x;
	quaternionLookAt.y = vectorCameraToLookAt.y;
	quaternionLookAt.z = vectorCameraToLookAt.z;
	
	// 座標の変換
	quaternionLookAt = quaternionTranform * quaternionLookAt;
	quaternionTranform.x *= -1;
	quaternionTranform.y *= -1;
	quaternionTranform.z *= -1;
	quaternionLookAt = quaternionLookAt * quaternionTranform;
	
	// 注視点の設定
	positionLookAt_.x = positionCamera_.x + quaternionLookAt.x;
	positionLookAt_.y = positionCamera_.y + quaternionLookAt.y;
	positionLookAt_.z = positionCamera_.z + quaternionLookAt.z;
}

//==============================================================================
// Brief  : 注視点中心X軸回転の設定
// Return : void								: なし
// Arg    : float x								: 設定する値
//==============================================================================
void CameraObject::SetRotationLookAtX( float x )
{
	// 視点から注視点までの距離算出
	D3DXVECTOR3	vectorCameraToLookAt;		// 視点から注視点のベクトル
	float		distanceCameraToLookAt;		// 視点から注視点の距離
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// 視点の移動
	positionCamera_.y = positionLookAt_.y + sinf( x + D3DX_PI ) * distanceCameraToLookAt;
	positionCamera_.z = positionLookAt_.z + cosf( x + D3DX_PI ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : 注視点中心Y軸回転の設定
// Return : void								: なし
// Arg    : float y								: 設定する値
//==============================================================================
void CameraObject::SetRotationLookAtY( float y )
{
	// 視点から注視点までの距離算出
	D3DXVECTOR3	vectorCameraToLookAt;		// 視点から注視点のベクトル
	float		distanceCameraToLookAt;		// 視点から注視点の距離
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// 視点の移動
	positionCamera_.x = positionLookAt_.x + sinf( y + D3DX_PI ) * distanceCameraToLookAt;
	positionCamera_.z = positionLookAt_.z + cosf( y + D3DX_PI ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : 注視点中心X軸回転の加算
// Return : void								: なし
// Arg    : float x								: 加算する値
//==============================================================================
void CameraObject::AddRotationLookAtX( float x )
{
	// 現在の角度算出
	float		rotationCurrentX;			// 現在の角度
	D3DXVECTOR3	vectorCameraToLookAt;		// 視点から注視点のベクトル
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	rotationCurrentX = atan2f( vectorCameraToLookAt.y, vectorCameraToLookAt.z );


	// 視点から注視点までの距離算出
	float	distanceCameraToLookAt;		// 視点から注視点の距離
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// 視点の移動
	positionCamera_.y = positionLookAt_.y + sinf( rotationCurrentX + x ) * distanceCameraToLookAt;
	positionCamera_.z = positionLookAt_.z + cosf( rotationCurrentX + x ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : 注視点中心Y軸回転の加算
// Return : void								: なし
// Arg    : float y								: 加算する値
//==============================================================================
void CameraObject::AddRotationLookAtY( float y )
{
	// 現在の角度算出
	float		rotationCurrentY;			// 現在の角度
	D3DXVECTOR3	vectorCameraToLookAt;		// 視点から注視点のベクトル
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	rotationCurrentY = atan2f( vectorCameraToLookAt.x, vectorCameraToLookAt.z );

	// 視点から注視点までの距離算出
	float		distanceCameraToLookAt;		// 視点から注視点の距離
	distanceCameraToLookAt = D3DXVec3Length( &vectorCameraToLookAt );

	// 視点の移動
	positionCamera_.x = positionLookAt_.x + sinf( rotationCurrentY + y ) * distanceCameraToLookAt;
	positionCamera_.z = positionLookAt_.z + cosf( rotationCurrentY + y ) * distanceCameraToLookAt;
}

//==============================================================================
// Brief  : X軸回転の取得
// Return : float								: 取得する値
// Arg    : void								: なし
//==============================================================================
float CameraObject::GetRotationX( void )
{
	// 現在の角度算出
	D3DXVECTOR3	vectorCameraToLookAt;		// 視点から注視点のベクトル
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	return atan2f( vectorCameraToLookAt.y, vectorCameraToLookAt.z );
}

//==============================================================================
// Brief  : Y軸回転の取得
// Return : float								: 取得する値
// Arg    : void								: なし
//==============================================================================
float CameraObject::GetRotationY( void )
{
	// 現在の角度算出
	D3DXVECTOR3	vectorCameraToLookAt;		// 視点から注視点のベクトル
	vectorCameraToLookAt = positionCamera_ - positionLookAt_;
	return atan2f( vectorCameraToLookAt.x, vectorCameraToLookAt.z );
}

//==============================================================================
// Brief  : ステートの設定
// Return : void								: なし
// Arg    : CameraState* pValue					: 設定する値
//==============================================================================
void CameraObject::SetState( CameraState* pValue )
{
	// 値の設定
#ifdef _DEVELOP
	if( isDebugMode_ )
	{
		pStateOriginal_ = pValue;
	}
	else
	{
		pState_ = pValue;
	}
#else
	pState_ = pValue;
#endif
}

//==============================================================================
// Brief  : ステートの取得
// Return : CameraState*						: 返却する値
// Arg    : void								: なし
//==============================================================================
CameraState* CameraObject::GetState( void ) const
{
	// 値の返却
	return pState_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void CameraObject::InitializeSelf( void )
{
	// メンバ変数の初期化
	pState_ = nullptr;
#ifdef _DEVELOP
	pStateOriginal_ = nullptr;
	pStateDebug_ = nullptr;
	isDebugMode_ = false;
#endif
}
