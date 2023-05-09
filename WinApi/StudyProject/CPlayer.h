#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:

public:
    void update() override;
    void render(HDC _dc) override;

private:
    void CreateMissile();

    CLONE(CPlayer);

public:
    CPlayer();
    ~CPlayer();
};

