//==============================================================================
//
// File   : FireworksUI.h
// Brief  : �ԉ�UI�I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h�K�[�h
//******************************************************************************
#ifndef MY_FIREWORKSUI_H
#define MY_FIREWORKSUI_H

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "d3dx9.h"
#include "../target/Target.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N��
//******************************************************************************
#define FIREWORKS_UI_MAX (12)

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
class FireworksUI : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : �R���X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	FireworksUI( void );

	//==============================================================================
	// Brief  : �f�X�g���N�^
	// Return : 									: 
	// Arg    : void								: �Ȃ�
	//==============================================================================
	~FireworksUI( void );

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
	Texture* pFireworksUITex);

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
	void addPositionX(float _value){pos.x += _value;}
	void addPositionY(float _value){pos.y += _value;}
	COLOR_STATE getColorState(){return colorState;}
	void addRotColor();
	void subRotColor();

	void SetEnableGraphic(bool _flag);

protected:

	Object2D* fireworksUI;

	D3DXVECTOR3 pos;
	float rot;
	float addRot;

	COLOR_STATE colorState;
	int stateNum;
	int stateNumOld;
	bool moveFlag;
	int moveCount;

private:
	void InitializeSelf( void );
	FireworksUI( const FireworksUI& );
	FireworksUI operator=( const FireworksUI& );
};

#endif	// MY_FIREWORKSUI_H
