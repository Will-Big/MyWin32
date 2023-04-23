#pragma once
#include "CObject.h"
class CMissile :
	public CObject
{
private:
	float		m_fDir;		// 위 아래 방향
	float		m_xDir;		// 좌 우 방향
	float		m_xSpeed;	// 좌 우 속도
	float		m_xCurve;	// x 커브 좌표
	float		m_xStart;	// x 시작 좌표
	

public:
	void SetDir(bool _bUp) { _bUp ? m_fDir = -1.f : m_fDir = 1.f; }
	void SetXstart(float _x) { m_xStart = _x; }

public:
	void update() override;
	void render(HDC _dc) override;

public:
	CMissile();
	~CMissile();
};

