//==============================================================================
//
// File   : ObjectScore.h
// Brief  : �X�R�A�p�|���S���I�u�W�F�N�g�N���X
// Author : Kotaro Nagasaki
// Date   : 2015/10/24 sat : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// �C���N���[�h
//******************************************************************************
#include "ObjectScore.h"
#include "Object2D.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/Graphic2D.h"

//******************************************************************************
// ���C�u����
//******************************************************************************

//******************************************************************************
// �}�N����`
//******************************************************************************

//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************

//==============================================================================
// Brief  : �R���X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectScore::ObjectScore( void ) : ObjectMovement()
{
	// �N���X���̏���������
	InitializeSelf();
}
//==============================================================================
// Brief  : �N���X���̏���������
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectScore::InitializeSelf( void )
{
	// �����o�ϐ��̏�����
	color_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	score = 0;
	scoreMax = 0;
	scoreFuture = 0;
	figure = 0;
}
//==============================================================================
// Brief  : �f�X�g���N�^
// Return : 									: 
// Arg    : void								: �Ȃ�
//==============================================================================
ObjectScore::~ObjectScore( void )
{
	// �I������
	Finalize();
}

//==============================================================================
// Brief  : ����������
// Return : int									: ���s����
// Arg    : int priority						: �X�V�D��x
// Arg2   : int _figure							: ����
//==============================================================================
int ObjectScore::Initialize( int priority , int _figure )
{
	// ��{�N���X�̏���
	int		result;		// ���s����
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	//	�����ݒ�
	figure = _figure;

	//	�X�R�A�̍ő�l�ݒ�
	int temp = 1;
	for (int figureCount = figure - 1; figureCount > 0; figureCount--)
	{
		temp *= 10;
	}
	scoreMax = temp * 10;

	//	�����������I�u�W�F�N�g����
	number = new Object2D*[figure];
	for(int count = 0;count < figure;count++)
	{
		number[count] = new Object2D;
		result = number[count]->Initialize(priority);

		if( result != 0 )
		{
			return result;
		}
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �I������
// Return : int									: ���s����
// Arg    : void								: �Ȃ�
//==============================================================================
int ObjectScore::Finalize( void )
{
	// ��{�N���X�̏���
	int		result;		// ���s����

	for(int count = 0;count < figure;count++)
	{
		result = number[count]->Finalize();

		if( result != 0 )
		{
			return result;
		}

		delete number[count];
	}

	delete[] number;


	// ��{�N���X�̏���
	result = Object::Finalize();
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
// Arg    : int priority						: �X�V�D��x
// Arg2   : int _figure							: ����
//==============================================================================
int ObjectScore::Reinitialize( int priority , int _figure )
{
	// �I������
	int		result;		// ���s����
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// ����������
	return Initialize( priority , _figure);
}

//==============================================================================
// Brief  : �X�V����
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectScore::Update( void )
{
	bool tempFlag = false;

	//	�X�R�A�l���Z
	if(score < scoreFuture)
	{
		score++;
		tempFlag = true;
	}
	else if(score > scoreFuture)
	{
		score--;
		tempFlag = true;
	}

	//	�ő�l�ƍŏ��l�̂܂��
	if (score >= scoreMax)
	{
		score = scoreMax - 1;
		tempFlag = true;
	}
	else if (score <= -1)
	{
		score = 0;
		tempFlag = true;
	}

	//	�X�R�A���ϓ�������e�N�X�`�����W�ύX
	if(tempFlag == true)
		desideScore();
}

//==============================================================================
// Brief  : �`��N���X�̐���
// Return : int									: ���s����
// Arg    : int priority						: �`��D��x
// Arg    : const EffectParameter* pParameter	: �G�t�F�N�g�p�����[�^
// Arg    : Effect* pEffectGeneral				: �ʏ�`��G�t�F�N�g
// Arg    : Texture* pTexture					: �e�N�X�`��
//==============================================================================
int ObjectScore::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture )
{
	// �O���t�B�b�N�̐���
	int					result;				// ���s����
	IDirect3DTexture9*	pTextureSet;		// �ݒ肷��e�N�X�`��
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}

	for(int count = 0;count < figure;count++)
	{
		//	�|���S��������(�����ł����g���\�薳������10�ɂ��Ă���)
		number[count]->SetScaleTexture(10.0f, 1.0f);

		result = number[count]->CreateGraphic(
			priority,
			pParameter,
			pEffectGeneral,
			pTexture);

		//	�T�C�Y�擾
		number[count]->GetScale(&size);

		//	�ʒu�����炷
		number[count]->SetPositionX(pos.x + (size.x * count));

		if(result == 1)
			return 1;
	}

	// ����I��
	return 0;
}

//==============================================================================
// Brief  : �`��N���X�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : Graphic2D* pValue						: �ݒ肷��l
//==============================================================================
void ObjectScore::SetGraphic( Graphic2D* pValue )
{
	// �l�̐ݒ�
	for(int count = 0; count < figure; count++)
	{
		// �l�̐ݒ�
		number[count]->SetGraphic(pValue);
	}
}

//==============================================================================
// Brief  : �`��N���X�̎擾
// Return : Graphic2D*							: �ԋp����l
// Arg    : int									: �z��ԍ�
//==============================================================================
Graphic2D* ObjectScore::GetGraphic( int num ) const
{
	// �l�̕ԋp
	return number[num]->GetGraphic();
}

//==============================================================================
// Brief  : �F�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: �ݒ肷��l
//==============================================================================
void ObjectScore::SetColor( const D3DXCOLOR& value )
{
	// �l�̐ݒ�
	color_ = value;
	for(int count = 0;count < figure;count++)
		number[count]->SetColor(value);
}

//==============================================================================
// Brief  : �F��RGBA�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void ObjectScore::SetColor( float r, float g, float b, float a )
{
	// �l�̐ݒ�
	color_.r = r;
	color_.g = g;
	color_.b = b;
	color_.a = a;
	for(int count = 0;count < figure;count++)
		number[count]->SetColor(r, g, b, a);
}

//==============================================================================
// Brief  : �F��RGB�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
//==============================================================================
void ObjectScore::SetColor( float r, float g, float b )
{
	// �l�̐ݒ�
	color_.r = r;
	color_.g = g;
	color_.b = b;
	for(int count = 0;count < figure;count++)
		number[count]->SetColor(r, g, b);
}

//==============================================================================
// Brief  : �F��R�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
//==============================================================================
void ObjectScore::SetColorR( float r )
{
	// �l�̐ݒ�
	color_.r = r;
	for(int count = 0;count < figure;count++)
		number[count]->SetColorR(r);
}

//==============================================================================
// Brief  : �F��G�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void ObjectScore::SetColorG( float g )
{
	// �l�̐ݒ�
	color_.g = g;
	for(int count = 0;count < figure;count++)
		number[count]->SetColorG(g);
}

//==============================================================================
// Brief  : �F��B�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void ObjectScore::SetColorB( float b )
{
	// �l�̐ݒ�
	color_.b = b;
	for(int count = 0;count < figure;count++)
		number[count]->SetColorB(b);
}

//==============================================================================
// Brief  : �F��A�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void ObjectScore::SetColorA( float a )
{
	// �l�̐ݒ�
	color_.a = a;
	for(int count = 0;count < figure;count++)
		number[count]->SetColorA(a);
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void ObjectScore::SetColorAlpha( float alpha )
{
	// �l�̐ݒ�
	color_.a = alpha;
	for(int count = 0;count < figure;count++)
		number[count]->SetColorAlpha(alpha);
}

//==============================================================================
// Brief  : �F�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXCOLOR* pOut						: �l�̊i�[�A�h���X
//==============================================================================
void ObjectScore::GetColor( D3DXCOLOR* pOut ) const
{
	// �l�̕ԋp
	*pOut = color_;
}

//==============================================================================
// Brief  : �F��R�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectScore::GetColorR( void ) const
{
	// �l�̕ԋp
	return color_.r;
}

//==============================================================================
// Brief  : �F��G�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectScore::GetColorG( void ) const
{
	// �l�̕ԋp
	return color_.g;
}

//==============================================================================
// Brief  : �F��B�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectScore::GetColorB( void ) const
{
	// �l�̕ԋp
	return color_.b;
}

//==============================================================================
// Brief  : �F��A�l�̎擾
// Return : float								: �ԋp����l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectScore::GetColorA( void ) const
{
	// �l�̕ԋp
	return color_.a;
}

//==============================================================================
// Brief  : �F�̉��Z
// Return : void								: �Ȃ�
// Arg    : const D3DXCOLOR& value				: ���Z����l
//==============================================================================
void ObjectScore::AddColor( const D3DXCOLOR& value )
{
	// �l�̉��Z
	color_ += value;
	for(int count = 0;count < figure;count++)
		number[count]->AddColor(value);
}

//==============================================================================
// Brief  : �F��RGBA�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
// Arg    : float a								: A�l
//==============================================================================
void ObjectScore::AddColor( float r, float g, float b, float a )
{
	// �l�̉��Z
	color_.r += r;
	color_.g += g;
	color_.b += b;
	color_.a += a;
	for(int count = 0;count < figure;count++)
		number[count]->AddColor(r, g, b, a);
}

//==============================================================================
// Brief  : �F��RGB�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
// Arg    : float g								: G�l
// Arg    : float b								: B�l
//==============================================================================
void ObjectScore::AddColor( float r, float g, float b )
{
	// �l�̉��Z
	color_.r += r;
	color_.g += g;
	color_.b += b;
	for(int count = 0;count < figure;count++)
		number[count]->AddColor(r, g, b);
}

//==============================================================================
// Brief  : �F��R�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float r								: R�l
//==============================================================================
void ObjectScore::AddColorR( float r )
{
	// �l�̉��Z
	color_.r += r;
	for(int count = 0;count < figure;count++)
		number[count]->AddColorR(r);
}

//==============================================================================
// Brief  : �F��G�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float g								: G�l
//==============================================================================
void ObjectScore::AddColorG( float g )
{
	// �l�̉��Z
	color_.g += g;
	for(int count = 0;count < figure;count++)
		number[count]->AddColorG(g);
}

//==============================================================================
// Brief  : �F��B�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float b								: B�l
//==============================================================================
void ObjectScore::AddColorB( float b )
{
	// �l�̉��Z
	color_.b += b;
	for(int count = 0;count < figure;count++)
		number[count]->AddColorB(b);
}

//==============================================================================
// Brief  : �F��A�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float a								: A�l
//==============================================================================
void ObjectScore::AddColorA( float a )
{
	// �l�̉��Z
	color_.a += a;
	for(int count = 0;count < figure;count++)
		number[count]->AddColorA(a);
}

//==============================================================================
// Brief  : �F�̃A���t�@�l�̉��Z
// Return : void								: �Ȃ�
// Arg    : float alpha							: �A���t�@�l
//==============================================================================
void ObjectScore::AddColorAlpha( float alpha )
{
	// �l�̉��Z
	color_.a += alpha;
	for(int count = 0;count < figure;count++)
		number[count]->AddColorAlpha(alpha);
}
//==============================================================================
// Brief  : �X�R�A���ݒl�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int _value							: �X�R�A���ݒl
//==============================================================================
void ObjectScore::SetScore(int _value)
{
	score = _value;
	desideScore();
}
//==============================================================================
// Brief  : �X�R�A���ݒl�̉��Z
// Return : void								: �Ȃ�
// Arg    : int _value							: ���Z�l
//==============================================================================
void ObjectScore::AddScore(int _value)
{
	score += _value;
	desideScore();
}
//==============================================================================
// Brief  : �X�R�A�����l�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : int _value							: �X�R�A�����l
//==============================================================================
void ObjectScore::SetScoreFuture(int _value)
{
	scoreFuture = _value;
}
//==============================================================================
// Brief  : �X�R�A�����l�̉��Z
// Return : void								: �Ȃ�
// Arg    : int _value							: ���Z�l
//==============================================================================
void ObjectScore::AddScoreFuture(int _value)
{
	scoreFuture += _value;
}
//==============================================================================
// Brief  : �X�R�A���ݒl�̐ݒ�
// Return : int score								: �X�R�A���ݒl
// Arg    : �Ȃ�									: 
//==============================================================================
int ObjectScore::GetScore()
{
	return score;
}
//==============================================================================
// Brief  : �X�R�A�����l�̎擾
// Return : int score								: �X�R�A�����l
// Arg    : �Ȃ�									: 
//==============================================================================
int ObjectScore::GetScoreFuture()
{
	return scoreFuture;
}
//==============================================================================
// Brief  : �ʒu�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void ObjectScore::SetPos(float _x, float _y, float _z)
{
	pos.x = _x;
	pos.y = _y;
	pos.z = _z;

	for(int count = 0;count < figure;count++)
		number[count]->SetPosition(_x + (size.x * count), _y, _z);
}
//==============================================================================
// Brief  : �ʒu�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3 _value					: �ݒ肷��l
//==============================================================================
void ObjectScore::SetPos(const D3DXVECTOR3& _value)
{
	pos = _value;

	for(int count = 0;count < figure;count++)
		number[count]->SetPosition(pos.x + (size.x * count), pos.y, pos.z);
}
//==============================================================================
// Brief  : �ʒuX�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectScore::SetPosX(float _x)
{
	pos.x = _x;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionX(_x + (size.x * count));
}
//==============================================================================
// Brief  : �ʒuY�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectScore::SetPosY(float _y)
{
	pos.y = _y;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionY(_y);
}
//==============================================================================
// Brief  : �ʒuZ�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void ObjectScore::SetPosZ(float _z)
{
	pos.z = _z;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionZ(_z);
}
//==============================================================================
// Brief  : �T�C�Y�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void ObjectScore::SetSize(float _x, float _y, float _z)
{
	size.x = _x;
	size.y = _y;
	size.z = _z;

	for(int count = 0;count < figure;count++)
	{
		number[count]->SetScale(_x, _y, _z);
		number[count]->SetPositionX(pos.x + (size.x * count));
	}
}
//==============================================================================
// Brief  : �T�C�Y�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3 _value					: �ݒ肷��l
//==============================================================================
void ObjectScore::SetSize(const D3DXVECTOR3& _value)
{
	size = _value;

	for(int count = 0;count < figure;count++)
	{
		number[count]->SetScale(size.x, size.y, size.z);
		number[count]->SetPositionX(pos.x + (size.x * count));
	}
}
//==============================================================================
// Brief  : �T�C�YX�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectScore::SetSizeX(float _x)
{
	size.x = _x;

	for(int count = 0;count < figure;count++)
	{
		number[count]->SetScaleX(size.x);
		number[count]->SetPositionX(pos.x + (size.x * count));
	}
}
//==============================================================================
// Brief  : �T�C�YY�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectScore::SetSizeY(float _y)
{
	size.y = _y;

	for(int count = 0;count < figure;count++)
	{
		number[count]->SetScaleY(size.y);
		number[count]->SetPositionY(pos.y);
	}
}
//==============================================================================
// Brief  : �T�C�YZ�̐ݒ�
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void ObjectScore::SetSizeZ(float _z)
{
	size.y = _z;

	for(int count = 0;count < figure;count++)
	{
		number[count]->SetScaleZ(size.z);
		number[count]->SetPositionZ(pos.z);
	}
}
//==============================================================================
// Brief  : �ʒu�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void ObjectScore::AddPos(float _x, float _y, float _z)
{
	pos.x += _x;
	pos.y += _y;
	pos.z += _z;

	for(int count = 0;count < figure;count++)
		number[count]->SetPosition(pos.x + (size.x * count), pos.y, pos.z);
}
//==============================================================================
// Brief  : �ʒu�̉��Z
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3 _value					: �ݒ肷��l
//==============================================================================
void ObjectScore::AddPos( const D3DXVECTOR3& _value )
{
	pos = _value;

	for(int count = 0;count < figure;count++)
		number[count]->SetPosition(pos.x + (size.x * count), pos.y, pos.z);
}
//==============================================================================
// Brief  : �ʒuX�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectScore::AddPosX(float _x)
{
	pos.x += _x;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionX(pos.x + (size.x * count));
}
//==============================================================================
// Brief  : �ʒuY�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectScore::AddPosY(float _y)
{
	pos.y += _y;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionY(pos.y);
}
//==============================================================================
// Brief  : �ʒuZ�̉��Z
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void ObjectScore::AddPosZ(float _z)
{
	pos.z += _z;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionZ(pos.z);
}
//==============================================================================
// Brief  : �T�C�Y�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
// Arg    : float y								: Y�l
// Arg    : float z								: Z�l
//==============================================================================
void ObjectScore::AddSize(float _x, float _y, float _z)
{
	size.x += _x;
	size.y += _y;
	size.z += _z;

	for(int count = 0;count < figure;count++)
	{
		number[count]->SetScale(size);
		number[count]->SetPosition(pos.x + (size.x * count), pos.y, pos.z);
	}
}
//==============================================================================
// Brief  : �T�C�Y�̉��Z
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3 _value					: ���Z����l
//==============================================================================
void ObjectScore::AddSize( const D3DXVECTOR3& _value )
{
	size += _value;

	for(int count = 0;count < figure;count++)
	{
		number[count]->SetScale(size);
		number[count]->SetPosition(pos.x + (size.x * count), pos.y, pos.z);
	}
}
//==============================================================================
// Brief  : �T�C�YX�̉��Z
// Return : void								: �Ȃ�
// Arg    : float x								: X�l
//==============================================================================
void ObjectScore::AddSizeX(float _x)
{
	size.x += _x;

	for(int count = 0;count < figure;count++)
	{
		number[count]->SetScaleX(size.x);
		number[count]->SetPositionX(pos.x + (size.x * count));
	}
}
//==============================================================================
// Brief  : �T�C�YY�̉��Z
// Return : void								: �Ȃ�
// Arg    : float y								: Y�l
//==============================================================================
void ObjectScore::AddSizeY(float _y)
{
	size.y += _y;

	for(int count = 0;count < figure;count++)
	{
		number[count]->SetScaleY(size.y);
		number[count]->SetPositionY(pos.y);
	}
}
//==============================================================================
// Brief  : �T�C�YZ�̉��Z
// Return : void								: �Ȃ�
// Arg    : float z								: Z�l
//==============================================================================
void ObjectScore::AddSizeZ(float _z)
{
	size.z += _z;

	for(int count = 0;count < figure;count++)
	{
		number[count]->SetScaleZ(size.z);
		number[count]->SetPositionZ(pos.z);
	}
}
//==============================================================================
// Brief  : �ʒuX�̎擾
// Return : void								: �Ȃ�
// Arg    : D3DXVECTOR3* _out					: �l�̊i�[�A�h���X
//==============================================================================
void ObjectScore::GetPos(D3DXVECTOR3* _out) const
{
	*_out = pos;
}
//==============================================================================
// Brief  : �ʒuX�̎擾
// Return : int									: X�l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectScore::GetPosX()
{
	return pos.x;
}
//==============================================================================
// Brief  : �ʒuY�̎擾
// Return : int									: X�l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectScore::GetPosY()
{
	return pos.y;
}
//==============================================================================
// Brief  : �ʒuZ�̎擾
// Return : int									: X�l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectScore::GetPosZ()
{
	return pos.z;
}
//==============================================================================
// Brief  : �ʒuZ�̎擾
// Return : int									: X�l
// Arg    : �Ȃ�								: �Ȃ�
//==============================================================================
void ObjectScore::GetSize(D3DXVECTOR3*_out) const
{
	*_out = size;
}
//==============================================================================
// Brief  : �T�C�YX�̎擾
// Return : int									: X�l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectScore::GetSizeX()
{
	return size.x;
}
//==============================================================================
// Brief  : �T�C�YY�̎擾
// Return : int									: Y�l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectScore::GetSizeY()
{
	return size.y;
}
//==============================================================================
// Brief  : �T�C�YZ�̎擾
// Return : int									: Z�l
// Arg    : void								: �Ȃ�
//==============================================================================
float ObjectScore::GetSizeZ()
{
	return size.z;
}
//==============================================================================
// Brief  : �X�R�A�̒l�ɉ����ăe�N�X�`��UV�l�����肷��
// Return : void								: �Ȃ�
// Arg    : void								: �Ȃ�
//==============================================================================
void ObjectScore::desideScore()
{
	for (int count = 0; count < figure; count++)
	{
		int nowFigure = 1;
		for (int figureCount = figure - 1; figureCount > count; figureCount--)
		{
			nowFigure *= 10;
		}

		int setScore;
		setScore = (score % (nowFigure * 10)) / nowFigure;

		number[count]->SetPositionTextureX(setScore * 0.1f);
	}
}
