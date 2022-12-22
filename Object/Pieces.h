#pragma once
#include "Vec2.h"
#include "Player.h"
#include "Enemy.h"

//�s�[�X�̐F���
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
	//�Ֆʂ̃s�N�Z����
	static constexpr int kFieldHeight = 11;
	static constexpr int kFieldWidth = 7;
	
public:
	Pieces();
	virtual ~Pieces();

	void Update();
	void Draw();
	/// <summary>
	/// �t�B�[���h�̈�ԏ�Ƀu���b�N���u���ꂽ���ǂ���
	/// </summary>
	/// <returns>false:�Q�[�����s true:�Q�[���I��</returns>
	bool GameOver();

	bool GameClear();

private:
	///������
	void Init();
	/// ���̃u���b�N�̐F��m_nextPieceColor�Ɏw��
	void NextPiece();
	/// �e�g���~�m���t�B�[���h�ɃR�s�[����
	void PiecrToField();
	///���������s�[�X���폜����
	void DeletePiece();
	void DePiece(int X, int Y, int color);
	//�ׂ������̐F���l�����m�F
	void NextToMyColor(int X,int Y,int color);
	///�폜���ꂽ���Ƀe�g���~�m���������牺�Ɉړ�������
	void DropPiece();

private:
	struct Piece
	{
		//�s�[�X�̔z��ʒu
		int X;
		int Y;
		//�s�[�X�̐F
		int color;
	};

private:
	//�t�B�[���h�ʒu
	int m_statePosX;
	int m_statePosY;

	//�Q�[���t�B�[���h
	int m_field[kFieldHeight][kFieldWidth] = {};
	//�s�[�X����
	int m_erase[kFieldHeight][kFieldWidth] = {};

	bool m_isErasePiese;

	//���݂̃s�[�X
	Piece m_piece;
	//���̃s�[�X
	Piece m_nextPiece;

	//�s�[�X��3�ȏキ�����Ă��邩�ǂ���
	int m_count;

	//�}�E�X��������Ă��邩�ǂ���
	bool m_isPushMouse;
	//�}�E�X�̈ʒu��z��̃C���f���g�ɕς���
	int m_indexX;
	//�Ăу}�E�X��������悤�ɂȂ�܂ł̎���
	float m_pushWaitTime;
	//����s�[�X�𗎂Ƃ�����
	int m_pieceNum;

	Player m_player;
	int m_playerGraph[Player::kGraphicDivNum];
	Enemy m_enemy;
};

