#pragma once
#include "../Util/Vec2.h"

class Player
{
public:
	//�v���C���[�O���t�B�b�N������
	static constexpr int kGraphicDivX = 3;//static�@�v���O�����J�n���ɍ쐬�����@�v���O�������I������܂Ŋm�ۂ����
	static constexpr int kGraphicDivY = 2;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY - 1;

	//�v���C���[�O���t�B�b�N�T�C�Y
	static constexpr int kGraphicSizeX = 150;
	static constexpr int kGraphicSizeY = 140;

	Player();
	virtual ~Player();
	 void Init();
	 //�U������
	 void Update();
	 //�v���C���[��HP�o�[��\��
	 void Draw();

	//�O���t�B�b�N�ƃG�t�F�N�g�O���t�B�b�N���擾
	 void SetEffectGraph(int effectHandle);
	 void SetGraph(int graphHandle, int index);

	 bool GetIsDamage() const { return m_isDamage; }

	//HP���擾����
	 int GetHp() const { return static_cast<int>(m_nowHp); }
	//�_���[�W�v�Z
	 void Damage(const float damage);
	//�񕜌v�Z
	 void Heal(const float heal);
private:
	 //HP�̍ő�A�ŏ��𒴂��Ȃ��͈͂�m_hp�ɃZ�b�g����
	 virtual void SetHp(const float hp);

	 //���݂�HP
	 float m_nowHp;
	 //�摜�̕��ő�l
	 float m_hpWidth;

	 //�O���t�B�b�N�\���ʒu
	 Vec2 m_pos;
	 //�O���t�B�b�N
	 int m_handle[kGraphicDivNum];
	 int m_animeNo;//�\������ԍ�
	 int m_animeFrame;//�t���[��

	 //�U��
	 int m_attackGraph;
	 //�O���t�B�b�N�\���ʒu
	 Vec2 m_attackPos;

	 bool m_isDamage;

	 int m_fade;
	 int m_fadeSpeed;
	 int m_effectDrawTime;
};

