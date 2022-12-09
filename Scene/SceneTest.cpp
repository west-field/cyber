#include "DxLib.h"
#include "SceneTest.h"
#include "SceneTitle.h"
#include "Pad.h"

void SceneTest::init()
{
	m_textPosX = 0;
	m_textVecX = 4;
}

SceneBase* SceneTest::update()
{
	// •¶Žš‚ÌˆÚ“®
	m_textPosX += m_textVecX;
	if (m_textPosX < 0)
	{
		m_textPosX = 0;
		m_textVecX = 4;
	}
	if (m_textPosX > 300)
	{
		m_textPosX = 300;
		m_textVecX = -4;
	}

	Pad::update();
	if (Pad::isPress(PAD_INPUT_3))
	{
		return (new SceneTitle);
	}

	return this;
}

void SceneTest::draw()
{
	DrawString(m_textPosX, 20, "test‰æ–Ê", GetColor(255, 255, 0));
}