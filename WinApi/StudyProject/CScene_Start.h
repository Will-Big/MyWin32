#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
public:
    virtual void update() override;

public:
    // virtual(override) �� �Ⱥٿ��� �������� ��������� �˸��� ���� �ۼ�
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CScene_Start();
    ~CScene_Start();
};
