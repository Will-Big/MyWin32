#pragma once
#include "CObject.h"
class CMissile :
	public CObject
{
private:
	float		m_fDir;		// �� �Ʒ� ����
	float		m_xDir;		// �� �� ����
	float		m_xSpeed;	// �� �� �ӵ�
	float		m_xCurve;	// x Ŀ�� ��ǥ
	float		m_xStart;	// x ���� ��ǥ
	

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

