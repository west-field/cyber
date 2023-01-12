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
	//������
	m_bg.Init();
	//�O���t�B�b�N�����[�h
	m_bg.SetGraph(LoadGraph(kBgBlueGraph));
	//BGM
	Sound::StartBgm(Sound::SoundId_Bgm, 255);
}

void SceneMain::end()
{
	//BGM���~�߂�
	Sound::StopBgm(Sound::SoundId_Bgm);
}

SceneBase* SceneMain::update()
{
	//�t�F�[�h�C��
	m_fade += m_fadeSpeed;
	if (m_fade <= 0)
	{
		m_fade = 0;
		m_fadeSpeed = 0;
	}
	//�X�V
	m_bg.Update();
	m_piece.Update();
	
	//�s�[�X���K��ʒu�ɒB�����Ƃ��Q�[���I�[�o�[�ɂȂ�
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

	//�^�C�g���ɖ߂�
	Pad::update();
	if (Pad::isPress(PAD_INPUT_1))
	{
		m_select = 3;
		m_fadeSpeed = kFadeSpeed;
	}
	//�t�F�[�h�A�E�g
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
	//�`��
	m_bg.Draw();
	m_piece.Draw();
	
	//�t�F�[�h
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fade);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}