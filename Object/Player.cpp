#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "../game.h"
#include "../Sound.h"

namespace
{
	constexpr int kMaxHp = 100;
	constexpr int kGraphSizeX = 140;
	constexpr int kGraphSizeY = 130;

	constexpr int kDamageGraphSizeX = 150 * 1.5;
	constexpr int kDamageGraphSizeY = 110 * 1.5;

	//キャラクターアニメーション1コマ当たりのフレーム数
	constexpr int kAnimeChngeFrame = 8;
}

Player::Player()
{
	m_nowHp = 0.0f;
	m_hpWidth = 0.0f;
	m_pos = {};
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	m_animeNo = 0;
	m_animeFrame = 0;
	m_attackGraph = -1;
	m_attackPos = {};
	m_isDamage = false;
	m_fade = 255;
	m_fadeSpeed = 10;
	m_effectDrawTime = 120;
}

Player::~Player()
{
	for (auto& handle : m_handle)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_attackGraph);
}

void Player::Init()
{
	m_nowHp = kMaxHp;
	m_hpWidth = kGraphSizeX;

	m_pos.x = (Game::kScreenWidth - 10 * 60) / 2;
	m_pos.y = 20.0f;

	m_attackPos.x = (Game::kScreenWidth - 10 * 60) / 2 - 40;
}

void Player::Update()
{
	m_animeFrame++;

	if (m_animeFrame >= kGraphicDivX * kAnimeChngeFrame)
	{
		m_animeFrame = 0;
		
		if (m_animeNo++ >= 2)
		{
			m_animeNo = 0;
		}
	}
}

void Player::Draw()
{
	//HPバー表示
	DrawBoxAA(m_pos.x, m_pos.y + kGraphSizeY, m_pos.x + (m_nowHp / kMaxHp * m_hpWidth), m_pos.y + kGraphSizeY + 10, 0x008000, true);
	DrawBoxAA(m_pos.x, m_pos.y + kGraphSizeY, m_pos.x + m_hpWidth, m_pos.y + kGraphSizeY + 10, 0xffffff, false);

	if (m_isDamage)
	{
		m_fade += m_fadeSpeed;
		DrawExtendGraphF(m_pos.x, m_pos.y, m_pos.x + kGraphSizeX, m_pos.y + kGraphSizeY, m_handle[4], true);
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
		m_animeNo = 0;
	}
	else
	{
		//プレイヤー表示
		DrawExtendGraphF(m_pos.x, m_pos.y, m_pos.x + kGraphSizeX, m_pos.y + kGraphSizeY, m_handle[m_animeNo], true);
	}
}

void Player::SetEffectGraph(int effectHandle)
{
	m_attackGraph = effectHandle;
	assert(m_attackGraph > 0);
}

void  Player::SetGraph(int graphHandle, int index)
{
	m_handle[index] = graphHandle;
	assert(m_handle[index] > 0);
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
