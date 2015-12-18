//==============================================================================
//
// File   : ManagerTarget.cpp
// Brief  : ターゲット管理オブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerTarget.h"
#include "../framework/develop/Debug.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerTexture.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define _CRT_SECURE_NO_WARNINGS
//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ManagerTarget::ManagerTarget( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerTarget::InitializeSelf( void )
{
	// メンバ変数の初期化
	target = nullptr;
	targetAppearData = nullptr;
	targetAppearDataMax = 0;
	targetAppearCount = 0;
	targetAppearIndex = 0;

	for(int count = 0;count < TARGET_MAX;count++)
		enableOld[count] = false;
}
//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ManagerTarget::~ManagerTarget( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int ManagerTarget::Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Texture* pTextureCross,
	Texture* pTextureArrow,
	Texture* pTextureCircle
	)
{
	//	ターゲットを指定個数分用意
	target = new Target[TARGET_MAX];
	for(int count = 0;count < TARGET_MAX;count++)
	{
		target[count].Initialize(
			pDevice,
			pParameter,
			pEffectGeneral,
			pTextureCross,
			pTextureArrow,
			pTextureCircle);
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ManagerTarget::Finalize( void )
{
	delete targetAppearData;
	delete[] target;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerTarget::Update(int* _table , int* _targetTableIndex)
{
	//	自動で生成
	//autoAppear(_table, _targetTableIndex);

	for( int counterPoint = 0; counterPoint < TARGET_MAX; ++counterPoint )
	{
		//	消えた瞬間を判定して、テーブルを再構築
		if(enableOld[counterPoint] == true &&
			target[counterPoint].IsEnable() == false)
		{
			Sort(_table, counterPoint);
			*_targetTableIndex -= 1;
		}

		//	使用状態の前情報を保存
		enableOld[ counterPoint ] = target[ counterPoint ].IsEnable();

		// 使用されていないとき次へ
		if( !target[ counterPoint ].IsEnable() )
		{
			continue;
		}
		target[counterPoint].setInvViewMatrix(invViewMatrix);
		target[counterPoint].Update();
	}
}
//==============================================================================
// Brief  : 自動生成処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerTarget::autoAppear(int* _table , int* _targetTableIndex)
{
	//	出現カウント加算
	if(targetAppearIndex < targetAppearDataMax)
		targetAppearCount++;

	//	現在の出現データの、出現時間がカウンタと一致したら
	if(targetAppearData[targetAppearIndex].appearTime == targetAppearCount)
	{
		//	生成
		int buff = Add(targetAppearData[targetAppearIndex].appearPos, targetAppearData[targetAppearIndex].colorState);
		targetAppearIndex++;

		//	テーブルへ追加
		if(buff != -1)
		{
			_table[*_targetTableIndex] = buff;
			*_targetTableIndex += 1;
		}

		//	同じ時間に複数生成される場合があるので、その判定
		int tempIndex = targetAppearIndex;

		//	カウンタが同じである限り続ける
		while(targetAppearData[tempIndex].appearTime == targetAppearCount)
		{
			//	生成
			buff = Add(targetAppearData[tempIndex].appearPos, targetAppearData[tempIndex].colorState);

			//	テーブルへ追加
			if(buff != -1)
			{
				_table[*_targetTableIndex] = buff;
				*_targetTableIndex += 1;
			}


			//	さらに次のインデックスと判定
			tempIndex++;

			if(tempIndex >= targetAppearDataMax)
				break;
		}

		//	インデックス値をセットし直す
		targetAppearIndex = tempIndex;
	}
}
//==============================================================================
// Brief  : テーブルのソート処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerTarget::Sort(int* _table, int _deleteIndex)
{
	//	消去するテーブル番号の一時保存
	int tempIndex;

	//	テーブルを全て一時保存
	int tempTable[TARGET_MAX];

	for(int count = 0;count < TARGET_MAX;count++)
	{
		//	テーブルを全て一時保存
		tempTable[count] = _table[count];

		//	消去するテーブル番号の一時保存
		if(_table[count] == _deleteIndex)
			tempIndex = count;
	}

	//	配列保存用の一時カウンタ
	int tempCount = 0;

	for(int count = 0;count < TARGET_MAX;count++)
	{
		//	削除する番号以外
		if(count != tempIndex)
		{
			_table[tempCount] = tempTable[count];
			tempCount++;
		}
	}

	//	最後に-1追加
	_table[TARGET_MAX - 1] = -1;
}
//==============================================================================
// Brief  : ターゲット発射処理
// Return : void								: なし
// Arg2   : D3DXVECTOR3							: 発生位置
//==============================================================================
int ManagerTarget::Add(D3DXVECTOR3 _pos, COLOR_STATE _colorState)
{
	int index = GetIndex();
	if(index < 0)
	{
		//PrintDebugWnd( _T( "ポイントに空きがありません。\n" ) );
		return -1;
	}

	//	ターゲットのセット
	target[index].Set(_pos, _colorState);

	return index;
}
//==============================================================================
// Brief  : インデックス取得処理
// Return : int									: 使用可能なオブジェクトの番号（全部使用中の場合は負の値が返る）
// Arg    : void								: なし
//==============================================================================
int ManagerTarget::GetIndex()
{
	// 空き番号を探す
	for( int counterPoint = 0; counterPoint < TARGET_MAX; ++counterPoint )
	{
		if( !target[ counterPoint ].IsEnable() )
		{
			return counterPoint;
		}
	}

	// 空いていなかった
	return -1;
}

//==============================================================================
// Brief  : ターゲット生成スクリプト読み込み処理
//==============================================================================
void ManagerTarget::ReadTargetScriptFromFile(const char* _fileName)
{
	//	ファイル読み込み開始
	FILE* fp;

	if(fopen_s(&fp, _fileName, "r") != NULL)
		return;

	char readBuff[256];
	int readDataIndex = 0;

	//	生成するターゲット情報を読み込み
	ReadAppearTargetMax(fp);

	//	読み込み位置を戻す
	fseek(fp, 0, SEEK_SET);

	//	一行読み込んで
	while(fgets(readBuff, sizeof(readBuff), fp) != NULL)
	{
		//	以下、最初の３文字によって分岐して読み込みを行う
		//-----------------------------------------------------------------------
		//	複数行コメントを認識したら
		if(readBuff[0] == '/' && readBuff[1] == '-' && readBuff[2] == '-')
		{
			//	コメントスキップ
			SkipComment(fp);
		}
		//	１行コメントを認識したら
		else if(readBuff[0] == 'C' && readBuff[1] == 'O' && readBuff[2] == 'M')
		{
			continue;
		}
		//	オブジェクトの名前を認識したら
		else if(readBuff[0] == 'N' && readBuff[1] == 'A' && readBuff[2] == 'M')
		{
			//	NAM を読み飛ばす
			char* setName;
			char* ctx;
			ctx = strtok_s(readBuff, " ", &setName);

			//	名前保存
			strcpy_s(targetAppearData[readDataIndex].name, setName);

			//	出現時間と位置の読み込み
			Read_TIM_POS_COL(fp, readDataIndex);
			readDataIndex++;
		}
		//-----------------------------------------------------------------------
	}

	fclose(fp);


	//	データのソート
	SortAppearTargetData();
}

void ManagerTarget::ReadAppearTargetMax(FILE* _fp)
{
	char readBuff[256];
	targetAppearDataMax = 0;

	//	一行読み込んで
	while(fgets(readBuff, sizeof(readBuff), _fp) != NULL)
	{
		//	以下、最初の３文字によって分岐して読み込みを行う
		//-----------------------------------------------------------------------
		//	複数行コメントを認識したら
		if(readBuff[0] == '/' && readBuff[1] == '-' && readBuff[2] == '-')
		{
			//	コメントスキップ
			SkipComment(_fp);
		}
		//	１行コメントを認識したら
		else if(readBuff[0] == 'C' && readBuff[1] == 'O' && readBuff[2] == 'M')
		{
			continue;
		}
		//	オブジェクトの名前を認識したら
		else if(readBuff[0] == 'N' && readBuff[1] == 'A' && readBuff[2] == 'M')
		{
			targetAppearDataMax++;
		}
		//-----------------------------------------------------------------------
	}

	//	データ生成
	targetAppearData = new TARGET_APPEAR_DATA[targetAppearDataMax];
}

void ManagerTarget::Read_TIM_POS_COL(FILE* _fp, int _readDataIndex)
{
	//	TIM の読み飛ばし
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);
	//	実数値読み込み
	fscanf_s(_fp, "%d", &targetAppearData[_readDataIndex].appearTime);

	//	POS の読み飛ばし
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);

	//	実数値読み込み
	//fread_s(targetAppearData[_readDataIndex].appearPos, sizeof(float) * 3, sizeof(float), 3, _fp);
	fscanf_s(_fp, "%f %f %f", &targetAppearData[_readDataIndex].appearPos.x, &targetAppearData[_readDataIndex].appearPos.y, &targetAppearData[_readDataIndex].appearPos.z);
	//-----------------------------------------------------------------------

	//	COL の読み飛ばし
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);
	fgetc(_fp);

	//	R G B Wいづれかの読み込み
	char c = fgetc(_fp);
	if(c == 'R')
		targetAppearData[_readDataIndex].colorState = COLOR_STATE_R;
	else if(c == 'G')
		targetAppearData[_readDataIndex].colorState = COLOR_STATE_G;
	else if(c == 'B')
		targetAppearData[_readDataIndex].colorState = COLOR_STATE_B;
	else if(c == 'W')
		targetAppearData[_readDataIndex].colorState = COLOR_STATE_W;
	else if(c == 'S')
		targetAppearData[_readDataIndex].colorState = COLOR_STATE_S;
}

void ManagerTarget::SkipComment(FILE* _fp)
{
	char readBuff[512];
	while(fgets(readBuff, sizeof(readBuff), _fp) != NULL)
	{
		//	以下、最初の３文字によって分岐して読み込みを行う
		//-----------------------------------------------------------------------
		//	コメントの終了を認識したら
		if(readBuff[0] == '-' && readBuff[1] == '-' && readBuff[2] == '/')
		{
			return;
		}
		//-----------------------------------------------------------------------
	}

	//	コメントの終了を認識できなかったら
	return;
}

void ManagerTarget::SortAppearTargetData()
{
	for(int i = 0;i < targetAppearDataMax - 1;i++)
	{
		for(int j = targetAppearDataMax - 1; j > i;j--)
		{
			if(targetAppearData[j - 1].appearTime >= targetAppearData[j].appearTime)
			{
				TARGET_APPEAR_DATA temp = targetAppearData[j];
				targetAppearData[j] = targetAppearData[j - 1];
				targetAppearData[j - 1] = temp;
			}
		}
	}
}
