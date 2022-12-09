#include "Pieces.h"
#include "DxLib.h"
#include "../game.h"
#include "../Sound.h"
namespace
{
	const char* const kPlayerGraph = "Data/animalrobot.png";
	const char* const kPlayerDamageGraph = "Data/effect2.png";
	const char* const kEnemyGraph = "Data/animalrobot.png";
	const char* const kEnemyDamageGraph = "Data/effect.png";

	int kColor[Color_Num] =
	{
		0xffffff,//��
		0xFF0000,//��
		0x0000FF,//��
		0xAAD8E6,//���F
		0x008000,//��
		0xFFFF00,//���F
		0xFF00FF//��
	};
	//�s�[�X�̑傫��
	 constexpr int kSizeX = 60;
	 constexpr int kSizeY = kSizeX;
	//�����鎞��
	 constexpr float kDropWaitTime = 5.0f;
}

Pieces::Pieces() :
	m_player(),
	m_enemy()
{
	m_player.Init();
	m_enemy.Init();

	m_player.SetGraph(LoadGraph(kPlayerGraph), LoadGraph(kPlayerDamageGraph));
	m_enemy.SetGraph(LoadGraph(kEnemyGraph), LoadGraph(kEnemyDamageGraph));

	m_statePosX = (Game::kScreenWidth - kFieldWidth * kSizeX) / 2;
	m_statePosY = (Game::kScreenHeight - (kFieldHeight-3) * kSizeY) / 2;

	m_isErasePiese = false;

	m_piece.X = 0;
	m_piece.Y = 0;
	m_piece.color = rand() % (Color_Num - 1) + 1;

	m_nextPiece.X = m_statePosX + kFieldWidth* kSizeX + 30;
	m_nextPiece.Y = m_statePosY + 2 * kSizeX + 30;
	m_nextPiece.color = rand() % (Color_Num - 1) + 1;

	m_count = 0;

	m_isPushMouse = false;
	m_indexX = 0;
	m_pushWaitTime = 0;

	m_pieceNum = 0;
}

Pieces::~Pieces()
{

}

void Pieces::Update()
{
	

	m_player.Update();
	m_enemy.Update();

	//�}�E�X�̈ʒu
	int m_mouseX;
	int m_mouseY;
	GetMousePoint(&m_mouseX, &m_mouseY);
	//�}�E�X�̈ʒu���t�B�[���h���ɂ��邩�ǂ���
	m_indexX = (m_mouseX - m_statePosX) / kSizeX;
	//�͈͊O�ɂ��鎞�͔͈͓��ɓ����
	if (m_indexX >= kFieldWidth)	m_indexX = kFieldWidth - 1;
	else if (m_indexX < 0) m_indexX = 0;

	if (m_player.GetIsDamage()) return;
	if (m_enemy.GetIsDamage()) return;

	//�e�g���~�m�����ɗ��Ƃ��Ă��������B���ɂ�����܂��}�E�X���N���b�N�ł���悤�ɂ���
	if (m_pushWaitTime-- <= 0)
	{
		m_pushWaitTime = 0;
		//�t�B�[���h���Ƀ}�E�X�J�[�\�������鎞�ɃN���b�N�ł���
		if (m_mouseX >= m_statePosX && m_mouseX <= m_statePosX + kSizeX * kFieldWidth &&
			m_mouseY >= m_statePosY && m_mouseY <= m_statePosY + kSizeY * kFieldHeight)
		{
			//�}�E�X���N���b�N�����Ƃ�
			if (!m_isPushMouse && (GetMouseInput() & MOUSE_INPUT_LEFT))
			{
				Sound::Play(Sound::SoundId_CursorClick);
				m_isPushMouse = true;
				m_piece.X = m_indexX;
			}
		}

		//�}�E�X���������Ƃ�
		if (m_isPushMouse)
		{
			//������t�B�[���h���̉����Ȃ���Ԃ��ǂ���
			if (m_piece.Y + 1 < kFieldHeight && m_field[m_piece.Y + 1][m_piece.X] == 0)
			{
				m_piece.Y += 1;
			}
			//������t�B�[���h�̒[�A���łɃs�[�X���u���Ă���Ƃ�
			else
			{
				PiecrToField();
				m_isPushMouse = false;
				m_pieceNum++;
				//���̐F�����߂�
				m_piece.color = m_nextPiece.color;
				NextPiece();
			}
			m_pushWaitTime = kDropWaitTime;
		}
	}

	//�_���[�W��^����
	if (m_pieceNum == 5)
	{
		m_player.Damage(10);
		m_pieceNum = 0;
	}

	//�s�[�X�������o������`�F�C�������������G�l�~�[�Ƀ_���[�W��^����
	if (m_isErasePiese)
	{
		m_enemy.HitDamage(static_cast<float>(m_count * 10));
		m_isErasePiese = false;
		m_count = 0;
	}
	
}

void Pieces::Draw()
{
	//�}�E�X�ʒu�\��
	int X = m_statePosX + kSizeX * m_indexX;
	int Y = m_statePosY + kSizeY * 0;
	//�}�E�X�ʒu����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(X, Y, X + kSizeX, Y + kFieldHeight * kSizeY, kColor[0], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int y = 0; y < kFieldHeight; y++)
	{
		for (int x = 0; x < kFieldWidth; x++)
		{
			int iX = x * kSizeX + m_statePosX;
			int iY = y * kSizeY + m_statePosY;

			//�t�B�[���h�̘g
			DrawBox(iX, iY, iX + kSizeX, iY + kSizeY, 0xffffff, false);
			if (m_field[y][x] != 0)
			{
				//�t�B�[���h�ɌŒ肳�ꂽ�s�[�X
				DrawBox(iX, iY, iX + kSizeX, iY + kSizeY,kColor[m_field[y][x]], true);
				DrawBox(iX, iY, iX + kSizeX, iY + kSizeY, 0x000000, false);
			}
		}
	}
	if (m_isPushMouse)
	{
		//�ړ����̃s�[�X
		DrawBox(m_piece.X * kSizeX + m_statePosX, m_piece.Y * kSizeY + m_statePosY, 
			m_piece.X * kSizeX + m_statePosX + kSizeX, m_piece.Y * kSizeY + m_statePosY + kSizeY, kColor[m_piece.color], true);
		DrawBox(m_piece.X * kSizeX + m_statePosX, m_piece.Y * kSizeY + m_statePosY,
			m_piece.X * kSizeX + m_statePosX + kSizeX, m_piece.Y * kSizeY + m_statePosY + kSizeY, 0x000000, false);
	}
	else
	{
		//���ɗ�����s�[�X��\��
		DrawBox(X, Y, X + kSizeX, Y + kSizeY, kColor[m_piece.color], true);
		DrawBox(X, Y, X + kSizeX, Y + kSizeY, 0x000000, false);
	}

	//���̃s�[�X��\�����Ă���
	DrawBox(m_nextPiece.X, m_nextPiece.Y, m_nextPiece.X + kSizeX, m_nextPiece.Y + kSizeY, kColor[m_nextPiece.color], true);
	DrawBox(m_nextPiece.X, m_nextPiece.Y, m_nextPiece.X + kSizeX, m_nextPiece.Y + kSizeY, 0x000000, false);

	m_player.Draw();
	m_enemy.Draw();
	DrawFormatString((Game::kScreenWidth + 5 * 50) / 2 + 140, 20.0f, 0xffffff, "����%d", 5 - m_pieceNum);
	//�m�F
	DrawFormatString(0, 0, 0xffffff, "X.%d,Y.%d", m_piece.X, m_piece.Y);
	DrawFormatString(0, 40, 0xffffff, "%d", m_pieceNum);
	DrawFormatString(0, 20, 0xffffff, "m_dropWaitTime%3f", m_pushWaitTime);
}

bool Pieces::GameOver()
{
	if (m_player.GetIsDamage()) return false;
	if (m_enemy.GetIsDamage()) return false;

	for (int x = 0; x < kFieldWidth; x++)
	{
		if (m_field[0][x] != 0)
		{
			return true;
		}
	}

	return false;
}

bool Pieces::GameClear()
{
	if (m_player.GetIsDamage()) return false;
	if (m_enemy.GetIsDamage()) return false;

	if (m_enemy.GetHp() == 0)
	{
		return true;
	}

	return false;
}

void Pieces::Init()
{
	m_piece.X = 0;
	m_piece.Y = 0;

	for (int y = kFieldHeight - 1; y > 0; y--)
	{
		for (int x = 0; x < kFieldWidth; x++)
		{
			m_erase[y][x] = 0;
		}
	}
}

void Pieces::NextPiece()
{
	m_nextPiece.color = rand() % (Color_Num - 1) + 1;
}

void Pieces::PiecrToField()
{
	m_field[m_piece.Y][m_piece.X] = m_piece.color;
	DeletePiece();
}

void Pieces::DeletePiece()
{
	m_erase[m_piece.Y][m_piece.X] = m_piece.color;

	DePiece(m_piece.X, m_piece.Y, m_piece.color);

	for (int y = kFieldHeight - 1; y > 0; y--)
	{
		for (int x = 0; x < kFieldWidth; x++)
		{
			if (m_field[y][x] != 0)
			{
				DePiece(x, y, m_field[y][x]);
			}
		}
	}
}

void Pieces::DePiece(int X, int Y, int color)
{
	NextToMyColor(X, Y, color);

	for (int y = kFieldHeight - 1; y > 0; y--)
	{
		for (int x = 0; x < kFieldWidth; x++)
		{
			if (m_erase[y][x] == color)
			{
				NextToMyColor(x, y, color);
			}
		}
	}
	int count = 0;
	for (int y = kFieldHeight - 1; y > 0; y--)
	{
		for (int x = 0; x < kFieldWidth; x++)
		{
			if (m_erase[y][x] == color)
			{
				count++;
			}
		}
	}

	if (count >= 3)
	{
		for (int y = kFieldHeight - 1; y > 0; y--)
		{
			for (int x = 0; x < kFieldWidth; x++)
			{
				if (m_erase[y][x] != 0)
				{
					m_field[y][x] = 0;
					m_erase[y][x] = 0;
				}
			}
		}
		m_count = count;
		m_isErasePiese = true;
		Sound::Play(Sound::SoundId_Attack);
	}
	
	DropPiece();
}

void Pieces::NextToMyColor(int X,int Y, int color)
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			//[y][x]�ɂȂ邩��i==0,j==0�̎��������Ȃ�,�Ֆʂ͈̔͊O�͏������Ȃ�
			if (i == 0 && j == 0 || i == 1 && j == 1 || i == -1 && j == 1 || i == 1 && j == -1 || i == -1 && j == -1) continue;
			if (Y + i < 0 || Y + i > kFieldHeight || X + j < 0 || X + j > kFieldWidth) continue;
			//�ׂ�(4����)�����̐F�łȂ���Ώ��������Ȃ�
			if (m_field[Y + i][X + j] != color) continue;
			//�ׂ������̐F�̎�
			m_erase[Y + i][X + j] = color;
		}
	}
}

void Pieces::DropPiece()
{
	//int moveFieldPiece[kFieldHeight][kFieldWidth] = {};
	for (int y = kFieldHeight - 1; y > 0; y--)
	{
		for (int x = 0; x < kFieldWidth; x++)
		{
			if (m_field[y][x] == 0 && m_field[y - 1][x] != 0)
			{
				m_field[y][x] = m_field[y - 1][x];
				m_field[y - 1][x] = 0;
			}
		}
	}
	Init();
}

