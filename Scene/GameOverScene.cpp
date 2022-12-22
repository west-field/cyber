#include "GameOverScene.h"
#include "DxLib.h"
#include "../game.h"
#include "../Sound.h"
#include "SceneTitle.h"

namespace
{
	constexpr int kFadeSpeed = 8;
	const char* const kGraph = "Data/gameover.png";
}

GameOverScene::GameOverScene()
{
	m_fade = 255;
	m_fadeSpeed = -kFadeSpeed;
	m_graph = -1;
}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::init()
{
	Sound::StartBgm(Sound::SoundId_BgmGameover, 255);
	m_graph = LoadGraph(kGraph);
}

void GameOverScene::end()
{
	Sound::StopBgm(Sound::SoundId_BgmGameover);
	DeleteGraph(m_graph);
}

SceneBase* GameOverScene::update()
{
	//フェードイン
	m_fade += m_fadeSpeed;
	if (m_fade <= 0)
	{
		m_fade = 0;
		m_fadeSpeed = 0;
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		m_fadeSpeed = kFadeSpeed;
	}

	if (m_fade >= 255 && m_fadeSpeed > 0)
	{
		m_fade = 255;
		return (new SceneTitle);
	}

	return this;
}

void GameOverScene::draw()
{
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_graph, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fade);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
