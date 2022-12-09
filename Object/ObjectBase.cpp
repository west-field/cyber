#include "ObjectBase.h"
#include "DxLib.h"
namespace
{
	constexpr int kMaxHp = 100;
}

ObjectBase::ObjectBase()
{
	m_nowHp = 0;
	m_graph = -1;
	m_graphSizeX = 0;
	m_graphSizeY = 0;
	m_attackGraph = -1;
	m_attackGraphSizeX = 0;
	m_attackGraphSizeY = 0;
}

ObjectBase::~ObjectBase()
{

}

void ObjectBase::SetGraph(int handle/*, int damageGraph*/)
{
	m_graph = handle;
	//GetGraphSize(m_graph, &m_graphSizeX, &m_graphSizeY);
	/*m_attackGraph = damageGraph;
	GetGraphSize(m_attackGraph, &m_attackGraphSizeX, &m_attackGraphSizeY);*/
}

void ObjectBase::Damage(const int damage)
{
	SetHp(m_nowHp - damage);
}

void ObjectBase::Heal(const int heal)
{
	SetHp(m_nowHp + heal);
}

void ObjectBase::SetHp(const int hp)
{
	if (hp >= kMaxHp)
	{
		m_nowHp = kMaxHp;
	}
	else if (hp <= 0)
	{
		m_nowHp = 0;
	}
	else
	{
		m_nowHp = hp;
	}
}

