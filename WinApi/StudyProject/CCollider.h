#pragma once

class CObject;

class CCollider
{
private:
	CObject*	m_pOwner; // Collider 를 소유하고 있는 오브젝트

	Vec2		m_vOffsetPos; // 기준점으로부터의 거리
	Vec2		m_vFinalPos; // finalupdate 에서 매 프레임마다 계산

	Vec2		m_vScale; // 충돌체의 크기

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

public:
	void finalupdate();

public:
	CCollider();
	~CCollider();

	friend class CObject;
};

