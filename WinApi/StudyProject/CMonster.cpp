#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CMissile.h"
#include "CScene.h"
#include "CSceneMgr.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CAnimator.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_bAttackAble(false)
	, m_dLastAttack(0)
	, m_dAttackCooldown(1.0)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Monster", L"texture\\Goomba.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Goomba", m_pTex, Vec2(0, 0), Vec2(256, 256), Vec2(256, 256), 1.f, 1);
	GetAnimator()->Play(L"Goomba", true);
	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));
}

CMonster::~CMonster()
{
}

void CMonster::Attack()
{
	Vec2 vCurPos = GetPos();
	Vec2 vCurScale = GetScale();

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(Vec2(vCurPos.x, vCurScale.y / 2.f));
	pMissile->SetScale(Vec2(GetScale().x / 2.f, GetScale().y / 2.f));
	pMissile->SetDir(Vec2(0.f, 1.f));
	pMissile->SetName(L"Missile");
	pMissile->GetCollider()->SetScale(Vec2(pMissile->GetScale()));
	pMissile->GetCollider()->SetOffsetPos(Vec2(pMissile->GetScale().x / 2.f, pMissile->GetScale().y / 2.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);


	m_bAttackAble = false;
}

void CMonster::OnCollision(CCollider* _pOther)
{
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	// 내 맘대로
 	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_iHp--;

		if (m_iHp <= 0)
			DeleteObject(this);
	}
}

void CMonster::OnCollisionExit(CCollider* _pOther)
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

	SetPos(vCurPos);

	if (m_bAttackAble)
		Attack();
	else
	{
		m_dLastAttack += fDT;

		if (m_dLastAttack > m_dAttackCooldown)
		{
			m_dLastAttack -= m_dAttackCooldown;
			m_bAttackAble = true;
		}
	}
}

void CMonster::render(HDC _dc)
{
	//int iWidth = (int)m_pTex->Width();
	//int iHeight = (int)m_pTex->Height();

	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();

	//// 투명화
	////TransparentBlt(_dc
	////	, vPos.x - (float)(iWidth / 2)
	////	, vPos.y - (float)(iHeight / 2)
	////	, iWidth, iHeight
	////	, m_pTex->GetDC()
	////	, 0, 0, iWidth, iHeight
	////	, RGB(255, 0, 255));

	//TransparentBlt(_dc
	//	, (int)(vPos.x - (float)(vScale.x / 2))
	//	, (int)(vPos.y - (float)(vScale.y / 2))
	//	, (int)vScale.x
	//	, (int)vScale.y
	//	, m_pTex->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, RGB(255, 255, 255));

	component_render(_dc);
}


