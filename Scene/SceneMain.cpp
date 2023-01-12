#include "DxLib.h"
#include "../Util/Pad.h"
#include "../game.h"
#include "../Sound.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "GameOverScene.h"
#include "GameClearScene.h"

namespace
{
	const char* const kBlockGraph = "Data/block.bmp";
	const char* const kBgBlueGraph = "Data/flameblue.png";

	constexpr int kFadeSpeed = 8;
}

SceneMain::SceneMain():
	m_piece(),
	m_bg(),
	m_select(),
	m_fade(255),
	m_fadeSpeed(-kFadeSpeed)
{

}
SceneMain::~SceneMain() 
{

}
void SceneMain::init()
{
	//初期化
	m_bg.Init();
	//グラフィックをロード
	m_bg.SetGraph(LoadGraph(kBgBlueGraph));
	//BGM
	Sound::StartBgm(Sound::SoundId_Bgm, 255);
}

void SceneMain::end()
{
	//BGMを止める
	Sound::StopBgm(Sound::SoundId_Bgm);
}

SceneBase* SceneMain::update()
{
	//フェードイン
	m_fade += m_fadeSpeed;
	if (m_fade <= 0)
	{
		m_fade = 0;
		m_fadeSpeed = 0;
	}
	//更新
	m_bg.Update();
	m_piece.Update();
	
	//ピースが規定位置に達したときゲームオーバーになる
	if (m_piece.GameOver())
	{
		m_select = 1;
		m_fadeSpeed = kFadeSpeed;
	}
	else if (m_piece.GameClear())
	{
		m_select = 2;
		m_fadeSpeed = kFadeSpeed;
	}

	//タイトルに戻る
	Pad::update();
	if (Pad::isPress(PAD_INPUT_1))
	{
		m_select = 3;
		m_fadeSpeed = kFadeSpeed;
	}
	//フェードアウト
	if (m_fade >= 255 && m_fadeSpeed > 0)
	{
		m_fade = 255;
		switch (m_select)
		{
		case 1:return (new GameOverScene);
			break;
		case 2:return (new GameClearScene);
			break;
		case 3:return (new SceneTitle);
		default:
			break;
		}
	}

	return this;
}

void SceneMain::draw()
{
	//描画
	m_bg.Draw();
	m_piece.Draw();
	
	//フェード
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fade);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}