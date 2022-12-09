#include "Sound.h"
#include "DxLib.h"
#include <vector>

namespace
{
	std::vector<int> m_sound;

	const char* const kFileName[Sound::SoundId_Num] =
	{
		//BGM
		"Sound/marbletechno1.mp3",	//�^�C�g��BGM
		"Sound/retrogamecenter.mp3",		//BGM
		"Sound/picopicodisco.mp3",	//�Q�[���N���A��BGM
		"Sound/shizukanoumi.mp3",		//�Q�[���I�[�o�[��BGM
		//���ʉ�
		"Sound/cursorMove11.mp3",	//�J�[�\�����ړ��������Ƃ��̉�
		"Sound/cursorSelect.mp3",	//�J�[�\���ŃN���b�N�����Ƃ��̉�

		"Sound/cursorPush.mp3",//���肵���Ƃ��̉�

		"Sound/attack.mp3",	//�U����
		"Sound/hit.mp3"		//��e��
	};
}

namespace Sound
{
	//���[�h�A�A�����[�h
	void Load()
	{
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			m_sound.push_back(handle);
		}
	}
	void Unload()
	{
		for (auto& handle : m_sound)
		{
			DeleteSoundMem(handle);
			handle = -1;
		}
	}

	//BGM�̍Đ�
	void StartBgm(SoundId id, int volume)
	{
		PlaySoundMem(m_sound[id], DX_PLAYTYPE_BACK, true);
		SetVolume(id, volume);
	}
	void StopBgm(SoundId id)
	{
		StopSoundMem(m_sound[id]);
	}

	//���ʉ��̍Đ�
	void Play(SoundId id)
	{
		PlaySoundMem(m_sound[id], DX_PLAYTYPE_BACK, true);
	}

	//���ʐݒ�
	void SetVolume(SoundId id, int volume)
	{
		ChangeVolumeSoundMem(volume, m_sound[id]);
	}

}