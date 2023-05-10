#pragma once
#include "CObject.h"
class MySkill :
    public CObject
{
private:
    wstring m_strName;
    float   m_fDamage;
    float   m_fCooldown;
    float   m_fCost;
    Vec2    m_vRange;
    Vec2    m_vEffectArea;

public:
    const wstring& GetName() { return m_strName; };
    void SetName(const wstring& _strName) { m_strName = _strName; }
    const float GetDamage() { return m_fDamage; };
    void SetDamage(float _damage) { m_fDamage = _damage; }
    const float GetCooldown() { return m_fCooldown; };
    void SetCooldown(float _cooldown) { m_fCooldown = _cooldown; }
    const float GetCost() { return m_fCost; };
    void SetCost(float _cost) { m_strName = _cost; }
    const Vec2 GetRange() { return m_vRange; };
    void SetRange(Vec2 _range) { m_vRange = _range; }
    const Vec2 GetEffectArea() { return m_vEffectArea; };
    void SetEffectArea(Vec2 _effectArea) { m_vEffectArea = _effectArea; }


public:
    virtual void init() = 0;
    virtual void update() override = 0;
    virtual void render(HDC _dc) override = 0;

};

