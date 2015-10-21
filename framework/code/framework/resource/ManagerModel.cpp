//==============================================================================
//
// File   : ManagerModel.cpp
// Brief  : モデル管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerModel.h"
#include "ManagerTexture.h"
#include "ModelX.h"
#include "Texture.h"
#include "../graphic/Material.h"
#include "../vertex/Vertex.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// テンプレート宣言
//******************************************************************************
template class ManagerModel< class Model >;

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerModel< TypeItem >::ManagerModel( void ) : ManagerResource()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerModel< TypeItem >::~ManagerModel( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : TCHAR* pDirectory					: 基準ディレクトリ
// Arg    : int maximumItem						: 最大要素数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : ManagerTexture< Texture >* pTexture	: テクスチャ管理クラス
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Initialize( TCHAR* pDirectory, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerResource::Initialize( pDirectory, maximumItem );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	pDevice_ = pDevice;
	pTexture_ = pTexture;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerResource::Finalize();
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
// Arg    : TCHAR* pDirectory					: 基準ディレクトリ
// Arg    : int maximumItem						: 最大要素数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : ManagerTexture< Texture >* pTexture	: テクスチャ管理クラス
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Reinitialize( TCHAR* pDirectory, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDirectory, maximumItem, pDevice, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ManagerModel* pOut					: コピー先アドレス
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Copy( ManagerModel* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerResource::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
void ManagerModel< TypeItem >::InitializeSelf( void )
{
	// メンバ変数の初期化
	pDevice_ = nullptr;
	pTexture_ = nullptr;
}

//==============================================================================
// Brief  : リソースの読み込み
// Return : int									: 実行結果
// Arg    : TCHAR* pPath						: ファイルパス
// Arg    : int index							: 格納要素番号
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::LoadResource( TCHAR* pPath, int index )
{
	// モデル生成
	DWORD				countMaterial;				// マテリアル情報の数
	ID3DXMesh*			pMesh = nullptr;			// メッシュ情報へのアドレス
	ID3DXBuffer*		pMaterial = nullptr;		// マテリアル情報へのアドレス
	HRESULT				result;						// 実行結果
	result = D3DXLoadMeshFromX( pPath, D3DXMESH_SYSTEMMEM, pDevice_, NULL, &pMaterial, NULL, &countMaterial, &pMesh );
	if( result != 0 )
	{
		TCHAR	pStringError[ 512 ] = {};		// エラー文字列
		sprintf_s( pStringError, 512, _T( "ファイル\"%s\"が見つかりません" ), pPath );
		MessageBox( NULL, pStringError, _T( "エラー" ), MB_OK );
		return 1;
	}

	// モデルの生成
	ModelX*	pModel = nullptr;		// モデル
	pModel= new ModelX();
	if( pModel == nullptr )
	{
		return 1;
	}
	result = pModel->Initialize( pDevice_, Vertex::ELEMENT_SET_SIMPLE, countMaterial, countMaterial, pMesh );
	if( result != 0 )
	{
		return result;
	}
	pBufferItem_[ index ].pItem_ = pModel;

	// テクスチャの設定
	D3DXMATERIAL*	pMaterialPointer = nullptr;		// マテリアル情報の先頭アドレス
	Texture*		pTexture = nullptr;				// テクスチャ
	pMaterialPointer = static_cast< D3DXMATERIAL* >( pMaterial->GetBufferPointer() );
	for( unsigned long counterMaterial = 0; counterMaterial < countMaterial; ++counterMaterial )
	{
		if( pMaterialPointer[ counterMaterial ].pTextureFilename == nullptr )
		{
			continue;
		}
		pTexture = nullptr;
		pTexture = pTexture_->Get( pMaterialPointer[ counterMaterial ].pTextureFilename );
		if( pTexture != nullptr )
		{
			pBufferItem_[ index ].pItem_->SetTexture( counterMaterial, pTexture->pTexture_ );
		}
	}

	// マテリアルの設定
	Material		materialSet;		// 設定するマテリアル
	D3DMATERIAL9	materialGet;		// 取得したマテリアル
	for( unsigned long counterMaterial = 0; counterMaterial < countMaterial; ++counterMaterial )
	{
		materialGet = pMaterialPointer[ counterMaterial ].MatD3D;
		materialSet.diffuse_ = materialGet.Diffuse;
		materialSet.specular_ = materialGet.Specular;
		materialSet.ambient_ = materialGet.Ambient;
		materialSet.emmisive_ = materialGet.Emissive;
		materialSet.power_ = materialGet.Power;
		materialSet.reflection_ = 1.0f;
		materialSet.refractive_ = 0.1f;
		pBufferItem_[ index ].pItem_->SetMaterial( counterMaterial, materialSet );
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : リソースの開放
// Return : void								: なし
// Arg    : int index							: 格納要素番号
//==============================================================================
template< class TypeItem >
void ManagerModel< TypeItem >::ReleaseResource( int index )
{
	// モデルの開放
	delete pBufferItem_[ index ].pItem_;
	pBufferItem_[ index ].pItem_ = nullptr;
}
