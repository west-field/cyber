#pragma once
#include "SceneBase.h"
class GameClearScene :   public SceneBase
{
public:
	GameClearScene();
	virtual ~GameClearScene();

	virtual void init()override;
	virtual void end()override;

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	int m_fade;
	int m_fadeSpeed;

	int m_graph;
};

