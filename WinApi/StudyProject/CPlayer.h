#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:
    CTexture*   m_pTex;

public:
    void update() override;
    void render(HDC _dc) override;

private:
    void CreateMissile();

public:
    CPlayer();
    ~CPlayer();
};

