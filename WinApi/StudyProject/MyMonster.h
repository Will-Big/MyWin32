#pragma once
#include "CObject.h"

class MySkill;

class MyMonster :
    public CObject
{
private:
    wstring m_strName;

    float   m_fHp;
    float   m_fDef;
    float   m_fDamage;
    float   m_fAttackSpeed;
    float   m_fSpeed;

    map<wstring, MySkill*> m_mapSkill;

public:
    const wstring& GetName() { return m_strName; }
    void SetName(const wstring _strName) { m_strName = _strName; }

    const float GetHp() { return m_fHp; }
    void SetHp(float _hp) { m_fHp = _hp; }

    const float GetDef() { return m_fDef; }
    void SetDef(float _def) { m_fDef = _def; }

    const float GetDamage() { return m_fDamage; }
    void SetDamage(float _damage) { m_fDef = _damage; }

    const float GetAttackSpeed() { return m_fAttackSpeed; }
    void SetAttackSpeed(float _attackSpeed) { m_fAttackSpeed = _attackSpeed; }

    const float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _speed) { m_fSpeed = _speed; }

    const MySkill* GetSkill(const wstring& _strName);
    void AddSkill(const wstring& _strName, MySkill* _skill);
    void DeleteSkill(const wstring& _strName, MySkill* _skill);

public:
    virtual void Attack() = 0;

public:
    virtual void init() = 0;
    virtual void update() override = 0;
    virtual void render(HDC _dc) override = 0;

public:
    MyMonster();
    virtual ~MyMonster();
};

