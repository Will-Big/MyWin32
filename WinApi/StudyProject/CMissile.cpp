#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fDir(1.f)
	, m_xDir(1.f)
	, m_xSpeed(100.f)
	, m_xCurve(5.f)
	, m_xStart(0.f)
{
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();
	vPos.y += 300.f * fDT * m_fDir;
	vPos.x += m_xSpeed * fDT * m_xDir;

	float fxOver = abs(m_xStart - vPos.x) - abs(m_xCurve);

	if (fxOver > 0)
	{
		m_xDir *= -1;
		vPos.x += m_xDir * fxOver;
		m_xCurve = (-1) * abs(m_xCurve * 1.5f);
		m_xSpeed *= 1.35f;
	}

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Ellipse(_dc,
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.x / 2.f));
}
