#pragma once

class Bg
{
public:
	Bg();
	virtual ~Bg();

	void Init();

	void SetGraph(int blueHandle);

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

