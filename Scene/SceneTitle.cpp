#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneTest.h"
#include "Pad.h"
#include "../game.h"
#include "../Sound.h"

namespace
{
	constexpr int kOriginalPosX = Game::kScreenWidth / 3;    //���j���[�����̌���x�ʒu
	constexpr int kOriginalPosY = Game::kScreenHeight / 2 - 20;    //���j���[�����̌���y�ʒu

	constexpr int kMovedPosX = kOriginalPosX - Game::kFontSize;    //���j���[�����̈ړ�����x�ʒu

	constexpr int kPushSize = Game::kFontSize / 3;//������̕�
	constexpr int kGap = Game::kFontSize - 20;//������̕�

// ���j���[���ڗv�f�����  �^�O�̒��g�̏��ԂŊi�[�����Bx.y���W�@���j���[�ŏ��̈ʒu + (�����̃T�C�Y + ��)�@* ���Ԗڂɕ\�����邩
	MenuElement_t MenuElement[eMenu_Num] = {
		{ kMovedPosX, kOriginalPosY + Game::kFontSize * eMenu_GameStart, "�Q�[���X�^�[�g" }
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
	//�t�F�[�h�C��
	m_fade += m_fadeSpeed;
	if (m_fade <= 0)
	{
		m_fade = 0;
		m_fadeSpeed = 0;
	}

	if (m_fadeSpeed == 0)
	{
		//�}�E�X�̈ʒu
		int mouseX = 0;
		int mouseY = 0;
		GetMousePoint(&mouseX, &mouseY);

		//�����͈̔�X���Ƀ}�E�X�J�[�\�������邩
		if (mouseX > kOriginalPosX - Game::kFontSize && mouseX <= 900)
		{
			//���j���[�\���ʒuY���ɃJ�[�\�������邩�ǂ���
			if ( mouseY > MenuElement[eMenu_GameStart].y && mouseY < MenuElement[eMenu_GameStart].y + Game::kFontSize)
			{
				Sound::Play(Sound::SoundId_CursorMove);
				if (m_selectNum != eMenu_GameStart)
				{
					m_selectNum = eMenu_GameStart;
				}
			}
			//�}�E�X�������ꂽ��
			if (GetMouseInput() & MOUSE_INPUT_LEFT)
			{
				m_fadeSpeed = kFadeSpeed;
				Sound::Play(Sound::SoundId_Select);
			}
		}

		// ���j���[���ڐ��ł���4���[�v����
		for (int i = 0; i < eMenu_Num; i++)
		{
			// ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
			if (i == m_selectNum)
			{
				MenuElement[i].x = kMovedPosX;//�ړ��ʒu�Ɉړ�����
			}
			// ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
			else
			{
				MenuElement[i].x = kOriginalPosX;//���̈ʒu�ɖ߂�
			}
		}
	}

	if (m_fade >= 255 && m_fadeSpeed > 0)
	{
		m_fade = 255;
		//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
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
	//�w�i��\��
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_bgGraph, true);
	//���j���[��\��
	SetFontSize(Game::kFontSize);
	for (int i = 0; i < eMenu_Num; i++)
	{
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, GetColor(255, 255, 255), MenuElement[i].name);
	}
	SetFontSize(0);
	//�t�F�[�h�\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fade);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}