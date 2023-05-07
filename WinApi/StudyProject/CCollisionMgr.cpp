#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::init()
{
}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 행 : 0 ~ 31, 열 : 31 ~ 0
	UINT iRow = (UINT)_eLeft;	// 작은 값의 그룹 타입을 행으로
	UINT iCol = (UINT)_eRight;	// 큰 값의 그룹 타입을 열으로

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	// iCol 만큼 비트 연산으로 밀어서 iRow에 넣기
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// 반환 타입을 참조로 줬지만 원본이 아님!
	// 반환은 원본, 하지만 복사해서 받았기에 지역변수가 됨
	// 따라서 받을 때도 참조로 받아야 함
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	unordered_map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체가 없을 경우
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// 충돌체가 없거나 자신과 같은 주소값(=자기 자신)을 갖는 오브젝트일 경우
			if (vecRight[j]->GetCollider() == nullptr || vecLeft[i] == vecRight[j])
				continue;

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// 두 총돌체의 조합 아이디 생성
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// 등록되지 않은 아이디
			if (iter == m_mapColInfo.end())
			{
				// 새로운 아이디 생성(충돌하지 않음)
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			
			// 이전 프레임의 정보를 이용해서
			// 충돌 전인지, 충돌 중이었는지, 충돌을 벗어났는지 확인함
			if (IsCollision(pLeftCol, pRightCol))
			{
				// 현재 충돌 중
				if (iter->second)
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// 삭제 예정인 오브젝트와 충돌했다면, 충돌 해제
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						// 이전에도 충돌 함
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						// 이전에는 충돌하지 않음
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
					// 삭제 예정인 오브젝트와 충돌했다면 충돌 처리하지 않음
				}

			}
			else
			{
				// 현재 충돌 중이 아님
				if (iter->second)
				{
					// 이전에는 충돌 함
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
				// 삭제 예정인 오브젝트라면 굳이 따로 처리해주지 않아도
				// 이 구문에서 알아서 Exit 함수를 수행해주기 떄문에
				// 예외처리를 할 필요가 없음
			}

		}
	}

}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();
	
	if (abs(vLeftPos.x - vRightPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vLeftPos.y - vRightPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}
