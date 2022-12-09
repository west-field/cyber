#pragma once
#include "Vec2.h"

class Bg
{
public:
	Bg();
	virtual ~Bg();

	void Init();

	void SetGraph(int blueHandle/*, int greenHandle*/);

	void Update();
	void Draw();
private:
	//�O���t�B�b�N
	int m_bgBlueGraph;
	int m_bgGreenGraph;
	//�{
	int m_add;
	//�_�ł��Ă���悤�Ɍ�����
	int m_fade;
};

