#include "Bg.h"
#include "DxLib.h"
#include "../game.h"

namespace
{
	constexpr int kMaxRadius = 100;
	constexpr int kMinRadius = 5;

	constexpr int kMaxFade = 255;
}

Bg::Bg()
{
	m_bgBlueGraph = -1;
	m_bgGreenGraph = -1;
	m_add = 0;
	m_fade = 0;
}

Bg::~Bg()
{
	DeleteGraph(m_bgBlueGraph);
	DeleteGraph(m_bgGreenGraph);
}

void Bg::Init()
{
	m_add = 1;
	m_fade = rand() % kMaxFade + 0;
}

void Bg::SetGraph(int blueHandle)
{
	m_bgBlueGraph = blueHandle;
}

void Bg::Update()
{
	m_fade += m_add;
	if (m_fade >= kMaxFade)
	{
		m_add *= -1;
	}
	else if(m_fade <= 100)
	{
		m_add *= -1;
	}
}

void Bg::Draw()
{
	//グラフィック表示
	DrawExtendGraph(0, 0, 0 + Game::kScreenWidth, 0 + Game::kScreenHeight, m_bgBlueGraph, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fade);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
