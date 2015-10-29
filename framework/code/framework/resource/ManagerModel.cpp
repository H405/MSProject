//==============================================================================
//
// File   : ManagerModel.cpp
// Brief  : ���f���Ǘ��N���X
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ManagerModel.h"
#include "ManagerTexture.h"
#include "ModelX.h"
#include "Texture.h"
#include "../graphic/Material.h"
#include "../system/File.h"
#include "../vertex/Vertex.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �e���v���[�g�錾
//******************************************************************************
template class ManagerModel< class Model >;

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerModel< TypeItem >::ManagerModel( void ) : ManagerResource()
{
	// �N���X���̏���������
	InitializeSelf();
}

//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
ManagerModel< TypeItem >::~ManagerModel( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : TCHAR* pDirectory					: ��f�B���N�g��
// Arg    : TCHAR* pDirectoryTexture			: �e�N�X�`����f�B���N�g��
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : ManagerTexture< Texture >* pTexture	: �e�N�X�`���Ǘ��N���X
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Initialize( TCHAR* pDirectory, TCHAR* pDirectoryTexture, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerResource::Initialize( pDirectory, maximumItem );
	if( result != 0 )
	{
		return result;
	}

	// �����o�ϐ��̐ݒ�
	pDevice_ = pDevice;
	pTexture_ = pTexture;

	// ������̊i�[�̈���m��
	pDirectoryTexture_ = new TCHAR[ _MAX_PATH ];
	if( pDirectoryTexture_ == nullptr )
	{
		return 1;
	}
	memset( pDirectoryTexture_, 0x00, sizeof( TCHAR ) * _MAX_PATH );
	_tcscpy_s( pDirectoryTexture_, _MAX_PATH, pDirectoryTexture );

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Finalize( void )
{
	// �i�[�̈�̊J��
	delete[] pDirectoryTexture_;
	pDirectoryTexture_ = nullptr;

	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerResource::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// �N���X���̏���������
	InitializeSelf();

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ď���������
// Return : int									: ���s����
// Arg    : TCHAR* pDirectory					: ��f�B���N�g��
// Arg    : TCHAR* pDirectoryTexture			: �e�N�X�`����f�B���N�g��
// Arg    : int maximumItem						: �ő�v�f��
// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
// Arg    : ManagerTexture< Texture >* pTexture	: �e�N�X�`���Ǘ��N���X
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Reinitialize( TCHAR* pDirectory, TCHAR* pDirectoryTexture, int maximumItem, IDirect3DDevice9* pDevice, ManagerTexture< Texture >* pTexture )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( pDirectory, pDirectoryTexture, maximumItem, pDevice, pTexture );
}

//==============================================================================
// Brief  : �N���X�̃R�s�[
// Return : int									: ���s����
// Arg    : ManagerModel* pOut					: �R�s�[��A�h���X
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::Copy( ManagerModel* pOut ) const
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = ManagerResource::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
template< class TypeItem >
void ManagerModel< TypeItem >::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	pDevice_ = nullptr;
	pTexture_ = nullptr;
	pDirectoryTexture_ = nullptr;
}

//==============================================================================
// Brief  : ���\�[�X�̓ǂݍ���
// Return : int									: ���s����
// Arg    : TCHAR* pPath						: �t�@�C���p�X
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::LoadResource( TCHAR* pPath, int index )
{
	// X�t�@�C�����f���̓ǂݍ���
	if( pPath[ _tcslen( pPath ) - 1 ] == _T( 'x' ) )
	{
		return LoadModelX( pPath, index );
	}

	// �ϊ��ς݃��f���̓ǂݍ���
	return LoadModelConvert( pPath, index );
}

//==============================================================================
// Brief  : ���\�[�X�̊J��
// Return : void								: �Ȃ�
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
void ManagerModel< TypeItem >::ReleaseResource( int index )
{
	// ���f���̊J��
	delete pBufferItem_[ index ].pItem_;
	pBufferItem_[ index ].pItem_ = nullptr;
}

//==============================================================================
// Brief  : X�t�@�C���̓ǂݍ���
// Return : int									: ���s����
// Arg    : TCHAR* pPath						: �t�@�C���p�X
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::LoadModelX( TCHAR* pPath, int index )
{
	// ���f������
	DWORD				countMaterial;				// �}�e���A�����̐�
	ID3DXMesh*			pMesh = nullptr;			// ���b�V�����ւ̃A�h���X
	ID3DXBuffer*		pMaterial = nullptr;		// �}�e���A�����ւ̃A�h���X
	HRESULT				result;						// ���s����
	result = D3DXLoadMeshFromX( pPath, D3DXMESH_SYSTEMMEM, pDevice_, NULL, &pMaterial, NULL, &countMaterial, &pMesh );
	if( result != 0 )
	{
		TCHAR	pStringError[ 512 ] = {};		// �G���[������
		sprintf_s( pStringError, 512, _T( "�t�@�C��\"%s\"��������܂���" ), pPath );
		MessageBox( NULL, pStringError, _T( "�G���[" ), MB_OK );
		return 1;
	}

	// ���f���̐���
	ModelX*	pModel = nullptr;		// ���f��
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

	// �e�N�X�`���̐ݒ�
	D3DXMATERIAL*	pMaterialPointer = nullptr;		// �}�e���A�����̐擪�A�h���X
	Texture*		pTexture = nullptr;				// �e�N�X�`��
	TCHAR			pNameTexture[ _MAX_PATH ];		// �e�N�X�`���t�@�C����
	pMaterialPointer = static_cast< D3DXMATERIAL* >( pMaterial->GetBufferPointer() );
	for( unsigned long counterMaterial = 0; counterMaterial < countMaterial; ++counterMaterial )
	{
		// �e�N�X�`�������邩�m�F
		if( pMaterialPointer[ counterMaterial ].pTextureFilename == nullptr )
		{
			continue;
		}

		// �e�N�X�`�����̍쐬
		_tcscpy_s( pNameTexture, _MAX_PATH, pDirectoryTexture_ );
		_tcscat_s( pNameTexture, _MAX_PATH, pMaterialPointer[ counterMaterial ].pTextureFilename );

		// �e�N�X�`���̓ǂݍ���
		pTexture = nullptr;
		pTexture = pTexture_->Get( pNameTexture );
		if( pTexture != nullptr )
		{
			pBufferItem_[ index ].pItem_->SetTexture( counterMaterial, pTexture->pTexture_ );
		}
	}

	// �}�e���A���̐ݒ�
	Material		materialSet;		// �ݒ肷��}�e���A��
	D3DMATERIAL9	materialGet;		// �擾�����}�e���A��
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

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �ϊ��ς݃��f���t�@�C���̓ǂݍ���
// Return : int									: ���s����
// Arg    : TCHAR* pPath						: �t�@�C���p�X
// Arg    : int index							: �i�[�v�f�ԍ�
//==============================================================================
template< class TypeItem >
int ManagerModel< TypeItem >::LoadModelConvert( TCHAR* pPath, int index )
{
#if 0
	// �t�@�C���̓ǂݍ���
	File	file;
	file.Initialize( pPath );

	// �t�@�C���̎�ނ��m�F
	if( !file.IsType( _T( "SKN3" ) ) )
	{
		TCHAR	aStrError[ 256 ];		// �G���[���b�Z�[�W
		sprintf_s( &aStrError[ 0 ], 256, _T( "�t�@�C��\"%s\"��������܂���B" ), pPath );
		MessageBox( nullptr, &aStrError[ 0 ], _T( "�G���[" ), MB_OK );
		return 1;
	}

	// �e�N�X�`�����̓ǂݍ���
	unsigned long	numTexture = 0;				// �e�N�X�`����
	unsigned long	sizeBufferTexture = 0;		// �e�N�X�`���o�b�t�@�T�C�Y
	char*			pBufferTexture = nullptr;	// �e�N�X�`���o�b�t�@
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

	// �e�N�X�`���̓ǂݍ���
	int*	pIndexTexture = nullptr;	// �e�N�X�`���ԍ�
	if( sizeBufferTexture > 0 )
	{
		unsigned long	indexTextureCurrent = 0;		// ���݂̃e�N�X�`���ԍ�
		TCHAR			aNameTexture[ _MAX_PATH ];	// �e�N�X�`���t�@�C����

		// �e�N�X�`���ԍ��i�[�̈�̊m��
		pIndexTexture = new int[ sizeBufferTexture ];
		if( pIndexTexture == nullptr )
		{
			return 1;
		}

		// �ǂݍ���
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

	// �e�N�X�`�����o�b�t�@�̊J��
	delete[] pBufferTexture;
	pBufferTexture = nullptr;

	// �X�L�����b�V�����̎擾
	unsigned long	numMesh;		// ���b�V����
	unsigned long	numBone;		// �{�[����
	file.Read( &numMesh );
	file.Read( &numBone );
	m_pSkinMesh->Initialize( numMesh, numBone );

	// ���b�V�����̎擾
	for( unsigned long cntMesh = 0; cntMesh < numMesh; ++cntMesh )
	{
		// ���̏����擾
		unsigned long	numVertex;		// ���_��
		unsigned long	numCoord;		// ���W��
		unsigned long	numNormal;		// �@����
		unsigned long	numUVSet;		// UV�Z�b�g��
		unsigned long	numColorSet;	// ���_�J���[��
		unsigned long	numBlend;		// �u�����h��
		file.Read( &numVertex );
		file.Read( &numCoord );
		file.Read( &numNormal );
		file.Read( &numUVSet );
		file.Read( &numColorSet );
		file.Read( &numBlend );
		m_pSkinMesh->m_pMesh[ cntMesh ].Initialize( pDevice->m_pD3DDevice, numVertex / 3, numUVSet );

		// ���_�o�b�t�@�X�V�J�n
		CSkinMesh::CMesh::VERTEX_COORD	*pVertexBufferCoord = nullptr;		// ���������p���_�o�b�t�@�A�h���X
		m_pSkinMesh->m_pMesh[ cntMesh ].m_pCoord->Lock( 0, 0, (void**)&pVertexBufferCoord, 0 );

		// ���W�����擾
		float*	pCoord = nullptr;		// ���W���
		pCoord = new float[ numCoord * 3 ];
		if( pCoord == nullptr )
		{
			return 1;
		}
		file.Read( pCoord, numCoord * 3 );

		// ���W�̐ݒ�
		for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
		{
			unsigned long	indexCoord;		// ���W�ԍ�
			file.Read( &indexCoord );
			pVertexBufferCoord[ cntVertex ].coordX = pCoord[ indexCoord * 3 + 0 ];
			pVertexBufferCoord[ cntVertex ].coordY = pCoord[ indexCoord * 3 + 1 ];
			pVertexBufferCoord[ cntVertex ].coordZ = pCoord[ indexCoord * 3 + 2 ];
		}

		// ���W���̔j��
		delete[] pCoord;
		pCoord = nullptr;

		// �@�������擾
		float*	pNormal = nullptr;		// �@�����
		pNormal = new float[ numNormal * 3 ];
		if( pNormal == nullptr )
		{
			return 1;
		}
		file.Read( pNormal, numNormal * 3 );

		// �@���̐ݒ�
		for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
		{
			unsigned long	indexNormal;		// �@���ԍ�
			file.Read( &indexNormal );
			pVertexBufferCoord[ cntVertex ].normalX = pNormal[ indexNormal * 3 + 0 ];
			pVertexBufferCoord[ cntVertex ].normalY = pNormal[ indexNormal * 3 + 1 ];
			pVertexBufferCoord[ cntVertex ].normalZ = pNormal[ indexNormal * 3 + 2 ];

		}

		// �@�����̔j��
		delete[] pNormal;
		pNormal = nullptr;

		// �u�����h�����擾
		float*			pBlendWeight = nullptr;		// �u�����h�d�ݏ��
		unsigned char*	pBlendIndex = nullptr;		// �u�����h�{�[���ԍ����
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

		// �u�����h�̐ݒ�
		for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
		{
			unsigned long	indexBlend;		// �u�����h�ԍ�
			file.Read( &indexBlend );
			pVertexBufferCoord[ cntVertex ].weight[ 0 ] = pBlendWeight[ indexBlend * 3 + 0 ];
			pVertexBufferCoord[ cntVertex ].weight[ 1 ] = pBlendWeight[ indexBlend * 3 + 1 ];
			pVertexBufferCoord[ cntVertex ].weight[ 2 ] = pBlendWeight[ indexBlend * 3 + 2 ];
			pVertexBufferCoord[ cntVertex ].indexBone[ 0 ] = pBlendIndex[ indexBlend * 4 + 0 ];
			pVertexBufferCoord[ cntVertex ].indexBone[ 1 ] = pBlendIndex[ indexBlend * 4 + 1 ];
			pVertexBufferCoord[ cntVertex ].indexBone[ 2 ] = pBlendIndex[ indexBlend * 4 + 2 ];
			pVertexBufferCoord[ cntVertex ].indexBone[ 3 ] = pBlendIndex[ indexBlend * 4 + 3 ];
		}

		// �u�����h���̔j��
		delete[] pBlendWeight;
		pBlendWeight = nullptr;
		delete[] pBlendIndex;
		pBlendIndex = nullptr;

		// ���_�J���[���̐ݒ�
		for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
		{
			pVertexBufferCoord[ cntVertex ].color = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
		}

		// ���_�o�b�t�@�X�V�I��
		m_pSkinMesh->m_pMesh[ cntMesh ].m_pCoord->Unlock();

		// UV�Z�b�g���̎擾
		for( unsigned long cntUVSet = 0; cntUVSet < numUVSet; ++cntUVSet )
		{
			// UV�Z�b�g�̏����擾
			long			indexTexture;					// �e�N�X�`���ԍ�
			unsigned long	typeUVset;						// UV�Z�b�g�̎��
			unsigned long	numUV;							// UV��
			CTexture*		pTextureUVset = nullptr;		// �e�N�X�`��
			file.Read( &indexTexture );
			if( indexTexture >= 0 )
			{
				pTextureUVset = pTexture->Get( pIndexTexture[ indexTexture ] );
				m_pSkinMesh->m_pMesh[ cntMesh ].m_pUVSet[ cntUVSet ].m_pTexture = pTextureUVset->m_pTexture;
			}
			file.Read( &typeUVset );
			file.Read( &numUV );
			m_pSkinMesh->m_pMesh[ cntMesh ].m_pUVSet[ cntUVSet ].Initialize( pDevice->m_pD3DDevice, numVertex / 3 );

			// UV���W�o�b�t�@�X�V�J�n
			CSkinMesh::CMesh::CUVSet::VERTEX_TEXTURE	*pVertexBufferTexture = nullptr;		// ���������p���_�o�b�t�@�A�h���X
			m_pSkinMesh->m_pMesh[ cntMesh ].m_pUVSet[ cntUVSet ].m_pUV->Lock( 0, 0, (void**)&pVertexBufferTexture, 0 );

			// UV���W�����擾
			float*	pUV = nullptr;		// UV���W���
			pUV = new float[ numUV * 2 ];
			if( pUV == nullptr )
			{
				return 1;
			}
			file.Read( pUV, numUV * 2 );

			// ���_���W�̐ݒ�
			for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
			{
				unsigned long	indexUV;		// UV���W�ԍ�
				file.Read( &indexUV );
				pVertexBufferTexture[ cntVertex ].textureU = pUV[ indexUV * 2 + 0 ];
				pVertexBufferTexture[ cntVertex ].textureV = 1.0f - pUV[ indexUV * 2 + 1 ];
			}

			// �d�݂̎擾
			file.Read( &m_pSkinMesh->m_pMesh[ cntMesh ].m_pUVSet[ cntUVSet ].m_weight );

			// ���_���̔j��
			delete[] pUV;
			pUV = nullptr;

			// UV���W�o�b�t�@�X�V�I��
			m_pSkinMesh->m_pMesh[ cntMesh ].m_pUVSet[ cntUVSet ].m_pUV->Unlock();
		}

		// ���_�J���[�Z�b�g���̎擾
		for( unsigned long cntColorSet = 0; cntColorSet < numColorSet; ++cntColorSet )
		{
			// ���_�J���[�Z�b�g�̏����擾
			unsigned long	numColor;		// ���_�J���[��
			file.Read( &numColor );

			// ���_�J���[�����擾
			float*	pColor = nullptr;		// ���_�J���[���
			pColor = new float[ numTexture * 4 ];
			if( pColor == nullptr )
			{
				return 1;
			}
			file.Read( pColor, numColor * 4 );

			// ���_�J���[�̐ݒ�
			for( unsigned long cntVertex = 0; cntVertex < numVertex; ++cntVertex )
			{
				unsigned long	indexColor;		// ���_�J���[�ԍ�
				file.Read( &indexColor );
			}

			// ���_�J���[���̔j��
			delete[] pColor;
			pColor = nullptr;
		}

		// �}�e���A�����̎擾
		float	transparent;		// ���ߓx
		float	reflection;			// ���˗�
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

	// �{�[�����̎擾
	for( unsigned long cntBone = 0; cntBone < numBone; ++cntBone )
	{
		D3DXMatrixIdentity( &m_pSkinMesh->m_pMatrixBone[ cntBone ] );
		file.Read( &m_pSkinMesh->m_pMatrixBone[ cntBone ]._11, 3 );
		file.Read( &m_pSkinMesh->m_pMatrixBone[ cntBone ]._21, 3 );
		file.Read( &m_pSkinMesh->m_pMatrixBone[ cntBone ]._31, 3 );
		file.Read( &m_pSkinMesh->m_pMatrixBone[ cntBone ]._41, 3 );
	}

	// �e�N�X�`���o�b�t�@�̊J��
	delete[] pIndexTexture;
	pIndexTexture = nullptr;
#endif
	// ����I��
	return 0;
}
