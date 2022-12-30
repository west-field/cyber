#include "Enemy.h"
#include <DxLib.h>
#include <cassert>
#include "../game.h"
#include "../Sound.h"
#include "Player.h"
#include "Pieces.h"

namespace
{
	constexpr float kMaxHp = 100.0f;
	constexpr int kGraphSizeX = 140;
	constexpr int kGraphSizeY = 130;

	constexpr int kDamage = 10;
}

Enemy::Enemy()
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
	m_effectDrawTime = 0;
}

Enemy::~Enemy()
{
	DeleteGraph(m_graph);
	DeleteGraph(m_attackGraph);
}

void Enemy::Init()
{
	m_nowHp = kMaxHp;
	m_hpWidth = kGraphSizeX;

	m_pos.x = m_attackPos.x = (Game::kScreenWidth + 5 * 60) / 2;
	m_pos.y = m_attackPos.y = 20.0f;

	m_effectDrawTime = 120;
}

void Enemy::Update()
{

}

void Enemy::Draw()
{
	SetDrawBright(128, 128, 128);
	//エネミー表示
	DrawExtendGraphF(m_pos.x, m_pos.y, m_pos.x + kGraphSizeX, m_pos.y + kGraphSizeY, m_graph, true);
	SetDrawBright(255, 255, 255);
	//HPバー表示
	DrawBoxAA(m_pos.x, m_pos.y + kGraphSizeY, m_pos.x + (m_nowHp / kMaxHp * m_hpWidth), m_pos.y + kGraphSizeY + 10, 0x008000, true);
	DrawBoxAA(m_pos.x, m_pos.y + kGraphSizeY, m_pos.x + m_hpWidth, m_pos.y + kGraphSizeY + 10, 0xffffff, false);

	if (m_isDamage)
	{
		m_fade += m_fadeSpeed;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fade);
		DrawExtendGraphF(m_attackPos.x, m_attackPos.y, m_attackPos.x + kGraphSizeX, m_attackPos.y + kGraphSizeY, m_attackGraph, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if(--m_effectDrawTime == 0)
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
		else if(m_fade <= 0)
		{
			m_fade = 0;
			m_fadeSpeed = 10;
		}
	}
	
}

void Enemy::SetGraph(int graphHandle, int effectHandle)
{
	m_graph = graphHandle;
	assert(m_graph > 0);
	m_attackGraph = effectHandle;
	assert(m_attackGraph > 0);
}

void Enemy::HitDamage(const float damage)
{
	Sound::Play(Sound::SoundId_Hit);
	m_isDamage = true;
	SetHp(m_nowHp - damage);
}

void Enemy::Heal(const float heal)
{
	SetHp(m_nowHp + heal);
}

void Enemy::SetHp(const float hp)
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
