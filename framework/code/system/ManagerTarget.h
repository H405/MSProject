//==============================================================================
//
// File   : ManagerTarget.h
// Brief  : ターゲット管理オブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_MANAGER_TARGET_H
#define MY_MANAGER_TARGET_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "target/Target.h"
#include <stdio.h>

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************
#define TARGET_MAX (16)

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Target;
class Effect;
class EffectParameter;
class Texture;


//******************************************************************************
// クラス定義
//******************************************************************************
class ManagerTarget
{
public:
	enum
	{
		STATE_NORMAL = 0,
		STATE_MAX
	}STATE;

	typedef struct
	{
		char name[256];
		int appearTime;
		D3DXVECTOR3 appearPos;
		COLOR_STATE colorState;
	}TARGET_APPEAR_DATA;

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ManagerTarget( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ManagerTarget( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize(
		IDirect3DDevice9* pDevice,
		const EffectParameter* pParameter,
		Effect* pEffectGeneral,
		Texture* pTextureCross,
		Texture* pTextureArrow,
		Texture* pTextureCircle
	);

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update(int* _table , int* _fireworksTableIndex);

	//==============================================================================
	// Brief  : ターゲット発射処理
	// Return : int									: 配列番号
	// Arg2   : D3DXVECTOR3							: 発生位置
	//==============================================================================
	int Add(D3DXVECTOR3 _pos, COLOR_STATE _colorState = COLOR_STATE_W);

	//==============================================================================
	// Brief  : インデックス取得処理
	// Return : int									: 使用可能なオブジェクトの番号（全部使用中の場合は負の値が返る）
	// Arg    : void								: なし
	//==============================================================================
	int GetIndex();

	//==============================================================================
	// Brief  : テーブルのソート処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Sort(int* _table, int _deleteIndex);

	//==============================================================================
	// Brief  : ターゲット生成スクリプト読み込み処理
	//==============================================================================
	void ReadTargetScriptFromFile(const char* _fileName);

	//==============================================================================
	// アクセサ
	//==============================================================================
	Target* getTarget(int _index){return &target[_index];}
	void setInvViewMatrix(D3DXMATRIX _invViewMatrix){invViewMatrix = _invViewMatrix;};

protected:

	//	ターゲットの配列
	Target* target;

	//	カメラの逆行列
	D3DXMATRIX invViewMatrix;

	//	ターゲットの自然消滅認識用フラグ
	bool enableOld[TARGET_MAX];

	TARGET_APPEAR_DATA* targetAppearData;
	int targetAppearDataMax;

	int targetAppearCount;
	int targetAppearIndex;

	//==============================================================================
	// Brief  : ターゲット生成スクリプト読み込み処理
	//==============================================================================
	void SkipComment(FILE* _fp);
	void Read_TIM_POS_COL(FILE* _fp, int _readDataIndex);
	void ReadAppearTargetMax(FILE* _fp);
	void SortAppearTargetData();
	void autoAppear(int* _table , int* _targetTableIndex);

private:
	void InitializeSelf( void );
	ManagerTarget( const ManagerTarget& );
	ManagerTarget operator=( const ManagerTarget& );
};

#endif	// MY_MANAGER_TARGET_H
