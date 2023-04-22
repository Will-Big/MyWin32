#pragma once
#include "CObject.h"
class CPlayer :
    public CObject
{
public:
    void update() override;
    //void render(HDC _dc) override;
};

