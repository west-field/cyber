#pragma once

namespace Sound
{
	typedef enum  SoundId
	{
		SoundId_TitleBgm,	//�^�C�g��BGM
		SoundId_Bgm,		//BGM
		SoundId_ClearBgm,	//�Q�[���N���A��BGM
		SoundId_BgmGameover,//�Q�[���I�[�o�[��BGM

		SoundId_CursorMove,	//�J�[�\�����ړ��������Ƃ��̉�
		SoundId_CursorClick,//�J�[�\���ŃN���b�N�����Ƃ��̉�
		
		SoundId_Select,//���肵���Ƃ��̉�
		
		SoundId_Attack,//�U����
		SoundId_Hit,	//��e��
		
		SoundId_Num
	}SoundId;

	//���[�h�A�A�����[�h
	void Load();
	void Unload();

	//BGM�̍Đ�
	void StartBgm(SoundId id, int volume );
	void StopBgm(SoundId id);

	//���ʉ��̍Đ�
	void Play(SoundId id);

	//���ʐݒ�
	void SetVolume(SoundId id, int volume);
}