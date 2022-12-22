#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneTest.h"
#include "Pad.h"
#include "../game.h"
#include "../Sound.h"

namespace
{
	constexpr int kOriginalPosX = Game::kScreenWidth / 3;    //メニュー文字の元のx位置
	constexpr int kOriginalPosY = Game::kScreenHeight / 2 - 20;    //メニュー文字の元のy位置

	constexpr int kMovedPosX = kOriginalPosX - Game::kFontSize;    //メニュー文字の移動したx位置

	constexpr int kPushSize = Game::kFontSize / 3;//文字列の幅
	constexpr int kGap = Game::kFontSize - 20;//文字列の幅

// メニュー項目要素を作る  タグの中身の順番で格納される。x.y座標　メニュー最初の位置 + (文字のサイズ + 間)　* 何番目に表示するか
	MenuElement_t MenuElement[eMenu_Num] = {
		{ kMovedPosX, kOriginalPosY + Game::kFontSize * eMenu_GameStart, "ゲームスタート" }
	};

	constexpr int kFadeSpeed = 8;

	const char* const kBgGraph = "Data/flamegreen.png";
}

SceneTitle::SceneTitle()
{
	m_selectNum = 0;
	m_nextItem = 0;
	m_moveFrame = 0;
	m_fade = 255;
	m_fadeSpeed = 0;
	m_bgGraph = -1;
	m_isFirst = true;
}

void SceneTitle::init()
{
	m_selectNum = 0;
	m_nextItem = 0;
	m_moveFrame = 0;
	m_fadeSpeed = -kFadeSpeed;
	m_bgGraph = LoadGraph(kBgGraph);
	
	Sound::StartBgm(Sound::SoundId_TitleBgm,255);
}

void SceneTitle::end()
{
	DeleteGraph(m_bgGraph);
	Sound::StopBgm(Sound::SoundId_TitleBgm);
}

SceneBase* SceneTitle::update()
{
	//フェードイン
	m_fade += m_fadeSpeed;
	if (m_fade <= 0)
	{
		m_fade = 0;
		m_fadeSpeed = 0;
	}

	if (m_fadeSpeed == 0)
	{
		//マウスの位置
		int mouseX = 0;
		int mouseY = 0;
		GetMousePoint(&mouseX, &mouseY);

		//文字の範囲X内にマウスカーソルがあるか
		if (mouseX > kOriginalPosX - Game::kFontSize && mouseX <= 900)
		{
			//メニュー表示位置Y内にカーソルがあるかどうか
			if ( mouseY > MenuElement[eMenu_GameStart].y && mouseY < MenuElement[eMenu_GameStart].y + Game::kFontSize)
			{
				Sound::Play(Sound::SoundId_CursorMove);
				if (m_selectNum != eMenu_GameStart)
				{
					m_selectNum = eMenu_GameStart;
				}
			}
			//マウスが押されたら
			if (GetMouseInput() & MOUSE_INPUT_LEFT)
			{
				m_fadeSpeed = kFadeSpeed;
				Sound::Play(Sound::SoundId_Select);
			}
		}

		// メニュー項目数である4個ループ処理
		for (int i = 0; i < eMenu_Num; i++)
		{
			// 今処理しているのが、選択番号と同じ要素なら
			if (i == m_selectNum)
			{
				MenuElement[i].x = kMovedPosX;//移動位置に移動する
			}
			// 今処理しているのが、選択番号以外なら
			else
			{
				MenuElement[i].x = kOriginalPosX;//元の位置に戻す
			}
		}
	}

	if (m_fade >= 255 && m_fadeSpeed > 0)
	{
		m_fade = 255;
		//現在選択中の状態によって処理を分岐
		switch (m_selectNum)
		{

		case eMenu_GameStart:
			return (new SceneTest);
			break;
		default:
			break;
		}
	}
	return this;
}

void SceneTitle::draw()
{
	//背景を表示
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_bgGraph, true);
	//メニューを表示
	SetFontSize(Game::kFontSize);
	for (int i = 0; i < eMenu_Num; i++)
	{
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, GetColor(255, 255, 255), MenuElement[i].name);
	}
	SetFontSize(0);
	//フェード表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fade);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}