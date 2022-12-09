#pragma once
#include "SceneBase.h"

class GameOverScene :   public SceneBase
{
public:
	GameOverScene();
	virtual ~GameOverScene();

	virtual void init()override;
	virtual void end()override;

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	int m_fade;
	int m_fadeSpeed;

	int m_graph;
};

