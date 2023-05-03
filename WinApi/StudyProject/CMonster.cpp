#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CMissile.h"
#include "CScene.h"
#include "CSceneMgr.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CCollider.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Monster", L"texture\\Goomba.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	// 진행 방향으로 시간당 m_fSpeed 만큼 이동
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	float fDist = abs(vCurPos.x - m_vCenterPos.x) - m_fMaxDistance;

	if (fDist > 0.f)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	double dPrevSec = dCurSec;
	// 몬스터마다 받아오는 시간이 다르다면 ... 누군가는 안쏴야하는거 아닌가?
	// -> CTimeMgr 가 같은 시간을 보장한다!
	dCurSec = CTimeMgr::GetInst()->GetdAcc();

	Vec2 vMisslePos = vCurPos;
	vMisslePos.y += GetScale().y / 2.f;

	//if (dCurSec < dPrevSec)
	//{
	//	CMissile* pMissile = new CMissile;
	//	pMissile->SetPos(vMisslePos);
	//	pMissile->SetDir(Vec2(0.f, 1.f));
	//	pMissile->SetScale(Vec2(GetScale().x / 2.f, GetScale().y / 2.f));
	//	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	//	pCurScene->AddObject(pMissile, GROUP_TYPE::MONSTER);
	//}

	SetPos(vCurPos);
}

void CMonster::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	// 투명화
	//TransparentBlt(_dc
	//	, vPos.x - (float)(iWidth / 2)
	//	, vPos.y - (float)(iHeight / 2)
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, RGB(255, 0, 255));

	TransparentBlt(_dc
		, (int)(vPos.x - (float)(vScale.x / 2)) // 0 ~ 50
		, (int)(vPos.y - (float)(vScale.y / 2)) // 25 ~ 25
		, (int)vScale.x // 50
		, (int)vScale.y // 50
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 255, 255));

	component_render(_dc);
}


