#pragma once
#include "CScene.h"
class CScene_Tool :
    public CScene
{
private:
    
public:
    virtual void update() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    CScene_Tool();
    ~CScene_Tool();
};

