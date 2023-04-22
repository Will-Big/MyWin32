#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
		vPos.y -= 200.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
		vPos.y += 200.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * fDT;
	}

	SetPos(vPos);
}

//void CPlayer::render(HDC _dc)
//{
//	Vec2 vPos = GetPos();
//	Vec2 vScale = GetScale();
//
//	Rectangle(_dc,
//		int(vPos.x - vScale.x / 2.f),
//		int(vPos.y - vScale.y / 2.f),
//		int(vPos.x + vScale.x / 2.f),
//		int(vPos.y + vScale.x / 2.f));
//}
