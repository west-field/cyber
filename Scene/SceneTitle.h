#pragma once
#include "SceneBase.h"

enum eMenu {
	eMenu_GameStart,		//ゲーム

	eMenu_Num,				//本項目の数
};

// メニュー項目の表示に必要な構造体を用意する
struct MenuElement_t {
	int x;       // 座標格納用変数
	int y;
	char name[128]; // 項目名格納用変数
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
	int m_selectNum;// 現在の選択番号
	//選択先の項目
	int m_nextItem;
	//カーソルの移動フレームカウント
	int m_moveFrame;
	//フェード処理
	int m_fade;
	int m_fadeSpeed;
	//背景
	int m_bgGraph;
	//メニュー表示に初めて重なったかどうか
	bool m_isFirst;
};