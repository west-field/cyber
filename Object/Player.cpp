#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "../game.h"
#include "../Sound.h"

namespace
{
	constexpr int kMaxHp = 100;
	constexpr int kGraphSizeX = 150;
	constexpr int kGraphSizeY = 140;

	constexpr int kDamageGraphSizeX = 160*1.5;
	constexpr int kDamageGraphSizeY = 120*1.5;
}

//1754 : 1600
//1600 : 1200

Player::Player()
{
	m_nowHp = 0.0f;
	m_hpWidth = 0.0f;
	m_graph = -1;
	m_pos = {};
	m_attackGraph = -1;
	m_attackPos = {};
	m_isDamage = false;
	m_fade = 255;
	m_fadeSpeed = 10;
	m_effectDrawTime = 120;
}

Player::~Player()
{
	DeleteGraph(m_graph);
	DeleteGraph(m_attackGraph);
}

void Player::Init()
{
	m_nowHp = kMaxHp;
	m_hpWidth = kGraphSizeX;

	m_pos.x = (Game::kScreenWidth - 10 * 50) / 2;
	m_pos.y = 20.0f;

	m_attackPos.x = (Game::kScreenWidth - 10 * 50) / 2 - 40;
}

void Player::Update()
{
	//HPバー表示幅
	//m_nowHp / kMaxHp;HP比率計算
	//m_nowHp / kMaxHp * m_hpWidth;HP比率計算
}

void Player::Draw()
{
	//プレイヤー表示
	DrawExtendGraphF(m_pos.x, m_pos.y, m_pos.x + kGraphSizeX, m_pos.y + kGraphSizeY, m_graph, true);
	//HPバー表示
	DrawBoxAA(m_pos.x, m_pos.y + kGraphSizeY, m_pos.x + (m_nowHp / kMaxHp * m_hpWidth), m_pos.y + kGraphSizeY + 10, 0x008000, true);
	DrawBoxAA(m_pos.x, m_pos.y + kGraphSizeY, m_pos.x + m_hpWidth, m_pos.y + kGraphSizeY + 10, 0xffffff, false);
	DrawFormatString(0, 100, 0xffffff, "%3f,%3f", m_nowHp, m_nowHp / kMaxHp);

	if (m_isDamage)
	{
		m_fade += m_fadeSpeed;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fade);
		DrawExtendGraphF(m_attackPos.x, m_attackPos.y, m_attackPos.x + kDamageGraphSizeX, m_attackPos.y + kDamageGraphSizeY, m_attackGraph, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (--m_effectDrawTime == 0)
		{
			m_isDamage = false;
			m_fade = 255;
			m_fadeSpeed = 10;
			m_effectDrawTime = 120;
		}

		if (m_fade >= 255)
		{
			m_fade = 255;
			m_fadeSpeed = -10;
		}
		else if (m_fade <= 0)
		{
			m_fade = 0;
			m_fadeSpeed = 10;
		}
	}
}

void Player::SetGraph(int graphHandle, int effectHandle)
{
	m_graph = graphHandle;
	assert(m_graph > 0);
	m_attackGraph = effectHandle;
	assert(m_attackGraph > 0);
}

void Player::Damage(const float damage)
{
	Sound::Play(Sound::SoundId_Hit);
	m_isDamage = true;
	SetHp(m_nowHp - damage);
}

void Player::Heal(const float heal)
{
	SetHp(m_nowHp + heal);
}

void Player::SetHp(const float hp)
{
	if (hp >= kMaxHp)
	{
		m_nowHp = kMaxHp;
	}
	else if (hp <= 0)
	{
		m_nowHp = 0;
	}
	else
	{
		m_nowHp = hp;
	}
}
