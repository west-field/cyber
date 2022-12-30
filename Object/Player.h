#pragma once
#include "../Util/Vec2.h"

class Player
{
public:
	//プレイヤーグラフィック分割数
	static constexpr int kGraphicDivX = 3;//static　プログラム開始時に作成される　プログラムが終了するまで確保される
	static constexpr int kGraphicDivY = 2;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY - 1;

	//プレイヤーグラフィックサイズ
	static constexpr int kGraphicSizeX = 150;
	static constexpr int kGraphicSizeY = 140;

	Player();
	virtual ~Player();
	 void Init();
	 //攻撃判定
	 void Update();
	 //プレイヤーとHPバーを表示
	 void Draw();

	//グラフィックとエフェクトグラフィックを取得
	 void SetEffectGraph(int effectHandle);
	 void SetGraph(int graphHandle, int index);

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

	 //グラフィック表示位置
	 Vec2 m_pos;
	 //グラフィック
	 int m_handle[kGraphicDivNum];
	 int m_animeNo;//表示する番号
	 int m_animeFrame;//フレーム

	 //攻撃
	 int m_attackGraph;
	 //グラフィック表示位置
	 Vec2 m_attackPos;

	 bool m_isDamage;

	 int m_fade;
	 int m_fadeSpeed;
	 int m_effectDrawTime;
};

