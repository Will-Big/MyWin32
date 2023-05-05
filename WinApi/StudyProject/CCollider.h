#pragma once

class CObject;

class CCollider
{
private:
	static UINT	g_iNextID;

	CObject*	m_pOwner;		// Collider �� �����ϰ� �ִ� ������Ʈ
	Vec2		m_vOffsetPos;	// ���������κ����� �Ÿ�
	Vec2		m_vFinalPos;	// finalupdate ���� �� �����Ӹ��� ���
	Vec2		m_vScale;		// �浹ü�� ũ��

	UINT		m_iID;			// �浹ü ������ ID ��
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
	// ����Ʈ �����ڸ� �̿��� ������ �����
	// '=' ������ ��ü�� ������� ���ϰ� �ϴ� �ڵ�
	CCollider& operator=(CCollider& _origin) = delete;


public:
	CCollider();
	// ����Ʈ ���� �����ڸ� ����Ͽ� �ݶ��̴� ��ü�� �����ϸ�
	// ID ���� �ߺ��Ǳ� ������ ������� ���� �������� ���ǰ� �ʿ��ϴ�
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};



