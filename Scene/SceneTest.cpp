#include "DxLib.h"
#include "SceneTest.h"
#include "SceneTitle.h"
#include "../game.h"

namespace
{
	constexpr int kFadeSpeed = 8;
}

SceneTest::SceneTest():
	m_select(),
	m_fade(255),
	m_fadeSpeed(-kFadeSpeed)
{
	
}

void SceneTest::init()
{
	
}

SceneBase* SceneTest::update()
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

	//フェードアウト
	if (m_fade >= 255 && m_fadeSpeed > 0)
	{
		m_fade = 255;
		return (new SceneTitle);
	}
	
	return this;
}

void SceneTest::draw()
{
	m_pieces.Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(180, 90, 180 + 13 * 20, 90 + 2 * 20, 0x32CD32, true);
	DrawBox(430, 180, 430 + 11 * 20, 180 + 4 * 20, 0x32CD32, true);
	DrawBox(0, 280, 0 + 23 * 20, 280 + 5 * 20, 0x32CD32, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(180, 90, "フィールド内をクリックして\nブロックを落とそう", 0xFFF0F5);

	DrawString(430, 180, "相手のHPをけずりきると\nゲームクリア！", 0xFFF0F5);
	DrawString(430, 220, "近くにある数字が\n0になると攻撃されるよ", 0xFFF0F5);
	
	DrawString(0, 280, "自分のHPがなくなるとゲームオーバー", 0xFFF0F5);
	DrawString(0, 300, "フィールドの一番上にブロックが来てもアウトだよ", 0xFFF0F5);

	DrawString(0, 340, "Zキーでタイトルにもどれるよ", 0xFFF0F5);
	DrawString(0, 360, "ESCキーでゲームを終了できるよ", 0xFFF0F5);

	//フェード
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fade);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}