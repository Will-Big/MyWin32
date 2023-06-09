#pragma once
// 오브젝트는 직접 생성할 이유가 없는 클래스이기 때문에
// 순수 가상함수를 만들어서 추상 클래스화 해준다.

#include "CCamera.h"

class CCollider;
class CAnimator;

class CObject
{
private:
	wstring		m_strName;

	Vec2		m_vPos;
	Vec2		m_vScale;

	CCollider*	m_pCollider;
	CAnimator*	m_pAnimator;

	bool		m_bAlive;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void CreateCollider();
	CCollider* GetCollider() { return m_pCollider; }

	void CreateAnimator();
	CAnimator* GetAnimator() { return m_pAnimator; }

	bool IsDead() { return !m_bAlive; }

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

public:
	virtual void update() = 0;
	virtual void finalupdate() final;
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	// 자신의 복제 버전을 되돌려주는 역할
	virtual CObject* Clone() = 0;

private:
	// EventMgr 에서만 처리
	void SetDead() { m_bAlive = false; }

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class CEventMgr;
};

