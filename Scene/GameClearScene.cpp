#include "GameClearScene.h"
#include "DxLib.h"
#include "../game.h"
#include "../Sound.h"
#include "SceneTitle.h"

namespace
{
	constexpr int kFadeSpeed = 8;
	const char* const kGraph = "Data/gameclear.png";
}


GameClearScene::GameClearScene()
{
	m_fade = 255;
	m_fadeSpeed = -kFadeSpeed;
	m_graph = -1;
}

GameClearScene::~GameClearScene()
{

}

void GameClearScene::init()
{
	Sound::StartBgm(Sound::SoundId_ClearBgm, 255);
	m_graph = LoadGraph(kGraph);
}

void GameClearScene::end()
{
	Sound::StopBgm(Sound::SoundId_ClearBgm);
	DeleteGraph(m_graph);
}

SceneBase* GameClearScene::update()
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

void GameClearScene::draw()
{
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_graph, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fade);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
