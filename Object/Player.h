#pragma once
#include "Vec2.h"

class Player
{
public:
	Player();
	virtual ~Player();
	 void Init();
	 //攻撃判定
	 void Update();
	 //プレイヤーとHPバーを表示
	 void Draw();

	//グラフィックとグラフィックのサイズを取得
	 void SetGraph(int graphHandle, int effectHandle);

	 bool GetIsDamage() const { return m_isDamage; }

	//HPを取得する
	 int GetHp() const { return static_cast<int>(m_nowHp); }
	//ダメージ計算
	 void Damage(const float damage);
	//回復計算
	 void Heal(const float heal);
private:
	 //HPの最大、最小を超えない範囲でm_hpにセットする
	 virtual void SetHp(const float hp);

	 //現在のHP
	 float m_nowHp;
	 //画像の幅最大値
	 float m_hpWidth;

	 //グラフィック
	 int m_graph;
	 //グラフィック表示位置
	 Vec2 m_pos;
	 
	 //攻撃
	 int m_attackGraph;
	 //グラフィック表示位置
	 Vec2 m_attackPos;

	 bool m_isDamage;

	 int m_fade;
	 int m_fadeSpeed;
	 int m_effectDrawTime;
};

