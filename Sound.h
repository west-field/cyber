#pragma once

namespace Sound
{
	typedef enum  SoundId
	{
		SoundId_TitleBgm,	//タイトルBGM
		SoundId_Bgm,		//BGM
		SoundId_ClearBgm,	//ゲームクリア時BGM
		SoundId_BgmGameover,//ゲームオーバー時BGM

		SoundId_CursorMove,	//カーソルを移動させたときの音
		SoundId_CursorClick,//カーソルでクリックしたときの音
		
		SoundId_Select,//決定したときの音
		
		SoundId_Attack,//攻撃音
		SoundId_Hit,	//被弾音
		
		SoundId_Num
	}SoundId;

	//ロード、アンロード
	void Load();
	void Unload();

	//BGMの再生
	void StartBgm(SoundId id, int volume );
	void StopBgm(SoundId id);

	//効果音の再生
	void Play(SoundId id);

	//音量設定
	void SetVolume(SoundId id, int volume);
}