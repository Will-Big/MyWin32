#pragma once
#include "CObject.h"

class CTexture;

class CMissile :
	public CObject
{
private:
	float		m_fTheta;		// �� �Ʒ� ����
	Vec2		m_vDir;
	// ������� ��� ����
	float		m_fRadian;
	CTexture*	m_pTex;
	POINT		m_pRotate[3];

public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; }
	void SetDir(Vec2 _vDir) 
	{ 
		m_vDir = _vDir; 
		m_vDir.Normalize();
	}
	// ������� �Լ�
	void Rotate(float _fRadin);
	void OnCollisionEnter(CCollider* _pOther) override;

public:
	void update() override;
	void render(HDC _dc) override;

public:
	CMissile();
	~CMissile();
};

