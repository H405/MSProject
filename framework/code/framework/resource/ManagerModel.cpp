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
#include "ModelConvert.h"
#include "ModelX.h"
#include "Texture.h"
#include "../graphic/Material.h"
#include "../system/File.h"
#include "../vertex/Vertex.h"
#include "../vertex/VertexBuffer.h"

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
	// �t�@�C���̓ǂݍ���
	File	file;
	file.Initialize( pPath );

	// �t�@�C���̎�ނ��m�F
	if( !file.IsType( _T( "SKN3" ) ) )
	{
		TCHAR	pStringError[ 256 ];		// �G���[���b�Z�[�W
		sprintf_s( pStringError, 256, _T( "�t�@�C��\"%s\"��������܂���B" ), pPath );
		MessageBox( nullptr, &pStringError[ 0 ], _T( "�G���[" ), MB_OK );
		return 1;
	}

	// �e�N�X�`�����̓ǂݍ���
	unsigned long	countTexture = 0;				// �e�N�X�`����
	unsigned long	sizeBufferTexture = 0;			// �e�N�X�`���o�b�t�@�T�C�Y
	char*			pBufferTexture = nullptr;		// �e�N�X�`���o�b�t�@
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

	// �e�N�X�`���̓ǂݍ���
	int*	pIndexTexture = nullptr;	// �e�N�X�`���ԍ�
	if( sizeBufferTexture > 0 )
	{
		unsigned long	indexTextureCurrent = 0;		// ���݂̃e�N�X�`���ԍ�
		TCHAR			pNameTexture[ _MAX_PATH ];		// �e�N�X�`���t�@�C����

		// �e�N�X�`���ԍ��i�[�̈�̊m��
		pIndexTexture = new int[ countTexture ];
		if( pIndexTexture == nullptr )
		{
			return 1;
		}

		// �ǂݍ���
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

	// �e�N�X�`�����o�b�t�@�̊J��
	delete[] pBufferTexture;
	pBufferTexture = nullptr;

	// �X�L�����b�V�����̎擾
	unsigned long	countMesh;		// ���b�V����
	unsigned long	countBone;		// �{�[����
	file.Read( &countMesh );
	file.Read( &countBone );

	// ���_���̐���
	int		result;		// ���s����
	Vertex	vertex;		// ���_���
	result = vertex.Initialize( pDevice_, Vertex::ELEMENT_SET_SKIN );
	if( result != 0 )
	{
		return result;
	}

	// ���_�o�b�t�@�̐���
	VertexBuffer*	pVertexBuffer = nullptr;		// ���_�o�b�t�@
	pVertexBuffer = new VertexBuffer[ countMesh ];
	if( pVertexBuffer == nullptr )
	{
		return 1;
	}

	// �}�e���A�����i�[�o�b�t�@�̊m��
	Material*	pMaterial = nullptr;			// �}�e���A�����
	int*		pIndexMaterial = nullptr;		// �}�e���A���ԍ�
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

	// �e�N�X�`�����i�[�o�b�t�@�̊m��
	IDirect3DTexture9**	ppTexture = nullptr;			// �e�N�X�`�����
	int*				pIndexTextureSet = nullptr;		// �e�N�X�`���ԍ�
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

	// ���b�V���̒��_���i�[�o�b�t�@�̊m��
	int*	pCountVertex = nullptr;		// ���b�V���̒��_��
	pCountVertex = new int[ countMesh ];
	if( pCountVertex == nullptr )
	{
		return 1;
	}
	for( unsigned int counterMesh = 0; counterMesh < countMesh; ++counterMesh )
	{
		pCountVertex[ counterMesh ] = 0;
	}

	// ���b�V�����̎擾
	for( unsigned long counterMesh = 0; counterMesh < countMesh; ++counterMesh )
	{
		// ���̏����擾
		unsigned long	countVertex;		// ���_��
		unsigned long	countCoord;			// ���W��
		unsigned long	countNormal;		// �@����
		unsigned long	countUVSet;			// UV�Z�b�g��
		unsigned long	countColorSet;		// ���_�J���[��
		unsigned long	countBlend;			// �u�����h��
		file.Read( &countVertex );
		file.Read( &countCoord );
		file.Read( &countNormal );
		file.Read( &countUVSet );
		file.Read( &countColorSet );
		file.Read( &countBlend );

		// ���_�o�b�t�@�ɏ���ݒ�
		pVertexBuffer[ counterMesh ].Initialize( countVertex, &vertex );

		// ���_���̕ۑ�
		pCountVertex[ counterMesh ] = countVertex;

		// ���W�����擾
		float*	pCoord = nullptr;		// ���W���
		pCoord = new float[ countCoord * 3 ];
		if( pCoord == nullptr )
		{
			return 1;
		}
		file.Read( pCoord, countCoord * 3 );

		// ���W�̐ݒ�
		for( unsigned long counterVertex = 0; counterVertex < countVertex; ++counterVertex )
		{
			unsigned long	indexCoord;		// ���W�ԍ�
			file.Read( &indexCoord );
			pVertexBuffer[ counterMesh ].SetPosition( counterVertex, pCoord[ indexCoord * 3 + 0 ], pCoord[ indexCoord * 3 + 1 ], pCoord[ indexCoord * 3 + 2 ] );
		}

		// ���W���̔j��
		delete[] pCoord;
		pCoord = nullptr;

		// �@�������擾
		float*	pNormal = nullptr;		// �@�����
		pNormal = new float[ countNormal * 3 ];
		if( pNormal == nullptr )
		{
			return 1;
		}
		file.Read( pNormal, countNormal * 3 );

		// �@���̐ݒ�
		for( unsigned long counterVertex = 0; counterVertex < countVertex; ++counterVertex )
		{
			unsigned long	indexNormal;		// �@���ԍ�
			file.Read( &indexNormal );
			pVertexBuffer[ counterMesh ].SetNormal( counterVertex, pNormal[ indexNormal * 3 + 0 ], pNormal[ indexNormal * 3 + 1 ], pNormal[ indexNormal * 3 + 2 ] );

		}

		// �@�����̔j��
		delete[] pNormal;
		pNormal = nullptr;

		// �u�����h�����擾
		float*			pBlendWeight = nullptr;		// �u�����h�d�ݏ��
		unsigned char*	pBlendIndex = nullptr;		// �u�����h�{�[���ԍ����
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

		// �u�����h�̐ݒ�
		for( unsigned long counterVertex = 0; counterVertex < countVertex; ++counterVertex )
		{
			unsigned long	indexBlend;		// �u�����h�ԍ�
			file.Read( &indexBlend );
			pVertexBuffer[ counterMesh ].SetBlendWeight( counterVertex,
				pBlendWeight[ indexBlend * 3 + 0 ], pBlendWeight[ indexBlend * 3 + 1 ], pBlendWeight[ indexBlend * 3 + 2 ] );
			pVertexBuffer[ counterMesh ].SetBlendIndecies( counterVertex,
				pBlendIndex[ indexBlend * 4 + 0 ], pBlendIndex[ indexBlend * 4 + 1 ],
				pBlendIndex[ indexBlend * 4 + 2 ], pBlendIndex[ indexBlend * 4 + 3 ] );
		}

		// �u�����h���̔j��
		delete[] pBlendWeight;
		pBlendWeight = nullptr;
		delete[] pBlendIndex;
		pBlendIndex = nullptr;

		// UV�Z�b�g���̎擾
		for( unsigned long counterUVSet = 0; counterUVSet < countUVSet; ++counterUVSet )
		{
			// UV�Z�b�g�̏����擾
			long			indexTexture;					// �e�N�X�`���ԍ�
			unsigned long	typeUVset;						// UV�Z�b�g�̎��
			unsigned long	countUV;						// UV��
			Texture*		pTextureUVset = nullptr;		// �e�N�X�`��
			file.Read( &indexTexture );
			file.Read( &typeUVset );
			file.Read( &countUV );

			// �e�N�X�`���ԍ���ۑ�
			if( counterUVSet == 0 )
			{
				pIndexTextureSet[ counterMesh ] = indexTexture;
			}

			// UV���W�����擾
			float*	pUV = nullptr;		// UV���W���
			pUV = new float[ countUV * 2 ];
			if( pUV == nullptr )
			{
				return 1;
			}
			file.Read( pUV, countUV * 2 );

			// UV���W�̐ݒ�
			for( unsigned long counterVertex = 0; counterVertex < countVertex; ++counterVertex )
			{
				unsigned long	indexUV;		// UV���W�ԍ�
				file.Read( &indexUV );
				if( counterUVSet == 0 )
				{
					pVertexBuffer[ counterMesh ].SetTextureCoord0( counterVertex, pUV[ indexUV * 2 + 0 ], 1.0f - pUV[ indexUV * 2 + 1 ] );
				}
			}

			// �d�݂̎擾
			float	weight;
			file.Read( &weight );

			// ���_���̔j��
			delete[] pUV;
			pUV = nullptr;
		}

		// ���_�J���[�Z�b�g���̎擾
		for( unsigned long cntColorSet = 0; cntColorSet < countColorSet; ++cntColorSet )
		{
			// ���_�J���[�Z�b�g�̏����擾
			unsigned long	countColor;		// ���_�J���[��
			file.Read( &countColor );

			// ���_�J���[�����擾
			float*	pColor = nullptr;		// ���_�J���[���
			pColor = new float[ countTexture * 4 ];
			if( pColor == nullptr )
			{
				return 1;
			}
			file.Read( pColor, countColor * 4 );

			// ���_�J���[�̐ݒ�
			for( unsigned long counterVertex = 0; counterVertex < countVertex; ++counterVertex )
			{
				unsigned long	indexColor;		// ���_�J���[�ԍ�
				file.Read( &indexColor );
			}

			// ���_�J���[���̔j��
			delete[] pColor;
			pColor = nullptr;
		}

		// �}�e���A�����̎擾
		Material	material;			// �}�e���A��
		D3DXCOLOR	emissive;			// �G�~�b�V�u�F
		float		transparent;		// ���ߓx
		float		reflection;			// ���˗�
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

	// �{�[�����̎擾
	D3DXMATRIX*	pMatrixBone = nullptr;		// �{�[�������p���s��
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

	// ���f���̐���
	ModelConvert*	pModel = nullptr;				// ���f��
	void**			ppVertexBuffer = nullptr;		// ���_���
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

	// �{�[�����i�[�o�b�t�@�̊J��
	delete[] pMatrixBone;
	pMatrixBone = nullptr;

	// ���b�V���̒��_���i�[�o�b�t�@�̊J��
	delete[] ppVertexBuffer;
	ppVertexBuffer = nullptr;
	delete[] pCountVertex;
	pCountVertex = nullptr;

	// �e�N�X�`�����i�[�o�b�t�@�̊J��
	delete[] pIndexTextureSet;
	pIndexTextureSet = nullptr;
	delete[] ppTexture;
	ppTexture = nullptr;

	// �}�e���A�����i�[�o�b�t�@�̊J��
	delete[] pIndexMaterial;
	pIndexMaterial = nullptr;
	delete[] pMaterial;
	pMaterial = nullptr;

	// ���_�o�b�t�@�̊J��
	delete[] pVertexBuffer;
	pVertexBuffer = nullptr;

	// �e�N�X�`���o�b�t�@�̊J��
	delete[] pIndexTexture;
	pIndexTexture = nullptr;

	// ����I��
	return 0;
}
