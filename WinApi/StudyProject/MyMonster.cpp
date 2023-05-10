#include "pch.h"
#include "MyMonster.h"

const MySkill* MyMonster::GetSkill(const wstring& _strName)
{
	map<wstring, MySkill*>::iterator iter = m_mapSkill.find(_strName);

	if (iter == m_mapSkill.end()) // 스킬 존재 여부 검사
		return nullptr;
	else
		return iter->second;
}

void MyMonster::AddSkill(const wstring& _strName, MySkill* _skill)
{
	map<wstring, MySkill*>::iterator iter = m_mapSkill.find(_strName);

	assert(iter == m_mapSkill.end()); // 중복 스킬명 검사

	m_mapSkill.insert(make_pair(_strName, _skill));
}

void MyMonster::DeleteSkill(const wstring& _strName, MySkill* _skill)
{
	map<wstring, MySkill*>::iterator iter = m_mapSkill.find(_strName);

	if (iter == m_mapSkill.end()) // 스킬 존재 여부 검사
		return;

	m_mapSkill.erase(iter);
}

void MyMonster::update()
{
}

void MyMonster::render(HDC _dc)
{
}

MyMonster::MyMonster()
	: m_fHp(0.f)
	, m_fDef(0.f)
	, m_fDamage(0.f)
	, m_fAttackSpeed(0.f)
	, m_fSpeed(0.f)
{
}

MyMonster::~MyMonster()
{
	Safe_Delete_Map(m_mapSkill);
}

