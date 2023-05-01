#pragma once
// 오브젝트는 직접 생성할 이유가 없는 클래스이기 때문에
// 순수 가상함수를 만들어서 추상 클래스화 해준다.

class CCollider;

class CObject
{
private:
	Vec2		m_vPos;
	Vec2		m_vScale;

	CCollider*	m_pCollider;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void CreateCollider();
	CCollider* GetCollider() { return m_pCollider; }

public:
	virtual void update() = 0;
	virtual void finalupdate() final;
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

public:
	CObject();
	virtual ~CObject();
};

