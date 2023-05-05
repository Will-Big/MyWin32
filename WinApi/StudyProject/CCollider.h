#pragma once

class CObject;

class CCollider
{
private:
	static UINT	g_iNextID;

	CObject*	m_pOwner;		// Collider 를 소유하고 있는 오브젝트
	Vec2		m_vOffsetPos;	// 기준점으로부터의 거리
	Vec2		m_vFinalPos;	// finalupdate 에서 매 프레임마다 계산
	Vec2		m_vScale;		// 충돌체의 크기

	UINT		m_iID;			// 충돌체 고유한 ID 값
	UINT		m_iCol;


public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }

	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther);
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);
	// 디폴트 생성자를 이용한 대입을 방어함
	// '=' 연산자 자체를 사용하지 못하게 하는 코드
	CCollider& operator=(CCollider& _origin) = delete;


public:
	CCollider();
	// 디폴트 복사 생성자를 사용하여 콜라이더 객체를 복사하면
	// ID 값이 중복되기 때문에 명시적인 복사 생성자의 정의가 필요하다
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};



