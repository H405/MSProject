//==============================================================================
//
// File   : ObjectScore.h
// Brief  : スコア用ポリゴンオブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/24 sat : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectScore.h"
#include "Object2D.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/Graphic2D.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectScore::ObjectScore( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectScore::InitializeSelf( void )
{
	// メンバ変数の初期化
	color_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	score = 0;
	scoreMax = 0;
	scoreFuture = 0;
	figure = 0;
}
//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectScore::~ObjectScore( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
// Arg2   : int _figure							: 桁数
//==============================================================================
int ObjectScore::Initialize( int priority , int _figure )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	//	桁数設定
	figure = _figure;

	//	スコアの最大値設定
	int temp = 1;
	for (int figureCount = figure - 1; figureCount > 0; figureCount--)
	{
		temp *= 10;
	}
	scoreMax = temp * 10;

	//	桁数分だけオブジェクト生成
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

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ObjectScore::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果

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


	// 基本クラスの処理
	result = Object::Finalize();
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
// Arg    : int priority						: 更新優先度
// Arg2   : int _figure							: 桁数
//==============================================================================
int ObjectScore::Reinitialize( int priority , int _figure )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority , _figure);
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectScore::Update( void )
{
	bool tempFlag = false;

	//	スコア値加算
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

	//	最大値と最小値のまるめ
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

	//	スコアが変動したらテクスチャ座標変更
	if(tempFlag == true)
		desideScore();
}

//==============================================================================
// Brief  : 描画クラスの生成
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : Texture* pTexture					: テクスチャ
//==============================================================================
int ObjectScore::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture )
{
	// グラフィックの生成
	int					result;				// 実行結果
	IDirect3DTexture9*	pTextureSet;		// 設定するテクスチャ
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}

	for(int count = 0;count < figure;count++)
	{
		//	ポリゴン分割数(数字でしか使う予定無いから10にしておく)
		number[count]->SetScaleTexture(10.0f, 1.0f);

		result = number[count]->CreateGraphic(
			priority,
			pParameter,
			pEffectGeneral,
			pTexture);

		//	サイズ取得
		number[count]->GetScale(&size);

		//	位置をずらす
		number[count]->SetPositionX(pos.x + (size.x * count));

		if(result == 1)
			return 1;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画クラスの設定
// Return : void								: なし
// Arg    : Graphic2D* pValue						: 設定する値
//==============================================================================
void ObjectScore::SetGraphic( Graphic2D* pValue )
{
	// 値の設定
	for(int count = 0; count < figure; count++)
	{
		// 値の設定
		number[count]->SetGraphic(pValue);
	}
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : Graphic2D*							: 返却する値
// Arg    : int									: 配列番号
//==============================================================================
Graphic2D* ObjectScore::GetGraphic( int num ) const
{
	// 値の返却
	return number[num]->GetGraphic();
}

//==============================================================================
// Brief  : 色の設定
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 設定する値
//==============================================================================
void ObjectScore::SetColor( const D3DXCOLOR& value )
{
	// 値の設定
	color_ = value;
	for(int count = 0;count < figure;count++)
		number[count]->SetColor(value);
}

//==============================================================================
// Brief  : 色のRGBA値の設定
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
// Arg    : float a								: A値
//==============================================================================
void ObjectScore::SetColor( float r, float g, float b, float a )
{
	// 値の設定
	color_.r = r;
	color_.g = g;
	color_.b = b;
	color_.a = a;
	for(int count = 0;count < figure;count++)
		number[count]->SetColor(r, g, b, a);
}

//==============================================================================
// Brief  : 色のRGB値の設定
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
//==============================================================================
void ObjectScore::SetColor( float r, float g, float b )
{
	// 値の設定
	color_.r = r;
	color_.g = g;
	color_.b = b;
	for(int count = 0;count < figure;count++)
		number[count]->SetColor(r, g, b);
}

//==============================================================================
// Brief  : 色のR値の設定
// Return : void								: なし
// Arg    : float r								: R値
//==============================================================================
void ObjectScore::SetColorR( float r )
{
	// 値の設定
	color_.r = r;
	for(int count = 0;count < figure;count++)
		number[count]->SetColorR(r);
}

//==============================================================================
// Brief  : 色のG値の設定
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void ObjectScore::SetColorG( float g )
{
	// 値の設定
	color_.g = g;
	for(int count = 0;count < figure;count++)
		number[count]->SetColorG(g);
}

//==============================================================================
// Brief  : 色のB値の設定
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void ObjectScore::SetColorB( float b )
{
	// 値の設定
	color_.b = b;
	for(int count = 0;count < figure;count++)
		number[count]->SetColorB(b);
}

//==============================================================================
// Brief  : 色のA値の設定
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void ObjectScore::SetColorA( float a )
{
	// 値の設定
	color_.a = a;
	for(int count = 0;count < figure;count++)
		number[count]->SetColorA(a);
}

//==============================================================================
// Brief  : 色のアルファ値の設定
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void ObjectScore::SetColorAlpha( float alpha )
{
	// 値の設定
	color_.a = alpha;
	for(int count = 0;count < figure;count++)
		number[count]->SetColorAlpha(alpha);
}

//==============================================================================
// Brief  : 色の取得
// Return : void								: なし
// Arg    : D3DXCOLOR* pOut						: 値の格納アドレス
//==============================================================================
void ObjectScore::GetColor( D3DXCOLOR* pOut ) const
{
	// 値の返却
	*pOut = color_;
}

//==============================================================================
// Brief  : 色のR値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectScore::GetColorR( void ) const
{
	// 値の返却
	return color_.r;
}

//==============================================================================
// Brief  : 色のG値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectScore::GetColorG( void ) const
{
	// 値の返却
	return color_.g;
}

//==============================================================================
// Brief  : 色のB値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectScore::GetColorB( void ) const
{
	// 値の返却
	return color_.b;
}

//==============================================================================
// Brief  : 色のA値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectScore::GetColorA( void ) const
{
	// 値の返却
	return color_.a;
}

//==============================================================================
// Brief  : 色の加算
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 加算する値
//==============================================================================
void ObjectScore::AddColor( const D3DXCOLOR& value )
{
	// 値の加算
	color_ += value;
	for(int count = 0;count < figure;count++)
		number[count]->AddColor(value);
}

//==============================================================================
// Brief  : 色のRGBA値の加算
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
// Arg    : float a								: A値
//==============================================================================
void ObjectScore::AddColor( float r, float g, float b, float a )
{
	// 値の加算
	color_.r += r;
	color_.g += g;
	color_.b += b;
	color_.a += a;
	for(int count = 0;count < figure;count++)
		number[count]->AddColor(r, g, b, a);
}

//==============================================================================
// Brief  : 色のRGB値の加算
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
//==============================================================================
void ObjectScore::AddColor( float r, float g, float b )
{
	// 値の加算
	color_.r += r;
	color_.g += g;
	color_.b += b;
	for(int count = 0;count < figure;count++)
		number[count]->AddColor(r, g, b);
}

//==============================================================================
// Brief  : 色のR値の加算
// Return : void								: なし
// Arg    : float r								: R値
//==============================================================================
void ObjectScore::AddColorR( float r )
{
	// 値の加算
	color_.r += r;
	for(int count = 0;count < figure;count++)
		number[count]->AddColorR(r);
}

//==============================================================================
// Brief  : 色のG値の加算
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void ObjectScore::AddColorG( float g )
{
	// 値の加算
	color_.g += g;
	for(int count = 0;count < figure;count++)
		number[count]->AddColorG(g);
}

//==============================================================================
// Brief  : 色のB値の加算
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void ObjectScore::AddColorB( float b )
{
	// 値の加算
	color_.b += b;
	for(int count = 0;count < figure;count++)
		number[count]->AddColorB(b);
}

//==============================================================================
// Brief  : 色のA値の加算
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void ObjectScore::AddColorA( float a )
{
	// 値の加算
	color_.a += a;
	for(int count = 0;count < figure;count++)
		number[count]->AddColorA(a);
}

//==============================================================================
// Brief  : 色のアルファ値の加算
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void ObjectScore::AddColorAlpha( float alpha )
{
	// 値の加算
	color_.a += alpha;
	for(int count = 0;count < figure;count++)
		number[count]->AddColorAlpha(alpha);
}
//==============================================================================
// Brief  : スコア現在値の設定
// Return : void								: なし
// Arg    : int _value							: スコア現在値
//==============================================================================
void ObjectScore::SetScore(int _value)
{
	score = _value;
	desideScore();
}
//==============================================================================
// Brief  : スコア現在値の加算
// Return : void								: なし
// Arg    : int _value							: 加算値
//==============================================================================
void ObjectScore::AddScore(int _value)
{
	score += _value;
	desideScore();
}
//==============================================================================
// Brief  : スコア未来値の設定
// Return : void								: なし
// Arg    : int _value							: スコア未来値
//==============================================================================
void ObjectScore::SetScoreFuture(int _value)
{
	scoreFuture = _value;
}
//==============================================================================
// Brief  : スコア未来値の加算
// Return : void								: なし
// Arg    : int _value							: 加算値
//==============================================================================
void ObjectScore::AddScoreFuture(int _value)
{
	scoreFuture += _value;
}
//==============================================================================
// Brief  : スコア現在値の設定
// Return : int score								: スコア現在値
// Arg    : なし									: 
//==============================================================================
int ObjectScore::GetScore()
{
	return score;
}
//==============================================================================
// Brief  : スコア未来値の取得
// Return : int score								: スコア未来値
// Arg    : なし									: 
//==============================================================================
int ObjectScore::GetScoreFuture()
{
	return scoreFuture;
}
//==============================================================================
// Brief  : 位置の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
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
// Brief  : 位置の設定
// Return : void								: なし
// Arg    : D3DXVECTOR3 _value					: 設定する値
//==============================================================================
void ObjectScore::SetPos(const D3DXVECTOR3& _value)
{
	pos = _value;

	for(int count = 0;count < figure;count++)
		number[count]->SetPosition(pos.x + (size.x * count), pos.y, pos.z);
}
//==============================================================================
// Brief  : 位置Xの設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void ObjectScore::SetPosX(float _x)
{
	pos.x = _x;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionX(_x + (size.x * count));
}
//==============================================================================
// Brief  : 位置Yの設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void ObjectScore::SetPosY(float _y)
{
	pos.y = _y;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionY(_y);
}
//==============================================================================
// Brief  : 位置Zの設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void ObjectScore::SetPosZ(float _z)
{
	pos.z = _z;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionZ(_z);
}
//==============================================================================
// Brief  : サイズの設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
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
// Brief  : サイズの設定
// Return : void								: なし
// Arg    : D3DXVECTOR3 _value					: 設定する値
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
// Brief  : サイズXの設定
// Return : void								: なし
// Arg    : float x								: X値
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
// Brief  : サイズYの設定
// Return : void								: なし
// Arg    : float y								: Y値
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
// Brief  : サイズZの設定
// Return : void								: なし
// Arg    : float z								: Z値
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
// Brief  : 位置の加算
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
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
// Brief  : 位置の加算
// Return : void								: なし
// Arg    : D3DXVECTOR3 _value					: 設定する値
//==============================================================================
void ObjectScore::AddPos( const D3DXVECTOR3& _value )
{
	pos = _value;

	for(int count = 0;count < figure;count++)
		number[count]->SetPosition(pos.x + (size.x * count), pos.y, pos.z);
}
//==============================================================================
// Brief  : 位置Xの加算
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void ObjectScore::AddPosX(float _x)
{
	pos.x += _x;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionX(pos.x + (size.x * count));
}
//==============================================================================
// Brief  : 位置Yの加算
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void ObjectScore::AddPosY(float _y)
{
	pos.y += _y;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionY(pos.y);
}
//==============================================================================
// Brief  : 位置Zの加算
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void ObjectScore::AddPosZ(float _z)
{
	pos.z += _z;

	for(int count = 0;count < figure;count++)
		number[count]->SetPositionZ(pos.z);
}
//==============================================================================
// Brief  : サイズの加算
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
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
// Brief  : サイズの加算
// Return : void								: なし
// Arg    : D3DXVECTOR3 _value					: 加算する値
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
// Brief  : サイズXの加算
// Return : void								: なし
// Arg    : float x								: X値
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
// Brief  : サイズYの加算
// Return : void								: なし
// Arg    : float y								: Y値
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
// Brief  : サイズZの加算
// Return : void								: なし
// Arg    : float z								: Z値
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
// Brief  : 位置Xの取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* _out					: 値の格納アドレス
//==============================================================================
void ObjectScore::GetPos(D3DXVECTOR3* _out) const
{
	*_out = pos;
}
//==============================================================================
// Brief  : 位置Xの取得
// Return : int									: X値
// Arg    : void								: なし
//==============================================================================
float ObjectScore::GetPosX()
{
	return pos.x;
}
//==============================================================================
// Brief  : 位置Yの取得
// Return : int									: X値
// Arg    : void								: なし
//==============================================================================
float ObjectScore::GetPosY()
{
	return pos.y;
}
//==============================================================================
// Brief  : 位置Zの取得
// Return : int									: X値
// Arg    : void								: なし
//==============================================================================
float ObjectScore::GetPosZ()
{
	return pos.z;
}
//==============================================================================
// Brief  : 位置Zの取得
// Return : int									: X値
// Arg    : なし								: なし
//==============================================================================
void ObjectScore::GetSize(D3DXVECTOR3*_out) const
{
	*_out = size;
}
//==============================================================================
// Brief  : サイズXの取得
// Return : int									: X値
// Arg    : void								: なし
//==============================================================================
float ObjectScore::GetSizeX()
{
	return size.x;
}
//==============================================================================
// Brief  : サイズYの取得
// Return : int									: Y値
// Arg    : void								: なし
//==============================================================================
float ObjectScore::GetSizeY()
{
	return size.y;
}
//==============================================================================
// Brief  : サイズZの取得
// Return : int									: Z値
// Arg    : void								: なし
//==============================================================================
float ObjectScore::GetSizeZ()
{
	return size.z;
}
//==============================================================================
// Brief  : スコアの値に応じてテクスチャUV値を決定する
// Return : void								: なし
// Arg    : void								: なし
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
