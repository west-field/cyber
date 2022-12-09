#pragma once
#include "Vec2.h"

class Player
{
public:
	Player();
	virtual ~Player();
	 void Init();
	 //�U������
	 void Update();
	 //�v���C���[��HP�o�[��\��
	 void Draw();

	//�O���t�B�b�N�ƃO���t�B�b�N�̃T�C�Y���擾
	 void SetGraph(int graphHandle, int effectHandle);

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

	 //�O���t�B�b�N
	 int m_graph;
	 //�O���t�B�b�N�\���ʒu
	 Vec2 m_pos;
	 
	 //�U��
	 int m_attackGraph;
	 //�O���t�B�b�N�\���ʒu
	 Vec2 m_attackPos;

	 bool m_isDamage;

	 int m_fade;
	 int m_fadeSpeed;
	 int m_effectDrawTime;
};

