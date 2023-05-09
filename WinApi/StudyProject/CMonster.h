#pragma once
#include "CObject.h"


class CTexture;

class CMonster :
    public CObject
{
private:
    Vec2        m_vCenterPos;
    float       m_fSpeed;
    float       m_fMaxDistance;
    int         m_iDir; // 1, -1
    CTexture*   m_pTex;
    double      dCurSec = 0;
    
    // ³» ¸¾´ë·Î
    int         m_iHp = 5;
    bool        m_bAttackAble;
    double      m_dLastTime;
    

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
    void Attack();
    void OnCollision(CCollider* _pOther) override;
    void OnCollisionEnter(CCollider* _pOther) override;
    void OnCollisionExit(CCollider* _pOther) override;

public:
    void update() override;
    void render(HDC _dc) override;


    CLONE(CMonster);

public:
    CMonster();
    ~CMonster();
};

