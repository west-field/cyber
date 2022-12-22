#pragma once
#include "Vec2.h"
#include "Player.h"
#include "Enemy.h"

//ピースの色種類
enum Color
{
	Color_White,
	Color_Red,
	Color_Blue,
	Color_LightBlue,
	Color_Green,
	Color_Yellow,
	Color_Purple,

	Color_Num
};

class Pieces
{
public:
	//盤面のピクセル数
	static constexpr int kFieldHeight = 11;
	static constexpr int kFieldWidth = 7;
	
public:
	Pieces();
	virtual ~Pieces();

	void Update();
	void Draw();
	/// <summary>
	/// フィールドの一番上にブロックが置かれたかどうか
	/// </summary>
	/// <returns>false:ゲーム続行 true:ゲーム終了</returns>
	bool GameOver();

	bool GameClear();

private:
	///初期化
	void Init();
	/// 次のブロックの色をm_nextPieceColorに指定
	void NextPiece();
	/// テトリミノをフィールドにコピーする
	void PiecrToField();
	///そろったらピースを削除する
	void DeletePiece();
	void DePiece(int X, int Y, int color);
	//隣が自分の色か四方向確認
	void NextToMyColor(int X,int Y,int color);
	///削除された後上にテトリミノがあったら下に移動させる
	void DropPiece();

private:
	struct Piece
	{
		//ピースの配列位置
		int X;
		int Y;
		//ピースの色
		int color;
	};

private:
	//フィールド位置
	int m_statePosX;
	int m_statePosY;

	//ゲームフィールド
	int m_field[kFieldHeight][kFieldWidth] = {};
	//ピース消去
	int m_erase[kFieldHeight][kFieldWidth] = {};

	bool m_isErasePiese;

	//現在のピース
	Piece m_piece;
	//次のピース
	Piece m_nextPiece;

	//ピースが3つ以上くっついているかどうか
	int m_count;

	//マウスが押されているかどうか
	bool m_isPushMouse;
	//マウスの位置を配列のインデントに変える
	int m_indexX;
	//再びマウスを押せるようになるまでの時間
	float m_pushWaitTime;
	//何回ピースを落としたか
	int m_pieceNum;

	Player m_player;
	int m_playerGraph[Player::kGraphicDivNum];
	Enemy m_enemy;
};

