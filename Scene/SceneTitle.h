#pragma once
#include "SceneBase.h"

enum eMenu {
	eMenu_GameStart,		//�Q�[��

	eMenu_Num,				//�{���ڂ̐�
};

// ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
struct MenuElement_t {
	int x;       // ���W�i�[�p�ϐ�
	int y;
	char name[128]; // ���ږ��i�[�p�ϐ�
};

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle() {}


	virtual void init()override;
	virtual void end() override;

	virtual SceneBase* update()override;
	virtual void draw()override;
private:
	int m_selectNum;// ���݂̑I��ԍ�
	//�I���̍���
	int m_nextItem;
	//�J�[�\���̈ړ��t���[���J�E���g
	int m_moveFrame;
	//�t�F�[�h����
	int m_fade;
	int m_fadeSpeed;
	//�w�i
	int m_bgGraph;
	//���j���[�\���ɏ��߂ďd�Ȃ������ǂ���
	bool m_isFirst;
};