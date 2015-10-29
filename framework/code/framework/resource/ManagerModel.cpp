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
#include "../system/File.h"
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
// Arg    : TCHAR* pDirectoryTexture			: テクスチャ基準ディレクトリ
// Arg    : int maximumItem						: 最大要素数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : ManagerTexture< Texture >* pTexture	: テクスチャ管理クラス
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Initialize( TCHAR* pDirectory, TCHAR* pDirectoryTexture, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture )
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

	// 文字列の格納領域を確保
	pDirectoryTexture_ = new TCHAR[ _MAX_PATH ];
	if( pDirectoryTexture_ == nullptr )
	{
		return 1;
	}
	memset( pDirectoryTexture_, 0x00, sizeof( TCHAR ) * _MAX_PATH );
	_tcscpy_s( pDirectoryTexture_, _MAX_PATH, pDirectoryTexture );

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
	// 格納領域の開放
	delete[] pDirectoryTexture_;
	pDirectoryTexture_ = nullptr;

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
// Arg    : TCHAR* pDirectoryTexture			: テクスチャ基準ディレクトリ
// Arg    : int maximumItem						: 最大要素数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : ManagerTexture< Texture >* pTexture	: テクスチャ管理クラス
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Reinitialize( TCHAR* pDirectory, TCHAR* pDirectoryTexture, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDirectory, pDirectoryTexture, maximumItem, pDevice, pTexture );
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
	pDirectoryTexture_ = nullptr;
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
	// Xファイルモデルの読み込み
	if( pPath[ _tcslen( pPath ) - 1 ] == _T( 'x' ) )
	{
		return LoadModelX( pPath, index );
	}

	// 変換済みモデルの読み込み
	return LoadModelConvert( pPath, index );
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

//==============================================================================
// Brief  : Xファイルの読み込み
// Return : int									: 実行結果
// Arg    : TCHAR* pPath						: ファイルパス
// Arg    : int index							: 格納要素番号
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::LoadModelX( TCHAR* pPath, int index )
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
	TCHAR			pNameTexture[ _MAX_PATH ];		// テクスチャファイル名
	pMaterialPointer = static_cast< D3DXMATERIAL* >( pMaterial->GetBufferPointer() );
	for( unsigned long counterMaterial = 0; counterMaterial < countMaterial; ++counterMaterial )
	{
		// テクスチャがあるか確認
		if( pMaterialPointer[ counterMaterial ].pTextureFilename == nullptr )
		{
			continue;
		}

		// テクスチャ名の作成
		_tcscpy_s( pNameTexture, _MAX_PATH, pDirectoryTexture_ );
		_tcscat_s( pNameTexture, _MAX_PATH, pMaterialPointer[ counterMaterial ].pTextureFilename );

		// テクスチャの読み込み
		pTexture = nullptr;
		pTexture = pTexture_->Get( pNameTexture );
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
// Brief  : 変換済みモデルファイルの読み込み
// Return : int									: 実行結果
// Arg    : TCHAR* pPath						: ファイルパス
// Arg    : int index							: 格納要素番号
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::LoadModelConvert( TCHAR* pPath, int index )
{
#if 0
	// ファイルの読み込み
	File	file;
	file.Initialize( pPath );

	// ファイルの種類を確認
	if( !file.IsType( _T( "SKN3" ) ) )
	{
		TCHAR	aStrError[ 256 ];		// エラーメッセージ
		sprintf_s( &aStrError[ 0 ], 256, _T( "ファイル\"%s\"が見つかりません。" ), pPath );
		MessageBox( nullptr, &aStrError[ 0 ], _T( "エラー" ), MB_OK );
		return 1;
	}

	// テクスチャ名の読み込み
	unsigned long	numTexture = 0;				// テクスチャ数
	unsigned long	sizeBufferTexture = 0;		// テクスチャバッファサイズ
	char*			pBufferTexture = nullptr;	// テクスチャバッファ
	file.Read( &numTexture );
	file.Read( &sizeBufferTexture );
	if( sizeBufferTexture > 0 )
	{
		pBufferTexture = new char[ sizeBufferTexture ];
		if( pBufferTexture == nullptr )
		{
			return 1;
		}
		file.Read( &pBufferTexture[ 0 ], sizeBufferTexture );
	}

	// テクスチャの読み込み
	int*	pIndexTexture = nullptr;	// テクスチャ番号
	if( sizeBufferTexture > 0 )
	{
		unsigned long	indexTextureCurrent = 0;		// 現在のテクスチャ番号
		TCHAR			aNameTexture[ _MAX_PATH ];	// テクスチャファイル名

		// テクスチャ番号格納領域の確保
		pIndexTexture = new int[ sizeBufferTexture ];
		if( pIndexTexture == nullptr )
		{
			return 1;
		}

		// 読み込み
		pIndexTexture[ 0 ] = pTexture->Load( &aNameTexture[ 0 ] );
		indexTextureCurrent += 1;
		for( unsigned long cntIndex = 0; cntIndex < sizeBufferTexture - 1; ++cntIndex )
		{
			if( pBufferTexture[ cntIndex ] == '\0' )
			{
				_tcscpy_s( &aNameTexture[ 0 ], _MAX_PATH, pPathTexture );
				_tcscat_s( &aNameTexture[ 0 ], _MAX_PATH, _T( "/" ) );
				_tcscat_s( &aNameTexture[ 0 ], _MAX_PATH, &pBufferTexture[ cntIndex + 1 ] );
				pIndexTexture[ indexTextureCurrent ] = pTexture->Load( &aNameTexture[ 0 ] );
				indexTextureCurrent += 1;
			}
		}
	}

	// テクスチャ名バッファの開放
	delete[] pBufferTexture;
	pBufferTexture = nullptr;

	// スキンメッシュ情報の取得
	unsigned long	numMesh;		// メッシュ数
	unsigned long	numBone;		// ボーン数
	file.Read( &numMesh );
	file.Read( &numBone );
	m_pSkinMesh->Initialize( numMesh, numBone );

	// メッシュ情報の取得
	for( unsigned long cntMesh = 0; cntMesh < numMesh; ++cntMesh )
	{
		// 個数の情報を取得
		unsigned long	numVertex;		// 頂点数
		unsigned long	numCoord;		// 座標数
		unsigned long	numNormal;		// 法線数
		unsigned long	numUVSet;		// UVセット数
		unsigned long	numColorSet;	// 頂点カラー数
		unsigned long	numBlend;		// ブレンド数
		file.Read( &numVertex );
		file.Read( &numCoord );
		file.Read( &numNormal );
		file.Read( &numUVSet );
		file.Read( &numColorSet );
		file.Read( &numBlend );
		m_pSkinMesh->m_pMesh[ cntMesh ].Initialize( pDevice->m_pD3DDevice, numVertex / 3, numUVSet );

		// 頂点バッファ更新開始
		CSkinMesh::CMesh::VERTEX_COORD	*pVertexBufferCoord = nullptr;		// 書き換え用頂点バッファアドレス
		m_pSkinMesh->m_pMesh[ cntMesh ].m_pCoord->Lock( 0, 0, (void**)&pVertexBufferCoord, 0 );

		// 座標情報を取得
		float*	pCoord = nullptr;		// 座標情報
		pCoord = new float[ numCoord * 3 ];
		if( pCoord == nullptr )
		{
			return 1;
		}
		file.Read( pCoord, numCoord * 3 );

		// 座標の設定
		for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
		{
			unsigned long	indexCoord;		// 座標番号
			file.Read( &indexCoord );
			pVertexBufferCoord[ cntVertex ].coordX = pCoord[ indexCoord * 3 + 0 ];
			pVertexBufferCoord[ cntVertex ].coordY = pCoord[ indexCoord * 3 + 1 ];
			pVertexBufferCoord[ cntVertex ].coordZ = pCoord[ indexCoord * 3 + 2 ];
		}

		// 座標情報の破棄
		delete[] pCoord;
		pCoord = nullptr;

		// 法線情報を取得
		float*	pNormal = nullptr;		// 法線情報
		pNormal = new float[ numNormal * 3 ];
		if( pNormal == nullptr )
		{
			return 1;
		}
		file.Read( pNormal, numNormal * 3 );

		// 法線の設定
		for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
		{
			unsigned long	indexNormal;		// 法線番号
			file.Read( &indexNormal );
			pVertexBufferCoord[ cntVertex ].normalX = pNormal[ indexNormal * 3 + 0 ];
			pVertexBufferCoord[ cntVertex ].normalY = pNormal[ indexNormal * 3 + 1 ];
			pVertexBufferCoord[ cntVertex ].normalZ = pNormal[ indexNormal * 3 + 2 ];

		}

		// 法線情報の破棄
		delete[] pNormal;
		pNormal = nullptr;

		// ブレンド情報を取得
		float*			pBlendWeight = nullptr;		// ブレンド重み情報
		unsigned char*	pBlendIndex = nullptr;		// ブレンドボーン番号情報
		pBlendWeight = new float[ numBlend * 3 ];
		if( pBlendWeight == nullptr )
		{
			return 1;
		}
		pBlendIndex = new unsigned char[ numBlend * 4 ];
		if( pBlendIndex == nullptr )
		{
			return 1;
		}
		file.Read( pBlendWeight, numBlend * 3 );
		file.Read( pBlendIndex, numBlend * 4 );

		// ブレンドの設定
		for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
		{
			unsigned long	indexBlend;		// ブレンド番号
			file.Read( &indexBlend );
			pVertexBufferCoord[ cntVertex ].weight[ 0 ] = pBlendWeight[ indexBlend * 3 + 0 ];
			pVertexBufferCoord[ cntVertex ].weight[ 1 ] = pBlendWeight[ indexBlend * 3 + 1 ];
			pVertexBufferCoord[ cntVertex ].weight[ 2 ] = pBlendWeight[ indexBlend * 3 + 2 ];
			pVertexBufferCoord[ cntVertex ].indexBone[ 0 ] = pBlendIndex[ indexBlend * 4 + 0 ];
			pVertexBufferCoord[ cntVertex ].indexBone[ 1 ] = pBlendIndex[ indexBlend * 4 + 1 ];
			pVertexBufferCoord[ cntVertex ].indexBone[ 2 ] = pBlendIndex[ indexBlend * 4 + 2 ];
			pVertexBufferCoord[ cntVertex ].indexBone[ 3 ] = pBlendIndex[ indexBlend * 4 + 3 ];
		}

		// ブレンド情報の破棄
		delete[] pBlendWeight;
		pBlendWeight = nullptr;
		delete[] pBlendIndex;
		pBlendIndex = nullptr;

		// 頂点カラー情報の設定
		for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
		{
			pVertexBufferCoord[ cntVertex ].color = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
		}

		// 頂点バッファ更新終了
		m_pSkinMesh->m_pMesh[ cntMesh ].m_pCoord->Unlock();

		// UVセット情報の取得
		for( unsigned long cntUVSet = 0; cntUVSet < numUVSet; ++cntUVSet )
		{
			// UVセットの情報を取得
			long			indexTexture;					// テクスチャ番号
			unsigned long	typeUVset;						// UVセットの種類
			unsigned long	numUV;							// UV数
			CTexture*		pTextureUVset = nullptr;		// テクスチャ
			file.Read( &indexTexture );
			if( indexTexture >= 0 )
			{
				pTextureUVset = pTexture->Get( pIndexTexture[ indexTexture ] );
				m_pSkinMesh->m_pMesh[ cntMesh ].m_pUVSet[ cntUVSet ].m_pTexture = pTextureUVset->m_pTexture;
			}
			file.Read( &typeUVset );
			file.Read( &numUV );
			m_pSkinMesh->m_pMesh[ cntMesh ].m_pUVSet[ cntUVSet ].Initialize( pDevice->m_pD3DDevice, numVertex / 3 );

			// UV座標バッファ更新開始
			CSkinMesh::CMesh::CUVSet::VERTEX_TEXTURE	*pVertexBufferTexture = nullptr;		// 書き換え用頂点バッファアドレス
			m_pSkinMesh->m_pMesh[ cntMesh ].m_pUVSet[ cntUVSet ].m_pUV->Lock( 0, 0, (void**)&pVertexBufferTexture, 0 );

			// UV座標情報を取得
			float*	pUV = nullptr;		// UV座標情報
			pUV = new float[ numUV * 2 ];
			if( pUV == nullptr )
			{
				return 1;
			}
			file.Read( pUV, numUV * 2 );

			// 頂点座標の設定
			for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
			{
				unsigned long	indexUV;		// UV座標番号
				file.Read( &indexUV );
				pVertexBufferTexture[ cntVertex ].textureU = pUV[ indexUV * 2 + 0 ];
				pVertexBufferTexture[ cntVertex ].textureV = 1.0f - pUV[ indexUV * 2 + 1 ];
			}

			// 重みの取得
			file.Read( &m_pSkinMesh->m_pMesh[ cntMesh ].m_pUVSet[ cntUVSet ].m_weight );

			// 頂点情報の破棄
			delete[] pUV;
			pUV = nullptr;

			// UV座標バッファ更新終了
			m_pSkinMesh->m_pMesh[ cntMesh ].m_pUVSet[ cntUVSet ].m_pUV->Unlock();
		}

		// 頂点カラーセット情報の取得
		for( unsigned long cntColorSet = 0; cntColorSet < numColorSet; ++cntColorSet )
		{
			// 頂点カラーセットの情報を取得
			unsigned long	numColor;		// 頂点カラー数
			file.Read( &numColor );

			// 頂点カラー情報を取得
			float*	pColor = nullptr;		// 頂点カラー情報
			pColor = new float[ numTexture * 4 ];
			if( pColor == nullptr )
			{
				return 1;
			}
			file.Read( pColor, numColor * 4 );

			// 頂点カラーの設定
			for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
			{
				unsigned long	indexColor;		// 頂点カラー番号
				file.Read( &indexColor );
			}

			// 頂点カラー情報の破棄
			delete[] pColor;
			pColor = nullptr;
		}

		// マテリアル情報の取得
		float	transparent;		// 透過度
		float	reflection;			// 反射率
		file.Read( &m_pSkinMesh->m_pMesh[ cntMesh ].m_material.Ambient.r, 3 );
		file.Read( &m_pSkinMesh->m_pMesh[ cntMesh ].m_material.Diffuse.r, 3 );
		file.Read( &m_pSkinMesh->m_pMesh[ cntMesh ].m_material.Specular.r, 3 );
		file.Read( &m_pSkinMesh->m_pMesh[ cntMesh ].m_material.Emissive.r, 3 );
		file.Read( &m_pSkinMesh->m_pMesh[ cntMesh ].m_material.Power );
		file.Read( &transparent );
		file.Read( &reflection );
		m_pSkinMesh->m_pMesh[ cntMesh ].m_material.Ambient.a = transparent;
		m_pSkinMesh->m_pMesh[ cntMesh ].m_material.Diffuse.a = transparent;
		m_pSkinMesh->m_pMesh[ cntMesh ].m_material.Specular.a = transparent;
		m_pSkinMesh->m_pMesh[ cntMesh ].m_material.Emissive.a = transparent;
	}

	// ボーン情報の取得
	for( unsigned long cntBone = 0; cntBone < numBone; ++cntBone )
	{
		D3DXMatrixIdentity( &m_pSkinMesh->m_pMatrixBone[ cntBone ] );
		file.Read( &m_pSkinMesh->m_pMatrixBone[ cntBone ]._11, 3 );
		file.Read( &m_pSkinMesh->m_pMatrixBone[ cntBone ]._21, 3 );
		file.Read( &m_pSkinMesh->m_pMatrixBone[ cntBone ]._31, 3 );
		file.Read( &m_pSkinMesh->m_pMatrixBone[ cntBone ]._41, 3 );
	}

	// テクスチャバッファの開放
	delete[] pIndexTexture;
	pIndexTexture = nullptr;
#endif
	// 正常終了
	return 0;
}
