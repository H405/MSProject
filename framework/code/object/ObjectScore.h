//==============================================================================
//
// File   : ObjectScore.h
// Brief  : スコア用ポリゴンオブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/24 sat : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_SCORE_H
#define MY_OBJECT_SCORE_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../framework/object/ObjectMovement.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Effect;
class EffectParameter;
class Graphic2D;
class Object2D;
class Texture;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectScore
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectScore( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectScore( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	// Arg2   : int _figure							: 桁数
	//==============================================================================
	int Initialize( int priority , int _figure );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	//==============================================================================
	int Reinitialize( int priority , int _figure );

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : 描画クラスの生成
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : Texture* pTexture					: テクスチャ
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture = nullptr );

	//==============================================================================
	// アクセサ
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
	D3DXCOLOR	color_;					// 色

	//	一番左の桁の位置をセットしていく
	D3DXVECTOR3 pos;
	//	数字一つ一つのサイズ
	D3DXVECTOR3 size;

	Object2D** number;

	//	桁数
	int figure;

	//	スコア現在値
	int score;

	//	スコア最大値
	int scoreMax;

	//	スコア未来値
	int scoreFuture;

private:
	void InitializeSelf( void );
	ObjectScore( const ObjectScore& );
	ObjectScore operator=( const ObjectScore& );

	//==============================================================================
	// Brief  : スコアの値に応じてテクスチャUV値を決定する
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void desideScore();
};

#endif	// MY_OBJECT_SCORE_H
