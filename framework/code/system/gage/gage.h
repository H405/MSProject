//==============================================================================
//
// File   : Gage.h
// Brief  : �V���N���Q�[�W�I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_GAGE_H
#define MY_GAGE_H

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
#define GAGEBAR_MAX (25)

//******************************************************************************
// �N���X�O���錾
//******************************************************************************
class Object2D;
class Effect;
class EffectParameter;
class Texture;
class ObjectScore;

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "../../framework/object/ObjectMovement.h"

//******************************************************************************
// �N���X��`
//******************************************************************************
class Gage : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	Gage( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~Gage( void );

	//==============================================================================
	// Brief  : ����������
	// Return : int									: ���s����
	// Arg    : IDirect3DDevice9* pDevice			: Direct3D�f�o�C�X
	// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
	// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
	// Arg    : IDirect3DTexture9* pTexture			: �e�N�X�`��
	//==============================================================================
	int Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Effect* pEffectGeneral2,
	Texture* pGageBar,
	Texture* pGageBase,
	Texture* pGageBack,
	Texture* pGageScore);

	//==============================================================================
	// Brief  : �I������
	// Return : int									: ���s����
	// Arg    : void								: �Ȃ�
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : �X�V����
	// Return : void								: �Ȃ�
	// Arg    : void								: �Ȃ�
	//==============================================================================
	void Update( void );

	//==============================================================================
	// �A�N�Z�T
	//==============================================================================
	void setPosition(float _x, float _y, float _z);
	void setPercent(float _value){percent = _value;if(percent < 0.0f)percent = 0.0f;if(percent > 100.0f)percent = 100.0f;}
	void addPercent(float _value){percent += _value;if(percent < 0.0f)percent = 0.0f;if(percent > 100.0f)percent = 100.0f;}

	void setPercentFuture(float _value){percentFuture = _value;if(percentFuture < 0.0f)percentFuture = 0.0f;if(percentFuture > 100.0f)percentFuture = 100.0f;}
	void addPercentFuture(float _value){percentFuture += _value;if(percentFuture < 0.0f)percentFuture = 0.0f;if(percentFuture > 100.0f)percentFuture = 100.0f;}

protected:

	Object2D* gageBar;
	Object2D* gageBase;
	Object2D* gageBack;
	int gageBackCount;
	float gageBackAddSize;

	ObjectScore* gageScore;

	float percent;
	float percentFuture;
	int barNum;
	int barNumOld;

private:
	void InitializeSelf( void );
	Gage( const Gage& );
	Gage operator=( const Gage& );

	//	�X�V�֐��i�[�p�|�C���^
	void (Gage::*fpUpdate)(void);
};

#endif	// MY_GAGE_H
