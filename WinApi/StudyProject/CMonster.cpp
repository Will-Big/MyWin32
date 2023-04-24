#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CMissile.h"
#include "CScene.h"
#include "CSceneMgr.h"

void CMonster::update()
{
	Vec2 vCurPos = GetPos();
	
	// ���� �������� �ð��� m_fSpeed ��ŭ �̵�
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	float fDist = abs(vCurPos.x - m_vCenterPos.x) - m_fMaxDistance;

	if (fDist > 0.f)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	double dPrevSec = dCurSec;
	// ���͸��� �޾ƿ��� �ð��� �ٸ��ٸ� ... �������� �Ƚ����ϴ°� �ƴѰ�?
	// -> CTimeMgr �� ���� �ð��� �����Ѵ�!
	dCurSec = CTimeMgr::GetInst()->GetdAcc();

	Vec2 vMisslePos = vCurPos;
	vMisslePos.y += GetScale().y / 2.f;

	if (dCurSec < dPrevSec)
	{
		CMissile* pMissile = new CMissile;
		pMissile->SetPos(vMisslePos);
		pMissile->SetDir(false);
		pMissile->SetScale(Vec2(GetScale().x / 2.f, GetScale().y / 2.f));
		pMissile->SetXstart(vMisslePos.x);
		CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
		pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
	}

	SetPos(vCurPos);
}

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
}

CMonster::~CMonster()
{
}
