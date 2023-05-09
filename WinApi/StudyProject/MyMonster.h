#pragma once
#include "CObject.h"
class MyMonster :
    public CObject
{
private:
    int     m_iHp;
    int     m_iDef;
    int     m_iDamage;
    float   m_fAttackRange;
    float   m_fAttackPerSecond; //  == Attack Speed
};

