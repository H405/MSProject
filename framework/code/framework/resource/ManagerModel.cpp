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
#include "ModelConvert.h"
#include "ModelX.h"
#include "Texture.h"
#include "../graphic/Material.h"
#include "../system/File.h"
#include "../vertex/Vertex.h"
#include "../vertex/VertexBuffer.h"

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
	// ファイルの読み込み
	File	file;
	file.Initialize( pPath );

	// ファイルの種類を確認
	if( !file.IsType( _T( "SKN3" ) ) )
	{
		TCHAR	pStringError[ 256 ];		// エラーメッセージ
		sprintf_s( pStringError, 256, _T( "ファイル\"%s\"が見つかりません。" ), pPath );
		MessageBox( nullptr, &pStringError[ 0 ], _T( "エラー" ), MB_OK );
		return 1;
	}

	// テクスチャ名の読み込み
	unsigned long	countTexture = 0;				// テクスチャ数
	unsigned long	sizeBufferTexture = 0;			// テクスチャバッファサイズ
	char*			pBufferTexture = nullptr;		// テクスチャバッファ
	file.Read( &countTexture );
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
		TCHAR			pNameTexture[ _MAX_PATH ];		// テクスチャファイル名

		// テクスチャ番号格納領域の確保
		pIndexTexture = new int[ countTexture ];
		if( pIndexTexture == nullptr )
		{
			return 1;
		}

		// 読み込み
		_tcscpy_s( &pNameTexture[ 0 ], _MAX_PATH, _T( "model/" ) );
		_tcscat_s( &pNameTexture[ 0 ], _MAX_PATH, &pBufferTexture[ 0 ] );
		pIndexTexture[ 0 ] = pTexture_->Load( &pNameTexture[ 0 ] );
		indexTextureCurrent += 1;
		for( unsigned long counterIndex = 0; counterIndex < sizeBufferTexture - 1; ++counterIndex )
		{
			if( pBufferTexture[ counterIndex ] == '\0' )
			{
				_tcscpy_s( &pNameTexture[ 0 ], _MAX_PATH, _T( "model/" ) );
				_tcscat_s( &pNameTexture[ 0 ], _MAX_PATH, &pBufferTexture[ counterIndex + 1 ] );
				pIndexTexture[ indexTextureCurrent ] = pTexture_->Load( &pNameTexture[ 0 ] );
				indexTextureCurrent += 1;
			}
		}
	}

	// テクスチャ名バッファの開放
	delete[] pBufferTexture;
	pBufferTexture = nullptr;

	// スキンメッシュ情報の取得
	unsigned long	countMesh;		// メッシュ数
	unsigned long	countBone;		// ボーン数
	file.Read( &countMesh );
	file.Read( &countBone );

	// 頂点情報の生成
	int		result;		// 実行結果
	Vertex	vertex;		// 頂点情報
	result = vertex.Initialize( pDevice_, Vertex::ELEMENT_SET_SKIN );
	if( result != 0 )
	{
		return result;
	}

	// 頂点バッファの生成
	VertexBuffer*	pVertexBuffer = nullptr;		// 頂点バッファ
	pVertexBuffer = new VertexBuffer[ countMesh ];
	if( pVertexBuffer == nullptr )
	{
		return 1;
	}

	// マテリアル情報格納バッファの確保
	Material*	pMaterial = nullptr;			// マテリアル情報
	int*		pIndexMaterial = nullptr;		// マテリアル番号
	pMaterial = new Material[ countMesh ];
	if( pMaterial == nullptr )
	{
		return 1;
	}
	pIndexMaterial = new int[ countMesh ];
	for( unsigned int counterIndex = 0; counterIndex < countMesh; ++counterIndex )
	{
		pIndexMaterial[ counterIndex ] = -1;
	}

	// テクスチャ情報格納バッファの確保
	IDirect3DTexture9**	ppTexture = nullptr;			// テクスチャ情報
	int*				pIndexTextureSet = nullptr;		// テクスチャ番号
	if( countTexture > 0 )
	{
		ppTexture = new IDirect3DTexture9*[ countTexture ];
		if( ppTexture == nullptr )
		{
			return 1;
		}
		for( unsigned int counterTexture = 0; counterTexture < countTexture; ++counterTexture )
		{
			ppTexture[ counterTexture ] = pTexture_->Get( pIndexTexture[ counterTexture ] )->pTexture_;
		}
	}
	pIndexTextureSet = new int[ countMesh ];
	for( unsigned int counterIndex = 0; counterIndex < countMesh; ++counterIndex )
	{
		pIndexTextureSet[ counterIndex ] = -1;
	}

	// メッシュの頂点数格納バッファの確保
	int*	pCountVertex = nullptr;		// メッシュの頂点数
	pCountVertex = new int[ countMesh ];
	if( pCountVertex == nullptr )
	{
		return 1;
	}
	for( unsigned int counterMesh = 0; counterMesh < countMesh; ++counterMesh )
	{
		pCountVertex[ counterMesh ] = 0;
	}

	// メッシュ情報の取得
	for( unsigned long counterMesh = 0; counterMesh < countMesh; ++counterMesh )
	{
		// 個数の情報を取得
		unsigned long	countVertex;		// 頂点数
		unsigned long	countCoord;			// 座標数
		unsigned long	countNormal;		// 法線数
		unsigned long	countUVSet;			// UVセット数
		unsigned long	countColorSet;		// 頂点カラー数
		unsigned long	countBlend;			// ブレンド数
		file.Read( &countVertex );
		file.Read( &countCoord );
		file.Read( &countNormal );
		file.Read( &countUVSet );
		file.Read( &countColorSet );
		file.Read( &countBlend );

		// 頂点バッファに情報を設定
		pVertexBuffer[ counterMesh ].Initialize( countVertex, &vertex );

		// 頂点数の保存
		pCountVertex[ counterMesh ] = countVertex;

		// 座標情報を取得
		float*	pCoord = nullptr;		// 座標情報
		pCoord = new float[ countCoord * 3 ];
		if( pCoord == nullptr )
		{
			return 1;
		}
		file.Read( pCoord, countCoord * 3 );

		// 座標の設定
		for( unsigned long counterVertex = 0; counterVertex < countVertex; ++counterVertex )
		{
			unsigned long	indexCoord;		// 座標番号
			file.Read( &indexCoord );
			pVertexBuffer[ counterMesh ].SetPosition( counterVertex, pCoord[ indexCoord * 3 + 0 ], pCoord[ indexCoord * 3 + 1 ], pCoord[ indexCoord * 3 + 2 ] );
		}

		// 座標情報の破棄
		delete[] pCoord;
		pCoord = nullptr;

		// 法線情報を取得
		float*	pNormal = nullptr;		// 法線情報
		pNormal = new float[ countNormal * 3 ];
		if( pNormal == nullptr )
		{
			return 1;
		}
		file.Read( pNormal, countNormal * 3 );

		// 法線の設定
		for( unsigned long counterVertex = 0; counterVertex < countVertex; ++counterVertex )
		{
			unsigned long	indexNormal;		// 法線番号
			file.Read( &indexNormal );
			pVertexBuffer[ counterMesh ].SetNormal( counterVertex, pNormal[ indexNormal * 3 + 0 ], pNormal[ indexNormal * 3 + 1 ], pNormal[ indexNormal * 3 + 2 ] );

		}

		// 法線情報の破棄
		delete[] pNormal;
		pNormal = nullptr;

		// ブレンド情報を取得
		float*			pBlendWeight = nullptr;		// ブレンド重み情報
		unsigned char*	pBlendIndex = nullptr;		// ブレンドボーン番号情報
		pBlendWeight = new float[ countBlend * 3 ];
		if( pBlendWeight == nullptr )
		{
			return 1;
		}
		pBlendIndex = new unsigned char[ countBlend * 4 ];
		if( pBlendIndex == nullptr )
		{
			return 1;
		}
		file.Read( pBlendWeight, countBlend * 3 );
		file.Read( pBlendIndex, countBlend * 4 );

		// ブレンドの設定
		for( unsigned long counterVertex = 0; counterVertex < countVertex; ++counterVertex )
		{
			unsigned long	indexBlend;		// ブレンド番号
			file.Read( &indexBlend );
			pVertexBuffer[ counterMesh ].SetBlendWeight( counterVertex,
				pBlendWeight[ indexBlend * 3 + 0 ], pBlendWeight[ indexBlend * 3 + 1 ], pBlendWeight[ indexBlend * 3 + 2 ] );
			pVertexBuffer[ counterMesh ].SetBlendIndecies( counterVertex,
				pBlendIndex[ indexBlend * 4 + 0 ], pBlendIndex[ indexBlend * 4 + 1 ],
				pBlendIndex[ indexBlend * 4 + 2 ], pBlendIndex[ indexBlend * 4 + 3 ] );
		}

		// ブレンド情報の破棄
		delete[] pBlendWeight;
		pBlendWeight = nullptr;
		delete[] pBlendIndex;
		pBlendIndex = nullptr;

		// UVセット情報の取得
		for( unsigned long counterUVSet = 0; counterUVSet < countUVSet; ++counterUVSet )
		{
			// UVセットの情報を取得
			long			indexTexture;					// テクスチャ番号
			unsigned long	typeUVset;						// UVセットの種類
			unsigned long	countUV;						// UV数
			Texture*		pTextureUVset = nullptr;		// テクスチャ
			file.Read( &indexTexture );
			file.Read( &typeUVset );
			file.Read( &countUV );

			// テクスチャ番号を保存
			if( counterUVSet == 0 )
			{
				pIndexTextureSet[ counterMesh ] = indexTexture;
			}

			// UV座標情報を取得
			float*	pUV = nullptr;		// UV座標情報
			pUV = new float[ countUV * 2 ];
			if( pUV == nullptr )
			{
				return 1;
			}
			file.Read( pUV, countUV * 2 );

			// UV座標の設定
			for( unsigned long counterVertex = 0; counterVertex < countVertex; ++counterVertex )
			{
				unsigned long	indexUV;		// UV座標番号
				file.Read( &indexUV );
				if( counterUVSet == 0 )
				{
					pVertexBuffer[ counterMesh ].SetTextureCoord0( counterVertex, pUV[ indexUV * 2 + 0 ], 1.0f - pUV[ indexUV * 2 + 1 ] );
				}
			}

			// 重みの取得
			float	weight;
			file.Read( &weight );

			// 頂点情報の破棄
			delete[] pUV;
			pUV = nullptr;
		}

		// 頂点カラーセット情報の取得
		for( unsigned long cntColorSet = 0; cntColorSet < countColorSet; ++cntColorSet )
		{
			// 頂点カラーセットの情報を取得
			unsigned long	countColor;		// 頂点カラー数
			file.Read( &countColor );

			// 頂点カラー情報を取得
			float*	pColor = nullptr;		// 頂点カラー情報
			pColor = new float[ countTexture * 4 ];
			if( pColor == nullptr )
			{
				return 1;
			}
			file.Read( pColor, countColor * 4 );

			// 頂点カラーの設定
			for( unsigned long counterVertex = 0; counterVertex < countVertex; ++counterVertex )
			{
				unsigned long	indexColor;		// 頂点カラー番号
				file.Read( &indexColor );
			}

			// 頂点カラー情報の破棄
			delete[] pColor;
			pColor = nullptr;
		}

		// マテリアル情報の取得
		Material	material;			// マテリアル
		D3DXCOLOR	emissive;			// エミッシブ色
		float		transparent;		// 透過度
		float		reflection;			// 反射率
		file.Read( &material.ambient_.r, 3 );
		file.Read( &material.diffuse_.r, 3 );
		file.Read( &material.specular_.r, 3 );
		file.Read( &emissive.r, 3 );
		file.Read( &material.power_ );
		file.Read( &transparent );
		file.Read( &reflection );
		material.ambient_.a = transparent;
		material.diffuse_.a = transparent;
		material.specular_.a = transparent;
		pMaterial[ counterMesh ] = material;
	}

	// ボーン情報の取得
	D3DXMATRIX*	pMatrixBone = nullptr;		// ボーン初期姿勢行列
	pMatrixBone = new D3DXMATRIX[ countBone ];
	if( pMatrixBone == nullptr )
	{
		return 1;
	}
	for( unsigned long counterBone = 0; counterBone < countBone; ++counterBone )
	{
		D3DXMatrixIdentity( &pMatrixBone[ counterBone ] );
		file.Read( &pMatrixBone[ counterBone ]._11, 3 );
		file.Read( &pMatrixBone[ counterBone ]._21, 3 );
		file.Read( &pMatrixBone[ counterBone ]._31, 3 );
		file.Read( &pMatrixBone[ counterBone ]._41, 3 );
	}

	// モデルの生成
	ModelConvert*	pModel = nullptr;				// モデル
	void**			ppVertexBuffer = nullptr;		// 頂点情報
	ppVertexBuffer = new void*[ countMesh ];
	if( ppVertexBuffer == nullptr )
	{
		return 1;
	}
	for( unsigned int counterMesh = 0; counterMesh < countMesh; ++counterMesh )
	{
		ppVertexBuffer[ counterMesh ] = pVertexBuffer[ counterMesh ].GetBuffer();
	}
	pModel= new ModelConvert();
	if( pModel == nullptr )
	{
		return 1;
	}
	result = pModel->Initialize( pDevice_, Vertex::ELEMENT_SET_SKIN, countMesh, countTexture, countMesh, countBone,
		ppVertexBuffer, pCountVertex, pMaterial, pIndexMaterial, ppTexture, pIndexTextureSet, pMatrixBone );
	if( result != 0 )
	{
		return result;
	}
	pBufferItem_[ index ].pItem_ = pModel;

	// ボーン情報格納バッファの開放
	delete[] pMatrixBone;
	pMatrixBone = nullptr;

	// メッシュの頂点数格納バッファの開放
	delete[] ppVertexBuffer;
	ppVertexBuffer = nullptr;
	delete[] pCountVertex;
	pCountVertex = nullptr;

	// テクスチャ情報格納バッファの開放
	delete[] pIndexTextureSet;
	pIndexTextureSet = nullptr;
	delete[] ppTexture;
	ppTexture = nullptr;

	// マテリアル情報格納バッファの開放
	delete[] pIndexMaterial;
	pIndexMaterial = nullptr;
	delete[] pMaterial;
	pMaterial = nullptr;

	// 頂点バッファの開放
	delete[] pVertexBuffer;
	pVertexBuffer = nullptr;

	// テクスチャバッファの開放
	delete[] pIndexTexture;
	pIndexTexture = nullptr;

	// 正常終了
	return 0;
}
