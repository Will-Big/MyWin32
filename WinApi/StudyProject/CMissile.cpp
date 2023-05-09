#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

#include "CPathMgr.h"

#include "CTexture.h"
#include "CResMgr.h"

#include "CCore.h"

#include "CCollider.h"


CMissile::CMissile()
	: m_fTheta(3.f * PI / 2.f)
	, m_vDir(Vec2(1.f, 1.f))
	, m_pTex(nullptr)
	, m_fRadian(0.f)
	, m_pRotate{}
{
	m_vDir.Normalize();
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Missile", L"texture//FireBall.bmp");
	//m_pTex->MakeTransparent();
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(12.5f, 12.5f));
	GetCollider()->SetScale(Vec2(25.f, 25.f));
}

CMissile::~CMissile()
{
}

void CMissile::Rotate(float _fRadian)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	POINT points[3] = { 0, };

	points[0] = { (int)vPos.x, (int)vPos.y };
	points[1] = { (int)(vPos.x + vScale.x), (int)vPos.y };
	points[2] = { (int)vPos.x, (int)(vPos.y + vScale.y) };

	// 오브젝트 로컬 좌표로 원점이동
	POINT center = { vPos.x + vScale.x / 2, vPos.y + vScale.y / 2 };
	{
		for (int i = 0; i < 3; ++i)
		{
			points[i].x -= center.x;
			points[i].y -= center.y;
		}
	}

	// 회전
	{
		float cosScalr = cos(_fRadian);
		float sinScalr = sin(_fRadian);
		POINT temp;

		for (int i = 0; i < 3; ++i)
		{
			temp.x = points[i].x * cosScalr - points[i].y * sinScalr;
			temp.y = points[i].x * sinScalr + points[i].y * cosScalr;
			points[i] = temp;
		}
	}

	// 월드 좌표로 원점이동
	{
		for (int i = 0; i < 3; ++i)
		{
			points[i].x += center.x;
			points[i].y += center.y;
		}
	}

	m_pRotate[0] = points[0];
	m_pRotate[1] = points[1];
	m_pRotate[2] = points[2];
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	//vPos.x += 600.f * cosf(m_fTheta) * fDT;
	//vPos.y -= 600.f * sinf(m_fTheta) * fDT;

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;
	m_fRadian += PI * fDT * 10.f;

	if (m_fRadian > 2 * PI)
		m_fRadian = 0.f;

	Rotate(m_fRadian);

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	HDC hdcTex = m_pTex->GetDC();

   	BOOL boo = PlgBlt(_dc, m_pRotate, hdcTex, 0, 0, iWidth, iHeight, 0, 0, 0);

	component_render(_dc);
}
