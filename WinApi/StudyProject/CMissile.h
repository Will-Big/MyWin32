#pragma once
#include "CObject.h"
class CMissile :
	public CObject
{
private:
	float		m_fTheta;		// �� �Ʒ� ����

public:
	float SetDir(float _fTheta) { return m_fTheta; }

public:
	void update() override;
	void render(HDC _dc) override;

public:
	CMissile();
	~CMissile();
};

