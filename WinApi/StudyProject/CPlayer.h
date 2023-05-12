#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:
    Vec2 m_vDir;

public:
    void update() override;
    void render(HDC _dc) override;

public:
    const Vec2& GetDir() { return m_vDir; }
    void SetDir(Vec2 _vDir) { m_vDir = _vDir; }

private:
    void CreateMissile();
    


    CLONE(CPlayer);

public:
    CPlayer();
    ~CPlayer();
};

