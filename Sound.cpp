#include "Sound.h"
#include "DxLib.h"
#include <vector>

namespace
{
	std::vector<int> m_sound;

	const char* const kFileName[Sound::SoundId_Num] =
	{
		//BGM
		"Sound/marbletechno1.mp3",	//タイトルBGM
		"Sound/retrogamecenter.mp3",		//BGM
		"Sound/picopicodisco.mp3",	//ゲームクリア時BGM
		"Sound/shizukanoumi.mp3",		//ゲームオーバー時BGM
		//効果音
		"Sound/cursorMove11.mp3",	//カーソルを移動させたときの音
		"Sound/cursorSelect.mp3",	//カーソルでクリックしたときの音

		"Sound/cursorPush.mp3",//決定したときの音

		"Sound/attack.mp3",	//攻撃音
		"Sound/hit.mp3"		//被弾音
	};
}

namespace Sound
{
	//ロード、アンロード
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

	//BGMの再生
	void StartBgm(SoundId id, int volume)
	{
		PlaySoundMem(m_sound[id], DX_PLAYTYPE_BACK, true);
		SetVolume(id, volume);
	}
	void StopBgm(SoundId id)
	{
		StopSoundMem(m_sound[id]);
	}

	//効果音の再生
	void Play(SoundId id)
	{
		PlaySoundMem(m_sound[id], DX_PLAYTYPE_BACK, true);
	}

	//音量設定
	void SetVolume(SoundId id, int volume)
	{
		ChangeVolumeSoundMem(volume, m_sound[id]);
	}

}