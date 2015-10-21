//==============================================================================
//
// File   : VertexBuffer.h
// Brief  : ���_�o�b�t�@�֒l��ݒ肷�邽�߂̃o�b�t�@
// Author : Taiga Shirakawa
// Date   : 2015/10/14 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_VERTEX_BUFFER_H
#define MY_VERTEX_BUFFER_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "d3dx9.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Vertex;

//******************************************************************************
// �N���X��`
//******************************************************************************
class VertexBuffer
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	VertexBuffer( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~VertexBuffer( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int count							: �m�ۂ��鐔
	// Arg    : Vertex* pVertex						: ���_���
	//==============================================================================
	int Initialize( int count, Vertex* pVertex );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : int count							: �m�ۂ��鐔
	// Arg    : Vertex* pVertex						: ���_���
	//==============================================================================
	int Reinitialize( int count, Vertex* pVertex );

	//==============================================================================
	// Brief  : �N���X�̃R�s�[
	// Return : int									: ���s����
	// Arg    : VertexBuffer* pOut					: �R�s�[��A�h���X
	//==============================================================================
	int Copy( VertexBuffer* pOut ) const;

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void* GetBuffer( void ) const;

	void SetPosition( int index, const D3DXVECTOR3& value );
	void SetPosition( int index, float x, float y, float z );
	void SetPositionX( int index, float x );
	void SetPositionY( int index, float y );
	void SetPositionZ( int index, float z );
	void SetPositionTweening( int index, const D3DXVECTOR3& value );
	void SetPositionTweening( int index, float x, float y, float z );
	void SetPositionTweeningX( int index, float x );
	void SetPositionTweeningY( int index, float y );
	void SetPositionTweeningZ( int index, float z );
	void SetBlendWeight( int index, const D3DXVECTOR3& value );
	void SetBlendWeight( int index, float x, float y, float z );
	void SetBlendWeightX( int index, float x );
	void SetBlendWeightY( int index, float y );
	void SetBlendWeightZ( int index, float z );
	void SetBlendIndecies( int index, unsigned char value0, unsigned char value1, unsigned char value2, unsigned char value3 );
	void SetBlendIndecies0( int index, unsigned char value );
	void SetBlendIndecies1( int index, unsigned char value );
	void SetBlendIndecies2( int index, unsigned char value );
	void SetBlendIndecies3( int index, unsigned char value );
	void SetNormal( int index, const D3DXVECTOR3& value );
	void SetNormal( int index, float x, float y, float z );
	void SetNormalX( int index, float x );
	void SetNormalY( int index, float y );
	void SetNormalZ( int index, float z );
	void SetNormalTweening( int index, const D3DXVECTOR3& value );
	void SetNormalTweening( int index, float x, float y, float z );
	void SetNormalTweeningX( int index, float x );
	void SetNormalTweeningY( int index, float y );
	void SetNormalTweeningZ( int index, float z );
	void SetPointSize( int index, float value );
	void SetTextureCoord0( int index, const D3DXVECTOR2& value );
	void SetTextureCoord0( int index, float x, float y );
	void SetTextureCoord0X( int index, float x );
	void SetTextureCoord0Y( int index, float y );
	void SetTextureCoord1( int index, const D3DXVECTOR2& value );
	void SetTextureCoord1( int index, float x, float y );
	void SetTextureCoord1X( int index, float x );
	void SetTextureCoord1Y( int index, float y );
	void SetTextureCoord2( int index, const D3DXVECTOR2& value );
	void SetTextureCoord2( int index, float x, float y );
	void SetTextureCoord2X( int index, float x );
	void SetTextureCoord2Y( int index, float y );
	void SetTextureCoord3( int index, const D3DXVECTOR2& value );
	void SetTextureCoord3( int index, float x, float y );
	void SetTextureCoord3X( int index, float x );
	void SetTextureCoord3Y( int index, float y );
	void SetTangent( int index, const D3DXVECTOR3& value );
	void SetTangent( int index, float x, float y, float z );
	void SetTangentX( int index, float x );
	void SetTangentY( int index, float y );
	void SetTangentZ( int index, float z );
	void SetBinormal( int index, const D3DXVECTOR3& value );
	void SetBinormal( int index, float x, float y, float z );
	void SetBinormalX( int index, float x );
	void SetBinormalY( int index, float y );
	void SetBinormalZ( int index, float z );
	void SetTessellationFactor( int index, float value );
	void SetPositionTransform( int index, const D3DXVECTOR3& value );
	void SetPositionTransform( int index, float x, float y, float z );
	void SetPositionTransformX( int index, float x );
	void SetPositionTransformY( int index, float y );
	void SetPositionTransformZ( int index, float z );
	void SetColorDiffuse( int index, const D3DXCOLOR& value );
	void SetColorDiffuse( int index, float r, float g, float b, float a );
	void SetColorSpecular( int index, const D3DXCOLOR& value );
	void SetColorSpecular( int index, float r, float g, float b, float a );
	void SetFog( int index, float value );
	void SetDepth( int index, float value );
	void SetSampler( int index, float value );

protected:

private:
	void InitializeSelf( void );
	void SetToBuffer( int type, int index, void* pValue, size_t size, int offset = 0 );

	VertexBuffer( const VertexBuffer& );
	VertexBuffer operator=( const VertexBuffer& );

	char*			pBuffer_;		// �o�b�t�@
	unsigned int	size_;			// �o�b�t�@�T�C�Y
	Vertex*			pVertex_;		// ���_���
};

#endif	// MY_VERTEX_BUFFER_H
