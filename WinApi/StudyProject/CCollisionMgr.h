#pragma once

class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	 // 충돌체 간의 이전 프레임 충돌 정보
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // 그룹 간의 충돌 체크 매트릭스

public:
	void init();
	void update();
	// 비트연산을 할때 세로 0 ~ 31, 가로 31 ~ 0 이라는데 왜?
	// 작은 숫자가 인덱스에서 먼저 와야 함
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

