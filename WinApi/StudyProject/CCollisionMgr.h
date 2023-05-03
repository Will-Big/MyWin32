#pragma once

class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	 // �浹ü ���� ���� ������ �浹 ����
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // �׷� ���� �浹 üũ ��Ʈ����

public:
	void init();
	void update();
	// ��Ʈ������ �Ҷ� ���� 0 ~ 31, ���� 31 ~ 0 �̶�µ� ��?
	// ���� ���ڰ� �ε������� ���� �;� ��
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

