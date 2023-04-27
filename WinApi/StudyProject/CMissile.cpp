#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

#include "CPathMgr.h"

#include "CTexture.h"
#include "CResMgr.h"

#include "CCore.h"


CMissile::CMissile()
	: m_fTheta(3.f * PI / 2.f)
	, m_vDir(Vec2(1.f, 1.f))
	, m_pTex(nullptr)
	, m_fRadian(0.f)
	, m_pRotate{}
{
	m_vDir.Normalize();
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Missile", L"texture//FireBall.bmp");
	CreateCollider();
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

	// UV좌표 지정
	//POINT UV = { 37, 40 };
	//POINT UV_SIZE = { 21, 24 };
	//PlgBlt(backMemDC, points, textureDC, UV.x, UV.y, UV_SIZE.x, UV_SIZE.y, 0, 0, 0);

	m_pRotate[0] = points[0];
	m_pRotate[1] = points[1];
	m_pRotate[2] = points[2];
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	//vPos.x += 600.f * cosf(m_fTheta) * fDT;
	//vPos.y -= 600.f * sinf(m_fTheta) * fDT;

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;
	m_fRadian += PI * fDT;

	//Rotate(m_fRadian);


	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	//HDC tempDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	TransparentBlt(_dc
		, (int)(vPos.x - (float)(vScale.x / 2))
		, (int)(vPos.y - (float)(vScale.y / 2))
		, (int)vScale.x, (int)vScale.y
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 255, 255));

 	//BOOL boo = PlgBlt(_dc, m_pRotate, tempDC, vPos.x, vPos.y, vScale.x, vScale.y, 0, 0, 0);
	
	//StretchBlt(_dc
	//	, vPos.x - (float)(vScale.x / 2)
	//	, vPos.y - (float)(vScale.y / 2)
	//	, vScale.x
	//	, vScale.y
	//	, m_pTex->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, SRCCOPY);

	//HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
	//FillRect(m_pTex->GetDC(), )


}
