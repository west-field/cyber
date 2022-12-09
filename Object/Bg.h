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
	//グラフィック
	int m_bgBlueGraph;
	int m_bgGreenGraph;
	//＋
	int m_add;
	//点滅しているように見せる
	int m_fade;
};

