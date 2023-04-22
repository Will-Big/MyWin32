#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
public:
    // virtual 을 안붙여도 괜찮지만 명시적으로 알리기 위해 작성
    virtual void Enter();
    virtual void Exit();

public:
    CScene_Start();
    ~CScene_Start();
};
