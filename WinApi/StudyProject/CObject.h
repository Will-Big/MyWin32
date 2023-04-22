#pragma once
// 오브젝트는 직접 생성할 이유가 없는 클래스이기 때문에
// 순수 가상함수를 만들어서 추상 클래스화 해준다.
class CObject
{
private:
	Vec2	m_vPos;
	Vec2	m_vScale;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	CObject();
	virtual ~CObject();
};

