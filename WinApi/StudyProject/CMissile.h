#pragma once
#include "CObject.h"
class CMissile :
	public CObject
{
private:
	float		m_fTheta;		// 위 아래 방향
	Vec2		m_vDir;

public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; }
	void SetDir(Vec2 _vDir) 
	{ 
		m_vDir = _vDir; 
		m_vDir.Normalize();
	}

public:
	void update() override;
	void render(HDC _dc) override;

public:
	CMissile();
	~CMissile();
};

