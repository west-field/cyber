#pragma once
class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase();

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//グラフィックとグラフィックのサイズを取得
	virtual void SetGraph(int handle/*,int attackGraph*/);

	//HPを取得する
	virtual int GetHp() const { return m_nowHp; }
	//ダメージ計算
	virtual void Damage( const int damage);
	//回復計算
	virtual void Heal(const int heal);
protected:
	//グラフィック
	int m_graph;
	//グラフィックの大きさ
	int m_graphSizeX;
	int m_graphSizeY;
	//攻撃
	int m_attackGraph;
	//グラフィックの大きさ
	int m_attackGraphSizeX;
	int m_attackGraphSizeY;
private:
	//HPの最大、最小を超えない範囲でm_hpにセットする
	virtual void SetHp(const int hp);

	//現在のHP
	int m_nowHp;
};

