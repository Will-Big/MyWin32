#pragma once
class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];
public:
	void init();
	void update();
	// ��Ʈ������ �Ҷ� ���� 0 ~ 31, ���� 31 ~ 0 �̶�µ� ��?
	// ���� ���ڰ� �ε������� ���� �;� ��
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }
};

