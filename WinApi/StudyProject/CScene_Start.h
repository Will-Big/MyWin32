#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
public:
    // virtual(override) �� �Ⱥٿ��� �������� ��������� �˸��� ���� �ۼ�
    void Enter() override;
    void Exit() override;

public:
    CScene_Start();
    ~CScene_Start();
};
