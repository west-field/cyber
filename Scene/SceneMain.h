#pragma once
#include "SceneBase.h"
#include "Pieces.h"

#include "Bg.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();


	virtual void init()override;
	virtual void end()override;

	virtual SceneBase* update()override;
	virtual void draw()override;
private:
	Pieces m_piece;

	Bg m_bg;
	
	int m_select;
	int m_fade;
	int m_fadeSpeed;
};