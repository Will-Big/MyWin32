#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CPathMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	// Texture 로딩하기
	// m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Mario.bmp");
	
	CreateCollider();
	//GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	//GetCollider()->SetScale(Vec2(35.f, 80.f));

	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE_DOWN", pTex, Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(0.f, 130.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"IDLE_UP", pTex, Vec2(0.f, 260.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0.f, 390.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 3);
	
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 10);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 650.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 10);
	GetAnimator()->CreateAnimation(L"WALK_UP", pTex, Vec2(0.f, 780.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 10);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 910.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 10);
	GetAnimator()->Play(L"IDLE_DOWN", true);

	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	//for (int i = 0; i < pAnim->GetMaxFrame(); ++i)
	//{
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	//}
	
}

CPlayer::~CPlayer()
{

}


void CPlayer::update()
{
	Vec2 vPos = GetPos();
	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
		SetDir(Vec2(0.f, -1.f));
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
		SetDir(Vec2(0.f, 1.f));
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
		SetDir(Vec2(-1.f, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
		SetDir(Vec2(1.f, 0.f));
	}
	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
	GetAnimator()->update();
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;
	
	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}


void CPlayer::render(HDC _dc)
{

	
	component_render(_dc);
}
