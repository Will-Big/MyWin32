#pragma once
class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];
public:
	void init();
	void update();
	// 비트연산을 할때 세로 0 ~ 31, 가로 31 ~ 0 이라는데 왜?
	// 작은 숫자가 인덱스에서 먼저 와야 함
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }
};

