#pragma once
#include "SceneBase.h"
#include "../Object/Pieces.h"

class SceneTest : public SceneBase
{
public:
	SceneTest();
	virtual ~SceneTest() {}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update()override;
	virtual void draw()override;
private:
	Pieces m_pieces;

	int m_select;
	int m_fade;
	int m_fadeSpeed;
};