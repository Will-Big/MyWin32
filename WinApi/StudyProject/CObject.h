#pragma once
// 오브젝트는 직접 생성할 이유가 없는 클래스이기 때문에
// 순수 가상함수를 만들어서 추상 클래스화 해준다.

class CCollider;

class CObject
{
private:
	wstring		m_strName;

	Vec2		m_vPos;
	Vec2		m_vScale;

	CCollider*	m_pCollider;

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

	bool IsDead() { return !m_bAlive; }

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

public:
	virtual void update() = 0;
	virtual void finalupdate() final;
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

private:
	// EventMgr 에서만 처리
	void SetDead() { m_bAlive = false; }

public:
	CObject();
	virtual ~CObject();

	friend class CEventMgr;
};

