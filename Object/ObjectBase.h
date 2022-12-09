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

	//�O���t�B�b�N�ƃO���t�B�b�N�̃T�C�Y���擾
	virtual void SetGraph(int handle/*,int attackGraph*/);

	//HP���擾����
	virtual int GetHp() const { return m_nowHp; }
	//�_���[�W�v�Z
	virtual void Damage( const int damage);
	//�񕜌v�Z
	virtual void Heal(const int heal);
protected:
	//�O���t�B�b�N
	int m_graph;
	//�O���t�B�b�N�̑傫��
	int m_graphSizeX;
	int m_graphSizeY;
	//�U��
	int m_attackGraph;
	//�O���t�B�b�N�̑傫��
	int m_attackGraphSizeX;
	int m_attackGraphSizeY;
private:
	//HP�̍ő�A�ŏ��𒴂��Ȃ��͈͂�m_hp�ɃZ�b�g����
	virtual void SetHp(const int hp);

	//���݂�HP
	int m_nowHp;
};

