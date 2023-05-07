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

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// Texture �ε��ϱ�
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Mario.bmp");
	
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetCollider()->SetScale(Vec2(35.f, 80.f));
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
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}
	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
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
	// 23, 13:45 ����� ������ �����ϴ� ��찡 �־ int�� �޴´ٰ� �ߴµ�..
	// UINT �� int�� ĳ�����ϸ� ���������� �ǳ�?
	// ���� int �� �޾ƾ� �ϳ�?
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	// ����ȭ
	TransparentBlt(_dc
		, (int)(vPos.x - (float)(vScale.x / 2))
		, (int)(vPos.y - (float)(vScale.y / 2))
		, (int)vScale.x, (int)vScale.y
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	component_render(_dc);
}
