#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

void CScene_Start::Enter()
{
	// Object �߰�
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT);
	
	// Monster Object �߰�
	// ���� ����� ���ÿ� ������ �ϸ�? -> ���� �����ڰ� ȣ���
	int iMonCount = 16;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonsterObj = nullptr;
	
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);

	for (int i = 0; i < iMonCount; ++i)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + fTerm * i, 50.f));
		pMonsterObj->SetCenterPos(Vec2(pMonsterObj->GetPos()));
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, 50.f));
		AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);
	}
}

void CScene_Start::Exit()
{
}

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

