//==============================================================================
//
// File   : ObjectSkinMesh.cpp
// Brief  : スキンメッシュオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectSkinMesh.h"
#include "../graphic/graphic/GraphicSkinMesh.h"
#include "../framework/resource/Model.h"
#include "../framework/resource/Motion.h"

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
ObjectSkinMesh::ObjectSkinMesh( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectSkinMesh::~ObjectSkinMesh( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
// Arg    : int countMotion						: モーション数
//==============================================================================
int ObjectSkinMesh::Initialize( int priority, int countMotion )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	countMotion_ = countMotion;
	ppTableMotion_ = new Motion*[ countMotion ];
	for( int counterItem = 0; counterItem < countMotion; ++counterItem )
	{
		ppTableMotion_[ counterItem ] = nullptr;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ObjectSkinMesh::Finalize( void )
{
	// 格納領域の開放
	delete[] ppTableMotion_;
	ppTableMotion_ = nullptr;

	delete[] pMatrixBoneCurrent_;
	pMatrixBoneCurrent_ = nullptr;

	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Finalize();
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
// Arg    : int priority						: 更新優先度
// Arg    : int countMotion						: モーション数
//==============================================================================
int ObjectSkinMesh::Reinitialize( int priority, int countMotion )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, countMotion );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ObjectSkinMesh* pOut				: コピー先アドレス
//==============================================================================
int ObjectSkinMesh::Copy( ObjectSkinMesh* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Copy( pOut );
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
void ObjectSkinMesh::Update( void )
{
	// ボーン変換行列の更新
	unsigned long	countBone;				// ボーン数
	D3DXMATRIX		matrixBoneMotion;		// モーションのボーン変換行列
	countBone = pModel_->GetCountBone();
	for( unsigned int counterBone = 0; counterBone < countBone; ++counterBone )
	{
		pModel_->GetMatrixBone( counterBone, &pMatrixBoneCurrent_[ counterBone ] );
	}
	if( indexMotionNext_ >= 0 )
	{
		// 合成割合を求める
		float	proportion;		// 合成割合
		if( indexFrame_ <= indexFrameBeginBlend_ || indexMotionNext_ < 0 )
		{
			proportion = 0.0f;
		}
		else
		{
			proportion = static_cast< float >( indexFrame_ - indexFrameBeginBlend_ ) / countFrameBlend_;
		}

		// ボーン変換行列を計算
		for( unsigned int counterBone = 0; counterBone < countBone; ++counterBone )
		{
			ppTableMotion_[ indexMotionCurrent_ ]->GetMatrixBone( indexFrame_, counterBone, &matrixBoneMotion );
			if( proportion > 0.0f && indexMotionNext_ >= 0 )
			{
				D3DXMATRIX	matrixBoneNext;		// 次のモーションのボーン変換行列
				ppTableMotion_[ indexMotionNext_ ]->GetMatrixBone( indexFrame_, counterBone, &matrixBoneNext );
				matrixBoneMotion *= 1.0f - proportion;
				matrixBoneMotion += proportion * matrixBoneNext;
			}
		}
	}
	else
	{
		for( unsigned int counterBone = 0; counterBone < countBone; ++counterBone )
		{
			ppTableMotion_[ indexMotionCurrent_ ]->GetMatrixBone( indexFrame_, counterBone, &matrixBoneMotion );
			D3DXMatrixMultiply( &pMatrixBoneCurrent_[ counterBone ], &pMatrixBoneCurrent_[ counterBone ], &matrixBoneMotion );
		}
	}

	// フレームを進める
	if( countMotion_ > 0 )
	{
		++indexFrame_;
		if( static_cast< unsigned int >( indexFrame_ ) >= ppTableMotion_[ indexMotionCurrent_ ]->GetCountFrame() )
		{
			indexFrame_ = 0;
			if( indexMotionNext_ >= 0 )
			{
				indexMotionCurrent_ = indexMotionNext_;
			}
		}
	}

	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : 描画クラスの生成
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : Model* pModel						: モデル
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
// Arg    : Effect* pEffectShadow				: 影描画エフェクト
// Arg    : Effect* pEffectParaboloid			: 放物変換描画エフェクト
//==============================================================================
int ObjectSkinMesh::CreateGraphic( int priority, Model* pModel, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow, Effect* pEffectParaboloid )
{
	// メンバ変数の設定
	pModel_ = pModel;

	// ボーン変換行列の格納領域を確保
	int		countBone;		// ボーン数
	countBone = pModel->GetCountBone();
	pMatrixBoneCurrent_ = new D3DXMATRIX[ countBone ];
	for( int counterItem = 0; counterItem < countBone; ++counterItem )
	{
		D3DXMatrixIdentity( &pMatrixBoneCurrent_[ counterItem ] );
	}

	// グラフィックの生成
	int		result;		// 実行結果
	pGraphic_ = new GraphicSkinMesh();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, pEffectReflect, pEffectShadow, pEffectParaboloid,
		pModel, countBone, pMatrixBoneCurrent_ );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// 値の返却
	return 0;
}

//==============================================================================
// Brief  : 次のモーションを設定
// Return : void								: なし
// Arg    : int indexMotion						: 次のモーション番号
// Arg    : int timeBeginBlend					: ブレンド開始時間
// Arg    : int timeBlend						: ブレンド時間
//==============================================================================
void ObjectSkinMesh::SetNextMotion( int indexMotion, int timeBeginBlend, int timeBlend )
{
	// メンバ変数の設定
	indexMotionNext_ = indexMotion;
	indexFrameBeginBlend_ = timeBeginBlend;
	countFrameBlend_ = timeBlend;

	// ブレンド開始時間の修正
	int		timeMotionCurrent;		// 現在のモーションの時間
	timeMotionCurrent = ppTableMotion_[ indexMotionCurrent_ ]->GetCountFrame();
	if( timeBeginBlend == -1 )
	{
		indexFrameBeginBlend_ = timeMotionCurrent - timeBlend;
	}
	if( timeBeginBlend < 0 )
	{
		timeBeginBlend = 0;
	}

	// ブレンド時間の修正
	if( timeBeginBlend + timeBlend > timeMotionCurrent )
	{
		timeBlend = timeMotionCurrent - timeBeginBlend;
	}
}

//==============================================================================
// Brief  : ブレンド中か判定
// Return : bool								: ブレンド中かどうか
// Arg    : void								: なし
//==============================================================================
bool ObjectSkinMesh::IsBlending( void )
{
	// 値の返却
	return (indexFrame_ >= indexFrameBeginBlend_ ? true : false);
}

//==============================================================================
// Brief  : モーションテーブルの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : Motion* pValue						: 設定する値
//==============================================================================
void ObjectSkinMesh::SetTableMotion( int index, Motion* pValue )
{
	// 値の設定
	ppTableMotion_[ index ] = pValue;
}

//==============================================================================
// Brief  : モーションテーブルの取得
// Return : Motion*								: 返却する値
// Arg    : int index							: 設定する番号
//==============================================================================
Motion* ObjectSkinMesh::GetTableMotion( int index ) const
{
	// 値の返却
	return ppTableMotion_[ index ];
}

//==============================================================================
// Brief  : 現在のモーション番号の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int ObjectSkinMesh::GetIndexMotionCurrent( void ) const
{
	// 値の返却
	return indexMotionCurrent_;
}

//==============================================================================
// Brief  : 次のモーション番号の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int ObjectSkinMesh::GetIndexMotionNext( void ) const
{
	// 値の返却
	return indexMotionNext_;
}

//==============================================================================
// Brief  : フレーム番号の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int ObjectSkinMesh::GetIndexFrame( void ) const
{
	// 値の返却
	return indexFrame_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectSkinMesh::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
	pModel_ = nullptr;
	ppTableMotion_ = nullptr;
	pMatrixBoneCurrent_ = nullptr;
	countMotion_ = 0;
	indexMotionCurrent_ = 0;
	indexMotionNext_ = -1;
	indexFrame_ = 0;
	indexFrameBeginBlend_ = 0;
	countFrameBlend_ = 0;
}
