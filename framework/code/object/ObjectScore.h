//==============================================================================
//
// File   : ObjectScore.h
// Brief  : �X�R�A�p�|���S���I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/24 sat : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_OBJECT_SCORE_H
#define MY_OBJECT_SCORE_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../framework/object/ObjectMovement.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Effect;
class EffectParameter;
class Graphic2D;
class Object2D;
class Texture;

//******************************************************************************
// �N���X��`
//******************************************************************************
class ObjectScore
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	ObjectScore( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~ObjectScore( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	// Arg2   : int _figure							: ����
	//==============================================================================
	int Initialize( int priority , int _figure );

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �ď���������
	// Return : int									: ���s����
	// Arg    : int priority						: �X�V�D��x
	//==============================================================================
	int Reinitialize( int priority , int _figure );

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : �`��N���X�̐���
	// Return : int									: ���s����
	// Arg    : int priority						: �`��D��x
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : Texture* pTexture					: �e�N�X�`��
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture = nullptr );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void SetGraphic( Graphic2D* pValue );
	Graphic2D* GetGraphic( int num ) const;
	void SetColor( const D3DXCOLOR& value );
	void SetColor( float r, float g, float b, float a );
	void SetColor( float r, float g, float b );
	void SetColorR( float r );
	void SetColorG( float g );
	void SetColorB( float b );
	void SetColorA( float a );
	void SetColorAlpha( float alpha );
	void GetColor( D3DXCOLOR* pOut ) const;
	float GetColorR( void ) const;
	float GetColorG( void ) const;
	float GetColorB( void ) const;
	float GetColorA( void ) const;
	void AddColor( const D3DXCOLOR& value );
	void AddColor( float r, float g, float b, float a );
	void AddColor( float r, float g, float b );
	void AddColorR( float r );
	void AddColorG( float g );
	void AddColorB( float b );
	void AddColorA( float a );
	void AddColorAlpha( float alpha );

	void SetScore(int _value);
	void AddScore(int _value);
	int GetScore();
	void SetScoreFuture(int _value);
	void AddScoreFuture(int _value);
	int GetScoreFuture();

	void SetPos(float _x, float _y, float _z);
	void SetPos(const D3DXVECTOR3& _value);
	void SetPosX(float _x);
	void SetPosY(float _y);
	void SetPosZ(float _z);
	void SetSize(float _x, float _y, float _z);
	void SetSize(const D3DXVECTOR3& _value);
	void SetSizeX(float _x);
	void SetSizeY(float _y);
	void SetSizeZ(float _z);
	void AddPos(float _x, float _y, float _z);
	void AddPos( const D3DXVECTOR3& _value );
	void AddPosX(float _x);
	void AddPosY(float _y);
	void AddPosZ(float _z);
	void AddSize(float _x, float _y, float _z);
	void AddSize( const D3DXVECTOR3& _value );
	void AddSizeX(float _x);
	void AddSizeY(float _y);
	void AddSizeZ(float _z);
	void GetPos(D3DXVECTOR3* _out) const;
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	void GetSize(D3DXVECTOR3*_out) const;
	float GetSizeX();
	float GetSizeY();
	float GetSizeZ();

protected:
	D3DXCOLOR	color_;					// �F

	//	��ԍ��̌��̈ʒu���Z�b�g���Ă���
	D3DXVECTOR3 pos;
	//	�������̃T�C�Y
	D3DXVECTOR3 size;

	Object2D** number;

	//	����
	int figure;

	//	�X�R�A���ݒl
	int score;

	//	�X�R�A�ő�l
	int scoreMax;

	//	�X�R�A�����l
	int scoreFuture;

private:
	void InitializeSelf( void );
	ObjectScore( const ObjectScore& );
	ObjectScore operator=( const ObjectScore& );

	//==============================================================================
	// Brief  : �X�R�A�̒l�ɉ����ăe�N�X�`��UV�l�����肷��
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void desideScore();
};

#endif	// MY_OBJECT_SCORE_H
