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

    vector<MySkill*> m_vecSkill;

public:
    const wstring& GetName() { return m_strName; }
    void SetName(const wstring _strName) { m_strName = _strName; }
    float GetHp() { return m_fHp; }
    void SetHp(float _hp) { m_fHp = _hp; }
    float GetDef() { return m_fDef; }
    void SetDef(float _def) { m_fDef = _def; }
    float GetDamage() { return m_fDamage; }
    void SetDamage(float _damage) { m_fDef = _damage; }
    float GetAttackSpeed() { return m_fAttackSpeed; }
    void SetAttackSpeed(float _attackSpeed) { m_fAttackSpeed = _attackSpeed; }
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _speed) { m_fSpeed = _speed; }

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

